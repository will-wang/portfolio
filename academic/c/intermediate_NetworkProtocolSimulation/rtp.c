/*#include <sys/time_impl.h> -- mrb */
/* time_impl.h is Implementation-private, solaris specific.  The header file
specifically states that it should not be included by an application, that
<time.h> should instead be included, which includes the private header -mrb */
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

#include "queue.h"
#include "network64.h"
#include "rtp.h"

typedef struct _MESSAGE{
  char* buffer;
  int length;
} MESSAGE;

/* ================================================================ */
/*                  H E L P E R    F U N C T I O N S                */
/* ================================================================ */

/*
 *  Returns a number computed based on the data in the buffer.
 * 
 *
 */
static int checksum(char *buffer, int length){
  int checksum = 0;
  while (length--)
    checksum += *(buffer+length);
  return checksum;
}

/*
 *  Converts the given buffer into an array of PACKETs and returns
 *  the array.  The value of (*count) should be updated so that it 
 *  contains the length of the array created.
 */
static PACKET *packetize(char *buffer, int length, int *count){

  /*  ----  FIX ME  ----
   *
   *  The goal is to turn the buffer into an array of packets.
   *  You should allocate the space for an array of packets and
   *  return a pointer to the first element in that array.  The
   *  integer pointed to by 'count' should be updated to indicate
   *  the number of packets in the array.
   */ 

  int numPckts = length/MAX_PAYLOAD_LENGTH + ((length % MAX_PAYLOAD_LENGTH)?1:0);
  PACKET * array = malloc(sizeof(PACKET)*numPckts);
  int i,j;
  for (i = 0; i < numPckts; i++)
  {
    if (i < numPckts-1)
    {
      array[i].type = DATA;
      array[i].payload_length = MAX_PAYLOAD_LENGTH;
    }
    else if (i == numPckts-1)
    {
      array[i].payload_length = length % MAX_PAYLOAD_LENGTH;
      array[i].type = LAST_DATA;
    }

    array[i].checksum = 
      checksum(&buffer[MAX_PAYLOAD_LENGTH*i],array[i].payload_length);
    for (j = 0; j < array[i].payload_length; j++)
    {
      array[i].payload[j] = buffer[MAX_PAYLOAD_LENGTH*i+j];
    }
  }

  (*count)=numPckts;

  return array;

}

/* ================================================================ */
/*                      R T P       T H R E A D S                   */
/* ================================================================ */

static void *rtp_recv_thread(void *void_ptr){

  RTP_CONNECTION *connection = (RTP_CONNECTION*)void_ptr;

  do{
    MESSAGE *message;
    int buffer_length = 0;
    char *buffer = NULL;
    PACKET packet;

    /* 
     * put messages in buffer until the last packet is received 
     */  
    do {
      char *temp;

      if (net_recv_packet(connection->net_connection_handle, &packet) != 1){
        /* remote side has disconnected */
        free(buffer);
        connection->alive = 0;
        pthread_cond_signal(&(connection->recv_cond));
        pthread_cond_signal(&(connection->send_cond));
        break;
      }

      /* if this is a data packet then add the payload to the message buffer */
      if (packet.type == DATA || packet.type == LAST_DATA)
      {
        PACKET ack_pckt;
        ack_pckt.payload_length = 0;
        
        /*  ----  FIX ME  ----
      	 *
      	 * 1. check to make sure payload of packet is correct 
      	 * 2. send an ACK or a NACK, whichever is appropriate
      	 * 3. if this is the last packet in a sequence of packets
      	 *    and the payload was corrupted, make sure the loop
      	 *    does not terminate
      	 * 4. if the payload matches, add the payload to the buffer
      	 *    as done below
      	 */ 
     	  /* add payload of packet to buffer */
        if (packet.checksum == checksum(packet.payload,packet.payload_length))
        {
          temp = realloc(buffer,buffer_length+packet.payload_length);
          if (temp == NULL)
          {
            fprintf(stderr,"Out of memory!\n");
            exit (EXIT_FAILURE);
          }

          buffer = temp;
          memcpy(buffer+buffer_length,packet.payload,packet.payload_length);
          buffer_length += packet.payload_length;
          ack_pckt.type = ACK;
        }
        else
        {
          packet.type = ACK;
          ack_pckt.type = NACK;
        }

        if (net_send_packet(connection->net_connection_handle,&ack_pckt)<0)
        {
	        connection->alive = 0;
          break;
        }
      }

      /*  ----  FIX ME  ----
       * 
       *  What if the packet received is not a data packet?
       *  If it is a NACK or an ACK, the sending thread should
       *  be notified so that it can finish sending the message.
       *   
       *  1. add the necessary fields to the CONNECTION data structure
       *     in rtp.h so that the sending thread has a way to determine
       *     whether a NACK or an ACK was received
       *  2. signal the sending thread that an ACK or a NACK has been
       *     received.
       */
      else if (packet.type == ACK || packet.type == NACK)
      {
	connection -> NACK = (packet.type == NACK);
        connection->last_ack = &packet;
        pthread_cond_signal(&(connection->ack_cond));
      }
      else
      {
        PACKET ack_pckt;
        ack_pckt.type = NACK;
        net_send_packet(connection->net_connection_handle,&ack_pckt);
        continue;
      }
      
    } while (packet.type != LAST_DATA);
      
    if (connection->alive == 1)
    {
      /* add message to received queue */
      if ((message = malloc(sizeof(MESSAGE))) == NULL)
      {
	      fprintf(stderr,"Out of memory!\n");
	      exit (EXIT_FAILURE);
      }

      message->buffer = buffer;
      message->length = buffer_length;
      buffer = NULL;
      buffer_length = 0;
      
      pthread_mutex_lock(&(connection->recv_mutex));
      queue_add(&(connection->recv_queue),message);
      pthread_cond_signal(&(connection->recv_cond));
      pthread_mutex_unlock(&(connection->recv_mutex));
    }
    else
      free(buffer);
    
  } while (connection->alive == 1);

  return NULL;

}

static void *rtp_send_thread(void *void_ptr){

  RTP_CONNECTION *connection = (RTP_CONNECTION*)void_ptr;
  MESSAGE *message;
  int array_length=0, i;
  PACKET *packet_array;

  do {
    /* extract the next message from the send queue */
    /* -------------------------------------------- */
    pthread_mutex_lock(&(connection->send_mutex));
    while (queue_size(&(connection->send_queue)) == 0 &&
	    connection->alive == 1)
      pthread_cond_wait(&(connection->send_cond), &(connection->send_mutex));

    if (connection->alive == 0)
      break;

    message = queue_extract(&(connection->send_queue));

    pthread_mutex_unlock(&(connection->send_mutex));

    /* packetize the message and send it */
    /* --------------------------------- */
    packet_array = packetize(message->buffer, message->length, &array_length);


    for (i=0; i<array_length; i++)
    {
      if (net_send_packet(connection->net_connection_handle,
          &(packet_array[i]))<0)
      {
        /* remote side has disconnected */
        connection->alive = 0;
        break;
      }
	
      /*  ----FIX ME ---- 
       * 
       *  1. wait for the recv thread to notify you of when a NACK or
       *     an ACK has been received
       *  2. check the data structure for this connection to determine
       *     if an ACK or NACK was received.  (You'll have to add the
       *     necessary fields yourself)
       *  3. If it was an ACK, continue sending the packets.
       *  4. If it was a NACK, resend the last packet
       */

      pthread_mutex_lock(&(connection->ack_mutex));
      while (NULL == connection->last_ack) {
        pthread_cond_wait(&(connection->ack_cond),&(connection->ack_mutex));
      }
      pthread_mutex_unlock(&(connection->ack_mutex));

      if (connection->NACK) {
        i--;
      }
      connection->last_ack = NULL;
    }

    free(packet_array);
    free(message->buffer);
    free(message);
  } while(connection->alive == 1);
  return NULL;
}

RTP_CONNECTION *rtp_init_connection(int net_connection_handle){
  RTP_CONNECTION *rtp_connection = malloc(sizeof(RTP_CONNECTION));
 
  if (rtp_connection == NULL){
    fprintf(stderr,"Out of memory!\n");
    exit (EXIT_FAILURE);
  }

  rtp_connection->net_connection_handle = net_connection_handle;

  queue_init(&(rtp_connection->recv_queue));
  queue_init(&(rtp_connection->send_queue));

  pthread_mutex_init(&(rtp_connection->recv_mutex),NULL);
  pthread_mutex_init(&(rtp_connection->send_mutex),NULL);
  pthread_mutex_init(&(rtp_connection->ack_mutex),NULL);
  pthread_cond_init(&(rtp_connection->recv_cond),NULL);
  pthread_cond_init(&(rtp_connection->send_cond),NULL);
  pthread_cond_init(&(rtp_connection->ack_cond),NULL);

  rtp_connection->alive = 1;

  pthread_create(&(rtp_connection->recv_thread), NULL, rtp_recv_thread,
		 (void*)rtp_connection);
  pthread_create(&(rtp_connection->send_thread), NULL, rtp_send_thread,
		 (void*)rtp_connection);

  return rtp_connection;
}

/* ================================================================ */
/*                           R T P    A P I                         */
/* ================================================================ */

RTP_CONNECTION *rtp_connect(char *host, int port){
  
  int net_connection_handle;
  if ((net_connection_handle = net_connect(host,port)) < 1)
    return NULL;

  return rtp_init_connection(net_connection_handle);

}

int rtp_disconnect(RTP_CONNECTION *connection){

  MESSAGE *message;

  connection->alive = 0;
  
  net_disconnect(connection->net_connection_handle);

  pthread_cond_signal(&(connection->send_cond));
  pthread_cond_signal(&(connection->recv_cond));

  pthread_join(connection->send_thread,NULL);
  pthread_join(connection->recv_thread,NULL);

  /* emtpy recv queue and free allocated memory */
  while ((message = queue_extract(&(connection->recv_queue))) != NULL){
    free(message->buffer);
    free(message);
  }

  /* emtpy send queue and free allocated memory */
  while ((message = queue_extract(&(connection->send_queue))) != NULL){
    free(message);
  }

  free(connection);

  return 1;

}

int rtp_recv_message(RTP_CONNECTION *connection, char **buffer, int *length){

  MESSAGE *message;

  if (connection->alive == 0)
    return -1;

  /* lock */
  pthread_mutex_lock(&(connection->recv_mutex));
  while (queue_size(&(connection->recv_queue)) == 0 &&
	 connection->alive == 1)
    pthread_cond_wait(&(connection->recv_cond), &(connection->recv_mutex));
  
  if (connection->alive == 0){
    pthread_mutex_unlock(&(connection->recv_mutex));
    return -1;
  }

  /* extract */
  message = queue_extract(&(connection->recv_queue));
  *buffer = message->buffer;
  *length = message->length;
  free(message);

  /* unlock */
  pthread_mutex_unlock(&(connection->recv_mutex));

  return *length;
}

int rtp_send_message(RTP_CONNECTION *connection, char *buffer, int length){

  MESSAGE *message;

  if (connection->alive == 0)
    return -1;

  message = malloc(sizeof(MESSAGE));
  if (message == NULL)
    return -1;
  message->buffer = malloc(length);
  message->length = length;

  if (message->buffer == NULL){
    free(message);
    return -1;
  }

  memcpy(message->buffer,buffer,length);

  /* lock */
  pthread_mutex_lock(&(connection->send_mutex));
  
  /* add */
  queue_add(&(connection->send_queue),message);

  /* unlock */
  pthread_cond_signal(&(connection->send_cond));
  pthread_mutex_unlock(&(connection->send_mutex));

  return 1;

}
