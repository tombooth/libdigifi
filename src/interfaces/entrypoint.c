/*
 *  m_entrypoint.c
 *  libdigifi
 *
 *  Created by Tom Booth on 29/03/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "DigiFi.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tests.h"


static df_connection** connections;
static int num_connections;

static int check_connection(int id) { if (id >= num_connections || id < 0) { return 0; } else { return 1; } }

static void get_search_rows(df_search *s) { df_extract_from(s, 1, -1); df_free_search(s); }


void print_ActivateExternalStorage(int input, void *context) {
	printf("Printing ActivateExternalStorage return:\n");
	printf("ActivateExternalStorage_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_AddAlbumsToUserPlaylist(int input, void *context) {
	printf("Printing AddAlbumsToUserPlaylist return:\n");
	printf("AddAlbumsToUserPlaylist_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_AddExternalStorage(df_extstorageresult* input, void *context) {
	printf("Printing AddExternalStorage return:\n");
	printf("AddExternalStorage_Success: %d\n", input->AddExternalStorage_Success);
	printf("AddExternalStorage_Message: \"%s\"\n", input->AddExternalStorage_Message);
	printf("AddExternalStorage_Key: %d\n", input->AddExternalStorage_Key);
	printf("AddExternalStorage_Hostname: \"%s\"\n", input->AddExternalStorage_Hostname);
	printf("AddExternalStorage_IPAddress: \"%s\"\n", input->AddExternalStorage_IPAddress);
	printf("AddExternalStorage_ShareName: \"%s\"\n", input->AddExternalStorage_ShareName);
	printf("AddExternalStorage_Username: \"%s\"\n", input->AddExternalStorage_Username);
	printf("AddExternalStorage_Password: \"%s\"\n", input->AddExternalStorage_Password);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_AddNewBackupJob(int input, void *context) {
	printf("Printing AddNewBackupJob return:\n");
	printf("AddNewBackupJob_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_AddNewDrive(df_newdriveresult* input, void *context) {
	printf("Printing AddNewDrive return:\n");
	printf("AddNewDrive_Return: %d\n", input->AddNewDrive_Return);
	printf("AddNewDrive_ErrorMessage: \"%s\"\n", input->AddNewDrive_ErrorMessage);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_AddNewGenre(int input, void *context) {
	printf("Printing AddNewGenre return:\n");
	printf("AddNewGenre_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_AddNewLinkedRoom(int input, void *context) {
	printf("Printing AddNewLinkedRoom return:\n");
	printf("AddNewLinkedRoom_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_AddNewRoom(int input, void *context) {
	printf("Printing AddNewRoom return:\n");
	printf("AddNewRoom_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_AddNewSubGenre(int input, void *context) {
	printf("Printing AddNewSubGenre return:\n");
	printf("AddNewSubGenre_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_AddTracksToUserPlaylist(int input, void *context) {
	printf("Printing AddTracksToUserPlaylist return:\n");
	printf("AddTracksToUserPlaylist_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_AdvancedSearch(int rows, df_type3row *input, void *context) {
	df_type3row *current;

	printf("Printing AdvancedSearch return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);
		printf("AlbumKey: %d\n", current->AlbumKey);
		printf("AlbumName: \"%s\"\n", current->AlbumName);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("SubGenre: \"%s\"\n", current->SubGenre);
		printf("CoverURL: \"%s\"\n", current->CoverURL);
		printf("BitRate: %d\n", current->BitRate);
		printf("CoverAvailable: %d\n", current->CoverAvailable);

		current = current->next;
	}

	df_type3row_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_BackupDrive(df_backupresult* input, void *context) {
	printf("Printing BackupDrive return:\n");
	printf("BackupDrive_Success: %d\n", input->BackupDrive_Success);
	printf("BackupDrive_Message: \"%s\"\n", input->BackupDrive_Message);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_BulkCDLookup(int rows, df_bulklookuprow *input, void *context) {
	df_bulklookuprow *current;

	printf("Printing BulkCDLookup return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Success: %d\n", current->Success);
		printf("Message: \"%s\"\n", current->Message);

		current = current->next;
	}

	df_bulklookuprow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_BulkCDLookupEx(int input, void *context) {
	printf("Printing BulkCDLookupEx return:\n");
	printf("BulkCDLookupEx_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CDLookupGetQueue(int rows, df_type4row *input, void *context) {
	df_type4row *current;

	printf("Printing CDLookupGetQueue return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("QueueKey: %d\n", current->QueueKey);
		printf("Status: \"%s\"\n", current->Status);
		printf("Retries: %d\n", current->Retries);
		printf("LastError: \"%s\"\n", current->LastError);
		printf("AlbumKey: %d\n", current->AlbumKey);

		current = current->next;
	}

	df_type4row_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CDLookupGetStatus(df_type0* input, void *context) {
	printf("Printing CDLookupGetStatus return:\n");
	printf("Running: %d\n", input->Running);
	printf("AlbumKey: %d\n", input->AlbumKey);
	printf("AlbumName: \"%s\"\n", input->AlbumName);
	printf("Progress: %d\n", input->Progress);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CancelRipping(int input, void *context) {
	printf("Printing CancelRipping return:\n");
	printf("CancelRipping_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ChangeAlbumSubGenre(char* input, void *context) {
	printf("Printing ChangeAlbumSubGenre return:\n");
	printf("ChangeAlbumSubGenre_Return: \"%s\"\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ChangeNetworkAutoIP(int input, void *context) {
	printf("Printing ChangeNetworkAutoIP return:\n");
	printf("WmiReturnCode: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ChangeNetworkDhcp(int input, void *context) {
	printf("Printing ChangeNetworkDhcp return:\n");
	printf("WmiReturnCode: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ChangeNetworkMachineName(int input, void *context) {
	printf("Printing ChangeNetworkMachineName return:\n");
	printf("WmiReturnCode: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ChangeNetworkStatic(int input, void *context) {
	printf("Printing ChangeNetworkStatic return:\n");
	printf("WmiReturnCode: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ChangeNetworkWorkgroup(int input, void *context) {
	printf("Printing ChangeNetworkWorkgroup return:\n");
	printf("WmiReturnCode: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ChangeSystemSerialNumber(int input, void *context) {
	printf("Printing ChangeSystemSerialNumber return:\n");
	printf("Success: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ChangeTrackOrdinal(int input, void *context) {
	printf("Printing ChangeTrackOrdinal return:\n");
	printf("ChangeTrackOrdinal_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CheckCoverImage(df_coverimage* input, void *context) {
	printf("Printing CheckCoverImage return:\n");
	printf("CoverImageName: \"%s\"\n", input->CoverImageName);
	printf("CoverImageURI: \"%s\"\n", input->CoverImageURI);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CompactGenreOrdinals(int input, void *context) {
	printf("Printing CompactGenreOrdinals return:\n");
	printf("CompactGenreOrdinals_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ComplexSearchCountAlbums(int input, void *context) {
	printf("Printing ComplexSearchCountAlbums return:\n");
	printf("CountComplexSearchForAlbums_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ComplexSearchCountArtists(int input, void *context) {
	printf("Printing ComplexSearchCountArtists return:\n");
	printf("CountComplexSearchForArtists_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ComplexSearchCountContributors(int input, void *context) {
	printf("Printing ComplexSearchCountContributors return:\n");
	printf("CountComplexSearchForContributors_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ComplexSearchCountTracks(int input, void *context) {
	printf("Printing ComplexSearchCountTracks return:\n");
	printf("CountComplexSearchForTracks_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ComplexSearchGetAlbums(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing ComplexSearchGetAlbums return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ComplexSearchGetArtists(int rows, df_artistrow *input, void *context) {
	df_artistrow *current;

	printf("Printing ComplexSearchGetArtists return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("Name: \"%s\"\n", current->Name);

		current = current->next;
	}

	df_artistrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ComplexSearchGetContributors(int rows, df_extcontributorrow *input, void *context) {
	df_extcontributorrow *current;

	printf("Printing ComplexSearchGetContributors return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("ContributorKey: %d\n", current->ContributorKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ContributorType: %d\n", current->ContributorType);

		current = current->next;
	}

	df_extcontributorrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ComplexSearchGetTracks(int rows, df_trackrow *input, void *context) {
	df_trackrow *current;

	printf("Printing ComplexSearchGetTracks return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);

		current = current->next;
	}

	df_trackrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountAlbums(int input, void *context) {
	printf("Printing CountAlbums return:\n");
	printf("CountAlbums_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountAlbumsForArtist(int input, void *context) {
	printf("Printing CountAlbumsForArtist return:\n");
	printf("CountAlbumsForArtist_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountAlbumsForArtistForDevice(int input, void *context) {
	printf("Printing CountAlbumsForArtistForDevice return:\n");
	printf("CountAlbumsForArtistForDevice_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountAlbumsForArtistForServer(int input, void *context) {
	printf("Printing CountAlbumsForArtistForServer return:\n");
	printf("CountAlbumsForArtistForServer_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountAlbumsForArtistForShare(int input, void *context) {
	printf("Printing CountAlbumsForArtistForShare return:\n");
	printf("CountAlbumsForArtistForShare_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountAlbumsForDevice(int input, void *context) {
	printf("Printing CountAlbumsForDevice return:\n");
	printf("CountAlbumsForDevice_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountAlbumsForServer(int input, void *context) {
	printf("Printing CountAlbumsForServer return:\n");
	printf("CountAlbumsForServer_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountAlbumsForShare(int input, void *context) {
	printf("Printing CountAlbumsForShare return:\n");
	printf("CountAlbumsForShare_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountArtists(int input, void *context) {
	printf("Printing CountArtists return:\n");
	printf("CountArtists_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountArtistsForDevice(int input, void *context) {
	printf("Printing CountArtistsForDevice return:\n");
	printf("CountArtistsForDevice_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountArtistsForServer(int input, void *context) {
	printf("Printing CountArtistsForServer return:\n");
	printf("CountArtistsForServer_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountArtistsForShare(int input, void *context) {
	printf("Printing CountArtistsForShare return:\n");
	printf("CountArtistsForShare_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountDevices(int input, void *context) {
	printf("Printing CountDevices return:\n");
	printf("CountDevices_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountGenres(int input, void *context) {
	printf("Printing CountGenres return:\n");
	printf("CountGenres_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountPlaylistsForSubGenre(int input, void *context) {
	printf("Printing CountPlaylistsForSubGenre return:\n");
	printf("CountPlaylistsForSubGenre_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountPlaylistsForSubGenreForDevice(int input, void *context) {
	printf("Printing CountPlaylistsForSubGenreForDevice return:\n");
	printf("CountPlaylistsForSubGenreForDevice_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountPlaylistsForSubGenreForServer(int input, void *context) {
	printf("Printing CountPlaylistsForSubGenreForServer return:\n");
	printf("CountPlaylistsForSubGenreForServer_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountPlaylistsForSubGenreForShare(int input, void *context) {
	printf("Printing CountPlaylistsForSubGenreForShare return:\n");
	printf("CountPlaylistsForSubGenreForShare_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountShares(int input, void *context) {
	printf("Printing CountShares return:\n");
	printf("CountShares_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountSubGenresForDevice(int input, void *context) {
	printf("Printing CountSubGenresForDevice return:\n");
	printf("CountSubGenresForDevice_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountSubGenresForGenre(int input, void *context) {
	printf("Printing CountSubGenresForGenre return:\n");
	printf("CountSubGenresForGenre_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountSubGenresForServer(int input, void *context) {
	printf("Printing CountSubGenresForServer return:\n");
	printf("CountSubGenresForServer_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountSubGenresForShare(int input, void *context) {
	printf("Printing CountSubGenresForShare return:\n");
	printf("CountSubGenresForShare_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountTracksAll(int input, void *context) {
	printf("Printing CountTracksAll return:\n");
	printf("CountTracksAll_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountTracksForDevice(int input, void *context) {
	printf("Printing CountTracksForDevice return:\n");
	printf("CountTracksForDevice_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountTracksForPlaylist(int input, void *context) {
	printf("Printing CountTracksForPlaylist return:\n");
	printf("CountTracksForPlaylist_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountTracksForServer(int input, void *context) {
	printf("Printing CountTracksForServer return:\n");
	printf("CountTracksForServer_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountTracksForShare(int input, void *context) {
	printf("Printing CountTracksForShare return:\n");
	printf("CountTracksForShare_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountUserPlaylists(int input, void *context) {
	printf("Printing CountUserPlaylists return:\n");
	printf("CountUserPlaylists_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountUserPlaylistsForDevice(int input, void *context) {
	printf("Printing CountUserPlaylistsForDevice return:\n");
	printf("CountUserPlaylistsForDevice_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountUserPlaylistsForServer(int input, void *context) {
	printf("Printing CountUserPlaylistsForServer return:\n");
	printf("CountUserPlaylistsForServer_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CountUserPlaylistsForShare(int input, void *context) {
	printf("Printing CountUserPlaylistsForShare return:\n");
	printf("CountUserPlaylistsForShare_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CreatePlaylist(int input, void *context) {
	printf("Printing CreatePlaylist return:\n");
	printf("NewKey: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CreateRandomPlaylist(int input, void *context) {
	printf("Printing CreateRandomPlaylist return:\n");
	printf("TracksAdded: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_CreateRandomPlaylistEx(int input, void *context) {
	printf("Printing CreateRandomPlaylistEx return:\n");
	printf("TracksAdded: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_DeleteAlbum(int input, void *context) {
	printf("Printing DeleteAlbum return:\n");
	printf("DeleteAlbum_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_DeleteBackupJob(int input, void *context) {
	printf("Printing DeleteBackupJob return:\n");
	printf("DeleteBackupJob_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_DeleteDevice(int input, void *context) {
	printf("Printing DeleteDevice return:\n");
	printf("DeleteDevice_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_DeleteDrive(int input, void *context) {
	printf("Printing DeleteDrive return:\n");
	printf("DeleteDrive_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_DeleteGenre(int input, void *context) {
	printf("Printing DeleteGenre return:\n");
	printf("DeleteGenre_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_DeleteLinkedRoom(int input, void *context) {
	printf("Printing DeleteLinkedRoom return:\n");
	printf("DeleteLinkedRoom_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_DeleteOutputChannel(int input, void *context) {
	printf("Printing DeleteOutputChannel return:\n");
	printf("DeleteOutputChannel_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_DeleteRoom(int input, void *context) {
	printf("Printing DeleteRoom return:\n");
	printf("DeleteRoom_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_DeleteSubGenre(int input, void *context) {
	printf("Printing DeleteSubGenre return:\n");
	printf("DeleteSubGenre_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_DeleteTrack(int input, void *context) {
	printf("Printing DeleteTrack return:\n");
	printf("DeleteTrack_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_DemoteMusicStoreToShare(df_demoteresult* input, void *context) {
	printf("Printing DemoteMusicStoreToShare return:\n");
	printf("DemoteMusicStoreToShare_Success: %d\n", input->DemoteMusicStoreToShare_Success);
	printf("DemoteMusicStoreToShare_Message: \"%s\"\n", input->DemoteMusicStoreToShare_Message);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_DeviceChecksum(char* input, void *context) {
	printf("Printing DeviceChecksum return:\n");
	printf("DeviceChecksum_Return: \"%s\"\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_DisconnectDevice(int input, void *context) {
	printf("Printing DisconnectDevice return:\n");
	printf("DisconnectDevice_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ExternalStorageCancelScan(int input, void *context) {
	printf("Printing ExternalStorageCancelScan return:\n");
	printf("ExternalStorageCancelScan_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_FindAllRooms(int input, void *context) {
	printf("Printing FindAllRooms return:\n");
	printf("FindAllRooms_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_FindNewRooms(int input, void *context) {
	printf("Printing FindNewRooms return:\n");
	printf("FindNewRooms_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ForceGenrePlaylistBackup(int input, void *context) {
	printf("Printing ForceGenrePlaylistBackup return:\n");
	printf("ForceGenrePlaylistBackup_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ForceGenrePlaylistRestore(int input, void *context) {
	printf("Printing ForceGenrePlaylistRestore return:\n");
	printf("ForceGenrePlaylistRestore_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAdvancedStatus(int rows, df_keyvaluerow *input, void *context) {
	df_keyvaluerow *current;

	printf("Printing GetAdvancedStatus return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("Name: \"%s\"\n", current->Name);
		printf("Value: \"%s\"\n", current->Value);

		current = current->next;
	}

	df_keyvaluerow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbumArtist(df_albumartist* input, void *context) {
	printf("Printing GetAlbumArtist return:\n");
	printf("Album: \"%s\"\n", input->Album);
	printf("Artist: \"%s\"\n", input->Artist);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbumDetails(int rows, df_albumdetailrow *input, void *context) {
	df_albumdetailrow *current;

	printf("Printing GetAlbumDetails return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("Genre: \"%s\"\n", current->Genre);
		printf("TrackCount: %d\n", current->TrackCount);
		printf("CoverImage: \"%s\"\n", current->CoverImage);

		current = current->next;
	}

	df_albumdetailrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbums(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetAlbums return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbumsForArtists(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetAlbumsForArtists return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbumsForArtistsForDevice(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetAlbumsForArtistsForDevice return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbumsForArtistsForServer(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetAlbumsForArtistsForServer return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbumsForArtistsForShare(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetAlbumsForArtistsForShare return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbumsForArtistsInGenre(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetAlbumsForArtistsInGenre return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbumsForArtistsInSubGenre(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetAlbumsForArtistsInSubGenre return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbumsForDeletion(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetAlbumsForDeletion return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbumsForDevice(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetAlbumsForDevice return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbumsForPlaylist(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetAlbumsForPlaylist return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbumsForServer(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetAlbumsForServer return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbumsForShare(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetAlbumsForShare return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbumsForStore(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetAlbumsForStore return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbumsOtherInfo(int rows, df_type2row *input, void *context) {
	df_type2row *current;

	printf("Printing GetAlbumsOtherInfo return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("GenreKey: %d\n", current->GenreKey);
		printf("Genre: \"%s\"\n", current->Genre);
		printf("SubGenreKey: %d\n", current->SubGenreKey);
		printf("SubGenre: \"%s\"\n", current->SubGenre);
		printf("TrackCount: %d\n", current->TrackCount);
		printf("LowQuality: %d\n", current->LowQuality);
		printf("StorageKey: %d\n", current->StorageKey);
		printf("StorageName: \"%s\"\n", current->StorageName);
		printf("ProviderUsed: %d\n", current->ProviderUsed);
		printf("CoverURL: \"%s\"\n", current->CoverURL);
		printf("CoverAvailable: %d\n", current->CoverAvailable);

		current = current->next;
	}

	df_type2row_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbumsOtherInfoAll(int rows, df_type2row *input, void *context) {
	df_type2row *current;

	printf("Printing GetAlbumsOtherInfoAll return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("GenreKey: %d\n", current->GenreKey);
		printf("Genre: \"%s\"\n", current->Genre);
		printf("SubGenreKey: %d\n", current->SubGenreKey);
		printf("SubGenre: \"%s\"\n", current->SubGenre);
		printf("TrackCount: %d\n", current->TrackCount);
		printf("LowQuality: %d\n", current->LowQuality);
		printf("StorageKey: %d\n", current->StorageKey);
		printf("StorageName: \"%s\"\n", current->StorageName);
		printf("ProviderUsed: %d\n", current->ProviderUsed);
		printf("CoverURL: \"%s\"\n", current->CoverURL);
		printf("CoverAvailable: %d\n", current->CoverAvailable);

		current = current->next;
	}

	df_type2row_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbumsOtherInfoForDevice(int rows, df_type2row *input, void *context) {
	df_type2row *current;

	printf("Printing GetAlbumsOtherInfoForDevice return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("GenreKey: %d\n", current->GenreKey);
		printf("Genre: \"%s\"\n", current->Genre);
		printf("SubGenreKey: %d\n", current->SubGenreKey);
		printf("SubGenre: \"%s\"\n", current->SubGenre);
		printf("TrackCount: %d\n", current->TrackCount);
		printf("LowQuality: %d\n", current->LowQuality);
		printf("StorageKey: %d\n", current->StorageKey);
		printf("StorageName: \"%s\"\n", current->StorageName);
		printf("ProviderUsed: %d\n", current->ProviderUsed);
		printf("CoverURL: \"%s\"\n", current->CoverURL);
		printf("CoverAvailable: %d\n", current->CoverAvailable);

		current = current->next;
	}

	df_type2row_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbumsOtherInfoForServer(int rows, df_type2row *input, void *context) {
	df_type2row *current;

	printf("Printing GetAlbumsOtherInfoForServer return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("GenreKey: %d\n", current->GenreKey);
		printf("Genre: \"%s\"\n", current->Genre);
		printf("SubGenreKey: %d\n", current->SubGenreKey);
		printf("SubGenre: \"%s\"\n", current->SubGenre);
		printf("TrackCount: %d\n", current->TrackCount);
		printf("LowQuality: %d\n", current->LowQuality);
		printf("StorageKey: %d\n", current->StorageKey);
		printf("StorageName: \"%s\"\n", current->StorageName);
		printf("ProviderUsed: %d\n", current->ProviderUsed);
		printf("CoverURL: \"%s\"\n", current->CoverURL);
		printf("CoverAvailable: %d\n", current->CoverAvailable);

		current = current->next;
	}

	df_type2row_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbumsOtherInfoForShare(int rows, df_type2row *input, void *context) {
	df_type2row *current;

	printf("Printing GetAlbumsOtherInfoForShare return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("GenreKey: %d\n", current->GenreKey);
		printf("Genre: \"%s\"\n", current->Genre);
		printf("SubGenreKey: %d\n", current->SubGenreKey);
		printf("SubGenre: \"%s\"\n", current->SubGenre);
		printf("TrackCount: %d\n", current->TrackCount);
		printf("LowQuality: %d\n", current->LowQuality);
		printf("StorageKey: %d\n", current->StorageKey);
		printf("StorageName: \"%s\"\n", current->StorageName);
		printf("ProviderUsed: %d\n", current->ProviderUsed);
		printf("CoverURL: \"%s\"\n", current->CoverURL);
		printf("CoverAvailable: %d\n", current->CoverAvailable);

		current = current->next;
	}

	df_type2row_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbumsSearchAlbumArtist(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetAlbumsSearchAlbumArtist return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlbumsWithAlbumLookupMessages(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetAlbumsWithAlbumLookupMessages return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAlertDetails(int rows, df_alertdetailrow *input, void *context) {
	df_alertdetailrow *current;

	printf("Printing GetAlertDetails return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("AlertKey: %d\n", current->AlertKey);
		printf("Severity: \"%s\"\n", current->Severity);
		printf("Category: \"%s\"\n", current->Category);
		printf("Module: \"%s\"\n", current->Module);
		printf("Message: \"%s\"\n", current->Message);
		printf("UserMessage: \"%s\"\n", current->UserMessage);

		current = current->next;
	}

	df_alertdetailrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetArtistDetails(int rows, df_artistrow *input, void *context) {
	df_artistrow *current;

	printf("Printing GetArtistDetails return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("Name: \"%s\"\n", current->Name);

		current = current->next;
	}

	df_artistrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetArtists(int rows, df_artistrow *input, void *context) {
	df_artistrow *current;

	printf("Printing GetArtists return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("Name: \"%s\"\n", current->Name);

		current = current->next;
	}

	df_artistrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetArtistsForDevice(int rows, df_artistrow *input, void *context) {
	df_artistrow *current;

	printf("Printing GetArtistsForDevice return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("Name: \"%s\"\n", current->Name);

		current = current->next;
	}

	df_artistrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetArtistsForServer(int rows, df_artistrow *input, void *context) {
	df_artistrow *current;

	printf("Printing GetArtistsForServer return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("Name: \"%s\"\n", current->Name);

		current = current->next;
	}

	df_artistrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetArtistsForShare(int rows, df_artistrow *input, void *context) {
	df_artistrow *current;

	printf("Printing GetArtistsForShare return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("Name: \"%s\"\n", current->Name);

		current = current->next;
	}

	df_artistrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetArtistsInGenre(int rows, df_artistrow *input, void *context) {
	df_artistrow *current;

	printf("Printing GetArtistsInGenre return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("Name: \"%s\"\n", current->Name);

		current = current->next;
	}

	df_artistrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetArtistsInSubGenre(int rows, df_artistrow *input, void *context) {
	df_artistrow *current;

	printf("Printing GetArtistsInSubGenre return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("Name: \"%s\"\n", current->Name);

		current = current->next;
	}

	df_artistrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetAvailableValues(int rows, df_keyvaluerow *input, void *context) {
	df_keyvaluerow *current;

	printf("Printing GetAvailableValues return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("Name: \"%s\"\n", current->Name);
		printf("Value: \"%s\"\n", current->Value);

		current = current->next;
	}

	df_keyvaluerow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetBackupJobDetail(int rows, df_backupjobrow *input, void *context) {
	df_backupjobrow *current;

	printf("Printing GetBackupJobDetail return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("BackupJobKey: %d\n", current->BackupJobKey);
		printf("SourceDriveKey: %d\n", current->SourceDriveKey);
		printf("DestinationDriveKey: %d\n", current->DestinationDriveKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("BackupType: %d\n", current->BackupType);
		printf("BackupPeriod: %d\n", current->BackupPeriod);
		printf("PeriodValue: %d\n", current->PeriodValue);
		printf("JobStatus: %d\n", current->JobStatus);
		printf("LastResult: %d\n", current->LastResult);

		current = current->next;
	}

	df_backupjobrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetBackupJobs(int rows, df_backupjobrow *input, void *context) {
	df_backupjobrow *current;

	printf("Printing GetBackupJobs return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("BackupJobKey: %d\n", current->BackupJobKey);
		printf("SourceDriveKey: %d\n", current->SourceDriveKey);
		printf("DestinationDriveKey: %d\n", current->DestinationDriveKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("BackupType: %d\n", current->BackupType);
		printf("BackupPeriod: %d\n", current->BackupPeriod);
		printf("PeriodValue: %d\n", current->PeriodValue);
		printf("JobStatus: %d\n", current->JobStatus);
		printf("LastResult: %d\n", current->LastResult);

		current = current->next;
	}

	df_backupjobrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetBackupLogDetail(int rows, df_backuplogdetailrow *input, void *context) {
	df_backuplogdetailrow *current;

	printf("Printing GetBackupLogDetail return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("BackupLogKey: %d\n", current->BackupLogKey);
		printf("BackupJobKey: %d\n", current->BackupJobKey);
		printf("ExecutionType: %d\n", current->ExecutionType);
		printf("Name: \"%s\"\n", current->Name);
		printf("BackupType: %d\n", current->BackupType);
		printf("SourcePath: \"%s\"\n", current->SourcePath);
		printf("DestinationPath: \"%s\"\n", current->DestinationPath);
		printf("Result: %d\n", current->Result);
		printf("TotalFolders: %d\n", current->TotalFolders);
		printf("TotalFiles: %d\n", current->TotalFiles);
		printf("TotalKiloBytes: %d\n", current->TotalKiloBytes);
		printf("TotalErrors: %d\n", current->TotalErrors);
		printf("ErrorDetail: \"%s\"\n", current->ErrorDetail);

		current = current->next;
	}

	df_backuplogdetailrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetBackupLogs(int rows, df_backuplogrow *input, void *context) {
	df_backuplogrow *current;

	printf("Printing GetBackupLogs return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("BackupLogKey: %d\n", current->BackupLogKey);
		printf("BackupJobKey: %d\n", current->BackupJobKey);
		printf("ExecutionType: %d\n", current->ExecutionType);
		printf("Name: \"%s\"\n", current->Name);
		printf("BackupType: %d\n", current->BackupType);
		printf("SourcePath: \"%s\"\n", current->SourcePath);
		printf("DestinationPath: \"%s\"\n", current->DestinationPath);
		printf("Result: %d\n", current->Result);
		printf("TotalFolders: %d\n", current->TotalFolders);
		printf("TotalFiles: %d\n", current->TotalFiles);
		printf("TotalKiloBytes: %d\n", current->TotalKiloBytes);
		printf("TotalErrors: %d\n", current->TotalErrors);

		current = current->next;
	}

	df_backuplogrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetBackupStatus(df_backupstatus* input, void *context) {
	printf("Printing GetBackupStatus return:\n");
	printf("Backup_SourceDrive: \"%s\"\n", input->Backup_SourceDrive);
	printf("Backup_DestDrive: \"%s\"\n", input->Backup_DestDrive);
	printf("Backup_Type: \"%s\"\n", input->Backup_Type);
	printf("Backup_Status: \"%s\"\n", input->Backup_Status);
	printf("Backup_CurrentFile: \"%s\"\n", input->Backup_CurrentFile);
	printf("Backup_LastError: \"%s\"\n", input->Backup_LastError);
	printf("Backup_SourceFileCount: %d\n", input->Backup_SourceFileCount);
	printf("Backup_SourceFolderCount: %d\n", input->Backup_SourceFolderCount);
	printf("Backup_SourceByteCount: %ld\n", input->Backup_SourceByteCount);
	printf("Backup_ProcessedFileCount: %d\n", input->Backup_ProcessedFileCount);
	printf("Backup_ProcessedFolderCount: %d\n", input->Backup_ProcessedFolderCount);
	printf("Backup_ProcessedByteCount: %ld\n", input->Backup_ProcessedByteCount);
	printf("Backup_ErrorCount: %d\n", input->Backup_ErrorCount);
	printf("Backup_ErrorFileCount: %d\n", input->Backup_ErrorFileCount);
	printf("Backup_ErrorByteCount: %ld\n", input->Backup_ErrorByteCount);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetCDDBGenres(int rows, df_cddbgenrerow *input, void *context) {
	df_cddbgenrerow *current;

	printf("Printing GetCDDBGenres return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("CDDBGenreKey: %d\n", current->CDDBGenreKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SubGenreKey: %d\n", current->SubGenreKey);
		printf("SubGenreName: \"%s\"\n", current->SubGenreName);

		current = current->next;
	}

	df_cddbgenrerow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetComponentVersions(int rows, df_keyvaluerow *input, void *context) {
	df_keyvaluerow *current;

	printf("Printing GetComponentVersions return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("Name: \"%s\"\n", current->Name);
		printf("Value: \"%s\"\n", current->Value);

		current = current->next;
	}

	df_keyvaluerow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetCount(int input, void *context) {
	printf("Printing GetCount return:\n");
	printf("GetCount_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetCurOp(char* input, void *context) {
	printf("Printing GetCurOp return:\n");
	printf("GetCurOp_Return: \"%s\"\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetCurrentPlayList(int rows, df_currentplaylistrow *input, void *context) {
	df_currentplaylistrow *current;

	printf("Printing GetCurrentPlayList return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);
		printf("Source: %d\n", current->Source);

		current = current->next;
	}

	df_currentplaylistrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetCurrentPlaylistEx(int rows, df_type0row *input, void *context) {
	df_type0row *current;

	printf("Printing GetCurrentPlaylistEx return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);
		printf("AlbumKey: %d\n", current->AlbumKey);
		printf("AlbumName: \"%s\"\n", current->AlbumName);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("SubGenre: \"%s\"\n", current->SubGenre);
		printf("CoverURL: \"%s\"\n", current->CoverURL);
		printf("BitRate: %d\n", current->BitRate);
		printf("Source: %d\n", current->Source);
		printf("CoverAvailable: %d\n", current->CoverAvailable);
		printf("Hidden: %d\n", current->Hidden);

		current = current->next;
	}

	df_type0row_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetDeviceDetails(int rows, df_devicerow *input, void *context) {
	df_devicerow *current;

	printf("Printing GetDeviceDetails return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("DeviceKey: %d\n", current->DeviceKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SerialNumber: \"%s\"\n", current->SerialNumber);
		printf("Type: \"%s\"\n", current->Type);
		printf("State: \"%s\"\n", current->State);
		printf("LastState: \"%s\"\n", current->LastState);
		printf("Connections: %d\n", current->Connections);
		printf("Sync: %d\n", current->Sync);

		current = current->next;
	}

	df_devicerow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetDevices(int rows, df_devicerow *input, void *context) {
	df_devicerow *current;

	printf("Printing GetDevices return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("DeviceKey: %d\n", current->DeviceKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SerialNumber: \"%s\"\n", current->SerialNumber);
		printf("Type: \"%s\"\n", current->Type);
		printf("State: \"%s\"\n", current->State);
		printf("LastState: \"%s\"\n", current->LastState);
		printf("Connections: %d\n", current->Connections);
		printf("Sync: %d\n", current->Sync);

		current = current->next;
	}

	df_devicerow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetDriveDetail(df_drivedetail* input, void *context) {
	printf("Printing GetDriveDetail return:\n");
	printf("DriveKey: %d\n", input->DriveKey);
	printf("DriveLetter: \"%s\"\n", input->DriveLetter);
	printf("Primary: %d\n", input->Primary);
	printf("RootPath: \"%s\"\n", input->RootPath);
	printf("SharePath: \"%s\"\n", input->SharePath);
	printf("Usage: %d\n", input->Usage);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetEncodingQueue(int rows, df_encodingqueuerow *input, void *context) {
	df_encodingqueuerow *current;

	printf("Printing GetEncodingQueue return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("Value: \"%s\"\n", current->Value);

		current = current->next;
	}

	df_encodingqueuerow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetEncodingStatus(int rows, df_encodingstatusrow *input, void *context) {
	df_encodingstatusrow *current;

	printf("Printing GetEncodingStatus return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("Artist: \"%s\"\n", current->Artist);
		printf("Album: \"%s\"\n", current->Album);
		printf("Track: \"%s\"\n", current->Track);
		printf("Activity: \"%s\"\n", current->Activity);
		printf("Max: %d\n", current->Max);
		printf("Progress: %d\n", current->Progress);

		current = current->next;
	}

	df_encodingstatusrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtAlbumCredits(int rows, df_extalbumcreditrow *input, void *context) {
	df_extalbumcreditrow *current;

	printf("Printing GetExtAlbumCredits return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("CreditKey: %d\n", current->CreditKey);
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Description: \"%s\"\n", current->Description);
		printf("ContributorKey: %d\n", current->ContributorKey);
		printf("ContributorName: \"%s\"\n", current->ContributorName);

		current = current->next;
	}

	df_extalbumcreditrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtAlbumsByContributor(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetExtAlbumsByContributor return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtAlbumsByContributorForDevice(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetExtAlbumsByContributorForDevice return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtAlbumsByContributorForServer(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetExtAlbumsByContributorForServer return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtAlbumsByContributorForShare(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetExtAlbumsByContributorForShare return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtAlbumsByCredit(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetExtAlbumsByCredit return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtAlbumsByWork(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetExtAlbumsByWork return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtAlbumsInfo(int rows, df_extalbuminforow *input, void *context) {
	df_extalbuminforow *current;

	printf("Printing GetExtAlbumsInfo return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Discs: %d\n", current->Discs);
		printf("DiscNumber: %d\n", current->DiscNumber);
		printf("CatalogID: \"%s\"\n", current->CatalogID);
		printf("ImageURL: \"%s\"\n", current->ImageURL);

		current = current->next;
	}

	df_extalbuminforow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtAlbumsSearchPeople(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetExtAlbumsSearchPeople return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtContributorDetails(int rows, df_extcontributorrow *input, void *context) {
	df_extcontributorrow *current;

	printf("Printing GetExtContributorDetails return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("ContributorKey: %d\n", current->ContributorKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ContributorType: %d\n", current->ContributorType);

		current = current->next;
	}

	df_extcontributorrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtContributors(int rows, df_extcontributorrow *input, void *context) {
	df_extcontributorrow *current;

	printf("Printing GetExtContributors return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("ContributorKey: %d\n", current->ContributorKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ContributorType: %d\n", current->ContributorType);

		current = current->next;
	}

	df_extcontributorrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtContributorsForAlbum(int rows, df_extcontributorrow *input, void *context) {
	df_extcontributorrow *current;

	printf("Printing GetExtContributorsForAlbum return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("ContributorKey: %d\n", current->ContributorKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ContributorType: %d\n", current->ContributorType);

		current = current->next;
	}

	df_extcontributorrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtContributorsForDevice(int rows, df_extcontributorrow *input, void *context) {
	df_extcontributorrow *current;

	printf("Printing GetExtContributorsForDevice return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("ContributorKey: %d\n", current->ContributorKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ContributorType: %d\n", current->ContributorType);

		current = current->next;
	}

	df_extcontributorrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtContributorsForServer(int rows, df_extcontributorrow *input, void *context) {
	df_extcontributorrow *current;

	printf("Printing GetExtContributorsForServer return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("ContributorKey: %d\n", current->ContributorKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ContributorType: %d\n", current->ContributorType);

		current = current->next;
	}

	df_extcontributorrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtContributorsForShare(int rows, df_extcontributorrow *input, void *context) {
	df_extcontributorrow *current;

	printf("Printing GetExtContributorsForShare return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("ContributorKey: %d\n", current->ContributorKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ContributorType: %d\n", current->ContributorType);

		current = current->next;
	}

	df_extcontributorrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtCountAlbumsByContributor(int input, void *context) {
	printf("Printing GetExtCountAlbumsByContributor return:\n");
	printf("GetExtCountAlbumsByContributor_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtCountAlbumsByContributorForDevice(int input, void *context) {
	printf("Printing GetExtCountAlbumsByContributorForDevice return:\n");
	printf("GetExtCountAlbumsByContributorForDevice_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtCountAlbumsByContributorForServer(int input, void *context) {
	printf("Printing GetExtCountAlbumsByContributorForServer return:\n");
	printf("GetExtCountAlbumsByContributorForServer_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtCountAlbumsByContributorForShare(int input, void *context) {
	printf("Printing GetExtCountAlbumsByContributorForShare return:\n");
	printf("GetExtCountAlbumsByContributorForShare_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtCountContributors(int input, void *context) {
	printf("Printing GetExtCountContributors return:\n");
	printf("GetExtCountContributors_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtCountContributorsForDevice(int input, void *context) {
	printf("Printing GetExtCountContributorsForDevice return:\n");
	printf("GetExtCountContributorsForDevice_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtCountContributorsForServer(int input, void *context) {
	printf("Printing GetExtCountContributorsForServer return:\n");
	printf("GetExtCountContributorsForServer_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtCountContributorsForShare(int input, void *context) {
	printf("Printing GetExtCountContributorsForShare return:\n");
	printf("GetExtCountContributorsForShare_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtTrackContributors(int rows, df_exttrackcontribrow *input, void *context) {
	df_exttrackcontribrow *current;

	printf("Printing GetExtTrackContributors return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("ContributorKey: %d\n", current->ContributorKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ContributorType: %d\n", current->ContributorType);

		current = current->next;
	}

	df_exttrackcontribrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtTracksByContributor(int rows, df_trackrow *input, void *context) {
	df_trackrow *current;

	printf("Printing GetExtTracksByContributor return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);

		current = current->next;
	}

	df_trackrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtTracksByContributorForDevice(int rows, df_trackrow *input, void *context) {
	df_trackrow *current;

	printf("Printing GetExtTracksByContributorForDevice return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);

		current = current->next;
	}

	df_trackrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtTracksByContributorForServer(int rows, df_trackrow *input, void *context) {
	df_trackrow *current;

	printf("Printing GetExtTracksByContributorForServer return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);

		current = current->next;
	}

	df_trackrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtTracksByContributorForShare(int rows, df_trackrow *input, void *context) {
	df_trackrow *current;

	printf("Printing GetExtTracksByContributorForShare return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);

		current = current->next;
	}

	df_trackrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtTracksByWork(int rows, df_trackrow *input, void *context) {
	df_trackrow *current;

	printf("Printing GetExtTracksByWork return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);

		current = current->next;
	}

	df_trackrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtTracksInfo(int rows, df_exttrackinforow *input, void *context) {
	df_exttrackinforow *current;

	printf("Printing GetExtTracksInfo return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("CompositionDate: \"%s\"\n", current->CompositionDate);
		printf("Part: \"%s\"\n", current->Part);
		printf("PerformanceDate: \"%s\"\n", current->PerformanceDate);
		printf("Work: \"%s\"\n", current->Work);

		current = current->next;
	}

	df_exttrackinforow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExtWorks(int rows, df_extworksrow *input, void *context) {
	df_extworksrow *current;

	printf("Printing GetExtWorks return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("Work: \"%s\"\n", current->Work);

		current = current->next;
	}

	df_extworksrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExternalStorageDetail(df_extstoragedetail* input, void *context) {
	printf("Printing GetExternalStorageDetail return:\n");
	printf("StorageKey: %d\n", input->StorageKey);
	printf("IPAddress: \"%s\"\n", input->IPAddress);
	printf("HostName: \"%s\"\n", input->HostName);
	printf("ShareName: \"%s\"\n", input->ShareName);
	printf("FullSharePath: \"%s\"\n", input->FullSharePath);
	printf("State: \"%s\"\n", input->State);
	printf("LastState: \"%s\"\n", input->LastState);
	printf("Active: %d\n", input->Active);
	printf("UserName: \"%s\"\n", input->UserName);
	printf("Password: \"%s\"\n", input->Password);
	printf("ScanIgnore: \"%s\"\n", input->ScanIgnore);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetExternalStorages(int rows, df_externalstoragerow *input, void *context) {
	df_externalstoragerow *current;

	printf("Printing GetExternalStorages return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("StorageKey: %d\n", current->StorageKey);
		printf("IPAddress: \"%s\"\n", current->IPAddress);
		printf("HostName: \"%s\"\n", current->HostName);
		printf("ShareName: \"%s\"\n", current->ShareName);
		printf("FullSharePath: \"%s\"\n", current->FullSharePath);
		printf("State: \"%s\"\n", current->State);
		printf("LastState: \"%s\"\n", current->LastState);
		printf("Active: %d\n", current->Active);
		printf("UserName: \"%s\"\n", current->UserName);
		printf("Password: \"%s\"\n", current->Password);
		printf("ScanIgnore: \"%s\"\n", current->ScanIgnore);

		current = current->next;
	}

	df_externalstoragerow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetFileSystemDriveDetail(df_fsdrivedetail* input, void *context) {
	printf("Printing GetFileSystemDriveDetail return:\n");
	printf("DriveLetter: \"%s\"\n", input->DriveLetter);
	printf("RootPath: \"%s\"\n", input->RootPath);
	printf("SharePath: \"%s\"\n", input->SharePath);
	printf("Usage: %d\n", input->Usage);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetGenreDetail(df_genre* input, void *context) {
	printf("Printing GetGenreDetail return:\n");
	printf("GenreKey: %d\n", input->GenreKey);
	printf("GenreName: \"%s\"\n", input->GenreName);
	printf("Ordinal: %d\n", input->Ordinal);
	printf("Storage: %d\n", input->Storage);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetGenres(int rows, df_genrerow *input, void *context) {
	df_genrerow *current;

	printf("Printing GetGenres return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("GenreKey: %d\n", current->GenreKey);
		printf("Genre: \"%s\"\n", current->Genre);
		printf("GenreOrdinal: %d\n", current->GenreOrdinal);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_genrerow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetGenresSubGenres(int rows, df_genressubgenresrow *input, void *context) {
	df_genressubgenresrow *current;

	printf("Printing GetGenresSubGenres return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("SubGenreKey: %d\n", current->SubGenreKey);
		printf("SubGenre: \"%s\"\n", current->SubGenre);
		printf("GenreKey: %d\n", current->GenreKey);
		printf("Genre: \"%s\"\n", current->Genre);
		printf("GenreOrdinal: %d\n", current->GenreOrdinal);
		printf("SubGenreOrdinal: %d\n", current->SubGenreOrdinal);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_genressubgenresrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetHostDetails(df_hostdetails* input, void *context) {
	printf("Printing GetHostDetails return:\n");
	printf("GetHostDetails_Name: \"%s\"\n", input->GetHostDetails_Name);
	printf("GetHostDetails_Address: \"%s\"\n", input->GetHostDetails_Address);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetLastError(char* input, void *context) {
	printf("Printing GetLastError return:\n");
	printf("GetLastError_Return: \"%s\"\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetLatestPlayedAlbums(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetLatestPlayedAlbums return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetLibraryCheckSum(int input, void *context) {
	printf("Printing GetLibraryCheckSum return:\n");
	printf("GetLibraryCheckSum_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetLinkedRoomDetail(int rows, df_linkedroomdetailrow *input, void *context) {
	df_linkedroomdetailrow *current;

	printf("Printing GetLinkedRoomDetail return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("RoomKey: %d\n", current->RoomKey);
		printf("IPAddress: \"%s\"\n", current->IPAddress);
		printf("Channel: %d\n", current->Channel);
		printf("RoomName: \"%s\"\n", current->RoomName);
		printf("ShortName: \"%s\"\n", current->ShortName);
		printf("IsMultiRoom: %d\n", current->IsMultiRoom);
		printf("PlaybackCapability: %d\n", current->PlaybackCapability);
		printf("RippingCapability: %d\n", current->RippingCapability);
		printf("MusicManagementCapability: %d\n", current->MusicManagementCapability);
		printf("RoomID: %d\n", current->RoomID);
		printf("HostName: \"%s\"\n", current->HostName);

		current = current->next;
	}

	df_linkedroomdetailrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetLinkedRooms(int rows, df_roomrow *input, void *context) {
	df_roomrow *current;

	printf("Printing GetLinkedRooms return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

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

	df_roomrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetNetworkActiveAdapters(int rows, df_networkadaptorrow *input, void *context) {
	df_networkadaptorrow *current;

	printf("Printing GetNetworkActiveAdapters return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("DeviceID: %d\n", current->DeviceID);
		printf("Description: \"%s\"\n", current->Description);
		printf("MacAddress: \"%s\"\n", current->MacAddress);
		printf("DhcpEnabled: %d\n", current->DhcpEnabled);
		printf("IpAddress: \"%s\"\n", current->IpAddress);
		printf("SubnetMask: \"%s\"\n", current->SubnetMask);
		printf("DefaultGateway: \"%s\"\n", current->DefaultGateway);
		printf("DnsServer: \"%s\"\n", current->DnsServer);

		current = current->next;
	}

	df_networkadaptorrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetNetworkWorkgroup(char* input, void *context) {
	printf("Printing GetNetworkWorkgroup return:\n");
	printf("Workgroup: \"%s\"\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetNewestAlbums(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetNewestAlbums return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetNonLinkedRooms(int rows, df_roomrow *input, void *context) {
	df_roomrow *current;

	printf("Printing GetNonLinkedRooms return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

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

	df_roomrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetOperationActivity(char* input, void *context) {
	printf("Printing GetOperationActivity return:\n");
	printf("GetOperationActivity_Return: \"%s\"\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetOutputChannels(int rows, df_outputchannelrow *input, void *context) {
	df_outputchannelrow *current;

	printf("Printing GetOutputChannels return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("InitString: \"%s\"\n", current->InitString);
		printf("ChannelID: %d\n", current->ChannelID);

		current = current->next;
	}

	df_outputchannelrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetOutputDevices(int rows, df_outputdevicerow *input, void *context) {
	df_outputdevicerow *current;

	printf("Printing GetOutputDevices return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("Name: \"%s\"\n", current->Name);
		printf("OutputDeviceID: %d\n", current->OutputDeviceID);

		current = current->next;
	}

	df_outputdevicerow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetPlayListsByLetter(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetPlayListsByLetter return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetPlayerInstances(int rows, df_playerinstancerow *input, void *context) {
	df_playerinstancerow *current;

	printf("Printing GetPlayerInstances return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("Key: %d\n", current->Key);
		printf("Name: \"%s\"\n", current->Name);
		printf("OutputDeviceID: %d\n", current->OutputDeviceID);
		printf("SourceLineID: %d\n", current->SourceLineID);

		current = current->next;
	}

	df_playerinstancerow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetPlayerStatus(char* input, void *context) {
	printf("Printing GetPlayerStatus return:\n");
	printf("Status: \"%s\"\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetPlayerVersion(char* input, void *context) {
	printf("Printing GetPlayerVersion return:\n");
	printf("Version: \"%s\"\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetPlaylistsForGenre(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetPlaylistsForGenre return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetPlaylistsForSubGenre(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetPlaylistsForSubGenre return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetPlaylistsForSubGenreForDevice(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetPlaylistsForSubGenreForDevice return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetPlaylistsForSubGenreForServer(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetPlaylistsForSubGenreForServer return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetPlaylistsForSubGenreForShare(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetPlaylistsForSubGenreForShare return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetRepeat(int input, void *context) {
	printf("Printing GetRepeat return:\n");
	printf("Repeat: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetRipEncSettings(int rows, df_settingsrow *input, void *context) {
	df_settingsrow *current;

	printf("Printing GetRipEncSettings return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("RegistryKey: \"%s\"\n", current->RegistryKey);
		printf("Value: \"%s\"\n", current->Value);
		printf("ReadOnly: %d\n", current->ReadOnly);
		printf("Default: \"%s\"\n", current->Default);
		printf("MaxLength: %d\n", current->MaxLength);

		current = current->next;
	}

	df_settingsrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetRipEncSettingsEx(int rows, df_settingsexrow *input, void *context) {
	df_settingsexrow *current;

	printf("Printing GetRipEncSettingsEx return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("RegistryKey: \"%s\"\n", current->RegistryKey);
		printf("Value: \"%s\"\n", current->Value);
		printf("ReadOnly: %d\n", current->ReadOnly);
		printf("Default: \"%s\"\n", current->Default);
		printf("MaxLength: %d\n", current->MaxLength);
		printf("ValueType: %d\n", current->ValueType);
		printf("TabCaption: \"%s\"\n", current->TabCaption);
		printf("Category: \"%s\"\n", current->Category);
		printf("Caption: \"%s\"\n", current->Caption);
		printf("ShortTabCaption: \"%s\"\n", current->ShortTabCaption);
		printf("ShortCategory: \"%s\"\n", current->ShortCategory);
		printf("ShortCaption: \"%s\"\n", current->ShortCaption);
		printf("Description: \"%s\"\n", current->Description);

		current = current->next;
	}

	df_settingsexrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetRippingAlerts(int rows, df_rippingalertrow *input, void *context) {
	df_rippingalertrow *current;

	printf("Printing GetRippingAlerts return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("AlertKey: %d\n", current->AlertKey);
		printf("Severity: \"%s\"\n", current->Severity);
		printf("Category: \"%s\"\n", current->Category);

		current = current->next;
	}

	df_rippingalertrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetRippingStatus(int rows, df_type1row *input, void *context) {
	df_type1row *current;

	printf("Printing GetRippingStatus return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("Artist: \"%s\"\n", current->Artist);
		printf("Album: \"%s\"\n", current->Album);
		printf("Tracks: %d\n", current->Tracks);
		printf("TracksRipped: %d\n", current->TracksRipped);
		printf("Errors: %d\n", current->Errors);
		printf("Track: \"%s\"\n", current->Track);
		printf("TrackPercent: %d\n", current->TrackPercent);
		printf("UserMessage: \"%s\"\n", current->UserMessage);
		printf("LookupProviderUsed: \"%s\"\n", current->LookupProviderUsed);
		printf("Destination: \"%s\"\n", current->Destination);

		current = current->next;
	}

	df_type1row_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetRoomDetail(df_room* input, void *context) {
	printf("Printing GetRoomDetail return:\n");
	printf("RoomKey: %d\n", input->RoomKey);
	printf("IPAddress: \"%s\"\n", input->IPAddress);
	printf("Channel: %d\n", input->Channel);
	printf("RoomName: \"%s\"\n", input->RoomName);
	printf("ShortName: %d\n", input->ShortName);
	printf("IsMultiRoom: %d\n", input->IsMultiRoom);
	printf("PlaybackCapability: %d\n", input->PlaybackCapability);
	printf("RippingCapability: %d\n", input->RippingCapability);
	printf("MusicManagementCapability: %d\n", input->MusicManagementCapability);
	printf("RoomID: %d\n", input->RoomID);
	printf("HostName: \"%s\"\n", input->HostName);
	printf("Created: %d\n", input->Created);
	printf("Modified: %d\n", input->Modified);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetRooms(int rows, df_roomrow *input, void *context) {
	df_roomrow *current;

	printf("Printing GetRooms return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

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

	df_roomrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetRoomsWithPlayBack(int rows, df_roomrow *input, void *context) {
	df_roomrow *current;

	printf("Printing GetRoomsWithPlayBack return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

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

	df_roomrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetRoomsWithRipping(int rows, df_roomrow *input, void *context) {
	df_roomrow *current;

	printf("Printing GetRoomsWithRipping return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

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

	df_roomrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetRows(int input, void *context) {
	printf("Printing GetRows return:\n");
	printf("GetRows_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetSearchOffset(df_searchoffset* input, void *context) {
	printf("Printing GetSearchOffset return:\n");
	printf("GetSearchOffset_Return: %d\n", input->GetSearchOffset_Return);
	printf("GetSearchOffset_Count: %d\n", input->GetSearchOffset_Count);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetSettings(int rows, df_settingsrow *input, void *context) {
	df_settingsrow *current;

	printf("Printing GetSettings return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("RegistryKey: \"%s\"\n", current->RegistryKey);
		printf("Value: \"%s\"\n", current->Value);
		printf("ReadOnly: %d\n", current->ReadOnly);
		printf("Default: \"%s\"\n", current->Default);
		printf("MaxLength: %d\n", current->MaxLength);

		current = current->next;
	}

	df_settingsrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetSettingsEx(int rows, df_settingsexrow *input, void *context) {
	df_settingsexrow *current;

	printf("Printing GetSettingsEx return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("RegistryKey: \"%s\"\n", current->RegistryKey);
		printf("Value: \"%s\"\n", current->Value);
		printf("ReadOnly: %d\n", current->ReadOnly);
		printf("Default: \"%s\"\n", current->Default);
		printf("MaxLength: %d\n", current->MaxLength);
		printf("ValueType: %d\n", current->ValueType);
		printf("TabCaption: \"%s\"\n", current->TabCaption);
		printf("Category: \"%s\"\n", current->Category);
		printf("Caption: \"%s\"\n", current->Caption);
		printf("ShortTabCaption: \"%s\"\n", current->ShortTabCaption);
		printf("ShortCategory: \"%s\"\n", current->ShortCategory);
		printf("ShortCaption: \"%s\"\n", current->ShortCaption);
		printf("Description: \"%s\"\n", current->Description);

		current = current->next;
	}

	df_settingsexrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetSetupVal(int input, void *context) {
	printf("Printing GetSetupVal return:\n");
	printf("GetSetupVal_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetShuffle(int input, void *context) {
	printf("Printing GetShuffle return:\n");
	printf("Shuffle: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetSingleRipEncSetting(char* input, void *context) {
	printf("Printing GetSingleRipEncSetting return:\n");
	printf("GetSingleRipEncSetting_Return: \"%s\"\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetSingleSystemSetting(char* input, void *context) {
	printf("Printing GetSingleSystemSetting return:\n");
	printf("GetSingleSystemSetting_Return: \"%s\"\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetStatusMessageDetail(df_messagedetail* input, void *context) {
	printf("Printing GetStatusMessageDetail return:\n");
	printf("Message: \"%s\"\n", input->Message);
	printf("Category: \"%s\"\n", input->Category);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetStatusMessages(int rows, df_statusmessagerow *input, void *context) {
	df_statusmessagerow *current;

	printf("Printing GetStatusMessages return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("MessageAddress: %d\n", current->MessageAddress);
		printf("Severity: \"%s\"\n", current->Severity);
		printf("Category: \"%s\"\n", current->Category);
		printf("Tag: %d\n", current->Tag);

		current = current->next;
	}

	df_statusmessagerow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetStoreDetail(int rows, df_storedetailrow *input, void *context) {
	df_storedetailrow *current;

	printf("Printing GetStoreDetail return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("MusicStoreKey: %d\n", current->MusicStoreKey);
		printf("Path: \"%s\"\n", current->Path);
		printf("Local: %d\n", current->Local);
		printf("IPAddress: \"%s\"\n", current->IPAddress);
		printf("Online: %d\n", current->Online);
		printf("State: \"%s\"\n", current->State);
		printf("Priority: %d\n", current->Priority);
		printf("Username: \"%s\"\n", current->Username);
		printf("Password: \"%s\"\n", current->Password);
		printf("SpaceUsed: \"%s\"\n", current->SpaceUsed);
		printf("SpaceAvailable: \"%s\"\n", current->SpaceAvailable);
		printf("NumberOfAlbums: %d\n", current->NumberOfAlbums);

		current = current->next;
	}

	df_storedetailrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetStores(int rows, df_storerow *input, void *context) {
	df_storerow *current;

	printf("Printing GetStores return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("MusicStoreKey: %d\n", current->MusicStoreKey);
		printf("Path: \"%s\"\n", current->Path);
		printf("Local: %d\n", current->Local);
		printf("IPAddress: \"%s\"\n", current->IPAddress);
		printf("Online: %d\n", current->Online);
		printf("State: \"%s\"\n", current->State);
		printf("Priority: %d\n", current->Priority);

		current = current->next;
	}

	df_storerow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetSubGenreDetail(df_subgenre* input, void *context) {
	printf("Printing GetSubGenreDetail return:\n");
	printf("SubGenreKey: %d\n", input->SubGenreKey);
	printf("GenreKey: %d\n", input->GenreKey);
	printf("SubGenreName: \"%s\"\n", input->SubGenreName);
	printf("Ordinal: %d\n", input->Ordinal);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetSubGenresForDevice(int rows, df_subgenrerow *input, void *context) {
	df_subgenrerow *current;

	printf("Printing GetSubGenresForDevice return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("SubGenreKey: %d\n", current->SubGenreKey);
		printf("SubGenre: \"%s\"\n", current->SubGenre);
		printf("SubGenreOrdinal: %d\n", current->SubGenreOrdinal);

		current = current->next;
	}

	df_subgenrerow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetSubGenresForGenre(int rows, df_subgenrerow *input, void *context) {
	df_subgenrerow *current;

	printf("Printing GetSubGenresForGenre return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("SubGenreKey: %d\n", current->SubGenreKey);
		printf("SubGenre: \"%s\"\n", current->SubGenre);
		printf("SubGenreOrdinal: %d\n", current->SubGenreOrdinal);

		current = current->next;
	}

	df_subgenrerow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetSubGenresForServer(int rows, df_subgenrerow *input, void *context) {
	df_subgenrerow *current;

	printf("Printing GetSubGenresForServer return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("SubGenreKey: %d\n", current->SubGenreKey);
		printf("SubGenre: \"%s\"\n", current->SubGenre);
		printf("SubGenreOrdinal: %d\n", current->SubGenreOrdinal);

		current = current->next;
	}

	df_subgenrerow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetSubGenresForShare(int rows, df_subgenrerow *input, void *context) {
	df_subgenrerow *current;

	printf("Printing GetSubGenresForShare return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("SubGenreKey: %d\n", current->SubGenreKey);
		printf("SubGenre: \"%s\"\n", current->SubGenre);
		printf("SubGenreOrdinal: %d\n", current->SubGenreOrdinal);

		current = current->next;
	}

	df_subgenrerow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetSystemDrives(int rows, df_driverow *input, void *context) {
	df_driverow *current;

	printf("Printing GetSystemDrives return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("DriveKey: %d\n", current->DriveKey);
		printf("DriveLetter: \"%s\"\n", current->DriveLetter);
		printf("IsPrimary: %d\n", current->IsPrimary);
		printf("RootPath: \"%s\"\n", current->RootPath);
		printf("SharePath: \"%s\"\n", current->SharePath);
		printf("Usage: %d\n", current->Usage);

		current = current->next;
	}

	df_driverow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetSystemTime(df_systemtime* input, void *context) {
	printf("Printing GetSystemTime return:\n");
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTopPlayedAlbums(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetTopPlayedAlbums return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTrackCount(int input, void *context) {
	printf("Printing GetTrackCount return:\n");
	printf("TrackCount: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTrackDetailsFromPlayer(df_trackfromplayer* input, void *context) {
	printf("Printing GetTrackDetailsFromPlayer return:\n");
	printf("Source: %d\n", input->Source);
	printf("Name: \"%s\"\n", input->Name);
	printf("Album: \"%s\"\n", input->Album);
	printf("Artist: \"%s\"\n", input->Artist);
	printf("Genre: \"%s\"\n", input->Genre);
	printf("Comment: \"%s\"\n", input->Comment);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTrackLength(df_time input, void *context) {
	printf("Printing GetTrackLength return:\n");
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTrackName(df_trkname* input, void *context) {
	printf("Printing GetTrackName return:\n");
	printf("TrackKey: %d\n", input->TrackKey);
	printf("Name: \"%s\"\n", input->Name);
	printf("Type: \"%s\"\n", input->Type);
	printf("Source: %d\n", input->Source);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTrackNum(int input, void *context) {
	printf("Printing GetTrackNum return:\n");
	printf("TrackNumber: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTrackPosition(df_time input, void *context) {
	printf("Printing GetTrackPosition return:\n");
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTrackRange(int rows, df_trackrangerow *input, void *context) {
	df_trackrangerow *current;

	printf("Printing GetTrackRange return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);
		printf("AllTracksOffset: %d\n", current->AllTracksOffset);

		current = current->next;
	}

	df_trackrangerow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTracksAll(int rows, df_trackrow *input, void *context) {
	df_trackrow *current;

	printf("Printing GetTracksAll return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);

		current = current->next;
	}

	df_trackrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTracksForAlbumInUPL(int rows, df_trackrow *input, void *context) {
	df_trackrow *current;

	printf("Printing GetTracksForAlbumInUPL return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);

		current = current->next;
	}

	df_trackrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTracksForArtist(int rows, df_trackrow *input, void *context) {
	df_trackrow *current;

	printf("Printing GetTracksForArtist return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);

		current = current->next;
	}

	df_trackrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTracksForArtistForDevice(int rows, df_trackrow *input, void *context) {
	df_trackrow *current;

	printf("Printing GetTracksForArtistForDevice return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);

		current = current->next;
	}

	df_trackrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTracksForArtistForServer(int rows, df_trackrow *input, void *context) {
	df_trackrow *current;

	printf("Printing GetTracksForArtistForServer return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);

		current = current->next;
	}

	df_trackrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTracksForArtistForShare(int rows, df_trackrow *input, void *context) {
	df_trackrow *current;

	printf("Printing GetTracksForArtistForShare return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);

		current = current->next;
	}

	df_trackrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTracksForDeletion(int rows, df_type3row *input, void *context) {
	df_type3row *current;

	printf("Printing GetTracksForDeletion return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);
		printf("AlbumKey: %d\n", current->AlbumKey);
		printf("AlbumName: \"%s\"\n", current->AlbumName);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("SubGenre: \"%s\"\n", current->SubGenre);
		printf("CoverURL: \"%s\"\n", current->CoverURL);
		printf("BitRate: %d\n", current->BitRate);
		printf("CoverAvailable: %d\n", current->CoverAvailable);

		current = current->next;
	}

	df_type3row_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTracksForDevice(int rows, df_trackrow *input, void *context) {
	df_trackrow *current;

	printf("Printing GetTracksForDevice return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);

		current = current->next;
	}

	df_trackrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTracksForGenre(int rows, df_trackrow *input, void *context) {
	df_trackrow *current;

	printf("Printing GetTracksForGenre return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);

		current = current->next;
	}

	df_trackrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTracksForNamedEntity(int rows, df_trackrow *input, void *context) {
	df_trackrow *current;

	printf("Printing GetTracksForNamedEntity return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);

		current = current->next;
	}

	df_trackrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTracksForPlaylist(int rows, df_tracksforplaylistrow *input, void *context) {
	df_tracksforplaylistrow *current;

	printf("Printing GetTracksForPlaylist return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);
		printf("Hidden: %d\n", current->Hidden);

		current = current->next;
	}

	df_tracksforplaylistrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTracksForServer(int rows, df_trackrow *input, void *context) {
	df_trackrow *current;

	printf("Printing GetTracksForServer return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);

		current = current->next;
	}

	df_trackrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTracksForShare(int rows, df_trackrow *input, void *context) {
	df_trackrow *current;

	printf("Printing GetTracksForShare return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);

		current = current->next;
	}

	df_trackrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTracksForSubGenre(int rows, df_trackrow *input, void *context) {
	df_trackrow *current;

	printf("Printing GetTracksForSubGenre return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);

		current = current->next;
	}

	df_trackrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTracksForSubGenreForDevice(int rows, df_trackrow *input, void *context) {
	df_trackrow *current;

	printf("Printing GetTracksForSubGenreForDevice return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);

		current = current->next;
	}

	df_trackrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTracksForSubGenreForServer(int rows, df_trackrow *input, void *context) {
	df_trackrow *current;

	printf("Printing GetTracksForSubGenreForServer return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);

		current = current->next;
	}

	df_trackrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTracksForSubGenreForShare(int rows, df_trackrow *input, void *context) {
	df_trackrow *current;

	printf("Printing GetTracksForSubGenreForShare return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);

		current = current->next;
	}

	df_trackrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTracksOtherInfo(int rows, df_type3row *input, void *context) {
	df_type3row *current;

	printf("Printing GetTracksOtherInfo return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);
		printf("AlbumKey: %d\n", current->AlbumKey);
		printf("AlbumName: \"%s\"\n", current->AlbumName);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("SubGenre: \"%s\"\n", current->SubGenre);
		printf("CoverURL: \"%s\"\n", current->CoverURL);
		printf("BitRate: %d\n", current->BitRate);
		printf("CoverAvailable: %d\n", current->CoverAvailable);

		current = current->next;
	}

	df_type3row_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetTracksSearchName(int rows, df_type3row *input, void *context) {
	df_type3row *current;

	printf("Printing GetTracksSearchName return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("TrackKey: %d\n", current->TrackKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("SortName: \"%s\"\n", current->SortName);
		printf("Type: \"%s\"\n", current->Type);
		printf("Ordinal: %d\n", current->Ordinal);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
		printf("SampleRate: %d\n", current->SampleRate);
		printf("BitsPerSample: %d\n", current->BitsPerSample);
		printf("ChannelCount: %d\n", current->ChannelCount);
		printf("AlbumKey: %d\n", current->AlbumKey);
		printf("AlbumName: \"%s\"\n", current->AlbumName);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("SubGenre: \"%s\"\n", current->SubGenre);
		printf("CoverURL: \"%s\"\n", current->CoverURL);
		printf("BitRate: %d\n", current->BitRate);
		printf("CoverAvailable: %d\n", current->CoverAvailable);

		current = current->next;
	}

	df_type3row_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetUpnpMediaRenderers(int rows, df_mediarendererrow *input, void *context) {
	df_mediarendererrow *current;

	printf("Printing GetUpnpMediaRenderers return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("FriendlyName: \"%s\"\n", current->FriendlyName);
		printf("UDN: \"%s\"\n", current->UDN);
		printf("Manufacturer: \"%s\"\n", current->Manufacturer);
		printf("ModelNumber: \"%s\"\n", current->ModelNumber);
		printf("SupportedExtensions: \"%s\"\n", current->SupportedExtensions);

		current = current->next;
	}

	df_mediarendererrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetUserPlaylists(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetUserPlaylists return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetUserPlaylistsForDevice(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetUserPlaylistsForDevice return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetUserPlaylistsForServer(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetUserPlaylistsForServer return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetUserPlaylistsForShare(int rows, df_albumrow *input, void *context) {
	df_albumrow *current;

	printf("Printing GetUserPlaylistsForShare return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);

		current = current->next;
	}

	df_albumrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetUserStatus(int rows, df_keyvaluerow *input, void *context) {
	df_keyvaluerow *current;

	printf("Printing GetUserStatus return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("Name: \"%s\"\n", current->Name);
		printf("Value: \"%s\"\n", current->Value);

		current = current->next;
	}

	df_keyvaluerow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_GetVolume(int input, void *context) {
	printf("Printing GetVolume return:\n");
	printf("Volume: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_IgnoreExternalStorage(int input, void *context) {
	printf("Printing IgnoreExternalStorage return:\n");
	printf("IgnoreExternalStorage_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_IsCDPlaying(int input, void *context) {
	printf("Printing IsCDPlaying return:\n");
	printf("CDPlaying: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_LookupError(char* input, void *context) {
	printf("Printing LookupError return:\n");
	printf("LookupError_Return: \"%s\"\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_MoveAlbumGetQueue(int rows, df_movealbumgetqueuerow *input, void *context) {
	df_movealbumgetqueuerow *current;

	printf("Printing MoveAlbumGetQueue return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("QueueKey: %d\n", current->QueueKey);
		printf("Status: \"%s\"\n", current->Status);
		printf("Retries: %d\n", current->Retries);
		printf("LastError: \"%s\"\n", current->LastError);
		printf("AlbumKey: %d\n", current->AlbumKey);
		printf("StoreKey: %d\n", current->StoreKey);

		current = current->next;
	}

	df_movealbumgetqueuerow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_MoveAlbumGetStatus(df_movealbumstatus* input, void *context) {
	printf("Printing MoveAlbumGetStatus return:\n");
	printf("Running: %d\n", input->Running);
	printf("AlbumKey: %d\n", input->AlbumKey);
	printf("AlbumName: \"%s\"\n", input->AlbumName);
	printf("SourceStoreKey: %d\n", input->SourceStoreKey);
	printf("DestinationStoreKey: %d\n", input->DestinationStoreKey);
	printf("Progress: %d\n", input->Progress);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_MoveAlbumToMusicStore(int input, void *context) {
	printf("Printing MoveAlbumToMusicStore return:\n");
	printf("MoveAlbumToMusicStore_Count: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_NewOutputChannel(int input, void *context) {
	printf("Printing NewOutputChannel return:\n");
	printf("NewOutputChannel_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_NextTrack(int input, void *context) {
	printf("Printing NextTrack return:\n");
	printf("NewTrackNumber: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_PlayAlbum(int input, void *context) {
	printf("Printing PlayAlbum return:\n");
	printf("TracksAdded: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_PlayAlbums(int input, void *context) {
	printf("Printing PlayAlbums return:\n");
	printf("TracksAdded: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_PlayAlbumsFromSearch(int input, void *context) {
	printf("Printing PlayAlbumsFromSearch return:\n");
	printf("TracksAdded: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_PlayAll(int input, void *context) {
	printf("Printing PlayAll return:\n");
	printf("TracksAdded: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_PlayArtistAlbum(int input, void *context) {
	printf("Printing PlayArtistAlbum return:\n");
	printf("TracksAdded: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_PlayLastPlayed(int input, void *context) {
	printf("Printing PlayLastPlayed return:\n");
	printf("TracksAdded: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_PlayLastRipped(int input, void *context) {
	printf("Printing PlayLastRipped return:\n");
	printf("TracksAdded: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_PlayMostPopular(int input, void *context) {
	printf("Printing PlayMostPopular return:\n");
	printf("TracksAdded: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_PlayPlaylist(int input, void *context) {
	printf("Printing PlayPlaylist return:\n");
	printf("TracksAdded: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_PlayRandom(int input, void *context) {
	printf("Printing PlayRandom return:\n");
	printf("TracksAdded: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_PlayTrack(int input, void *context) {
	printf("Printing PlayTrack return:\n");
	printf("TracksAdded: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_PlayTracks(int input, void *context) {
	printf("Printing PlayTracks return:\n");
	printf("TracksAdded: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_PlayTracksFromSearch(int input, void *context) {
	printf("Printing PlayTracksFromSearch return:\n");
	printf("TracksAdded: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_PlayUrl(int input, void *context) {
	printf("Printing PlayUrl return:\n");
	printf("TracksAdded: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_PlayUrls(int input, void *context) {
	printf("Printing PlayUrls return:\n");
	printf("TracksAdded: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_PrevTrack(int input, void *context) {
	printf("Printing PrevTrack return:\n");
	printf("NewTrackNumber: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ProcessEmbeddedInit(char* input, void *context) {
	printf("Printing ProcessEmbeddedInit return:\n");
	printf("ProcessEmbeddedInit_Report: \"%s\"\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_PromoteShareToMusicStore(df_promoteshare* input, void *context) {
	printf("Printing PromoteShareToMusicStore return:\n");
	printf("PromoteShareToMusicStore_Success: %d\n", input->PromoteShareToMusicStore_Success);
	printf("PromoteShareToMusicStore_Message: \"%s\"\n", input->PromoteShareToMusicStore_Message);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_QueryAllPlayback(df_queryplayback* input, void *context) {
	printf("Printing QueryAllPlayback return:\n");
	printf("CDPlaying: %d\n", input->CDPlaying);
	printf("TrackName: \"%s\"\n", input->TrackName);
	printf("Album: \"%s\"\n", input->Album);
	printf("Artist: \"%s\"\n", input->Artist);
	printf("TrackNumber: %d\n", input->TrackNumber);
	printf("TrackCount: %d\n", input->TrackCount);
	printf("Shuffle: %d\n", input->Shuffle);
	printf("Repeat: %d\n", input->Repeat);
	printf("Status: \"%s\"\n", input->Status);
	printf("Version: \"%s\"\n", input->Version);
	printf("Volume: %d\n", input->Volume);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ReleaseSerialPort(int input, void *context) {
	printf("Printing ReleaseSerialPort return:\n");
	printf("ReleaseSerialPort_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_RemoveAlbumsFromUserPlaylist(int input, void *context) {
	printf("Printing RemoveAlbumsFromUserPlaylist return:\n");
	printf("RemoveAlbumsFromUserPlaylist_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_RemoveCoverImage(char* input, void *context) {
	printf("Printing RemoveCoverImage return:\n");
	printf("Success: \"%s\"\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_RemoveExternalStorage(int input, void *context) {
	printf("Printing RemoveExternalStorage return:\n");
	printf("RemoveExternalStorage_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_RemoveOldRooms(int input, void *context) {
	printf("Printing RemoveOldRooms return:\n");
	printf("RemoveOldRooms_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_RemovePlayerInstance(int input, void *context) {
	printf("Printing RemovePlayerInstance return:\n");
	printf("RemovePlayerInstance_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_RemoveTrack(int input, void *context) {
	printf("Printing RemoveTrack return:\n");
	printf("RemoveTrack_Response: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_RenameAlbum(char* input, void *context) {
	printf("Printing RenameAlbum return:\n");
	printf("ReNameAlbum_Return: \"%s\"\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_RenameArtist(char* input, void *context) {
	printf("Printing RenameArtist return:\n");
	printf("ReNameArtist_Return: \"%s\"\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_RenamePlaylist(int input, void *context) {
	printf("Printing RenamePlaylist return:\n");
	printf("RenamePlaylist_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_RenameTrack(char* input, void *context) {
	printf("Printing RenameTrack return:\n");
	printf("ReNameTrack_Return: \"%s\"\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_RequestAlbumCover(int input, void *context) {
	printf("Printing RequestAlbumCover return:\n");
	printf("RequestAlbumCover_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_RescanExternalStorages(int input, void *context) {
	printf("Printing RescanExternalStorages return:\n");
	printf("RescanExternalStorages_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_RescanMusicStore(df_rescanresult* input, void *context) {
	printf("Printing RescanMusicStore return:\n");
	printf("RescanMusicStore_Success: %d\n", input->RescanMusicStore_Success);
	printf("RescanMusicStore_Message: \"%s\"\n", input->RescanMusicStore_Message);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_RestoreSingleAlbum(int input, void *context) {
	printf("Printing RestoreSingleAlbum return:\n");
	printf("RestoreSingleAlbum_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_RestoreSingleTrack(int input, void *context) {
	printf("Printing RestoreSingleTrack return:\n");
	printf("RestoreSingleTrack_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_SaveCurrentPlayList(int input, void *context) {
	printf("Printing SaveCurrentPlayList return:\n");
	printf("SaveCurrentPlayList_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_SavePlayerInstance(int input, void *context) {
	printf("Printing SavePlayerInstance return:\n");
	printf("SavePlayerInstance_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ScanExternalStorage(int input, void *context) {
	printf("Printing ScanExternalStorage return:\n");
	printf("ScanExternalStorage_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ScanForExternalStorages(int input, void *context) {
	printf("Printing ScanForExternalStorages return:\n");
	printf("ScanForExternalStorages_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ServiceMode(df_servicemode* input, void *context) {
	printf("Printing ServiceMode return:\n");
	printf("ServiceMode_ModeValue: %d\n", input->ServiceMode_ModeValue);
	printf("ServiceMode_ModeName: \"%s\"\n", input->ServiceMode_ModeName);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_SetAlbumLowQuality(int input, void *context) {
	printf("Printing SetAlbumLowQuality return:\n");
	printf("SetAlbumLowQuality_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_SetCoverImage(char* input, void *context) {
	printf("Printing SetCoverImage return:\n");
	printf("Success: \"%s\"\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_SetDriveUsage(df_driveusageresult* input, void *context) {
	printf("Printing SetDriveUsage return:\n");
	printf("SetDriveUsage_Success: %d\n", input->SetDriveUsage_Success);
	printf("SetDriveUsage_DriveInUse: %d\n", input->SetDriveUsage_DriveInUse);
	printf("SetDriveUsage_Message: \"%s\"\n", input->SetDriveUsage_Message);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_SetMusicStoreCredentials(int input, void *context) {
	printf("Printing SetMusicStoreCredentials return:\n");
	printf("SetMusicStoreCredentials_Success: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_SetMusicStorePriority(df_musicstorepriorityresult* input, void *context) {
	printf("Printing SetMusicStorePriority return:\n");
	printf("SetMusicStorePriority_Success: %d\n", input->SetMusicStorePriority_Success);
	printf("SetMusicStorePriority_Message: \"%s\"\n", input->SetMusicStorePriority_Message);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_Status(int rows, df_statusrow *input, void *context) {
	df_statusrow *current;

	printf("Printing Status return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("StatusSettingName: \"%s\"\n", current->StatusSettingName);
		printf("StatusSettingValue: \"%s\"\n", current->StatusSettingValue);

		current = current->next;
	}

	df_statusrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_StopBackupDrive(df_stopbackupdriveresult* input, void *context) {
	printf("Printing StopBackupDrive return:\n");
	printf("StopBackupDrive_Success: %d\n", input->StopBackupDrive_Success);
	printf("StopBackupDrive_Message: \"%s\"\n", input->StopBackupDrive_Message);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_ToggleDeviceSync(int input, void *context) {
	printf("Printing ToggleDeviceSync return:\n");
	printf("ToggleDeviceSync_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_UndoUserEdits(int rows, df_bulklookuprow *input, void *context) {
	df_bulklookuprow *current;

	printf("Printing UndoUserEdits return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Success: %d\n", current->Success);
		printf("Message: \"%s\"\n", current->Message);

		current = current->next;
	}

	df_bulklookuprow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_UpdateBackupJob(int input, void *context) {
	printf("Printing UpdateBackupJob return:\n");
	printf("UpdateBackupJob_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_UpdateDrive(df_updatedrivedetails* input, void *context) {
	printf("Printing UpdateDrive return:\n");
	printf("UpdateDrive_Return: %d\n", input->UpdateDrive_Return);
	printf("UpdateDrive_ErrorMessage: \"%s\"\n", input->UpdateDrive_ErrorMessage);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_UpdateExternalStorage(int input, void *context) {
	printf("Printing UpdateExternalStorage return:\n");
	printf("UpdateExternalStorage_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_UpdateGenre(int input, void *context) {
	printf("Printing UpdateGenre return:\n");
	printf("UpdateGenre_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_UpdateHitCount(int input, void *context) {
	printf("Printing UpdateHitCount return:\n");
	printf("UpdateHitCount_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_UpdateLinkedRoom(int input, void *context) {
	printf("Printing UpdateLinkedRoom return:\n");
	printf("UpdateLinkedRoom_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_UpdateOutputChannel(int input, void *context) {
	printf("Printing UpdateOutputChannel return:\n");
	printf("UpdateOutputChannel_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_UpdatePlaylist(int input, void *context) {
	printf("Printing UpdatePlaylist return:\n");
	printf("UpdatePlaylist_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_UpdateRoom(int input, void *context) {
	printf("Printing UpdateRoom return:\n");
	printf("UpdateRoom_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_UpdateSingleRipEncSetting(char* input, void *context) {
	printf("Printing UpdateSingleRipEncSetting return:\n");
	printf("UpdateSingleRipEncSetting_Return: \"%s\"\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_UpdateSingleSystemSetting(char* input, void *context) {
	printf("Printing UpdateSingleSystemSetting return:\n");
	printf("UpdateSingleSystemSetting_Return: \"%s\"\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_UpdateSubGenre(int input, void *context) {
	printf("Printing UpdateSubGenre return:\n");
	printf("UpdateSubGenre_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_UploadMessages(int input, void *context) {
	printf("Printing UploadMessages return:\n");
	printf("UploadMessages_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_Version(df_version* input, void *context) {
	printf("Printing Version return:\n");
	printf("Version_Service: \"%s\"\n", input->Version_Service);
	printf("Version_Protocol: \"%s\"\n", input->Version_Protocol);
	printf("Version_CommandDef: \"%s\"\n", input->Version_CommandDef);
	printf("Version_System: \"%s\"\n", input->Version_System);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_vTunerAddRemoveFavourite(int input, void *context) {
	printf("Printing vTunerAddRemoveFavourite return:\n");
	printf("vTunerAddRemoveFavourite_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_vTunerCheckAvailability(int input, void *context) {
	printf("Printing vTunerCheckAvailability return:\n");
	printf("vTunerCheckAvailability_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_vTunerGetChildNodes(int rows, df_vtunernoderow *input, void *context) {
	df_vtunernoderow *current;

	printf("Printing vTunerGetChildNodes return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("Name: \"%s\"\n", current->Name);
		printf("NodeType: %d\n", current->NodeType);
		printf("UrlBookmark: \"%s\"\n", current->UrlBookmark);
		printf("UrlPlay: \"%s\"\n", current->UrlPlay);
		printf("UrlChildren: \"%s\"\n", current->UrlChildren);
		printf("UrlChildrenBackup: \"%s\"\n", current->UrlChildrenBackup);
		printf("ID: \"%s\"\n", current->ID);
		printf("Description: \"%s\"\n", current->Description);
		printf("ParentDescription: \"%s\"\n", current->ParentDescription);
		printf("Format: \"%s\"\n", current->Format);
		printf("Language: \"%s\"\n", current->Language);
		printf("City: \"%s\"\n", current->City);
		printf("State: \"%s\"\n", current->State);
		printf("Country: \"%s\"\n", current->Country);
		printf("Location: \"%s\"\n", current->Location);
		printf("Bandwidth: %d\n", current->Bandwidth);
		printf("MimeType: \"%s\"\n", current->MimeType);
		printf("ReliabilityRating: %d\n", current->ReliabilityRating);

		current = current->next;
	}

	df_vtunernoderow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_vTunerGetLastPlayed(int rows, df_vtunerplayedrow *input, void *context) {
	df_vtunerplayedrow *current;

	printf("Printing vTunerGetLastPlayed return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("Key: %d\n", current->Key);
		printf("HitCount: %d\n", current->HitCount);
		printf("Name: \"%s\"\n", current->Name);
		printf("NodeType: %d\n", current->NodeType);
		printf("UrlBookmark: \"%s\"\n", current->UrlBookmark);
		printf("UrlPlay: \"%s\"\n", current->UrlPlay);
		printf("UrlChildren: \"%s\"\n", current->UrlChildren);
		printf("UrlChildrenBackup: \"%s\"\n", current->UrlChildrenBackup);
		printf("ID: \"%s\"\n", current->ID);
		printf("Description: \"%s\"\n", current->Description);
		printf("ParentDescription: \"%s\"\n", current->ParentDescription);
		printf("Format: \"%s\"\n", current->Format);
		printf("Language: \"%s\"\n", current->Language);
		printf("City: \"%s\"\n", current->City);
		printf("State: \"%s\"\n", current->State);
		printf("Country: \"%s\"\n", current->Country);
		printf("Location: \"%s\"\n", current->Location);
		printf("Bandwidth: %d\n", current->Bandwidth);
		printf("MimeType: \"%s\"\n", current->MimeType);
		printf("ReliabilityRating: %d\n", current->ReliabilityRating);

		current = current->next;
	}

	df_vtunerplayedrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_vTunerGetMostPlayed(int rows, df_vtunerplayedrow *input, void *context) {
	df_vtunerplayedrow *current;

	printf("Printing vTunerGetMostPlayed return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("Key: %d\n", current->Key);
		printf("HitCount: %d\n", current->HitCount);
		printf("Name: \"%s\"\n", current->Name);
		printf("NodeType: %d\n", current->NodeType);
		printf("UrlBookmark: \"%s\"\n", current->UrlBookmark);
		printf("UrlPlay: \"%s\"\n", current->UrlPlay);
		printf("UrlChildren: \"%s\"\n", current->UrlChildren);
		printf("UrlChildrenBackup: \"%s\"\n", current->UrlChildrenBackup);
		printf("ID: \"%s\"\n", current->ID);
		printf("Description: \"%s\"\n", current->Description);
		printf("ParentDescription: \"%s\"\n", current->ParentDescription);
		printf("Format: \"%s\"\n", current->Format);
		printf("Language: \"%s\"\n", current->Language);
		printf("City: \"%s\"\n", current->City);
		printf("State: \"%s\"\n", current->State);
		printf("Country: \"%s\"\n", current->Country);
		printf("Location: \"%s\"\n", current->Location);
		printf("Bandwidth: %d\n", current->Bandwidth);
		printf("MimeType: \"%s\"\n", current->MimeType);
		printf("ReliabilityRating: %d\n", current->ReliabilityRating);

		current = current->next;
	}

	df_vtunerplayedrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_vTunerGetNodeFromPlayedUrl(int rows, df_vtunernoderow *input, void *context) {
	df_vtunernoderow *current;

	printf("Printing vTunerGetNodeFromPlayedUrl return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("Name: \"%s\"\n", current->Name);
		printf("NodeType: %d\n", current->NodeType);
		printf("UrlBookmark: \"%s\"\n", current->UrlBookmark);
		printf("UrlPlay: \"%s\"\n", current->UrlPlay);
		printf("UrlChildren: \"%s\"\n", current->UrlChildren);
		printf("UrlChildrenBackup: \"%s\"\n", current->UrlChildrenBackup);
		printf("ID: \"%s\"\n", current->ID);
		printf("Description: \"%s\"\n", current->Description);
		printf("ParentDescription: \"%s\"\n", current->ParentDescription);
		printf("Format: \"%s\"\n", current->Format);
		printf("Language: \"%s\"\n", current->Language);
		printf("City: \"%s\"\n", current->City);
		printf("State: \"%s\"\n", current->State);
		printf("Country: \"%s\"\n", current->Country);
		printf("Location: \"%s\"\n", current->Location);
		printf("Bandwidth: %d\n", current->Bandwidth);
		printf("MimeType: \"%s\"\n", current->MimeType);
		printf("ReliabilityRating: %d\n", current->ReliabilityRating);

		current = current->next;
	}

	df_vtunernoderow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_vTunerGetPresetChannels(int rows, df_vtunerpresetrow *input, void *context) {
	df_vtunerpresetrow *current;

	printf("Printing vTunerGetPresetChannels return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("Key: %d\n", current->Key);
		printf("ChannelNumber: %d\n", current->ChannelNumber);
		printf("ChannelName: \"%s\"\n", current->ChannelName);
		printf("Name: \"%s\"\n", current->Name);
		printf("NodeType: %d\n", current->NodeType);
		printf("UrlBookmark: \"%s\"\n", current->UrlBookmark);
		printf("UrlPlay: \"%s\"\n", current->UrlPlay);
		printf("UrlChildren: \"%s\"\n", current->UrlChildren);
		printf("UrlChildrenBackup: \"%s\"\n", current->UrlChildrenBackup);
		printf("ID: \"%s\"\n", current->ID);
		printf("Description: \"%s\"\n", current->Description);
		printf("ParentDescription: \"%s\"\n", current->ParentDescription);
		printf("Format: \"%s\"\n", current->Format);
		printf("Language: \"%s\"\n", current->Language);
		printf("City: \"%s\"\n", current->City);
		printf("State: \"%s\"\n", current->State);
		printf("Country: \"%s\"\n", current->Country);
		printf("Location: \"%s\"\n", current->Location);
		printf("Bandwidth: %d\n", current->Bandwidth);
		printf("MimeType: \"%s\"\n", current->MimeType);
		printf("ReliabilityRating: %d\n", current->ReliabilityRating);

		current = current->next;
	}

	df_vtunerpresetrow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_vTunerLookupById(int rows, df_vtunernoderow *input, void *context) {
	df_vtunernoderow *current;

	printf("Printing vTunerLookupById return:\n");
	printf("Total rows: %d\n", rows);
	current = input;

	while (current != NULL) {
		printf("Name: \"%s\"\n", current->Name);
		printf("NodeType: %d\n", current->NodeType);
		printf("UrlBookmark: \"%s\"\n", current->UrlBookmark);
		printf("UrlPlay: \"%s\"\n", current->UrlPlay);
		printf("UrlChildren: \"%s\"\n", current->UrlChildren);
		printf("UrlChildrenBackup: \"%s\"\n", current->UrlChildrenBackup);
		printf("ID: \"%s\"\n", current->ID);
		printf("Description: \"%s\"\n", current->Description);
		printf("ParentDescription: \"%s\"\n", current->ParentDescription);
		printf("Format: \"%s\"\n", current->Format);
		printf("Language: \"%s\"\n", current->Language);
		printf("City: \"%s\"\n", current->City);
		printf("State: \"%s\"\n", current->State);
		printf("Country: \"%s\"\n", current->Country);
		printf("Location: \"%s\"\n", current->Location);
		printf("Bandwidth: %d\n", current->Bandwidth);
		printf("MimeType: \"%s\"\n", current->MimeType);
		printf("ReliabilityRating: %d\n", current->ReliabilityRating);

		current = current->next;
	}

	df_vtunernoderow_free(input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_vTunerPlayById(int input, void *context) {
	printf("Printing vTunerPlayById return:\n");
	printf("TracksAdded: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_vTunerPlayByIds(int input, void *context) {
	printf("Printing vTunerPlayByIds return:\n");
	printf("TracksAdded: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

void print_vTunerSetPresetChannel(int input, void *context) {
	printf("Printing vTunerSetPresetChannel return:\n");
	printf("vTunerSetPresetChannel_Return: %d\n", input);
	fflush(stdout);
	pthread_mutex_unlock((pthread_mutex_t*)context);
}


void call_ActivateExternalStorage(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	int x2;



	printf("Calling ActivateExternalStorage\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("StorageKey: ");
	scanf("%d", &x0);
	printf("ActiveFlag: ");
	scanf("%d", &x1);
	printf("ClearPlaying: ");
	scanf("%d", &x2);

	df_ActivateExternalStorage(connections[conn_id], x0, x1, x2, print_ActivateExternalStorage, (void*)parent_lock);}

void call_AddAlbumsToUserPlaylist(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];



	printf("Calling AddAlbumsToUserPlaylist\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("UserPlaylistKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("AlbumKey: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_AddAlbumsToUserPlaylist(connections[conn_id], x0, x1, print_AddAlbumsToUserPlaylist, (void*)parent_lock);}

void call_AddExternalStorage(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];
	int x3;
	int x4;



	printf("Calling AddExternalStorage\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SharePath: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Username: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("Password: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("Activate: ");
	scanf("%d", &x3);
	printf("ForceAdd: ");
	scanf("%d", &x4);

	df_AddExternalStorage(connections[conn_id], x0, x1, x2, x3, x4, print_AddExternalStorage, (void*)parent_lock);}

void call_AddNewBackupJob(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];
	int x3;
	int x4;
	int x5;
	df_date x6;
	df_time x7;



	printf("Calling AddNewBackupJob\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SourceDriveAddress: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("DestinationDriveAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("Name: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("BackupType: ");
	scanf("%d", &x3);
	printf("BackupPeriod: ");
	scanf("%d", &x4);
	printf("PeriodValue: ");
	scanf("%d", &x5);
	printf("RunDate: ");
	//x6 = malloc(sizeof(df_date));
	scanf("%ud-%ud-%ud", &x6.day, &x6.month, &x6.year);
	printf("RunTime: ");
	//x7 = malloc(sizeof(df_time));
	scanf("%ud:%ud:%ud", &x7.hours, &x7.minutes, &x7.seconds);

	df_AddNewBackupJob(connections[conn_id], x0, x1, x2, x3, x4, x5, x6, x7, print_AddNewBackupJob, (void*)parent_lock);}

void call_AddNewDrive(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;
	char x2[30];
	char x3[30];
	int x4;
	int x5;



	printf("Calling AddNewDrive\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("DriveLetter: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("PrimaryDrive: ");
	scanf("%d", &x1);
	printf("RootPath: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("SharePath: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }
	printf("Usage: ");
	scanf("%d", &x4);
	printf("BadPathBehaviour: ");
	scanf("%d", &x5);

	df_AddNewDrive(connections[conn_id], x0, x1, x2, x3, x4, x5, print_AddNewDrive, (void*)parent_lock);}

void call_AddNewGenre(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;



	printf("Calling AddNewGenre\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("GenreName: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Ordinal: ");
	scanf("%d", &x1);

	df_AddNewGenre(connections[conn_id], x0, x1, print_AddNewGenre, (void*)parent_lock);}

void call_AddNewLinkedRoom(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	int x2;
	char x3[30];



	printf("Calling AddNewLinkedRoom\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomName: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("ShortName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("RoomID: ");
	scanf("%d", &x2);
	printf("ChildRoomKey: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }

	df_AddNewLinkedRoom(connections[conn_id], x0, x1, x2, x3, print_AddNewLinkedRoom, (void*)parent_lock);}

void call_AddNewRoom(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;
	char x2[30];
	char x3[30];
	int x4;
	int x5;
	int x6;
	int x7;
	char x8[30];



	printf("Calling AddNewRoom\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomIP: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Channel: ");
	scanf("%d", &x1);
	printf("RoomName: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("ShortName: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }
	printf("PlaybackCapability: ");
	scanf("%d", &x4);
	printf("RippingCapability: ");
	scanf("%d", &x5);
	printf("MusicManagementCapability: ");
	scanf("%d", &x6);
	printf("RoomID: ");
	scanf("%d", &x7);
	printf("HostName: ");
	scanf("%s", x8);
	if (x8[0] == '-') { x8[0] = '\0'; }

	df_AddNewRoom(connections[conn_id], x0, x1, x2, x3, x4, x5, x6, x7, x8, print_AddNewRoom, (void*)parent_lock);}

void call_AddNewSubGenre(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	int x2;



	printf("Calling AddNewSubGenre\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("GenreKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SubGenreName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("Ordinal: ");
	scanf("%d", &x2);

	df_AddNewSubGenre(connections[conn_id], x0, x1, x2, print_AddNewSubGenre, (void*)parent_lock);}

void call_AddTracksToUserPlaylist(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];



	printf("Calling AddTracksToUserPlaylist\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("UserPlaylistKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("TrackKey: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_AddTracksToUserPlaylist(connections[conn_id], x0, x1, print_AddTracksToUserPlaylist, (void*)parent_lock);}

void call_AdvancedSearch(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	int x2;
	int x3;
	char x4[30];
	char x5[30];
	int x6;
	int x7;
	int x8;

	printf("Calling AdvancedSearch\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("EntityName: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SearchString: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SearchType: ");
	scanf("%d", &x2);
	printf("Match: ");
	scanf("%d", &x3);
	printf("EntityName2: ");
	scanf("%s", x4);
	if (x4[0] == '-') { x4[0] = '\0'; }
	printf("SearchString2: ");
	scanf("%s", x5);
	if (x5[0] == '-') { x5[0] = '\0'; }
	printf("SearchType2: ");
	scanf("%d", &x6);
	printf("RemoteImagePath: ");
	scanf("%d", &x7);
	printf("ImageSize: ");
	scanf("%d", &x8);

	df_AdvancedSearch(connections[conn_id], x0, x1, x2, x3, x4, x5, x6, x7, x8, get_search_rows, print_AdvancedSearch, (void*)parent_lock);}

void call_BackupDrive(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	int x2;
	int x3;



	printf("Calling BackupDrive\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SourceDriveKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("DestDriveKey: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("BackupType: ");
	scanf("%d", &x2);
	printf("NoFileCheck: ");
	scanf("%d", &x3);

	df_BackupDrive(connections[conn_id], x0, x1, x2, x3, print_BackupDrive, (void*)parent_lock);}

void call_BulkCDLookup(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	int x2;
	char x3[30];

	printf("Calling BulkCDLookup\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("AllAlbums: ");
	scanf("%d", &x0);
	printf("Interval: ");
	scanf("%d", &x1);
	printf("IgnoreProviderUsed: ");
	scanf("%d", &x2);
	printf("AlbumKey: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }

	df_BulkCDLookup(connections[conn_id], x0, x1, x2, x3, get_search_rows, print_BulkCDLookup, (void*)parent_lock);}

void call_BulkCDLookupEx(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	char x2[30];



	printf("Calling BulkCDLookupEx\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("LookupProviderUsed: ");
	scanf("%d", &x0);
	printf("Interval: ");
	scanf("%d", &x1);
	printf("AlbumKey: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_BulkCDLookupEx(connections[conn_id], x0, x1, x2, print_BulkCDLookupEx, (void*)parent_lock);}

void call_CDLookupCancel(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling CDLookupCancel\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_CDLookupCancel(connections[conn_id], x0);
	pthread_mutex_unlock(parent_lock);
}

void call_CDLookupGetQueue(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling CDLookupGetQueue\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_CDLookupGetQueue(connections[conn_id], get_search_rows, print_CDLookupGetQueue, (void*)parent_lock);}

void call_CDLookupGetStatus(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling CDLookupGetStatus\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_CDLookupGetStatus(connections[conn_id], print_CDLookupGetStatus, (void*)parent_lock);}

void call_CancelRipping(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling CancelRipping\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_CancelRipping(connections[conn_id], x0, print_CancelRipping, (void*)parent_lock);}

void call_ChangeAlbumSubGenre(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];



	printf("Calling ChangeAlbumSubGenre\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("AlbumKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SubGenreKey: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_ChangeAlbumSubGenre(connections[conn_id], x0, x1, print_ChangeAlbumSubGenre, (void*)parent_lock);}

void call_ChangeCDDBSubGenreAssociation(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];

	printf("Calling ChangeCDDBSubGenreAssociation\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("GenreKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("NewSubGenreKey: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_ChangeCDDBSubGenreAssociation(connections[conn_id], x0, x1);
	pthread_mutex_unlock(parent_lock);
}

void call_ChangeNetworkAutoIP(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];
	char x2[30];
	char x3[30];
	int x4;



	printf("Calling ChangeNetworkAutoIP\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("DeviceID: ");
	scanf("%d", &x0);
	printf("AutoIpRange: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("DefaultGateway: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("DnsServer: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }
	printf("RestartDevice: ");
	scanf("%d", &x4);

	df_ChangeNetworkAutoIP(connections[conn_id], x0, x1, x2, x3, x4, print_ChangeNetworkAutoIP, (void*)parent_lock);}

void call_ChangeNetworkDhcp(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;



	printf("Calling ChangeNetworkDhcp\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("DeviceID: ");
	scanf("%d", &x0);
	printf("RestartDevice: ");
	scanf("%d", &x1);

	df_ChangeNetworkDhcp(connections[conn_id], x0, x1, print_ChangeNetworkDhcp, (void*)parent_lock);}

void call_ChangeNetworkMachineName(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling ChangeNetworkMachineName\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("MachineName: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_ChangeNetworkMachineName(connections[conn_id], x0, print_ChangeNetworkMachineName, (void*)parent_lock);}

void call_ChangeNetworkStatic(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];
	char x2[30];
	char x3[30];
	char x4[30];
	int x5;



	printf("Calling ChangeNetworkStatic\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("DeviceID: ");
	scanf("%d", &x0);
	printf("IpAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SubnetMask: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("DefaultGateway: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }
	printf("DnsServer: ");
	scanf("%s", x4);
	if (x4[0] == '-') { x4[0] = '\0'; }
	printf("RestartDevice: ");
	scanf("%d", &x5);

	df_ChangeNetworkStatic(connections[conn_id], x0, x1, x2, x3, x4, x5, print_ChangeNetworkStatic, (void*)parent_lock);}

void call_ChangeNetworkWorkgroup(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling ChangeNetworkWorkgroup\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Workgroup: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_ChangeNetworkWorkgroup(connections[conn_id], x0, print_ChangeNetworkWorkgroup, (void*)parent_lock);}

void call_ChangeSystemSerialNumber(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling ChangeSystemSerialNumber\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SerialNumber: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_ChangeSystemSerialNumber(connections[conn_id], x0, print_ChangeSystemSerialNumber, (void*)parent_lock);}

void call_ChangeTrackOrdinal(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	int x2;
	int x3;
	int x4;



	printf("Calling ChangeTrackOrdinal\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("TrackKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("PlaylistKey: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("Ordinal: ");
	scanf("%d", &x2);
	printf("NewPosition: ");
	scanf("%d", &x3);
	printf("ReorderPlaylist: ");
	scanf("%d", &x4);

	df_ChangeTrackOrdinal(connections[conn_id], x0, x1, x2, x3, x4, print_ChangeTrackOrdinal, (void*)parent_lock);}

void call_CheckCoverImage(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;
	int x2;
	int x3;
	char x4[30];
	char x5[30];



	printf("Calling CheckCoverImage\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("ImageSize: ");
	scanf("%d", &x1);
	printf("AddressType: ");
	scanf("%d", &x2);
	printf("Local: ");
	scanf("%d", &x3);
	printf("Protocol: ");
	scanf("%s", x4);
	if (x4[0] == '-') { x4[0] = '\0'; }
	printf("ImageFormat: ");
	scanf("%s", x5);
	if (x5[0] == '-') { x5[0] = '\0'; }

	df_CheckCoverImage(connections[conn_id], x0, x1, x2, x3, x4, x5, print_CheckCoverImage, (void*)parent_lock);}

void call_ClearAllPlaying(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling ClearAllPlaying\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_ClearAllPlaying(connections[conn_id]);
	pthread_mutex_unlock(parent_lock);
}

void call_ClearDownloadFolder(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling ClearDownloadFolder\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_ClearDownloadFolder(connections[conn_id], x0);
	pthread_mutex_unlock(parent_lock);
}

void call_ClearPlaylist(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling ClearPlaylist\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_ClearPlaylist(connections[conn_id], x0);
	pthread_mutex_unlock(parent_lock);
}

void call_CompactGenreOrdinals(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling CompactGenreOrdinals\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_CompactGenreOrdinals(connections[conn_id], print_CompactGenreOrdinals, (void*)parent_lock);}

void call_ComplexSearchCountAlbums(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling ComplexSearchCountAlbums\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SearchParameter: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_ComplexSearchCountAlbums(connections[conn_id], x0, print_ComplexSearchCountAlbums, (void*)parent_lock);}

void call_ComplexSearchCountArtists(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling ComplexSearchCountArtists\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SearchParameter: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_ComplexSearchCountArtists(connections[conn_id], x0, print_ComplexSearchCountArtists, (void*)parent_lock);}

void call_ComplexSearchCountContributors(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];



	printf("Calling ComplexSearchCountContributors\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Type: ");
	scanf("%d", &x0);
	printf("SearchParameter: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_ComplexSearchCountContributors(connections[conn_id], x0, x1, print_ComplexSearchCountContributors, (void*)parent_lock);}

void call_ComplexSearchCountTracks(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling ComplexSearchCountTracks\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SearchParameter: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_ComplexSearchCountTracks(connections[conn_id], x0, print_ComplexSearchCountTracks, (void*)parent_lock);}

void call_ComplexSearchGetAlbums(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];

	printf("Calling ComplexSearchGetAlbums\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SearchParameter: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_ComplexSearchGetAlbums(connections[conn_id], x0, x1, x2, get_search_rows, print_ComplexSearchGetAlbums, (void*)parent_lock);}

void call_ComplexSearchGetArtists(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling ComplexSearchGetArtists\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SearchParameter: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_ComplexSearchGetArtists(connections[conn_id], x0, get_search_rows, print_ComplexSearchGetArtists, (void*)parent_lock);}

void call_ComplexSearchGetContributors(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];

	printf("Calling ComplexSearchGetContributors\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Type: ");
	scanf("%d", &x0);
	printf("SearchParameter: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_ComplexSearchGetContributors(connections[conn_id], x0, x1, get_search_rows, print_ComplexSearchGetContributors, (void*)parent_lock);}

void call_ComplexSearchGetTracks(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling ComplexSearchGetTracks\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SearchParameter: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_ComplexSearchGetTracks(connections[conn_id], x0, get_search_rows, print_ComplexSearchGetTracks, (void*)parent_lock);}

void call_CountAlbums(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling CountAlbums\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_CountAlbums(connections[conn_id], print_CountAlbums, (void*)parent_lock);}

void call_CountAlbumsForArtist(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling CountAlbumsForArtist\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_CountAlbumsForArtist(connections[conn_id], x0, print_CountAlbumsForArtist, (void*)parent_lock);}

void call_CountAlbumsForArtistForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];



	printf("Calling CountAlbumsForArtistForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("DeviceAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_CountAlbumsForArtistForDevice(connections[conn_id], x0, x1, print_CountAlbumsForArtistForDevice, (void*)parent_lock);}

void call_CountAlbumsForArtistForServer(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling CountAlbumsForArtistForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_CountAlbumsForArtistForServer(connections[conn_id], x0, print_CountAlbumsForArtistForServer, (void*)parent_lock);}

void call_CountAlbumsForArtistForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];



	printf("Calling CountAlbumsForArtistForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("ShareAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_CountAlbumsForArtistForShare(connections[conn_id], x0, x1, print_CountAlbumsForArtistForShare, (void*)parent_lock);}

void call_CountAlbumsForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling CountAlbumsForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_CountAlbumsForDevice(connections[conn_id], x0, print_CountAlbumsForDevice, (void*)parent_lock);}

void call_CountAlbumsForServer(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling CountAlbumsForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_CountAlbumsForServer(connections[conn_id], print_CountAlbumsForServer, (void*)parent_lock);}

void call_CountAlbumsForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling CountAlbumsForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_CountAlbumsForShare(connections[conn_id], x0, print_CountAlbumsForShare, (void*)parent_lock);}

void call_CountArtists(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling CountArtists\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Allocated: ");
	scanf("%d", &x0);

	df_CountArtists(connections[conn_id], x0, print_CountArtists, (void*)parent_lock);}

void call_CountArtistsForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling CountArtistsForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_CountArtistsForDevice(connections[conn_id], x0, print_CountArtistsForDevice, (void*)parent_lock);}

void call_CountArtistsForServer(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling CountArtistsForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_CountArtistsForServer(connections[conn_id], print_CountArtistsForServer, (void*)parent_lock);}

void call_CountArtistsForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling CountArtistsForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_CountArtistsForShare(connections[conn_id], x0, print_CountArtistsForShare, (void*)parent_lock);}

void call_CountDevices(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling CountDevices\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("ActiveOnly: ");
	scanf("%d", &x0);

	df_CountDevices(connections[conn_id], x0, print_CountDevices, (void*)parent_lock);}

void call_CountGenres(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling CountGenres\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Allocated: ");
	scanf("%d", &x0);

	df_CountGenres(connections[conn_id], x0, print_CountGenres, (void*)parent_lock);}

void call_CountPlaylistsForSubGenre(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling CountPlaylistsForSubGenre\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_CountPlaylistsForSubGenre(connections[conn_id], x0, print_CountPlaylistsForSubGenre, (void*)parent_lock);}

void call_CountPlaylistsForSubGenreForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];



	printf("Calling CountPlaylistsForSubGenreForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("DeviceAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_CountPlaylistsForSubGenreForDevice(connections[conn_id], x0, x1, print_CountPlaylistsForSubGenreForDevice, (void*)parent_lock);}

void call_CountPlaylistsForSubGenreForServer(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling CountPlaylistsForSubGenreForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_CountPlaylistsForSubGenreForServer(connections[conn_id], x0, print_CountPlaylistsForSubGenreForServer, (void*)parent_lock);}

void call_CountPlaylistsForSubGenreForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];



	printf("Calling CountPlaylistsForSubGenreForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("ShareAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_CountPlaylistsForSubGenreForShare(connections[conn_id], x0, x1, print_CountPlaylistsForSubGenreForShare, (void*)parent_lock);}

void call_CountShares(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling CountShares\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("AvailableOnly: ");
	scanf("%d", &x0);

	df_CountShares(connections[conn_id], x0, print_CountShares, (void*)parent_lock);}

void call_CountSubGenresForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling CountSubGenresForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_CountSubGenresForDevice(connections[conn_id], x0, print_CountSubGenresForDevice, (void*)parent_lock);}

void call_CountSubGenresForGenre(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;



	printf("Calling CountSubGenresForGenre\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Allocated: ");
	scanf("%d", &x1);

	df_CountSubGenresForGenre(connections[conn_id], x0, x1, print_CountSubGenresForGenre, (void*)parent_lock);}

void call_CountSubGenresForServer(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;



	printf("Calling CountSubGenresForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Allocated: ");
	scanf("%d", &x0);
	printf("UserDefined: ");
	scanf("%d", &x1);

	df_CountSubGenresForServer(connections[conn_id], x0, x1, print_CountSubGenresForServer, (void*)parent_lock);}

void call_CountSubGenresForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling CountSubGenresForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_CountSubGenresForShare(connections[conn_id], x0, print_CountSubGenresForShare, (void*)parent_lock);}

void call_CountTracksAll(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling CountTracksAll\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_CountTracksAll(connections[conn_id], print_CountTracksAll, (void*)parent_lock);}

void call_CountTracksForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling CountTracksForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_CountTracksForDevice(connections[conn_id], x0, print_CountTracksForDevice, (void*)parent_lock);}

void call_CountTracksForPlaylist(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling CountTracksForPlaylist\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_CountTracksForPlaylist(connections[conn_id], x0, print_CountTracksForPlaylist, (void*)parent_lock);}

void call_CountTracksForServer(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling CountTracksForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_CountTracksForServer(connections[conn_id], print_CountTracksForServer, (void*)parent_lock);}

void call_CountTracksForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling CountTracksForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_CountTracksForShare(connections[conn_id], x0, print_CountTracksForShare, (void*)parent_lock);}

void call_CountUserPlaylists(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling CountUserPlaylists\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_CountUserPlaylists(connections[conn_id], print_CountUserPlaylists, (void*)parent_lock);}

void call_CountUserPlaylistsForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling CountUserPlaylistsForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_CountUserPlaylistsForDevice(connections[conn_id], x0, print_CountUserPlaylistsForDevice, (void*)parent_lock);}

void call_CountUserPlaylistsForServer(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling CountUserPlaylistsForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_CountUserPlaylistsForServer(connections[conn_id], print_CountUserPlaylistsForServer, (void*)parent_lock);}

void call_CountUserPlaylistsForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling CountUserPlaylistsForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_CountUserPlaylistsForShare(connections[conn_id], x0, print_CountUserPlaylistsForShare, (void*)parent_lock);}

void call_CreatePlaylist(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];



	printf("Calling CreatePlaylist\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Name: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("TrackKey: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_CreatePlaylist(connections[conn_id], x0, x1, print_CreatePlaylist, (void*)parent_lock);}

void call_CreateRandomPlaylist(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];
	char x2[30];
	char x3[30];
	char x4[30];
	int x5;
	char x6[30];



	printf("Calling CreateRandomPlaylist\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Genre: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SubGenre: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("Artists: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }
	printf("Albums: ");
	scanf("%s", x4);
	if (x4[0] == '-') { x4[0] = '\0'; }
	printf("MaxTracks: ");
	scanf("%d", &x5);
	printf("Tracks: ");
	scanf("%s", x6);
	if (x6[0] == '-') { x6[0] = '\0'; }

	df_CreateRandomPlaylist(connections[conn_id], x0, x1, x2, x3, x4, x5, x6, print_CreateRandomPlaylist, (void*)parent_lock);}

void call_CreateRandomPlaylistEx(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	int x2;
	char x3[30];
	char x4[30];
	char x5[30];
	char x6[30];
	char x7[30];



	printf("Calling CreateRandomPlaylistEx\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Replace: ");
	scanf("%d", &x1);
	printf("PlayScope: ");
	scanf("%d", &x2);
	printf("ScopeKey: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }
	printf("SubGenre: ");
	scanf("%s", x4);
	if (x4[0] == '-') { x4[0] = '\0'; }
	printf("Artists: ");
	scanf("%s", x5);
	if (x5[0] == '-') { x5[0] = '\0'; }
	printf("Albums: ");
	scanf("%s", x6);
	if (x6[0] == '-') { x6[0] = '\0'; }
	printf("Tracks: ");
	scanf("%s", x7);
	if (x7[0] == '-') { x7[0] = '\0'; }

	df_CreateRandomPlaylistEx(connections[conn_id], x0, x1, x2, x3, x4, x5, x6, x7, print_CreateRandomPlaylistEx, (void*)parent_lock);}

void call_DeleteAlbum(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling DeleteAlbum\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("AlbumKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_DeleteAlbum(connections[conn_id], x0, print_DeleteAlbum, (void*)parent_lock);}

void call_DeleteBackupJob(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling DeleteBackupJob\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_DeleteBackupJob(connections[conn_id], x0, print_DeleteBackupJob, (void*)parent_lock);}

void call_DeleteDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling DeleteDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Key: ");
	scanf("%d", &x0);

	df_DeleteDevice(connections[conn_id], x0, print_DeleteDevice, (void*)parent_lock);}

void call_DeleteDrive(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling DeleteDrive\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("DriveKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_DeleteDrive(connections[conn_id], x0, print_DeleteDrive, (void*)parent_lock);}

void call_DeleteGenre(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling DeleteGenre\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("GenreKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_DeleteGenre(connections[conn_id], x0, print_DeleteGenre, (void*)parent_lock);}

void call_DeleteLinkedRoom(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling DeleteLinkedRoom\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_DeleteLinkedRoom(connections[conn_id], x0, print_DeleteLinkedRoom, (void*)parent_lock);}

void call_DeleteOutputChannel(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];
	int x2;



	printf("Calling DeleteOutputChannel\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("HostName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("ChannelNumber: ");
	scanf("%d", &x2);

	df_DeleteOutputChannel(connections[conn_id], x0, x1, x2, print_DeleteOutputChannel, (void*)parent_lock);}

void call_DeleteRoom(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling DeleteRoom\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_DeleteRoom(connections[conn_id], x0, print_DeleteRoom, (void*)parent_lock);}

void call_DeleteSubGenre(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling DeleteSubGenre\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SubGenreKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_DeleteSubGenre(connections[conn_id], x0, print_DeleteSubGenre, (void*)parent_lock);}

void call_DeleteTrack(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	int x2;



	printf("Calling DeleteTrack\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("TrackKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("PlaylistKey: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("Ordinal: ");
	scanf("%d", &x2);

	df_DeleteTrack(connections[conn_id], x0, x1, x2, print_DeleteTrack, (void*)parent_lock);}

void call_DemoteMusicStoreToShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;



	printf("Calling DemoteMusicStoreToShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("MusicStoreKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Deactivate: ");
	scanf("%d", &x1);

	df_DemoteMusicStoreToShare(connections[conn_id], x0, x1, print_DemoteMusicStoreToShare, (void*)parent_lock);}

void call_DeviceChecksum(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling DeviceChecksum\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_DeviceChecksum(connections[conn_id], print_DeviceChecksum, (void*)parent_lock);}

void call_DisableField(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];

	printf("Calling DisableField\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("FormatList: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("FieldName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_DisableField(connections[conn_id], x0, x1);
	pthread_mutex_unlock(parent_lock);
}

void call_DisconnectDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;



	printf("Calling DisconnectDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Key: ");
	scanf("%d", &x0);
	printf("ClearPlaying: ");
	scanf("%d", &x1);

	df_DisconnectDevice(connections[conn_id], x0, x1, print_DisconnectDevice, (void*)parent_lock);}

void call_EjectCD(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling EjectCD\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_EjectCD(connections[conn_id], x0);
	pthread_mutex_unlock(parent_lock);
}

void call_EmptyRecycleBin(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling EmptyRecycleBin\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_EmptyRecycleBin(connections[conn_id]);
	pthread_mutex_unlock(parent_lock);
}

void call_EmptyRipShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling EmptyRipShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_EmptyRipShare(connections[conn_id], x0);
	pthread_mutex_unlock(parent_lock);
}

void call_EnableField(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];

	printf("Calling EnableField\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("FormatList: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("FieldName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_EnableField(connections[conn_id], x0, x1);
	pthread_mutex_unlock(parent_lock);
}

void call_ExternalStorageCancelScan(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling ExternalStorageCancelScan\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("StorageKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_ExternalStorageCancelScan(connections[conn_id], x0, print_ExternalStorageCancelScan, (void*)parent_lock);}

void call_FastForward(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling FastForward\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_FastForward(connections[conn_id], x0);
	pthread_mutex_unlock(parent_lock);
}

void call_FastRewind(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling FastRewind\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_FastRewind(connections[conn_id], x0);
	pthread_mutex_unlock(parent_lock);
}

void call_FindAllRooms(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling FindAllRooms\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("TimeoutPerHost: ");
	scanf("%d", &x0);

	df_FindAllRooms(connections[conn_id], x0, print_FindAllRooms, (void*)parent_lock);}

void call_FindNewRooms(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling FindNewRooms\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("TimeoutPerHost: ");
	scanf("%d", &x0);

	df_FindNewRooms(connections[conn_id], x0, print_FindNewRooms, (void*)parent_lock);}

void call_ForceDBRebuild(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling ForceDBRebuild\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_ForceDBRebuild(connections[conn_id]);
	pthread_mutex_unlock(parent_lock);
}

void call_ForceGenrePlaylistBackup(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling ForceGenrePlaylistBackup\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_ForceGenrePlaylistBackup(connections[conn_id], print_ForceGenrePlaylistBackup, (void*)parent_lock);}

void call_ForceGenrePlaylistRestore(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling ForceGenrePlaylistRestore\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_ForceGenrePlaylistRestore(connections[conn_id], print_ForceGenrePlaylistRestore, (void*)parent_lock);}

void call_ForceHostUpgrade(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling ForceHostUpgrade\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_ForceHostUpgrade(connections[conn_id], x0);
	pthread_mutex_unlock(parent_lock);
}

void call_GetAdvancedStatus(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling GetAdvancedStatus\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_GetAdvancedStatus(connections[conn_id], get_search_rows, print_GetAdvancedStatus, (void*)parent_lock);}

void call_GetAlbumArtist(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling GetAlbumArtist\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetAlbumArtist(connections[conn_id], x0, print_GetAlbumArtist, (void*)parent_lock);}

void call_GetAlbumDetails(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetAlbumDetails\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetAlbumDetails(connections[conn_id], x0, get_search_rows, print_GetAlbumDetails, (void*)parent_lock);}

void call_GetAlbums(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];

	printf("Calling GetAlbums\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SortColumn: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_GetAlbums(connections[conn_id], x0, x1, get_search_rows, print_GetAlbums, (void*)parent_lock);}

void call_GetAlbumsForArtists(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];

	printf("Calling GetAlbumsForArtists\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetAlbumsForArtists(connections[conn_id], x0, x1, x2, get_search_rows, print_GetAlbumsForArtists, (void*)parent_lock);}

void call_GetAlbumsForArtistsForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];
	char x3[30];

	printf("Calling GetAlbumsForArtistsForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("DeviceAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }

	df_GetAlbumsForArtistsForDevice(connections[conn_id], x0, x1, x2, x3, get_search_rows, print_GetAlbumsForArtistsForDevice, (void*)parent_lock);}

void call_GetAlbumsForArtistsForServer(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];

	printf("Calling GetAlbumsForArtistsForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetAlbumsForArtistsForServer(connections[conn_id], x0, x1, x2, get_search_rows, print_GetAlbumsForArtistsForServer, (void*)parent_lock);}

void call_GetAlbumsForArtistsForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];
	char x3[30];

	printf("Calling GetAlbumsForArtistsForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("ShareAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }

	df_GetAlbumsForArtistsForShare(connections[conn_id], x0, x1, x2, x3, get_search_rows, print_GetAlbumsForArtistsForShare, (void*)parent_lock);}

void call_GetAlbumsForArtistsInGenre(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];
	char x3[30];

	printf("Calling GetAlbumsForArtistsInGenre\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("GenreAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }

	df_GetAlbumsForArtistsInGenre(connections[conn_id], x0, x1, x2, x3, get_search_rows, print_GetAlbumsForArtistsInGenre, (void*)parent_lock);}

void call_GetAlbumsForArtistsInSubGenre(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];
	char x3[30];

	printf("Calling GetAlbumsForArtistsInSubGenre\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SubGenreAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }

	df_GetAlbumsForArtistsInSubGenre(connections[conn_id], x0, x1, x2, x3, get_search_rows, print_GetAlbumsForArtistsInSubGenre, (void*)parent_lock);}

void call_GetAlbumsForDeletion(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];

	printf("Calling GetAlbumsForDeletion\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SortColumn: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_GetAlbumsForDeletion(connections[conn_id], x0, x1, get_search_rows, print_GetAlbumsForDeletion, (void*)parent_lock);}

void call_GetAlbumsForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];

	printf("Calling GetAlbumsForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetAlbumsForDevice(connections[conn_id], x0, x1, x2, get_search_rows, print_GetAlbumsForDevice, (void*)parent_lock);}

void call_GetAlbumsForPlaylist(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];

	printf("Calling GetAlbumsForPlaylist\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetAlbumsForPlaylist(connections[conn_id], x0, x1, x2, get_search_rows, print_GetAlbumsForPlaylist, (void*)parent_lock);}

void call_GetAlbumsForServer(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];

	printf("Calling GetAlbumsForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SortColumn: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_GetAlbumsForServer(connections[conn_id], x0, x1, get_search_rows, print_GetAlbumsForServer, (void*)parent_lock);}

void call_GetAlbumsForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];

	printf("Calling GetAlbumsForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetAlbumsForShare(connections[conn_id], x0, x1, x2, get_search_rows, print_GetAlbumsForShare, (void*)parent_lock);}

void call_GetAlbumsForStore(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;
	char x2[30];
	char x3[30];

	printf("Calling GetAlbumsForStore\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("StoreKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("IncludeDeleted: ");
	scanf("%d", &x1);
	printf("SortColumn: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }

	df_GetAlbumsForStore(connections[conn_id], x0, x1, x2, x3, get_search_rows, print_GetAlbumsForStore, (void*)parent_lock);}

void call_GetAlbumsOtherInfo(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];
	int x3;
	int x4;

	printf("Calling GetAlbumsOtherInfo\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("RemoteImagePath: ");
	scanf("%d", &x3);
	printf("ImageSize: ");
	scanf("%d", &x4);

	df_GetAlbumsOtherInfo(connections[conn_id], x0, x1, x2, x3, x4, get_search_rows, print_GetAlbumsOtherInfo, (void*)parent_lock);}

void call_GetAlbumsOtherInfoAll(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	int x2;
	int x3;

	printf("Calling GetAlbumsOtherInfoAll\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SortColumn: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("RemoteImagePath: ");
	scanf("%d", &x2);
	printf("ImageSize: ");
	scanf("%d", &x3);

	df_GetAlbumsOtherInfoAll(connections[conn_id], x0, x1, x2, x3, get_search_rows, print_GetAlbumsOtherInfoAll, (void*)parent_lock);}

void call_GetAlbumsOtherInfoForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];
	int x3;
	int x4;

	printf("Calling GetAlbumsOtherInfoForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("RemoteImagePath: ");
	scanf("%d", &x3);
	printf("ImageSize: ");
	scanf("%d", &x4);

	df_GetAlbumsOtherInfoForDevice(connections[conn_id], x0, x1, x2, x3, x4, get_search_rows, print_GetAlbumsOtherInfoForDevice, (void*)parent_lock);}

void call_GetAlbumsOtherInfoForServer(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	int x2;
	int x3;

	printf("Calling GetAlbumsOtherInfoForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SortColumn: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("RemoteImagePath: ");
	scanf("%d", &x2);
	printf("ImageSize: ");
	scanf("%d", &x3);

	df_GetAlbumsOtherInfoForServer(connections[conn_id], x0, x1, x2, x3, get_search_rows, print_GetAlbumsOtherInfoForServer, (void*)parent_lock);}

void call_GetAlbumsOtherInfoForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];
	int x3;
	int x4;

	printf("Calling GetAlbumsOtherInfoForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("RemoteImagePath: ");
	scanf("%d", &x3);
	printf("ImageSize: ");
	scanf("%d", &x4);

	df_GetAlbumsOtherInfoForShare(connections[conn_id], x0, x1, x2, x3, x4, get_search_rows, print_GetAlbumsOtherInfoForShare, (void*)parent_lock);}

void call_GetAlbumsSearchAlbumArtist(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];
	int x3;

	printf("Calling GetAlbumsSearchAlbumArtist\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SearchString: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("SearchType: ");
	scanf("%d", &x3);

	df_GetAlbumsSearchAlbumArtist(connections[conn_id], x0, x1, x2, x3, get_search_rows, print_GetAlbumsSearchAlbumArtist, (void*)parent_lock);}

void call_GetAlbumsWithAlbumLookupMessages(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling GetAlbumsWithAlbumLookupMessages\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_GetAlbumsWithAlbumLookupMessages(connections[conn_id], get_search_rows, print_GetAlbumsWithAlbumLookupMessages, (void*)parent_lock);}

void call_GetAlertDetails(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetAlertDetails\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetAlertDetails(connections[conn_id], x0, get_search_rows, print_GetAlertDetails, (void*)parent_lock);}

void call_GetArtistDetails(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetArtistDetails\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetArtistDetails(connections[conn_id], x0, get_search_rows, print_GetArtistDetails, (void*)parent_lock);}

void call_GetArtists(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling GetArtists\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Allocated: ");
	scanf("%d", &x0);

	df_GetArtists(connections[conn_id], x0, get_search_rows, print_GetArtists, (void*)parent_lock);}

void call_GetArtistsForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetArtistsForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetArtistsForDevice(connections[conn_id], x0, get_search_rows, print_GetArtistsForDevice, (void*)parent_lock);}

void call_GetArtistsForServer(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling GetArtistsForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_GetArtistsForServer(connections[conn_id], get_search_rows, print_GetArtistsForServer, (void*)parent_lock);}

void call_GetArtistsForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetArtistsForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetArtistsForShare(connections[conn_id], x0, get_search_rows, print_GetArtistsForShare, (void*)parent_lock);}

void call_GetArtistsInGenre(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetArtistsInGenre\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetArtistsInGenre(connections[conn_id], x0, get_search_rows, print_GetArtistsInGenre, (void*)parent_lock);}

void call_GetArtistsInSubGenre(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetArtistsInSubGenre\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetArtistsInSubGenre(connections[conn_id], x0, get_search_rows, print_GetArtistsInSubGenre, (void*)parent_lock);}

void call_GetAvailableValues(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetAvailableValues\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetAvailableValues(connections[conn_id], x0, get_search_rows, print_GetAvailableValues, (void*)parent_lock);}

void call_GetBackupJobDetail(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetBackupJobDetail\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetBackupJobDetail(connections[conn_id], x0, get_search_rows, print_GetBackupJobDetail, (void*)parent_lock);}

void call_GetBackupJobs(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling GetBackupJobs\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_GetBackupJobs(connections[conn_id], get_search_rows, print_GetBackupJobs, (void*)parent_lock);}

void call_GetBackupLogDetail(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetBackupLogDetail\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetBackupLogDetail(connections[conn_id], x0, get_search_rows, print_GetBackupLogDetail, (void*)parent_lock);}

void call_GetBackupLogs(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetBackupLogs\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetBackupLogs(connections[conn_id], x0, get_search_rows, print_GetBackupLogs, (void*)parent_lock);}

void call_GetBackupStatus(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling GetBackupStatus\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_GetBackupStatus(connections[conn_id], print_GetBackupStatus, (void*)parent_lock);}

void call_GetCDDBGenres(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling GetCDDBGenres\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_GetCDDBGenres(connections[conn_id], get_search_rows, print_GetCDDBGenres, (void*)parent_lock);}

void call_GetComponentVersions(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling GetComponentVersions\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetComponentVersions(connections[conn_id], x0, get_search_rows, print_GetComponentVersions, (void*)parent_lock);}

void call_GetCount(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling GetCount\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_GetCount(connections[conn_id], print_GetCount, (void*)parent_lock);}

void call_GetCurOp(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling GetCurOp\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_GetCurOp(connections[conn_id], print_GetCurOp, (void*)parent_lock);}

void call_GetCurrentPlayList(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling GetCurrentPlayList\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetCurrentPlayList(connections[conn_id], x0, get_search_rows, print_GetCurrentPlayList, (void*)parent_lock);}

void call_GetCurrentPlaylistEx(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	int x2;

	printf("Calling GetCurrentPlaylistEx\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("RemoteImagePath: ");
	scanf("%d", &x1);
	printf("ImageSize: ");
	scanf("%d", &x2);

	df_GetCurrentPlaylistEx(connections[conn_id], x0, x1, x2, get_search_rows, print_GetCurrentPlaylistEx, (void*)parent_lock);}

void call_GetDeviceDetails(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetDeviceDetails\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("DeviceAddress: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetDeviceDetails(connections[conn_id], x0, get_search_rows, print_GetDeviceDetails, (void*)parent_lock);}

void call_GetDevices(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling GetDevices\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("ActiveOnly: ");
	scanf("%d", &x0);

	df_GetDevices(connections[conn_id], x0, get_search_rows, print_GetDevices, (void*)parent_lock);}

void call_GetDriveDetail(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling GetDriveDetail\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("DriveKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetDriveDetail(connections[conn_id], x0, print_GetDriveDetail, (void*)parent_lock);}

void call_GetEncodingQueue(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling GetEncodingQueue\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetEncodingQueue(connections[conn_id], x0, get_search_rows, print_GetEncodingQueue, (void*)parent_lock);}

void call_GetEncodingStatus(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling GetEncodingStatus\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetEncodingStatus(connections[conn_id], x0, get_search_rows, print_GetEncodingStatus, (void*)parent_lock);}

void call_GetExtAlbumCredits(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetExtAlbumCredits\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetExtAlbumCredits(connections[conn_id], x0, get_search_rows, print_GetExtAlbumCredits, (void*)parent_lock);}

void call_GetExtAlbumsByContributor(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;
	char x2[30];
	char x3[30];

	printf("Calling GetExtAlbumsByContributor\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Type: ");
	scanf("%d", &x1);
	printf("SortColumn: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }

	df_GetExtAlbumsByContributor(connections[conn_id], x0, x1, x2, x3, get_search_rows, print_GetExtAlbumsByContributor, (void*)parent_lock);}

void call_GetExtAlbumsByContributorForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	int x2;
	char x3[30];
	char x4[30];

	printf("Calling GetExtAlbumsByContributorForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("DeviceAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("Type: ");
	scanf("%d", &x2);
	printf("SortColumn: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x4);
	if (x4[0] == '-') { x4[0] = '\0'; }

	df_GetExtAlbumsByContributorForDevice(connections[conn_id], x0, x1, x2, x3, x4, get_search_rows, print_GetExtAlbumsByContributorForDevice, (void*)parent_lock);}

void call_GetExtAlbumsByContributorForServer(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;
	char x2[30];
	char x3[30];

	printf("Calling GetExtAlbumsByContributorForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Type: ");
	scanf("%d", &x1);
	printf("SortColumn: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }

	df_GetExtAlbumsByContributorForServer(connections[conn_id], x0, x1, x2, x3, get_search_rows, print_GetExtAlbumsByContributorForServer, (void*)parent_lock);}

void call_GetExtAlbumsByContributorForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	int x2;
	char x3[30];
	char x4[30];

	printf("Calling GetExtAlbumsByContributorForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("ShareAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("Type: ");
	scanf("%d", &x2);
	printf("SortColumn: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x4);
	if (x4[0] == '-') { x4[0] = '\0'; }

	df_GetExtAlbumsByContributorForShare(connections[conn_id], x0, x1, x2, x3, x4, get_search_rows, print_GetExtAlbumsByContributorForShare, (void*)parent_lock);}

void call_GetExtAlbumsByCredit(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];

	printf("Calling GetExtAlbumsByCredit\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetExtAlbumsByCredit(connections[conn_id], x0, x1, x2, get_search_rows, print_GetExtAlbumsByCredit, (void*)parent_lock);}

void call_GetExtAlbumsByWork(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];

	printf("Calling GetExtAlbumsByWork\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Work: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetExtAlbumsByWork(connections[conn_id], x0, x1, x2, get_search_rows, print_GetExtAlbumsByWork, (void*)parent_lock);}

void call_GetExtAlbumsInfo(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetExtAlbumsInfo\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetExtAlbumsInfo(connections[conn_id], x0, get_search_rows, print_GetExtAlbumsInfo, (void*)parent_lock);}

void call_GetExtAlbumsSearchPeople(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;
	char x2[30];
	char x3[30];

	printf("Calling GetExtAlbumsSearchPeople\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SearchString: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SearchType: ");
	scanf("%d", &x1);
	printf("SortColumn: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }

	df_GetExtAlbumsSearchPeople(connections[conn_id], x0, x1, x2, x3, get_search_rows, print_GetExtAlbumsSearchPeople, (void*)parent_lock);}

void call_GetExtContributorDetails(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;

	printf("Calling GetExtContributorDetails\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Type: ");
	scanf("%d", &x1);

	df_GetExtContributorDetails(connections[conn_id], x0, x1, get_search_rows, print_GetExtContributorDetails, (void*)parent_lock);}

void call_GetExtContributors(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling GetExtContributors\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Type: ");
	scanf("%d", &x0);

	df_GetExtContributors(connections[conn_id], x0, get_search_rows, print_GetExtContributors, (void*)parent_lock);}

void call_GetExtContributorsForAlbum(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;

	printf("Calling GetExtContributorsForAlbum\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Type: ");
	scanf("%d", &x1);

	df_GetExtContributorsForAlbum(connections[conn_id], x0, x1, get_search_rows, print_GetExtContributorsForAlbum, (void*)parent_lock);}

void call_GetExtContributorsForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;

	printf("Calling GetExtContributorsForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Type: ");
	scanf("%d", &x1);

	df_GetExtContributorsForDevice(connections[conn_id], x0, x1, get_search_rows, print_GetExtContributorsForDevice, (void*)parent_lock);}

void call_GetExtContributorsForServer(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling GetExtContributorsForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Type: ");
	scanf("%d", &x0);

	df_GetExtContributorsForServer(connections[conn_id], x0, get_search_rows, print_GetExtContributorsForServer, (void*)parent_lock);}

void call_GetExtContributorsForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;

	printf("Calling GetExtContributorsForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Type: ");
	scanf("%d", &x1);

	df_GetExtContributorsForShare(connections[conn_id], x0, x1, get_search_rows, print_GetExtContributorsForShare, (void*)parent_lock);}

void call_GetExtCountAlbumsByContributor(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;



	printf("Calling GetExtCountAlbumsByContributor\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Type: ");
	scanf("%d", &x1);

	df_GetExtCountAlbumsByContributor(connections[conn_id], x0, x1, print_GetExtCountAlbumsByContributor, (void*)parent_lock);}

void call_GetExtCountAlbumsByContributorForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	int x2;



	printf("Calling GetExtCountAlbumsByContributorForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("DeviceAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("Type: ");
	scanf("%d", &x2);

	df_GetExtCountAlbumsByContributorForDevice(connections[conn_id], x0, x1, x2, print_GetExtCountAlbumsByContributorForDevice, (void*)parent_lock);}

void call_GetExtCountAlbumsByContributorForServer(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;



	printf("Calling GetExtCountAlbumsByContributorForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Type: ");
	scanf("%d", &x1);

	df_GetExtCountAlbumsByContributorForServer(connections[conn_id], x0, x1, print_GetExtCountAlbumsByContributorForServer, (void*)parent_lock);}

void call_GetExtCountAlbumsByContributorForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	int x2;



	printf("Calling GetExtCountAlbumsByContributorForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("ShareAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("Type: ");
	scanf("%d", &x2);

	df_GetExtCountAlbumsByContributorForShare(connections[conn_id], x0, x1, x2, print_GetExtCountAlbumsByContributorForShare, (void*)parent_lock);}

void call_GetExtCountContributors(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling GetExtCountContributors\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Type: ");
	scanf("%d", &x0);

	df_GetExtCountContributors(connections[conn_id], x0, print_GetExtCountContributors, (void*)parent_lock);}

void call_GetExtCountContributorsForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;



	printf("Calling GetExtCountContributorsForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Type: ");
	scanf("%d", &x1);

	df_GetExtCountContributorsForDevice(connections[conn_id], x0, x1, print_GetExtCountContributorsForDevice, (void*)parent_lock);}

void call_GetExtCountContributorsForServer(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling GetExtCountContributorsForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Type: ");
	scanf("%d", &x0);

	df_GetExtCountContributorsForServer(connections[conn_id], x0, print_GetExtCountContributorsForServer, (void*)parent_lock);}

void call_GetExtCountContributorsForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;



	printf("Calling GetExtCountContributorsForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Type: ");
	scanf("%d", &x1);

	df_GetExtCountContributorsForShare(connections[conn_id], x0, x1, print_GetExtCountContributorsForShare, (void*)parent_lock);}

void call_GetExtTrackContributors(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;

	printf("Calling GetExtTrackContributors\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Type: ");
	scanf("%d", &x1);

	df_GetExtTrackContributors(connections[conn_id], x0, x1, get_search_rows, print_GetExtTrackContributors, (void*)parent_lock);}

void call_GetExtTracksByContributor(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;
	char x2[30];

	printf("Calling GetExtTracksByContributor\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Type: ");
	scanf("%d", &x1);
	printf("Album: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetExtTracksByContributor(connections[conn_id], x0, x1, x2, get_search_rows, print_GetExtTracksByContributor, (void*)parent_lock);}

void call_GetExtTracksByContributorForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	int x2;
	char x3[30];

	printf("Calling GetExtTracksByContributorForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("DeviceAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("Type: ");
	scanf("%d", &x2);
	printf("Album: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }

	df_GetExtTracksByContributorForDevice(connections[conn_id], x0, x1, x2, x3, get_search_rows, print_GetExtTracksByContributorForDevice, (void*)parent_lock);}

void call_GetExtTracksByContributorForServer(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;
	char x2[30];

	printf("Calling GetExtTracksByContributorForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Type: ");
	scanf("%d", &x1);
	printf("Album: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetExtTracksByContributorForServer(connections[conn_id], x0, x1, x2, get_search_rows, print_GetExtTracksByContributorForServer, (void*)parent_lock);}

void call_GetExtTracksByContributorForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	int x2;
	char x3[30];

	printf("Calling GetExtTracksByContributorForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("ShareAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("Type: ");
	scanf("%d", &x2);
	printf("Album: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }

	df_GetExtTracksByContributorForShare(connections[conn_id], x0, x1, x2, x3, get_search_rows, print_GetExtTracksByContributorForShare, (void*)parent_lock);}

void call_GetExtTracksByWork(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetExtTracksByWork\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Work: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetExtTracksByWork(connections[conn_id], x0, get_search_rows, print_GetExtTracksByWork, (void*)parent_lock);}

void call_GetExtTracksInfo(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetExtTracksInfo\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetExtTracksInfo(connections[conn_id], x0, get_search_rows, print_GetExtTracksInfo, (void*)parent_lock);}

void call_GetExtWorks(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling GetExtWorks\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_GetExtWorks(connections[conn_id], get_search_rows, print_GetExtWorks, (void*)parent_lock);}

void call_GetExternalStorageDetail(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling GetExternalStorageDetail\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("StorageKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetExternalStorageDetail(connections[conn_id], x0, print_GetExternalStorageDetail, (void*)parent_lock);}

void call_GetExternalStorages(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling GetExternalStorages\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("AvailableOnly: ");
	scanf("%d", &x0);

	df_GetExternalStorages(connections[conn_id], x0, get_search_rows, print_GetExternalStorages, (void*)parent_lock);}

void call_GetFileSystemDriveDetail(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling GetFileSystemDriveDetail\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("DriveLetter: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetFileSystemDriveDetail(connections[conn_id], x0, print_GetFileSystemDriveDetail, (void*)parent_lock);}

void call_GetGenreDetail(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling GetGenreDetail\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("GenreKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetGenreDetail(connections[conn_id], x0, print_GetGenreDetail, (void*)parent_lock);}

void call_GetGenres(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];
	char x2[30];

	printf("Calling GetGenres\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Allocated: ");
	scanf("%d", &x0);
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetGenres(connections[conn_id], x0, x1, x2, get_search_rows, print_GetGenres, (void*)parent_lock);}

void call_GetGenresSubGenres(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];
	char x2[30];

	printf("Calling GetGenresSubGenres\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Allocated: ");
	scanf("%d", &x0);
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetGenresSubGenres(connections[conn_id], x0, x1, x2, get_search_rows, print_GetGenresSubGenres, (void*)parent_lock);}

void call_GetHostDetails(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling GetHostDetails\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_GetHostDetails(connections[conn_id], print_GetHostDetails, (void*)parent_lock);}

void call_GetLastError(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling GetLastError\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_GetLastError(connections[conn_id], print_GetLastError, (void*)parent_lock);}

void call_GetLatestPlayedAlbums(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];
	char x2[30];

	printf("Calling GetLatestPlayedAlbums\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("TopCount: ");
	scanf("%d", &x0);
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetLatestPlayedAlbums(connections[conn_id], x0, x1, x2, get_search_rows, print_GetLatestPlayedAlbums, (void*)parent_lock);}

void call_GetLibraryCheckSum(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling GetLibraryCheckSum\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetLibraryCheckSum(connections[conn_id], x0, print_GetLibraryCheckSum, (void*)parent_lock);}

void call_GetLinkedRoomDetail(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetLinkedRoomDetail\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetLinkedRoomDetail(connections[conn_id], x0, get_search_rows, print_GetLinkedRoomDetail, (void*)parent_lock);}

void call_GetLinkedRooms(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling GetLinkedRooms\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("LocalOnly: ");
	scanf("%d", &x0);

	df_GetLinkedRooms(connections[conn_id], x0, get_search_rows, print_GetLinkedRooms, (void*)parent_lock);}

void call_GetNetworkActiveAdapters(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling GetNetworkActiveAdapters\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("IncludeWireless: ");
	scanf("%d", &x0);

	df_GetNetworkActiveAdapters(connections[conn_id], x0, get_search_rows, print_GetNetworkActiveAdapters, (void*)parent_lock);}

void call_GetNetworkWorkgroup(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling GetNetworkWorkgroup\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_GetNetworkWorkgroup(connections[conn_id], print_GetNetworkWorkgroup, (void*)parent_lock);}

void call_GetNewestAlbums(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];
	char x2[30];

	printf("Calling GetNewestAlbums\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("TopCount: ");
	scanf("%d", &x0);
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetNewestAlbums(connections[conn_id], x0, x1, x2, get_search_rows, print_GetNewestAlbums, (void*)parent_lock);}

void call_GetNonLinkedRooms(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling GetNonLinkedRooms\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("LocalOnly: ");
	scanf("%d", &x0);

	df_GetNonLinkedRooms(connections[conn_id], x0, get_search_rows, print_GetNonLinkedRooms, (void*)parent_lock);}

void call_GetOperationActivity(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;



	printf("Calling GetOperationActivity\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Service: ");
	scanf("%d", &x1);

	df_GetOperationActivity(connections[conn_id], x0, x1, print_GetOperationActivity, (void*)parent_lock);}

void call_GetOutputChannels(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];

	printf("Calling GetOutputChannels\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("HostName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_GetOutputChannels(connections[conn_id], x0, x1, get_search_rows, print_GetOutputChannels, (void*)parent_lock);}

void call_GetOutputDevices(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];
	int x2;

	printf("Calling GetOutputDevices\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("HostName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("AsioOutputs: ");
	scanf("%d", &x2);

	df_GetOutputDevices(connections[conn_id], x0, x1, x2, get_search_rows, print_GetOutputDevices, (void*)parent_lock);}

void call_GetPlayListsByLetter(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];

	printf("Calling GetPlayListsByLetter\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SearchLetter: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetPlayListsByLetter(connections[conn_id], x0, x1, x2, get_search_rows, print_GetPlayListsByLetter, (void*)parent_lock);}

void call_GetPlayerInstances(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling GetPlayerInstances\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetPlayerInstances(connections[conn_id], x0, get_search_rows, print_GetPlayerInstances, (void*)parent_lock);}

void call_GetPlayerStatus(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling GetPlayerStatus\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetPlayerStatus(connections[conn_id], x0, print_GetPlayerStatus, (void*)parent_lock);}

void call_GetPlayerVersion(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling GetPlayerVersion\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetPlayerVersion(connections[conn_id], x0, print_GetPlayerVersion, (void*)parent_lock);}

void call_GetPlaylistsForGenre(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];

	printf("Calling GetPlaylistsForGenre\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetPlaylistsForGenre(connections[conn_id], x0, x1, x2, get_search_rows, print_GetPlaylistsForGenre, (void*)parent_lock);}

void call_GetPlaylistsForSubGenre(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];

	printf("Calling GetPlaylistsForSubGenre\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetPlaylistsForSubGenre(connections[conn_id], x0, x1, x2, get_search_rows, print_GetPlaylistsForSubGenre, (void*)parent_lock);}

void call_GetPlaylistsForSubGenreForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];
	char x3[30];

	printf("Calling GetPlaylistsForSubGenreForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("DeviceAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }

	df_GetPlaylistsForSubGenreForDevice(connections[conn_id], x0, x1, x2, x3, get_search_rows, print_GetPlaylistsForSubGenreForDevice, (void*)parent_lock);}

void call_GetPlaylistsForSubGenreForServer(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];

	printf("Calling GetPlaylistsForSubGenreForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetPlaylistsForSubGenreForServer(connections[conn_id], x0, x1, x2, get_search_rows, print_GetPlaylistsForSubGenreForServer, (void*)parent_lock);}

void call_GetPlaylistsForSubGenreForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];
	char x3[30];

	printf("Calling GetPlaylistsForSubGenreForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("ShareAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }

	df_GetPlaylistsForSubGenreForShare(connections[conn_id], x0, x1, x2, x3, get_search_rows, print_GetPlaylistsForSubGenreForShare, (void*)parent_lock);}

void call_GetRepeat(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling GetRepeat\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetRepeat(connections[conn_id], x0, print_GetRepeat, (void*)parent_lock);}

void call_GetRipEncSettings(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling GetRipEncSettings\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetRipEncSettings(connections[conn_id], x0, get_search_rows, print_GetRipEncSettings, (void*)parent_lock);}

void call_GetRipEncSettingsEx(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling GetRipEncSettingsEx\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetRipEncSettingsEx(connections[conn_id], x0, get_search_rows, print_GetRipEncSettingsEx, (void*)parent_lock);}

void call_GetRippingAlerts(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling GetRippingAlerts\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_GetRippingAlerts(connections[conn_id], get_search_rows, print_GetRippingAlerts, (void*)parent_lock);}

void call_GetRippingStatus(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling GetRippingStatus\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetRippingStatus(connections[conn_id], x0, get_search_rows, print_GetRippingStatus, (void*)parent_lock);}

void call_GetRoomDetail(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling GetRoomDetail\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetRoomDetail(connections[conn_id], x0, print_GetRoomDetail, (void*)parent_lock);}

void call_GetRooms(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling GetRooms\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("LocalOnly: ");
	scanf("%d", &x0);

	df_GetRooms(connections[conn_id], x0, get_search_rows, print_GetRooms, (void*)parent_lock);}

void call_GetRoomsWithPlayBack(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling GetRoomsWithPlayBack\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("LocalOnly: ");
	scanf("%d", &x0);

	df_GetRoomsWithPlayBack(connections[conn_id], x0, get_search_rows, print_GetRoomsWithPlayBack, (void*)parent_lock);}

void call_GetRoomsWithRipping(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling GetRoomsWithRipping\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("LocalOnly: ");
	scanf("%d", &x0);

	df_GetRoomsWithRipping(connections[conn_id], x0, get_search_rows, print_GetRoomsWithRipping, (void*)parent_lock);}

void call_GetRows(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	char x2[30];



	printf("Calling GetRows\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("StartRow: ");
	scanf("%d", &x0);
	printf("RowCount: ");
	scanf("%d", &x1);
	printf("FormatList: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetRows(connections[conn_id], x0, x1, x2, print_GetRows, (void*)parent_lock);}

void call_GetSearchOffset(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	int x2;



	printf("Calling GetSearchOffset\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SearchValue: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SearchColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SearchType: ");
	scanf("%d", &x2);

	df_GetSearchOffset(connections[conn_id], x0, x1, x2, print_GetSearchOffset, (void*)parent_lock);}

void call_GetSettings(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling GetSettings\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetSettings(connections[conn_id], x0, get_search_rows, print_GetSettings, (void*)parent_lock);}

void call_GetSettingsEx(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling GetSettingsEx\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetSettingsEx(connections[conn_id], x0, get_search_rows, print_GetSettingsEx, (void*)parent_lock);}

void call_GetSetupVal(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling GetSetupVal\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_GetSetupVal(connections[conn_id], print_GetSetupVal, (void*)parent_lock);}

void call_GetShuffle(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling GetShuffle\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetShuffle(connections[conn_id], x0, print_GetShuffle, (void*)parent_lock);}

void call_GetSingleRipEncSetting(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];



	printf("Calling GetSingleRipEncSetting\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("SettingName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_GetSingleRipEncSetting(connections[conn_id], x0, x1, print_GetSingleRipEncSetting, (void*)parent_lock);}

void call_GetSingleSystemSetting(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];



	printf("Calling GetSingleSystemSetting\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("SettingName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_GetSingleSystemSetting(connections[conn_id], x0, x1, print_GetSingleSystemSetting, (void*)parent_lock);}

void call_GetStatusMessageDetail(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling GetStatusMessageDetail\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Key: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetStatusMessageDetail(connections[conn_id], x0, print_GetStatusMessageDetail, (void*)parent_lock);}

void call_GetStatusMessages(pthread_mutex_t *parent_lock) {
	int conn_id;
	df_date x0;
	char x1[30];
	int x2;

	printf("Calling GetStatusMessages\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("MessageDate: ");
	//x0 = malloc(sizeof(df_date));
	scanf("%ud-%ud-%ud", &x0.day, &x0.month, &x0.year);
	printf("Category: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("Tag: ");
	scanf("%d", &x2);

	df_GetStatusMessages(connections[conn_id], x0, x1, x2, get_search_rows, print_GetStatusMessages, (void*)parent_lock);}

void call_GetStoreDetail(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetStoreDetail\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("MusicStoreKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetStoreDetail(connections[conn_id], x0, get_search_rows, print_GetStoreDetail, (void*)parent_lock);}

void call_GetStores(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;

	printf("Calling GetStores\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("IncludeReadOnly: ");
	scanf("%d", &x0);
	printf("MusicStoreType: ");
	scanf("%d", &x1);

	df_GetStores(connections[conn_id], x0, x1, get_search_rows, print_GetStores, (void*)parent_lock);}

void call_GetSubGenreDetail(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling GetSubGenreDetail\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SubGenreKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetSubGenreDetail(connections[conn_id], x0, print_GetSubGenreDetail, (void*)parent_lock);}

void call_GetSubGenresForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];

	printf("Calling GetSubGenresForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetSubGenresForDevice(connections[conn_id], x0, x1, x2, get_search_rows, print_GetSubGenresForDevice, (void*)parent_lock);}

void call_GetSubGenresForGenre(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;
	char x2[30];
	char x3[30];

	printf("Calling GetSubGenresForGenre\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Allocated: ");
	scanf("%d", &x1);
	printf("SortColumn: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }

	df_GetSubGenresForGenre(connections[conn_id], x0, x1, x2, x3, get_search_rows, print_GetSubGenresForGenre, (void*)parent_lock);}

void call_GetSubGenresForServer(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	char x2[30];
	char x3[30];

	printf("Calling GetSubGenresForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Allocated: ");
	scanf("%d", &x0);
	printf("UserDefined: ");
	scanf("%d", &x1);
	printf("SortColumn: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }

	df_GetSubGenresForServer(connections[conn_id], x0, x1, x2, x3, get_search_rows, print_GetSubGenresForServer, (void*)parent_lock);}

void call_GetSubGenresForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];

	printf("Calling GetSubGenresForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetSubGenresForShare(connections[conn_id], x0, x1, x2, get_search_rows, print_GetSubGenresForShare, (void*)parent_lock);}

void call_GetSystemDrives(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling GetSystemDrives\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_GetSystemDrives(connections[conn_id], get_search_rows, print_GetSystemDrives, (void*)parent_lock);}

void call_GetSystemTime(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling GetSystemTime\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_GetSystemTime(connections[conn_id], print_GetSystemTime, (void*)parent_lock);}

void call_GetTopPlayedAlbums(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];
	char x2[30];

	printf("Calling GetTopPlayedAlbums\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("TopCount: ");
	scanf("%d", &x0);
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetTopPlayedAlbums(connections[conn_id], x0, x1, x2, get_search_rows, print_GetTopPlayedAlbums, (void*)parent_lock);}

void call_GetTrackCount(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling GetTrackCount\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetTrackCount(connections[conn_id], x0, print_GetTrackCount, (void*)parent_lock);}

void call_GetTrackDetailsFromPlayer(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];



	printf("Calling GetTrackDetailsFromPlayer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("TrackPath: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_GetTrackDetailsFromPlayer(connections[conn_id], x0, x1, print_GetTrackDetailsFromPlayer, (void*)parent_lock);}

void call_GetTrackLength(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling GetTrackLength\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetTrackLength(connections[conn_id], x0, print_GetTrackLength, (void*)parent_lock);}

void call_GetTrackName(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling GetTrackName\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetTrackName(connections[conn_id], x0, print_GetTrackName, (void*)parent_lock);}

void call_GetTrackNum(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling GetTrackNum\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetTrackNum(connections[conn_id], x0, print_GetTrackNum, (void*)parent_lock);}

void call_GetTrackPosition(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling GetTrackPosition\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetTrackPosition(connections[conn_id], x0, print_GetTrackPosition, (void*)parent_lock);}

void call_GetTrackRange(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	char x2[30];
	char x3[30];
	int x4;

	printf("Calling GetTrackRange\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("StartRow: ");
	scanf("%d", &x0);
	printf("RowCount: ");
	scanf("%d", &x1);
	printf("Filter: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("Address: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }
	printf("Storage: ");
	scanf("%d", &x4);

	df_GetTrackRange(connections[conn_id], x0, x1, x2, x3, x4, get_search_rows, print_GetTrackRange, (void*)parent_lock);}

void call_GetTracksAll(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling GetTracksAll\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_GetTracksAll(connections[conn_id], get_search_rows, print_GetTracksAll, (void*)parent_lock);}

void call_GetTracksForAlbumInUPL(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetTracksForAlbumInUPL\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetTracksForAlbumInUPL(connections[conn_id], x0, get_search_rows, print_GetTracksForAlbumInUPL, (void*)parent_lock);}

void call_GetTracksForArtist(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetTracksForArtist\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetTracksForArtist(connections[conn_id], x0, get_search_rows, print_GetTracksForArtist, (void*)parent_lock);}

void call_GetTracksForArtistForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];

	printf("Calling GetTracksForArtistForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("DeviceAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_GetTracksForArtistForDevice(connections[conn_id], x0, x1, get_search_rows, print_GetTracksForArtistForDevice, (void*)parent_lock);}

void call_GetTracksForArtistForServer(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetTracksForArtistForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetTracksForArtistForServer(connections[conn_id], x0, get_search_rows, print_GetTracksForArtistForServer, (void*)parent_lock);}

void call_GetTracksForArtistForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];

	printf("Calling GetTracksForArtistForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("ShareAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_GetTracksForArtistForShare(connections[conn_id], x0, x1, get_search_rows, print_GetTracksForArtistForShare, (void*)parent_lock);}

void call_GetTracksForDeletion(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;

	printf("Calling GetTracksForDeletion\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RemoteImagePath: ");
	scanf("%d", &x0);
	printf("ImageSize: ");
	scanf("%d", &x1);

	df_GetTracksForDeletion(connections[conn_id], x0, x1, get_search_rows, print_GetTracksForDeletion, (void*)parent_lock);}

void call_GetTracksForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetTracksForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetTracksForDevice(connections[conn_id], x0, get_search_rows, print_GetTracksForDevice, (void*)parent_lock);}

void call_GetTracksForGenre(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetTracksForGenre\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetTracksForGenre(connections[conn_id], x0, get_search_rows, print_GetTracksForGenre, (void*)parent_lock);}

void call_GetTracksForNamedEntity(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	int x2;

	printf("Calling GetTracksForNamedEntity\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("EntityName: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("EntityValue: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("ExactMatch: ");
	scanf("%d", &x2);

	df_GetTracksForNamedEntity(connections[conn_id], x0, x1, x2, get_search_rows, print_GetTracksForNamedEntity, (void*)parent_lock);}

void call_GetTracksForPlaylist(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;

	printf("Calling GetTracksForPlaylist\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("ShowHidden: ");
	scanf("%d", &x1);

	df_GetTracksForPlaylist(connections[conn_id], x0, x1, get_search_rows, print_GetTracksForPlaylist, (void*)parent_lock);}

void call_GetTracksForServer(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling GetTracksForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_GetTracksForServer(connections[conn_id], get_search_rows, print_GetTracksForServer, (void*)parent_lock);}

void call_GetTracksForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetTracksForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetTracksForShare(connections[conn_id], x0, get_search_rows, print_GetTracksForShare, (void*)parent_lock);}

void call_GetTracksForSubGenre(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetTracksForSubGenre\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetTracksForSubGenre(connections[conn_id], x0, get_search_rows, print_GetTracksForSubGenre, (void*)parent_lock);}

void call_GetTracksForSubGenreForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];

	printf("Calling GetTracksForSubGenreForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("DeviceAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_GetTracksForSubGenreForDevice(connections[conn_id], x0, x1, get_search_rows, print_GetTracksForSubGenreForDevice, (void*)parent_lock);}

void call_GetTracksForSubGenreForServer(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling GetTracksForSubGenreForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_GetTracksForSubGenreForServer(connections[conn_id], x0, get_search_rows, print_GetTracksForSubGenreForServer, (void*)parent_lock);}

void call_GetTracksForSubGenreForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];

	printf("Calling GetTracksForSubGenreForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("ShareAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_GetTracksForSubGenreForShare(connections[conn_id], x0, x1, get_search_rows, print_GetTracksForSubGenreForShare, (void*)parent_lock);}

void call_GetTracksOtherInfo(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;
	int x2;

	printf("Calling GetTracksOtherInfo\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("RemoteImagePath: ");
	scanf("%d", &x1);
	printf("ImageSize: ");
	scanf("%d", &x2);

	df_GetTracksOtherInfo(connections[conn_id], x0, x1, x2, get_search_rows, print_GetTracksOtherInfo, (void*)parent_lock);}

void call_GetTracksSearchName(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;
	int x2;
	int x3;

	printf("Calling GetTracksSearchName\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SearchString: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SearchType: ");
	scanf("%d", &x1);
	printf("RemoteImagePath: ");
	scanf("%d", &x2);
	printf("ImageSize: ");
	scanf("%d", &x3);

	df_GetTracksSearchName(connections[conn_id], x0, x1, x2, x3, get_search_rows, print_GetTracksSearchName, (void*)parent_lock);}

void call_GetUpnpMediaRenderers(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling GetUpnpMediaRenderers\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_GetUpnpMediaRenderers(connections[conn_id], get_search_rows, print_GetUpnpMediaRenderers, (void*)parent_lock);}

void call_GetUserPlaylists(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];

	printf("Calling GetUserPlaylists\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SortColumn: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_GetUserPlaylists(connections[conn_id], x0, x1, get_search_rows, print_GetUserPlaylists, (void*)parent_lock);}

void call_GetUserPlaylistsForDevice(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];

	printf("Calling GetUserPlaylistsForDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetUserPlaylistsForDevice(connections[conn_id], x0, x1, x2, get_search_rows, print_GetUserPlaylistsForDevice, (void*)parent_lock);}

void call_GetUserPlaylistsForServer(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];

	printf("Calling GetUserPlaylistsForServer\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SortColumn: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_GetUserPlaylistsForServer(connections[conn_id], x0, x1, get_search_rows, print_GetUserPlaylistsForServer, (void*)parent_lock);}

void call_GetUserPlaylistsForShare(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];

	printf("Calling GetUserPlaylistsForShare\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SortColumn: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SortOrder: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_GetUserPlaylistsForShare(connections[conn_id], x0, x1, x2, get_search_rows, print_GetUserPlaylistsForShare, (void*)parent_lock);}

void call_GetUserStatus(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling GetUserStatus\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_GetUserStatus(connections[conn_id], get_search_rows, print_GetUserStatus, (void*)parent_lock);}

void call_GetVolume(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling GetVolume\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_GetVolume(connections[conn_id], x0, print_GetVolume, (void*)parent_lock);}

void call_IgnoreExternalStorage(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;



	printf("Calling IgnoreExternalStorage\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("StorageKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("IgnoreLevel: ");
	scanf("%d", &x1);

	df_IgnoreExternalStorage(connections[conn_id], x0, x1, print_IgnoreExternalStorage, (void*)parent_lock);}

void call_IsCDPlaying(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling IsCDPlaying\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_IsCDPlaying(connections[conn_id], x0, print_IsCDPlaying, (void*)parent_lock);}

void call_LookupError(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling LookupError\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("ErrorCode: ");
	scanf("%d", &x0);

	df_LookupError(connections[conn_id], x0, print_LookupError, (void*)parent_lock);}

void call_MasterIpChanged(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];

	printf("Calling MasterIpChanged\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("MasterName: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("MasterAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_MasterIpChanged(connections[conn_id], x0, x1);
	pthread_mutex_unlock(parent_lock);
}

void call_MoveAlbumCancel(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling MoveAlbumCancel\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_MoveAlbumCancel(connections[conn_id], x0);
	pthread_mutex_unlock(parent_lock);
}

void call_MoveAlbumGetQueue(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling MoveAlbumGetQueue\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_MoveAlbumGetQueue(connections[conn_id], get_search_rows, print_MoveAlbumGetQueue, (void*)parent_lock);}

void call_MoveAlbumGetStatus(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling MoveAlbumGetStatus\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_MoveAlbumGetStatus(connections[conn_id], print_MoveAlbumGetStatus, (void*)parent_lock);}

void call_MoveAlbumToMusicStore(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];



	printf("Calling MoveAlbumToMusicStore\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("MusicStoreKey: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_MoveAlbumToMusicStore(connections[conn_id], x0, x1, print_MoveAlbumToMusicStore, (void*)parent_lock);}

void call_NewOutputChannel(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];
	int x2;
	char x3[30];



	printf("Calling NewOutputChannel\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("HostName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("ChannelNumber: ");
	scanf("%d", &x2);
	printf("InitString: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }

	df_NewOutputChannel(connections[conn_id], x0, x1, x2, x3, print_NewOutputChannel, (void*)parent_lock);}

void call_NextTrack(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling NextTrack\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_NextTrack(connections[conn_id], x0, print_NextTrack, (void*)parent_lock);}

void call_Pause(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling Pause\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_Pause(connections[conn_id], x0);
	pthread_mutex_unlock(parent_lock);
}

void call_Play(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling Play\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_Play(connections[conn_id], x0);
	pthread_mutex_unlock(parent_lock);
}

void call_PlayAlbum(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	char x2[30];
	int x3;



	printf("Calling PlayAlbum\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Replace: ");
	scanf("%d", &x1);
	printf("Address: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("StartTrack: ");
	scanf("%d", &x3);

	df_PlayAlbum(connections[conn_id], x0, x1, x2, x3, print_PlayAlbum, (void*)parent_lock);}

void call_PlayAlbums(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	char x2[30];



	printf("Calling PlayAlbums\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Replace: ");
	scanf("%d", &x1);
	printf("Address: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_PlayAlbums(connections[conn_id], x0, x1, x2, print_PlayAlbums, (void*)parent_lock);}

void call_PlayAlbumsFromSearch(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;



	printf("Calling PlayAlbumsFromSearch\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Replace: ");
	scanf("%d", &x1);

	df_PlayAlbumsFromSearch(connections[conn_id], x0, x1, print_PlayAlbumsFromSearch, (void*)parent_lock);}

void call_PlayAll(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	int x2;
	char x3[30];
	int x4;
	char x5[30];



	printf("Calling PlayAll\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Replace: ");
	scanf("%d", &x1);
	printf("PlayScope: ");
	scanf("%d", &x2);
	printf("ScopeKey: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }
	printf("PlayType: ");
	scanf("%d", &x4);
	printf("Address: ");
	scanf("%s", x5);
	if (x5[0] == '-') { x5[0] = '\0'; }

	df_PlayAll(connections[conn_id], x0, x1, x2, x3, x4, x5, print_PlayAll, (void*)parent_lock);}

void call_PlayArtistAlbum(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];
	char x2[30];
	int x3;
	int x4;



	printf("Calling PlayArtistAlbum\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Artist: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("Album: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("Randomise: ");
	scanf("%d", &x3);
	printf("OnErrorBehaviour: ");
	scanf("%d", &x4);

	df_PlayArtistAlbum(connections[conn_id], x0, x1, x2, x3, x4, print_PlayArtistAlbum, (void*)parent_lock);}

void call_PlayLastPlayed(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	int x2;



	printf("Calling PlayLastPlayed\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Randomise: ");
	scanf("%d", &x1);
	printf("Number: ");
	scanf("%d", &x2);

	df_PlayLastPlayed(connections[conn_id], x0, x1, x2, print_PlayLastPlayed, (void*)parent_lock);}

void call_PlayLastRipped(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	int x2;



	printf("Calling PlayLastRipped\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Randomise: ");
	scanf("%d", &x1);
	printf("Number: ");
	scanf("%d", &x2);

	df_PlayLastRipped(connections[conn_id], x0, x1, x2, print_PlayLastRipped, (void*)parent_lock);}

void call_PlayMostPopular(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	int x2;



	printf("Calling PlayMostPopular\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Randomise: ");
	scanf("%d", &x1);
	printf("Number: ");
	scanf("%d", &x2);

	df_PlayMostPopular(connections[conn_id], x0, x1, x2, print_PlayMostPopular, (void*)parent_lock);}

void call_PlayPlaylist(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];
	int x2;
	int x3;



	printf("Calling PlayPlaylist\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("PlaylistName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("Randomise: ");
	scanf("%d", &x2);
	printf("OnErrorBehaviour: ");
	scanf("%d", &x3);

	df_PlayPlaylist(connections[conn_id], x0, x1, x2, x3, print_PlayPlaylist, (void*)parent_lock);}

void call_PlayRandom(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];
	char x2[30];
	int x3;



	printf("Calling PlayRandom\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Genre: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SubGenre: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("OnErrorBehaviour: ");
	scanf("%d", &x3);

	df_PlayRandom(connections[conn_id], x0, x1, x2, x3, print_PlayRandom, (void*)parent_lock);}

void call_PlayTrack(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	char x2[30];



	printf("Calling PlayTrack\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Replace: ");
	scanf("%d", &x1);
	printf("Address: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_PlayTrack(connections[conn_id], x0, x1, x2, print_PlayTrack, (void*)parent_lock);}

void call_PlayTracks(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	char x2[30];
	int x3;



	printf("Calling PlayTracks\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Replace: ");
	scanf("%d", &x1);
	printf("Address: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("StartTrack: ");
	scanf("%d", &x3);

	df_PlayTracks(connections[conn_id], x0, x1, x2, x3, print_PlayTracks, (void*)parent_lock);}

void call_PlayTracksFromSearch(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	int x2;



	printf("Calling PlayTracksFromSearch\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Replace: ");
	scanf("%d", &x1);
	printf("StartTrack: ");
	scanf("%d", &x2);

	df_PlayTracksFromSearch(connections[conn_id], x0, x1, x2, print_PlayTracksFromSearch, (void*)parent_lock);}

void call_PlayUrl(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	char x2[30];



	printf("Calling PlayUrl\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Replace: ");
	scanf("%d", &x1);
	printf("Url: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_PlayUrl(connections[conn_id], x0, x1, x2, print_PlayUrl, (void*)parent_lock);}

void call_PlayUrls(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	char x2[30];
	int x3;



	printf("Calling PlayUrls\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Replace: ");
	scanf("%d", &x1);
	printf("Urls: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("StartTrack: ");
	scanf("%d", &x3);

	df_PlayUrls(connections[conn_id], x0, x1, x2, x3, print_PlayUrls, (void*)parent_lock);}

void call_PrevTrack(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling PrevTrack\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_PrevTrack(connections[conn_id], x0, print_PrevTrack, (void*)parent_lock);}

void call_ProcessEmbeddedInit(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling ProcessEmbeddedInit\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_ProcessEmbeddedInit(connections[conn_id], print_ProcessEmbeddedInit, (void*)parent_lock);}

void call_PromoteShareToMusicStore(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;



	printf("Calling PromoteShareToMusicStore\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("ShareKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("ChangeOwnership: ");
	scanf("%d", &x1);

	df_PromoteShareToMusicStore(connections[conn_id], x0, x1, print_PromoteShareToMusicStore, (void*)parent_lock);}

void call_PurgeImageCache(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling PurgeImageCache\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("All: ");
	scanf("%d", &x0);

	df_PurgeImageCache(connections[conn_id], x0);
	pthread_mutex_unlock(parent_lock);
}

void call_QueryAllPlayback(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling QueryAllPlayback\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_QueryAllPlayback(connections[conn_id], x0, print_QueryAllPlayback, (void*)parent_lock);}

void call_RandomisePlaylist(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling RandomisePlaylist\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_RandomisePlaylist(connections[conn_id], x0);
	pthread_mutex_unlock(parent_lock);
}

void call_ReleaseSerialPort(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling ReleaseSerialPort\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_ReleaseSerialPort(connections[conn_id], print_ReleaseSerialPort, (void*)parent_lock);}

void call_RemoveAlbumsFromUserPlaylist(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];



	printf("Calling RemoveAlbumsFromUserPlaylist\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("UserPlaylistKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("AlbumKey: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_RemoveAlbumsFromUserPlaylist(connections[conn_id], x0, x1, print_RemoveAlbumsFromUserPlaylist, (void*)parent_lock);}

void call_RemoveCoverImage(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling RemoveCoverImage\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_RemoveCoverImage(connections[conn_id], x0, print_RemoveCoverImage, (void*)parent_lock);}

void call_RemoveExternalStorage(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling RemoveExternalStorage\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("StorageKey: ");
	scanf("%d", &x0);

	df_RemoveExternalStorage(connections[conn_id], x0, print_RemoveExternalStorage, (void*)parent_lock);}

void call_RemoveOldRooms(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;



	printf("Calling RemoveOldRooms\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("TimeoutPerHost: ");
	scanf("%d", &x0);

	df_RemoveOldRooms(connections[conn_id], x0, print_RemoveOldRooms, (void*)parent_lock);}

void call_RemovePlayerInstance(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;



	printf("Calling RemovePlayerInstance\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Key: ");
	scanf("%d", &x1);

	df_RemovePlayerInstance(connections[conn_id], x0, x1, print_RemovePlayerInstance, (void*)parent_lock);}

void call_RemoveTrack(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;



	printf("Calling RemoveTrack\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("TrackNumber: ");
	scanf("%d", &x1);

	df_RemoveTrack(connections[conn_id], x0, x1, print_RemoveTrack, (void*)parent_lock);}

void call_RenameAlbum(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];



	printf("Calling RenameAlbum\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("AlbumKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("NewAlbumName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_RenameAlbum(connections[conn_id], x0, x1, print_RenameAlbum, (void*)parent_lock);}

void call_RenameArtist(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];



	printf("Calling RenameArtist\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("AlbumKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("NewArtistName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_RenameArtist(connections[conn_id], x0, x1, print_RenameArtist, (void*)parent_lock);}

void call_RenamePlaylist(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];



	printf("Calling RenamePlaylist\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("PlaylistKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("NewName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_RenamePlaylist(connections[conn_id], x0, x1, print_RenamePlaylist, (void*)parent_lock);}

void call_RenameTrack(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];



	printf("Calling RenameTrack\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("TrackKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("NewTrackName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_RenameTrack(connections[conn_id], x0, x1, print_RenameTrack, (void*)parent_lock);}

void call_RequestAlbumCover(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling RequestAlbumCover\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_RequestAlbumCover(connections[conn_id], x0, print_RequestAlbumCover, (void*)parent_lock);}

void call_RescanExternalStorages(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling RescanExternalStorages\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_RescanExternalStorages(connections[conn_id], print_RescanExternalStorages, (void*)parent_lock);}

void call_RescanMusicStore(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling RescanMusicStore\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("MusicStoreKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_RescanMusicStore(connections[conn_id], x0, print_RescanMusicStore, (void*)parent_lock);}

void call_RestartDevice(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling RestartDevice\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_RestartDevice(connections[conn_id]);
	pthread_mutex_unlock(parent_lock);
}

void call_RestoreSingleAlbum(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling RestoreSingleAlbum\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("AlbumKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_RestoreSingleAlbum(connections[conn_id], x0, print_RestoreSingleAlbum, (void*)parent_lock);}

void call_RestoreSingleTrack(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];



	printf("Calling RestoreSingleTrack\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("AlbumKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("TrackKey: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_RestoreSingleTrack(connections[conn_id], x0, x1, print_RestoreSingleTrack, (void*)parent_lock);}

void call_RoomIpChanged(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling RoomIpChanged\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_RoomIpChanged(connections[conn_id]);
	pthread_mutex_unlock(parent_lock);
}

void call_SaveCurrentPlayList(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];



	printf("Calling SaveCurrentPlayList\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("NewName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_SaveCurrentPlayList(connections[conn_id], x0, x1, print_SaveCurrentPlayList, (void*)parent_lock);}

void call_SavePlayerInstance(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	int x2;
	int x3;



	printf("Calling SavePlayerInstance\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Key: ");
	scanf("%d", &x1);
	printf("OutputDeviceID: ");
	scanf("%d", &x2);
	printf("SourceLineID: ");
	scanf("%d", &x3);

	df_SavePlayerInstance(connections[conn_id], x0, x1, x2, x3, print_SavePlayerInstance, (void*)parent_lock);}

void call_ScanExternalStorage(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling ScanExternalStorage\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("StorageKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_ScanExternalStorage(connections[conn_id], x0, print_ScanExternalStorage, (void*)parent_lock);}

void call_ScanForExternalStorages(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling ScanForExternalStorages\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_ScanForExternalStorages(connections[conn_id], print_ScanForExternalStorages, (void*)parent_lock);}

void call_ServiceMode(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling ServiceMode\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_ServiceMode(connections[conn_id], print_ServiceMode, (void*)parent_lock);}

void call_SetAlbumLowQuality(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;



	printf("Calling SetAlbumLowQuality\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("AlbumKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("LowQuality: ");
	scanf("%d", &x1);

	df_SetAlbumLowQuality(connections[conn_id], x0, x1, print_SetAlbumLowQuality, (void*)parent_lock);}

void call_SetCDDetected(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling SetCDDetected\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("CDDetected: ");
	scanf("%d", &x0);

	df_SetCDDetected(connections[conn_id], x0);
	pthread_mutex_unlock(parent_lock);
}

void call_SetConnOption(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];

	printf("Calling SetConnOption\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("OptionName: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("OptionValue: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_SetConnOption(connections[conn_id], x0, x1);
	pthread_mutex_unlock(parent_lock);
}

void call_SetCoverImage(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;
	char x2[30];



	printf("Calling SetCoverImage\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("ForceOverwrite: ");
	scanf("%d", &x1);
	printf("ImageData: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_SetCoverImage(connections[conn_id], x0, x1, x2, print_SetCoverImage, (void*)parent_lock);}

void call_SetDriveUsage(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;
	int x2;



	printf("Calling SetDriveUsage\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("DriveKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Usage: ");
	scanf("%d", &x1);
	printf("ForceChange: ");
	scanf("%d", &x2);

	df_SetDriveUsage(connections[conn_id], x0, x1, x2, print_SetDriveUsage, (void*)parent_lock);}

void call_SetLength(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	int x2;

	printf("Calling SetLength\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("FormatList: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("FieldName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("Length: ");
	scanf("%d", &x2);

	df_SetLength(connections[conn_id], x0, x1, x2);
	pthread_mutex_unlock(parent_lock);
}

void call_SetMusicStoreCredentials(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];



	printf("Calling SetMusicStoreCredentials\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("MusicStoreKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Username: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("Password: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_SetMusicStoreCredentials(connections[conn_id], x0, x1, x2, print_SetMusicStoreCredentials, (void*)parent_lock);}

void call_SetMusicStorePriority(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;



	printf("Calling SetMusicStorePriority\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("MusicStoreKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Priority: ");
	scanf("%d", &x1);

	df_SetMusicStorePriority(connections[conn_id], x0, x1, print_SetMusicStorePriority, (void*)parent_lock);}

void call_SetRepeat(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;

	printf("Calling SetRepeat\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Repeat: ");
	scanf("%d", &x1);

	df_SetRepeat(connections[conn_id], x0, x1);
	pthread_mutex_unlock(parent_lock);
}

void call_SetRippingStatus(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	int x2;
	int x3;
	int x4;
	df_time x5;
	df_time x6;
	char x7[30];
	int x8;
	char x9[30];
	char x10[30];
	char x11[30];

	printf("Calling SetRippingStatus\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Artist: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Album: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("Tracks: ");
	scanf("%d", &x2);
	printf("TracksRipped: ");
	scanf("%d", &x3);
	printf("Errors: ");
	scanf("%d", &x4);
	printf("TimeTaken: ");
	//x5 = malloc(sizeof(df_time));
	scanf("%ud:%ud:%ud", &x5.hours, &x5.minutes, &x5.seconds);
	printf("TimeLeft: ");
	//x6 = malloc(sizeof(df_time));
	scanf("%ud:%ud:%ud", &x6.hours, &x6.minutes, &x6.seconds);
	printf("Track: ");
	scanf("%s", x7);
	if (x7[0] == '-') { x7[0] = '\0'; }
	printf("TrackPercent: ");
	scanf("%d", &x8);
	printf("UserMessage: ");
	scanf("%s", x9);
	if (x9[0] == '-') { x9[0] = '\0'; }
	printf("LookupProviderUsed: ");
	scanf("%s", x10);
	if (x10[0] == '-') { x10[0] = '\0'; }
	printf("SourceFolder: ");
	scanf("%s", x11);
	if (x11[0] == '-') { x11[0] = '\0'; }

	df_SetRippingStatus(connections[conn_id], x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11);
	pthread_mutex_unlock(parent_lock);
}

void call_SetShuffle(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;

	printf("Calling SetShuffle\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Shuffle: ");
	scanf("%d", &x1);

	df_SetShuffle(connections[conn_id], x0, x1);
	pthread_mutex_unlock(parent_lock);
}

void call_SetTrack(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;

	printf("Calling SetTrack\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("TrackNumber: ");
	scanf("%d", &x1);

	df_SetTrack(connections[conn_id], x0, x1);
	pthread_mutex_unlock(parent_lock);
}

void call_SetTrackPosition(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	df_time x1;

	printf("Calling SetTrackPosition\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("PlayPosition: ");
	//x1 = malloc(sizeof(df_time));
	scanf("%ud:%ud:%ud", &x1.hours, &x1.minutes, &x1.seconds);

	df_SetTrackPosition(connections[conn_id], x0, x1);
	pthread_mutex_unlock(parent_lock);
}

void call_SetVolume(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;

	printf("Calling SetVolume\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Volume: ");
	scanf("%d", &x1);

	df_SetVolume(connections[conn_id], x0, x1);
	pthread_mutex_unlock(parent_lock);
}

void call_Status(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling Status\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_Status(connections[conn_id], get_search_rows, print_Status, (void*)parent_lock);}

void call_Stop(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling Stop\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);

	df_Stop(connections[conn_id], x0);
	pthread_mutex_unlock(parent_lock);
}

void call_StopBackupDrive(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling StopBackupDrive\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_StopBackupDrive(connections[conn_id], print_StopBackupDrive, (void*)parent_lock);}

void call_ToggleDeviceSync(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;



	printf("Calling ToggleDeviceSync\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Key: ");
	scanf("%d", &x0);
	printf("Sync: ");
	scanf("%d", &x1);

	df_ToggleDeviceSync(connections[conn_id], x0, x1, print_ToggleDeviceSync, (void*)parent_lock);}

void call_UndoUserEdits(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling UndoUserEdits\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("AlbumKeys: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_UndoUserEdits(connections[conn_id], x0, get_search_rows, print_UndoUserEdits, (void*)parent_lock);}

void call_UpdateBackupJob(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];
	char x3[30];
	int x4;
	int x5;
	int x6;
	df_date x7;
	df_time x8;



	printf("Calling UpdateBackupJob\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("SourceDriveAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("DestinationDriveAddress: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("Name: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }
	printf("BackupType: ");
	scanf("%d", &x4);
	printf("BackupPeriod: ");
	scanf("%d", &x5);
	printf("PeriodValue: ");
	scanf("%d", &x6);
	printf("RunDate: ");
	//x7 = malloc(sizeof(df_date));
	scanf("%ud-%ud-%ud", &x7.day, &x7.month, &x7.year);
	printf("RunTime: ");
	//x8 = malloc(sizeof(df_time));
	scanf("%ud:%ud:%ud", &x8.hours, &x8.minutes, &x8.seconds);

	df_UpdateBackupJob(connections[conn_id], x0, x1, x2, x3, x4, x5, x6, x7, x8, print_UpdateBackupJob, (void*)parent_lock);}

void call_UpdateDrive(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	int x2;
	char x3[30];
	char x4[30];
	int x5;



	printf("Calling UpdateDrive\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("DriveKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("DriveLetter: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("PrimaryDrive: ");
	scanf("%d", &x2);
	printf("RootPath: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }
	printf("SharePath: ");
	scanf("%s", x4);
	if (x4[0] == '-') { x4[0] = '\0'; }
	printf("BadPathBehaviour: ");
	scanf("%d", &x5);

	df_UpdateDrive(connections[conn_id], x0, x1, x2, x3, x4, x5, print_UpdateDrive, (void*)parent_lock);}

void call_UpdateExternalStorage(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];
	char x3[30];
	char x4[30];
	char x5[30];



	printf("Calling UpdateExternalStorage\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("StorageKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("IPAddress: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("HostName: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("ShareName: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }
	printf("UserName: ");
	scanf("%s", x4);
	if (x4[0] == '-') { x4[0] = '\0'; }
	printf("Password: ");
	scanf("%s", x5);
	if (x5[0] == '-') { x5[0] = '\0'; }

	df_UpdateExternalStorage(connections[conn_id], x0, x1, x2, x3, x4, x5, print_UpdateExternalStorage, (void*)parent_lock);}

void call_UpdateGenre(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	int x2;



	printf("Calling UpdateGenre\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("GenreKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("GenreName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("Ordinal: ");
	scanf("%d", &x2);

	df_UpdateGenre(connections[conn_id], x0, x1, x2, print_UpdateGenre, (void*)parent_lock);}

void call_UpdateHitCount(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;



	printf("Calling UpdateHitCount\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("Address: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("ResetHitCount: ");
	scanf("%d", &x1);

	df_UpdateHitCount(connections[conn_id], x0, x1, print_UpdateHitCount, (void*)parent_lock);}

void call_UpdateLinkedRoom(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];
	int x3;
	char x4[30];



	printf("Calling UpdateLinkedRoom\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("RoomName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("ShortName: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("RoomID: ");
	scanf("%d", &x3);
	printf("ChildRoomKey: ");
	scanf("%s", x4);
	if (x4[0] == '-') { x4[0] = '\0'; }

	df_UpdateLinkedRoom(connections[conn_id], x0, x1, x2, x3, x4, print_UpdateLinkedRoom, (void*)parent_lock);}

void call_UpdateOutputChannel(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];
	int x2;
	char x3[30];



	printf("Calling UpdateOutputChannel\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("HostName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("ChannelNumber: ");
	scanf("%d", &x2);
	printf("InitString: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }

	df_UpdateOutputChannel(connections[conn_id], x0, x1, x2, x3, print_UpdateOutputChannel, (void*)parent_lock);}

void call_UpdatePlaylist(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];



	printf("Calling UpdatePlaylist\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("PlaylistKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("Name: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("TrackKey: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_UpdatePlaylist(connections[conn_id], x0, x1, x2, print_UpdatePlaylist, (void*)parent_lock);}

void call_UpdateRoom(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	int x2;
	char x3[30];
	char x4[30];
	int x5;
	int x6;
	int x7;
	int x8;
	char x9[30];



	printf("Calling UpdateRoom\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("RoomIP: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("Channel: ");
	scanf("%d", &x2);
	printf("RoomName: ");
	scanf("%s", x3);
	if (x3[0] == '-') { x3[0] = '\0'; }
	printf("ShortName: ");
	scanf("%s", x4);
	if (x4[0] == '-') { x4[0] = '\0'; }
	printf("PlaybackCapability: ");
	scanf("%d", &x5);
	printf("RippingCapability: ");
	scanf("%d", &x6);
	printf("MusicManagementCapability: ");
	scanf("%d", &x7);
	printf("RoomID: ");
	scanf("%d", &x8);
	printf("HostName: ");
	scanf("%s", x9);
	if (x9[0] == '-') { x9[0] = '\0'; }

	df_UpdateRoom(connections[conn_id], x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, print_UpdateRoom, (void*)parent_lock);}

void call_UpdateSingleRipEncSetting(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];
	char x2[30];



	printf("Calling UpdateSingleRipEncSetting\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("SettingName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("NewValue: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_UpdateSingleRipEncSetting(connections[conn_id], x0, x1, x2, print_UpdateSingleRipEncSetting, (void*)parent_lock);}

void call_UpdateSingleSystemSetting(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];
	char x2[30];



	printf("Calling UpdateSingleSystemSetting\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("SettingName: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("NewValue: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_UpdateSingleSystemSetting(connections[conn_id], x0, x1, x2, print_UpdateSingleSystemSetting, (void*)parent_lock);}

void call_UpdateSubGenre(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];
	char x2[30];
	int x3;



	printf("Calling UpdateSubGenre\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("SubGenreKey: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("GenreKey: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("SubGenreName: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }
	printf("Ordinal: ");
	scanf("%d", &x3);

	df_UpdateSubGenre(connections[conn_id], x0, x1, x2, x3, print_UpdateSubGenre, (void*)parent_lock);}

void call_UploadMessages(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling UploadMessages\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_UploadMessages(connections[conn_id], print_UploadMessages, (void*)parent_lock);}

void call_Version(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling Version\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_Version(connections[conn_id], print_Version, (void*)parent_lock);}

void call_vTunerAddRemoveFavourite(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];



	printf("Calling vTunerAddRemoveFavourite\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("vTunerUrl: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_vTunerAddRemoveFavourite(connections[conn_id], x0, print_vTunerAddRemoveFavourite, (void*)parent_lock);}

void call_vTunerCheckAvailability(pthread_mutex_t *parent_lock) {
	int conn_id;



	printf("Calling vTunerCheckAvailability\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_vTunerCheckAvailability(connections[conn_id], print_vTunerCheckAvailability, (void*)parent_lock);}

void call_vTunerCleanStatistics(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling vTunerCleanStatistics\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_vTunerCleanStatistics(connections[conn_id]);
	pthread_mutex_unlock(parent_lock);
}

void call_vTunerClearPresetChannel(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;

	printf("Calling vTunerClearPresetChannel\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("ChannelNumber: ");
	scanf("%d", &x0);

	df_vTunerClearPresetChannel(connections[conn_id], x0);
	pthread_mutex_unlock(parent_lock);
}

void call_vTunerGetChildNodes(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	char x1[30];

	printf("Calling vTunerGetChildNodes\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("vTunerUrl: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("vTunerBackupUrl: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }

	df_vTunerGetChildNodes(connections[conn_id], x0, x1, get_search_rows, print_vTunerGetChildNodes, (void*)parent_lock);}

void call_vTunerGetLastPlayed(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling vTunerGetLastPlayed\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_vTunerGetLastPlayed(connections[conn_id], get_search_rows, print_vTunerGetLastPlayed, (void*)parent_lock);}

void call_vTunerGetMostPlayed(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling vTunerGetMostPlayed\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_vTunerGetMostPlayed(connections[conn_id], get_search_rows, print_vTunerGetMostPlayed, (void*)parent_lock);}

void call_vTunerGetNodeFromPlayedUrl(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];

	printf("Calling vTunerGetNodeFromPlayedUrl\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("URLPlayed: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }

	df_vTunerGetNodeFromPlayedUrl(connections[conn_id], x0, get_search_rows, print_vTunerGetNodeFromPlayedUrl, (void*)parent_lock);}

void call_vTunerGetPresetChannels(pthread_mutex_t *parent_lock) {
	int conn_id;

	printf("Calling vTunerGetPresetChannels\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);

	df_vTunerGetPresetChannels(connections[conn_id], get_search_rows, print_vTunerGetPresetChannels, (void*)parent_lock);}

void call_vTunerLookupById(pthread_mutex_t *parent_lock) {
	int conn_id;
	char x0[30];
	int x1;

	printf("Calling vTunerLookupById\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("vTunerId: ");
	scanf("%s", x0);
	if (x0[0] == '-') { x0[0] = '\0'; }
	printf("vTunerLookupType: ");
	scanf("%d", &x1);

	df_vTunerLookupById(connections[conn_id], x0, x1, get_search_rows, print_vTunerLookupById, (void*)parent_lock);}

void call_vTunerPlayById(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	char x2[30];



	printf("Calling vTunerPlayById\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Replace: ");
	scanf("%d", &x1);
	printf("Address: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_vTunerPlayById(connections[conn_id], x0, x1, x2, print_vTunerPlayById, (void*)parent_lock);}

void call_vTunerPlayByIds(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	int x1;
	char x2[30];



	printf("Calling vTunerPlayByIds\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("RoomID: ");
	scanf("%d", &x0);
	printf("Replace: ");
	scanf("%d", &x1);
	printf("Address: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_vTunerPlayByIds(connections[conn_id], x0, x1, x2, print_vTunerPlayByIds, (void*)parent_lock);}

void call_vTunerSetPresetChannel(pthread_mutex_t *parent_lock) {
	int conn_id;
	int x0;
	char x1[30];
	char x2[30];



	printf("Calling vTunerSetPresetChannel\n");

	printf("Connection: ");
	scanf("%d", &conn_id); check_connection(conn_id);
	printf("ChannelNumber: ");
	scanf("%d", &x0);
	printf("VTunerID: ");
	scanf("%s", x1);
	if (x1[0] == '-') { x1[0] = '\0'; }
	printf("ChannelName: ");
	scanf("%s", x2);
	if (x2[0] == '-') { x2[0] = '\0'; }

	df_vTunerSetPresetChannel(connections[conn_id], x0, x1, x2, print_vTunerSetPresetChannel, (void*)parent_lock);}







// list entrypoints
static void list_entrypoint(pthread_mutex_t *parent_lock);
static void test_entrypoint(pthread_mutex_t *parent_lock);
static void rget_entrypoint(pthread_mutex_t *parent_lock);
static void call_entrypoint(pthread_mutex_t *parent_lock);


// command functions
static void discover(pthread_mutex_t *parent_lock);
static void connect(pthread_mutex_t *parent_lock);
static void disconnect(pthread_mutex_t *parent_lock);

static void list_connections(pthread_mutex_t *parent_lock);

static void rget_trackposition(pthread_mutex_t *parent_lock);
static void rget_detailedtrackinfo(pthread_mutex_t *parent_lock);
static void rget_albumartist(pthread_mutex_t *parent_lock);
static void rget_lastplayererror(pthread_mutex_t *parent_lock);
static void rget_playerstatus(pthread_mutex_t *parent_lock);
static void rget_playingchecksum(pthread_mutex_t *parent_lock);
static void rget_repeat(pthread_mutex_t *parent_lock);
static void rget_shuffle(pthread_mutex_t *parent_lock);
static void rget_trackname(pthread_mutex_t *parent_lock);
static void rget_clear(pthread_mutex_t *parent_lock);




struct command_option {
	char *label;
	void (*function)(pthread_mutex_t*);
};

static void process_menu(char *ident, struct command_option *options, int num, pthread_mutex_t *parent_lock);
static int num_options = 8;
static struct command_option options[8] = { { "discover", discover },
											{ "connect", connect },
											{ "disconnect", disconnect },
											{ "tests", test_entrypoint },
											{ "list", list_entrypoint },
											{ "rget", rget_entrypoint },
											{ "call", call_entrypoint },
											{ "quit", NULL }};

static int num_list_options = 3;
static struct command_option list_options[3] = { { "connections", list_connections }, 
												 { "threads", NULL },
												 { "regex", NULL }};

static int num_test_options = 5;
static struct command_option test_options[5] = { { "main", main_conn_test },
												 { "func", main_func_test },
												 { "rget", rget_test },
												 { "misc", misc_test },
                         { "search", search_test } };

static int num_rget_options = 10;
static struct command_option rget_options[10] = { { "trackposition", rget_trackposition }, 
												  { "detailedtrackinfo", rget_detailedtrackinfo }, 
												  { "albumartist", rget_albumartist }, 
												  { "lastplayererror", rget_lastplayererror },
												  { "playerstatus", rget_playerstatus },
												  { "playingchecksum", rget_playingchecksum },
												  { "repeat", rget_repeat },
												  { "shuffle", rget_shuffle },
											      { "trackname", rget_trackname },
												  { "clear", rget_clear }};


static int num_call_options = 374;
static struct command_option call_options[374] = { { "ActivateExternalStorage", call_ActivateExternalStorage }, 
{ "AddAlbumsToUserPlaylist", call_AddAlbumsToUserPlaylist }, 
{ "AddExternalStorage", call_AddExternalStorage }, 
{ "AddNewBackupJob", call_AddNewBackupJob }, 
{ "AddNewDrive", call_AddNewDrive }, 
{ "AddNewGenre", call_AddNewGenre }, 
{ "AddNewLinkedRoom", call_AddNewLinkedRoom }, 
{ "AddNewRoom", call_AddNewRoom }, 
{ "AddNewSubGenre", call_AddNewSubGenre }, 
{ "AddTracksToUserPlaylist", call_AddTracksToUserPlaylist }, 
{ "AdvancedSearch", call_AdvancedSearch }, 
{ "BackupDrive", call_BackupDrive }, 
{ "BulkCDLookup", call_BulkCDLookup }, 
{ "BulkCDLookupEx", call_BulkCDLookupEx }, 
{ "CDLookupCancel", call_CDLookupCancel }, 
{ "CDLookupGetQueue", call_CDLookupGetQueue }, 
{ "CDLookupGetStatus", call_CDLookupGetStatus }, 
{ "CancelRipping", call_CancelRipping }, 
{ "ChangeAlbumSubGenre", call_ChangeAlbumSubGenre }, 
{ "ChangeCDDBSubGenreAssociation", call_ChangeCDDBSubGenreAssociation }, 
{ "ChangeNetworkAutoIP", call_ChangeNetworkAutoIP }, 
{ "ChangeNetworkDhcp", call_ChangeNetworkDhcp }, 
{ "ChangeNetworkMachineName", call_ChangeNetworkMachineName }, 
{ "ChangeNetworkStatic", call_ChangeNetworkStatic }, 
{ "ChangeNetworkWorkgroup", call_ChangeNetworkWorkgroup }, 
{ "ChangeSystemSerialNumber", call_ChangeSystemSerialNumber }, 
{ "ChangeTrackOrdinal", call_ChangeTrackOrdinal }, 
{ "CheckCoverImage", call_CheckCoverImage }, 
{ "ClearAllPlaying", call_ClearAllPlaying }, 
{ "ClearDownloadFolder", call_ClearDownloadFolder }, 
{ "ClearPlaylist", call_ClearPlaylist }, 
{ "CompactGenreOrdinals", call_CompactGenreOrdinals }, 
{ "ComplexSearchCountAlbums", call_ComplexSearchCountAlbums }, 
{ "ComplexSearchCountArtists", call_ComplexSearchCountArtists }, 
{ "ComplexSearchCountContributors", call_ComplexSearchCountContributors }, 
{ "ComplexSearchCountTracks", call_ComplexSearchCountTracks }, 
{ "ComplexSearchGetAlbums", call_ComplexSearchGetAlbums }, 
{ "ComplexSearchGetArtists", call_ComplexSearchGetArtists }, 
{ "ComplexSearchGetContributors", call_ComplexSearchGetContributors }, 
{ "ComplexSearchGetTracks", call_ComplexSearchGetTracks }, 
{ "CountAlbums", call_CountAlbums }, 
{ "CountAlbumsForArtist", call_CountAlbumsForArtist }, 
{ "CountAlbumsForArtistForDevice", call_CountAlbumsForArtistForDevice }, 
{ "CountAlbumsForArtistForServer", call_CountAlbumsForArtistForServer }, 
{ "CountAlbumsForArtistForShare", call_CountAlbumsForArtistForShare }, 
{ "CountAlbumsForDevice", call_CountAlbumsForDevice }, 
{ "CountAlbumsForServer", call_CountAlbumsForServer }, 
{ "CountAlbumsForShare", call_CountAlbumsForShare }, 
{ "CountArtists", call_CountArtists }, 
{ "CountArtistsForDevice", call_CountArtistsForDevice }, 
{ "CountArtistsForServer", call_CountArtistsForServer }, 
{ "CountArtistsForShare", call_CountArtistsForShare }, 
{ "CountDevices", call_CountDevices }, 
{ "CountGenres", call_CountGenres }, 
{ "CountPlaylistsForSubGenre", call_CountPlaylistsForSubGenre }, 
{ "CountPlaylistsForSubGenreForDevice", call_CountPlaylistsForSubGenreForDevice }, 
{ "CountPlaylistsForSubGenreForServer", call_CountPlaylistsForSubGenreForServer }, 
{ "CountPlaylistsForSubGenreForShare", call_CountPlaylistsForSubGenreForShare }, 
{ "CountShares", call_CountShares }, 
{ "CountSubGenresForDevice", call_CountSubGenresForDevice }, 
{ "CountSubGenresForGenre", call_CountSubGenresForGenre }, 
{ "CountSubGenresForServer", call_CountSubGenresForServer }, 
{ "CountSubGenresForShare", call_CountSubGenresForShare }, 
{ "CountTracksAll", call_CountTracksAll }, 
{ "CountTracksForDevice", call_CountTracksForDevice }, 
{ "CountTracksForPlaylist", call_CountTracksForPlaylist }, 
{ "CountTracksForServer", call_CountTracksForServer }, 
{ "CountTracksForShare", call_CountTracksForShare }, 
{ "CountUserPlaylists", call_CountUserPlaylists }, 
{ "CountUserPlaylistsForDevice", call_CountUserPlaylistsForDevice }, 
{ "CountUserPlaylistsForServer", call_CountUserPlaylistsForServer }, 
{ "CountUserPlaylistsForShare", call_CountUserPlaylistsForShare }, 
{ "CreatePlaylist", call_CreatePlaylist }, 
{ "CreateRandomPlaylist", call_CreateRandomPlaylist }, 
{ "CreateRandomPlaylistEx", call_CreateRandomPlaylistEx }, 
{ "DeleteAlbum", call_DeleteAlbum }, 
{ "DeleteBackupJob", call_DeleteBackupJob }, 
{ "DeleteDevice", call_DeleteDevice }, 
{ "DeleteDrive", call_DeleteDrive }, 
{ "DeleteGenre", call_DeleteGenre }, 
{ "DeleteLinkedRoom", call_DeleteLinkedRoom }, 
{ "DeleteOutputChannel", call_DeleteOutputChannel }, 
{ "DeleteRoom", call_DeleteRoom }, 
{ "DeleteSubGenre", call_DeleteSubGenre }, 
{ "DeleteTrack", call_DeleteTrack }, 
{ "DemoteMusicStoreToShare", call_DemoteMusicStoreToShare }, 
{ "DeviceChecksum", call_DeviceChecksum }, 
{ "DisableField", call_DisableField }, 
{ "DisconnectDevice", call_DisconnectDevice }, 
{ "EjectCD", call_EjectCD }, 
{ "EmptyRecycleBin", call_EmptyRecycleBin }, 
{ "EmptyRipShare", call_EmptyRipShare }, 
{ "EnableField", call_EnableField }, 
{ "ExternalStorageCancelScan", call_ExternalStorageCancelScan }, 
{ "FastForward", call_FastForward }, 
{ "FastRewind", call_FastRewind }, 
{ "FindAllRooms", call_FindAllRooms }, 
{ "FindNewRooms", call_FindNewRooms }, 
{ "ForceDBRebuild", call_ForceDBRebuild }, 
{ "ForceGenrePlaylistBackup", call_ForceGenrePlaylistBackup }, 
{ "ForceGenrePlaylistRestore", call_ForceGenrePlaylistRestore }, 
{ "ForceHostUpgrade", call_ForceHostUpgrade }, 
{ "GetAdvancedStatus", call_GetAdvancedStatus }, 
{ "GetAlbumArtist", call_GetAlbumArtist }, 
{ "GetAlbumDetails", call_GetAlbumDetails }, 
{ "GetAlbums", call_GetAlbums }, 
{ "GetAlbumsForArtists", call_GetAlbumsForArtists }, 
{ "GetAlbumsForArtistsForDevice", call_GetAlbumsForArtistsForDevice }, 
{ "GetAlbumsForArtistsForServer", call_GetAlbumsForArtistsForServer }, 
{ "GetAlbumsForArtistsForShare", call_GetAlbumsForArtistsForShare }, 
{ "GetAlbumsForArtistsInGenre", call_GetAlbumsForArtistsInGenre }, 
{ "GetAlbumsForArtistsInSubGenre", call_GetAlbumsForArtistsInSubGenre }, 
{ "GetAlbumsForDeletion", call_GetAlbumsForDeletion }, 
{ "GetAlbumsForDevice", call_GetAlbumsForDevice }, 
{ "GetAlbumsForPlaylist", call_GetAlbumsForPlaylist }, 
{ "GetAlbumsForServer", call_GetAlbumsForServer }, 
{ "GetAlbumsForShare", call_GetAlbumsForShare }, 
{ "GetAlbumsForStore", call_GetAlbumsForStore }, 
{ "GetAlbumsOtherInfo", call_GetAlbumsOtherInfo }, 
{ "GetAlbumsOtherInfoAll", call_GetAlbumsOtherInfoAll }, 
{ "GetAlbumsOtherInfoForDevice", call_GetAlbumsOtherInfoForDevice }, 
{ "GetAlbumsOtherInfoForServer", call_GetAlbumsOtherInfoForServer }, 
{ "GetAlbumsOtherInfoForShare", call_GetAlbumsOtherInfoForShare }, 
{ "GetAlbumsSearchAlbumArtist", call_GetAlbumsSearchAlbumArtist }, 
{ "GetAlbumsWithAlbumLookupMessages", call_GetAlbumsWithAlbumLookupMessages }, 
{ "GetAlertDetails", call_GetAlertDetails }, 
{ "GetArtistDetails", call_GetArtistDetails }, 
{ "GetArtists", call_GetArtists }, 
{ "GetArtistsForDevice", call_GetArtistsForDevice }, 
{ "GetArtistsForServer", call_GetArtistsForServer }, 
{ "GetArtistsForShare", call_GetArtistsForShare }, 
{ "GetArtistsInGenre", call_GetArtistsInGenre }, 
{ "GetArtistsInSubGenre", call_GetArtistsInSubGenre }, 
{ "GetAvailableValues", call_GetAvailableValues }, 
{ "GetBackupJobDetail", call_GetBackupJobDetail }, 
{ "GetBackupJobs", call_GetBackupJobs }, 
{ "GetBackupLogDetail", call_GetBackupLogDetail }, 
{ "GetBackupLogs", call_GetBackupLogs }, 
{ "GetBackupStatus", call_GetBackupStatus }, 
{ "GetCDDBGenres", call_GetCDDBGenres }, 
{ "GetComponentVersions", call_GetComponentVersions }, 
{ "GetCount", call_GetCount }, 
{ "GetCurOp", call_GetCurOp }, 
{ "GetCurrentPlayList", call_GetCurrentPlayList }, 
{ "GetCurrentPlaylistEx", call_GetCurrentPlaylistEx }, 
{ "GetDeviceDetails", call_GetDeviceDetails }, 
{ "GetDevices", call_GetDevices }, 
{ "GetDriveDetail", call_GetDriveDetail }, 
{ "GetEncodingQueue", call_GetEncodingQueue }, 
{ "GetEncodingStatus", call_GetEncodingStatus }, 
{ "GetExtAlbumCredits", call_GetExtAlbumCredits }, 
{ "GetExtAlbumsByContributor", call_GetExtAlbumsByContributor }, 
{ "GetExtAlbumsByContributorForDevice", call_GetExtAlbumsByContributorForDevice }, 
{ "GetExtAlbumsByContributorForServer", call_GetExtAlbumsByContributorForServer }, 
{ "GetExtAlbumsByContributorForShare", call_GetExtAlbumsByContributorForShare }, 
{ "GetExtAlbumsByCredit", call_GetExtAlbumsByCredit }, 
{ "GetExtAlbumsByWork", call_GetExtAlbumsByWork }, 
{ "GetExtAlbumsInfo", call_GetExtAlbumsInfo }, 
{ "GetExtAlbumsSearchPeople", call_GetExtAlbumsSearchPeople }, 
{ "GetExtContributorDetails", call_GetExtContributorDetails }, 
{ "GetExtContributors", call_GetExtContributors }, 
{ "GetExtContributorsForAlbum", call_GetExtContributorsForAlbum }, 
{ "GetExtContributorsForDevice", call_GetExtContributorsForDevice }, 
{ "GetExtContributorsForServer", call_GetExtContributorsForServer }, 
{ "GetExtContributorsForShare", call_GetExtContributorsForShare }, 
{ "GetExtCountAlbumsByContributor", call_GetExtCountAlbumsByContributor }, 
{ "GetExtCountAlbumsByContributorForDevice", call_GetExtCountAlbumsByContributorForDevice }, 
{ "GetExtCountAlbumsByContributorForServer", call_GetExtCountAlbumsByContributorForServer }, 
{ "GetExtCountAlbumsByContributorForShare", call_GetExtCountAlbumsByContributorForShare }, 
{ "GetExtCountContributors", call_GetExtCountContributors }, 
{ "GetExtCountContributorsForDevice", call_GetExtCountContributorsForDevice }, 
{ "GetExtCountContributorsForServer", call_GetExtCountContributorsForServer }, 
{ "GetExtCountContributorsForShare", call_GetExtCountContributorsForShare }, 
{ "GetExtTrackContributors", call_GetExtTrackContributors }, 
{ "GetExtTracksByContributor", call_GetExtTracksByContributor }, 
{ "GetExtTracksByContributorForDevice", call_GetExtTracksByContributorForDevice }, 
{ "GetExtTracksByContributorForServer", call_GetExtTracksByContributorForServer }, 
{ "GetExtTracksByContributorForShare", call_GetExtTracksByContributorForShare }, 
{ "GetExtTracksByWork", call_GetExtTracksByWork }, 
{ "GetExtTracksInfo", call_GetExtTracksInfo }, 
{ "GetExtWorks", call_GetExtWorks }, 
{ "GetExternalStorageDetail", call_GetExternalStorageDetail }, 
{ "GetExternalStorages", call_GetExternalStorages }, 
{ "GetFileSystemDriveDetail", call_GetFileSystemDriveDetail }, 
{ "GetGenreDetail", call_GetGenreDetail }, 
{ "GetGenres", call_GetGenres }, 
{ "GetGenresSubGenres", call_GetGenresSubGenres }, 
{ "GetHostDetails", call_GetHostDetails }, 
{ "GetLastError", call_GetLastError }, 
{ "GetLatestPlayedAlbums", call_GetLatestPlayedAlbums }, 
{ "GetLibraryCheckSum", call_GetLibraryCheckSum }, 
{ "GetLinkedRoomDetail", call_GetLinkedRoomDetail }, 
{ "GetLinkedRooms", call_GetLinkedRooms }, 
{ "GetNetworkActiveAdapters", call_GetNetworkActiveAdapters }, 
{ "GetNetworkWorkgroup", call_GetNetworkWorkgroup }, 
{ "GetNewestAlbums", call_GetNewestAlbums }, 
{ "GetNonLinkedRooms", call_GetNonLinkedRooms }, 
{ "GetOperationActivity", call_GetOperationActivity }, 
{ "GetOutputChannels", call_GetOutputChannels }, 
{ "GetOutputDevices", call_GetOutputDevices }, 
{ "GetPlayListsByLetter", call_GetPlayListsByLetter }, 
{ "GetPlayerInstances", call_GetPlayerInstances }, 
{ "GetPlayerStatus", call_GetPlayerStatus }, 
{ "GetPlayerVersion", call_GetPlayerVersion }, 
{ "GetPlaylistsForGenre", call_GetPlaylistsForGenre }, 
{ "GetPlaylistsForSubGenre", call_GetPlaylistsForSubGenre }, 
{ "GetPlaylistsForSubGenreForDevice", call_GetPlaylistsForSubGenreForDevice }, 
{ "GetPlaylistsForSubGenreForServer", call_GetPlaylistsForSubGenreForServer }, 
{ "GetPlaylistsForSubGenreForShare", call_GetPlaylistsForSubGenreForShare }, 
{ "GetRepeat", call_GetRepeat }, 
{ "GetRipEncSettings", call_GetRipEncSettings }, 
{ "GetRipEncSettingsEx", call_GetRipEncSettingsEx }, 
{ "GetRippingAlerts", call_GetRippingAlerts }, 
{ "GetRippingStatus", call_GetRippingStatus }, 
{ "GetRoomDetail", call_GetRoomDetail }, 
{ "GetRooms", call_GetRooms }, 
{ "GetRoomsWithPlayBack", call_GetRoomsWithPlayBack }, 
{ "GetRoomsWithRipping", call_GetRoomsWithRipping }, 
{ "GetRows", call_GetRows }, 
{ "GetSearchOffset", call_GetSearchOffset }, 
{ "GetSettings", call_GetSettings }, 
{ "GetSettingsEx", call_GetSettingsEx }, 
{ "GetSetupVal", call_GetSetupVal }, 
{ "GetShuffle", call_GetShuffle }, 
{ "GetSingleRipEncSetting", call_GetSingleRipEncSetting }, 
{ "GetSingleSystemSetting", call_GetSingleSystemSetting }, 
{ "GetStatusMessageDetail", call_GetStatusMessageDetail }, 
{ "GetStatusMessages", call_GetStatusMessages }, 
{ "GetStoreDetail", call_GetStoreDetail }, 
{ "GetStores", call_GetStores }, 
{ "GetSubGenreDetail", call_GetSubGenreDetail }, 
{ "GetSubGenresForDevice", call_GetSubGenresForDevice }, 
{ "GetSubGenresForGenre", call_GetSubGenresForGenre }, 
{ "GetSubGenresForServer", call_GetSubGenresForServer }, 
{ "GetSubGenresForShare", call_GetSubGenresForShare }, 
{ "GetSystemDrives", call_GetSystemDrives }, 
{ "GetSystemTime", call_GetSystemTime }, 
{ "GetTopPlayedAlbums", call_GetTopPlayedAlbums }, 
{ "GetTrackCount", call_GetTrackCount }, 
{ "GetTrackDetailsFromPlayer", call_GetTrackDetailsFromPlayer }, 
{ "GetTrackLength", call_GetTrackLength }, 
{ "GetTrackName", call_GetTrackName }, 
{ "GetTrackNum", call_GetTrackNum }, 
{ "GetTrackPosition", call_GetTrackPosition }, 
{ "GetTrackRange", call_GetTrackRange }, 
{ "GetTracksAll", call_GetTracksAll }, 
{ "GetTracksForAlbumInUPL", call_GetTracksForAlbumInUPL }, 
{ "GetTracksForArtist", call_GetTracksForArtist }, 
{ "GetTracksForArtistForDevice", call_GetTracksForArtistForDevice }, 
{ "GetTracksForArtistForServer", call_GetTracksForArtistForServer }, 
{ "GetTracksForArtistForShare", call_GetTracksForArtistForShare }, 
{ "GetTracksForDeletion", call_GetTracksForDeletion }, 
{ "GetTracksForDevice", call_GetTracksForDevice }, 
{ "GetTracksForGenre", call_GetTracksForGenre }, 
{ "GetTracksForNamedEntity", call_GetTracksForNamedEntity }, 
{ "GetTracksForPlaylist", call_GetTracksForPlaylist }, 
{ "GetTracksForServer", call_GetTracksForServer }, 
{ "GetTracksForShare", call_GetTracksForShare }, 
{ "GetTracksForSubGenre", call_GetTracksForSubGenre }, 
{ "GetTracksForSubGenreForDevice", call_GetTracksForSubGenreForDevice }, 
{ "GetTracksForSubGenreForServer", call_GetTracksForSubGenreForServer }, 
{ "GetTracksForSubGenreForShare", call_GetTracksForSubGenreForShare }, 
{ "GetTracksOtherInfo", call_GetTracksOtherInfo }, 
{ "GetTracksSearchName", call_GetTracksSearchName }, 
{ "GetUpnpMediaRenderers", call_GetUpnpMediaRenderers }, 
{ "GetUserPlaylists", call_GetUserPlaylists }, 
{ "GetUserPlaylistsForDevice", call_GetUserPlaylistsForDevice }, 
{ "GetUserPlaylistsForServer", call_GetUserPlaylistsForServer }, 
{ "GetUserPlaylistsForShare", call_GetUserPlaylistsForShare }, 
{ "GetUserStatus", call_GetUserStatus }, 
{ "GetVolume", call_GetVolume }, 
{ "IgnoreExternalStorage", call_IgnoreExternalStorage }, 
{ "IsCDPlaying", call_IsCDPlaying }, 
{ "LookupError", call_LookupError }, 
{ "MasterIpChanged", call_MasterIpChanged }, 
{ "MoveAlbumCancel", call_MoveAlbumCancel }, 
{ "MoveAlbumGetQueue", call_MoveAlbumGetQueue }, 
{ "MoveAlbumGetStatus", call_MoveAlbumGetStatus }, 
{ "MoveAlbumToMusicStore", call_MoveAlbumToMusicStore }, 
{ "NewOutputChannel", call_NewOutputChannel }, 
{ "NextTrack", call_NextTrack }, 
{ "Pause", call_Pause }, 
{ "Play", call_Play }, 
{ "PlayAlbum", call_PlayAlbum }, 
{ "PlayAlbums", call_PlayAlbums }, 
{ "PlayAlbumsFromSearch", call_PlayAlbumsFromSearch }, 
{ "PlayAll", call_PlayAll }, 
{ "PlayArtistAlbum", call_PlayArtistAlbum }, 
{ "PlayLastPlayed", call_PlayLastPlayed }, 
{ "PlayLastRipped", call_PlayLastRipped }, 
{ "PlayMostPopular", call_PlayMostPopular }, 
{ "PlayPlaylist", call_PlayPlaylist }, 
{ "PlayRandom", call_PlayRandom }, 
{ "PlayTrack", call_PlayTrack }, 
{ "PlayTracks", call_PlayTracks }, 
{ "PlayTracksFromSearch", call_PlayTracksFromSearch }, 
{ "PlayUrl", call_PlayUrl }, 
{ "PlayUrls", call_PlayUrls }, 
{ "PrevTrack", call_PrevTrack }, 
{ "ProcessEmbeddedInit", call_ProcessEmbeddedInit }, 
{ "PromoteShareToMusicStore", call_PromoteShareToMusicStore }, 
{ "PurgeImageCache", call_PurgeImageCache }, 
{ "QueryAllPlayback", call_QueryAllPlayback }, 
{ "RandomisePlaylist", call_RandomisePlaylist }, 
{ "ReleaseSerialPort", call_ReleaseSerialPort }, 
{ "RemoveAlbumsFromUserPlaylist", call_RemoveAlbumsFromUserPlaylist }, 
{ "RemoveCoverImage", call_RemoveCoverImage }, 
{ "RemoveExternalStorage", call_RemoveExternalStorage }, 
{ "RemoveOldRooms", call_RemoveOldRooms }, 
{ "RemovePlayerInstance", call_RemovePlayerInstance }, 
{ "RemoveTrack", call_RemoveTrack }, 
{ "RenameAlbum", call_RenameAlbum }, 
{ "RenameArtist", call_RenameArtist }, 
{ "RenamePlaylist", call_RenamePlaylist }, 
{ "RenameTrack", call_RenameTrack }, 
{ "RequestAlbumCover", call_RequestAlbumCover }, 
{ "RescanExternalStorages", call_RescanExternalStorages }, 
{ "RescanMusicStore", call_RescanMusicStore }, 
{ "RestartDevice", call_RestartDevice }, 
{ "RestoreSingleAlbum", call_RestoreSingleAlbum }, 
{ "RestoreSingleTrack", call_RestoreSingleTrack }, 
{ "RoomIpChanged", call_RoomIpChanged }, 
{ "SaveCurrentPlayList", call_SaveCurrentPlayList }, 
{ "SavePlayerInstance", call_SavePlayerInstance }, 
{ "ScanExternalStorage", call_ScanExternalStorage }, 
{ "ScanForExternalStorages", call_ScanForExternalStorages }, 
{ "ServiceMode", call_ServiceMode }, 
{ "SetAlbumLowQuality", call_SetAlbumLowQuality }, 
{ "SetCDDetected", call_SetCDDetected }, 
{ "SetConnOption", call_SetConnOption }, 
{ "SetCoverImage", call_SetCoverImage }, 
{ "SetDriveUsage", call_SetDriveUsage }, 
{ "SetLength", call_SetLength }, 
{ "SetMusicStoreCredentials", call_SetMusicStoreCredentials }, 
{ "SetMusicStorePriority", call_SetMusicStorePriority }, 
{ "SetRepeat", call_SetRepeat }, 
{ "SetRippingStatus", call_SetRippingStatus }, 
{ "SetShuffle", call_SetShuffle }, 
{ "SetTrack", call_SetTrack }, 
{ "SetTrackPosition", call_SetTrackPosition }, 
{ "SetVolume", call_SetVolume }, 
{ "Status", call_Status }, 
{ "Stop", call_Stop }, 
{ "StopBackupDrive", call_StopBackupDrive }, 
{ "ToggleDeviceSync", call_ToggleDeviceSync }, 
{ "UndoUserEdits", call_UndoUserEdits }, 
{ "UpdateBackupJob", call_UpdateBackupJob }, 
{ "UpdateDrive", call_UpdateDrive }, 
{ "UpdateExternalStorage", call_UpdateExternalStorage }, 
{ "UpdateGenre", call_UpdateGenre }, 
{ "UpdateHitCount", call_UpdateHitCount }, 
{ "UpdateLinkedRoom", call_UpdateLinkedRoom }, 
{ "UpdateOutputChannel", call_UpdateOutputChannel }, 
{ "UpdatePlaylist", call_UpdatePlaylist }, 
{ "UpdateRoom", call_UpdateRoom }, 
{ "UpdateSingleRipEncSetting", call_UpdateSingleRipEncSetting }, 
{ "UpdateSingleSystemSetting", call_UpdateSingleSystemSetting }, 
{ "UpdateSubGenre", call_UpdateSubGenre }, 
{ "UploadMessages", call_UploadMessages }, 
{ "Version", call_Version }, 
{ "vTunerAddRemoveFavourite", call_vTunerAddRemoveFavourite }, 
{ "vTunerCheckAvailability", call_vTunerCheckAvailability }, 
{ "vTunerCleanStatistics", call_vTunerCleanStatistics }, 
{ "vTunerClearPresetChannel", call_vTunerClearPresetChannel }, 
{ "vTunerGetChildNodes", call_vTunerGetChildNodes }, 
{ "vTunerGetLastPlayed", call_vTunerGetLastPlayed }, 
{ "vTunerGetMostPlayed", call_vTunerGetMostPlayed }, 
{ "vTunerGetNodeFromPlayedUrl", call_vTunerGetNodeFromPlayedUrl }, 
{ "vTunerGetPresetChannels", call_vTunerGetPresetChannels }, 
{ "vTunerLookupById", call_vTunerLookupById }, 
{ "vTunerPlayById", call_vTunerPlayById }, 
{ "vTunerPlayByIds", call_vTunerPlayByIds }, 
{ "vTunerSetPresetChannel", call_vTunerSetPresetChannel }, 
 { "quit", NULL } };




static void list_entrypoint(pthread_mutex_t *parent_lock) {
	process_menu("list", list_options, num_list_options, parent_lock);
}
static void test_entrypoint(pthread_mutex_t *parent_lock) {
	process_menu("test", test_options, num_test_options, parent_lock);
}
static void rget_entrypoint(pthread_mutex_t *parent_lock) {
	process_menu("rget", rget_options, num_rget_options, parent_lock);
}
static void call_entrypoint(pthread_mutex_t *parent_lock) {
	process_menu("call", call_options, num_call_options, parent_lock);
}



static void discover_handler(df_server *servers, void *context) {
	df_server *curr;
	
	printf("Done. Found:\n");
	
	curr = servers;
	if (curr == NULL) printf("No servers found.\n");
	else {
		while (curr!=NULL) {
			printf("%s - %s [%s]\n", curr->address, curr->name, curr->version);
			curr = curr->next;
		}
	}
	
	pthread_mutex_unlock((pthread_mutex_t*)context);
}

static void discover(pthread_mutex_t *parent_lock) {
	printf("Running discover..."); fflush(stdout);
	df_discover(10, discover_handler, (void*)parent_lock);
}


static void connect(pthread_mutex_t *parent_lock) {
	char ip_address[20];
	
	printf("IP Address: ");
	scanf("%s", &ip_address);
	
	num_connections++; connections = realloc(connections, sizeof(df_connection*) * num_connections);
	connections[num_connections-1] = df_connect(ip_address, 2);
	
	printf("Connected to %s.\n", ip_address);
	
	pthread_mutex_unlock(parent_lock);
}

static void disconnect(pthread_mutex_t *parent_lock) {
	int id;
	printf("Connection: "); scanf("%d", &id); if (!check_connection(id)) { printf("Invalid connection\n"); return; }
	
	df_disconnect(connections[id]);
	
	printf("Disconnect from connection %d\n", id);
	
	pthread_mutex_unlock(parent_lock);
}









static void list_connections(pthread_mutex_t *parent_lock) {
	int i;
	
	printf("Open connections:\n");
	for (i = 0; i < num_connections; i++) {
		printf("[%d] %s\n", i, connections[i]->label);
	}
	
	pthread_mutex_unlock(parent_lock);
}







static void rget_trackposition_callback(int room, df_time *time, void *context) {
	printf("%s TrackPosition: %d:%d:%d\n", (char*)context, time->hours, time->minutes, time->seconds);
}

static void rget_trackposition(pthread_mutex_t *parent_lock) {
	int id, room;
	printf("Connection: "); scanf("%d", &id); if (!check_connection(id)) { printf("Invalid connection\n"); return; }
	printf("Room: "); scanf("%d", &room);
	
	dfrget_trackposition(connections[id], room, rget_trackposition_callback, connections[id]->label);
	
	printf("Recieving TrackPosition RGet.\n");
	pthread_mutex_unlock(parent_lock);
}



static void rget_detailedtrackinfo_callback(int room, df_detailedtrack *dt, void *context) {
	printf("%s DetailedTrackInfo: %s - %s - %s\n", (char*)context, dt->artistname, dt->albumname, dt->name);
}

static void rget_detailedtrackinfo(pthread_mutex_t *parent_lock) {
	int id, room;
	printf("Connection: "); scanf("%d", &id); if (!check_connection(id)) { printf("Invalid connection\n"); return; }
	printf("Room: "); scanf("%d", &room);
	
	dfrget_detailedtrackinfo(connections[id], room, rget_detailedtrackinfo_callback, connections[id]->label);
	
	printf("Recieving DetailedTrackInfo RGet.\n");
	pthread_mutex_unlock(parent_lock);
}




static void rget_albumartist_callback(int room, df_albumartist *aa, void *context) {
	printf("%s AlbumArtist: %s - %s\n", (char*)context, aa->Artist, aa->Album);
}

static void rget_albumartist(pthread_mutex_t *parent_lock) {
	int id, room;
	printf("Connection: "); scanf("%d", &id); if (!check_connection(id)) { printf("Invalid connection\n"); return; }
	printf("Room: "); scanf("%d", &room);
	
	dfrget_albumartist(connections[id], room, rget_albumartist_callback, connections[id]->label);
	
	printf("Recieving AlbumArtist RGet.\n");
	pthread_mutex_unlock(parent_lock);
}



static void rget_lastplayererror_callback(int room, char *lpe, void *context) {
	printf("%s LastPlayerError: %s\n", (char*)context, lpe);
}

static void rget_lastplayererror(pthread_mutex_t *parent_lock) {
	int id, room;
	printf("Connection: "); scanf("%d", &id); if (!check_connection(id)) { printf("Invalid connection\n"); return; }
	printf("Room: "); scanf("%d", &room);
	
	dfrget_lastplayererror(connections[id], room, rget_lastplayererror_callback, connections[id]->label);
	
	printf("Recieving LastPlayerError RGet.\n");
	pthread_mutex_unlock(parent_lock);
}



static void rget_playerstatus_callback(int room, char *lpe, void *context) {
	printf("%s PlayerStatus: %s\n", (char*)context, lpe);
}

static void rget_playerstatus(pthread_mutex_t *parent_lock) {
	int id, room;
	printf("Connection: "); scanf("%d", &id); if (!check_connection(id)) { printf("Invalid connection\n"); return; }
	printf("Room: "); scanf("%d", &room);
	
	dfrget_playerstatus(connections[id], room, rget_playerstatus_callback, connections[id]->label);
	
	printf("Recieving PlayerStatus RGet.\n");
	pthread_mutex_unlock(parent_lock);
}



static void rget_playingchecksum_callback(int room, char *lpe, void *context) {
	printf("%s PlayingChecksum: %s\n", (char*)context, lpe);
}

static void rget_playingchecksum(pthread_mutex_t *parent_lock) {
	int id, room;
	printf("Connection: "); scanf("%d", &id); if (!check_connection(id)) { printf("Invalid connection\n"); return; }
	printf("Room: "); scanf("%d", &room);
	
	dfrget_playingchecksum(connections[id], room, rget_playingchecksum_callback, connections[id]->label);
	
	printf("Recieving PlayingChecksum RGet.\n");
	pthread_mutex_unlock(parent_lock);
}



static void rget_repeat_callback(int room, int i, void *context) {
	printf("%s Repeat: %d\n", (char*)context, i);
}

static void rget_repeat(pthread_mutex_t *parent_lock) {
	int id, room;
	printf("Connection: "); scanf("%d", &id); if (!check_connection(id)) { printf("Invalid connection\n"); return; }
	printf("Room: "); scanf("%d", &room);
	
	dfrget_repeat(connections[id], room, rget_repeat_callback, connections[id]->label);
	
	printf("Recieving Repeat RGet.\n");
	pthread_mutex_unlock(parent_lock);
}



static void rget_shuffle_callback(int room, int i, void *context) {
	printf("%s Shuffle: %d\n", (char*)context, i);
}

static void rget_shuffle(pthread_mutex_t *parent_lock) {
	int id, room;
	printf("Connection: "); scanf("%d", &id); if (!check_connection(id)) { printf("Invalid connection\n"); return; }
	printf("Room: "); scanf("%d", &room);
	
	dfrget_shuffle(connections[id], room, rget_shuffle_callback, connections[id]->label);
	
	printf("Recieving Shuffle RGet.\n");
	pthread_mutex_unlock(parent_lock);
}



static void rget_trackname_callback(int room, df_trackname *tn, void *context) {
	printf("%s TrackName: %s\n", (char*)context, tn->name);
}

static void rget_trackname(pthread_mutex_t *parent_lock) {
	int id, room;
	printf("Connection: "); scanf("%d", &id); if (!check_connection(id)) { printf("Invalid connection\n"); return; }
	printf("Room: "); scanf("%d", &room);
	
	dfrget_trackname(connections[id], room, rget_trackname_callback, connections[id]->label);
	
	printf("Recieving TrackName RGet.\n");
	pthread_mutex_unlock(parent_lock);
}







static void rget_clear(pthread_mutex_t *parent_lock) {
	int id, room;
	printf("Connection: "); scanf("%d", &id); if (!check_connection(id)) { printf("Invalid connection\n"); return; }
	printf("Room: "); scanf("%d", &room);
	
	dfrget_clearcommands(connections[id], room);
	
	printf("Cleared RGets for room.\n");
	pthread_mutex_unlock(parent_lock);
}














static void process_menu(char *ident, struct command_option *options, int num, pthread_mutex_t *parent_lock) {
	char command[30];
	int processed, is_running, i;
	pthread_mutex_t my_lock;
	
	pthread_mutex_init(&my_lock, 0);
	
	is_running = 1;
	while (is_running) {
		pthread_mutex_lock(&my_lock);
		
		printf("%s> ", ident);
		scanf("%s", &command);
		
		if (strcmp(command, "..") == 0) {
			is_running = 0;
			pthread_mutex_unlock(&my_lock);
		} else if (strcmp(command, "?") == 0) {
			// list commands
			for (i = 0; i < num; i++) {
				printf("%s\n", options[i].label);
			}
			pthread_mutex_unlock(&my_lock);
		} else {
			// parse and forward
			processed = 0;
			for (i = 0; i < num; i++) {
				if (strcmp(command, options[i].label) == 0) {
					if (options[i].function != NULL) { options[i].function(&my_lock); }
					else { is_running = 0; pthread_mutex_unlock(&my_lock); }
					processed = 1; break;
				}
			}
			if (!processed) { printf("Unknown command.\n"); pthread_mutex_unlock(&my_lock); }
		}
	}
	
	if (parent_lock != NULL) pthread_mutex_unlock(parent_lock);
	
}


int main(int argc, char *argv[]) {
	
	printf("DigiFi Multi-connect test\n\n");
	
	// init the system
	df_init();
	
	process_menu("", options, num_options, NULL);
	
	
	return 0;
}