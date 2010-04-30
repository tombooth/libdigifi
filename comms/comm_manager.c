/*
 *  comm_manager.c
 *  libdigifi.new
 *
 *  Created by Tom Booth on 09/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "comm_manager.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <unistd.h>

#include "debugging.h"

static void start_threads();
static int connect_to_socket(char *ipadress, int port);
static int listen_on_socket(int port);
static int set_non_blocking(int fd);
static int randomise_port();
static char* get_local_ip();
static int pick_quietest_socket(connection *conn);



static pthread_t *out_threads;
static unsigned int out_threads_num;
static pthread_t in_thread;


void comm_start(int outgoing_threads, void (*rget_callback)(in_settings*, char*, char*)) {	
	comm_in_init(rget_callback);
	
	out_threads = (pthread_t *) malloc(outgoing_threads * sizeof(pthread_t));
	out_threads_num = outgoing_threads;
	in_thread = NULL;
}


static void start_threads() {
	int i;
	
	for (i=0; i < out_threads_num; i++) {
		pthread_create(&(out_threads[i]), NULL, comm_out_thread_start, NULL);
	}
	
	pthread_create(&in_thread, NULL, comm_in_thread_start, NULL);
}


connection *comm_connect(char *ipaddress, int connections) {
	int i, port;
	connection *conn;
	
	if (in_thread == NULL) start_threads();
	if (connections < 1) return NULL;
	if (ipaddress == NULL) return NULL;
	
	conn = (connection *) malloc(sizeof(connection));
	
	conn->label = strdup(ipaddress);
	conn->connected = 0;
	conn->sockets = (out_socket *) malloc(connections * sizeof(out_socket));
	conn->num_sockets = connections;
	
	// setup the outgoing connections
	for (i = 0; i < connections; i++) {
		conn->sockets[i].fd = connect_to_socket(ipaddress, SOPHIA_PORT);
		set_non_blocking(conn->sockets[i].fd);
		pthread_mutex_init(&(conn->sockets[i].fd_lock), 0);
		conn->sockets[i].backlog = 0;
		conn->sockets[i].done = 0;
	}
	
	conn->connected = 1;
	
	// setup the rget connection
	conn->rget_settings.buffer = cbuf_new();
	conn->rget_settings.client_fd = -1;
	
	conn->rget_settings.server_fd = -1;
	while( conn->rget_settings.server_fd < 0 ) {
		port = randomise_port();
		conn->rget_settings.server_fd = listen_on_socket(port);
	}
	
	comm_send(conn, 1, "void", 1, NULL, NULL, "[RGetRegisterClient \"%d\" \"%s\"]", port, get_local_ip());
	
	// wait to accept the rget connection
	while (conn->rget_settings.client_fd < 0) { conn->rget_settings.client_fd = accept(conn->rget_settings.server_fd, NULL, 0); }
	
	// add this connect to the inbound subsystem
	comm_in_add(&(conn->rget_settings));
	
	return conn;
}



int comm_send(connection *conn, int rget, char *tag, int count, void (*callback)(out_request*, out_response*, int, void*), void *context, char *message, ...) {
	char *buffer;
	va_list arg_ptr;
	out_request *req;
	int fd_id;
	
	if (!conn->connected) return -1;
	
	va_start(arg_ptr, message);
	vasprintf(&buffer, message, arg_ptr);
	va_end(arg_ptr);
	
	req = (out_request *) malloc(sizeof(out_request));
	req->tag = strdup(tag);
	req->response_count = count;
	req->response_regex = regex_get_compiled(tag);
	req->send = buffer;
	req->callback = callback;
	req->context = context;
	
	if (rget) fd_id = 0;
	else fd_id = pick_quietest_socket(conn);  
	
	req->socket = &(conn->sockets[fd_id]);
	
	comm_out_push_request(req);
	
	return 0;
}

int comm_send_via_socket(out_socket *socket, char *tag, int count, void (*callback)(out_request*, out_response*, int, void*), void *context, char *message, ...) {
	char *buffer;
	va_list arg_ptr;
	out_request *req;
	
	va_start(arg_ptr, message);
	vasprintf(&buffer, message, arg_ptr);
	va_end(arg_ptr);
	
	req = (out_request *) malloc(sizeof(out_request));
	req->tag = strdup(tag);
	req->response_count = count;
	req->response_regex = regex_get_compiled(tag);
	req->send = buffer;
	req->callback = callback;
	req->context = context;	
	req->socket = socket;
	
	comm_out_push_request(req);
	
	return 0;
}



void comm_disconnect(connection *conn) {
	int i;
	
	conn->connected = 0;
	
	comm_out_clear_requests_for(conn->sockets, conn->num_sockets);
	comm_in_remove(&(conn->rget_settings));
	
	shutdown(conn->rget_settings.client_fd, SHUT_RDWR);
	close(conn->rget_settings.client_fd);
	shutdown(conn->rget_settings.server_fd, SHUT_RDWR);
	close(conn->rget_settings.server_fd);
	
	for (i = 0; i < conn->num_sockets; i++) {
		shutdown(conn->sockets[i].fd, SHUT_RDWR);
		close(conn->sockets[i].fd);
	}
	
	free(conn->sockets);
	cbuf_free(conn->rget_settings.buffer);
	free(conn->label);
	
	free(conn);
}



void comm_stop() {
	// TODO:
	// Shutdown the threads
}




static int connect_to_socket(char *ipaddress, int port) {
	struct sockaddr_in *destination;
	int err;
	int fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	// check if we failed to get a descriptor
	if (fd == -1)
		return -1;
	
	if ((destination = malloc(sizeof(struct sockaddr_in))) == NULL) {close(fd); return -1;}
	destination->sin_family = AF_INET;
	destination->sin_port = htons(port);
	
	err = inet_pton(AF_INET, ipaddress, &destination->sin_addr);
	
	// check if the address converstion fucked up
	if (err <= 0) {
		close(fd);
		free(destination);
		return -1;
	}
	
	err = connect(fd, (const void*)destination, sizeof(struct sockaddr_in));
	
	if (err == -1) {
		close(fd);
		free(destination);
		return -1;
	}
	
	free(destination);
	
	return fd;	
}


static int listen_on_socket(int port) {
	struct sockaddr_in *destination;
	int err;
	int fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	// check if we failed to get a descriptor
	if (fd == -1)
		return -1;
	
	if ((destination = malloc(sizeof(struct sockaddr_in))) == NULL) {close(fd); return -1;}
	destination->sin_family = AF_INET;
	destination->sin_port = htons(port);
	destination->sin_addr.s_addr=htonl(INADDR_ANY);
	
	err = bind(fd, (const void*)destination, sizeof(struct sockaddr_in));
	
	if (err == -1) {
		close(fd);
		free(destination);
		return err;
	}
	
	free(destination);
	
	err = listen(fd, 1);
	
	if (err == -1) {
		close(fd);
		return err;
	}
	
	return fd;
}

static int set_non_blocking(int fd) {
	int flags;
	
	if ((flags = fcntl(fd, F_GETFL, 0)) < 0) { return -1; } 
	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0) { return -2; } 
	
	return 0;
}



static int randomise_port() {
	int r;
	struct timeval tv;
 	gettimeofday(&tv, NULL);
	
	srand48((long)tv.tv_usec);
	r = (int)(((double)lrand48()/(double)RAND_MAX) * 1000);
	
	return RGET_PORT_BASE + r;
}

static char* get_local_ip() {
	struct ifaddrs *ifap, *ifa;
	char *ret = NULL;
	
    if (getifaddrs(&ifap) != 0) {
		return NULL;
    }
	
    // cycle through available interfaces
    for (ifa = ifap; ifa != NULL; ifa = ifa->ifa_next) {
        // Skip loopback, point-to-point and down interfaces
        if( ( ifa->ifa_flags & IFF_LOOPBACK ) || ( !( ifa->ifa_flags & IFF_UP ) ) ) {
            continue;
        }
        if( ifa->ifa_addr->sa_family == AF_INET ) {
            // We don't want the loopback interface. 
            if( ((struct sockaddr_in *)(ifa->ifa_addr))->sin_addr.s_addr == htonl( INADDR_LOOPBACK ) ) {
                continue;
            }
			
			ret = inet_ntoa(((struct sockaddr_in *) ifa->ifa_addr)->sin_addr);
            break;
        }
    }
    freeifaddrs(ifap);
	
    return ret;
}

static int pick_quietest_socket(connection *conn) {
	int i = 0, min = 999, id = 0;
	
	for (i=0; i < conn->num_sockets; i++) {
		if (conn->sockets[i].backlog < min) { min = conn->sockets[i].backlog; id = i; }
	}
	
	return id;
}

