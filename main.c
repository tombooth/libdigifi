#include <stdio.h>
#include <unistd.h>


#include "DigiFi.h"

void tp_callback(df_time* t, void* c) {
	printf("TrackPosition: %u:%u:%u\n", t->hours, t->minutes, t->seconds);
}

void gr_callback(int num, df_roomrow *rows, void *context) {
	df_roomrow *current;
	
	printf("Printing GetRooms return:\n");
	printf("Total rows: %d\n", num);
	current = rows;
	
	while (current != NULL) {
		printf("RoomKey: %d\n", current->RoomKey);
		printf("IPAddress: \"%s\"\n", current->IPAddress);
		printf("Channel: %d\n", current->Channel);
		printf("Name: \"%s\"\n", current->Name);
		printf("ShortName: \"%s\"\n", current->ShortName);
		printf("IsMultiRoom: %d\n", current->IsMultiRoom);
		printf("PlaybackCapability: %d\n", current->PlaybackCapability);
		printf("RippingCapability: %d\n", current->RippingCapability);
		printf("MusicManagementCapability: %d\n", current->MusicManagementCapability);
		printf("RoomID: %d\n", current->RoomID);
		printf("HostName: \"%s\"\n", current->HostName);
		
		current = current->next;
	}
	
	fflush(stdout);
}

int main (int argc, const char * argv[]) {
	df_connection *conn1, *conn2;
	
	df_init();
	
	sleep(3);
	
	conn1 = df_connect("192.168.0.242", 1);
	sleep(1);
	conn2 = df_connect("192.168.0.39", 1);
	
	sleep(3);
	
	dfrget_trackposition(conn1, 3, tp_callback, NULL);
	dfrget_trackposition(conn2, 1, tp_callback, NULL);
	
	sleep(3);
	
	df_GetRooms(conn1, 0, gr_callback, NULL);
	
	sleep(120);
	
	
    return 0;
}
