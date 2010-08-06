/*
 *  commands.c
 *  libdigifi.new
 *
 *  Created by Tom Booth on 09/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "commands.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "comm_out.h"
#include "allocator.h"
#include "formatting.h"
#include "debugging.h"


struct call_holder {
	void (*callback)(void);
	void *context;
};

static void row_handler(out_request *request, out_response *response, int num, void *context);

static void pull_rows(out_request *request, out_response *response, int num, void *context) {
	int search_num = 0;
	int row_count = 0;
	char *call_name;
	regex_result *rx;
	
	if (response != NULL) {
		// get the searchnum and row count
		rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&search_num);
		sscanf(rx->subexps[rx->num_subexps-1].value,"%d",&row_count);
		call_name = strdup(rx->subexps[1].value);
		
		if (row_count < 1) {
			// if there are no rows to return
		} else {	
			// if there are rows
			int count = (row_count < request->requested_count ? row_count : request->requested_count);
			DFDEBUG("Pulling rows for request [%p] on %d search_num: %d response: %s maybe_search: %s", request, request->socket->fd, search_num, response->result->result->value, rx->subexps[2].value);
			comm_send_via_socket(request->socket, call_name, count, count, row_handler, context, "[GetRows %d 1 %d]", search_num, count);
		}
		
		free(call_name);
	}
	
	allocator_return(search_num);
}


static char* dfdate_to_string(df_date date) {
	char *datebuffer;
	
	datebuffer = malloc(sizeof(char) * 16);
	
	snprintf(datebuffer, 16, "%u-%u-%u", date.year, date.month, date.day);
	
	return datebuffer;
}

static char* dftime_to_string(df_time time) {
	char *timebuffer;
	
	timebuffer = malloc(sizeof(char) * 16);
	
	snprintf(timebuffer, 16, "%u:%u:%u", time.hours, time.minutes, time.seconds);
	
	return timebuffer;
}




// Generated prototypes
static void ActivateExternalStorage_handler(out_request *request, out_response *response, int num, void* context);
static void AddAlbumsToUserPlaylist_handler(out_request *request, out_response *response, int num, void* context);
static void AddExternalStorage_handler(out_request *request, out_response *response, int num, void* context);
static void AddNewBackupJob_handler(out_request *request, out_response *response, int num, void* context);
static void AddNewDrive_handler(out_request *request, out_response *response, int num, void* context);
static void AddNewGenre_handler(out_request *request, out_response *response, int num, void* context);
static void AddNewLinkedRoom_handler(out_request *request, out_response *response, int num, void* context);
static void AddNewRoom_handler(out_request *request, out_response *response, int num, void* context);
static void AddNewSubGenre_handler(out_request *request, out_response *response, int num, void* context);
static void AddTracksToUserPlaylist_handler(out_request *request, out_response *response, int num, void* context);
static void AdvancedSearch_handler(out_request *request, out_response *response, int num, void* context);
static void BackupDrive_handler(out_request *request, out_response *response, int num, void* context);
static void BulkCDLookup_handler(out_request *request, out_response *response, int num, void* context);
static void BulkCDLookupEx_handler(out_request *request, out_response *response, int num, void* context);
static void CDLookupGetQueue_handler(out_request *request, out_response *response, int num, void* context);
static void CDLookupGetStatus_handler(out_request *request, out_response *response, int num, void* context);
static void CancelRipping_handler(out_request *request, out_response *response, int num, void* context);
static void ChangeAlbumSubGenre_handler(out_request *request, out_response *response, int num, void* context);
static void ChangeNetworkAutoIP_handler(out_request *request, out_response *response, int num, void* context);
static void ChangeNetworkDhcp_handler(out_request *request, out_response *response, int num, void* context);
static void ChangeNetworkMachineName_handler(out_request *request, out_response *response, int num, void* context);
static void ChangeNetworkStatic_handler(out_request *request, out_response *response, int num, void* context);
static void ChangeNetworkWorkgroup_handler(out_request *request, out_response *response, int num, void* context);
static void ChangeSystemSerialNumber_handler(out_request *request, out_response *response, int num, void* context);
static void ChangeTrackOrdinal_handler(out_request *request, out_response *response, int num, void* context);
static void CheckCoverImage_handler(out_request *request, out_response *response, int num, void* context);
static void CompactGenreOrdinals_handler(out_request *request, out_response *response, int num, void* context);
static void ComplexSearchCountAlbums_handler(out_request *request, out_response *response, int num, void* context);
static void ComplexSearchCountArtists_handler(out_request *request, out_response *response, int num, void* context);
static void ComplexSearchCountContributors_handler(out_request *request, out_response *response, int num, void* context);
static void ComplexSearchCountTracks_handler(out_request *request, out_response *response, int num, void* context);
static void ComplexSearchGetAlbums_handler(out_request *request, out_response *response, int num, void* context);
static void ComplexSearchGetArtists_handler(out_request *request, out_response *response, int num, void* context);
static void ComplexSearchGetContributors_handler(out_request *request, out_response *response, int num, void* context);
static void ComplexSearchGetTracks_handler(out_request *request, out_response *response, int num, void* context);
static void CountAlbums_handler(out_request *request, out_response *response, int num, void* context);
static void CountAlbumsForArtist_handler(out_request *request, out_response *response, int num, void* context);
static void CountAlbumsForArtistForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void CountAlbumsForArtistForServer_handler(out_request *request, out_response *response, int num, void* context);
static void CountAlbumsForArtistForShare_handler(out_request *request, out_response *response, int num, void* context);
static void CountAlbumsForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void CountAlbumsForServer_handler(out_request *request, out_response *response, int num, void* context);
static void CountAlbumsForShare_handler(out_request *request, out_response *response, int num, void* context);
static void CountArtists_handler(out_request *request, out_response *response, int num, void* context);
static void CountArtistsForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void CountArtistsForServer_handler(out_request *request, out_response *response, int num, void* context);
static void CountArtistsForShare_handler(out_request *request, out_response *response, int num, void* context);
static void CountDevices_handler(out_request *request, out_response *response, int num, void* context);
static void CountGenres_handler(out_request *request, out_response *response, int num, void* context);
static void CountPlaylistsForSubGenre_handler(out_request *request, out_response *response, int num, void* context);
static void CountPlaylistsForSubGenreForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void CountPlaylistsForSubGenreForServer_handler(out_request *request, out_response *response, int num, void* context);
static void CountPlaylistsForSubGenreForShare_handler(out_request *request, out_response *response, int num, void* context);
static void CountShares_handler(out_request *request, out_response *response, int num, void* context);
static void CountSubGenresForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void CountSubGenresForGenre_handler(out_request *request, out_response *response, int num, void* context);
static void CountSubGenresForServer_handler(out_request *request, out_response *response, int num, void* context);
static void CountSubGenresForShare_handler(out_request *request, out_response *response, int num, void* context);
static void CountTracksAll_handler(out_request *request, out_response *response, int num, void* context);
static void CountTracksForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void CountTracksForPlaylist_handler(out_request *request, out_response *response, int num, void* context);
static void CountTracksForServer_handler(out_request *request, out_response *response, int num, void* context);
static void CountTracksForShare_handler(out_request *request, out_response *response, int num, void* context);
static void CountUserPlaylists_handler(out_request *request, out_response *response, int num, void* context);
static void CountUserPlaylistsForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void CountUserPlaylistsForServer_handler(out_request *request, out_response *response, int num, void* context);
static void CountUserPlaylistsForShare_handler(out_request *request, out_response *response, int num, void* context);
static void CreatePlaylist_handler(out_request *request, out_response *response, int num, void* context);
static void CreateRandomPlaylist_handler(out_request *request, out_response *response, int num, void* context);
static void CreateRandomPlaylistEx_handler(out_request *request, out_response *response, int num, void* context);
static void DeleteAlbum_handler(out_request *request, out_response *response, int num, void* context);
static void DeleteBackupJob_handler(out_request *request, out_response *response, int num, void* context);
static void DeleteDevice_handler(out_request *request, out_response *response, int num, void* context);
static void DeleteDrive_handler(out_request *request, out_response *response, int num, void* context);
static void DeleteGenre_handler(out_request *request, out_response *response, int num, void* context);
static void DeleteLinkedRoom_handler(out_request *request, out_response *response, int num, void* context);
static void DeleteOutputChannel_handler(out_request *request, out_response *response, int num, void* context);
static void DeleteRoom_handler(out_request *request, out_response *response, int num, void* context);
static void DeleteSubGenre_handler(out_request *request, out_response *response, int num, void* context);
static void DeleteTrack_handler(out_request *request, out_response *response, int num, void* context);
static void DemoteMusicStoreToShare_handler(out_request *request, out_response *response, int num, void* context);
static void DeviceChecksum_handler(out_request *request, out_response *response, int num, void* context);
static void DisconnectDevice_handler(out_request *request, out_response *response, int num, void* context);
static void ExternalStorageCancelScan_handler(out_request *request, out_response *response, int num, void* context);
static void FindAllRooms_handler(out_request *request, out_response *response, int num, void* context);
static void FindNewRooms_handler(out_request *request, out_response *response, int num, void* context);
static void ForceGenrePlaylistBackup_handler(out_request *request, out_response *response, int num, void* context);
static void ForceGenrePlaylistRestore_handler(out_request *request, out_response *response, int num, void* context);
static void GetAdvancedStatus_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbumArtist_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbumDetails_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbums_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbumsForArtists_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbumsForArtistsForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbumsForArtistsForServer_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbumsForArtistsForShare_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbumsForArtistsInGenre_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbumsForArtistsInSubGenre_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbumsForDeletion_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbumsForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbumsForPlaylist_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbumsForServer_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbumsForShare_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbumsForStore_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbumsOtherInfo_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbumsOtherInfoAll_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbumsOtherInfoForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbumsOtherInfoForServer_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbumsOtherInfoForShare_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbumsSearchAlbumArtist_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlbumsWithAlbumLookupMessages_handler(out_request *request, out_response *response, int num, void* context);
static void GetAlertDetails_handler(out_request *request, out_response *response, int num, void* context);
static void GetArtistDetails_handler(out_request *request, out_response *response, int num, void* context);
static void GetArtists_handler(out_request *request, out_response *response, int num, void* context);
static void GetArtistsForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void GetArtistsForServer_handler(out_request *request, out_response *response, int num, void* context);
static void GetArtistsForShare_handler(out_request *request, out_response *response, int num, void* context);
static void GetArtistsInGenre_handler(out_request *request, out_response *response, int num, void* context);
static void GetArtistsInSubGenre_handler(out_request *request, out_response *response, int num, void* context);
static void GetAvailableValues_handler(out_request *request, out_response *response, int num, void* context);
static void GetBackupJobDetail_handler(out_request *request, out_response *response, int num, void* context);
static void GetBackupJobs_handler(out_request *request, out_response *response, int num, void* context);
static void GetBackupLogDetail_handler(out_request *request, out_response *response, int num, void* context);
static void GetBackupLogs_handler(out_request *request, out_response *response, int num, void* context);
static void GetBackupStatus_handler(out_request *request, out_response *response, int num, void* context);
static void GetCDDBGenres_handler(out_request *request, out_response *response, int num, void* context);
static void GetComponentVersions_handler(out_request *request, out_response *response, int num, void* context);
static void GetCount_handler(out_request *request, out_response *response, int num, void* context);
static void GetCurOp_handler(out_request *request, out_response *response, int num, void* context);
static void GetCurrentPlayList_handler(out_request *request, out_response *response, int num, void* context);
static void GetCurrentPlaylistEx_handler(out_request *request, out_response *response, int num, void* context);
static void GetDeviceDetails_handler(out_request *request, out_response *response, int num, void* context);
static void GetDevices_handler(out_request *request, out_response *response, int num, void* context);
static void GetDriveDetail_handler(out_request *request, out_response *response, int num, void* context);
static void GetEncodingQueue_handler(out_request *request, out_response *response, int num, void* context);
static void GetEncodingStatus_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtAlbumCredits_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtAlbumsByContributor_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtAlbumsByContributorForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtAlbumsByContributorForServer_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtAlbumsByContributorForShare_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtAlbumsByCredit_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtAlbumsByWork_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtAlbumsInfo_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtAlbumsSearchPeople_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtContributorDetails_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtContributors_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtContributorsForAlbum_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtContributorsForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtContributorsForServer_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtContributorsForShare_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtCountAlbumsByContributor_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtCountAlbumsByContributorForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtCountAlbumsByContributorForServer_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtCountAlbumsByContributorForShare_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtCountContributors_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtCountContributorsForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtCountContributorsForServer_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtCountContributorsForShare_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtTrackContributors_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtTracksByContributor_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtTracksByContributorForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtTracksByContributorForServer_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtTracksByContributorForShare_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtTracksByWork_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtTracksInfo_handler(out_request *request, out_response *response, int num, void* context);
static void GetExtWorks_handler(out_request *request, out_response *response, int num, void* context);
static void GetExternalStorageDetail_handler(out_request *request, out_response *response, int num, void* context);
static void GetExternalStorages_handler(out_request *request, out_response *response, int num, void* context);
static void GetFileSystemDriveDetail_handler(out_request *request, out_response *response, int num, void* context);
static void GetGenreDetail_handler(out_request *request, out_response *response, int num, void* context);
static void GetGenres_handler(out_request *request, out_response *response, int num, void* context);
static void GetGenresSubGenres_handler(out_request *request, out_response *response, int num, void* context);
static void GetHostDetails_handler(out_request *request, out_response *response, int num, void* context);
static void GetLastError_handler(out_request *request, out_response *response, int num, void* context);
static void GetLatestPlayedAlbums_handler(out_request *request, out_response *response, int num, void* context);
static void GetLibraryCheckSum_handler(out_request *request, out_response *response, int num, void* context);
static void GetLinkedRoomDetail_handler(out_request *request, out_response *response, int num, void* context);
static void GetLinkedRooms_handler(out_request *request, out_response *response, int num, void* context);
static void GetNetworkActiveAdapters_handler(out_request *request, out_response *response, int num, void* context);
static void GetNetworkWorkgroup_handler(out_request *request, out_response *response, int num, void* context);
static void GetNewestAlbums_handler(out_request *request, out_response *response, int num, void* context);
static void GetNonLinkedRooms_handler(out_request *request, out_response *response, int num, void* context);
static void GetOperationActivity_handler(out_request *request, out_response *response, int num, void* context);
static void GetOutputChannels_handler(out_request *request, out_response *response, int num, void* context);
static void GetOutputDevices_handler(out_request *request, out_response *response, int num, void* context);
static void GetPlayListsByLetter_handler(out_request *request, out_response *response, int num, void* context);
static void GetPlayerInstances_handler(out_request *request, out_response *response, int num, void* context);
static void GetPlayerStatus_handler(out_request *request, out_response *response, int num, void* context);
static void GetPlayerVersion_handler(out_request *request, out_response *response, int num, void* context);
static void GetPlaylistsForGenre_handler(out_request *request, out_response *response, int num, void* context);
static void GetPlaylistsForSubGenre_handler(out_request *request, out_response *response, int num, void* context);
static void GetPlaylistsForSubGenreForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void GetPlaylistsForSubGenreForServer_handler(out_request *request, out_response *response, int num, void* context);
static void GetPlaylistsForSubGenreForShare_handler(out_request *request, out_response *response, int num, void* context);
static void GetRepeat_handler(out_request *request, out_response *response, int num, void* context);
static void GetRipEncSettings_handler(out_request *request, out_response *response, int num, void* context);
static void GetRipEncSettingsEx_handler(out_request *request, out_response *response, int num, void* context);
static void GetRippingAlerts_handler(out_request *request, out_response *response, int num, void* context);
static void GetRippingStatus_handler(out_request *request, out_response *response, int num, void* context);
static void GetRoomDetail_handler(out_request *request, out_response *response, int num, void* context);
static void GetRooms_handler(out_request *request, out_response *response, int num, void* context);
static void GetRoomsWithPlayBack_handler(out_request *request, out_response *response, int num, void* context);
static void GetRoomsWithRipping_handler(out_request *request, out_response *response, int num, void* context);
static void GetRows_handler(out_request *request, out_response *response, int num, void* context);
static void GetSearchOffset_handler(out_request *request, out_response *response, int num, void* context);
static void GetSettings_handler(out_request *request, out_response *response, int num, void* context);
static void GetSettingsEx_handler(out_request *request, out_response *response, int num, void* context);
static void GetSetupVal_handler(out_request *request, out_response *response, int num, void* context);
static void GetShuffle_handler(out_request *request, out_response *response, int num, void* context);
static void GetSingleRipEncSetting_handler(out_request *request, out_response *response, int num, void* context);
static void GetSingleSystemSetting_handler(out_request *request, out_response *response, int num, void* context);
static void GetStatusMessageDetail_handler(out_request *request, out_response *response, int num, void* context);
static void GetStatusMessages_handler(out_request *request, out_response *response, int num, void* context);
static void GetStoreDetail_handler(out_request *request, out_response *response, int num, void* context);
static void GetStores_handler(out_request *request, out_response *response, int num, void* context);
static void GetSubGenreDetail_handler(out_request *request, out_response *response, int num, void* context);
static void GetSubGenresForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void GetSubGenresForGenre_handler(out_request *request, out_response *response, int num, void* context);
static void GetSubGenresForServer_handler(out_request *request, out_response *response, int num, void* context);
static void GetSubGenresForShare_handler(out_request *request, out_response *response, int num, void* context);
static void GetSystemDrives_handler(out_request *request, out_response *response, int num, void* context);
static void GetSystemTime_handler(out_request *request, out_response *response, int num, void* context);
static void GetTopPlayedAlbums_handler(out_request *request, out_response *response, int num, void* context);
static void GetTrackCount_handler(out_request *request, out_response *response, int num, void* context);
static void GetTrackDetailsFromPlayer_handler(out_request *request, out_response *response, int num, void* context);
static void GetTrackLength_handler(out_request *request, out_response *response, int num, void* context);
static void GetTrackName_handler(out_request *request, out_response *response, int num, void* context);
static void GetTrackNum_handler(out_request *request, out_response *response, int num, void* context);
static void GetTrackPosition_handler(out_request *request, out_response *response, int num, void* context);
static void GetTrackRange_handler(out_request *request, out_response *response, int num, void* context);
static void GetTracksAll_handler(out_request *request, out_response *response, int num, void* context);
static void GetTracksForAlbumInUPL_handler(out_request *request, out_response *response, int num, void* context);
static void GetTracksForArtist_handler(out_request *request, out_response *response, int num, void* context);
static void GetTracksForArtistForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void GetTracksForArtistForServer_handler(out_request *request, out_response *response, int num, void* context);
static void GetTracksForArtistForShare_handler(out_request *request, out_response *response, int num, void* context);
static void GetTracksForDeletion_handler(out_request *request, out_response *response, int num, void* context);
static void GetTracksForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void GetTracksForGenre_handler(out_request *request, out_response *response, int num, void* context);
static void GetTracksForNamedEntity_handler(out_request *request, out_response *response, int num, void* context);
static void GetTracksForPlaylist_handler(out_request *request, out_response *response, int num, void* context);
static void GetTracksForServer_handler(out_request *request, out_response *response, int num, void* context);
static void GetTracksForShare_handler(out_request *request, out_response *response, int num, void* context);
static void GetTracksForSubGenre_handler(out_request *request, out_response *response, int num, void* context);
static void GetTracksForSubGenreForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void GetTracksForSubGenreForServer_handler(out_request *request, out_response *response, int num, void* context);
static void GetTracksForSubGenreForShare_handler(out_request *request, out_response *response, int num, void* context);
static void GetTracksOtherInfo_handler(out_request *request, out_response *response, int num, void* context);
static void GetTracksSearchName_handler(out_request *request, out_response *response, int num, void* context);
static void GetUpnpMediaRenderers_handler(out_request *request, out_response *response, int num, void* context);
static void GetUserPlaylists_handler(out_request *request, out_response *response, int num, void* context);
static void GetUserPlaylistsForDevice_handler(out_request *request, out_response *response, int num, void* context);
static void GetUserPlaylistsForServer_handler(out_request *request, out_response *response, int num, void* context);
static void GetUserPlaylistsForShare_handler(out_request *request, out_response *response, int num, void* context);
static void GetUserStatus_handler(out_request *request, out_response *response, int num, void* context);
static void GetVolume_handler(out_request *request, out_response *response, int num, void* context);
static void IgnoreExternalStorage_handler(out_request *request, out_response *response, int num, void* context);
static void IsCDPlaying_handler(out_request *request, out_response *response, int num, void* context);
static void LookupError_handler(out_request *request, out_response *response, int num, void* context);
static void MoveAlbumGetQueue_handler(out_request *request, out_response *response, int num, void* context);
static void MoveAlbumGetStatus_handler(out_request *request, out_response *response, int num, void* context);
static void MoveAlbumToMusicStore_handler(out_request *request, out_response *response, int num, void* context);
static void NewOutputChannel_handler(out_request *request, out_response *response, int num, void* context);
static void NextTrack_handler(out_request *request, out_response *response, int num, void* context);
static void PlayAlbum_handler(out_request *request, out_response *response, int num, void* context);
static void PlayAlbums_handler(out_request *request, out_response *response, int num, void* context);
static void PlayAlbumsFromSearch_handler(out_request *request, out_response *response, int num, void* context);
static void PlayAll_handler(out_request *request, out_response *response, int num, void* context);
static void PlayArtistAlbum_handler(out_request *request, out_response *response, int num, void* context);
static void PlayLastPlayed_handler(out_request *request, out_response *response, int num, void* context);
static void PlayLastRipped_handler(out_request *request, out_response *response, int num, void* context);
static void PlayMostPopular_handler(out_request *request, out_response *response, int num, void* context);
static void PlayPlaylist_handler(out_request *request, out_response *response, int num, void* context);
static void PlayRandom_handler(out_request *request, out_response *response, int num, void* context);
static void PlayTrack_handler(out_request *request, out_response *response, int num, void* context);
static void PlayTracks_handler(out_request *request, out_response *response, int num, void* context);
static void PlayTracksFromSearch_handler(out_request *request, out_response *response, int num, void* context);
static void PlayUrl_handler(out_request *request, out_response *response, int num, void* context);
static void PlayUrls_handler(out_request *request, out_response *response, int num, void* context);
static void PrevTrack_handler(out_request *request, out_response *response, int num, void* context);
static void ProcessEmbeddedInit_handler(out_request *request, out_response *response, int num, void* context);
static void PromoteShareToMusicStore_handler(out_request *request, out_response *response, int num, void* context);
static void QueryAllPlayback_handler(out_request *request, out_response *response, int num, void* context);
static void ReleaseSerialPort_handler(out_request *request, out_response *response, int num, void* context);
static void RemoveAlbumsFromUserPlaylist_handler(out_request *request, out_response *response, int num, void* context);
static void RemoveCoverImage_handler(out_request *request, out_response *response, int num, void* context);
static void RemoveExternalStorage_handler(out_request *request, out_response *response, int num, void* context);
static void RemoveOldRooms_handler(out_request *request, out_response *response, int num, void* context);
static void RemovePlayerInstance_handler(out_request *request, out_response *response, int num, void* context);
static void RemoveTrack_handler(out_request *request, out_response *response, int num, void* context);
static void RenameAlbum_handler(out_request *request, out_response *response, int num, void* context);
static void RenameArtist_handler(out_request *request, out_response *response, int num, void* context);
static void RenamePlaylist_handler(out_request *request, out_response *response, int num, void* context);
static void RenameTrack_handler(out_request *request, out_response *response, int num, void* context);
static void RequestAlbumCover_handler(out_request *request, out_response *response, int num, void* context);
static void RescanExternalStorages_handler(out_request *request, out_response *response, int num, void* context);
static void RescanMusicStore_handler(out_request *request, out_response *response, int num, void* context);
static void RestoreSingleAlbum_handler(out_request *request, out_response *response, int num, void* context);
static void RestoreSingleTrack_handler(out_request *request, out_response *response, int num, void* context);
static void SaveCurrentPlayList_handler(out_request *request, out_response *response, int num, void* context);
static void SavePlayerInstance_handler(out_request *request, out_response *response, int num, void* context);
static void ScanExternalStorage_handler(out_request *request, out_response *response, int num, void* context);
static void ScanForExternalStorages_handler(out_request *request, out_response *response, int num, void* context);
static void ServiceMode_handler(out_request *request, out_response *response, int num, void* context);
static void SetAlbumLowQuality_handler(out_request *request, out_response *response, int num, void* context);
static void SetCoverImage_handler(out_request *request, out_response *response, int num, void* context);
static void SetDriveUsage_handler(out_request *request, out_response *response, int num, void* context);
static void SetMusicStoreCredentials_handler(out_request *request, out_response *response, int num, void* context);
static void SetMusicStorePriority_handler(out_request *request, out_response *response, int num, void* context);
static void Status_handler(out_request *request, out_response *response, int num, void* context);
static void StopBackupDrive_handler(out_request *request, out_response *response, int num, void* context);
static void ToggleDeviceSync_handler(out_request *request, out_response *response, int num, void* context);
static void UndoUserEdits_handler(out_request *request, out_response *response, int num, void* context);
static void UpdateBackupJob_handler(out_request *request, out_response *response, int num, void* context);
static void UpdateDrive_handler(out_request *request, out_response *response, int num, void* context);
static void UpdateExternalStorage_handler(out_request *request, out_response *response, int num, void* context);
static void UpdateGenre_handler(out_request *request, out_response *response, int num, void* context);
static void UpdateHitCount_handler(out_request *request, out_response *response, int num, void* context);
static void UpdateLinkedRoom_handler(out_request *request, out_response *response, int num, void* context);
static void UpdateOutputChannel_handler(out_request *request, out_response *response, int num, void* context);
static void UpdatePlaylist_handler(out_request *request, out_response *response, int num, void* context);
static void UpdateRoom_handler(out_request *request, out_response *response, int num, void* context);
static void UpdateSingleRipEncSetting_handler(out_request *request, out_response *response, int num, void* context);
static void UpdateSingleSystemSetting_handler(out_request *request, out_response *response, int num, void* context);
static void UpdateSubGenre_handler(out_request *request, out_response *response, int num, void* context);
static void UploadMessages_handler(out_request *request, out_response *response, int num, void* context);
static void Version_handler(out_request *request, out_response *response, int num, void* context);
static void vTunerAddRemoveFavourite_handler(out_request *request, out_response *response, int num, void* context);
static void vTunerCheckAvailability_handler(out_request *request, out_response *response, int num, void* context);
static void vTunerGetChildNodes_handler(out_request *request, out_response *response, int num, void* context);
static void vTunerGetLastPlayed_handler(out_request *request, out_response *response, int num, void* context);
static void vTunerGetMostPlayed_handler(out_request *request, out_response *response, int num, void* context);
static void vTunerGetNodeFromPlayedUrl_handler(out_request *request, out_response *response, int num, void* context);
static void vTunerGetPresetChannels_handler(out_request *request, out_response *response, int num, void* context);
static void vTunerLookupById_handler(out_request *request, out_response *response, int num, void* context);
static void vTunerPlayById_handler(out_request *request, out_response *response, int num, void* context);
static void vTunerPlayByIds_handler(out_request *request, out_response *response, int num, void* context);
static void vTunerSetPresetChannel_handler(out_request *request, out_response *response, int num, void* context);



// Generated functions
// Get commands

void df_newdriveresult_free(df_newdriveresult *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->AddNewDrive_ErrorMessage);

	free(ptr);
}

void df_servicemode_free(df_servicemode *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->ServiceMode_ModeName);

	free(ptr);
}

void df_drivedetail_free(df_drivedetail *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->DriveLetter);
	free(ptr->RootPath);
	free(ptr->SharePath);

	free(ptr);
}

void df_extstoragedetail_free(df_extstoragedetail *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->IPAddress);
	free(ptr->HostName);
	free(ptr->ShareName);
	free(ptr->FullSharePath);
	free(ptr->State);
	free(ptr->LastState);
	free(ptr->UserName);
	free(ptr->Password);
	free(ptr->ScanIgnore);

	free(ptr);
}

void df_trkname_free(df_trkname *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->Name);
	free(ptr->Type);

	free(ptr);
}

void df_rescanresult_free(df_rescanresult *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->RescanMusicStore_Message);

	free(ptr);
}

void df_updatedrivedetails_free(df_updatedrivedetails *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->UpdateDrive_ErrorMessage);

	free(ptr);
}

void df_fsdrivedetail_free(df_fsdrivedetail *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->DriveLetter);
	free(ptr->RootPath);
	free(ptr->SharePath);

	free(ptr);
}

void df_extstorageresult_free(df_extstorageresult *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->AddExternalStorage_Message);
	free(ptr->AddExternalStorage_Hostname);
	free(ptr->AddExternalStorage_IPAddress);
	free(ptr->AddExternalStorage_ShareName);
	free(ptr->AddExternalStorage_Username);
	free(ptr->AddExternalStorage_Password);

	free(ptr);
}

void df_systemtime_free(df_systemtime *ptr) {
	if (ptr == NULL) { return; }


	free(ptr);
}

void df_demoteresult_free(df_demoteresult *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->DemoteMusicStoreToShare_Message);

	free(ptr);
}

void df_albumartist_free(df_albumartist *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->Album);
	free(ptr->Artist);

	free(ptr);
}

void df_musicstorepriorityresult_free(df_musicstorepriorityresult *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->SetMusicStorePriority_Message);

	free(ptr);
}

void df_backupstatus_free(df_backupstatus *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->Backup_SourceDrive);
	free(ptr->Backup_DestDrive);
	free(ptr->Backup_Type);
	free(ptr->Backup_Status);
	free(ptr->Backup_CurrentFile);
	free(ptr->Backup_LastError);

	free(ptr);
}

void df_coverimage_free(df_coverimage *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->CoverImageName);
	free(ptr->CoverImageURI);

	free(ptr);
}

void df_queryplayback_free(df_queryplayback *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->TrackName);
	free(ptr->Album);
	free(ptr->Artist);
	free(ptr->Status);
	free(ptr->Version);

	free(ptr);
}

void df_hostdetails_free(df_hostdetails *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->GetHostDetails_Name);
	free(ptr->GetHostDetails_Address);

	free(ptr);
}

void df_stopbackupdriveresult_free(df_stopbackupdriveresult *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->StopBackupDrive_Message);

	free(ptr);
}

void df_version_free(df_version *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->Version_Service);
	free(ptr->Version_Protocol);
	free(ptr->Version_CommandDef);
	free(ptr->Version_System);

	free(ptr);
}

void df_room_free(df_room *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->IPAddress);
	free(ptr->RoomName);
	free(ptr->HostName);

	free(ptr);
}

void df_movealbumstatus_free(df_movealbumstatus *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->AlbumName);

	free(ptr);
}

void df_backupresult_free(df_backupresult *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->BackupDrive_Message);

	free(ptr);
}

void df_searchoffset_free(df_searchoffset *ptr) {
	if (ptr == NULL) { return; }


	free(ptr);
}

void df_type0_free(df_type0 *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->AlbumName);

	free(ptr);
}

void df_genre_free(df_genre *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->GenreName);

	free(ptr);
}

void df_trackfromplayer_free(df_trackfromplayer *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->Name);
	free(ptr->Album);
	free(ptr->Artist);
	free(ptr->Genre);
	free(ptr->Comment);

	free(ptr);
}

void df_driveusageresult_free(df_driveusageresult *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->SetDriveUsage_Message);

	free(ptr);
}

void df_subgenre_free(df_subgenre *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->SubGenreName);

	free(ptr);
}

void df_messagedetail_free(df_messagedetail *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->Message);
	free(ptr->Category);

	free(ptr);
}

void df_promoteshare_free(df_promoteshare *ptr) {
	if (ptr == NULL) { return; }

	free(ptr->PromoteShareToMusicStore_Message);

	free(ptr);
}

int df_ActivateExternalStorage(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ActivateExternalStorage", 1, -1, ActivateExternalStorage_handler, c, "[ActivateExternalStorage %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

int df_AddAlbumsToUserPlaylist(df_connection *conn, char* UserPlaylistKey, char* AlbumKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddAlbumsToUserPlaylist", 1, -1, AddAlbumsToUserPlaylist_handler, c, "[AddAlbumsToUserPlaylist \"%s\" \"%s\"]", UserPlaylistKey, AlbumKey);
}

int df_AddExternalStorage(df_connection *conn, char* SharePath, char* Username, char* Password, int Activate, int ForceAdd, void (*callback)(df_extstorageresult*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddExternalStorage", 1, -1, AddExternalStorage_handler, c, "[AddExternalStorage \"%s\" \"%s\" \"%s\" %d %d]", SharePath, Username, Password, Activate, ForceAdd);
}

int df_AddNewBackupJob(df_connection *conn, char* SourceDriveAddress, char* DestinationDriveAddress, char* Name, int BackupType, int BackupPeriod, int PeriodValue, df_date RunDate, df_time RunTime, void (*callback)(int, void*), void *context) {	char *RunDate_string;
	char *RunTime_string;

	struct call_holder *c;
	RunDate_string = dfdate_to_string(RunDate);
	RunTime_string = dftime_to_string(RunTime);

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddNewBackupJob", 1, -1, AddNewBackupJob_handler, c, "[AddNewBackupJob \"%s\" \"%s\" \"%s\" %d %d %d \"%s\" \"%s\"]", SourceDriveAddress, DestinationDriveAddress, Name, BackupType, BackupPeriod, PeriodValue, RunDate_string, RunTime_string);
}

int df_AddNewDrive(df_connection *conn, char* DriveLetter, int PrimaryDrive, char* RootPath, char* SharePath, int Usage, int BadPathBehaviour, void (*callback)(df_newdriveresult*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddNewDrive", 1, -1, AddNewDrive_handler, c, "[AddNewDrive \"%s\" %d \"%s\" \"%s\" %d %d]", DriveLetter, PrimaryDrive, RootPath, SharePath, Usage, BadPathBehaviour);
}

int df_AddNewGenre(df_connection *conn, char* GenreName, int Ordinal, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddNewGenre", 1, -1, AddNewGenre_handler, c, "[AddNewGenre \"%s\" %d]", GenreName, Ordinal);
}

int df_AddNewLinkedRoom(df_connection *conn, char* RoomName, char* ShortName, int RoomID, char* ChildRoomKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddNewLinkedRoom", 1, -1, AddNewLinkedRoom_handler, c, "[AddNewLinkedRoom \"%s\" \"%s\" %d \"%s\"]", RoomName, ShortName, RoomID, ChildRoomKey);
}

int df_AddNewRoom(df_connection *conn, char* RoomIP, int Channel, char* RoomName, char* ShortName, int PlaybackCapability, int RippingCapability, int MusicManagementCapability, int RoomID, char* HostName, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddNewRoom", 1, -1, AddNewRoom_handler, c, "[AddNewRoom \"%s\" %d \"%s\" \"%s\" %d %d %d %d \"%s\"]", RoomIP, Channel, RoomName, ShortName, PlaybackCapability, RippingCapability, MusicManagementCapability, RoomID, HostName);
}

int df_AddNewSubGenre(df_connection *conn, char* GenreKey, char* SubGenreName, int Ordinal, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddNewSubGenre", 1, -1, AddNewSubGenre_handler, c, "[AddNewSubGenre \"%s\" \"%s\" %d]", GenreKey, SubGenreName, Ordinal);
}

int df_AddTracksToUserPlaylist(df_connection *conn, char* UserPlaylistKey, char* TrackKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddTracksToUserPlaylist", 1, -1, AddTracksToUserPlaylist_handler, c, "[AddTracksToUserPlaylist \"%s\" \"%s\"]", UserPlaylistKey, TrackKey);
}

int df_BackupDrive(df_connection *conn, char* SourceDriveKey, char* DestDriveKey, int BackupType, int NoFileCheck, void (*callback)(df_backupresult*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "BackupDrive", 1, -1, BackupDrive_handler, c, "[BackupDrive \"%s\" \"%s\" %d %d]", SourceDriveKey, DestDriveKey, BackupType, NoFileCheck);
}

int df_BulkCDLookupEx(df_connection *conn, int LookupProviderUsed, int Interval, char* AlbumKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "BulkCDLookupEx", 1, -1, BulkCDLookupEx_handler, c, "[BulkCDLookupEx %d %d \"%s\"]", LookupProviderUsed, Interval, AlbumKey);
}

int df_CDLookupGetStatus(df_connection *conn, void (*callback)(df_type0*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CDLookupGetStatus", 1, -1, CDLookupGetStatus_handler, c, "[CDLookupGetStatus]");
}

int df_CancelRipping(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CancelRipping", 1, -1, CancelRipping_handler, c, "[CancelRipping %d]", RoomID);
}

int df_ChangeAlbumSubGenre(df_connection *conn, char* AlbumKey, char* SubGenreKey, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeAlbumSubGenre", 1, -1, ChangeAlbumSubGenre_handler, c, "[ChangeAlbumSubGenre \"%s\" \"%s\"]", AlbumKey, SubGenreKey);
}

int df_ChangeNetworkAutoIP(df_connection *conn, int DeviceID, char* AutoIpRange, char* DefaultGateway, char* DnsServer, int RestartDevice, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeNetworkAutoIP", 1, -1, ChangeNetworkAutoIP_handler, c, "[ChangeNetworkAutoIP %d \"%s\" \"%s\" \"%s\" %d]", DeviceID, AutoIpRange, DefaultGateway, DnsServer, RestartDevice);
}

int df_ChangeNetworkDhcp(df_connection *conn, int DeviceID, int RestartDevice, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeNetworkDhcp", 1, -1, ChangeNetworkDhcp_handler, c, "[ChangeNetworkDhcp %d %d]", DeviceID, RestartDevice);
}

int df_ChangeNetworkMachineName(df_connection *conn, char* MachineName, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeNetworkMachineName", 1, -1, ChangeNetworkMachineName_handler, c, "[ChangeNetworkMachineName \"%s\"]", MachineName);
}

int df_ChangeNetworkStatic(df_connection *conn, int DeviceID, char* IpAddress, char* SubnetMask, char* DefaultGateway, char* DnsServer, int RestartDevice, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeNetworkStatic", 1, -1, ChangeNetworkStatic_handler, c, "[ChangeNetworkStatic %d \"%s\" \"%s\" \"%s\" \"%s\" %d]", DeviceID, IpAddress, SubnetMask, DefaultGateway, DnsServer, RestartDevice);
}

int df_ChangeNetworkWorkgroup(df_connection *conn, char* Workgroup, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeNetworkWorkgroup", 1, -1, ChangeNetworkWorkgroup_handler, c, "[ChangeNetworkWorkgroup \"%s\"]", Workgroup);
}

int df_ChangeSystemSerialNumber(df_connection *conn, char* SerialNumber, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeSystemSerialNumber", 1, -1, ChangeSystemSerialNumber_handler, c, "[ChangeSystemSerialNumber \"%s\"]", SerialNumber);
}

int df_ChangeTrackOrdinal(df_connection *conn, char* TrackKey, char* PlaylistKey, int Ordinal, int NewPosition, int ReorderPlaylist, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeTrackOrdinal", 1, -1, ChangeTrackOrdinal_handler, c, "[ChangeTrackOrdinal \"%s\" \"%s\" %d %d %d]", TrackKey, PlaylistKey, Ordinal, NewPosition, ReorderPlaylist);
}

int df_CheckCoverImage(df_connection *conn, char* Address, int ImageSize, int AddressType, int Local, char* Protocol, char* ImageFormat, void (*callback)(df_coverimage*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CheckCoverImage", 1, -1, CheckCoverImage_handler, c, "[CheckCoverImage \"%s\" %d %d %d \"%s\" \"%s\"]", Address, ImageSize, AddressType, Local, Protocol, ImageFormat);
}

int df_CompactGenreOrdinals(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CompactGenreOrdinals", 1, -1, CompactGenreOrdinals_handler, c, "[CompactGenreOrdinals]");
}

int df_ComplexSearchCountAlbums(df_connection *conn, char* SearchParameter, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ComplexSearchCountAlbums", 1, -1, ComplexSearchCountAlbums_handler, c, "[ComplexSearchCountAlbums \"%s\"]", SearchParameter);
}

int df_ComplexSearchCountArtists(df_connection *conn, char* SearchParameter, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ComplexSearchCountArtists", 1, -1, ComplexSearchCountArtists_handler, c, "[ComplexSearchCountArtists \"%s\"]", SearchParameter);
}

int df_ComplexSearchCountContributors(df_connection *conn, int Type, char* SearchParameter, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ComplexSearchCountContributors", 1, -1, ComplexSearchCountContributors_handler, c, "[ComplexSearchCountContributors %d \"%s\"]", Type, SearchParameter);
}

int df_ComplexSearchCountTracks(df_connection *conn, char* SearchParameter, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ComplexSearchCountTracks", 1, -1, ComplexSearchCountTracks_handler, c, "[ComplexSearchCountTracks \"%s\"]", SearchParameter);
}

int df_CountAlbums(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbums", 1, -1, CountAlbums_handler, c, "[CountAlbums]");
}

int df_CountAlbumsForArtist(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbumsForArtist", 1, -1, CountAlbumsForArtist_handler, c, "[CountAlbumsForArtist \"%s\"]", Address);
}

int df_CountAlbumsForArtistForDevice(df_connection *conn, char* Address, char* DeviceAddress, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbumsForArtistForDevice", 1, -1, CountAlbumsForArtistForDevice_handler, c, "[CountAlbumsForArtistForDevice \"%s\" \"%s\"]", Address, DeviceAddress);
}

int df_CountAlbumsForArtistForServer(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbumsForArtistForServer", 1, -1, CountAlbumsForArtistForServer_handler, c, "[CountAlbumsForArtistForServer \"%s\"]", Address);
}

int df_CountAlbumsForArtistForShare(df_connection *conn, char* Address, char* ShareAddress, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbumsForArtistForShare", 1, -1, CountAlbumsForArtistForShare_handler, c, "[CountAlbumsForArtistForShare \"%s\" \"%s\"]", Address, ShareAddress);
}

int df_CountAlbumsForDevice(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbumsForDevice", 1, -1, CountAlbumsForDevice_handler, c, "[CountAlbumsForDevice \"%s\"]", Address);
}

int df_CountAlbumsForServer(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbumsForServer", 1, -1, CountAlbumsForServer_handler, c, "[CountAlbumsForServer]");
}

int df_CountAlbumsForShare(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbumsForShare", 1, -1, CountAlbumsForShare_handler, c, "[CountAlbumsForShare \"%s\"]", Address);
}

int df_CountArtists(df_connection *conn, int Allocated, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountArtists", 1, -1, CountArtists_handler, c, "[CountArtists %d]", Allocated);
}

int df_CountArtistsForDevice(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountArtistsForDevice", 1, -1, CountArtistsForDevice_handler, c, "[CountArtistsForDevice \"%s\"]", Address);
}

int df_CountArtistsForServer(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountArtistsForServer", 1, -1, CountArtistsForServer_handler, c, "[CountArtistsForServer]");
}

int df_CountArtistsForShare(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountArtistsForShare", 1, -1, CountArtistsForShare_handler, c, "[CountArtistsForShare \"%s\"]", Address);
}

int df_CountDevices(df_connection *conn, int ActiveOnly, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountDevices", 1, -1, CountDevices_handler, c, "[CountDevices %d]", ActiveOnly);
}

int df_CountGenres(df_connection *conn, int Allocated, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountGenres", 1, -1, CountGenres_handler, c, "[CountGenres %d]", Allocated);
}

int df_CountPlaylistsForSubGenre(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountPlaylistsForSubGenre", 1, -1, CountPlaylistsForSubGenre_handler, c, "[CountPlaylistsForSubGenre \"%s\"]", Address);
}

int df_CountPlaylistsForSubGenreForDevice(df_connection *conn, char* Address, char* DeviceAddress, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountPlaylistsForSubGenreForDevice", 1, -1, CountPlaylistsForSubGenreForDevice_handler, c, "[CountPlaylistsForSubGenreForDevice \"%s\" \"%s\"]", Address, DeviceAddress);
}

int df_CountPlaylistsForSubGenreForServer(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountPlaylistsForSubGenreForServer", 1, -1, CountPlaylistsForSubGenreForServer_handler, c, "[CountPlaylistsForSubGenreForServer \"%s\"]", Address);
}

int df_CountPlaylistsForSubGenreForShare(df_connection *conn, char* Address, char* ShareAddress, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountPlaylistsForSubGenreForShare", 1, -1, CountPlaylistsForSubGenreForShare_handler, c, "[CountPlaylistsForSubGenreForShare \"%s\" \"%s\"]", Address, ShareAddress);
}

int df_CountShares(df_connection *conn, int AvailableOnly, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountShares", 1, -1, CountShares_handler, c, "[CountShares %d]", AvailableOnly);
}

int df_CountSubGenresForDevice(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountSubGenresForDevice", 1, -1, CountSubGenresForDevice_handler, c, "[CountSubGenresForDevice \"%s\"]", Address);
}

int df_CountSubGenresForGenre(df_connection *conn, char* Address, int Allocated, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountSubGenresForGenre", 1, -1, CountSubGenresForGenre_handler, c, "[CountSubGenresForGenre \"%s\" %d]", Address, Allocated);
}

int df_CountSubGenresForServer(df_connection *conn, int Allocated, int UserDefined, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountSubGenresForServer", 1, -1, CountSubGenresForServer_handler, c, "[CountSubGenresForServer %d %d]", Allocated, UserDefined);
}

int df_CountSubGenresForShare(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountSubGenresForShare", 1, -1, CountSubGenresForShare_handler, c, "[CountSubGenresForShare \"%s\"]", Address);
}

int df_CountTracksAll(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountTracksAll", 1, -1, CountTracksAll_handler, c, "[CountTracksAll]");
}

int df_CountTracksForDevice(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountTracksForDevice", 1, -1, CountTracksForDevice_handler, c, "[CountTracksForDevice \"%s\"]", Address);
}

int df_CountTracksForPlaylist(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountTracksForPlaylist", 1, -1, CountTracksForPlaylist_handler, c, "[CountTracksForPlaylist \"%s\"]", Address);
}

int df_CountTracksForServer(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountTracksForServer", 1, -1, CountTracksForServer_handler, c, "[CountTracksForServer]");
}

int df_CountTracksForShare(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountTracksForShare", 1, -1, CountTracksForShare_handler, c, "[CountTracksForShare \"%s\"]", Address);
}

int df_CountUserPlaylists(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountUserPlaylists", 1, -1, CountUserPlaylists_handler, c, "[CountUserPlaylists]");
}

int df_CountUserPlaylistsForDevice(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountUserPlaylistsForDevice", 1, -1, CountUserPlaylistsForDevice_handler, c, "[CountUserPlaylistsForDevice \"%s\"]", Address);
}

int df_CountUserPlaylistsForServer(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountUserPlaylistsForServer", 1, -1, CountUserPlaylistsForServer_handler, c, "[CountUserPlaylistsForServer]");
}

int df_CountUserPlaylistsForShare(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountUserPlaylistsForShare", 1, -1, CountUserPlaylistsForShare_handler, c, "[CountUserPlaylistsForShare \"%s\"]", Address);
}

int df_CreatePlaylist(df_connection *conn, char* Name, char* TrackKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CreatePlaylist", 1, -1, CreatePlaylist_handler, c, "[CreatePlaylist \"%s\" \"%s\"]", Name, TrackKey);
}

int df_CreateRandomPlaylist(df_connection *conn, int RoomID, char* Genre, char* SubGenre, char* Artists, char* Albums, int MaxTracks, char* Tracks, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CreateRandomPlaylist", 1, -1, CreateRandomPlaylist_handler, c, "[CreateRandomPlaylist %d \"%s\" \"%s\" \"%s\" \"%s\" %d \"%s\"]", RoomID, Genre, SubGenre, Artists, Albums, MaxTracks, Tracks);
}

int df_CreateRandomPlaylistEx(df_connection *conn, int RoomID, int Replace, int PlayScope, char* ScopeKey, char* SubGenre, char* Artists, char* Albums, char* Tracks, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CreateRandomPlaylistEx", 1, -1, CreateRandomPlaylistEx_handler, c, "[CreateRandomPlaylistEx %d %d %d \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"]", RoomID, Replace, PlayScope, ScopeKey, SubGenre, Artists, Albums, Tracks);
}

int df_DeleteAlbum(df_connection *conn, char* AlbumKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteAlbum", 1, -1, DeleteAlbum_handler, c, "[DeleteAlbum \"%s\"]", AlbumKey);
}

int df_DeleteBackupJob(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteBackupJob", 1, -1, DeleteBackupJob_handler, c, "[DeleteBackupJob \"%s\"]", Address);
}

int df_DeleteDevice(df_connection *conn, int Key, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteDevice", 1, -1, DeleteDevice_handler, c, "[DeleteDevice %d]", Key);
}

int df_DeleteDrive(df_connection *conn, char* DriveKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteDrive", 1, -1, DeleteDrive_handler, c, "[DeleteDrive \"%s\"]", DriveKey);
}

int df_DeleteGenre(df_connection *conn, char* GenreKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteGenre", 1, -1, DeleteGenre_handler, c, "[DeleteGenre \"%s\"]", GenreKey);
}

int df_DeleteLinkedRoom(df_connection *conn, char* RoomKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteLinkedRoom", 1, -1, DeleteLinkedRoom_handler, c, "[DeleteLinkedRoom \"%s\"]", RoomKey);
}

int df_DeleteOutputChannel(df_connection *conn, int RoomID, char* HostName, int ChannelNumber, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteOutputChannel", 1, -1, DeleteOutputChannel_handler, c, "[DeleteOutputChannel %d \"%s\" %d]", RoomID, HostName, ChannelNumber);
}

int df_DeleteRoom(df_connection *conn, char* RoomKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteRoom", 1, -1, DeleteRoom_handler, c, "[DeleteRoom \"%s\"]", RoomKey);
}

int df_DeleteSubGenre(df_connection *conn, char* SubGenreKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteSubGenre", 1, -1, DeleteSubGenre_handler, c, "[DeleteSubGenre \"%s\"]", SubGenreKey);
}

int df_DeleteTrack(df_connection *conn, char* TrackKey, char* PlaylistKey, int Ordinal, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteTrack", 1, -1, DeleteTrack_handler, c, "[DeleteTrack \"%s\" \"%s\" %d]", TrackKey, PlaylistKey, Ordinal);
}

int df_DemoteMusicStoreToShare(df_connection *conn, char* MusicStoreKey, int Deactivate, void (*callback)(df_demoteresult*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DemoteMusicStoreToShare", 1, -1, DemoteMusicStoreToShare_handler, c, "[DemoteMusicStoreToShare \"%s\" %d]", MusicStoreKey, Deactivate);
}

int df_DeviceChecksum(df_connection *conn, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeviceChecksum", 1, -1, DeviceChecksum_handler, c, "[DeviceChecksum]");
}

int df_DisconnectDevice(df_connection *conn, int Key, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DisconnectDevice", 1, -1, DisconnectDevice_handler, c, "[DisconnectDevice %d %d]", Key, ClearPlaying);
}

int df_ExternalStorageCancelScan(df_connection *conn, char* StorageKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ExternalStorageCancelScan", 1, -1, ExternalStorageCancelScan_handler, c, "[ExternalStorageCancelScan \"%s\"]", StorageKey);
}

int df_FindAllRooms(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "FindAllRooms", 1, -1, FindAllRooms_handler, c, "[FindAllRooms %d]", TimeoutPerHost);
}

int df_FindNewRooms(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "FindNewRooms", 1, -1, FindNewRooms_handler, c, "[FindNewRooms %d]", TimeoutPerHost);
}

int df_ForceGenrePlaylistBackup(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ForceGenrePlaylistBackup", 1, -1, ForceGenrePlaylistBackup_handler, c, "[ForceGenrePlaylistBackup]");
}

int df_ForceGenrePlaylistRestore(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ForceGenrePlaylistRestore", 1, -1, ForceGenrePlaylistRestore_handler, c, "[ForceGenrePlaylistRestore]");
}

int df_GetAlbumArtist(df_connection *conn, int RoomID, void (*callback)(df_albumartist*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumArtist", 1, -1, GetAlbumArtist_handler, c, "[GetAlbumArtist %d]", RoomID);
}

int df_GetBackupStatus(df_connection *conn, void (*callback)(df_backupstatus*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetBackupStatus", 1, -1, GetBackupStatus_handler, c, "[GetBackupStatus]");
}

int df_GetCount(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetCount", 1, -1, GetCount_handler, c, "[GetCount]");
}

int df_GetCurOp(df_connection *conn, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetCurOp", 1, -1, GetCurOp_handler, c, "[GetCurOp]");
}

int df_GetDriveDetail(df_connection *conn, char* DriveKey, void (*callback)(df_drivedetail*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetDriveDetail", 1, -1, GetDriveDetail_handler, c, "[GetDriveDetail \"%s\"]", DriveKey);
}

int df_GetExtCountAlbumsByContributor(df_connection *conn, char* Address, int Type, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountAlbumsByContributor", 1, -1, GetExtCountAlbumsByContributor_handler, c, "[GetExtCountAlbumsByContributor \"%s\" %d]", Address, Type);
}

int df_GetExtCountAlbumsByContributorForDevice(df_connection *conn, char* Address, char* DeviceAddress, int Type, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountAlbumsByContributorForDevice", 1, -1, GetExtCountAlbumsByContributorForDevice_handler, c, "[GetExtCountAlbumsByContributorForDevice \"%s\" \"%s\" %d]", Address, DeviceAddress, Type);
}

int df_GetExtCountAlbumsByContributorForServer(df_connection *conn, char* Address, int Type, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountAlbumsByContributorForServer", 1, -1, GetExtCountAlbumsByContributorForServer_handler, c, "[GetExtCountAlbumsByContributorForServer \"%s\" %d]", Address, Type);
}

int df_GetExtCountAlbumsByContributorForShare(df_connection *conn, char* Address, char* ShareAddress, int Type, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountAlbumsByContributorForShare", 1, -1, GetExtCountAlbumsByContributorForShare_handler, c, "[GetExtCountAlbumsByContributorForShare \"%s\" \"%s\" %d]", Address, ShareAddress, Type);
}

int df_GetExtCountContributors(df_connection *conn, int Type, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountContributors", 1, -1, GetExtCountContributors_handler, c, "[GetExtCountContributors %d]", Type);
}

int df_GetExtCountContributorsForDevice(df_connection *conn, char* Address, int Type, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountContributorsForDevice", 1, -1, GetExtCountContributorsForDevice_handler, c, "[GetExtCountContributorsForDevice \"%s\" %d]", Address, Type);
}

int df_GetExtCountContributorsForServer(df_connection *conn, int Type, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountContributorsForServer", 1, -1, GetExtCountContributorsForServer_handler, c, "[GetExtCountContributorsForServer %d]", Type);
}

int df_GetExtCountContributorsForShare(df_connection *conn, char* Address, int Type, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountContributorsForShare", 1, -1, GetExtCountContributorsForShare_handler, c, "[GetExtCountContributorsForShare \"%s\" %d]", Address, Type);
}

int df_GetExternalStorageDetail(df_connection *conn, char* StorageKey, void (*callback)(df_extstoragedetail*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExternalStorageDetail", 1, -1, GetExternalStorageDetail_handler, c, "[GetExternalStorageDetail \"%s\"]", StorageKey);
}

int df_GetFileSystemDriveDetail(df_connection *conn, char* DriveLetter, void (*callback)(df_fsdrivedetail*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetFileSystemDriveDetail", 1, -1, GetFileSystemDriveDetail_handler, c, "[GetFileSystemDriveDetail \"%s\"]", DriveLetter);
}

int df_GetGenreDetail(df_connection *conn, char* GenreKey, void (*callback)(df_genre*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetGenreDetail", 1, -1, GetGenreDetail_handler, c, "[GetGenreDetail \"%s\"]", GenreKey);
}

int df_GetHostDetails(df_connection *conn, void (*callback)(df_hostdetails*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetHostDetails", 1, -1, GetHostDetails_handler, c, "[GetHostDetails]");
}

int df_GetLastError(df_connection *conn, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetLastError", 1, -1, GetLastError_handler, c, "[GetLastError]");
}

int df_GetLibraryCheckSum(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetLibraryCheckSum", 1, -1, GetLibraryCheckSum_handler, c, "[GetLibraryCheckSum %d]", RoomID);
}

int df_GetNetworkWorkgroup(df_connection *conn, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetNetworkWorkgroup", 1, -1, GetNetworkWorkgroup_handler, c, "[GetNetworkWorkgroup]");
}

int df_GetOperationActivity(df_connection *conn, int RoomID, int Service, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetOperationActivity", 1, -1, GetOperationActivity_handler, c, "[GetOperationActivity %d %d]", RoomID, Service);
}

int df_GetPlayerStatus(df_connection *conn, int RoomID, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetPlayerStatus", 1, -1, GetPlayerStatus_handler, c, "[GetPlayerStatus %d]", RoomID);
}

int df_GetPlayerVersion(df_connection *conn, int RoomID, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetPlayerVersion", 1, -1, GetPlayerVersion_handler, c, "[GetPlayerVersion %d]", RoomID);
}

int df_GetRepeat(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRepeat", 1, -1, GetRepeat_handler, c, "[GetRepeat %d]", RoomID);
}

int df_GetRoomDetail(df_connection *conn, char* RoomKey, void (*callback)(df_room*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRoomDetail", 1, -1, GetRoomDetail_handler, c, "[GetRoomDetail \"%s\"]", RoomKey);
}

int df_GetRows(df_connection *conn, int StartRow, int RowCount, char* FormatList, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRows", 1, -1, GetRows_handler, c, "[GetRows %d %d \"%s\"]", StartRow, RowCount, FormatList);
}

int df_GetSearchOffset(df_connection *conn, char* SearchValue, char* SearchColumn, int SearchType, void (*callback)(df_searchoffset*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSearchOffset", 1, -1, GetSearchOffset_handler, c, "[GetSearchOffset \"%s\" \"%s\" %d]", SearchValue, SearchColumn, SearchType);
}

int df_GetSetupVal(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSetupVal", 1, -1, GetSetupVal_handler, c, "[GetSetupVal]");
}

int df_GetShuffle(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetShuffle", 1, -1, GetShuffle_handler, c, "[GetShuffle %d]", RoomID);
}

int df_GetSingleRipEncSetting(df_connection *conn, int RoomID, char* SettingName, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSingleRipEncSetting", 1, -1, GetSingleRipEncSetting_handler, c, "[GetSingleRipEncSetting %d \"%s\"]", RoomID, SettingName);
}

int df_GetSingleSystemSetting(df_connection *conn, int RoomID, char* SettingName, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSingleSystemSetting", 1, -1, GetSingleSystemSetting_handler, c, "[GetSingleSystemSetting %d \"%s\"]", RoomID, SettingName);
}

int df_GetStatusMessageDetail(df_connection *conn, char* Key, void (*callback)(df_messagedetail*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetStatusMessageDetail", 1, -1, GetStatusMessageDetail_handler, c, "[GetStatusMessageDetail \"%s\"]", Key);
}

int df_GetSubGenreDetail(df_connection *conn, char* SubGenreKey, void (*callback)(df_subgenre*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSubGenreDetail", 1, -1, GetSubGenreDetail_handler, c, "[GetSubGenreDetail \"%s\"]", SubGenreKey);
}

int df_GetSystemTime(df_connection *conn, void (*callback)(df_systemtime*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSystemTime", 1, -1, GetSystemTime_handler, c, "[GetSystemTime]");
}

int df_GetTrackCount(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTrackCount", 1, -1, GetTrackCount_handler, c, "[GetTrackCount %d]", RoomID);
}

int df_GetTrackDetailsFromPlayer(df_connection *conn, int RoomID, char* TrackPath, void (*callback)(df_trackfromplayer*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTrackDetailsFromPlayer", 1, -1, GetTrackDetailsFromPlayer_handler, c, "[GetTrackDetailsFromPlayer %d \"%s\"]", RoomID, TrackPath);
}

int df_GetTrackLength(df_connection *conn, int RoomID, void (*callback)(df_time, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTrackLength", 1, -1, GetTrackLength_handler, c, "[GetTrackLength %d]", RoomID);
}

int df_GetTrackName(df_connection *conn, int RoomID, void (*callback)(df_trkname*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTrackName", 1, -1, GetTrackName_handler, c, "[GetTrackName %d]", RoomID);
}

int df_GetTrackNum(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTrackNum", 1, -1, GetTrackNum_handler, c, "[GetTrackNum %d]", RoomID);
}

int df_GetTrackPosition(df_connection *conn, int RoomID, void (*callback)(df_time, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTrackPosition", 1, -1, GetTrackPosition_handler, c, "[GetTrackPosition %d]", RoomID);
}

int df_GetVolume(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetVolume", 1, -1, GetVolume_handler, c, "[GetVolume %d]", RoomID);
}

int df_IgnoreExternalStorage(df_connection *conn, char* StorageKey, int IgnoreLevel, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "IgnoreExternalStorage", 1, -1, IgnoreExternalStorage_handler, c, "[IgnoreExternalStorage \"%s\" %d]", StorageKey, IgnoreLevel);
}

int df_IsCDPlaying(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "IsCDPlaying", 1, -1,IsCDPlaying_handler, c, "[IsCDPlaying %d]", RoomID);
}

int df_LookupError(df_connection *conn, int ErrorCode, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "LookupError", 1, -1,LookupError_handler, c, "[LookupError %d]", ErrorCode);
}

int df_MoveAlbumGetStatus(df_connection *conn, void (*callback)(df_movealbumstatus*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "MoveAlbumGetStatus", 1, -1,MoveAlbumGetStatus_handler, c, "[MoveAlbumGetStatus]");
}

int df_MoveAlbumToMusicStore(df_connection *conn, char* Address, char* MusicStoreKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "MoveAlbumToMusicStore", 1, -1,MoveAlbumToMusicStore_handler, c, "[MoveAlbumToMusicStore \"%s\" \"%s\"]", Address, MusicStoreKey);
}

int df_NewOutputChannel(df_connection *conn, int RoomID, char* HostName, int ChannelNumber, char* InitString, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "NewOutputChannel", 1, -1,NewOutputChannel_handler, c, "[NewOutputChannel %d \"%s\" %d \"%s\"]", RoomID, HostName, ChannelNumber, InitString);
}

int df_NextTrack(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "NextTrack", 1, -1,NextTrack_handler, c, "[NextTrack %d]", RoomID);
}

int df_PlayAlbum(df_connection *conn, int RoomID, int Replace, char* Address, int StartTrack, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayAlbum", 1, -1,PlayAlbum_handler, c, "[PlayAlbum %d %d \"%s\" %d]", RoomID, Replace, Address, StartTrack);
}

int df_PlayAlbums(df_connection *conn, int RoomID, int Replace, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayAlbums", 1, -1,PlayAlbums_handler, c, "[PlayAlbums %d %d \"%s\"]", RoomID, Replace, Address);
}

int df_PlayAlbumsFromSearch(df_connection *conn, int RoomID, int Replace, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayAlbumsFromSearch", 1, -1,PlayAlbumsFromSearch_handler, c, "[PlayAlbumsFromSearch %d %d]", RoomID, Replace);
}

int df_PlayAll(df_connection *conn, int RoomID, int Replace, int PlayScope, char* ScopeKey, int PlayType, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayAll", 1, -1,PlayAll_handler, c, "[PlayAll %d %d %d \"%s\" %d \"%s\"]", RoomID, Replace, PlayScope, ScopeKey, PlayType, Address);
}

int df_PlayArtistAlbum(df_connection *conn, int RoomID, char* Artist, char* Album, int Randomise, int OnErrorBehaviour, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayArtistAlbum", 1, -1,PlayArtistAlbum_handler, c, "[PlayArtistAlbum %d \"%s\" \"%s\" %d %d]", RoomID, Artist, Album, Randomise, OnErrorBehaviour);
}

int df_PlayLastPlayed(df_connection *conn, int RoomID, int Randomise, int Number, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayLastPlayed", 1, -1,PlayLastPlayed_handler, c, "[PlayLastPlayed %d %d %d]", RoomID, Randomise, Number);
}

int df_PlayLastRipped(df_connection *conn, int RoomID, int Randomise, int Number, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayLastRipped", 1, -1,PlayLastRipped_handler, c, "[PlayLastRipped %d %d %d]", RoomID, Randomise, Number);
}

int df_PlayMostPopular(df_connection *conn, int RoomID, int Randomise, int Number, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayMostPopular", 1, -1,PlayMostPopular_handler, c, "[PlayMostPopular %d %d %d]", RoomID, Randomise, Number);
}

int df_PlayPlaylist(df_connection *conn, int RoomID, char* PlaylistName, int Randomise, int OnErrorBehaviour, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayPlaylist", 1, -1,PlayPlaylist_handler, c, "[PlayPlaylist %d \"%s\" %d %d]", RoomID, PlaylistName, Randomise, OnErrorBehaviour);
}

int df_PlayRandom(df_connection *conn, int RoomID, char* Genre, char* SubGenre, int OnErrorBehaviour, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayRandom", 1, -1,PlayRandom_handler, c, "[PlayRandom %d \"%s\" \"%s\" %d]", RoomID, Genre, SubGenre, OnErrorBehaviour);
}

int df_PlayTrack(df_connection *conn, int RoomID, int Replace, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayTrack", 1, -1,PlayTrack_handler, c, "[PlayTrack %d %d \"%s\"]", RoomID, Replace, Address);
}

int df_PlayTracks(df_connection *conn, int RoomID, int Replace, char* Address, int StartTrack, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayTracks", 1, -1,PlayTracks_handler, c, "[PlayTracks %d %d \"%s\" %d]", RoomID, Replace, Address, StartTrack);
}

int df_PlayTracksFromSearch(df_connection *conn, int RoomID, int Replace, int StartTrack, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayTracksFromSearch", 1, -1,PlayTracksFromSearch_handler, c, "[PlayTracksFromSearch %d %d %d]", RoomID, Replace, StartTrack);
}

int df_PlayUrl(df_connection *conn, int RoomID, int Replace, char* Url, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayUrl", 1, -1,PlayUrl_handler, c, "[PlayUrl %d %d \"%s\"]", RoomID, Replace, Url);
}

int df_PlayUrls(df_connection *conn, int RoomID, int Replace, char* Urls, int StartTrack, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayUrls", 1, -1,PlayUrls_handler, c, "[PlayUrls %d %d \"%s\" %d]", RoomID, Replace, Urls, StartTrack);
}

int df_PrevTrack(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PrevTrack", 1, -1,PrevTrack_handler, c, "[PrevTrack %d]", RoomID);
}

int df_ProcessEmbeddedInit(df_connection *conn, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ProcessEmbeddedInit", 1, -1,ProcessEmbeddedInit_handler, c, "[ProcessEmbeddedInit]");
}

int df_PromoteShareToMusicStore(df_connection *conn, char* ShareKey, int ChangeOwnership, void (*callback)(df_promoteshare*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PromoteShareToMusicStore", 1, -1,PromoteShareToMusicStore_handler, c, "[PromoteShareToMusicStore \"%s\" %d]", ShareKey, ChangeOwnership);
}

int df_QueryAllPlayback(df_connection *conn, int RoomID, void (*callback)(df_queryplayback*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "QueryAllPlayback", 1, -1,QueryAllPlayback_handler, c, "[QueryAllPlayback %d]", RoomID);
}

int df_ReleaseSerialPort(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ReleaseSerialPort", 1, -1,ReleaseSerialPort_handler, c, "[ReleaseSerialPort]");
}

int df_RemoveAlbumsFromUserPlaylist(df_connection *conn, char* UserPlaylistKey, char* AlbumKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RemoveAlbumsFromUserPlaylist", 1, -1,RemoveAlbumsFromUserPlaylist_handler, c, "[RemoveAlbumsFromUserPlaylist \"%s\" \"%s\"]", UserPlaylistKey, AlbumKey);
}

int df_RemoveCoverImage(df_connection *conn, char* Address, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RemoveCoverImage", 1, -1,RemoveCoverImage_handler, c, "[RemoveCoverImage \"%s\"]", Address);
}

int df_RemoveExternalStorage(df_connection *conn, int StorageKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RemoveExternalStorage", 1, -1,RemoveExternalStorage_handler, c, "[RemoveExternalStorage %d]", StorageKey);
}

int df_RemoveOldRooms(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RemoveOldRooms", 1, -1,RemoveOldRooms_handler, c, "[RemoveOldRooms %d]", TimeoutPerHost);
}

int df_RemovePlayerInstance(df_connection *conn, int RoomID, int Key, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RemovePlayerInstance", 1, -1,RemovePlayerInstance_handler, c, "[RemovePlayerInstance %d %d]", RoomID, Key);
}

int df_RemoveTrack(df_connection *conn, int RoomID, int TrackNumber, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RemoveTrack", 1, -1,RemoveTrack_handler, c, "[RemoveTrack %d %d]", RoomID, TrackNumber);
}

int df_RenameAlbum(df_connection *conn, char* AlbumKey, char* NewAlbumName, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RenameAlbum", 1, -1,RenameAlbum_handler, c, "[RenameAlbum \"%s\" \"%s\"]", AlbumKey, NewAlbumName);
}

int df_RenameArtist(df_connection *conn, char* AlbumKey, char* NewArtistName, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RenameArtist", 1, -1,RenameArtist_handler, c, "[RenameArtist \"%s\" \"%s\"]", AlbumKey, NewArtistName);
}

int df_RenamePlaylist(df_connection *conn, char* PlaylistKey, char* NewName, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RenamePlaylist", 1, -1,RenamePlaylist_handler, c, "[RenamePlaylist \"%s\" \"%s\"]", PlaylistKey, NewName);
}

int df_RenameTrack(df_connection *conn, char* TrackKey, char* NewTrackName, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RenameTrack", 1, -1,RenameTrack_handler, c, "[RenameTrack \"%s\" \"%s\"]", TrackKey, NewTrackName);
}

int df_RequestAlbumCover(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RequestAlbumCover", 1, -1,RequestAlbumCover_handler, c, "[RequestAlbumCover \"%s\"]", Address);
}

int df_RescanExternalStorages(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RescanExternalStorages", 1, -1,RescanExternalStorages_handler, c, "[RescanExternalStorages]");
}

int df_RescanMusicStore(df_connection *conn, char* MusicStoreKey, void (*callback)(df_rescanresult*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RescanMusicStore", 1, -1,RescanMusicStore_handler, c, "[RescanMusicStore \"%s\"]", MusicStoreKey);
}

int df_RestoreSingleAlbum(df_connection *conn, char* AlbumKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RestoreSingleAlbum", 1, -1,RestoreSingleAlbum_handler, c, "[RestoreSingleAlbum \"%s\"]", AlbumKey);
}

int df_RestoreSingleTrack(df_connection *conn, char* AlbumKey, char* TrackKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RestoreSingleTrack", 1, -1,RestoreSingleTrack_handler, c, "[RestoreSingleTrack \"%s\" \"%s\"]", AlbumKey, TrackKey);
}

int df_SaveCurrentPlayList(df_connection *conn, int RoomID, char* NewName, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SaveCurrentPlayList", 1, -1,SaveCurrentPlayList_handler, c, "[SaveCurrentPlayList %d \"%s\"]", RoomID, NewName);
}

int df_SavePlayerInstance(df_connection *conn, int RoomID, int Key, int OutputDeviceID, int SourceLineID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SavePlayerInstance", 1, -1,SavePlayerInstance_handler, c, "[SavePlayerInstance %d %d %d %d]", RoomID, Key, OutputDeviceID, SourceLineID);
}

int df_ScanExternalStorage(df_connection *conn, char* StorageKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ScanExternalStorage", 1, -1,ScanExternalStorage_handler, c, "[ScanExternalStorage \"%s\"]", StorageKey);
}

int df_ScanForExternalStorages(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ScanForExternalStorages", 1, -1,ScanForExternalStorages_handler, c, "[ScanForExternalStorages]");
}

int df_ServiceMode(df_connection *conn, void (*callback)(df_servicemode*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ServiceMode", 1, -1,ServiceMode_handler, c, "[ServiceMode]");
}

int df_SetAlbumLowQuality(df_connection *conn, char* AlbumKey, int LowQuality, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetAlbumLowQuality", 1, -1,SetAlbumLowQuality_handler, c, "[SetAlbumLowQuality \"%s\" %d]", AlbumKey, LowQuality);
}

int df_SetCoverImage(df_connection *conn, char* Address, int ForceOverwrite, char* ImageData, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetCoverImage", 1, -1,SetCoverImage_handler, c, "[SetCoverImage \"%s\" %d \"%s\"]", Address, ForceOverwrite, ImageData);
}

int df_SetDriveUsage(df_connection *conn, char* DriveKey, int Usage, int ForceChange, void (*callback)(df_driveusageresult*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetDriveUsage", 1, -1,SetDriveUsage_handler, c, "[SetDriveUsage \"%s\" %d %d]", DriveKey, Usage, ForceChange);
}

int df_SetMusicStoreCredentials(df_connection *conn, char* MusicStoreKey, char* Username, char* Password, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetMusicStoreCredentials", 1, -1,SetMusicStoreCredentials_handler, c, "[SetMusicStoreCredentials \"%s\" \"%s\" \"%s\"]", MusicStoreKey, Username, Password);
}

int df_SetMusicStorePriority(df_connection *conn, char* MusicStoreKey, int Priority, void (*callback)(df_musicstorepriorityresult*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetMusicStorePriority", 1, -1,SetMusicStorePriority_handler, c, "[SetMusicStorePriority \"%s\" %d]", MusicStoreKey, Priority);
}

int df_StopBackupDrive(df_connection *conn, void (*callback)(df_stopbackupdriveresult*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "StopBackupDrive", 1, -1,StopBackupDrive_handler, c, "[StopBackupDrive]");
}

int df_ToggleDeviceSync(df_connection *conn, int Key, int Sync, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ToggleDeviceSync", 1, -1,ToggleDeviceSync_handler, c, "[ToggleDeviceSync %d %d]", Key, Sync);
}

int df_UpdateBackupJob(df_connection *conn, char* Address, char* SourceDriveAddress, char* DestinationDriveAddress, char* Name, int BackupType, int BackupPeriod, int PeriodValue, df_date RunDate, df_time RunTime, void (*callback)(int, void*), void *context) {	char *RunDate_string;
	char *RunTime_string;

	struct call_holder *c;
	RunDate_string = dfdate_to_string(RunDate);
	RunTime_string = dftime_to_string(RunTime);

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateBackupJob", 1, -1,UpdateBackupJob_handler, c, "[UpdateBackupJob \"%s\" \"%s\" \"%s\" \"%s\" %d %d %d \"%s\" \"%s\"]", Address, SourceDriveAddress, DestinationDriveAddress, Name, BackupType, BackupPeriod, PeriodValue, RunDate_string, RunTime_string);
}

int df_UpdateDrive(df_connection *conn, char* DriveKey, char* DriveLetter, int PrimaryDrive, char* RootPath, char* SharePath, int BadPathBehaviour, void (*callback)(df_updatedrivedetails*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateDrive", 1, -1,UpdateDrive_handler, c, "[UpdateDrive \"%s\" \"%s\" %d \"%s\" \"%s\" %d]", DriveKey, DriveLetter, PrimaryDrive, RootPath, SharePath, BadPathBehaviour);
}

int df_UpdateExternalStorage(df_connection *conn, char* StorageKey, char* IPAddress, char* HostName, char* ShareName, char* UserName, char* Password, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateExternalStorage", 1, -1,UpdateExternalStorage_handler, c, "[UpdateExternalStorage \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"]", StorageKey, IPAddress, HostName, ShareName, UserName, Password);
}

int df_UpdateGenre(df_connection *conn, char* GenreKey, char* GenreName, int Ordinal, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateGenre", 1, -1,UpdateGenre_handler, c, "[UpdateGenre \"%s\" \"%s\" %d]", GenreKey, GenreName, Ordinal);
}

int df_UpdateHitCount(df_connection *conn, char* Address, int ResetHitCount, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateHitCount", 1, -1,UpdateHitCount_handler, c, "[UpdateHitCount \"%s\" %d]", Address, ResetHitCount);
}

int df_UpdateLinkedRoom(df_connection *conn, char* RoomKey, char* RoomName, char* ShortName, int RoomID, char* ChildRoomKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateLinkedRoom", 1, -1,UpdateLinkedRoom_handler, c, "[UpdateLinkedRoom \"%s\" \"%s\" \"%s\" %d \"%s\"]", RoomKey, RoomName, ShortName, RoomID, ChildRoomKey);
}

int df_UpdateOutputChannel(df_connection *conn, int RoomID, char* HostName, int ChannelNumber, char* InitString, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateOutputChannel", 1, -1,UpdateOutputChannel_handler, c, "[UpdateOutputChannel %d \"%s\" %d \"%s\"]", RoomID, HostName, ChannelNumber, InitString);
}

int df_UpdatePlaylist(df_connection *conn, char* PlaylistKey, char* Name, char* TrackKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdatePlaylist", 1, -1,UpdatePlaylist_handler, c, "[UpdatePlaylist \"%s\" \"%s\" \"%s\"]", PlaylistKey, Name, TrackKey);
}

int df_UpdateRoom(df_connection *conn, char* RoomKey, char* RoomIP, int Channel, char* RoomName, char* ShortName, int PlaybackCapability, int RippingCapability, int MusicManagementCapability, int RoomID, char* HostName, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateRoom", 1, -1,UpdateRoom_handler, c, "[UpdateRoom \"%s\" \"%s\" %d \"%s\" \"%s\" %d %d %d %d \"%s\"]", RoomKey, RoomIP, Channel, RoomName, ShortName, PlaybackCapability, RippingCapability, MusicManagementCapability, RoomID, HostName);
}

int df_UpdateSingleRipEncSetting(df_connection *conn, int RoomID, char* SettingName, char* NewValue, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateSingleRipEncSetting", 1, -1,UpdateSingleRipEncSetting_handler, c, "[UpdateSingleRipEncSetting %d \"%s\" \"%s\"]", RoomID, SettingName, NewValue);
}

int df_UpdateSingleSystemSetting(df_connection *conn, int RoomID, char* SettingName, char* NewValue, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateSingleSystemSetting", 1, -1,UpdateSingleSystemSetting_handler, c, "[UpdateSingleSystemSetting %d \"%s\" \"%s\"]", RoomID, SettingName, NewValue);
}

int df_UpdateSubGenre(df_connection *conn, char* SubGenreKey, char* GenreKey, char* SubGenreName, int Ordinal, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateSubGenre", 1, -1,UpdateSubGenre_handler, c, "[UpdateSubGenre \"%s\" \"%s\" \"%s\" %d]", SubGenreKey, GenreKey, SubGenreName, Ordinal);
}

int df_UploadMessages(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UploadMessages", 1, -1,UploadMessages_handler, c, "[UploadMessages]");
}

int df_Version(df_connection *conn, void (*callback)(df_version*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "Version", 1, -1,Version_handler, c, "[Version]");
}

int df_vTunerAddRemoveFavourite(df_connection *conn, char* vTunerUrl, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerAddRemoveFavourite", 1, -1,vTunerAddRemoveFavourite_handler, c, "[vTunerAddRemoveFavourite \"%s\"]", vTunerUrl);
}

int df_vTunerCheckAvailability(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerCheckAvailability", 1, -1,vTunerCheckAvailability_handler, c, "[vTunerCheckAvailability]");
}

int df_vTunerPlayById(df_connection *conn, int RoomID, int Replace, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerPlayById", 1, -1,vTunerPlayById_handler, c, "[vTunerPlayById %d %d \"%s\"]", RoomID, Replace, Address);
}

int df_vTunerPlayByIds(df_connection *conn, int RoomID, int Replace, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerPlayByIds", 1, -1,vTunerPlayByIds_handler, c, "[vTunerPlayByIds %d %d \"%s\"]", RoomID, Replace, Address);
}

int df_vTunerSetPresetChannel(df_connection *conn, int ChannelNumber, char* VTunerID, char* ChannelName, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerSetPresetChannel", 1, -1,vTunerSetPresetChannel_handler, c, "[vTunerSetPresetChannel %d \"%s\" \"%s\"]", ChannelNumber, VTunerID, ChannelName);
}





// Set commands

int df_CDLookupCancel(df_connection *conn, char* Address) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[CDLookupCancel \"%s\"]", Address);
}

int df_ChangeCDDBSubGenreAssociation(df_connection *conn, char* GenreKey, char* NewSubGenreKey) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[ChangeCDDBSubGenreAssociation \"%s\" \"%s\"]", GenreKey, NewSubGenreKey);
}

int df_ClearAllPlaying(df_connection *conn) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[ClearAllPlaying]");
}

int df_ClearDownloadFolder(df_connection *conn, int RoomID) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[ClearDownloadFolder %d]", RoomID);
}

int df_ClearPlaylist(df_connection *conn, int RoomID) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[ClearPlaylist %d]", RoomID);
}

int df_DisableField(df_connection *conn, char* FormatList, char* FieldName) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[DisableField \"%s\" \"%s\"]", FormatList, FieldName);
}

int df_EjectCD(df_connection *conn, int RoomID) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[EjectCD %d]", RoomID);
}

int df_EmptyRecycleBin(df_connection *conn) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[EmptyRecycleBin]");
}

int df_EmptyRipShare(df_connection *conn, int RoomID) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[EmptyRipShare %d]", RoomID);
}

int df_EnableField(df_connection *conn, char* FormatList, char* FieldName) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[EnableField \"%s\" \"%s\"]", FormatList, FieldName);
}

int df_FastForward(df_connection *conn, int RoomID) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[FastForward %d]", RoomID);
}

int df_FastRewind(df_connection *conn, int RoomID) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[FastRewind %d]", RoomID);
}

int df_ForceDBRebuild(df_connection *conn) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[ForceDBRebuild]");
}

int df_ForceHostUpgrade(df_connection *conn, int RoomID) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[ForceHostUpgrade %d]", RoomID);
}

int df_MasterIpChanged(df_connection *conn, char* MasterName, char* MasterAddress) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[MasterIpChanged \"%s\" \"%s\"]", MasterName, MasterAddress);
}

int df_MoveAlbumCancel(df_connection *conn, char* Address) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[MoveAlbumCancel \"%s\"]", Address);
}

int df_Pause(df_connection *conn, int RoomID) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[Pause %d]", RoomID);
}

int df_Play(df_connection *conn, int RoomID) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[Play %d]", RoomID);
}

int df_PurgeImageCache(df_connection *conn, int All) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[PurgeImageCache %d]", All);
}

int df_RandomisePlaylist(df_connection *conn, int RoomID) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[RandomisePlaylist %d]", RoomID);
}

int df_RestartDevice(df_connection *conn) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[RestartDevice]");
}

int df_RoomIpChanged(df_connection *conn) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[RoomIpChanged]");
}

int df_SetCDDetected(df_connection *conn, int CDDetected) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[SetCDDetected %d]", CDDetected);
}

int df_SetConnOption(df_connection *conn, char* OptionName, char* OptionValue) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[SetConnOption \"%s\" \"%s\"]", OptionName, OptionValue);
}

int df_SetLength(df_connection *conn, char* FormatList, char* FieldName, int Length) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[SetLength \"%s\" \"%s\" %d]", FormatList, FieldName, Length);
}

int df_SetRepeat(df_connection *conn, int RoomID, int Repeat) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[SetRepeat %d %d]", RoomID, Repeat);
}

int df_SetRippingStatus(df_connection *conn, char* Artist, char* Album, int Tracks, int TracksRipped, int Errors, df_time TimeTaken, df_time TimeLeft, char* Track, int TrackPercent, char* UserMessage, char* LookupProviderUsed, char* SourceFolder) {	char *TimeTaken_string;
	char *TimeLeft_string;

	TimeTaken_string = dftime_to_string(TimeTaken);
	TimeLeft_string = dftime_to_string(TimeLeft);

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[SetRippingStatus \"%s\" \"%s\" %d %d %d \"%s\" \"%s\" \"%s\" %d \"%s\" \"%s\" \"%s\"]", Artist, Album, Tracks, TracksRipped, Errors, TimeTaken_string, TimeLeft_string, Track, TrackPercent, UserMessage, LookupProviderUsed, SourceFolder);
}

int df_SetShuffle(df_connection *conn, int RoomID, int Shuffle) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[SetShuffle %d %d]", RoomID, Shuffle);
}

int df_SetTrack(df_connection *conn, int RoomID, int TrackNumber) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[SetTrack %d %d]", RoomID, TrackNumber);
}

int df_SetTrackPosition(df_connection *conn, int RoomID, df_time PlayPosition) {	char *PlayPosition_string;

	PlayPosition_string = dftime_to_string(PlayPosition);

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[SetTrackPosition %d \"%s\"]", RoomID, PlayPosition_string);
}

int df_SetVolume(df_connection *conn, int RoomID, int Volume) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[SetVolume %d %d]", RoomID, Volume);
}

int df_Stop(df_connection *conn, int RoomID) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[Stop %d]", RoomID);
}

int df_vTunerCleanStatistics(df_connection *conn) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[vTunerCleanStatistics]");
}

int df_vTunerClearPresetChannel(df_connection *conn, int ChannelNumber) {

	return comm_send(conn, 0, "void", 1, -1,NULL, NULL, "[vTunerClearPresetChannel %d]", ChannelNumber);
}





// Row commands

void df_driverow_free(df_driverow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_driverow_free(ptr->next); }

	free(ptr->DriveLetter);
	free(ptr->RootPath);
	free(ptr->SharePath);

	free(ptr);
}

void df_outputdevicerow_free(df_outputdevicerow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_outputdevicerow_free(ptr->next); }

	free(ptr->Name);

	free(ptr);
}

void df_type1row_free(df_type1row *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_type1row_free(ptr->next); }

	free(ptr->Artist);
	free(ptr->Album);
	free(ptr->Track);
	free(ptr->UserMessage);
	free(ptr->LookupProviderUsed);
	free(ptr->Destination);

	free(ptr);
}

void df_settingsexrow_free(df_settingsexrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_settingsexrow_free(ptr->next); }

	free(ptr->RegistryKey);
	free(ptr->Value);
	free(ptr->Default);
	free(ptr->TabCaption);
	free(ptr->Category);
	free(ptr->Caption);
	free(ptr->ShortTabCaption);
	free(ptr->ShortCategory);
	free(ptr->ShortCaption);
	free(ptr->Description);

	free(ptr);
}

void df_effformatrow_free(df_effformatrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_effformatrow_free(ptr->next); }

	free(ptr->FieldName);
	free(ptr->FormatSource);

	free(ptr);
}

void df_artistrow_free(df_artistrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_artistrow_free(ptr->next); }

	free(ptr->Name);

	free(ptr);
}

void df_type0row_free(df_type0row *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_type0row_free(ptr->next); }

	free(ptr->Name);
	free(ptr->SortName);
	free(ptr->Type);
	free(ptr->AlbumName);
	free(ptr->ArtistName);
	free(ptr->SubGenre);
	free(ptr->CoverURL);

	free(ptr);
}

void df_tracksotherrow_free(df_tracksotherrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_tracksotherrow_free(ptr->next); }

	free(ptr->Name);
	free(ptr->SortName);
	free(ptr->Type);
	free(ptr->AlbumName);
	free(ptr->ArtistName);
	free(ptr->SubGenre);
	free(ptr->CoverURL);

	free(ptr);
}

void df_exttrackinforow_free(df_exttrackinforow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_exttrackinforow_free(ptr->next); }

	free(ptr->CompositionDate);
	free(ptr->Part);
	free(ptr->PerformanceDate);
	free(ptr->Work);

	free(ptr);
}

void df_outputchannelrow_free(df_outputchannelrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_outputchannelrow_free(ptr->next); }

	free(ptr->InitString);

	free(ptr);
}

void df_currplaylistexrow_free(df_currplaylistexrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_currplaylistexrow_free(ptr->next); }

	free(ptr->Name);
	free(ptr->SortName);
	free(ptr->Type);
	free(ptr->AlbumName);
	free(ptr->ArtistName);
	free(ptr->SubGenre);
	free(ptr->CoverURL);

	free(ptr);
}

void df_extcontributorrow_free(df_extcontributorrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_extcontributorrow_free(ptr->next); }

	free(ptr->Name);

	free(ptr);
}

void df_encodingstatusrow_free(df_encodingstatusrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_encodingstatusrow_free(ptr->next); }

	free(ptr->Artist);
	free(ptr->Album);
	free(ptr->Track);
	free(ptr->Activity);

	free(ptr);
}

void df_vtunerpresetrow_free(df_vtunerpresetrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_vtunerpresetrow_free(ptr->next); }

	free(ptr->ChannelName);
	free(ptr->Name);
	free(ptr->UrlBookmark);
	free(ptr->UrlPlay);
	free(ptr->UrlChildren);
	free(ptr->UrlChildrenBackup);
	free(ptr->ID);
	free(ptr->Description);
	free(ptr->ParentDescription);
	free(ptr->Format);
	free(ptr->Language);
	free(ptr->City);
	free(ptr->State);
	free(ptr->Country);
	free(ptr->Location);
	free(ptr->MimeType);

	free(ptr);
}

void df_albumrow_free(df_albumrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_albumrow_free(ptr->next); }

	free(ptr->Name);
	free(ptr->ArtistName);

	free(ptr);
}

void df_trackrow_free(df_trackrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_trackrow_free(ptr->next); }

	free(ptr->Name);
	free(ptr->SortName);
	free(ptr->Type);

	free(ptr);
}

void df_settingsrow_free(df_settingsrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_settingsrow_free(ptr->next); }

	free(ptr->RegistryKey);
	free(ptr->Value);
	free(ptr->Default);

	free(ptr);
}

void df_linkedroomdetailrow_free(df_linkedroomdetailrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_linkedroomdetailrow_free(ptr->next); }

	free(ptr->IPAddress);
	free(ptr->RoomName);
	free(ptr->ShortName);
	free(ptr->HostName);

	free(ptr);
}

void df_albumdetailrow_free(df_albumdetailrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_albumdetailrow_free(ptr->next); }

	free(ptr->Name);
	free(ptr->ArtistName);
	free(ptr->Genre);
	free(ptr->CoverImage);

	free(ptr);
}

void df_genrerow_free(df_genrerow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_genrerow_free(ptr->next); }

	free(ptr->Genre);

	free(ptr);
}

void df_type4row_free(df_type4row *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_type4row_free(ptr->next); }

	free(ptr->Status);
	free(ptr->LastError);

	free(ptr);
}

void df_mediarendererrow_free(df_mediarendererrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_mediarendererrow_free(ptr->next); }

	free(ptr->FriendlyName);
	free(ptr->UDN);
	free(ptr->Manufacturer);
	free(ptr->ModelNumber);
	free(ptr->SupportedExtensions);

	free(ptr);
}

void df_subgenrerow_free(df_subgenrerow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_subgenrerow_free(ptr->next); }

	free(ptr->SubGenre);

	free(ptr);
}

void df_statusmessagerow_free(df_statusmessagerow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_statusmessagerow_free(ptr->next); }

	free(ptr->Severity);
	free(ptr->Category);

	free(ptr);
}

void df_type3row_free(df_type3row *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_type3row_free(ptr->next); }

	free(ptr->Name);
	free(ptr->SortName);
	free(ptr->Type);
	free(ptr->AlbumName);
	free(ptr->ArtistName);
	free(ptr->SubGenre);
	free(ptr->CoverURL);

	free(ptr);
}

void df_exttrackcontribrow_free(df_exttrackcontribrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_exttrackcontribrow_free(ptr->next); }

	free(ptr->Name);

	free(ptr);
}

void df_vtunerplayedrow_free(df_vtunerplayedrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_vtunerplayedrow_free(ptr->next); }

	free(ptr->Name);
	free(ptr->UrlBookmark);
	free(ptr->UrlPlay);
	free(ptr->UrlChildren);
	free(ptr->UrlChildrenBackup);
	free(ptr->ID);
	free(ptr->Description);
	free(ptr->ParentDescription);
	free(ptr->Format);
	free(ptr->Language);
	free(ptr->City);
	free(ptr->State);
	free(ptr->Country);
	free(ptr->Location);
	free(ptr->MimeType);

	free(ptr);
}

void df_cddbgenrerow_free(df_cddbgenrerow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_cddbgenrerow_free(ptr->next); }

	free(ptr->Name);
	free(ptr->SubGenreName);

	free(ptr);
}

void df_playerinstancerow_free(df_playerinstancerow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_playerinstancerow_free(ptr->next); }

	free(ptr->Name);

	free(ptr);
}

void df_albumotherrow_free(df_albumotherrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_albumotherrow_free(ptr->next); }

	free(ptr->Name);
	free(ptr->ArtistName);
	free(ptr->Genre);
	free(ptr->SubGenre);
	free(ptr->StorageName);

	free(ptr);
}

void df_roomrow_free(df_roomrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_roomrow_free(ptr->next); }

	free(ptr->IPAddress);
	free(ptr->Name);
	free(ptr->ShortName);
	free(ptr->HostName);

	free(ptr);
}

void df_currentplaylistrow_free(df_currentplaylistrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_currentplaylistrow_free(ptr->next); }

	free(ptr->Name);
	free(ptr->SortName);
	free(ptr->Type);

	free(ptr);
}

void df_storerow_free(df_storerow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_storerow_free(ptr->next); }

	free(ptr->Path);
	free(ptr->IPAddress);
	free(ptr->State);

	free(ptr);
}

void df_statusrow_free(df_statusrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_statusrow_free(ptr->next); }

	free(ptr->StatusSettingName);
	free(ptr->StatusSettingValue);

	free(ptr);
}

void df_networkadaptorrow_free(df_networkadaptorrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_networkadaptorrow_free(ptr->next); }

	free(ptr->Description);
	free(ptr->MacAddress);
	free(ptr->IpAddress);
	free(ptr->SubnetMask);
	free(ptr->DefaultGateway);
	free(ptr->DnsServer);

	free(ptr);
}

void df_extworksrow_free(df_extworksrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_extworksrow_free(ptr->next); }

	free(ptr->Work);

	free(ptr);
}

void df_backuplogdetailrow_free(df_backuplogdetailrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_backuplogdetailrow_free(ptr->next); }

	free(ptr->Name);
	free(ptr->SourcePath);
	free(ptr->DestinationPath);
	free(ptr->ErrorDetail);

	free(ptr);
}

void df_extalbumcreditrow_free(df_extalbumcreditrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_extalbumcreditrow_free(ptr->next); }

	free(ptr->Description);
	free(ptr->ContributorName);

	free(ptr);
}

void df_trackrangerow_free(df_trackrangerow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_trackrangerow_free(ptr->next); }

	free(ptr->Name);
	free(ptr->SortName);
	free(ptr->Type);

	free(ptr);
}

void df_keyvaluerow_free(df_keyvaluerow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_keyvaluerow_free(ptr->next); }

	free(ptr->Name);
	free(ptr->Value);

	free(ptr);
}

void df_backuplogrow_free(df_backuplogrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_backuplogrow_free(ptr->next); }

	free(ptr->Name);
	free(ptr->SourcePath);
	free(ptr->DestinationPath);

	free(ptr);
}

void df_tracksforplaylistrow_free(df_tracksforplaylistrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_tracksforplaylistrow_free(ptr->next); }

	free(ptr->Name);
	free(ptr->SortName);
	free(ptr->Type);

	free(ptr);
}

void df_rippingalertrow_free(df_rippingalertrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_rippingalertrow_free(ptr->next); }

	free(ptr->Severity);
	free(ptr->Category);

	free(ptr);
}

void df_rippingstatusrow_free(df_rippingstatusrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_rippingstatusrow_free(ptr->next); }

	free(ptr->Artist);
	free(ptr->Album);
	free(ptr->Track);
	free(ptr->UserMessage);
	free(ptr->LookupProviderUsed);

	free(ptr);
}

void df_extalbuminforow_free(df_extalbuminforow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_extalbuminforow_free(ptr->next); }

	free(ptr->CatalogID);
	free(ptr->ImageURL);

	free(ptr);
}

void df_backupjobrow_free(df_backupjobrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_backupjobrow_free(ptr->next); }

	free(ptr->Name);

	free(ptr);
}

void df_genressubgenresrow_free(df_genressubgenresrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_genressubgenresrow_free(ptr->next); }

	free(ptr->SubGenre);
	free(ptr->Genre);

	free(ptr);
}

void df_alertdetailrow_free(df_alertdetailrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_alertdetailrow_free(ptr->next); }

	free(ptr->Severity);
	free(ptr->Category);
	free(ptr->Module);
	free(ptr->Message);
	free(ptr->UserMessage);

	free(ptr);
}

void df_encodingqueuerow_free(df_encodingqueuerow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_encodingqueuerow_free(ptr->next); }

	free(ptr->Value);

	free(ptr);
}

void df_movealbumgetqueuerow_free(df_movealbumgetqueuerow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_movealbumgetqueuerow_free(ptr->next); }

	free(ptr->Status);
	free(ptr->LastError);

	free(ptr);
}

void df_type2row_free(df_type2row *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_type2row_free(ptr->next); }

	free(ptr->Name);
	free(ptr->ArtistName);
	free(ptr->Genre);
	free(ptr->SubGenre);
	free(ptr->StorageName);
	free(ptr->CoverURL);

	free(ptr);
}

void df_storedetailrow_free(df_storedetailrow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_storedetailrow_free(ptr->next); }

	free(ptr->Path);
	free(ptr->IPAddress);
	free(ptr->State);
	free(ptr->Username);
	free(ptr->Password);
	free(ptr->SpaceUsed);
	free(ptr->SpaceAvailable);

	free(ptr);
}

void df_externalstoragerow_free(df_externalstoragerow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_externalstoragerow_free(ptr->next); }

	free(ptr->IPAddress);
	free(ptr->HostName);
	free(ptr->ShareName);
	free(ptr->FullSharePath);
	free(ptr->State);
	free(ptr->LastState);
	free(ptr->UserName);
	free(ptr->Password);
	free(ptr->ScanIgnore);

	free(ptr);
}

void df_bulklookuprow_free(df_bulklookuprow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_bulklookuprow_free(ptr->next); }

	free(ptr->Message);

	free(ptr);
}

void df_vtunernoderow_free(df_vtunernoderow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_vtunernoderow_free(ptr->next); }

	free(ptr->Name);
	free(ptr->UrlBookmark);
	free(ptr->UrlPlay);
	free(ptr->UrlChildren);
	free(ptr->UrlChildrenBackup);
	free(ptr->ID);
	free(ptr->Description);
	free(ptr->ParentDescription);
	free(ptr->Format);
	free(ptr->Language);
	free(ptr->City);
	free(ptr->State);
	free(ptr->Country);
	free(ptr->Location);
	free(ptr->MimeType);

	free(ptr);
}

void df_devicerow_free(df_devicerow *ptr) {
	if (ptr == NULL) { return; }
	if (ptr->next != NULL) { df_devicerow_free(ptr->next); }

	free(ptr->Name);
	free(ptr->SerialNumber);
	free(ptr->Type);
	free(ptr->State);
	free(ptr->LastState);

	free(ptr);
}

int df_AdvancedSearch(df_connection *conn, char* EntityName, char* SearchString, int SearchType, int Match, char* EntityName2, char* SearchString2, int SearchType2, int RemoteImagePath, int ImageSize, void (*callback)(int, df_type3row*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[AdvancedSearch %d \"%s\" \"%s\" %d %d \"%s\" \"%s\" %d %d %d]", search_num, EntityName, SearchString, SearchType, Match, EntityName2, SearchString2, SearchType2, RemoteImagePath, ImageSize);

}
int df_BulkCDLookup(df_connection *conn, int AllAlbums, int Interval, int IgnoreProviderUsed, char* AlbumKey, void (*callback)(int, df_bulklookuprow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[BulkCDLookup %d %d %d %d \"%s\"]", search_num, AllAlbums, Interval, IgnoreProviderUsed, AlbumKey);

}
int df_CDLookupGetQueue(df_connection *conn, void (*callback)(int, df_type4row*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[CDLookupGetQueue %d]", search_num);

}
int df_ComplexSearchGetAlbums(df_connection *conn, char* SearchParameter, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[ComplexSearchGetAlbums %d \"%s\" \"%s\" \"%s\"]", search_num, SearchParameter, SortColumn, SortOrder);

}
int df_ComplexSearchGetArtists(df_connection *conn, char* SearchParameter, void (*callback)(int, df_artistrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[ComplexSearchGetArtists %d \"%s\"]", search_num, SearchParameter);

}
int df_ComplexSearchGetContributors(df_connection *conn, int Type, char* SearchParameter, void (*callback)(int, df_extcontributorrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[ComplexSearchGetContributors %d %d \"%s\"]", search_num, Type, SearchParameter);

}
int df_ComplexSearchGetTracks(df_connection *conn, char* SearchParameter, void (*callback)(int, df_trackrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[ComplexSearchGetTracks %d \"%s\"]", search_num, SearchParameter);

}
int df_GetAdvancedStatus(df_connection *conn, void (*callback)(int, df_keyvaluerow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAdvancedStatus %d]", search_num);

}
int df_GetAlbumDetails(df_connection *conn, char* Address, void (*callback)(int, df_albumdetailrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlbumDetails %d \"%s\"]", search_num, Address);

}
int df_GetAlbums(df_connection *conn, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlbums %d \"%s\" \"%s\"]", search_num, SortColumn, SortOrder);

}
int df_GetAlbumsForArtists(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlbumsForArtists %d \"%s\" \"%s\" \"%s\"]", search_num, Address, SortColumn, SortOrder);

}
int df_GetAlbumsForArtistsForDevice(df_connection *conn, char* Address, char* DeviceAddress, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlbumsForArtistsForDevice %d \"%s\" \"%s\" \"%s\" \"%s\"]", search_num, Address, DeviceAddress, SortColumn, SortOrder);

}
int df_GetAlbumsForArtistsForServer(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlbumsForArtistsForServer %d \"%s\" \"%s\" \"%s\"]", search_num, Address, SortColumn, SortOrder);

}
int df_GetAlbumsForArtistsForShare(df_connection *conn, char* Address, char* ShareAddress, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlbumsForArtistsForShare %d \"%s\" \"%s\" \"%s\" \"%s\"]", search_num, Address, ShareAddress, SortColumn, SortOrder);

}
int df_GetAlbumsForArtistsInGenre(df_connection *conn, char* Address, char* GenreAddress, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlbumsForArtistsInGenre %d \"%s\" \"%s\" \"%s\" \"%s\"]", search_num, Address, GenreAddress, SortColumn, SortOrder);

}
int df_GetAlbumsForArtistsInSubGenre(df_connection *conn, char* Address, char* SubGenreAddress, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlbumsForArtistsInSubGenre %d \"%s\" \"%s\" \"%s\" \"%s\"]", search_num, Address, SubGenreAddress, SortColumn, SortOrder);

}
int df_GetAlbumsForDeletion(df_connection *conn, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlbumsForDeletion %d \"%s\" \"%s\"]", search_num, SortColumn, SortOrder);

}
int df_GetAlbumsForDevice(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlbumsForDevice %d \"%s\" \"%s\" \"%s\"]", search_num, Address, SortColumn, SortOrder);

}
int df_GetAlbumsForPlaylist(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlbumsForPlaylist %d \"%s\" \"%s\" \"%s\"]", search_num, Address, SortColumn, SortOrder);

}
int df_GetAlbumsForServer(df_connection *conn, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlbumsForServer %d \"%s\" \"%s\"]", search_num, SortColumn, SortOrder);

}
int df_GetAlbumsForShare(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlbumsForShare %d \"%s\" \"%s\" \"%s\"]", search_num, Address, SortColumn, SortOrder);

}
int df_GetAlbumsForStore(df_connection *conn, char* StoreKey, int IncludeDeleted, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlbumsForStore %d \"%s\" %d \"%s\" \"%s\"]", search_num, StoreKey, IncludeDeleted, SortColumn, SortOrder);

}
int df_GetAlbumsOtherInfo(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, int RemoteImagePath, int ImageSize, void (*callback)(int, df_type2row*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlbumsOtherInfo %d \"%s\" \"%s\" \"%s\" %d %d]", search_num, Address, SortColumn, SortOrder, RemoteImagePath, ImageSize);

}
int df_GetAlbumsOtherInfoAll(df_connection *conn, char* SortColumn, char* SortOrder, int RemoteImagePath, int ImageSize, void (*callback)(int, df_type2row*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlbumsOtherInfoAll %d \"%s\" \"%s\" %d %d]", search_num, SortColumn, SortOrder, RemoteImagePath, ImageSize);

}
int df_GetAlbumsOtherInfoForDevice(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, int RemoteImagePath, int ImageSize, void (*callback)(int, df_type2row*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlbumsOtherInfoForDevice %d \"%s\" \"%s\" \"%s\" %d %d]", search_num, Address, SortColumn, SortOrder, RemoteImagePath, ImageSize);

}
int df_GetAlbumsOtherInfoForServer(df_connection *conn, char* SortColumn, char* SortOrder, int RemoteImagePath, int ImageSize, void (*callback)(int, df_type2row*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlbumsOtherInfoForServer %d \"%s\" \"%s\" %d %d]", search_num, SortColumn, SortOrder, RemoteImagePath, ImageSize);

}
int df_GetAlbumsOtherInfoForShare(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, int RemoteImagePath, int ImageSize, void (*callback)(int, df_type2row*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlbumsOtherInfoForShare %d \"%s\" \"%s\" \"%s\" %d %d]", search_num, Address, SortColumn, SortOrder, RemoteImagePath, ImageSize);

}
int df_GetAlbumsSearchAlbumArtist(df_connection *conn, char* SearchString, char* SortColumn, char* SortOrder, int SearchType, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlbumsSearchAlbumArtist %d \"%s\" \"%s\" \"%s\" %d]", search_num, SearchString, SortColumn, SortOrder, SearchType);

}
int df_GetAlbumsWithAlbumLookupMessages(df_connection *conn, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlbumsWithAlbumLookupMessages %d]", search_num);

}
int df_GetAlertDetails(df_connection *conn, char* Address, void (*callback)(int, df_alertdetailrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAlertDetails %d \"%s\"]", search_num, Address);

}
int df_GetArtistDetails(df_connection *conn, char* Address, void (*callback)(int, df_artistrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetArtistDetails %d \"%s\"]", search_num, Address);

}
int df_GetArtists(df_connection *conn, int Allocated, void (*callback)(int, df_artistrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetArtists %d %d]", search_num, Allocated);

}
int df_GetArtistsForDevice(df_connection *conn, char* Address, void (*callback)(int, df_artistrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetArtistsForDevice %d \"%s\"]", search_num, Address);

}
int df_GetArtistsForServer(df_connection *conn, void (*callback)(int, df_artistrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetArtistsForServer %d]", search_num);

}
int df_GetArtistsForShare(df_connection *conn, char* Address, void (*callback)(int, df_artistrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetArtistsForShare %d \"%s\"]", search_num, Address);

}
int df_GetArtistsInGenre(df_connection *conn, char* Address, void (*callback)(int, df_artistrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetArtistsInGenre %d \"%s\"]", search_num, Address);

}
int df_GetArtistsInSubGenre(df_connection *conn, char* Address, void (*callback)(int, df_artistrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetArtistsInSubGenre %d \"%s\"]", search_num, Address);

}
int df_GetAvailableValues(df_connection *conn, char* Address, void (*callback)(int, df_keyvaluerow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetAvailableValues %d \"%s\"]", search_num, Address);

}
int df_GetBackupJobDetail(df_connection *conn, char* Address, void (*callback)(int, df_backupjobrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetBackupJobDetail %d \"%s\"]", search_num, Address);

}
int df_GetBackupJobs(df_connection *conn, void (*callback)(int, df_backupjobrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetBackupJobs %d]", search_num);

}
int df_GetBackupLogDetail(df_connection *conn, char* Address, void (*callback)(int, df_backuplogdetailrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetBackupLogDetail %d \"%s\"]", search_num, Address);

}
int df_GetBackupLogs(df_connection *conn, char* Address, void (*callback)(int, df_backuplogrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetBackupLogs %d \"%s\"]", search_num, Address);

}
int df_GetCDDBGenres(df_connection *conn, void (*callback)(int, df_cddbgenrerow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetCDDBGenres %d]", search_num);

}
int df_GetComponentVersions(df_connection *conn, int RoomID, void (*callback)(int, df_keyvaluerow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetComponentVersions %d %d]", search_num, RoomID);

}
int df_GetCurrentPlayList(df_connection *conn, int RoomID, void (*callback)(int, df_currentplaylistrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequestroom", 1, -1, pull_rows, (void *)c, "[GetCurrentPlayList %d %d]", search_num, RoomID);

}
int df_GetCurrentPlaylistEx(df_connection *conn, int RoomID, int RemoteImagePath, int ImageSize, void (*callback)(int, df_type0row*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequestroom", 1, -1, pull_rows, (void *)c, "[GetCurrentPlaylistEx %d %d %d %d]", search_num, RoomID, RemoteImagePath, ImageSize);

}
int df_GetDeviceDetails(df_connection *conn, char* DeviceAddress, void (*callback)(int, df_devicerow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetDeviceDetails %d \"%s\"]", search_num, DeviceAddress);

}
int df_GetDevices(df_connection *conn, int ActiveOnly, void (*callback)(int, df_devicerow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetDevices %d %d]", search_num, ActiveOnly);

}
int df_GetEncodingQueue(df_connection *conn, int RoomID, void (*callback)(int, df_encodingqueuerow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetEncodingQueue %d %d]", search_num, RoomID);

}
int df_GetEncodingStatus(df_connection *conn, int RoomID, void (*callback)(int, df_encodingstatusrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetEncodingStatus %d %d]", search_num, RoomID);

}
int df_GetExtAlbumCredits(df_connection *conn, char* Address, void (*callback)(int, df_extalbumcreditrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtAlbumCredits %d \"%s\"]", search_num, Address);

}
int df_GetExtAlbumsByContributor(df_connection *conn, char* Address, int Type, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtAlbumsByContributor %d \"%s\" %d \"%s\" \"%s\"]", search_num, Address, Type, SortColumn, SortOrder);

}
int df_GetExtAlbumsByContributorForDevice(df_connection *conn, char* Address, char* DeviceAddress, int Type, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtAlbumsByContributorForDevice %d \"%s\" \"%s\" %d \"%s\" \"%s\"]", search_num, Address, DeviceAddress, Type, SortColumn, SortOrder);

}
int df_GetExtAlbumsByContributorForServer(df_connection *conn, char* Address, int Type, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtAlbumsByContributorForServer %d \"%s\" %d \"%s\" \"%s\"]", search_num, Address, Type, SortColumn, SortOrder);

}
int df_GetExtAlbumsByContributorForShare(df_connection *conn, char* Address, char* ShareAddress, int Type, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtAlbumsByContributorForShare %d \"%s\" \"%s\" %d \"%s\" \"%s\"]", search_num, Address, ShareAddress, Type, SortColumn, SortOrder);

}
int df_GetExtAlbumsByCredit(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtAlbumsByCredit %d \"%s\" \"%s\" \"%s\"]", search_num, Address, SortColumn, SortOrder);

}
int df_GetExtAlbumsByWork(df_connection *conn, char* Work, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtAlbumsByWork %d \"%s\" \"%s\" \"%s\"]", search_num, Work, SortColumn, SortOrder);

}
int df_GetExtAlbumsInfo(df_connection *conn, char* Address, void (*callback)(int, df_extalbuminforow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtAlbumsInfo %d \"%s\"]", search_num, Address);

}
int df_GetExtAlbumsSearchPeople(df_connection *conn, char* SearchString, int SearchType, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtAlbumsSearchPeople %d \"%s\" %d \"%s\" \"%s\"]", search_num, SearchString, SearchType, SortColumn, SortOrder);

}
int df_GetExtContributorDetails(df_connection *conn, char* Address, int Type, void (*callback)(int, df_extcontributorrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtContributorDetails %d \"%s\" %d]", search_num, Address, Type);

}
int df_GetExtContributors(df_connection *conn, int Type, void (*callback)(int, df_extcontributorrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtContributors %d %d]", search_num, Type);

}
int df_GetExtContributorsForAlbum(df_connection *conn, char* Address, int Type, void (*callback)(int, df_extcontributorrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtContributorsForAlbum %d \"%s\" %d]", search_num, Address, Type);

}
int df_GetExtContributorsForDevice(df_connection *conn, char* Address, int Type, void (*callback)(int, df_extcontributorrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtContributorsForDevice %d \"%s\" %d]", search_num, Address, Type);

}
int df_GetExtContributorsForServer(df_connection *conn, int Type, void (*callback)(int, df_extcontributorrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtContributorsForServer %d %d]", search_num, Type);

}
int df_GetExtContributorsForShare(df_connection *conn, char* Address, int Type, void (*callback)(int, df_extcontributorrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtContributorsForShare %d \"%s\" %d]", search_num, Address, Type);

}
int df_GetExtTrackContributors(df_connection *conn, char* Address, int Type, void (*callback)(int, df_exttrackcontribrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtTrackContributors %d \"%s\" %d]", search_num, Address, Type);

}
int df_GetExtTracksByContributor(df_connection *conn, char* Address, int Type, char* Album, void (*callback)(int, df_trackrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtTracksByContributor %d \"%s\" %d \"%s\"]", search_num, Address, Type, Album);

}
int df_GetExtTracksByContributorForDevice(df_connection *conn, char* Address, char* DeviceAddress, int Type, char* Album, void (*callback)(int, df_trackrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtTracksByContributorForDevice %d \"%s\" \"%s\" %d \"%s\"]", search_num, Address, DeviceAddress, Type, Album);

}
int df_GetExtTracksByContributorForServer(df_connection *conn, char* Address, int Type, char* Album, void (*callback)(int, df_trackrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtTracksByContributorForServer %d \"%s\" %d \"%s\"]", search_num, Address, Type, Album);

}
int df_GetExtTracksByContributorForShare(df_connection *conn, char* Address, char* ShareAddress, int Type, char* Album, void (*callback)(int, df_trackrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtTracksByContributorForShare %d \"%s\" \"%s\" %d \"%s\"]", search_num, Address, ShareAddress, Type, Album);

}
int df_GetExtTracksByWork(df_connection *conn, char* Work, void (*callback)(int, df_trackrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtTracksByWork %d \"%s\"]", search_num, Work);

}
int df_GetExtTracksInfo(df_connection *conn, char* Address, void (*callback)(int, df_exttrackinforow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtTracksInfo %d \"%s\"]", search_num, Address);

}
int df_GetExtWorks(df_connection *conn, void (*callback)(int, df_extworksrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExtWorks %d]", search_num);

}
int df_GetExternalStorages(df_connection *conn, int AvailableOnly, void (*callback)(int, df_externalstoragerow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetExternalStorages %d %d]", search_num, AvailableOnly);

}
int df_GetGenres(df_connection *conn, int Allocated, char* SortColumn, char* SortOrder, void (*callback)(int, df_genrerow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetGenres %d %d \"%s\" \"%s\"]", search_num, Allocated, SortColumn, SortOrder);

}
int df_GetGenresSubGenres(df_connection *conn, int Allocated, char* SortColumn, char* SortOrder, void (*callback)(int, df_genressubgenresrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetGenresSubGenres %d %d \"%s\" \"%s\"]", search_num, Allocated, SortColumn, SortOrder);

}
int df_GetLatestPlayedAlbums(df_connection *conn, int TopCount, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetLatestPlayedAlbums %d %d \"%s\" \"%s\"]", search_num, TopCount, SortColumn, SortOrder);

}
int df_GetLinkedRoomDetail(df_connection *conn, char* RoomKey, void (*callback)(int, df_linkedroomdetailrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetLinkedRoomDetail %d \"%s\"]", search_num, RoomKey);

}
int df_GetLinkedRooms(df_connection *conn, int LocalOnly, void (*callback)(int, df_roomrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetLinkedRooms %d %d]", search_num, LocalOnly);

}
int df_GetNetworkActiveAdapters(df_connection *conn, int IncludeWireless, void (*callback)(int, df_networkadaptorrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetNetworkActiveAdapters %d %d]", search_num, IncludeWireless);

}
int df_GetNewestAlbums(df_connection *conn, int TopCount, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetNewestAlbums %d %d \"%s\" \"%s\"]", search_num, TopCount, SortColumn, SortOrder);

}
int df_GetNonLinkedRooms(df_connection *conn, int LocalOnly, void (*callback)(int, df_roomrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetNonLinkedRooms %d %d]", search_num, LocalOnly);

}
int df_GetOutputChannels(df_connection *conn, int RoomID, char* HostName, void (*callback)(int, df_outputchannelrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetOutputChannels %d %d \"%s\"]", search_num, RoomID, HostName);

}
int df_GetOutputDevices(df_connection *conn, int RoomID, char* HostName, int AsioOutputs, void (*callback)(int, df_outputdevicerow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetOutputDevices %d %d \"%s\" %d]", search_num, RoomID, HostName, AsioOutputs);

}
int df_GetPlayListsByLetter(df_connection *conn, char* SearchLetter, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetPlayListsByLetter %d \"%s\" \"%s\" \"%s\"]", search_num, SearchLetter, SortColumn, SortOrder);

}
int df_GetPlayerInstances(df_connection *conn, int RoomID, void (*callback)(int, df_playerinstancerow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetPlayerInstances %d %d]", search_num, RoomID);

}
int df_GetPlaylistsForGenre(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetPlaylistsForGenre %d \"%s\" \"%s\" \"%s\"]", search_num, Address, SortColumn, SortOrder);

}
int df_GetPlaylistsForSubGenre(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetPlaylistsForSubGenre %d \"%s\" \"%s\" \"%s\"]", search_num, Address, SortColumn, SortOrder);

}
int df_GetPlaylistsForSubGenreForDevice(df_connection *conn, char* Address, char* DeviceAddress, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetPlaylistsForSubGenreForDevice %d \"%s\" \"%s\" \"%s\" \"%s\"]", search_num, Address, DeviceAddress, SortColumn, SortOrder);

}
int df_GetPlaylistsForSubGenreForServer(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetPlaylistsForSubGenreForServer %d \"%s\" \"%s\" \"%s\"]", search_num, Address, SortColumn, SortOrder);

}
int df_GetPlaylistsForSubGenreForShare(df_connection *conn, char* Address, char* ShareAddress, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetPlaylistsForSubGenreForShare %d \"%s\" \"%s\" \"%s\" \"%s\"]", search_num, Address, ShareAddress, SortColumn, SortOrder);

}
int df_GetRipEncSettings(df_connection *conn, int RoomID, void (*callback)(int, df_settingsrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetRipEncSettings %d %d]", search_num, RoomID);

}
int df_GetRipEncSettingsEx(df_connection *conn, int RoomID, void (*callback)(int, df_settingsexrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetRipEncSettingsEx %d %d]", search_num, RoomID);

}
int df_GetRippingAlerts(df_connection *conn, void (*callback)(int, df_rippingalertrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetRippingAlerts %d]", search_num);

}
int df_GetRippingStatus(df_connection *conn, int RoomID, void (*callback)(int, df_type1row*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetRippingStatus %d %d]", search_num, RoomID);

}
int df_GetRooms(df_connection *conn, int LocalOnly, void (*callback)(int, df_roomrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetRooms %d %d]", search_num, LocalOnly);

}
int df_GetRoomsWithPlayBack(df_connection *conn, int LocalOnly, void (*callback)(int, df_roomrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetRoomsWithPlayBack %d %d]", search_num, LocalOnly);

}
int df_GetRoomsWithRipping(df_connection *conn, int LocalOnly, void (*callback)(int, df_roomrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetRoomsWithRipping %d %d]", search_num, LocalOnly);

}
int df_GetSettings(df_connection *conn, int RoomID, void (*callback)(int, df_settingsrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetSettings %d %d]", search_num, RoomID);

}
int df_GetSettingsEx(df_connection *conn, int RoomID, void (*callback)(int, df_settingsexrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetSettingsEx %d %d]", search_num, RoomID);

}
int df_GetStatusMessages(df_connection *conn, df_date MessageDate, char* Category, int Tag, void (*callback)(int, df_statusmessagerow*, void*), void *context) {
	int search_num;
	struct call_holder *c;
	char *MessageDate_string;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	MessageDate_string = dfdate_to_string(MessageDate);
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetStatusMessages %d \"%s\" \"%s\" %d]", search_num, MessageDate_string, Category, Tag);
	free(MessageDate_string);

}
int df_GetStoreDetail(df_connection *conn, char* MusicStoreKey, void (*callback)(int, df_storedetailrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetStoreDetail %d \"%s\"]", search_num, MusicStoreKey);

}
int df_GetStores(df_connection *conn, int IncludeReadOnly, int MusicStoreType, void (*callback)(int, df_storerow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetStores %d %d %d]", search_num, IncludeReadOnly, MusicStoreType);

}
int df_GetSubGenresForDevice(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_subgenrerow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetSubGenresForDevice %d \"%s\" \"%s\" \"%s\"]", search_num, Address, SortColumn, SortOrder);

}
int df_GetSubGenresForGenre(df_connection *conn, char* Address, int Allocated, char* SortColumn, char* SortOrder, void (*callback)(int, df_subgenrerow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetSubGenresForGenre %d \"%s\" %d \"%s\" \"%s\"]", search_num, Address, Allocated, SortColumn, SortOrder);

}
int df_GetSubGenresForServer(df_connection *conn, int Allocated, int UserDefined, char* SortColumn, char* SortOrder, void (*callback)(int, df_subgenrerow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetSubGenresForServer %d %d %d \"%s\" \"%s\"]", search_num, Allocated, UserDefined, SortColumn, SortOrder);

}
int df_GetSubGenresForShare(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_subgenrerow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetSubGenresForShare %d \"%s\" \"%s\" \"%s\"]", search_num, Address, SortColumn, SortOrder);

}
int df_GetSystemDrives(df_connection *conn, void (*callback)(int, df_driverow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetSystemDrives %d]", search_num);

}
int df_GetTopPlayedAlbums(df_connection *conn, int TopCount, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetTopPlayedAlbums %d %d \"%s\" \"%s\"]", search_num, TopCount, SortColumn, SortOrder);

}
int df_GetTrackRange(df_connection *conn, int StartRow, int RowCount, char* Filter, char* Address, int Storage, void (*callback)(int, df_trackrangerow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetTrackRange %d %d %d \"%s\" \"%s\" %d]", search_num, StartRow, RowCount, Filter, Address, Storage);

}
int df_GetTracksAll(df_connection *conn, void (*callback)(int, df_trackrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetTracksAll %d]", search_num);

}
int df_GetTracksForAlbumInUPL(df_connection *conn, char* Address, void (*callback)(int, df_trackrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetTracksForAlbumInUPL %d \"%s\"]", search_num, Address);

}
int df_GetTracksForArtist(df_connection *conn, char* Address, void (*callback)(int, df_trackrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetTracksForArtist %d \"%s\"]", search_num, Address);

}
int df_GetTracksForArtistForDevice(df_connection *conn, char* Address, char* DeviceAddress, void (*callback)(int, df_trackrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetTracksForArtistForDevice %d \"%s\" \"%s\"]", search_num, Address, DeviceAddress);

}
int df_GetTracksForArtistForServer(df_connection *conn, char* Address, void (*callback)(int, df_trackrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetTracksForArtistForServer %d \"%s\"]", search_num, Address);

}
int df_GetTracksForArtistForShare(df_connection *conn, char* Address, char* ShareAddress, void (*callback)(int, df_trackrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetTracksForArtistForShare %d \"%s\" \"%s\"]", search_num, Address, ShareAddress);

}
int df_GetTracksForDeletion(df_connection *conn, int RemoteImagePath, int ImageSize, void (*callback)(int, df_type3row*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetTracksForDeletion %d %d %d]", search_num, RemoteImagePath, ImageSize);

}
int df_GetTracksForDevice(df_connection *conn, char* Address, void (*callback)(int, df_trackrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetTracksForDevice %d \"%s\"]", search_num, Address);

}
int df_GetTracksForGenre(df_connection *conn, char* Address, void (*callback)(int, df_trackrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetTracksForGenre %d \"%s\"]", search_num, Address);

}
int df_GetTracksForNamedEntity(df_connection *conn, char* EntityName, char* EntityValue, int ExactMatch, void (*callback)(int, df_trackrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetTracksForNamedEntity %d \"%s\" \"%s\" %d]", search_num, EntityName, EntityValue, ExactMatch);

}
int df_GetTracksForPlaylist(df_connection *conn, char* Address, int ShowHidden, void (*callback)(int, df_tracksforplaylistrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetTracksForPlaylist %d \"%s\" %d]", search_num, Address, ShowHidden);

}
int df_GetTracksForServer(df_connection *conn, void (*callback)(int, df_trackrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetTracksForServer %d]", search_num);

}
int df_GetTracksForShare(df_connection *conn, char* Address, void (*callback)(int, df_trackrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetTracksForShare %d \"%s\"]", search_num, Address);

}
int df_GetTracksForSubGenre(df_connection *conn, char* Address, void (*callback)(int, df_trackrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetTracksForSubGenre %d \"%s\"]", search_num, Address);

}
int df_GetTracksForSubGenreForDevice(df_connection *conn, char* Address, char* DeviceAddress, void (*callback)(int, df_trackrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetTracksForSubGenreForDevice %d \"%s\" \"%s\"]", search_num, Address, DeviceAddress);

}
int df_GetTracksForSubGenreForServer(df_connection *conn, char* Address, void (*callback)(int, df_trackrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetTracksForSubGenreForServer %d \"%s\"]", search_num, Address);

}
int df_GetTracksForSubGenreForShare(df_connection *conn, char* Address, char* ShareAddress, void (*callback)(int, df_trackrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetTracksForSubGenreForShare %d \"%s\" \"%s\"]", search_num, Address, ShareAddress);

}
int df_GetTracksOtherInfo(df_connection *conn, char* Address, int RemoteImagePath, int ImageSize, void (*callback)(int, df_type3row*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetTracksOtherInfo %d \"%s\" %d %d]", search_num, Address, RemoteImagePath, ImageSize);

}
int df_GetTracksSearchName(df_connection *conn, char* SearchString, int SearchType, int RemoteImagePath, int ImageSize, void (*callback)(int, df_type3row*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetTracksSearchName %d \"%s\" %d %d %d]", search_num, SearchString, SearchType, RemoteImagePath, ImageSize);

}
int df_GetUpnpMediaRenderers(df_connection *conn, void (*callback)(int, df_mediarendererrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetUpnpMediaRenderers %d]", search_num);

}
int df_GetUserPlaylists(df_connection *conn, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetUserPlaylists %d \"%s\" \"%s\"]", search_num, SortColumn, SortOrder);

}
int df_GetUserPlaylistsForDevice(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetUserPlaylistsForDevice %d \"%s\" \"%s\" \"%s\"]", search_num, Address, SortColumn, SortOrder);

}
int df_GetUserPlaylistsForServer(df_connection *conn, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetUserPlaylistsForServer %d \"%s\" \"%s\"]", search_num, SortColumn, SortOrder);

}
int df_GetUserPlaylistsForShare(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetUserPlaylistsForShare %d \"%s\" \"%s\" \"%s\"]", search_num, Address, SortColumn, SortOrder);

}
int df_GetUserStatus(df_connection *conn, void (*callback)(int, df_keyvaluerow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[GetUserStatus %d]", search_num);

}
int df_MoveAlbumGetQueue(df_connection *conn, void (*callback)(int, df_movealbumgetqueuerow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[MoveAlbumGetQueue %d]", search_num);

}
int df_Status(df_connection *conn, void (*callback)(int, df_statusrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[Status %d]", search_num);

}
int df_UndoUserEdits(df_connection *conn, char* AlbumKeys, void (*callback)(int, df_bulklookuprow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[UndoUserEdits %d \"%s\"]", search_num, AlbumKeys);

}
int df_vTunerGetChildNodes(df_connection *conn, char* vTunerUrl, char* vTunerBackupUrl, void (*callback)(int, df_vtunernoderow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[vTunerGetChildNodes %d \"%s\" \"%s\"]", search_num, vTunerUrl, vTunerBackupUrl);

}
int df_vTunerGetLastPlayed(df_connection *conn, void (*callback)(int, df_vtunerplayedrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, 20, pull_rows, (void *)c, "[vTunerGetLastPlayed %d]", search_num);

}
int df_vTunerGetMostPlayed(df_connection *conn, void (*callback)(int, df_vtunerplayedrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, 20, pull_rows, (void *)c, "[vTunerGetMostPlayed %d]", search_num);

}
int df_vTunerGetNodeFromPlayedUrl(df_connection *conn, char* URLPlayed, void (*callback)(int, df_vtunernoderow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[vTunerGetNodeFromPlayedUrl %d \"%s\"]", search_num, URLPlayed);

}
int df_vTunerGetPresetChannels(df_connection *conn, void (*callback)(int, df_vtunerpresetrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[vTunerGetPresetChannels %d]", search_num);

}
int df_vTunerLookupById(df_connection *conn, char* vTunerId, int vTunerLookupType, void (*callback)(int, df_vtunernoderow*, void*), void *context) {
	int search_num;
	struct call_holder *c;

	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->context = context; c->callback = (void (*)(void))callback;
	return comm_send(conn, 0, "rowrequest", 1, -1, pull_rows, (void *)c, "[vTunerLookupById %d \"%s\" %d]", search_num, vTunerId, vTunerLookupType);

}








/*
 Core handler
 */

static void row_handler(out_request *request, out_response *response, int num, void *context) {
	 if (strcmp(request->tag, "AdvancedSearch") == 0) {
	AdvancedSearch_handler(request, response, num, context);
}
else if (strcmp(request->tag, "BulkCDLookup") == 0) {
	BulkCDLookup_handler(request, response, num, context);
}
else if (strcmp(request->tag, "CDLookupGetQueue") == 0) {
	CDLookupGetQueue_handler(request, response, num, context);
}
else if (strcmp(request->tag, "ComplexSearchGetAlbums") == 0) {
	ComplexSearchGetAlbums_handler(request, response, num, context);
}
else if (strcmp(request->tag, "ComplexSearchGetArtists") == 0) {
	ComplexSearchGetArtists_handler(request, response, num, context);
}
else if (strcmp(request->tag, "ComplexSearchGetContributors") == 0) {
	ComplexSearchGetContributors_handler(request, response, num, context);
}
else if (strcmp(request->tag, "ComplexSearchGetTracks") == 0) {
	ComplexSearchGetTracks_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAdvancedStatus") == 0) {
	GetAdvancedStatus_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlbumDetails") == 0) {
	GetAlbumDetails_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlbums") == 0) {
	GetAlbums_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlbumsForArtists") == 0) {
	GetAlbumsForArtists_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlbumsForArtistsForDevice") == 0) {
	GetAlbumsForArtistsForDevice_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlbumsForArtistsForServer") == 0) {
	GetAlbumsForArtistsForServer_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlbumsForArtistsForShare") == 0) {
	GetAlbumsForArtistsForShare_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlbumsForArtistsInGenre") == 0) {
	GetAlbumsForArtistsInGenre_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlbumsForArtistsInSubGenre") == 0) {
	GetAlbumsForArtistsInSubGenre_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlbumsForDeletion") == 0) {
	GetAlbumsForDeletion_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlbumsForDevice") == 0) {
	GetAlbumsForDevice_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlbumsForPlaylist") == 0) {
	GetAlbumsForPlaylist_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlbumsForServer") == 0) {
	GetAlbumsForServer_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlbumsForShare") == 0) {
	GetAlbumsForShare_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlbumsForStore") == 0) {
	GetAlbumsForStore_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlbumsOtherInfo") == 0) {
	GetAlbumsOtherInfo_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlbumsOtherInfoAll") == 0) {
	GetAlbumsOtherInfoAll_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlbumsOtherInfoForDevice") == 0) {
	GetAlbumsOtherInfoForDevice_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlbumsOtherInfoForServer") == 0) {
	GetAlbumsOtherInfoForServer_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlbumsOtherInfoForShare") == 0) {
	GetAlbumsOtherInfoForShare_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlbumsSearchAlbumArtist") == 0) {
	GetAlbumsSearchAlbumArtist_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlbumsWithAlbumLookupMessages") == 0) {
	GetAlbumsWithAlbumLookupMessages_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAlertDetails") == 0) {
	GetAlertDetails_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetArtistDetails") == 0) {
	GetArtistDetails_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetArtists") == 0) {
	GetArtists_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetArtistsForDevice") == 0) {
	GetArtistsForDevice_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetArtistsForServer") == 0) {
	GetArtistsForServer_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetArtistsForShare") == 0) {
	GetArtistsForShare_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetArtistsInGenre") == 0) {
	GetArtistsInGenre_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetArtistsInSubGenre") == 0) {
	GetArtistsInSubGenre_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetAvailableValues") == 0) {
	GetAvailableValues_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetBackupJobDetail") == 0) {
	GetBackupJobDetail_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetBackupJobs") == 0) {
	GetBackupJobs_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetBackupLogDetail") == 0) {
	GetBackupLogDetail_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetBackupLogs") == 0) {
	GetBackupLogs_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetCDDBGenres") == 0) {
	GetCDDBGenres_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetComponentVersions") == 0) {
	GetComponentVersions_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetCurrentPlayList") == 0) {
	GetCurrentPlayList_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetCurrentPlaylistEx") == 0) {
	GetCurrentPlaylistEx_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetDeviceDetails") == 0) {
	GetDeviceDetails_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetDevices") == 0) {
	GetDevices_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetEncodingQueue") == 0) {
	GetEncodingQueue_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetEncodingStatus") == 0) {
	GetEncodingStatus_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtAlbumCredits") == 0) {
	GetExtAlbumCredits_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtAlbumsByContributor") == 0) {
	GetExtAlbumsByContributor_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtAlbumsByContributorForDevice") == 0) {
	GetExtAlbumsByContributorForDevice_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtAlbumsByContributorForServer") == 0) {
	GetExtAlbumsByContributorForServer_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtAlbumsByContributorForShare") == 0) {
	GetExtAlbumsByContributorForShare_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtAlbumsByCredit") == 0) {
	GetExtAlbumsByCredit_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtAlbumsByWork") == 0) {
	GetExtAlbumsByWork_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtAlbumsInfo") == 0) {
	GetExtAlbumsInfo_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtAlbumsSearchPeople") == 0) {
	GetExtAlbumsSearchPeople_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtContributorDetails") == 0) {
	GetExtContributorDetails_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtContributors") == 0) {
	GetExtContributors_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtContributorsForAlbum") == 0) {
	GetExtContributorsForAlbum_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtContributorsForDevice") == 0) {
	GetExtContributorsForDevice_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtContributorsForServer") == 0) {
	GetExtContributorsForServer_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtContributorsForShare") == 0) {
	GetExtContributorsForShare_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtTrackContributors") == 0) {
	GetExtTrackContributors_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtTracksByContributor") == 0) {
	GetExtTracksByContributor_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtTracksByContributorForDevice") == 0) {
	GetExtTracksByContributorForDevice_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtTracksByContributorForServer") == 0) {
	GetExtTracksByContributorForServer_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtTracksByContributorForShare") == 0) {
	GetExtTracksByContributorForShare_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtTracksByWork") == 0) {
	GetExtTracksByWork_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtTracksInfo") == 0) {
	GetExtTracksInfo_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExtWorks") == 0) {
	GetExtWorks_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetExternalStorages") == 0) {
	GetExternalStorages_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetGenres") == 0) {
	GetGenres_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetGenresSubGenres") == 0) {
	GetGenresSubGenres_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetLatestPlayedAlbums") == 0) {
	GetLatestPlayedAlbums_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetLinkedRoomDetail") == 0) {
	GetLinkedRoomDetail_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetLinkedRooms") == 0) {
	GetLinkedRooms_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetNetworkActiveAdapters") == 0) {
	GetNetworkActiveAdapters_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetNewestAlbums") == 0) {
	GetNewestAlbums_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetNonLinkedRooms") == 0) {
	GetNonLinkedRooms_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetOutputChannels") == 0) {
	GetOutputChannels_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetOutputDevices") == 0) {
	GetOutputDevices_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetPlayListsByLetter") == 0) {
	GetPlayListsByLetter_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetPlayerInstances") == 0) {
	GetPlayerInstances_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetPlaylistsForGenre") == 0) {
	GetPlaylistsForGenre_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetPlaylistsForSubGenre") == 0) {
	GetPlaylistsForSubGenre_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetPlaylistsForSubGenreForDevice") == 0) {
	GetPlaylistsForSubGenreForDevice_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetPlaylistsForSubGenreForServer") == 0) {
	GetPlaylistsForSubGenreForServer_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetPlaylistsForSubGenreForShare") == 0) {
	GetPlaylistsForSubGenreForShare_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetRipEncSettings") == 0) {
	GetRipEncSettings_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetRipEncSettingsEx") == 0) {
	GetRipEncSettingsEx_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetRippingAlerts") == 0) {
	GetRippingAlerts_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetRippingStatus") == 0) {
	GetRippingStatus_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetRooms") == 0) {
	GetRooms_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetRoomsWithPlayBack") == 0) {
	GetRoomsWithPlayBack_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetRoomsWithRipping") == 0) {
	GetRoomsWithRipping_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetSettings") == 0) {
	GetSettings_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetSettingsEx") == 0) {
	GetSettingsEx_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetStatusMessages") == 0) {
	GetStatusMessages_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetStoreDetail") == 0) {
	GetStoreDetail_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetStores") == 0) {
	GetStores_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetSubGenresForDevice") == 0) {
	GetSubGenresForDevice_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetSubGenresForGenre") == 0) {
	GetSubGenresForGenre_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetSubGenresForServer") == 0) {
	GetSubGenresForServer_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetSubGenresForShare") == 0) {
	GetSubGenresForShare_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetSystemDrives") == 0) {
	GetSystemDrives_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetTopPlayedAlbums") == 0) {
	GetTopPlayedAlbums_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetTrackRange") == 0) {
	GetTrackRange_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetTracksAll") == 0) {
	GetTracksAll_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetTracksForAlbumInUPL") == 0) {
	GetTracksForAlbumInUPL_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetTracksForArtist") == 0) {
	GetTracksForArtist_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetTracksForArtistForDevice") == 0) {
	GetTracksForArtistForDevice_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetTracksForArtistForServer") == 0) {
	GetTracksForArtistForServer_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetTracksForArtistForShare") == 0) {
	GetTracksForArtistForShare_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetTracksForDeletion") == 0) {
	GetTracksForDeletion_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetTracksForDevice") == 0) {
	GetTracksForDevice_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetTracksForGenre") == 0) {
	GetTracksForGenre_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetTracksForNamedEntity") == 0) {
	GetTracksForNamedEntity_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetTracksForPlaylist") == 0) {
	GetTracksForPlaylist_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetTracksForServer") == 0) {
	GetTracksForServer_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetTracksForShare") == 0) {
	GetTracksForShare_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetTracksForSubGenre") == 0) {
	GetTracksForSubGenre_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetTracksForSubGenreForDevice") == 0) {
	GetTracksForSubGenreForDevice_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetTracksForSubGenreForServer") == 0) {
	GetTracksForSubGenreForServer_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetTracksForSubGenreForShare") == 0) {
	GetTracksForSubGenreForShare_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetTracksOtherInfo") == 0) {
	GetTracksOtherInfo_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetTracksSearchName") == 0) {
	GetTracksSearchName_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetUpnpMediaRenderers") == 0) {
	GetUpnpMediaRenderers_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetUserPlaylists") == 0) {
	GetUserPlaylists_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetUserPlaylistsForDevice") == 0) {
	GetUserPlaylistsForDevice_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetUserPlaylistsForServer") == 0) {
	GetUserPlaylistsForServer_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetUserPlaylistsForShare") == 0) {
	GetUserPlaylistsForShare_handler(request, response, num, context);
}
else if (strcmp(request->tag, "GetUserStatus") == 0) {
	GetUserStatus_handler(request, response, num, context);
}
else if (strcmp(request->tag, "MoveAlbumGetQueue") == 0) {
	MoveAlbumGetQueue_handler(request, response, num, context);
}
else if (strcmp(request->tag, "Status") == 0) {
	Status_handler(request, response, num, context);
}
else if (strcmp(request->tag, "UndoUserEdits") == 0) {
	UndoUserEdits_handler(request, response, num, context);
}
else if (strcmp(request->tag, "vTunerGetChildNodes") == 0) {
	vTunerGetChildNodes_handler(request, response, num, context);
}
else if (strcmp(request->tag, "vTunerGetLastPlayed") == 0) {
	vTunerGetLastPlayed_handler(request, response, num, context);
}
else if (strcmp(request->tag, "vTunerGetMostPlayed") == 0) {
	vTunerGetMostPlayed_handler(request, response, num, context);
}
else if (strcmp(request->tag, "vTunerGetNodeFromPlayedUrl") == 0) {
	vTunerGetNodeFromPlayedUrl_handler(request, response, num, context);
}
else if (strcmp(request->tag, "vTunerGetPresetChannels") == 0) {
	vTunerGetPresetChannels_handler(request, response, num, context);
}
else if (strcmp(request->tag, "vTunerLookupById") == 0) {
	vTunerLookupById_handler(request, response, num, context);
}

}










/*
 Front facing functions
 */

// Generated row handlers
static void AdvancedSearch_handler(out_request *request, out_response *response, int num, void* context) {
	df_type3row *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_type3row));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		sscanf(rx->subexps[16].value,"%d",&(fresh->AlbumKey));
		fresh->AlbumName = formatting_process(rx->subexps[17].value);
		sscanf(rx->subexps[18].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[19].value);
		fresh->SubGenre = formatting_process(rx->subexps[20].value);
		fresh->CoverURL = formatting_process(rx->subexps[21].value);
		sscanf(rx->subexps[22].value,"%d",&(fresh->BitRate));
		sscanf(rx->subexps[23].value,"%d",&(fresh->CoverAvailable));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_type3row*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void BulkCDLookup_handler(out_request *request, out_response *response, int num, void* context) {
	df_bulklookuprow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_bulklookuprow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		sscanf(rx->subexps[4].value,"%d",&(fresh->Success));
		fresh->Message = formatting_process(rx->subexps[5].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_bulklookuprow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void CDLookupGetQueue_handler(out_request *request, out_response *response, int num, void* context) {
	df_type4row *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_type4row));		sscanf(rx->subexps[3].value,"%d",&(fresh->QueueKey));
		fresh->Status = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->Retries));
		fresh->LastError = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->CreatedDate.year), &(fresh->CreatedDate.month), &(fresh->CreatedDate.day));
		sscanf(rx->subexps[8].value,"%u:%u:%u", &(fresh->CreatedTime.hours), &(fresh->CreatedTime.minutes), &(fresh->CreatedTime.seconds));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->ModifiedDate.year), &(fresh->ModifiedDate.month), &(fresh->ModifiedDate.day));
		sscanf(rx->subexps[10].value,"%u:%u:%u", &(fresh->ModifiedTime.hours), &(fresh->ModifiedTime.minutes), &(fresh->ModifiedTime.seconds));
		sscanf(rx->subexps[11].value,"%u-%u-%u", &(fresh->LastRetryDate.year), &(fresh->LastRetryDate.month), &(fresh->LastRetryDate.day));
		sscanf(rx->subexps[12].value,"%u:%u:%u", &(fresh->LastRetryTime.hours), &(fresh->LastRetryTime.minutes), &(fresh->LastRetryTime.seconds));
		sscanf(rx->subexps[13].value,"%d",&(fresh->AlbumKey));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_type4row*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void ComplexSearchGetAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void ComplexSearchGetArtists_handler(out_request *request, out_response *response, int num, void* context) {
	df_artistrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_artistrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->ArtistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_artistrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void ComplexSearchGetContributors_handler(out_request *request, out_response *response, int num, void* context) {
	df_extcontributorrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_extcontributorrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->ContributorKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ContributorType));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_extcontributorrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void ComplexSearchGetTracks_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrow *base = 0, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAdvancedStatus_handler(out_request *request, out_response *response, int num, void* context) {
	df_keyvaluerow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_keyvaluerow));		fresh->Name = formatting_process(rx->subexps[3].value);
		fresh->Value = formatting_process(rx->subexps[4].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_keyvaluerow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlbumDetails_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumdetailrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumdetailrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->Genre = formatting_process(rx->subexps[13].value);
		sscanf(rx->subexps[14].value,"%d",&(fresh->TrackCount));
		fresh->CoverImage = formatting_process(rx->subexps[15].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumdetailrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlbumsForArtists_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlbumsForArtistsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlbumsForArtistsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlbumsForArtistsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlbumsForArtistsInGenre_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlbumsForArtistsInSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlbumsForDeletion_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlbumsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlbumsForPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlbumsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlbumsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlbumsForStore_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlbumsOtherInfo_handler(out_request *request, out_response *response, int num, void* context) {
	df_type2row *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_type2row));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->GenreKey));
		fresh->Genre = formatting_process(rx->subexps[14].value);
		sscanf(rx->subexps[15].value,"%d",&(fresh->SubGenreKey));
		fresh->SubGenre = formatting_process(rx->subexps[16].value);
		sscanf(rx->subexps[17].value,"%d",&(fresh->TrackCount));
		sscanf(rx->subexps[18].value,"%d",&(fresh->LowQuality));
		sscanf(rx->subexps[19].value,"%d",&(fresh->StorageKey));
		fresh->StorageName = formatting_process(rx->subexps[20].value);
		sscanf(rx->subexps[21].value,"%d",&(fresh->ProviderUsed));
		fresh->CoverURL = formatting_process(rx->subexps[22].value);
		sscanf(rx->subexps[23].value,"%d",&(fresh->CoverAvailable));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_type2row*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlbumsOtherInfoAll_handler(out_request *request, out_response *response, int num, void* context) {
	df_type2row *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_type2row));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->GenreKey));
		fresh->Genre = formatting_process(rx->subexps[14].value);
		sscanf(rx->subexps[15].value,"%d",&(fresh->SubGenreKey));
		fresh->SubGenre = formatting_process(rx->subexps[16].value);
		sscanf(rx->subexps[17].value,"%d",&(fresh->TrackCount));
		sscanf(rx->subexps[18].value,"%d",&(fresh->LowQuality));
		sscanf(rx->subexps[19].value,"%d",&(fresh->StorageKey));
		fresh->StorageName = formatting_process(rx->subexps[20].value);
		sscanf(rx->subexps[21].value,"%d",&(fresh->ProviderUsed));
		fresh->CoverURL = formatting_process(rx->subexps[22].value);
		sscanf(rx->subexps[23].value,"%d",&(fresh->CoverAvailable));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_type2row*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlbumsOtherInfoForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	df_type2row *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_type2row));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->GenreKey));
		fresh->Genre = formatting_process(rx->subexps[14].value);
		sscanf(rx->subexps[15].value,"%d",&(fresh->SubGenreKey));
		fresh->SubGenre = formatting_process(rx->subexps[16].value);
		sscanf(rx->subexps[17].value,"%d",&(fresh->TrackCount));
		sscanf(rx->subexps[18].value,"%d",&(fresh->LowQuality));
		sscanf(rx->subexps[19].value,"%d",&(fresh->StorageKey));
		fresh->StorageName = formatting_process(rx->subexps[20].value);
		sscanf(rx->subexps[21].value,"%d",&(fresh->ProviderUsed));
		fresh->CoverURL = formatting_process(rx->subexps[22].value);
		sscanf(rx->subexps[23].value,"%d",&(fresh->CoverAvailable));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_type2row*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlbumsOtherInfoForServer_handler(out_request *request, out_response *response, int num, void* context) {
	df_type2row *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_type2row));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->GenreKey));
		fresh->Genre = formatting_process(rx->subexps[14].value);
		sscanf(rx->subexps[15].value,"%d",&(fresh->SubGenreKey));
		fresh->SubGenre = formatting_process(rx->subexps[16].value);
		sscanf(rx->subexps[17].value,"%d",&(fresh->TrackCount));
		sscanf(rx->subexps[18].value,"%d",&(fresh->LowQuality));
		sscanf(rx->subexps[19].value,"%d",&(fresh->StorageKey));
		fresh->StorageName = formatting_process(rx->subexps[20].value);
		sscanf(rx->subexps[21].value,"%d",&(fresh->ProviderUsed));
		fresh->CoverURL = formatting_process(rx->subexps[22].value);
		sscanf(rx->subexps[23].value,"%d",&(fresh->CoverAvailable));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_type2row*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlbumsOtherInfoForShare_handler(out_request *request, out_response *response, int num, void* context) {
	df_type2row *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_type2row));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->GenreKey));
		fresh->Genre = formatting_process(rx->subexps[14].value);
		sscanf(rx->subexps[15].value,"%d",&(fresh->SubGenreKey));
		fresh->SubGenre = formatting_process(rx->subexps[16].value);
		sscanf(rx->subexps[17].value,"%d",&(fresh->TrackCount));
		sscanf(rx->subexps[18].value,"%d",&(fresh->LowQuality));
		sscanf(rx->subexps[19].value,"%d",&(fresh->StorageKey));
		fresh->StorageName = formatting_process(rx->subexps[20].value);
		sscanf(rx->subexps[21].value,"%d",&(fresh->ProviderUsed));
		fresh->CoverURL = formatting_process(rx->subexps[22].value);
		sscanf(rx->subexps[23].value,"%d",&(fresh->CoverAvailable));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_type2row*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlbumsSearchAlbumArtist_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlbumsWithAlbumLookupMessages_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAlertDetails_handler(out_request *request, out_response *response, int num, void* context) {
	df_alertdetailrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_alertdetailrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->AlertKey));
		fresh->Severity = formatting_process(rx->subexps[4].value);
		fresh->Category = formatting_process(rx->subexps[5].value);
		fresh->Module = formatting_process(rx->subexps[6].value);
		fresh->Message = formatting_process(rx->subexps[7].value);
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->Modified.year), &(fresh->Modified.month), &(fresh->Modified.day));
		sscanf(rx->subexps[10].value,"%u-%u-%u", &(fresh->Sent.year), &(fresh->Sent.month), &(fresh->Sent.day));
		fresh->UserMessage = formatting_process(rx->subexps[11].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_alertdetailrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetArtistDetails_handler(out_request *request, out_response *response, int num, void* context) {
	df_artistrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_artistrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->ArtistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_artistrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetArtists_handler(out_request *request, out_response *response, int num, void* context) {
	df_artistrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_artistrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->ArtistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_artistrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetArtistsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	df_artistrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_artistrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->ArtistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_artistrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetArtistsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	df_artistrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_artistrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->ArtistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_artistrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetArtistsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	df_artistrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_artistrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->ArtistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_artistrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetArtistsInGenre_handler(out_request *request, out_response *response, int num, void* context) {
	df_artistrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_artistrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->ArtistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_artistrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetArtistsInSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	df_artistrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_artistrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->ArtistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_artistrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetAvailableValues_handler(out_request *request, out_response *response, int num, void* context) {
	df_keyvaluerow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_keyvaluerow));		fresh->Name = formatting_process(rx->subexps[3].value);
		fresh->Value = formatting_process(rx->subexps[4].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_keyvaluerow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetBackupJobDetail_handler(out_request *request, out_response *response, int num, void* context) {
	df_backupjobrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_backupjobrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->BackupJobKey));
		sscanf(rx->subexps[4].value,"%d",&(fresh->SourceDriveKey));
		sscanf(rx->subexps[5].value,"%d",&(fresh->DestinationDriveKey));
		fresh->Name = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->BackupType));
		sscanf(rx->subexps[8].value,"%d",&(fresh->BackupPeriod));
		sscanf(rx->subexps[9].value,"%d",&(fresh->PeriodValue));
		sscanf(rx->subexps[10].value,"%u-%u-%u", &(fresh->RunDate.year), &(fresh->RunDate.month), &(fresh->RunDate.day));
		sscanf(rx->subexps[11].value,"%u:%u:%u", &(fresh->RunTime.hours), &(fresh->RunTime.minutes), &(fresh->RunTime.seconds));
		sscanf(rx->subexps[12].value,"%u-%u-%u", &(fresh->NextRunDate.year), &(fresh->NextRunDate.month), &(fresh->NextRunDate.day));
		sscanf(rx->subexps[13].value,"%u:%u:%u", &(fresh->NextRunTime.hours), &(fresh->NextRunTime.minutes), &(fresh->NextRunTime.seconds));
		sscanf(rx->subexps[14].value,"%u-%u-%u", &(fresh->LastRunDate.year), &(fresh->LastRunDate.month), &(fresh->LastRunDate.day));
		sscanf(rx->subexps[15].value,"%u:%u:%u", &(fresh->LastRunTime.hours), &(fresh->LastRunTime.minutes), &(fresh->LastRunTime.seconds));
		sscanf(rx->subexps[16].value,"%d",&(fresh->JobStatus));
		sscanf(rx->subexps[17].value,"%d",&(fresh->LastResult));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_backupjobrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetBackupJobs_handler(out_request *request, out_response *response, int num, void* context) {
	df_backupjobrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_backupjobrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->BackupJobKey));
		sscanf(rx->subexps[4].value,"%d",&(fresh->SourceDriveKey));
		sscanf(rx->subexps[5].value,"%d",&(fresh->DestinationDriveKey));
		fresh->Name = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->BackupType));
		sscanf(rx->subexps[8].value,"%d",&(fresh->BackupPeriod));
		sscanf(rx->subexps[9].value,"%d",&(fresh->PeriodValue));
		sscanf(rx->subexps[10].value,"%u-%u-%u", &(fresh->RunDate.year), &(fresh->RunDate.month), &(fresh->RunDate.day));
		sscanf(rx->subexps[11].value,"%u:%u:%u", &(fresh->RunTime.hours), &(fresh->RunTime.minutes), &(fresh->RunTime.seconds));
		sscanf(rx->subexps[12].value,"%u-%u-%u", &(fresh->NextRunDate.year), &(fresh->NextRunDate.month), &(fresh->NextRunDate.day));
		sscanf(rx->subexps[13].value,"%u:%u:%u", &(fresh->NextRunTime.hours), &(fresh->NextRunTime.minutes), &(fresh->NextRunTime.seconds));
		sscanf(rx->subexps[14].value,"%u-%u-%u", &(fresh->LastRunDate.year), &(fresh->LastRunDate.month), &(fresh->LastRunDate.day));
		sscanf(rx->subexps[15].value,"%u:%u:%u", &(fresh->LastRunTime.hours), &(fresh->LastRunTime.minutes), &(fresh->LastRunTime.seconds));
		sscanf(rx->subexps[16].value,"%d",&(fresh->JobStatus));
		sscanf(rx->subexps[17].value,"%d",&(fresh->LastResult));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_backupjobrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetBackupLogDetail_handler(out_request *request, out_response *response, int num, void* context) {
	df_backuplogdetailrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_backuplogdetailrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->BackupLogKey));
		sscanf(rx->subexps[4].value,"%d",&(fresh->BackupJobKey));
		sscanf(rx->subexps[5].value,"%d",&(fresh->ExecutionType));
		fresh->Name = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->BackupType));
		fresh->SourcePath = formatting_process(rx->subexps[8].value);
		fresh->DestinationPath = formatting_process(rx->subexps[9].value);
		sscanf(rx->subexps[10].value,"%u-%u-%u", &(fresh->StartDate.year), &(fresh->StartDate.month), &(fresh->StartDate.day));
		sscanf(rx->subexps[11].value,"%u:%u:%u", &(fresh->StartTime.hours), &(fresh->StartTime.minutes), &(fresh->StartTime.seconds));
		sscanf(rx->subexps[12].value,"%u-%u-%u", &(fresh->FinishDate.year), &(fresh->FinishDate.month), &(fresh->FinishDate.day));
		sscanf(rx->subexps[13].value,"%u:%u:%u", &(fresh->FinishTime.hours), &(fresh->FinishTime.minutes), &(fresh->FinishTime.seconds));
		sscanf(rx->subexps[14].value,"%d",&(fresh->Result));
		sscanf(rx->subexps[15].value,"%d",&(fresh->TotalFolders));
		sscanf(rx->subexps[16].value,"%d",&(fresh->TotalFiles));
		sscanf(rx->subexps[17].value,"%d",&(fresh->TotalKiloBytes));
		sscanf(rx->subexps[18].value,"%d",&(fresh->TotalErrors));
		fresh->ErrorDetail = formatting_process(rx->subexps[19].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_backuplogdetailrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetBackupLogs_handler(out_request *request, out_response *response, int num, void* context) {
	df_backuplogrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_backuplogrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->BackupLogKey));
		sscanf(rx->subexps[4].value,"%d",&(fresh->BackupJobKey));
		sscanf(rx->subexps[5].value,"%d",&(fresh->ExecutionType));
		fresh->Name = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->BackupType));
		fresh->SourcePath = formatting_process(rx->subexps[8].value);
		fresh->DestinationPath = formatting_process(rx->subexps[9].value);
		sscanf(rx->subexps[10].value,"%u-%u-%u", &(fresh->StartDate.year), &(fresh->StartDate.month), &(fresh->StartDate.day));
		sscanf(rx->subexps[11].value,"%u:%u:%u", &(fresh->StartTime.hours), &(fresh->StartTime.minutes), &(fresh->StartTime.seconds));
		sscanf(rx->subexps[12].value,"%u-%u-%u", &(fresh->FinishDate.year), &(fresh->FinishDate.month), &(fresh->FinishDate.day));
		sscanf(rx->subexps[13].value,"%u:%u:%u", &(fresh->FinishTime.hours), &(fresh->FinishTime.minutes), &(fresh->FinishTime.seconds));
		sscanf(rx->subexps[14].value,"%d",&(fresh->Result));
		sscanf(rx->subexps[15].value,"%d",&(fresh->TotalFolders));
		sscanf(rx->subexps[16].value,"%d",&(fresh->TotalFiles));
		sscanf(rx->subexps[17].value,"%d",&(fresh->TotalKiloBytes));
		sscanf(rx->subexps[18].value,"%d",&(fresh->TotalErrors));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_backuplogrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetCDDBGenres_handler(out_request *request, out_response *response, int num, void* context) {
	df_cddbgenrerow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_cddbgenrerow));		sscanf(rx->subexps[3].value,"%d",&(fresh->CDDBGenreKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->SubGenreKey));
		fresh->SubGenreName = formatting_process(rx->subexps[6].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_cddbgenrerow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetComponentVersions_handler(out_request *request, out_response *response, int num, void* context) {
	df_keyvaluerow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_keyvaluerow));		fresh->Name = formatting_process(rx->subexps[3].value);
		fresh->Value = formatting_process(rx->subexps[4].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_keyvaluerow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetCurrentPlayList_handler(out_request *request, out_response *response, int num, void* context) {
	df_currentplaylistrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_currentplaylistrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		sscanf(rx->subexps[16].value,"%d",&(fresh->Source));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_currentplaylistrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetCurrentPlaylistEx_handler(out_request *request, out_response *response, int num, void* context) {
	df_type0row *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_type0row));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		sscanf(rx->subexps[16].value,"%d",&(fresh->AlbumKey));
		fresh->AlbumName = formatting_process(rx->subexps[17].value);
		sscanf(rx->subexps[18].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[19].value);
		fresh->SubGenre = formatting_process(rx->subexps[20].value);
		fresh->CoverURL = formatting_process(rx->subexps[21].value);
		sscanf(rx->subexps[22].value,"%d",&(fresh->BitRate));
		sscanf(rx->subexps[23].value,"%d",&(fresh->Source));
		sscanf(rx->subexps[24].value,"%d",&(fresh->CoverAvailable));
		sscanf(rx->subexps[25].value,"%d",&(fresh->Hidden));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_type0row*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetDeviceDetails_handler(out_request *request, out_response *response, int num, void* context) {
	df_devicerow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_devicerow));		sscanf(rx->subexps[3].value,"%d",&(fresh->DeviceKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SerialNumber = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		fresh->State = formatting_process(rx->subexps[7].value);
		fresh->LastState = formatting_process(rx->subexps[8].value);
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastConnected.year), &(fresh->LastConnected.month), &(fresh->LastConnected.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Connections));
		sscanf(rx->subexps[11].value,"%d",&(fresh->Sync));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_devicerow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetDevices_handler(out_request *request, out_response *response, int num, void* context) {
	df_devicerow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_devicerow));		sscanf(rx->subexps[3].value,"%d",&(fresh->DeviceKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SerialNumber = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		fresh->State = formatting_process(rx->subexps[7].value);
		fresh->LastState = formatting_process(rx->subexps[8].value);
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastConnected.year), &(fresh->LastConnected.month), &(fresh->LastConnected.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Connections));
		sscanf(rx->subexps[11].value,"%d",&(fresh->Sync));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_devicerow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetEncodingQueue_handler(out_request *request, out_response *response, int num, void* context) {
	df_encodingqueuerow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_encodingqueuerow));		fresh->Value = formatting_process(rx->subexps[3].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_encodingqueuerow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetEncodingStatus_handler(out_request *request, out_response *response, int num, void* context) {
	df_encodingstatusrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_encodingstatusrow));		fresh->Artist = formatting_process(rx->subexps[3].value);
		fresh->Album = formatting_process(rx->subexps[4].value);
		fresh->Track = formatting_process(rx->subexps[5].value);
		fresh->Activity = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->Max));
		sscanf(rx->subexps[8].value,"%d",&(fresh->Progress));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_encodingstatusrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtAlbumCredits_handler(out_request *request, out_response *response, int num, void* context) {
	df_extalbumcreditrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_extalbumcreditrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->CreditKey));
		sscanf(rx->subexps[4].value,"%d",&(fresh->PlaylistKey));
		fresh->Description = formatting_process(rx->subexps[5].value);
		sscanf(rx->subexps[6].value,"%d",&(fresh->ContributorKey));
		fresh->ContributorName = formatting_process(rx->subexps[7].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_extalbumcreditrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtAlbumsByContributor_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtAlbumsByContributorForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtAlbumsByContributorForServer_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtAlbumsByContributorForShare_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtAlbumsByCredit_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtAlbumsByWork_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtAlbumsInfo_handler(out_request *request, out_response *response, int num, void* context) {
	df_extalbuminforow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_extalbuminforow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		sscanf(rx->subexps[4].value,"%d",&(fresh->Discs));
		sscanf(rx->subexps[5].value,"%d",&(fresh->DiscNumber));
		fresh->CatalogID = formatting_process(rx->subexps[6].value);
		fresh->ImageURL = formatting_process(rx->subexps[7].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_extalbuminforow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtAlbumsSearchPeople_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtContributorDetails_handler(out_request *request, out_response *response, int num, void* context) {
	df_extcontributorrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_extcontributorrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->ContributorKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ContributorType));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_extcontributorrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtContributors_handler(out_request *request, out_response *response, int num, void* context) {
	df_extcontributorrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_extcontributorrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->ContributorKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ContributorType));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_extcontributorrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtContributorsForAlbum_handler(out_request *request, out_response *response, int num, void* context) {
	df_extcontributorrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_extcontributorrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->ContributorKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ContributorType));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_extcontributorrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtContributorsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	df_extcontributorrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_extcontributorrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->ContributorKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ContributorType));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_extcontributorrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtContributorsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	df_extcontributorrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_extcontributorrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->ContributorKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ContributorType));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_extcontributorrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtContributorsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	df_extcontributorrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_extcontributorrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->ContributorKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ContributorType));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_extcontributorrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtTrackContributors_handler(out_request *request, out_response *response, int num, void* context) {
	df_exttrackcontribrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_exttrackcontribrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		sscanf(rx->subexps[4].value,"%d",&(fresh->ContributorKey));
		fresh->Name = formatting_process(rx->subexps[5].value);
		sscanf(rx->subexps[6].value,"%d",&(fresh->ContributorType));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_exttrackcontribrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtTracksByContributor_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrow *base = 0, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtTracksByContributorForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrow *base = 0, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtTracksByContributorForServer_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrow *base = 0, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtTracksByContributorForShare_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrow *base = 0, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtTracksByWork_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrow *base = 0, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtTracksInfo_handler(out_request *request, out_response *response, int num, void* context) {
	df_exttrackinforow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_exttrackinforow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->CompositionDate = formatting_process(rx->subexps[4].value);
		fresh->Part = formatting_process(rx->subexps[5].value);
		fresh->PerformanceDate = formatting_process(rx->subexps[6].value);
		fresh->Work = formatting_process(rx->subexps[7].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_exttrackinforow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExtWorks_handler(out_request *request, out_response *response, int num, void* context) {
	df_extworksrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_extworksrow));		fresh->Work = formatting_process(rx->subexps[3].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_extworksrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetExternalStorages_handler(out_request *request, out_response *response, int num, void* context) {
	df_externalstoragerow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_externalstoragerow));		sscanf(rx->subexps[3].value,"%d",&(fresh->StorageKey));
		fresh->IPAddress = formatting_process(rx->subexps[4].value);
		fresh->HostName = formatting_process(rx->subexps[5].value);
		fresh->ShareName = formatting_process(rx->subexps[6].value);
		fresh->FullSharePath = formatting_process(rx->subexps[7].value);
		fresh->State = formatting_process(rx->subexps[8].value);
		fresh->LastState = formatting_process(rx->subexps[9].value);
		sscanf(rx->subexps[10].value,"%d",&(fresh->Active));
		sscanf(rx->subexps[11].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[12].value,"%u-%u-%u", &(fresh->Modified.year), &(fresh->Modified.month), &(fresh->Modified.day));
		sscanf(rx->subexps[13].value,"%u-%u-%u", &(fresh->LastScanDate.year), &(fresh->LastScanDate.month), &(fresh->LastScanDate.day));
		sscanf(rx->subexps[14].value,"%u:%u:%u", &(fresh->LastScanTime.hours), &(fresh->LastScanTime.minutes), &(fresh->LastScanTime.seconds));
		fresh->UserName = formatting_process(rx->subexps[15].value);
		fresh->Password = formatting_process(rx->subexps[16].value);
		fresh->ScanIgnore = formatting_process(rx->subexps[17].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_externalstoragerow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetGenres_handler(out_request *request, out_response *response, int num, void* context) {
	df_genrerow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_genrerow));		sscanf(rx->subexps[3].value,"%d",&(fresh->GenreKey));
		fresh->Genre = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[6].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[7].value,"%d",&(fresh->GenreOrdinal));
		sscanf(rx->subexps[8].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_genrerow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetGenresSubGenres_handler(out_request *request, out_response *response, int num, void* context) {
	df_genressubgenresrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_genressubgenresrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->SubGenreKey));
		fresh->SubGenre = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->GenreKey));
		fresh->Genre = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->GenreOrdinal));
		sscanf(rx->subexps[8].value,"%d",&(fresh->SubGenreOrdinal));
		sscanf(rx->subexps[9].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_genressubgenresrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetLatestPlayedAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetLinkedRoomDetail_handler(out_request *request, out_response *response, int num, void* context) {
	df_linkedroomdetailrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_linkedroomdetailrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->RoomKey));
		fresh->IPAddress = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->Channel));
		fresh->RoomName = formatting_process(rx->subexps[6].value);
		fresh->ShortName = formatting_process(rx->subexps[7].value);
		sscanf(rx->subexps[8].value,"%d",&(fresh->IsMultiRoom));
		sscanf(rx->subexps[9].value,"%d",&(fresh->PlaybackCapability));
		sscanf(rx->subexps[10].value,"%d",&(fresh->RippingCapability));
		sscanf(rx->subexps[11].value,"%d",&(fresh->MusicManagementCapability));
		sscanf(rx->subexps[12].value,"%d",&(fresh->RoomID));
		fresh->HostName = formatting_process(rx->subexps[13].value);
		sscanf(rx->subexps[14].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[15].value,"%u-%u-%u", &(fresh->Modified.year), &(fresh->Modified.month), &(fresh->Modified.day));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_linkedroomdetailrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetLinkedRooms_handler(out_request *request, out_response *response, int num, void* context) {
	df_roomrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_roomrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->RoomKey));
		fresh->IPAddress = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->Channel));
		fresh->Name = formatting_process(rx->subexps[6].value);
		fresh->ShortName = formatting_process(rx->subexps[7].value);
		sscanf(rx->subexps[8].value,"%d",&(fresh->IsMultiRoom));
		sscanf(rx->subexps[9].value,"%d",&(fresh->PlaybackCapability));
		sscanf(rx->subexps[10].value,"%d",&(fresh->RippingCapability));
		sscanf(rx->subexps[11].value,"%d",&(fresh->MusicManagementCapability));
		sscanf(rx->subexps[12].value,"%d",&(fresh->RoomID));
		fresh->HostName = formatting_process(rx->subexps[13].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_roomrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetNetworkActiveAdapters_handler(out_request *request, out_response *response, int num, void* context) {
	df_networkadaptorrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_networkadaptorrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->DeviceID));
		fresh->Description = formatting_process(rx->subexps[4].value);
		fresh->MacAddress = formatting_process(rx->subexps[5].value);
		sscanf(rx->subexps[6].value,"%d",&(fresh->DhcpEnabled));
		fresh->IpAddress = formatting_process(rx->subexps[7].value);
		fresh->SubnetMask = formatting_process(rx->subexps[8].value);
		fresh->DefaultGateway = formatting_process(rx->subexps[9].value);
		fresh->DnsServer = formatting_process(rx->subexps[10].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_networkadaptorrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetNewestAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetNonLinkedRooms_handler(out_request *request, out_response *response, int num, void* context) {
	df_roomrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_roomrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->RoomKey));
		fresh->IPAddress = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->Channel));
		fresh->Name = formatting_process(rx->subexps[6].value);
		fresh->ShortName = formatting_process(rx->subexps[7].value);
		sscanf(rx->subexps[8].value,"%d",&(fresh->IsMultiRoom));
		sscanf(rx->subexps[9].value,"%d",&(fresh->PlaybackCapability));
		sscanf(rx->subexps[10].value,"%d",&(fresh->RippingCapability));
		sscanf(rx->subexps[11].value,"%d",&(fresh->MusicManagementCapability));
		sscanf(rx->subexps[12].value,"%d",&(fresh->RoomID));
		fresh->HostName = formatting_process(rx->subexps[13].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_roomrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetOutputChannels_handler(out_request *request, out_response *response, int num, void* context) {
	df_outputchannelrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_outputchannelrow));		fresh->InitString = formatting_process(rx->subexps[3].value);
		sscanf(rx->subexps[4].value,"%d",&(fresh->ChannelID));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_outputchannelrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetOutputDevices_handler(out_request *request, out_response *response, int num, void* context) {
	df_outputdevicerow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_outputdevicerow));		fresh->Name = formatting_process(rx->subexps[3].value);
		sscanf(rx->subexps[4].value,"%d",&(fresh->OutputDeviceID));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_outputdevicerow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetPlayListsByLetter_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetPlayerInstances_handler(out_request *request, out_response *response, int num, void* context) {
	df_playerinstancerow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_playerinstancerow));		sscanf(rx->subexps[3].value,"%d",&(fresh->Key));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->OutputDeviceID));
		sscanf(rx->subexps[6].value,"%d",&(fresh->SourceLineID));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_playerinstancerow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetPlaylistsForGenre_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetPlaylistsForSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetPlaylistsForSubGenreForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetPlaylistsForSubGenreForServer_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetPlaylistsForSubGenreForShare_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetRipEncSettings_handler(out_request *request, out_response *response, int num, void* context) {
	df_settingsrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_settingsrow));		fresh->RegistryKey = formatting_process(rx->subexps[3].value);
		fresh->Value = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ReadOnly));
		fresh->Default = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->MaxLength));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_settingsrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetRipEncSettingsEx_handler(out_request *request, out_response *response, int num, void* context) {
	df_settingsexrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_settingsexrow));		fresh->RegistryKey = formatting_process(rx->subexps[3].value);
		fresh->Value = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ReadOnly));
		fresh->Default = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->MaxLength));
		sscanf(rx->subexps[8].value,"%d",&(fresh->ValueType));
		fresh->TabCaption = formatting_process(rx->subexps[9].value);
		fresh->Category = formatting_process(rx->subexps[10].value);
		fresh->Caption = formatting_process(rx->subexps[11].value);
		fresh->ShortTabCaption = formatting_process(rx->subexps[12].value);
		fresh->ShortCategory = formatting_process(rx->subexps[13].value);
		fresh->ShortCaption = formatting_process(rx->subexps[14].value);
		fresh->Description = formatting_process(rx->subexps[15].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_settingsexrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetRippingAlerts_handler(out_request *request, out_response *response, int num, void* context) {
	df_rippingalertrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_rippingalertrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->AlertKey));
		fresh->Severity = formatting_process(rx->subexps[4].value);
		fresh->Category = formatting_process(rx->subexps[5].value);
		sscanf(rx->subexps[6].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Time.hours), &(fresh->Time.minutes), &(fresh->Time.seconds));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_rippingalertrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetRippingStatus_handler(out_request *request, out_response *response, int num, void* context) {
	df_type1row *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_type1row));		fresh->Artist = formatting_process(rx->subexps[3].value);
		fresh->Album = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->Tracks));
		sscanf(rx->subexps[6].value,"%d",&(fresh->TracksRipped));
		sscanf(rx->subexps[7].value,"%d",&(fresh->Errors));
		sscanf(rx->subexps[8].value,"%u:%u:%u", &(fresh->TimeTaken.hours), &(fresh->TimeTaken.minutes), &(fresh->TimeTaken.seconds));
		sscanf(rx->subexps[9].value,"%u:%u:%u", &(fresh->TimeLeft.hours), &(fresh->TimeLeft.minutes), &(fresh->TimeLeft.seconds));
		fresh->Track = formatting_process(rx->subexps[10].value);
		sscanf(rx->subexps[11].value,"%d",&(fresh->TrackPercent));
		fresh->UserMessage = formatting_process(rx->subexps[12].value);
		fresh->LookupProviderUsed = formatting_process(rx->subexps[13].value);
		fresh->Destination = formatting_process(rx->subexps[14].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_type1row*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetRooms_handler(out_request *request, out_response *response, int num, void* context) {
	df_roomrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_roomrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->RoomKey));
		fresh->IPAddress = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->Channel));
		fresh->Name = formatting_process(rx->subexps[6].value);
		fresh->ShortName = formatting_process(rx->subexps[7].value);
		sscanf(rx->subexps[8].value,"%d",&(fresh->IsMultiRoom));
		sscanf(rx->subexps[9].value,"%d",&(fresh->PlaybackCapability));
		sscanf(rx->subexps[10].value,"%d",&(fresh->RippingCapability));
		sscanf(rx->subexps[11].value,"%d",&(fresh->MusicManagementCapability));
		sscanf(rx->subexps[12].value,"%d",&(fresh->RoomID));
		fresh->HostName = formatting_process(rx->subexps[13].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_roomrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetRoomsWithPlayBack_handler(out_request *request, out_response *response, int num, void* context) {
	df_roomrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_roomrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->RoomKey));
		fresh->IPAddress = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->Channel));
		fresh->Name = formatting_process(rx->subexps[6].value);
		fresh->ShortName = formatting_process(rx->subexps[7].value);
		sscanf(rx->subexps[8].value,"%d",&(fresh->IsMultiRoom));
		sscanf(rx->subexps[9].value,"%d",&(fresh->PlaybackCapability));
		sscanf(rx->subexps[10].value,"%d",&(fresh->RippingCapability));
		sscanf(rx->subexps[11].value,"%d",&(fresh->MusicManagementCapability));
		sscanf(rx->subexps[12].value,"%d",&(fresh->RoomID));
		fresh->HostName = formatting_process(rx->subexps[13].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_roomrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetRoomsWithRipping_handler(out_request *request, out_response *response, int num, void* context) {
	df_roomrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_roomrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->RoomKey));
		fresh->IPAddress = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->Channel));
		fresh->Name = formatting_process(rx->subexps[6].value);
		fresh->ShortName = formatting_process(rx->subexps[7].value);
		sscanf(rx->subexps[8].value,"%d",&(fresh->IsMultiRoom));
		sscanf(rx->subexps[9].value,"%d",&(fresh->PlaybackCapability));
		sscanf(rx->subexps[10].value,"%d",&(fresh->RippingCapability));
		sscanf(rx->subexps[11].value,"%d",&(fresh->MusicManagementCapability));
		sscanf(rx->subexps[12].value,"%d",&(fresh->RoomID));
		fresh->HostName = formatting_process(rx->subexps[13].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_roomrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetSettings_handler(out_request *request, out_response *response, int num, void* context) {
	df_settingsrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_settingsrow));		fresh->RegistryKey = formatting_process(rx->subexps[3].value);
		fresh->Value = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ReadOnly));
		fresh->Default = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->MaxLength));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_settingsrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetSettingsEx_handler(out_request *request, out_response *response, int num, void* context) {
	df_settingsexrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_settingsexrow));		fresh->RegistryKey = formatting_process(rx->subexps[3].value);
		fresh->Value = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ReadOnly));
		fresh->Default = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->MaxLength));
		sscanf(rx->subexps[8].value,"%d",&(fresh->ValueType));
		fresh->TabCaption = formatting_process(rx->subexps[9].value);
		fresh->Category = formatting_process(rx->subexps[10].value);
		fresh->Caption = formatting_process(rx->subexps[11].value);
		fresh->ShortTabCaption = formatting_process(rx->subexps[12].value);
		fresh->ShortCategory = formatting_process(rx->subexps[13].value);
		fresh->ShortCaption = formatting_process(rx->subexps[14].value);
		fresh->Description = formatting_process(rx->subexps[15].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_settingsexrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetStatusMessages_handler(out_request *request, out_response *response, int num, void* context) {
	df_statusmessagerow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_statusmessagerow));		sscanf(rx->subexps[3].value,"%d",&(fresh->MessageAddress));
		fresh->Severity = formatting_process(rx->subexps[4].value);
		fresh->Category = formatting_process(rx->subexps[5].value);
		sscanf(rx->subexps[6].value,"%u-%u-%u", &(fresh->DateCreated.year), &(fresh->DateCreated.month), &(fresh->DateCreated.day));
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->TimeCreated.hours), &(fresh->TimeCreated.minutes), &(fresh->TimeCreated.seconds));
		sscanf(rx->subexps[8].value,"%d",&(fresh->Tag));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_statusmessagerow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetStoreDetail_handler(out_request *request, out_response *response, int num, void* context) {
	df_storedetailrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_storedetailrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->MusicStoreKey));
		fresh->Path = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->Local));
		fresh->IPAddress = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->Online));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		fresh->State = formatting_process(rx->subexps[10].value);
		sscanf(rx->subexps[11].value,"%d",&(fresh->Priority));
		sscanf(rx->subexps[12].value,"%u-%u-%u", &(fresh->LastConnected.year), &(fresh->LastConnected.month), &(fresh->LastConnected.day));
		fresh->Username = formatting_process(rx->subexps[13].value);
		fresh->Password = formatting_process(rx->subexps[14].value);
		sscanf(rx->subexps[15].value,"%u-%u-%u", &(fresh->LastScanned.year), &(fresh->LastScanned.month), &(fresh->LastScanned.day));
		fresh->SpaceUsed = formatting_process(rx->subexps[16].value);
		fresh->SpaceAvailable = formatting_process(rx->subexps[17].value);
		sscanf(rx->subexps[18].value,"%d",&(fresh->NumberOfAlbums));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_storedetailrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetStores_handler(out_request *request, out_response *response, int num, void* context) {
	df_storerow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_storerow));		sscanf(rx->subexps[3].value,"%d",&(fresh->MusicStoreKey));
		fresh->Path = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->Local));
		fresh->IPAddress = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->Online));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		fresh->State = formatting_process(rx->subexps[10].value);
		sscanf(rx->subexps[11].value,"%d",&(fresh->Priority));
		sscanf(rx->subexps[12].value,"%u-%u-%u", &(fresh->LastConnected.year), &(fresh->LastConnected.month), &(fresh->LastConnected.day));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_storerow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetSubGenresForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	df_subgenrerow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_subgenrerow));		sscanf(rx->subexps[3].value,"%d",&(fresh->SubGenreKey));
		fresh->SubGenre = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[6].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[7].value,"%d",&(fresh->SubGenreOrdinal));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_subgenrerow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetSubGenresForGenre_handler(out_request *request, out_response *response, int num, void* context) {
	df_subgenrerow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_subgenrerow));		sscanf(rx->subexps[3].value,"%d",&(fresh->SubGenreKey));
		fresh->SubGenre = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[6].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[7].value,"%d",&(fresh->SubGenreOrdinal));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_subgenrerow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetSubGenresForServer_handler(out_request *request, out_response *response, int num, void* context) {
	df_subgenrerow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_subgenrerow));		sscanf(rx->subexps[3].value,"%d",&(fresh->SubGenreKey));
		fresh->SubGenre = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[6].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[7].value,"%d",&(fresh->SubGenreOrdinal));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_subgenrerow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetSubGenresForShare_handler(out_request *request, out_response *response, int num, void* context) {
	df_subgenrerow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_subgenrerow));		sscanf(rx->subexps[3].value,"%d",&(fresh->SubGenreKey));
		fresh->SubGenre = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[6].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[7].value,"%d",&(fresh->SubGenreOrdinal));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_subgenrerow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetSystemDrives_handler(out_request *request, out_response *response, int num, void* context) {
	df_driverow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_driverow));		sscanf(rx->subexps[3].value,"%d",&(fresh->DriveKey));
		fresh->DriveLetter = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->IsPrimary));
		fresh->RootPath = formatting_process(rx->subexps[6].value);
		fresh->SharePath = formatting_process(rx->subexps[7].value);
		sscanf(rx->subexps[8].value,"%d",&(fresh->Usage));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastBackup.year), &(fresh->LastBackup.month), &(fresh->LastBackup.day));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_driverow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetTopPlayedAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetTrackRange_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrangerow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrangerow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		sscanf(rx->subexps[16].value,"%d",&(fresh->AllTracksOffset));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrangerow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetTracksAll_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrow *base = 0, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetTracksForAlbumInUPL_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrow *base = 0, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetTracksForArtist_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrow *base = 0, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetTracksForArtistForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrow *base = 0, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetTracksForArtistForServer_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrow *base = 0, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetTracksForArtistForShare_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrow *base = 0, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetTracksForDeletion_handler(out_request *request, out_response *response, int num, void* context) {
	df_type3row *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_type3row));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		sscanf(rx->subexps[16].value,"%d",&(fresh->AlbumKey));
		fresh->AlbumName = formatting_process(rx->subexps[17].value);
		sscanf(rx->subexps[18].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[19].value);
		fresh->SubGenre = formatting_process(rx->subexps[20].value);
		fresh->CoverURL = formatting_process(rx->subexps[21].value);
		sscanf(rx->subexps[22].value,"%d",&(fresh->BitRate));
		sscanf(rx->subexps[23].value,"%d",&(fresh->CoverAvailable));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_type3row*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetTracksForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrow *base = 0, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetTracksForGenre_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrow *base = 0, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetTracksForNamedEntity_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrow *base = 0, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetTracksForPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	df_tracksforplaylistrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_tracksforplaylistrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		sscanf(rx->subexps[16].value,"%d",&(fresh->Hidden));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_tracksforplaylistrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetTracksForServer_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrow *base = 0, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetTracksForShare_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrow *base = 0, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetTracksForSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrow *base = 0, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetTracksForSubGenreForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrow *base = 0, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetTracksForSubGenreForServer_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrow *base = 0, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetTracksForSubGenreForShare_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackrow *base = 0, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_trackrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_trackrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetTracksOtherInfo_handler(out_request *request, out_response *response, int num, void* context) {
	df_type3row *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_type3row));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		sscanf(rx->subexps[16].value,"%d",&(fresh->AlbumKey));
		fresh->AlbumName = formatting_process(rx->subexps[17].value);
		sscanf(rx->subexps[18].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[19].value);
		fresh->SubGenre = formatting_process(rx->subexps[20].value);
		fresh->CoverURL = formatting_process(rx->subexps[21].value);
		sscanf(rx->subexps[22].value,"%d",&(fresh->BitRate));
		sscanf(rx->subexps[23].value,"%d",&(fresh->CoverAvailable));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_type3row*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetTracksSearchName_handler(out_request *request, out_response *response, int num, void* context) {
	df_type3row *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_type3row));		sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		fresh->SortName = formatting_process(rx->subexps[5].value);
		fresh->Type = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
		sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
		sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
		sscanf(rx->subexps[16].value,"%d",&(fresh->AlbumKey));
		fresh->AlbumName = formatting_process(rx->subexps[17].value);
		sscanf(rx->subexps[18].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[19].value);
		fresh->SubGenre = formatting_process(rx->subexps[20].value);
		fresh->CoverURL = formatting_process(rx->subexps[21].value);
		sscanf(rx->subexps[22].value,"%d",&(fresh->BitRate));
		sscanf(rx->subexps[23].value,"%d",&(fresh->CoverAvailable));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_type3row*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetUpnpMediaRenderers_handler(out_request *request, out_response *response, int num, void* context) {
	df_mediarendererrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_mediarendererrow));		fresh->FriendlyName = formatting_process(rx->subexps[3].value);
		fresh->UDN = formatting_process(rx->subexps[4].value);
		fresh->Manufacturer = formatting_process(rx->subexps[5].value);
		fresh->ModelNumber = formatting_process(rx->subexps[6].value);
		fresh->SupportedExtensions = formatting_process(rx->subexps[7].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_mediarendererrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetUserPlaylists_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetUserPlaylistsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetUserPlaylistsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetUserPlaylistsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_albumrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		fresh->Name = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
		fresh->ArtistName = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
		sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
		sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_albumrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void GetUserStatus_handler(out_request *request, out_response *response, int num, void* context) {
	df_keyvaluerow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_keyvaluerow));		fresh->Name = formatting_process(rx->subexps[3].value);
		fresh->Value = formatting_process(rx->subexps[4].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_keyvaluerow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void MoveAlbumGetQueue_handler(out_request *request, out_response *response, int num, void* context) {
	df_movealbumgetqueuerow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_movealbumgetqueuerow));		sscanf(rx->subexps[3].value,"%d",&(fresh->QueueKey));
		fresh->Status = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->Retries));
		fresh->LastError = formatting_process(rx->subexps[6].value);
		sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->CreatedDate.year), &(fresh->CreatedDate.month), &(fresh->CreatedDate.day));
		sscanf(rx->subexps[8].value,"%u:%u:%u", &(fresh->CreatedTime.hours), &(fresh->CreatedTime.minutes), &(fresh->CreatedTime.seconds));
		sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->ModifiedDate.year), &(fresh->ModifiedDate.month), &(fresh->ModifiedDate.day));
		sscanf(rx->subexps[10].value,"%u:%u:%u", &(fresh->ModifiedTime.hours), &(fresh->ModifiedTime.minutes), &(fresh->ModifiedTime.seconds));
		sscanf(rx->subexps[11].value,"%u-%u-%u", &(fresh->LastRetryDate.year), &(fresh->LastRetryDate.month), &(fresh->LastRetryDate.day));
		sscanf(rx->subexps[12].value,"%u:%u:%u", &(fresh->LastRetryTime.hours), &(fresh->LastRetryTime.minutes), &(fresh->LastRetryTime.seconds));
		sscanf(rx->subexps[13].value,"%d",&(fresh->AlbumKey));
		sscanf(rx->subexps[14].value,"%d",&(fresh->StoreKey));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_movealbumgetqueuerow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void Status_handler(out_request *request, out_response *response, int num, void* context) {
	df_statusrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_statusrow));		fresh->StatusSettingName = formatting_process(rx->subexps[3].value);
		fresh->StatusSettingValue = formatting_process(rx->subexps[4].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_statusrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void UndoUserEdits_handler(out_request *request, out_response *response, int num, void* context) {
	df_bulklookuprow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_bulklookuprow));		sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
		sscanf(rx->subexps[4].value,"%d",&(fresh->Success));
		fresh->Message = formatting_process(rx->subexps[5].value);
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_bulklookuprow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void vTunerGetChildNodes_handler(out_request *request, out_response *response, int num, void* context) {
	df_vtunernoderow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_vtunernoderow));		fresh->Name = formatting_process(rx->subexps[3].value);
		sscanf(rx->subexps[4].value,"%d",&(fresh->NodeType));
		fresh->UrlBookmark = formatting_process(rx->subexps[5].value);
		fresh->UrlPlay = formatting_process(rx->subexps[6].value);
		fresh->UrlChildren = formatting_process(rx->subexps[7].value);
		fresh->UrlChildrenBackup = formatting_process(rx->subexps[8].value);
		fresh->ID = formatting_process(rx->subexps[9].value);
		fresh->Description = formatting_process(rx->subexps[10].value);
		fresh->ParentDescription = formatting_process(rx->subexps[11].value);
		fresh->Format = formatting_process(rx->subexps[12].value);
		fresh->Language = formatting_process(rx->subexps[13].value);
		fresh->City = formatting_process(rx->subexps[14].value);
		fresh->State = formatting_process(rx->subexps[15].value);
		fresh->Country = formatting_process(rx->subexps[16].value);
		fresh->Location = formatting_process(rx->subexps[17].value);
		sscanf(rx->subexps[18].value,"%d",&(fresh->Bandwidth));
		fresh->MimeType = formatting_process(rx->subexps[19].value);
		sscanf(rx->subexps[20].value,"%d",&(fresh->ReliabilityRating));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_vtunernoderow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void vTunerGetLastPlayed_handler(out_request *request, out_response *response, int num, void* context) {
	df_vtunerplayedrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_vtunerplayedrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->Key));
		sscanf(rx->subexps[4].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[5].value,"%u-%u-%u", &(fresh->LastPlayed.year), &(fresh->LastPlayed.month), &(fresh->LastPlayed.day));
		sscanf(rx->subexps[6].value,"%u:%u:%u", &(fresh->LastPlayedTime.hours), &(fresh->LastPlayedTime.minutes), &(fresh->LastPlayedTime.seconds));
		sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[8].value,"%u:%u:%u", &(fresh->CreatedTime.hours), &(fresh->CreatedTime.minutes), &(fresh->CreatedTime.seconds));
		fresh->Name = formatting_process(rx->subexps[9].value);
		sscanf(rx->subexps[10].value,"%d",&(fresh->NodeType));
		fresh->UrlBookmark = formatting_process(rx->subexps[11].value);
		fresh->UrlPlay = formatting_process(rx->subexps[12].value);
		fresh->UrlChildren = formatting_process(rx->subexps[13].value);
		fresh->UrlChildrenBackup = formatting_process(rx->subexps[14].value);
		fresh->ID = formatting_process(rx->subexps[15].value);
		fresh->Description = formatting_process(rx->subexps[16].value);
		fresh->ParentDescription = formatting_process(rx->subexps[17].value);
		fresh->Format = formatting_process(rx->subexps[18].value);
		fresh->Language = formatting_process(rx->subexps[19].value);
		fresh->City = formatting_process(rx->subexps[20].value);
		fresh->State = formatting_process(rx->subexps[21].value);
		fresh->Country = formatting_process(rx->subexps[22].value);
		fresh->Location = formatting_process(rx->subexps[23].value);
		sscanf(rx->subexps[24].value,"%d",&(fresh->Bandwidth));
		fresh->MimeType = formatting_process(rx->subexps[25].value);
		sscanf(rx->subexps[26].value,"%d",&(fresh->ReliabilityRating));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_vtunerplayedrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void vTunerGetMostPlayed_handler(out_request *request, out_response *response, int num, void* context) {
	df_vtunerplayedrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_vtunerplayedrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->Key));
		sscanf(rx->subexps[4].value,"%d",&(fresh->HitCount));
		sscanf(rx->subexps[5].value,"%u-%u-%u", &(fresh->LastPlayed.year), &(fresh->LastPlayed.month), &(fresh->LastPlayed.day));
		sscanf(rx->subexps[6].value,"%u:%u:%u", &(fresh->LastPlayedTime.hours), &(fresh->LastPlayedTime.minutes), &(fresh->LastPlayedTime.seconds));
		sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[8].value,"%u:%u:%u", &(fresh->CreatedTime.hours), &(fresh->CreatedTime.minutes), &(fresh->CreatedTime.seconds));
		fresh->Name = formatting_process(rx->subexps[9].value);
		sscanf(rx->subexps[10].value,"%d",&(fresh->NodeType));
		fresh->UrlBookmark = formatting_process(rx->subexps[11].value);
		fresh->UrlPlay = formatting_process(rx->subexps[12].value);
		fresh->UrlChildren = formatting_process(rx->subexps[13].value);
		fresh->UrlChildrenBackup = formatting_process(rx->subexps[14].value);
		fresh->ID = formatting_process(rx->subexps[15].value);
		fresh->Description = formatting_process(rx->subexps[16].value);
		fresh->ParentDescription = formatting_process(rx->subexps[17].value);
		fresh->Format = formatting_process(rx->subexps[18].value);
		fresh->Language = formatting_process(rx->subexps[19].value);
		fresh->City = formatting_process(rx->subexps[20].value);
		fresh->State = formatting_process(rx->subexps[21].value);
		fresh->Country = formatting_process(rx->subexps[22].value);
		fresh->Location = formatting_process(rx->subexps[23].value);
		sscanf(rx->subexps[24].value,"%d",&(fresh->Bandwidth));
		fresh->MimeType = formatting_process(rx->subexps[25].value);
		sscanf(rx->subexps[26].value,"%d",&(fresh->ReliabilityRating));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_vtunerplayedrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void vTunerGetNodeFromPlayedUrl_handler(out_request *request, out_response *response, int num, void* context) {
	df_vtunernoderow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_vtunernoderow));		fresh->Name = formatting_process(rx->subexps[3].value);
		sscanf(rx->subexps[4].value,"%d",&(fresh->NodeType));
		fresh->UrlBookmark = formatting_process(rx->subexps[5].value);
		fresh->UrlPlay = formatting_process(rx->subexps[6].value);
		fresh->UrlChildren = formatting_process(rx->subexps[7].value);
		fresh->UrlChildrenBackup = formatting_process(rx->subexps[8].value);
		fresh->ID = formatting_process(rx->subexps[9].value);
		fresh->Description = formatting_process(rx->subexps[10].value);
		fresh->ParentDescription = formatting_process(rx->subexps[11].value);
		fresh->Format = formatting_process(rx->subexps[12].value);
		fresh->Language = formatting_process(rx->subexps[13].value);
		fresh->City = formatting_process(rx->subexps[14].value);
		fresh->State = formatting_process(rx->subexps[15].value);
		fresh->Country = formatting_process(rx->subexps[16].value);
		fresh->Location = formatting_process(rx->subexps[17].value);
		sscanf(rx->subexps[18].value,"%d",&(fresh->Bandwidth));
		fresh->MimeType = formatting_process(rx->subexps[19].value);
		sscanf(rx->subexps[20].value,"%d",&(fresh->ReliabilityRating));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_vtunernoderow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void vTunerGetPresetChannels_handler(out_request *request, out_response *response, int num, void* context) {
	df_vtunerpresetrow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_vtunerpresetrow));		sscanf(rx->subexps[3].value,"%d",&(fresh->Key));
		sscanf(rx->subexps[4].value,"%d",&(fresh->ChannelNumber));
		fresh->ChannelName = formatting_process(rx->subexps[5].value);
		sscanf(rx->subexps[6].value,"%u-%u-%u", &(fresh->Modified.year), &(fresh->Modified.month), &(fresh->Modified.day));
		sscanf(rx->subexps[7].value,"%u:%u:%u", &(fresh->ModifiedTime.hours), &(fresh->ModifiedTime.minutes), &(fresh->ModifiedTime.seconds));
		sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
		sscanf(rx->subexps[9].value,"%u:%u:%u", &(fresh->CreatedTime.hours), &(fresh->CreatedTime.minutes), &(fresh->CreatedTime.seconds));
		fresh->Name = formatting_process(rx->subexps[10].value);
		sscanf(rx->subexps[11].value,"%d",&(fresh->NodeType));
		fresh->UrlBookmark = formatting_process(rx->subexps[12].value);
		fresh->UrlPlay = formatting_process(rx->subexps[13].value);
		fresh->UrlChildren = formatting_process(rx->subexps[14].value);
		fresh->UrlChildrenBackup = formatting_process(rx->subexps[15].value);
		fresh->ID = formatting_process(rx->subexps[16].value);
		fresh->Description = formatting_process(rx->subexps[17].value);
		fresh->ParentDescription = formatting_process(rx->subexps[18].value);
		fresh->Format = formatting_process(rx->subexps[19].value);
		fresh->Language = formatting_process(rx->subexps[20].value);
		fresh->City = formatting_process(rx->subexps[21].value);
		fresh->State = formatting_process(rx->subexps[22].value);
		fresh->Country = formatting_process(rx->subexps[23].value);
		fresh->Location = formatting_process(rx->subexps[24].value);
		sscanf(rx->subexps[25].value,"%d",&(fresh->Bandwidth));
		fresh->MimeType = formatting_process(rx->subexps[26].value);
		sscanf(rx->subexps[27].value,"%d",&(fresh->ReliabilityRating));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_vtunerpresetrow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}

static void vTunerLookupById_handler(out_request *request, out_response *response, int num, void* context) {
	df_vtunernoderow *base, *current, *fresh;
	int i;
	regex_result *rx;
	struct call_holder *holder = context;

	for (i = 0; i < num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_vtunernoderow));		fresh->Name = formatting_process(rx->subexps[3].value);
		sscanf(rx->subexps[4].value,"%d",&(fresh->NodeType));
		fresh->UrlBookmark = formatting_process(rx->subexps[5].value);
		fresh->UrlPlay = formatting_process(rx->subexps[6].value);
		fresh->UrlChildren = formatting_process(rx->subexps[7].value);
		fresh->UrlChildrenBackup = formatting_process(rx->subexps[8].value);
		fresh->ID = formatting_process(rx->subexps[9].value);
		fresh->Description = formatting_process(rx->subexps[10].value);
		fresh->ParentDescription = formatting_process(rx->subexps[11].value);
		fresh->Format = formatting_process(rx->subexps[12].value);
		fresh->Language = formatting_process(rx->subexps[13].value);
		fresh->City = formatting_process(rx->subexps[14].value);
		fresh->State = formatting_process(rx->subexps[15].value);
		fresh->Country = formatting_process(rx->subexps[16].value);
		fresh->Location = formatting_process(rx->subexps[17].value);
		sscanf(rx->subexps[18].value,"%d",&(fresh->Bandwidth));
		fresh->MimeType = formatting_process(rx->subexps[19].value);
		sscanf(rx->subexps[20].value,"%d",&(fresh->ReliabilityRating));
		fresh->next = NULL;

		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}

	((void (*)(int, df_vtunernoderow*, void*))(holder->callback))(num, base, holder->context);
	free(holder);

}



// Generated get handlers
static void ActivateExternalStorage_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void AddAlbumsToUserPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void AddExternalStorage_handler(out_request *request, out_response *response, int num, void* context) {
	df_extstorageresult* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_extstorageresult));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->AddExternalStorage_Success));
	tmp->AddExternalStorage_Message = formatting_process(rx->subexps[3].value);
	sscanf(rx->subexps[4].value,"%d",&(tmp->AddExternalStorage_Key));
	tmp->AddExternalStorage_Hostname = formatting_process(rx->subexps[5].value);
	tmp->AddExternalStorage_IPAddress = formatting_process(rx->subexps[6].value);
	tmp->AddExternalStorage_ShareName = formatting_process(rx->subexps[7].value);
	tmp->AddExternalStorage_Username = formatting_process(rx->subexps[8].value);
	tmp->AddExternalStorage_Password = formatting_process(rx->subexps[9].value);

	((void (*)(df_extstorageresult*, void*))(holder->callback))(tmp, holder->context);

}

static void AddNewBackupJob_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void AddNewDrive_handler(out_request *request, out_response *response, int num, void* context) {
	df_newdriveresult* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_newdriveresult));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->AddNewDrive_Return));
	tmp->AddNewDrive_ErrorMessage = formatting_process(rx->subexps[3].value);

	((void (*)(df_newdriveresult*, void*))(holder->callback))(tmp, holder->context);

}

static void AddNewGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void AddNewLinkedRoom_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void AddNewRoom_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void AddNewSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void AddTracksToUserPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void BackupDrive_handler(out_request *request, out_response *response, int num, void* context) {
	df_backupresult* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_backupresult));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->BackupDrive_Success));
	tmp->BackupDrive_Message = formatting_process(rx->subexps[3].value);

	((void (*)(df_backupresult*, void*))(holder->callback))(tmp, holder->context);

}

static void BulkCDLookupEx_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CDLookupGetStatus_handler(out_request *request, out_response *response, int num, void* context) {
	df_type0* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_type0));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->Running));
	sscanf(rx->subexps[3].value,"%d",&(tmp->AlbumKey));
	tmp->AlbumName = formatting_process(rx->subexps[4].value);
	sscanf(rx->subexps[5].value,"%d",&(tmp->Progress));

	((void (*)(df_type0*, void*))(holder->callback))(tmp, holder->context);

}

static void CancelRipping_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void ChangeAlbumSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	char* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		tmp = formatting_process(rx->subexps[2].value);

	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);

}

static void ChangeNetworkAutoIP_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void ChangeNetworkDhcp_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void ChangeNetworkMachineName_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void ChangeNetworkStatic_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void ChangeNetworkWorkgroup_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void ChangeSystemSerialNumber_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void ChangeTrackOrdinal_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CheckCoverImage_handler(out_request *request, out_response *response, int num, void* context) {
	df_coverimage* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_coverimage));


	rx = response->result->result;
		tmp->CoverImageName = formatting_process(rx->subexps[2].value);
	tmp->CoverImageURI = formatting_process(rx->subexps[3].value);

	((void (*)(df_coverimage*, void*))(holder->callback))(tmp, holder->context);

}

static void CompactGenreOrdinals_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void ComplexSearchCountAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void ComplexSearchCountArtists_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void ComplexSearchCountContributors_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void ComplexSearchCountTracks_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountAlbumsForArtist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountAlbumsForArtistForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountAlbumsForArtistForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountAlbumsForArtistForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountAlbumsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountAlbumsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountAlbumsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountArtists_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountArtistsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountArtistsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountArtistsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountDevices_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountGenres_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountPlaylistsForSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountPlaylistsForSubGenreForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountPlaylistsForSubGenreForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountPlaylistsForSubGenreForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountShares_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountSubGenresForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountSubGenresForGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountSubGenresForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountSubGenresForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountTracksAll_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountTracksForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountTracksForPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountTracksForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountTracksForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountUserPlaylists_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountUserPlaylistsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountUserPlaylistsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CountUserPlaylistsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CreatePlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CreateRandomPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void CreateRandomPlaylistEx_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void DeleteAlbum_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void DeleteBackupJob_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void DeleteDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void DeleteDrive_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void DeleteGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void DeleteLinkedRoom_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void DeleteOutputChannel_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void DeleteRoom_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void DeleteSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void DeleteTrack_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void DemoteMusicStoreToShare_handler(out_request *request, out_response *response, int num, void* context) {
	df_demoteresult* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_demoteresult));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->DemoteMusicStoreToShare_Success));
	tmp->DemoteMusicStoreToShare_Message = formatting_process(rx->subexps[3].value);

	((void (*)(df_demoteresult*, void*))(holder->callback))(tmp, holder->context);

}

static void DeviceChecksum_handler(out_request *request, out_response *response, int num, void* context) {
	char* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		tmp = formatting_process(rx->subexps[2].value);

	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);

}

static void DisconnectDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void ExternalStorageCancelScan_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void FindAllRooms_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void FindNewRooms_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void ForceGenrePlaylistBackup_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void ForceGenrePlaylistRestore_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void GetAlbumArtist_handler(out_request *request, out_response *response, int num, void* context) {
	df_albumartist* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_albumartist));


	rx = response->result->result;
		tmp->Album = formatting_process(rx->subexps[2].value);
	tmp->Artist = formatting_process(rx->subexps[3].value);

	((void (*)(df_albumartist*, void*))(holder->callback))(tmp, holder->context);

}

static void GetBackupStatus_handler(out_request *request, out_response *response, int num, void* context) {
	df_backupstatus* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_backupstatus));


	rx = response->result->result;
		tmp->Backup_SourceDrive = formatting_process(rx->subexps[2].value);
	tmp->Backup_DestDrive = formatting_process(rx->subexps[3].value);
	tmp->Backup_Type = formatting_process(rx->subexps[4].value);
	tmp->Backup_Status = formatting_process(rx->subexps[5].value);
	tmp->Backup_CurrentFile = formatting_process(rx->subexps[6].value);
	tmp->Backup_LastError = formatting_process(rx->subexps[7].value);
	sscanf(rx->subexps[8].value,"%u:%u:%u", &(tmp->Backup_TimeTaken.hours), &(tmp->Backup_TimeTaken.minutes), &(tmp->Backup_TimeTaken.seconds));
	sscanf(rx->subexps[9].value,"%u:%u:%u", &(tmp->Backup_TimeRemaining.hours), &(tmp->Backup_TimeRemaining.minutes), &(tmp->Backup_TimeRemaining.seconds));
	sscanf(rx->subexps[10].value,"%d",&(tmp->Backup_SourceFileCount));
	sscanf(rx->subexps[11].value,"%d",&(tmp->Backup_SourceFolderCount));
	sscanf(rx->subexps[12].value,"%ld",&(tmp->Backup_SourceByteCount));
	sscanf(rx->subexps[13].value,"%d",&(tmp->Backup_ProcessedFileCount));
	sscanf(rx->subexps[14].value,"%d",&(tmp->Backup_ProcessedFolderCount));
	sscanf(rx->subexps[15].value,"%ld",&(tmp->Backup_ProcessedByteCount));
	sscanf(rx->subexps[16].value,"%d",&(tmp->Backup_ErrorCount));
	sscanf(rx->subexps[17].value,"%d",&(tmp->Backup_ErrorFileCount));
	sscanf(rx->subexps[18].value,"%ld",&(tmp->Backup_ErrorByteCount));

	((void (*)(df_backupstatus*, void*))(holder->callback))(tmp, holder->context);

}

static void GetCount_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void GetCurOp_handler(out_request *request, out_response *response, int num, void* context) {
	char* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		tmp = formatting_process(rx->subexps[2].value);

	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);

}

static void GetDriveDetail_handler(out_request *request, out_response *response, int num, void* context) {
	df_drivedetail* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_drivedetail));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->DriveKey));
	tmp->DriveLetter = formatting_process(rx->subexps[3].value);
	sscanf(rx->subexps[4].value,"%d",&(tmp->Primary));
	tmp->RootPath = formatting_process(rx->subexps[5].value);
	tmp->SharePath = formatting_process(rx->subexps[6].value);
	sscanf(rx->subexps[7].value,"%u-%u-%u", &(tmp->Created.year), &(tmp->Created.month), &(tmp->Created.day));
	sscanf(rx->subexps[8].value,"%u-%u-%u", &(tmp->Modified.year), &(tmp->Modified.month), &(tmp->Modified.day));
	sscanf(rx->subexps[9].value,"%d",&(tmp->Usage));
	sscanf(rx->subexps[10].value,"%u-%u-%u", &(tmp->LastBackup.year), &(tmp->LastBackup.month), &(tmp->LastBackup.day));

	((void (*)(df_drivedetail*, void*))(holder->callback))(tmp, holder->context);

}

static void GetExtCountAlbumsByContributor_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void GetExtCountAlbumsByContributorForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void GetExtCountAlbumsByContributorForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void GetExtCountAlbumsByContributorForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void GetExtCountContributors_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void GetExtCountContributorsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void GetExtCountContributorsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void GetExtCountContributorsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void GetExternalStorageDetail_handler(out_request *request, out_response *response, int num, void* context) {
	df_extstoragedetail* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_extstoragedetail));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->StorageKey));
	tmp->IPAddress = formatting_process(rx->subexps[3].value);
	tmp->HostName = formatting_process(rx->subexps[4].value);
	tmp->ShareName = formatting_process(rx->subexps[5].value);
	tmp->FullSharePath = formatting_process(rx->subexps[6].value);
	tmp->State = formatting_process(rx->subexps[7].value);
	tmp->LastState = formatting_process(rx->subexps[8].value);
	sscanf(rx->subexps[9].value,"%d",&(tmp->Active));
	sscanf(rx->subexps[10].value,"%u-%u-%u", &(tmp->Created.year), &(tmp->Created.month), &(tmp->Created.day));
	sscanf(rx->subexps[11].value,"%u-%u-%u", &(tmp->Modified.year), &(tmp->Modified.month), &(tmp->Modified.day));
	sscanf(rx->subexps[12].value,"%u-%u-%u", &(tmp->LastScanDate.year), &(tmp->LastScanDate.month), &(tmp->LastScanDate.day));
	sscanf(rx->subexps[13].value,"%u:%u:%u", &(tmp->LastScanTime.hours), &(tmp->LastScanTime.minutes), &(tmp->LastScanTime.seconds));
	tmp->UserName = formatting_process(rx->subexps[14].value);
	tmp->Password = formatting_process(rx->subexps[15].value);
	tmp->ScanIgnore = formatting_process(rx->subexps[16].value);

	((void (*)(df_extstoragedetail*, void*))(holder->callback))(tmp, holder->context);

}

static void GetFileSystemDriveDetail_handler(out_request *request, out_response *response, int num, void* context) {
	df_fsdrivedetail* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_fsdrivedetail));


	rx = response->result->result;
		tmp->DriveLetter = formatting_process(rx->subexps[2].value);
	tmp->RootPath = formatting_process(rx->subexps[3].value);
	tmp->SharePath = formatting_process(rx->subexps[4].value);
	sscanf(rx->subexps[5].value,"%d",&(tmp->Usage));

	((void (*)(df_fsdrivedetail*, void*))(holder->callback))(tmp, holder->context);

}

static void GetGenreDetail_handler(out_request *request, out_response *response, int num, void* context) {
	df_genre* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_genre));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->GenreKey));
	tmp->GenreName = formatting_process(rx->subexps[3].value);
	sscanf(rx->subexps[4].value,"%u-%u-%u", &(tmp->Created.year), &(tmp->Created.month), &(tmp->Created.day));
	sscanf(rx->subexps[5].value,"%u-%u-%u", &(tmp->Modified.year), &(tmp->Modified.month), &(tmp->Modified.day));
	sscanf(rx->subexps[6].value,"%d",&(tmp->Ordinal));
	sscanf(rx->subexps[7].value,"%d",&(tmp->Storage));

	((void (*)(df_genre*, void*))(holder->callback))(tmp, holder->context);

}

static void GetHostDetails_handler(out_request *request, out_response *response, int num, void* context) {
	df_hostdetails* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_hostdetails));


	rx = response->result->result;
		tmp->GetHostDetails_Name = formatting_process(rx->subexps[2].value);
	tmp->GetHostDetails_Address = formatting_process(rx->subexps[3].value);

	((void (*)(df_hostdetails*, void*))(holder->callback))(tmp, holder->context);

}

static void GetLastError_handler(out_request *request, out_response *response, int num, void* context) {
	char* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		tmp = formatting_process(rx->subexps[2].value);

	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);

}

static void GetLibraryCheckSum_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void GetNetworkWorkgroup_handler(out_request *request, out_response *response, int num, void* context) {
	char* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		tmp = formatting_process(rx->subexps[2].value);

	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);

}

static void GetOperationActivity_handler(out_request *request, out_response *response, int num, void* context) {
	char* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		tmp = formatting_process(rx->subexps[2].value);

	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);

}

static void GetPlayerStatus_handler(out_request *request, out_response *response, int num, void* context) {
	char* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		tmp = formatting_process(rx->subexps[2].value);

	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);

}

static void GetPlayerVersion_handler(out_request *request, out_response *response, int num, void* context) {
	char* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		tmp = formatting_process(rx->subexps[2].value);

	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);

}

static void GetRepeat_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void GetRoomDetail_handler(out_request *request, out_response *response, int num, void* context) {
	df_room* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_room));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->RoomKey));
	tmp->IPAddress = formatting_process(rx->subexps[3].value);
	sscanf(rx->subexps[4].value,"%d",&(tmp->Channel));
	tmp->RoomName = formatting_process(rx->subexps[5].value);
	sscanf(rx->subexps[6].value,"%d",&(tmp->ShortName));
	sscanf(rx->subexps[7].value,"%d",&(tmp->IsMultiRoom));
	sscanf(rx->subexps[8].value,"%d",&(tmp->PlaybackCapability));
	sscanf(rx->subexps[9].value,"%d",&(tmp->RippingCapability));
	sscanf(rx->subexps[10].value,"%d",&(tmp->MusicManagementCapability));
	sscanf(rx->subexps[11].value,"%d",&(tmp->RoomID));
	tmp->HostName = formatting_process(rx->subexps[12].value);
	sscanf(rx->subexps[13].value,"%d",&(tmp->Created));
	sscanf(rx->subexps[14].value,"%d",&(tmp->Modified));

	((void (*)(df_room*, void*))(holder->callback))(tmp, holder->context);

}

static void GetRows_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void GetSearchOffset_handler(out_request *request, out_response *response, int num, void* context) {
	df_searchoffset* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_searchoffset));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->GetSearchOffset_Return));
	sscanf(rx->subexps[3].value,"%d",&(tmp->GetSearchOffset_Count));

	((void (*)(df_searchoffset*, void*))(holder->callback))(tmp, holder->context);

}

static void GetSetupVal_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void GetShuffle_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void GetSingleRipEncSetting_handler(out_request *request, out_response *response, int num, void* context) {
	char* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		tmp = formatting_process(rx->subexps[2].value);

	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);

}

static void GetSingleSystemSetting_handler(out_request *request, out_response *response, int num, void* context) {
	char* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		tmp = formatting_process(rx->subexps[2].value);

	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);

}

static void GetStatusMessageDetail_handler(out_request *request, out_response *response, int num, void* context) {
	df_messagedetail* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_messagedetail));


	rx = response->result->result;
		tmp->Message = formatting_process(rx->subexps[2].value);
	tmp->Category = formatting_process(rx->subexps[3].value);
	sscanf(rx->subexps[4].value,"%u-%u-%u", &(tmp->DateCreated.year), &(tmp->DateCreated.month), &(tmp->DateCreated.day));

	((void (*)(df_messagedetail*, void*))(holder->callback))(tmp, holder->context);

}

static void GetSubGenreDetail_handler(out_request *request, out_response *response, int num, void* context) {
	df_subgenre* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_subgenre));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->SubGenreKey));
	sscanf(rx->subexps[3].value,"%d",&(tmp->GenreKey));
	tmp->SubGenreName = formatting_process(rx->subexps[4].value);
	sscanf(rx->subexps[5].value,"%u-%u-%u", &(tmp->Created.year), &(tmp->Created.month), &(tmp->Created.day));
	sscanf(rx->subexps[6].value,"%u-%u-%u", &(tmp->Modified.year), &(tmp->Modified.month), &(tmp->Modified.day));
	sscanf(rx->subexps[7].value,"%d",&(tmp->Ordinal));

	((void (*)(df_subgenre*, void*))(holder->callback))(tmp, holder->context);

}

static void GetSystemTime_handler(out_request *request, out_response *response, int num, void* context) {
	df_systemtime* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_systemtime));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%u-%u-%u", &(tmp->GetSystemTime_Date.year), &(tmp->GetSystemTime_Date.month), &(tmp->GetSystemTime_Date.day));
	sscanf(rx->subexps[3].value,"%u:%u:%u", &(tmp->GetSystemTime_Time.hours), &(tmp->GetSystemTime_Time.minutes), &(tmp->GetSystemTime_Time.seconds));

	((void (*)(df_systemtime*, void*))(holder->callback))(tmp, holder->context);

}

static void GetTrackCount_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void GetTrackDetailsFromPlayer_handler(out_request *request, out_response *response, int num, void* context) {
	df_trackfromplayer* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_trackfromplayer));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->Source));
	tmp->Name = formatting_process(rx->subexps[3].value);
	tmp->Album = formatting_process(rx->subexps[4].value);
	tmp->Artist = formatting_process(rx->subexps[5].value);
	tmp->Genre = formatting_process(rx->subexps[6].value);
	tmp->Comment = formatting_process(rx->subexps[7].value);
	sscanf(rx->subexps[8].value,"%u:%u:%u", &(tmp->Length.hours), &(tmp->Length.minutes), &(tmp->Length.seconds));

	((void (*)(df_trackfromplayer*, void*))(holder->callback))(tmp, holder->context);

}

static void GetTrackLength_handler(out_request *request, out_response *response, int num, void* context) {
	df_time tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%u:%u:%u", &(tmp.hours), &(tmp.minutes), &(tmp.seconds));

	((void (*)(df_time, void*))(holder->callback))(tmp, holder->context);

}

static void GetTrackName_handler(out_request *request, out_response *response, int num, void* context) {
	df_trkname* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_trkname));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->TrackKey));
	tmp->Name = formatting_process(rx->subexps[3].value);
	tmp->Type = formatting_process(rx->subexps[4].value);
	sscanf(rx->subexps[5].value,"%u:%u:%u", &(tmp->Length.hours), &(tmp->Length.minutes), &(tmp->Length.seconds));
	sscanf(rx->subexps[6].value,"%d",&(tmp->Source));

	((void (*)(df_trkname*, void*))(holder->callback))(tmp, holder->context);

}

static void GetTrackNum_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void GetTrackPosition_handler(out_request *request, out_response *response, int num, void* context) {
	df_time tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%u:%u:%u", &(tmp.hours), &(tmp.minutes), &(tmp.seconds));

	((void (*)(df_time, void*))(holder->callback))(tmp, holder->context);

}

static void GetVolume_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void IgnoreExternalStorage_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void IsCDPlaying_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void LookupError_handler(out_request *request, out_response *response, int num, void* context) {
	char* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		tmp = formatting_process(rx->subexps[2].value);

	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);

}

static void MoveAlbumGetStatus_handler(out_request *request, out_response *response, int num, void* context) {
	df_movealbumstatus* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_movealbumstatus));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->Running));
	sscanf(rx->subexps[3].value,"%d",&(tmp->AlbumKey));
	tmp->AlbumName = formatting_process(rx->subexps[4].value);
	sscanf(rx->subexps[5].value,"%d",&(tmp->SourceStoreKey));
	sscanf(rx->subexps[6].value,"%d",&(tmp->DestinationStoreKey));
	sscanf(rx->subexps[7].value,"%d",&(tmp->Progress));

	((void (*)(df_movealbumstatus*, void*))(holder->callback))(tmp, holder->context);

}

static void MoveAlbumToMusicStore_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void NewOutputChannel_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void NextTrack_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void PlayAlbum_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void PlayAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void PlayAlbumsFromSearch_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void PlayAll_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void PlayArtistAlbum_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void PlayLastPlayed_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void PlayLastRipped_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void PlayMostPopular_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void PlayPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void PlayRandom_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void PlayTrack_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void PlayTracks_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void PlayTracksFromSearch_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void PlayUrl_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void PlayUrls_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void PrevTrack_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void ProcessEmbeddedInit_handler(out_request *request, out_response *response, int num, void* context) {
	char* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		tmp = formatting_process(rx->subexps[2].value);

	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);

}

static void PromoteShareToMusicStore_handler(out_request *request, out_response *response, int num, void* context) {
	df_promoteshare* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_promoteshare));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->PromoteShareToMusicStore_Success));
	tmp->PromoteShareToMusicStore_Message = formatting_process(rx->subexps[3].value);

	((void (*)(df_promoteshare*, void*))(holder->callback))(tmp, holder->context);

}

static void QueryAllPlayback_handler(out_request *request, out_response *response, int num, void* context) {
	df_queryplayback* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_queryplayback));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->CDPlaying));
	tmp->TrackName = formatting_process(rx->subexps[3].value);
	tmp->Album = formatting_process(rx->subexps[4].value);
	tmp->Artist = formatting_process(rx->subexps[5].value);
	sscanf(rx->subexps[6].value,"%d",&(tmp->TrackNumber));
	sscanf(rx->subexps[7].value,"%d",&(tmp->TrackCount));
	sscanf(rx->subexps[8].value,"%d",&(tmp->Shuffle));
	sscanf(rx->subexps[9].value,"%d",&(tmp->Repeat));
	tmp->Status = formatting_process(rx->subexps[10].value);
	sscanf(rx->subexps[11].value,"%u:%u:%u", &(tmp->TrackLength.hours), &(tmp->TrackLength.minutes), &(tmp->TrackLength.seconds));
	sscanf(rx->subexps[12].value,"%u:%u:%u", &(tmp->TrackPosition.hours), &(tmp->TrackPosition.minutes), &(tmp->TrackPosition.seconds));
	tmp->Version = formatting_process(rx->subexps[13].value);
	sscanf(rx->subexps[14].value,"%d",&(tmp->Volume));

	((void (*)(df_queryplayback*, void*))(holder->callback))(tmp, holder->context);

}

static void ReleaseSerialPort_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void RemoveAlbumsFromUserPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void RemoveCoverImage_handler(out_request *request, out_response *response, int num, void* context) {
	char* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		tmp = formatting_process(rx->subexps[2].value);

	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);

}

static void RemoveExternalStorage_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void RemoveOldRooms_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void RemovePlayerInstance_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void RemoveTrack_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void RenameAlbum_handler(out_request *request, out_response *response, int num, void* context) {
	char* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		tmp = formatting_process(rx->subexps[2].value);

	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);

}

static void RenameArtist_handler(out_request *request, out_response *response, int num, void* context) {
	char* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		tmp = formatting_process(rx->subexps[2].value);

	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);

}

static void RenamePlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void RenameTrack_handler(out_request *request, out_response *response, int num, void* context) {
	char* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		tmp = formatting_process(rx->subexps[2].value);

	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);

}

static void RequestAlbumCover_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void RescanExternalStorages_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void RescanMusicStore_handler(out_request *request, out_response *response, int num, void* context) {
	df_rescanresult* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_rescanresult));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->RescanMusicStore_Success));
	tmp->RescanMusicStore_Message = formatting_process(rx->subexps[3].value);

	((void (*)(df_rescanresult*, void*))(holder->callback))(tmp, holder->context);

}

static void RestoreSingleAlbum_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void RestoreSingleTrack_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void SaveCurrentPlayList_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void SavePlayerInstance_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void ScanExternalStorage_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void ScanForExternalStorages_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void ServiceMode_handler(out_request *request, out_response *response, int num, void* context) {
	df_servicemode* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_servicemode));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->ServiceMode_ModeValue));
	tmp->ServiceMode_ModeName = formatting_process(rx->subexps[3].value);

	((void (*)(df_servicemode*, void*))(holder->callback))(tmp, holder->context);

}

static void SetAlbumLowQuality_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void SetCoverImage_handler(out_request *request, out_response *response, int num, void* context) {
	char* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		tmp = formatting_process(rx->subexps[2].value);

	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);

}

static void SetDriveUsage_handler(out_request *request, out_response *response, int num, void* context) {
	df_driveusageresult* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_driveusageresult));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->SetDriveUsage_Success));
	sscanf(rx->subexps[3].value,"%d",&(tmp->SetDriveUsage_DriveInUse));
	tmp->SetDriveUsage_Message = formatting_process(rx->subexps[4].value);

	((void (*)(df_driveusageresult*, void*))(holder->callback))(tmp, holder->context);

}

static void SetMusicStoreCredentials_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void SetMusicStorePriority_handler(out_request *request, out_response *response, int num, void* context) {
	df_musicstorepriorityresult* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_musicstorepriorityresult));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->SetMusicStorePriority_Success));
	tmp->SetMusicStorePriority_Message = formatting_process(rx->subexps[3].value);

	((void (*)(df_musicstorepriorityresult*, void*))(holder->callback))(tmp, holder->context);

}

static void StopBackupDrive_handler(out_request *request, out_response *response, int num, void* context) {
	df_stopbackupdriveresult* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_stopbackupdriveresult));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->StopBackupDrive_Success));
	tmp->StopBackupDrive_Message = formatting_process(rx->subexps[3].value);

	((void (*)(df_stopbackupdriveresult*, void*))(holder->callback))(tmp, holder->context);

}

static void ToggleDeviceSync_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void UpdateBackupJob_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void UpdateDrive_handler(out_request *request, out_response *response, int num, void* context) {
	df_updatedrivedetails* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_updatedrivedetails));


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp->UpdateDrive_Return));
	tmp->UpdateDrive_ErrorMessage = formatting_process(rx->subexps[3].value);

	((void (*)(df_updatedrivedetails*, void*))(holder->callback))(tmp, holder->context);

}

static void UpdateExternalStorage_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void UpdateGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void UpdateHitCount_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void UpdateLinkedRoom_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void UpdateOutputChannel_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void UpdatePlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void UpdateRoom_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void UpdateSingleRipEncSetting_handler(out_request *request, out_response *response, int num, void* context) {
	char* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		tmp = formatting_process(rx->subexps[2].value);

	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);

}

static void UpdateSingleSystemSetting_handler(out_request *request, out_response *response, int num, void* context) {
	char* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		tmp = formatting_process(rx->subexps[2].value);

	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);

}

static void UpdateSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void UploadMessages_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void Version_handler(out_request *request, out_response *response, int num, void* context) {
	df_version* tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }

	tmp = malloc(sizeof(df_version));


	rx = response->result->result;
		tmp->Version_Service = formatting_process(rx->subexps[1].value);
	tmp->Version_Protocol = formatting_process(rx->subexps[2].value);
	tmp->Version_CommandDef = formatting_process(rx->subexps[3].value);
	tmp->Version_System = formatting_process(rx->subexps[4].value);

	((void (*)(df_version*, void*))(holder->callback))(tmp, holder->context);

}

static void vTunerAddRemoveFavourite_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void vTunerCheckAvailability_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void vTunerPlayById_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[1].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void vTunerPlayByIds_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

static void vTunerSetPresetChannel_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}
















