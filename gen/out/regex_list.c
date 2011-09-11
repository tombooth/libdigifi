
/*
 *  regex_list.c
 *  libdigifi.new
 *
 *  Created by Tom Booth on 09/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "regex_list.h"

#include "string.h"

char* regex_list_get(char *regex_name) {
	char *pattern;

	if (strcmp(regex_name, "void") == 0) {
		pattern="\\[(.+)\\]";
	}
	else if (strcmp(regex_name, "error") == 0) {
		pattern = "\\[ERR (.+)\\]";
	}
	else if (strcmp(regex_name, "findname") == 0) {
		pattern = "\\[([^[:space:]]+)[[:space:]+](.+)[^\\\\]\\]";
	}
	else if (strcmp(regex_name, "rowrequest") == 0) {
		pattern = "\\[ACK[[:space:]+]([^[:space:]]+)[[:space:]+]([0-9]+)[[:space:]+]\"([0-9]+)\"\\]";
	}
	else if (strcmp(regex_name, "rowrequestroom") == 0) {
		pattern = "\\[ACK[[:space:]+]([^[:space:]]+)[[:space:]+]([0-9]+)[[:space:]+]([0-9]+)[[:space:]+]\"([0-9]+)\"\\]";
	}

   
   else if (strcmp(regex_name, "GetCurOp") == 0) {
      pattern = "GetCurOp";
   }
   
   else if (strcmp(regex_name, "ReleaseSerialPort") == 0) {
      pattern = "ReleaseSerialPort";
   }
   
   else if (strcmp(regex_name, "Version") == 0) {
      pattern = "Version";
   }
   
   else if (strcmp(regex_name, "GetRows") == 0) {
      pattern = "GetRows";
   }
   
   else if (strcmp(regex_name, "GetCount") == 0) {
      pattern = "GetCount";
   }
   
   else if (strcmp(regex_name, "GetLastError") == 0) {
      pattern = "GetLastError";
   }
   
   else if (strcmp(regex_name, "LookupError") == 0) {
      pattern = "LookupError";
   }
   
   else if (strcmp(regex_name, "FindAllRooms") == 0) {
      pattern = "FindAllRooms";
   }
   
   else if (strcmp(regex_name, "FindNewRooms") == 0) {
      pattern = "FindNewRooms";
   }
   
   else if (strcmp(regex_name, "RemoveOldRooms") == 0) {
      pattern = "RemoveOldRooms";
   }
   
   else if (strcmp(regex_name, "ServiceMode") == 0) {
      pattern = "ServiceMode";
   }
   
   else if (strcmp(regex_name, "GetSearchOffset") == 0) {
      pattern = "GetSearchOffset";
   }
   
   else if (strcmp(regex_name, "FilterSearch") == 0) {
      pattern = "FilterSearch";
   }
   
   else if (strcmp(regex_name, "SortSearch") == 0) {
      pattern = "SortSearch";
   }
   
   else if (strcmp(regex_name, "GetSystemTime") == 0) {
      pattern = "GetSystemTime";
   }
   
   else if (strcmp(regex_name, "GetHostDetails") == 0) {
      pattern = "GetHostDetails";
   }
   
   else if (strcmp(regex_name, "GetRecycleBinStatus") == 0) {
      pattern = "GetRecycleBinStatus";
   }
   
   else if (strcmp(regex_name, "GetSetupVal") == 0) {
      pattern = "GetSetupVal";
   }
   
   else if (strcmp(regex_name, "NextTrack") == 0) {
      pattern = "NextTrack";
   }
   
   else if (strcmp(regex_name, "PrevTrack") == 0) {
      pattern = "PrevTrack";
   }
   
   else if (strcmp(regex_name, "RemoveTrack") == 0) {
      pattern = "RemoveTrack";
   }
   
   else if (strcmp(regex_name, "PlayAlbums") == 0) {
      pattern = "PlayAlbums";
   }
   
   else if (strcmp(regex_name, "PlayAll") == 0) {
      pattern = "PlayAll";
   }
   
   else if (strcmp(regex_name, "PlayAlbum") == 0) {
      pattern = "PlayAlbum";
   }
   
   else if (strcmp(regex_name, "PlayTrack") == 0) {
      pattern = "PlayTrack";
   }
   
   else if (strcmp(regex_name, "PlayTracks") == 0) {
      pattern = "PlayTracks";
   }
   
   else if (strcmp(regex_name, "PlayTracksFromSearch") == 0) {
      pattern = "PlayTracksFromSearch";
   }
   
   else if (strcmp(regex_name, "PlayAlbumsFromSearch") == 0) {
      pattern = "PlayAlbumsFromSearch";
   }
   
   else if (strcmp(regex_name, "PlayUrl") == 0) {
      pattern = "PlayUrl";
   }
   
   else if (strcmp(regex_name, "PlayUrls") == 0) {
      pattern = "PlayUrls";
   }
   
   else if (strcmp(regex_name, "PlayPlaylist") == 0) {
      pattern = "PlayPlaylist";
   }
   
   else if (strcmp(regex_name, "PlayRandom") == 0) {
      pattern = "PlayRandom";
   }
   
   else if (strcmp(regex_name, "PlayArtistAlbum") == 0) {
      pattern = "PlayArtistAlbum";
   }
   
   else if (strcmp(regex_name, "PlayLastPlayed") == 0) {
      pattern = "PlayLastPlayed";
   }
   
   else if (strcmp(regex_name, "PlayLastRipped") == 0) {
      pattern = "PlayLastRipped";
   }
   
   else if (strcmp(regex_name, "PlayMostPopular") == 0) {
      pattern = "PlayMostPopular";
   }
   
   else if (strcmp(regex_name, "IsCDPlaying") == 0) {
      pattern = "IsCDPlaying";
   }
   
   else if (strcmp(regex_name, "GetTrackName") == 0) {
      pattern = "GetTrackName";
   }
   
   else if (strcmp(regex_name, "GetTrackDetailsFromPlayer") == 0) {
      pattern = "GetTrackDetailsFromPlayer";
   }
   
   else if (strcmp(regex_name, "GetAlbumArtist") == 0) {
      pattern = "GetAlbumArtist";
   }
   
   else if (strcmp(regex_name, "GetTrackNum") == 0) {
      pattern = "GetTrackNum";
   }
   
   else if (strcmp(regex_name, "GetTrackCount") == 0) {
      pattern = "GetTrackCount";
   }
   
   else if (strcmp(regex_name, "GetShuffle") == 0) {
      pattern = "GetShuffle";
   }
   
   else if (strcmp(regex_name, "GetRepeat") == 0) {
      pattern = "GetRepeat";
   }
   
   else if (strcmp(regex_name, "GetPlayerStatus") == 0) {
      pattern = "GetPlayerStatus";
   }
   
   else if (strcmp(regex_name, "GetTrackLength") == 0) {
      pattern = "GetTrackLength";
   }
   
   else if (strcmp(regex_name, "GetTrackPosition") == 0) {
      pattern = "GetTrackPosition";
   }
   
   else if (strcmp(regex_name, "GetPlayerVersion") == 0) {
      pattern = "GetPlayerVersion";
   }
   
   else if (strcmp(regex_name, "GetVolume") == 0) {
      pattern = "GetVolume";
   }
   
   else if (strcmp(regex_name, "QueryAllPlayback") == 0) {
      pattern = "QueryAllPlayback";
   }
   
   else if (strcmp(regex_name, "GetRooms") == 0) {
      pattern = "GetRooms";
   }
   
   else if (strcmp(regex_name, "GetRoomsWithPlayBack") == 0) {
      pattern = "GetRoomsWithPlayBack";
   }
   
   else if (strcmp(regex_name, "GetRoomsWithRipping") == 0) {
      pattern = "GetRoomsWithRipping";
   }
   
   else if (strcmp(regex_name, "GetNonLinkedRooms") == 0) {
      pattern = "GetNonLinkedRooms";
   }
   
   else if (strcmp(regex_name, "GetLinkedRooms") == 0) {
      pattern = "GetLinkedRooms";
   }
   
   else if (strcmp(regex_name, "GetAdvancedStatus") == 0) {
      pattern = "GetAdvancedStatus";
   }
   
   else if (strcmp(regex_name, "GetUserStatus") == 0) {
      pattern = "GetUserStatus";
   }
   
   else if (strcmp(regex_name, "GetStatusMessages") == 0) {
      pattern = "GetStatusMessages";
   }
   
   else if (strcmp(regex_name, "GetStatusMessageDetail") == 0) {
      pattern = "GetStatusMessageDetail";
   }
   
   else if (strcmp(regex_name, "GetCurrentPlayList") == 0) {
      pattern = "GetCurrentPlayList";
   }
   
   else if (strcmp(regex_name, "GetCurrentPlaylistEx") == 0) {
      pattern = "GetCurrentPlaylistEx";
   }
   
   else if (strcmp(regex_name, "GetRippingAlerts") == 0) {
      pattern = "GetRippingAlerts";
   }
   
   else if (strcmp(regex_name, "GetAlertDetails") == 0) {
      pattern = "GetAlertDetails";
   }
   
   else if (strcmp(regex_name, "GetRippingStatus") == 0) {
      pattern = "GetRippingStatus";
   }
   
   else if (strcmp(regex_name, "GetRipEncSettings") == 0) {
      pattern = "GetRipEncSettings";
   }
   
   else if (strcmp(regex_name, "GetRipEncSettingsEx") == 0) {
      pattern = "GetRipEncSettingsEx";
   }
   
   else if (strcmp(regex_name, "GetSettings") == 0) {
      pattern = "GetSettings";
   }
   
   else if (strcmp(regex_name, "GetSettingsEx") == 0) {
      pattern = "GetSettingsEx";
   }
   
   else if (strcmp(regex_name, "GetAvailableValues") == 0) {
      pattern = "GetAvailableValues";
   }
   
   else if (strcmp(regex_name, "GetSystemDrives") == 0) {
      pattern = "GetSystemDrives";
   }
   
   else if (strcmp(regex_name, "GetEncodingQueue") == 0) {
      pattern = "GetEncodingQueue";
   }
   
   else if (strcmp(regex_name, "GetLibraryCheckSum") == 0) {
      pattern = "GetLibraryCheckSum";
   }
   
   else if (strcmp(regex_name, "CancelRipping") == 0) {
      pattern = "CancelRipping";
   }
   
   else if (strcmp(regex_name, "GetEncodingStatus") == 0) {
      pattern = "GetEncodingStatus";
   }
   
   else if (strcmp(regex_name, "GetPlayerInstances") == 0) {
      pattern = "GetPlayerInstances";
   }
   
   else if (strcmp(regex_name, "GetOutputDevices") == 0) {
      pattern = "GetOutputDevices";
   }
   
   else if (strcmp(regex_name, "GetOutputChannels") == 0) {
      pattern = "GetOutputChannels";
   }
   
   else if (strcmp(regex_name, "GetUpnpMediaRenderers") == 0) {
      pattern = "GetUpnpMediaRenderers";
   }
   
   else if (strcmp(regex_name, "GetAsio4AllChannels") == 0) {
      pattern = "GetAsio4AllChannels";
   }
   
   else if (strcmp(regex_name, "GetDevices") == 0) {
      pattern = "GetDevices";
   }
   
   else if (strcmp(regex_name, "GetDeviceDetails") == 0) {
      pattern = "GetDeviceDetails";
   }
   
   else if (strcmp(regex_name, "GetExternalStorages") == 0) {
      pattern = "GetExternalStorages";
   }
   
   else if (strcmp(regex_name, "BackupUserPlaylists") == 0) {
      pattern = "BackupUserPlaylists";
   }
   
   else if (strcmp(regex_name, "RestoreUserPlaylists") == 0) {
      pattern = "RestoreUserPlaylists";
   }
   
   else if (strcmp(regex_name, "SetNetworkBackup") == 0) {
      pattern = "SetNetworkBackup";
   }
   
   else if (strcmp(regex_name, "GetNetworkBackup") == 0) {
      pattern = "GetNetworkBackup";
   }
   
   else if (strcmp(regex_name, "GetDriveDetail") == 0) {
      pattern = "GetDriveDetail";
   }
   
   else if (strcmp(regex_name, "GetFileSystemDriveDetail") == 0) {
      pattern = "GetFileSystemDriveDetail";
   }
   
   else if (strcmp(regex_name, "AddNewDrive") == 0) {
      pattern = "AddNewDrive";
   }
   
   else if (strcmp(regex_name, "UpdateDrive") == 0) {
      pattern = "UpdateDrive";
   }
   
   else if (strcmp(regex_name, "DeleteDrive") == 0) {
      pattern = "DeleteDrive";
   }
   
   else if (strcmp(regex_name, "DeleteRoom") == 0) {
      pattern = "DeleteRoom";
   }
   
   else if (strcmp(regex_name, "DeleteLinkedRoom") == 0) {
      pattern = "DeleteLinkedRoom";
   }
   
   else if (strcmp(regex_name, "GetSingleSystemSetting") == 0) {
      pattern = "GetSingleSystemSetting";
   }
   
   else if (strcmp(regex_name, "GetSingleRipEncSetting") == 0) {
      pattern = "GetSingleRipEncSetting";
   }
   
   else if (strcmp(regex_name, "UpdateSingleRipEncSetting") == 0) {
      pattern = "UpdateSingleRipEncSetting";
   }
   
   else if (strcmp(regex_name, "UpdateSingleSystemSetting") == 0) {
      pattern = "UpdateSingleSystemSetting";
   }
   
   else if (strcmp(regex_name, "GetRoomDetail") == 0) {
      pattern = "GetRoomDetail";
   }
   
   else if (strcmp(regex_name, "GetLinkedRoomDetail") == 0) {
      pattern = "GetLinkedRoomDetail";
   }
   
   else if (strcmp(regex_name, "AddNewLinkedRoom") == 0) {
      pattern = "AddNewLinkedRoom";
   }
   
   else if (strcmp(regex_name, "UpdateLinkedRoom") == 0) {
      pattern = "UpdateLinkedRoom";
   }
   
   else if (strcmp(regex_name, "AddNewRoom") == 0) {
      pattern = "AddNewRoom";
   }
   
   else if (strcmp(regex_name, "UpdateRoom") == 0) {
      pattern = "UpdateRoom";
   }
   
   else if (strcmp(regex_name, "GetGenreDetail") == 0) {
      pattern = "GetGenreDetail";
   }
   
   else if (strcmp(regex_name, "AddNewGenre") == 0) {
      pattern = "AddNewGenre";
   }
   
   else if (strcmp(regex_name, "UpdateGenre") == 0) {
      pattern = "UpdateGenre";
   }
   
   else if (strcmp(regex_name, "DeleteGenre") == 0) {
      pattern = "DeleteGenre";
   }
   
   else if (strcmp(regex_name, "GetSubGenreDetail") == 0) {
      pattern = "GetSubGenreDetail";
   }
   
   else if (strcmp(regex_name, "AddNewSubGenre") == 0) {
      pattern = "AddNewSubGenre";
   }
   
   else if (strcmp(regex_name, "UpdateSubGenre") == 0) {
      pattern = "UpdateSubGenre";
   }
   
   else if (strcmp(regex_name, "DeleteSubGenre") == 0) {
      pattern = "DeleteSubGenre";
   }
   
   else if (strcmp(regex_name, "CompactGenreOrdinals") == 0) {
      pattern = "CompactGenreOrdinals";
   }
   
   else if (strcmp(regex_name, "TestRows") == 0) {
      pattern = "TestRows";
   }
   
   else if (strcmp(regex_name, "SavePlayerInstance") == 0) {
      pattern = "SavePlayerInstance";
   }
   
   else if (strcmp(regex_name, "RemovePlayerInstance") == 0) {
      pattern = "RemovePlayerInstance";
   }
   
   else if (strcmp(regex_name, "DisconnectDevice") == 0) {
      pattern = "DisconnectDevice";
   }
   
   else if (strcmp(regex_name, "DeviceChecksum") == 0) {
      pattern = "DeviceChecksum";
   }
   
   else if (strcmp(regex_name, "DeleteDevice") == 0) {
      pattern = "DeleteDevice";
   }
   
   else if (strcmp(regex_name, "ToggleDeviceSync") == 0) {
      pattern = "ToggleDeviceSync";
   }
   
   else if (strcmp(regex_name, "IgnoreExternalStorage") == 0) {
      pattern = "IgnoreExternalStorage";
   }
   
   else if (strcmp(regex_name, "ExternalStorageCancelScan") == 0) {
      pattern = "ExternalStorageCancelScan";
   }
   
   else if (strcmp(regex_name, "ActivateExternalStorage") == 0) {
      pattern = "ActivateExternalStorage";
   }
   
   else if (strcmp(regex_name, "AddExternalStorage") == 0) {
      pattern = "AddExternalStorage";
   }
   
   else if (strcmp(regex_name, "ScanForExternalStorages") == 0) {
      pattern = "ScanForExternalStorages";
   }
   
   else if (strcmp(regex_name, "RescanExternalStorages") == 0) {
      pattern = "RescanExternalStorages";
   }
   
   else if (strcmp(regex_name, "ScanExternalStorage") == 0) {
      pattern = "ScanExternalStorage";
   }
   
   else if (strcmp(regex_name, "RemoveExternalStorage") == 0) {
      pattern = "RemoveExternalStorage";
   }
   
   else if (strcmp(regex_name, "GetExternalStorageDetail") == 0) {
      pattern = "GetExternalStorageDetail";
   }
   
   else if (strcmp(regex_name, "UpdateExternalStorage") == 0) {
      pattern = "UpdateExternalStorage";
   }
   
   else if (strcmp(regex_name, "NewOutputChannel") == 0) {
      pattern = "NewOutputChannel";
   }
   
   else if (strcmp(regex_name, "UpdateOutputChannel") == 0) {
      pattern = "UpdateOutputChannel";
   }
   
   else if (strcmp(regex_name, "DeleteOutputChannel") == 0) {
      pattern = "DeleteOutputChannel";
   }
   
   else if (strcmp(regex_name, "SetDriveUsage") == 0) {
      pattern = "SetDriveUsage";
   }
   
   else if (strcmp(regex_name, "BackupDrive") == 0) {
      pattern = "BackupDrive";
   }
   
   else if (strcmp(regex_name, "StopBackupDrive") == 0) {
      pattern = "StopBackupDrive";
   }
   
   else if (strcmp(regex_name, "GetBackupStatus") == 0) {
      pattern = "GetBackupStatus";
   }
   
   else if (strcmp(regex_name, "AddNewBackupJob") == 0) {
      pattern = "AddNewBackupJob";
   }
   
   else if (strcmp(regex_name, "UpdateBackupJob") == 0) {
      pattern = "UpdateBackupJob";
   }
   
   else if (strcmp(regex_name, "DeleteBackupJob") == 0) {
      pattern = "DeleteBackupJob";
   }
   
   else if (strcmp(regex_name, "GetBackupJobs") == 0) {
      pattern = "GetBackupJobs";
   }
   
   else if (strcmp(regex_name, "GetBackupJobDetail") == 0) {
      pattern = "GetBackupJobDetail";
   }
   
   else if (strcmp(regex_name, "GetBackupLogs") == 0) {
      pattern = "GetBackupLogs";
   }
   
   else if (strcmp(regex_name, "GetBackupLogDetail") == 0) {
      pattern = "GetBackupLogDetail";
   }
   
   else if (strcmp(regex_name, "ChangeNetworkDhcp") == 0) {
      pattern = "ChangeNetworkDhcp";
   }
   
   else if (strcmp(regex_name, "ChangeNetworkStatic") == 0) {
      pattern = "ChangeNetworkStatic";
   }
   
   else if (strcmp(regex_name, "ChangeNetworkAutoIP") == 0) {
      pattern = "ChangeNetworkAutoIP";
   }
   
   else if (strcmp(regex_name, "ChangeNetworkWorkgroup") == 0) {
      pattern = "ChangeNetworkWorkgroup";
   }
   
   else if (strcmp(regex_name, "ChangeNetworkMachineName") == 0) {
      pattern = "ChangeNetworkMachineName";
   }
   
   else if (strcmp(regex_name, "ChangeSystemSerialNumber") == 0) {
      pattern = "ChangeSystemSerialNumber";
   }
   
   else if (strcmp(regex_name, "ProcessEmbeddedInit") == 0) {
      pattern = "ProcessEmbeddedInit";
   }
   
   else if (strcmp(regex_name, "GetNetworkActiveAdapters") == 0) {
      pattern = "GetNetworkActiveAdapters";
   }
   
   else if (strcmp(regex_name, "GetNetworkWorkgroup") == 0) {
      pattern = "GetNetworkWorkgroup";
   }
   
   else if (strcmp(regex_name, "ComplexSearchGetAlbums") == 0) {
      pattern = "ComplexSearchGetAlbums";
   }
   
   else if (strcmp(regex_name, "ComplexSearchCountAlbums") == 0) {
      pattern = "ComplexSearchCountAlbums";
   }
   
   else if (strcmp(regex_name, "ComplexSearchGetTracks") == 0) {
      pattern = "ComplexSearchGetTracks";
   }
   
   else if (strcmp(regex_name, "ComplexSearchCountTracks") == 0) {
      pattern = "ComplexSearchCountTracks";
   }
   
   else if (strcmp(regex_name, "ComplexSearchGetArtists") == 0) {
      pattern = "ComplexSearchGetArtists";
   }
   
   else if (strcmp(regex_name, "ComplexSearchCountArtists") == 0) {
      pattern = "ComplexSearchCountArtists";
   }
   
   else if (strcmp(regex_name, "ComplexSearchGetContributors") == 0) {
      pattern = "ComplexSearchGetContributors";
   }
   
   else if (strcmp(regex_name, "ComplexSearchCountContributors") == 0) {
      pattern = "ComplexSearchCountContributors";
   }
   
   else if (strcmp(regex_name, "GetAlbums") == 0) {
      pattern = "GetAlbums";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForStore") == 0) {
      pattern = "GetAlbumsForStore";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtists") == 0) {
      pattern = "GetAlbumsForArtists";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsInSubGenre") == 0) {
      pattern = "GetAlbumsForArtistsInSubGenre";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsInSubGenreForDevice") == 0) {
      pattern = "GetAlbumsForArtistsInSubGenreForDevice";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsInSubGenreForServer") == 0) {
      pattern = "GetAlbumsForArtistsInSubGenreForServer";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsInSubGenreForShare") == 0) {
      pattern = "GetAlbumsForArtistsInSubGenreForShare";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsInGenre") == 0) {
      pattern = "GetAlbumsForArtistsInGenre";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsForDevice") == 0) {
      pattern = "GetAlbumsForArtistsForDevice";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsForShare") == 0) {
      pattern = "GetAlbumsForArtistsForShare";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsForServer") == 0) {
      pattern = "GetAlbumsForArtistsForServer";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForDevice") == 0) {
      pattern = "GetAlbumsForDevice";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForShare") == 0) {
      pattern = "GetAlbumsForShare";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForServer") == 0) {
      pattern = "GetAlbumsForServer";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForPlaylist") == 0) {
      pattern = "GetAlbumsForPlaylist";
   }
   
   else if (strcmp(regex_name, "GetAlbumsSearchAlbumArtist") == 0) {
      pattern = "GetAlbumsSearchAlbumArtist";
   }
   
   else if (strcmp(regex_name, "GetLatestPlayedAlbums") == 0) {
      pattern = "GetLatestPlayedAlbums";
   }
   
   else if (strcmp(regex_name, "GetNewestAlbums") == 0) {
      pattern = "GetNewestAlbums";
   }
   
   else if (strcmp(regex_name, "GetPlayListsByLetter") == 0) {
      pattern = "GetPlayListsByLetter";
   }
   
   else if (strcmp(regex_name, "GetPlaylistsForGenre") == 0) {
      pattern = "GetPlaylistsForGenre";
   }
   
   else if (strcmp(regex_name, "GetPlaylistsForSubGenre") == 0) {
      pattern = "GetPlaylistsForSubGenre";
   }
   
   else if (strcmp(regex_name, "GetPlaylistsForSubGenreForDevice") == 0) {
      pattern = "GetPlaylistsForSubGenreForDevice";
   }
   
   else if (strcmp(regex_name, "GetPlaylistsForSubGenreForShare") == 0) {
      pattern = "GetPlaylistsForSubGenreForShare";
   }
   
   else if (strcmp(regex_name, "GetPlaylistsForSubGenreForServer") == 0) {
      pattern = "GetPlaylistsForSubGenreForServer";
   }
   
   else if (strcmp(regex_name, "GetUserPlaylistsForDevice") == 0) {
      pattern = "GetUserPlaylistsForDevice";
   }
   
   else if (strcmp(regex_name, "GetUserPlaylistsForShare") == 0) {
      pattern = "GetUserPlaylistsForShare";
   }
   
   else if (strcmp(regex_name, "GetUserPlaylistsForServer") == 0) {
      pattern = "GetUserPlaylistsForServer";
   }
   
   else if (strcmp(regex_name, "GetUserPlaylists") == 0) {
      pattern = "GetUserPlaylists";
   }
   
   else if (strcmp(regex_name, "GetTopPlayedAlbums") == 0) {
      pattern = "GetTopPlayedAlbums";
   }
   
   else if (strcmp(regex_name, "GetAlbumsOtherInfo") == 0) {
      pattern = "GetAlbumsOtherInfo";
   }
   
   else if (strcmp(regex_name, "GetAlbumsOtherInfoForServer") == 0) {
      pattern = "GetAlbumsOtherInfoForServer";
   }
   
   else if (strcmp(regex_name, "GetAlbumsOtherInfoForDevice") == 0) {
      pattern = "GetAlbumsOtherInfoForDevice";
   }
   
   else if (strcmp(regex_name, "GetAlbumsOtherInfoForShare") == 0) {
      pattern = "GetAlbumsOtherInfoForShare";
   }
   
   else if (strcmp(regex_name, "GetAlbumsOtherInfoAll") == 0) {
      pattern = "GetAlbumsOtherInfoAll";
   }
   
   else if (strcmp(regex_name, "GetAlbumDetails") == 0) {
      pattern = "GetAlbumDetails";
   }
   
   else if (strcmp(regex_name, "GetTracksAll") == 0) {
      pattern = "GetTracksAll";
   }
   
   else if (strcmp(regex_name, "GetTrackRange") == 0) {
      pattern = "GetTrackRange";
   }
   
   else if (strcmp(regex_name, "GetTracksForArtist") == 0) {
      pattern = "GetTracksForArtist";
   }
   
   else if (strcmp(regex_name, "GetTracksForDevice") == 0) {
      pattern = "GetTracksForDevice";
   }
   
   else if (strcmp(regex_name, "GetTracksForShare") == 0) {
      pattern = "GetTracksForShare";
   }
   
   else if (strcmp(regex_name, "GetTracksForServer") == 0) {
      pattern = "GetTracksForServer";
   }
   
   else if (strcmp(regex_name, "GetTracksForGenre") == 0) {
      pattern = "GetTracksForGenre";
   }
   
   else if (strcmp(regex_name, "GetTracksForPlaylist") == 0) {
      pattern = "GetTracksForPlaylist";
   }
   
   else if (strcmp(regex_name, "GetTracksForSubGenre") == 0) {
      pattern = "GetTracksForSubGenre";
   }
   
   else if (strcmp(regex_name, "GetTracksOtherInfo") == 0) {
      pattern = "GetTracksOtherInfo";
   }
   
   else if (strcmp(regex_name, "GetTracksSearchName") == 0) {
      pattern = "GetTracksSearchName";
   }
   
   else if (strcmp(regex_name, "AdvancedSearch") == 0) {
      pattern = "AdvancedSearch";
   }
   
   else if (strcmp(regex_name, "GetTracksForNamedEntity") == 0) {
      pattern = "GetTracksForNamedEntity";
   }
   
   else if (strcmp(regex_name, "GetTracksForAlbumInUPL") == 0) {
      pattern = "GetTracksForAlbumInUPL";
   }
   
   else if (strcmp(regex_name, "GetArtistDetails") == 0) {
      pattern = "GetArtistDetails";
   }
   
   else if (strcmp(regex_name, "GetArtists") == 0) {
      pattern = "GetArtists";
   }
   
   else if (strcmp(regex_name, "GetArtistsInGenre") == 0) {
      pattern = "GetArtistsInGenre";
   }
   
   else if (strcmp(regex_name, "GetArtistsInSubGenre") == 0) {
      pattern = "GetArtistsInSubGenre";
   }
   
   else if (strcmp(regex_name, "GetArtistsInSubGenreForDevice") == 0) {
      pattern = "GetArtistsInSubGenreForDevice";
   }
   
   else if (strcmp(regex_name, "GetArtistsInSubGenreForServer") == 0) {
      pattern = "GetArtistsInSubGenreForServer";
   }
   
   else if (strcmp(regex_name, "GetArtistsInSubGenreForShare") == 0) {
      pattern = "GetArtistsInSubGenreForShare";
   }
   
   else if (strcmp(regex_name, "GetArtistsForDevice") == 0) {
      pattern = "GetArtistsForDevice";
   }
   
   else if (strcmp(regex_name, "GetArtistsForShare") == 0) {
      pattern = "GetArtistsForShare";
   }
   
   else if (strcmp(regex_name, "GetArtistsForServer") == 0) {
      pattern = "GetArtistsForServer";
   }
   
   else if (strcmp(regex_name, "GetGenres") == 0) {
      pattern = "GetGenres";
   }
   
   else if (strcmp(regex_name, "GetSubGenresForGenre") == 0) {
      pattern = "GetSubGenresForGenre";
   }
   
   else if (strcmp(regex_name, "GetGenresSubGenres") == 0) {
      pattern = "GetGenresSubGenres";
   }
   
   else if (strcmp(regex_name, "GetSubGenresForDevice") == 0) {
      pattern = "GetSubGenresForDevice";
   }
   
   else if (strcmp(regex_name, "GetSubGenresForShare") == 0) {
      pattern = "GetSubGenresForShare";
   }
   
   else if (strcmp(regex_name, "GetSubGenresForServer") == 0) {
      pattern = "GetSubGenresForServer";
   }
   
   else if (strcmp(regex_name, "GetCDDBGenres") == 0) {
      pattern = "GetCDDBGenres";
   }
   
   else if (strcmp(regex_name, "SaveCurrentPlayList") == 0) {
      pattern = "SaveCurrentPlayList";
   }
   
   else if (strcmp(regex_name, "CreateRandomPlaylistEx") == 0) {
      pattern = "CreateRandomPlaylistEx";
   }
   
   else if (strcmp(regex_name, "CreateRandomPlaylist") == 0) {
      pattern = "CreateRandomPlaylist";
   }
   
   else if (strcmp(regex_name, "CreatePlaylist") == 0) {
      pattern = "CreatePlaylist";
   }
   
   else if (strcmp(regex_name, "RenamePlaylist") == 0) {
      pattern = "RenamePlaylist";
   }
   
   else if (strcmp(regex_name, "AddTracksToUserPlaylist") == 0) {
      pattern = "AddTracksToUserPlaylist";
   }
   
   else if (strcmp(regex_name, "AddAlbumsToUserPlaylist") == 0) {
      pattern = "AddAlbumsToUserPlaylist";
   }
   
   else if (strcmp(regex_name, "RemoveAlbumsFromUserPlaylist") == 0) {
      pattern = "RemoveAlbumsFromUserPlaylist";
   }
   
   else if (strcmp(regex_name, "DeleteTrack") == 0) {
      pattern = "DeleteTrack";
   }
   
   else if (strcmp(regex_name, "ChangeTrackOrdinal") == 0) {
      pattern = "ChangeTrackOrdinal";
   }
   
   else if (strcmp(regex_name, "UpdatePlaylist") == 0) {
      pattern = "UpdatePlaylist";
   }
   
   else if (strcmp(regex_name, "DeleteAlbum") == 0) {
      pattern = "DeleteAlbum";
   }
   
   else if (strcmp(regex_name, "RenameAlbum") == 0) {
      pattern = "RenameAlbum";
   }
   
   else if (strcmp(regex_name, "SetAlbumLowQuality") == 0) {
      pattern = "SetAlbumLowQuality";
   }
   
   else if (strcmp(regex_name, "RenameTrack") == 0) {
      pattern = "RenameTrack";
   }
   
   else if (strcmp(regex_name, "UndoUserEdits") == 0) {
      pattern = "UndoUserEdits";
   }
   
   else if (strcmp(regex_name, "RenameArtist") == 0) {
      pattern = "RenameArtist";
   }
   
   else if (strcmp(regex_name, "ChangeAlbumSubGenre") == 0) {
      pattern = "ChangeAlbumSubGenre";
   }
   
   else if (strcmp(regex_name, "UpdateHitCount") == 0) {
      pattern = "UpdateHitCount";
   }
   
   else if (strcmp(regex_name, "CountAlbums") == 0) {
      pattern = "CountAlbums";
   }
   
   else if (strcmp(regex_name, "CountAlbumsForArtist") == 0) {
      pattern = "CountAlbumsForArtist";
   }
   
   else if (strcmp(regex_name, "CountArtists") == 0) {
      pattern = "CountArtists";
   }
   
   else if (strcmp(regex_name, "CountGenres") == 0) {
      pattern = "CountGenres";
   }
   
   else if (strcmp(regex_name, "CountPlaylistsForSubGenre") == 0) {
      pattern = "CountPlaylistsForSubGenre";
   }
   
   else if (strcmp(regex_name, "CountSubGenresForGenre") == 0) {
      pattern = "CountSubGenresForGenre";
   }
   
   else if (strcmp(regex_name, "CountTracksAll") == 0) {
      pattern = "CountTracksAll";
   }
   
   else if (strcmp(regex_name, "CountTracksForPlaylist") == 0) {
      pattern = "CountTracksForPlaylist";
   }
   
   else if (strcmp(regex_name, "CountUserPlaylists") == 0) {
      pattern = "CountUserPlaylists";
   }
   
   else if (strcmp(regex_name, "CountDevices") == 0) {
      pattern = "CountDevices";
   }
   
   else if (strcmp(regex_name, "CountAlbumsForDevice") == 0) {
      pattern = "CountAlbumsForDevice";
   }
   
   else if (strcmp(regex_name, "CountArtistsForDevice") == 0) {
      pattern = "CountArtistsForDevice";
   }
   
   else if (strcmp(regex_name, "CountSubGenresForDevice") == 0) {
      pattern = "CountSubGenresForDevice";
   }
   
   else if (strcmp(regex_name, "CountTracksForDevice") == 0) {
      pattern = "CountTracksForDevice";
   }
   
   else if (strcmp(regex_name, "CountUserPlaylistsForDevice") == 0) {
      pattern = "CountUserPlaylistsForDevice";
   }
   
   else if (strcmp(regex_name, "CountShares") == 0) {
      pattern = "CountShares";
   }
   
   else if (strcmp(regex_name, "CountAlbumsForShare") == 0) {
      pattern = "CountAlbumsForShare";
   }
   
   else if (strcmp(regex_name, "CountArtistsForShare") == 0) {
      pattern = "CountArtistsForShare";
   }
   
   else if (strcmp(regex_name, "CountSubGenresForShare") == 0) {
      pattern = "CountSubGenresForShare";
   }
   
   else if (strcmp(regex_name, "CountTracksForShare") == 0) {
      pattern = "CountTracksForShare";
   }
   
   else if (strcmp(regex_name, "CountUserPlaylistsForShare") == 0) {
      pattern = "CountUserPlaylistsForShare";
   }
   
   else if (strcmp(regex_name, "CountAlbumsForServer") == 0) {
      pattern = "CountAlbumsForServer";
   }
   
   else if (strcmp(regex_name, "CountArtistsForServer") == 0) {
      pattern = "CountArtistsForServer";
   }
   
   else if (strcmp(regex_name, "CountSubGenresForServer") == 0) {
      pattern = "CountSubGenresForServer";
   }
   
   else if (strcmp(regex_name, "CountTracksForServer") == 0) {
      pattern = "CountTracksForServer";
   }
   
   else if (strcmp(regex_name, "CountUserPlaylistsForServer") == 0) {
      pattern = "CountUserPlaylistsForServer";
   }
   
   else if (strcmp(regex_name, "CountAlbumsForArtistForServer") == 0) {
      pattern = "CountAlbumsForArtistForServer";
   }
   
   else if (strcmp(regex_name, "CountAlbumsForArtistForDevice") == 0) {
      pattern = "CountAlbumsForArtistForDevice";
   }
   
   else if (strcmp(regex_name, "CountAlbumsForArtistForShare") == 0) {
      pattern = "CountAlbumsForArtistForShare";
   }
   
   else if (strcmp(regex_name, "CountPlaylistsForSubGenreForServer") == 0) {
      pattern = "CountPlaylistsForSubGenreForServer";
   }
   
   else if (strcmp(regex_name, "CountPlaylistsForSubGenreForDevice") == 0) {
      pattern = "CountPlaylistsForSubGenreForDevice";
   }
   
   else if (strcmp(regex_name, "CountPlaylistsForSubGenreForShare") == 0) {
      pattern = "CountPlaylistsForSubGenreForShare";
   }
   
   else if (strcmp(regex_name, "GetTracksForArtistForServer") == 0) {
      pattern = "GetTracksForArtistForServer";
   }
   
   else if (strcmp(regex_name, "GetTracksForArtistForDevice") == 0) {
      pattern = "GetTracksForArtistForDevice";
   }
   
   else if (strcmp(regex_name, "GetTracksForArtistForShare") == 0) {
      pattern = "GetTracksForArtistForShare";
   }
   
   else if (strcmp(regex_name, "GetTracksForSubGenreForServer") == 0) {
      pattern = "GetTracksForSubGenreForServer";
   }
   
   else if (strcmp(regex_name, "GetTracksForSubGenreForDevice") == 0) {
      pattern = "GetTracksForSubGenreForDevice";
   }
   
   else if (strcmp(regex_name, "GetTracksForSubGenreForShare") == 0) {
      pattern = "GetTracksForSubGenreForShare";
   }
   
   else if (strcmp(regex_name, "GetAlbumsWithAlbumLookupMessages") == 0) {
      pattern = "GetAlbumsWithAlbumLookupMessages";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForDeletion") == 0) {
      pattern = "GetAlbumsForDeletion";
   }
   
   else if (strcmp(regex_name, "GetTracksForDeletion") == 0) {
      pattern = "GetTracksForDeletion";
   }
   
   else if (strcmp(regex_name, "RestoreSingleAlbum") == 0) {
      pattern = "RestoreSingleAlbum";
   }
   
   else if (strcmp(regex_name, "RestoreSingleTrack") == 0) {
      pattern = "RestoreSingleTrack";
   }
   
   else if (strcmp(regex_name, "SetCoverImage") == 0) {
      pattern = "SetCoverImage";
   }
   
   else if (strcmp(regex_name, "RemoveCoverImage") == 0) {
      pattern = "RemoveCoverImage";
   }
   
   else if (strcmp(regex_name, "CheckCoverImage") == 0) {
      pattern = "CheckCoverImage";
   }
   
   else if (strcmp(regex_name, "ForceGenrePlaylistBackup") == 0) {
      pattern = "ForceGenrePlaylistBackup";
   }
   
   else if (strcmp(regex_name, "ForceGenrePlaylistRestore") == 0) {
      pattern = "ForceGenrePlaylistRestore";
   }
   
   else if (strcmp(regex_name, "BulkCDLookup") == 0) {
      pattern = "BulkCDLookup";
   }
   
   else if (strcmp(regex_name, "BulkCDLookupEx") == 0) {
      pattern = "BulkCDLookupEx";
   }
   
   else if (strcmp(regex_name, "CDLookupGetStatus") == 0) {
      pattern = "CDLookupGetStatus";
   }
   
   else if (strcmp(regex_name, "CDLookupGetQueue") == 0) {
      pattern = "CDLookupGetQueue";
   }
   
   else if (strcmp(regex_name, "UploadMessages") == 0) {
      pattern = "UploadMessages";
   }
   
   else if (strcmp(regex_name, "GetComponentVersions") == 0) {
      pattern = "GetComponentVersions";
   }
   
   else if (strcmp(regex_name, "GetOperationActivity") == 0) {
      pattern = "GetOperationActivity";
   }
   
   else if (strcmp(regex_name, "RequestAlbumCover") == 0) {
      pattern = "RequestAlbumCover";
   }
   
   else if (strcmp(regex_name, "RGetTrackPosition") == 0) {
      pattern = "RGetTrackPosition";
   }
   
   else if (strcmp(regex_name, "RGetTrackName") == 0) {
      pattern = "RGetTrackName";
   }
   
   else if (strcmp(regex_name, "RGetAlbumArtist") == 0) {
      pattern = "RGetAlbumArtist";
   }
   
   else if (strcmp(regex_name, "RGetPlayerStatus") == 0) {
      pattern = "RGetPlayerStatus";
   }
   
   else if (strcmp(regex_name, "RGetRepeat") == 0) {
      pattern = "RGetRepeat";
   }
   
   else if (strcmp(regex_name, "RGetShuffle") == 0) {
      pattern = "RGetShuffle";
   }
   
   else if (strcmp(regex_name, "RGetPlayingCheckSum") == 0) {
      pattern = "RGetPlayingCheckSum";
   }
   
   else if (strcmp(regex_name, "RGetDetailedTrackInfo") == 0) {
      pattern = "RGetDetailedTrackInfo";
   }
   
   else if (strcmp(regex_name, "RGetLastPlayerError") == 0) {
      pattern = "RGetLastPlayerError";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumCredits") == 0) {
      pattern = "GetExtAlbumCredits";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsByContributor") == 0) {
      pattern = "GetExtAlbumsByContributor";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsByContributorForDevice") == 0) {
      pattern = "GetExtAlbumsByContributorForDevice";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsByContributorForShare") == 0) {
      pattern = "GetExtAlbumsByContributorForShare";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsByContributorForServer") == 0) {
      pattern = "GetExtAlbumsByContributorForServer";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsByCredit") == 0) {
      pattern = "GetExtAlbumsByCredit";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsByWork") == 0) {
      pattern = "GetExtAlbumsByWork";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsInfo") == 0) {
      pattern = "GetExtAlbumsInfo";
   }
   
   else if (strcmp(regex_name, "GetExtContributors") == 0) {
      pattern = "GetExtContributors";
   }
   
   else if (strcmp(regex_name, "GetExtContributorsForAlbum") == 0) {
      pattern = "GetExtContributorsForAlbum";
   }
   
   else if (strcmp(regex_name, "GetExtContributorsForDevice") == 0) {
      pattern = "GetExtContributorsForDevice";
   }
   
   else if (strcmp(regex_name, "GetExtContributorsForShare") == 0) {
      pattern = "GetExtContributorsForShare";
   }
   
   else if (strcmp(regex_name, "GetExtContributorsForServer") == 0) {
      pattern = "GetExtContributorsForServer";
   }
   
   else if (strcmp(regex_name, "GetExtTrackContributors") == 0) {
      pattern = "GetExtTrackContributors";
   }
   
   else if (strcmp(regex_name, "GetExtTracksByContributor") == 0) {
      pattern = "GetExtTracksByContributor";
   }
   
   else if (strcmp(regex_name, "GetExtTracksByWork") == 0) {
      pattern = "GetExtTracksByWork";
   }
   
   else if (strcmp(regex_name, "GetExtTracksInfo") == 0) {
      pattern = "GetExtTracksInfo";
   }
   
   else if (strcmp(regex_name, "GetExtWorks") == 0) {
      pattern = "GetExtWorks";
   }
   
   else if (strcmp(regex_name, "GetExtContributorDetails") == 0) {
      pattern = "GetExtContributorDetails";
   }
   
   else if (strcmp(regex_name, "GetExtCountContributors") == 0) {
      pattern = "GetExtCountContributors";
   }
   
   else if (strcmp(regex_name, "GetExtCountContributorsForDevice") == 0) {
      pattern = "GetExtCountContributorsForDevice";
   }
   
   else if (strcmp(regex_name, "GetExtCountContributorsForShare") == 0) {
      pattern = "GetExtCountContributorsForShare";
   }
   
   else if (strcmp(regex_name, "GetExtCountContributorsForServer") == 0) {
      pattern = "GetExtCountContributorsForServer";
   }
   
   else if (strcmp(regex_name, "GetExtCountAlbumsByContributor") == 0) {
      pattern = "GetExtCountAlbumsByContributor";
   }
   
   else if (strcmp(regex_name, "GetExtCountAlbumsByContributorForServer") == 0) {
      pattern = "GetExtCountAlbumsByContributorForServer";
   }
   
   else if (strcmp(regex_name, "GetExtCountAlbumsByContributorForDevice") == 0) {
      pattern = "GetExtCountAlbumsByContributorForDevice";
   }
   
   else if (strcmp(regex_name, "GetExtCountAlbumsByContributorForShare") == 0) {
      pattern = "GetExtCountAlbumsByContributorForShare";
   }
   
   else if (strcmp(regex_name, "GetExtTracksByContributorForServer") == 0) {
      pattern = "GetExtTracksByContributorForServer";
   }
   
   else if (strcmp(regex_name, "GetExtTracksByContributorForDevice") == 0) {
      pattern = "GetExtTracksByContributorForDevice";
   }
   
   else if (strcmp(regex_name, "GetExtTracksByContributorForShare") == 0) {
      pattern = "GetExtTracksByContributorForShare";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsSearchPeople") == 0) {
      pattern = "GetExtAlbumsSearchPeople";
   }
   
   else if (strcmp(regex_name, "vTunerLookupById") == 0) {
      pattern = "vTunerLookupById";
   }
   
   else if (strcmp(regex_name, "vTunerAddRemoveFavourite") == 0) {
      pattern = "vTunerAddRemoveFavourite";
   }
   
   else if (strcmp(regex_name, "vTunerGetChildNodes") == 0) {
      pattern = "vTunerGetChildNodes";
   }
   
   else if (strcmp(regex_name, "vTunerPlayById") == 0) {
      pattern = "vTunerPlayById";
   }
   
   else if (strcmp(regex_name, "vTunerPlayByIds") == 0) {
      pattern = "vTunerPlayByIds";
   }
   
   else if (strcmp(regex_name, "vTunerGetMostPlayed") == 0) {
      pattern = "vTunerGetMostPlayed";
   }
   
   else if (strcmp(regex_name, "vTunerGetLastPlayed") == 0) {
      pattern = "vTunerGetLastPlayed";
   }
   
   else if (strcmp(regex_name, "vTunerGetRadioStatisticsChecksum") == 0) {
      pattern = "vTunerGetRadioStatisticsChecksum";
   }
   
   else if (strcmp(regex_name, "vTunerSetPresetChannel") == 0) {
      pattern = "vTunerSetPresetChannel";
   }
   
   else if (strcmp(regex_name, "vTunerGetPresetChannels") == 0) {
      pattern = "vTunerGetPresetChannels";
   }
   
   else if (strcmp(regex_name, "vTunerGetNodeFromPlayedUrl") == 0) {
      pattern = "vTunerGetNodeFromPlayedUrl";
   }
   
   else if (strcmp(regex_name, "vTunerCheckAvailability") == 0) {
      pattern = "vTunerCheckAvailability";
   }
   
   else if (strcmp(regex_name, "MoveAlbumToMusicStore") == 0) {
      pattern = "MoveAlbumToMusicStore";
   }
   
   else if (strcmp(regex_name, "PromoteShareToMusicStore") == 0) {
      pattern = "PromoteShareToMusicStore";
   }
   
   else if (strcmp(regex_name, "DemoteMusicStoreToShare") == 0) {
      pattern = "DemoteMusicStoreToShare";
   }
   
   else if (strcmp(regex_name, "RescanMusicStore") == 0) {
      pattern = "RescanMusicStore";
   }
   
   else if (strcmp(regex_name, "SetMusicStorePriority") == 0) {
      pattern = "SetMusicStorePriority";
   }
   
   else if (strcmp(regex_name, "GetStores") == 0) {
      pattern = "GetStores";
   }
   
   else if (strcmp(regex_name, "GetStoreDetail") == 0) {
      pattern = "GetStoreDetail";
   }
   
   else if (strcmp(regex_name, "SetMusicStoreCredentials") == 0) {
      pattern = "SetMusicStoreCredentials";
   }
   
   else if (strcmp(regex_name, "MoveAlbumGetStatus") == 0) {
      pattern = "MoveAlbumGetStatus";
   }
   
   else if (strcmp(regex_name, "MoveAlbumGetQueue") == 0) {
      pattern = "MoveAlbumGetQueue";
   }
   
   else if (strcmp(regex_name, "GetExtContributorsExist") == 0) {
      pattern = "GetExtContributorsExist";
   }
   

   
   else if (strcmp(regex_name, "SetConnOption") == 0) {
      pattern = "SetConnOption";
   }
   
   else if (strcmp(regex_name, "Status") == 0) {
      pattern = "Status";
   }
   
   else if (strcmp(regex_name, "SetLength") == 0) {
      pattern = "SetLength";
   }
   
   else if (strcmp(regex_name, "EnableField") == 0) {
      pattern = "EnableField";
   }
   
   else if (strcmp(regex_name, "DisableField") == 0) {
      pattern = "DisableField";
   }
   
   else if (strcmp(regex_name, "EffFormat") == 0) {
      pattern = "EffFormat";
   }
   
   else if (strcmp(regex_name, "RoomIpChanged") == 0) {
      pattern = "RoomIpChanged";
   }
   
   else if (strcmp(regex_name, "MasterIpChanged") == 0) {
      pattern = "MasterIpChanged";
   }
   
   else if (strcmp(regex_name, "SetRippingStatus") == 0) {
      pattern = "SetRippingStatus";
   }
   
   else if (strcmp(regex_name, "SetCDDetected") == 0) {
      pattern = "SetCDDetected";
   }
   
   else if (strcmp(regex_name, "SetRecycleBinStatus") == 0) {
      pattern = "SetRecycleBinStatus";
   }
   
   else if (strcmp(regex_name, "Stop") == 0) {
      pattern = "Stop";
   }
   
   else if (strcmp(regex_name, "Play") == 0) {
      pattern = "Play";
   }
   
   else if (strcmp(regex_name, "Pause") == 0) {
      pattern = "Pause";
   }
   
   else if (strcmp(regex_name, "ClearPlaylist") == 0) {
      pattern = "ClearPlaylist";
   }
   
   else if (strcmp(regex_name, "FastForward") == 0) {
      pattern = "FastForward";
   }
   
   else if (strcmp(regex_name, "FastRewind") == 0) {
      pattern = "FastRewind";
   }
   
   else if (strcmp(regex_name, "RandomisePlaylist") == 0) {
      pattern = "RandomisePlaylist";
   }
   
   else if (strcmp(regex_name, "SetTrack") == 0) {
      pattern = "SetTrack";
   }
   
   else if (strcmp(regex_name, "SetTrackPosition") == 0) {
      pattern = "SetTrackPosition";
   }
   
   else if (strcmp(regex_name, "EjectCD") == 0) {
      pattern = "EjectCD";
   }
   
   else if (strcmp(regex_name, "SetVolume") == 0) {
      pattern = "SetVolume";
   }
   
   else if (strcmp(regex_name, "SetShuffle") == 0) {
      pattern = "SetShuffle";
   }
   
   else if (strcmp(regex_name, "SetRepeat") == 0) {
      pattern = "SetRepeat";
   }
   
   else if (strcmp(regex_name, "ClearAllPlaying") == 0) {
      pattern = "ClearAllPlaying";
   }
   
   else if (strcmp(regex_name, "RestartDevice") == 0) {
      pattern = "RestartDevice";
   }
   
   else if (strcmp(regex_name, "ChangeCDDBSubGenreAssociation") == 0) {
      pattern = "ChangeCDDBSubGenreAssociation";
   }
   
   else if (strcmp(regex_name, "ForceHostUpgrade") == 0) {
      pattern = "ForceHostUpgrade";
   }
   
   else if (strcmp(regex_name, "ForceDBRebuild") == 0) {
      pattern = "ForceDBRebuild";
   }
   
   else if (strcmp(regex_name, "PurgeImageCache") == 0) {
      pattern = "PurgeImageCache";
   }
   
   else if (strcmp(regex_name, "CDLookupCancel") == 0) {
      pattern = "CDLookupCancel";
   }
   
   else if (strcmp(regex_name, "CdLookupCancelAll") == 0) {
      pattern = "CdLookupCancelAll";
   }
   
   else if (strcmp(regex_name, "EmptyRecycleBin") == 0) {
      pattern = "EmptyRecycleBin";
   }
   
   else if (strcmp(regex_name, "EmptyRipShare") == 0) {
      pattern = "EmptyRipShare";
   }
   
   else if (strcmp(regex_name, "ClearDownloadFolder") == 0) {
      pattern = "ClearDownloadFolder";
   }
   
   else if (strcmp(regex_name, "RGetRegisterClient") == 0) {
      pattern = "RGetRegisterClient";
   }
   
   else if (strcmp(regex_name, "RGetClearCommands") == 0) {
      pattern = "RGetClearCommands";
   }
   
   else if (strcmp(regex_name, "vTunerCleanStatistics") == 0) {
      pattern = "vTunerCleanStatistics";
   }
   
   else if (strcmp(regex_name, "vTunerClearPresetChannel") == 0) {
      pattern = "vTunerClearPresetChannel";
   }
   
   else if (strcmp(regex_name, "MoveAlbumCancel") == 0) {
      pattern = "MoveAlbumCancel";
   }
   
   else if (strcmp(regex_name, "MoveAlbumCancelAll") == 0) {
      pattern = "MoveAlbumCancelAll";
   }
   

   
   else if (strcmp(regex_name, "Status") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "EffFormat") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "FilterSearch") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "SortSearch") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetRooms") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetRoomsWithPlayBack") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetRoomsWithRipping") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetNonLinkedRooms") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetLinkedRooms") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAdvancedStatus") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetUserStatus") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetStatusMessages") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetCurrentPlayList") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetCurrentPlaylistEx") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetRippingAlerts") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlertDetails") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetRippingStatus") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetRipEncSettings") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetRipEncSettingsEx") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetSettings") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetSettingsEx") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAvailableValues") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetSystemDrives") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetEncodingQueue") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetEncodingStatus") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetPlayerInstances") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetOutputDevices") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetOutputChannels") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetUpnpMediaRenderers") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAsio4AllChannels") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetDevices") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetDeviceDetails") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExternalStorages") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetNetworkBackup") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetLinkedRoomDetail") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "TestRows") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetBackupJobs") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetBackupJobDetail") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetBackupLogs") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetBackupLogDetail") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetNetworkActiveAdapters") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "ComplexSearchGetAlbums") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "ComplexSearchGetTracks") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "ComplexSearchGetArtists") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "ComplexSearchGetContributors") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbums") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForStore") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtists") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsInSubGenre") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsInSubGenreForDevice") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsInSubGenreForServer") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsInSubGenreForShare") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsInGenre") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsForDevice") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsForShare") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsForServer") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForDevice") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForShare") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForServer") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForPlaylist") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsSearchAlbumArtist") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetLatestPlayedAlbums") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetNewestAlbums") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetPlayListsByLetter") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetPlaylistsForGenre") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetPlaylistsForSubGenre") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetPlaylistsForSubGenreForDevice") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetPlaylistsForSubGenreForShare") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetPlaylistsForSubGenreForServer") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetUserPlaylistsForDevice") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetUserPlaylistsForShare") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetUserPlaylistsForServer") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetUserPlaylists") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetTopPlayedAlbums") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsOtherInfo") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsOtherInfoForServer") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsOtherInfoForDevice") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsOtherInfoForShare") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsOtherInfoAll") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumDetails") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetTracksAll") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetTrackRange") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetTracksForArtist") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetTracksForDevice") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetTracksForShare") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetTracksForServer") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetTracksForGenre") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetTracksForPlaylist") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetTracksForSubGenre") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetTracksOtherInfo") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetTracksSearchName") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "AdvancedSearch") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetTracksForNamedEntity") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetTracksForAlbumInUPL") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetArtistDetails") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetArtists") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetArtistsInGenre") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetArtistsInSubGenre") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetArtistsInSubGenreForDevice") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetArtistsInSubGenreForServer") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetArtistsInSubGenreForShare") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetArtistsForDevice") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetArtistsForShare") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetArtistsForServer") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetGenres") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetSubGenresForGenre") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetGenresSubGenres") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetSubGenresForDevice") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetSubGenresForShare") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetSubGenresForServer") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetCDDBGenres") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "UndoUserEdits") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetTracksForArtistForServer") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetTracksForArtistForDevice") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetTracksForArtistForShare") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetTracksForSubGenreForServer") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetTracksForSubGenreForDevice") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetTracksForSubGenreForShare") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsWithAlbumLookupMessages") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForDeletion") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetTracksForDeletion") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "BulkCDLookup") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "CDLookupGetQueue") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetComponentVersions") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumCredits") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsByContributor") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsByContributorForDevice") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsByContributorForShare") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsByContributorForServer") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsByCredit") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsByWork") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsInfo") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtContributors") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtContributorsForAlbum") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtContributorsForDevice") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtContributorsForShare") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtContributorsForServer") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtTrackContributors") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtTracksByContributor") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtTracksByWork") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtTracksInfo") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtWorks") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtContributorDetails") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtTracksByContributorForServer") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtTracksByContributorForDevice") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtTracksByContributorForShare") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsSearchPeople") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "vTunerLookupById") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "vTunerGetChildNodes") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "vTunerGetMostPlayed") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "vTunerGetLastPlayed") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "vTunerGetPresetChannels") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "vTunerGetNodeFromPlayedUrl") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetStores") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "GetStoreDetail") == 0) {
      pattern = "Record";
   }
   
   else if (strcmp(regex_name, "MoveAlbumGetQueue") == 0) {
      pattern = "Record";
   }
   

   return pattern;

}
