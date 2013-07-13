#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "network64.h"
#include "rtp.h"

void printUsage(){
  fprintf(stderr,"Usage:  prj5-client host port\n\n");
  fprintf(stderr,"   example ./prj5-client lennon.cc.gatech.edu 4000\n\n");
  exit (EXIT_FAILURE);
}

int main(int argc, char** argv){

  char *message_1 = "The use of COBOL cripples the mind; its "
    "teaching should, therefore, be regarded as a criminal " 
    "offense. -- Edsgar Dijkstra";

  char *message_2 = "C makes it easy to shoot yourself in the "
    "foot; C++ makes it harder, but when you do, it blows away "
    "your whole leg. -- Bjarne Stroustrup";

  char *message_3 = "A mathematician is a device for turning "
    "coffee into theorems. -- Paul Erdos";

  char *message_4 = "Grove giveth and Gates taketh away. "
    "-- Bob Metcalfe (inventor of Ethernet) on the trend of "
    "hardware speedups not being able to keep up with software demands";

  char *message_5 = "Wise men make proverbs, but fools repeat them. "
    "-- Samuel Palmer (1805-80)";


  char *rcv_buffer;
  int length;
  RTP_CONNECTION *connection;

  if (argc < 3){
    printUsage();
    return EXIT_FAILURE;
  }
  
  if ((connection = rtp_connect(argv[1],atoi(argv[2]))) == NULL){
    printUsage();
    return EXIT_FAILURE;
  }
      
  printf("Sending quotes to a remote host to have them "
	 "converted to pig latin!\n\n");
      
  rtp_send_message(connection,message_1,strlen(message_1)+1);
  rtp_recv_message(connection,&rcv_buffer,&length);
  if (rcv_buffer == NULL){
    printf("Connection reset by peer.\n");
    return EXIT_FAILURE;
  }
  printf("%s\n\n",rcv_buffer);
  free(rcv_buffer);  

  rtp_send_message(connection,message_2,strlen(message_2)+1);
  rtp_recv_message(connection,&rcv_buffer,&length);
  if (rcv_buffer == NULL){
    printf("Connection reset by peer.\n");
    return EXIT_FAILURE;
  }
  printf("%s\n\n",rcv_buffer);
  free(rcv_buffer);  

  rtp_send_message(connection,message_3,strlen(message_3)+1);
  rtp_recv_message(connection,&rcv_buffer,&length);
  if (rcv_buffer == NULL){
    printf("Connection reset by peer.\n");
    return EXIT_FAILURE;
  }
  printf("%s\n\n",rcv_buffer);
  free(rcv_buffer);  

  rtp_send_message(connection,message_4,strlen(message_4)+1);
  rtp_recv_message(connection,&rcv_buffer,&length);
  if (rcv_buffer == NULL){
    printf("Connection reset by peer.\n");
    return EXIT_FAILURE;
  }
  printf("%s\n\n",rcv_buffer);
  free(rcv_buffer);  

  rtp_send_message(connection,message_5,strlen(message_5)+1);
  rtp_recv_message(connection,&rcv_buffer,&length);
  if (rcv_buffer == NULL){
    printf("Connection reset by peer.\n");
    return EXIT_FAILURE;
  }
  printf("%s\n\n",rcv_buffer);
  free(rcv_buffer);  

  rtp_disconnect(connection);
  return EXIT_SUCCESS;
}
