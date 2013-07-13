#
#	This is a sample make file for RTP
# 

CFLAGS = -Wall -ansi -pedantic -g -O2 -ggdb
NETWORK_OBJECT = network64.o
LIBS = -lpthread -lnsl 
INCLUDES = -I /usr/include/linux

client: client.c rtp.o $(NETWORK_OBJECT)
	gcc $(CFLAGS) -o prj5-client client.c rtp.o queue.c $(NETWORK_OBJECT) $(LIBS) 
rtp.o : rtp.c rtp.h
	gcc -c $(CFLAGS) rtp.c

clean:
	rm -rf rtp.o prj5-client

