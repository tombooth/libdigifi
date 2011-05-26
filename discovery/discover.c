/*
 *	dfsearchpacket.c
 *	© 2009 DigiFi Limited
 *
 *	Discover me some digifis
 *
 */


#include "discover.h"
#include "searchpacket.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "debugging.h"

#define REQUEST_PORT		2921
#define RESPONSE_PORT		2922
#define DISCOVER_BACKLOG	10


static void dfdiscover_receive(void);
static void dfdiscover_addserver(df_server **servers, char *buffer, int length, struct sockaddr_in *addr);


pthread_t receiving_thread;
unsigned int go_flag = 0;
int wait_counts = 30;
static void *context_holder = NULL;

void (*client_callback)(df_server *, void *);

int df_discover(int wait_period, void (*callback)(df_server *, void *), void *context) {
	struct sockaddr_in *local_addr, *multicast_addr;
	int id, length, err, setting;
	void *packet;
	
	DFDEBUG("Starting discover");
	
	context_holder = context;
	client_callback = callback;
	wait_counts = wait_period;
	
	// setup the receiving thread
	pthread_create(&receiving_thread, NULL, (void* (*)(void*))dfdiscover_receive, NULL);
	
	// setup the sending udp multicast port
	id = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	local_addr = malloc(sizeof(struct sockaddr_in));
	local_addr->sin_family = AF_INET;
	local_addr->sin_port = htons(0);
	local_addr->sin_addr.s_addr=htonl(INADDR_ANY);
	
	bind(id, (struct sockaddr*)local_addr, sizeof(struct sockaddr_in));
	
	free(local_addr);
	
	// allow multicasting
	setting = 1;
	setsockopt(id, SOL_SOCKET, SO_BROADCAST, &setting, sizeof(int));
	
	// build the search packet
	packet = dfsearchpacket_create(RESPONSE_PORT, &length);
	
	// send the search packet
	multicast_addr = malloc(sizeof(struct sockaddr_in));
	multicast_addr->sin_family = AF_INET;
	multicast_addr->sin_port = htons(REQUEST_PORT);
	multicast_addr->sin_addr.s_addr=htonl(INADDR_BROADCAST);
	
	err = sendto(id, packet, length, 0, (struct sockaddr*)multicast_addr, sizeof(struct sockaddr_in));
	
	free(multicast_addr);
	
	// tell receiving thread to start receiving
	go_flag = 1;
	
	// close down the sending port
	close(id);
	
	/*int err =0;
	df_server *srv;
	srv = malloc(sizeof(df_server));
	
	srv->address = "192.168.56.101";
	srv->name = "df03ba88";
	srv->version = "1.0.0";
	srv->next = NULL;
	
	callback(srv);*/
	
	return err;
}


static void dfdiscover_receive(void) {
	struct sockaddr_in *local_addr, *remote_socket;
	int id, flags, i;
	char buffer[100];
	int buffered;
	unsigned int size;
	df_server *servers;
	
	servers = NULL;
		
	// setup bound port
	id = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	local_addr = malloc(sizeof(struct sockaddr_in));
	local_addr->sin_family = AF_INET;
	local_addr->sin_port = htons(RESPONSE_PORT);
	local_addr->sin_addr.s_addr=htonl(INADDR_ANY);
	
	bind(id, (struct sockaddr*)local_addr, sizeof(struct sockaddr_in));
	
	free(local_addr);
	
	listen(id, DISCOVER_BACKLOG);
	
	// set socket as non-blocking
	flags = fcntl(id, F_GETFL, 0);
	fcntl(id, F_SETFL, flags | O_NONBLOCK);
	
	// wait on go flag
	while (go_flag == 0) { sleep(1); }
	
	remote_socket = malloc(sizeof(struct sockaddr_in));
	size = sizeof(struct sockaddr_in);
	
	// receive for wait_counts time
	i=0;
	while(i<wait_counts) {
		memset(buffer, '\0', 100);
		
		if ((buffered = recvfrom(id, buffer, 100, 0, (struct sockaddr*)remote_socket, &size)) > 0) {

			dfdiscover_addserver(&servers, buffer, buffered, remote_socket);

			// call out to stashed callback
			client_callback(servers, context_holder);

			continue;
		}
		
		// wait for a second
		sleep(1);
		i++;
	}
	
	// shutdown gracefully
	close(id);
	
	DFDEBUG("Finished discovering servers");
	client_callback(NULL, context_holder);  // Inform client that search has finished
}


static void dfdiscover_addserver(df_server **servers, char *buffer, int length, struct sockaddr_in *addr) {
	df_searchpacket *packet;
	df_server *current;
	
	packet = dfsearchpacket_read(buffer, length);
	
	if (*servers == NULL) {
		*servers = malloc(sizeof(df_server));
		current = *servers;
	}
	else {
		current = *servers;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = malloc(sizeof(df_server));
		current = current->next;
	}
	
	
	current->name = strdup(packet->fields->next->next->next->value);
	current->version = strdup(packet->fields->next->next->value);
	current->address = malloc(16*sizeof(char));
	inet_ntop(AF_INET, &(addr->sin_addr.s_addr), current->address, 16);
	
	current->next = NULL;
	
	// clear the packet data
}





