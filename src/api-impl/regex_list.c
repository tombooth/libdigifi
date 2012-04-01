
/*
 *  regex_list.c
 *  libdigifi.new
 *
 *  Created by Tom Booth on 09/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "../api/regex_list.h"

#include <string.h>

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
      pattern = "GetCurOp[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "ReleaseSerialPort") == 0) {
      pattern = "ReleaseSerialPort[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "Version") == 0) {
      pattern = "Version[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetRows") == 0) {
      pattern = "GetRows[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetCount") == 0) {
      pattern = "GetCount[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetLastError") == 0) {
      pattern = "GetLastError[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "LookupError") == 0) {
      pattern = "LookupError[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "FindAllRooms") == 0) {
      pattern = "FindAllRooms[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "FindNewRooms") == 0) {
      pattern = "FindNewRooms[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "RemoveOldRooms") == 0) {
      pattern = "RemoveOldRooms[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "ServiceMode") == 0) {
      pattern = "ServiceMode[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetSearchOffset") == 0) {
      pattern = "GetSearchOffset[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetSystemTime") == 0) {
      pattern = "GetSystemTime[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetHostDetails") == 0) {
      pattern = "GetHostDetails[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetRecycleBinStatus") == 0) {
      pattern = "GetRecycleBinStatus[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetSetupVal") == 0) {
      pattern = "GetSetupVal[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "NextTrack") == 0) {
      pattern = "NextTrack[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "PrevTrack") == 0) {
      pattern = "PrevTrack[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "RemoveTrack") == 0) {
      pattern = "RemoveTrack[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "PlayAlbums") == 0) {
      pattern = "PlayAlbums[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "PlayAll") == 0) {
      pattern = "PlayAll[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "PlayAlbum") == 0) {
      pattern = "PlayAlbum[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "PlayTrack") == 0) {
      pattern = "PlayTrack[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "PlayTracks") == 0) {
      pattern = "PlayTracks[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "PlayTracksFromSearch") == 0) {
      pattern = "PlayTracksFromSearch[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "PlayAlbumsFromSearch") == 0) {
      pattern = "PlayAlbumsFromSearch[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "PlayUrl") == 0) {
      pattern = "PlayUrl[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "PlayUrls") == 0) {
      pattern = "PlayUrls[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "PlayPlaylist") == 0) {
      pattern = "PlayPlaylist[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "PlayRandom") == 0) {
      pattern = "PlayRandom[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "PlayArtistAlbum") == 0) {
      pattern = "PlayArtistAlbum[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "PlayLastPlayed") == 0) {
      pattern = "PlayLastPlayed[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "PlayLastRipped") == 0) {
      pattern = "PlayLastRipped[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "PlayMostPopular") == 0) {
      pattern = "PlayMostPopular[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "IsCDPlaying") == 0) {
      pattern = "IsCDPlaying[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "GetTrackName") == 0) {
      pattern = "GetTrackName[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetTrackDetailsFromPlayer") == 0) {
      pattern = "GetTrackDetailsFromPlayer[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumArtist") == 0) {
      pattern = "GetAlbumArtist[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetTrackNum") == 0) {
      pattern = "GetTrackNum[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetTrackCount") == 0) {
      pattern = "GetTrackCount[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetShuffle") == 0) {
      pattern = "GetShuffle[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "GetRepeat") == 0) {
      pattern = "GetRepeat[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "GetPlayerStatus") == 0) {
      pattern = "GetPlayerStatus[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetTrackLength") == 0) {
      pattern = "GetTrackLength[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetTrackPosition") == 0) {
      pattern = "GetTrackPosition[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetPlayerVersion") == 0) {
      pattern = "GetPlayerVersion[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetVolume") == 0) {
      pattern = "GetVolume[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "QueryAllPlayback") == 0) {
      pattern = "QueryAllPlayback[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetStatusMessageDetail") == 0) {
      pattern = "GetStatusMessageDetail[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetLibraryCheckSum") == 0) {
      pattern = "GetLibraryCheckSum[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CancelRipping") == 0) {
      pattern = "CancelRipping[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "BackupUserPlaylists") == 0) {
      pattern = "BackupUserPlaylists[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "RestoreUserPlaylists") == 0) {
      pattern = "RestoreUserPlaylists[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "SetNetworkBackup") == 0) {
      pattern = "SetNetworkBackup[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "GetDriveDetail") == 0) {
      pattern = "GetDriveDetail[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetFileSystemDriveDetail") == 0) {
      pattern = "GetFileSystemDriveDetail[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "AddNewDrive") == 0) {
      pattern = "AddNewDrive[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "UpdateDrive") == 0) {
      pattern = "UpdateDrive[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "DeleteDrive") == 0) {
      pattern = "DeleteDrive[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "DeleteRoom") == 0) {
      pattern = "DeleteRoom[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "DeleteLinkedRoom") == 0) {
      pattern = "DeleteLinkedRoom[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "GetSingleSystemSetting") == 0) {
      pattern = "GetSingleSystemSetting[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetSingleRipEncSetting") == 0) {
      pattern = "GetSingleRipEncSetting[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "UpdateSingleRipEncSetting") == 0) {
      pattern = "UpdateSingleRipEncSetting[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "UpdateSingleSystemSetting") == 0) {
      pattern = "UpdateSingleSystemSetting[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "AddNewLinkedRoom") == 0) {
      pattern = "AddNewLinkedRoom[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "UpdateLinkedRoom") == 0) {
      pattern = "UpdateLinkedRoom[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "AddNewRoom") == 0) {
      pattern = "AddNewRoom[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "UpdateRoom") == 0) {
      pattern = "UpdateRoom[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "GetGenreDetail") == 0) {
      pattern = "GetGenreDetail[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "AddNewGenre") == 0) {
      pattern = "AddNewGenre[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "UpdateGenre") == 0) {
      pattern = "UpdateGenre[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "DeleteGenre") == 0) {
      pattern = "DeleteGenre[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "GetSubGenreDetail") == 0) {
      pattern = "GetSubGenreDetail[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "AddNewSubGenre") == 0) {
      pattern = "AddNewSubGenre[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "UpdateSubGenre") == 0) {
      pattern = "UpdateSubGenre[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "DeleteSubGenre") == 0) {
      pattern = "DeleteSubGenre[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "CompactGenreOrdinals") == 0) {
      pattern = "CompactGenreOrdinals[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "SavePlayerInstance") == 0) {
      pattern = "SavePlayerInstance[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "RemovePlayerInstance") == 0) {
      pattern = "RemovePlayerInstance[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "DisconnectDevice") == 0) {
      pattern = "DisconnectDevice[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "DeviceChecksum") == 0) {
      pattern = "DeviceChecksum[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "DeleteDevice") == 0) {
      pattern = "DeleteDevice[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "ToggleDeviceSync") == 0) {
      pattern = "ToggleDeviceSync[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "IgnoreExternalStorage") == 0) {
      pattern = "IgnoreExternalStorage[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "ExternalStorageCancelScan") == 0) {
      pattern = "ExternalStorageCancelScan[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "ActivateExternalStorage") == 0) {
      pattern = "ActivateExternalStorage[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "AddExternalStorage") == 0) {
      pattern = "AddExternalStorage[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "ScanForExternalStorages") == 0) {
      pattern = "ScanForExternalStorages[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "RescanExternalStorages") == 0) {
      pattern = "RescanExternalStorages[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "ScanExternalStorage") == 0) {
      pattern = "ScanExternalStorage[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "RemoveExternalStorage") == 0) {
      pattern = "RemoveExternalStorage[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "GetExternalStorageDetail") == 0) {
      pattern = "GetExternalStorageDetail[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "UpdateExternalStorage") == 0) {
      pattern = "UpdateExternalStorage[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "NewOutputChannel") == 0) {
      pattern = "NewOutputChannel[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "UpdateOutputChannel") == 0) {
      pattern = "UpdateOutputChannel[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "DeleteOutputChannel") == 0) {
      pattern = "DeleteOutputChannel[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "SetDriveUsage") == 0) {
      pattern = "SetDriveUsage[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "BackupDrive") == 0) {
      pattern = "BackupDrive[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "StopBackupDrive") == 0) {
      pattern = "StopBackupDrive[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetBackupStatus") == 0) {
      pattern = "GetBackupStatus[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "AddNewBackupJob") == 0) {
      pattern = "AddNewBackupJob[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "UpdateBackupJob") == 0) {
      pattern = "UpdateBackupJob[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "DeleteBackupJob") == 0) {
      pattern = "DeleteBackupJob[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "ChangeNetworkDhcp") == 0) {
      pattern = "ChangeNetworkDhcp[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "ChangeNetworkStatic") == 0) {
      pattern = "ChangeNetworkStatic[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "ChangeNetworkAutoIP") == 0) {
      pattern = "ChangeNetworkAutoIP[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "ChangeNetworkWorkgroup") == 0) {
      pattern = "ChangeNetworkWorkgroup[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "ChangeNetworkMachineName") == 0) {
      pattern = "ChangeNetworkMachineName[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "ChangeSystemSerialNumber") == 0) {
      pattern = "ChangeSystemSerialNumber[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "ProcessEmbeddedInit") == 0) {
      pattern = "ProcessEmbeddedInit[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetNetworkWorkgroup") == 0) {
      pattern = "GetNetworkWorkgroup[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "ComplexSearchCountAlbums") == 0) {
      pattern = "ComplexSearchCountAlbums[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "ComplexSearchCountTracks") == 0) {
      pattern = "ComplexSearchCountTracks[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "ComplexSearchCountArtists") == 0) {
      pattern = "ComplexSearchCountArtists[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "ComplexSearchCountContributors") == 0) {
      pattern = "ComplexSearchCountContributors[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "SaveCurrentPlayList") == 0) {
      pattern = "SaveCurrentPlayList[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CreateRandomPlaylistEx") == 0) {
      pattern = "CreateRandomPlaylistEx[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CreateRandomPlaylist") == 0) {
      pattern = "CreateRandomPlaylist[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CreatePlaylist") == 0) {
      pattern = "CreatePlaylist[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "RenamePlaylist") == 0) {
      pattern = "RenamePlaylist[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "AddTracksToUserPlaylist") == 0) {
      pattern = "AddTracksToUserPlaylist[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "AddAlbumsToUserPlaylist") == 0) {
      pattern = "AddAlbumsToUserPlaylist[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "RemoveAlbumsFromUserPlaylist") == 0) {
      pattern = "RemoveAlbumsFromUserPlaylist[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "DeleteTrack") == 0) {
      pattern = "DeleteTrack[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "ChangeTrackOrdinal") == 0) {
      pattern = "ChangeTrackOrdinal[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "UpdatePlaylist") == 0) {
      pattern = "UpdatePlaylist[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "DeleteAlbum") == 0) {
      pattern = "DeleteAlbum[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "RenameAlbum") == 0) {
      pattern = "RenameAlbum[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "SetAlbumLowQuality") == 0) {
      pattern = "SetAlbumLowQuality[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "RenameTrack") == 0) {
      pattern = "RenameTrack[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "RenameArtist") == 0) {
      pattern = "RenameArtist[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "ChangeAlbumSubGenre") == 0) {
      pattern = "ChangeAlbumSubGenre[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "UpdateHitCount") == 0) {
      pattern = "UpdateHitCount[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "CountAlbums") == 0) {
      pattern = "CountAlbums[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountAlbumsForArtist") == 0) {
      pattern = "CountAlbumsForArtist[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountArtists") == 0) {
      pattern = "CountArtists[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountGenres") == 0) {
      pattern = "CountGenres[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountPlaylistsForSubGenre") == 0) {
      pattern = "CountPlaylistsForSubGenre[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountSubGenresForGenre") == 0) {
      pattern = "CountSubGenresForGenre[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountTracksAll") == 0) {
      pattern = "CountTracksAll[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountTracksForPlaylist") == 0) {
      pattern = "CountTracksForPlaylist[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountUserPlaylists") == 0) {
      pattern = "CountUserPlaylists[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountDevices") == 0) {
      pattern = "CountDevices[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountAlbumsForDevice") == 0) {
      pattern = "CountAlbumsForDevice[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountArtistsForDevice") == 0) {
      pattern = "CountArtistsForDevice[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountSubGenresForDevice") == 0) {
      pattern = "CountSubGenresForDevice[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountTracksForDevice") == 0) {
      pattern = "CountTracksForDevice[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountUserPlaylistsForDevice") == 0) {
      pattern = "CountUserPlaylistsForDevice[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountShares") == 0) {
      pattern = "CountShares[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountAlbumsForShare") == 0) {
      pattern = "CountAlbumsForShare[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountArtistsForShare") == 0) {
      pattern = "CountArtistsForShare[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountSubGenresForShare") == 0) {
      pattern = "CountSubGenresForShare[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountTracksForShare") == 0) {
      pattern = "CountTracksForShare[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountUserPlaylistsForShare") == 0) {
      pattern = "CountUserPlaylistsForShare[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountAlbumsForServer") == 0) {
      pattern = "CountAlbumsForServer[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountArtistsForServer") == 0) {
      pattern = "CountArtistsForServer[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountSubGenresForServer") == 0) {
      pattern = "CountSubGenresForServer[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountTracksForServer") == 0) {
      pattern = "CountTracksForServer[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountUserPlaylistsForServer") == 0) {
      pattern = "CountUserPlaylistsForServer[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountAlbumsForArtistForServer") == 0) {
      pattern = "CountAlbumsForArtistForServer[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountAlbumsForArtistForDevice") == 0) {
      pattern = "CountAlbumsForArtistForDevice[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountAlbumsForArtistForShare") == 0) {
      pattern = "CountAlbumsForArtistForShare[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountPlaylistsForSubGenreForServer") == 0) {
      pattern = "CountPlaylistsForSubGenreForServer[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountPlaylistsForSubGenreForDevice") == 0) {
      pattern = "CountPlaylistsForSubGenreForDevice[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CountPlaylistsForSubGenreForShare") == 0) {
      pattern = "CountPlaylistsForSubGenreForShare[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "RestoreSingleAlbum") == 0) {
      pattern = "RestoreSingleAlbum[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "RestoreSingleTrack") == 0) {
      pattern = "RestoreSingleTrack[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "SetCoverImage") == 0) {
      pattern = "SetCoverImage[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "RemoveCoverImage") == 0) {
      pattern = "RemoveCoverImage[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "CheckCoverImage") == 0) {
      pattern = "CheckCoverImage[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "ForceGenrePlaylistBackup") == 0) {
      pattern = "ForceGenrePlaylistBackup[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "ForceGenrePlaylistRestore") == 0) {
      pattern = "ForceGenrePlaylistRestore[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "BulkCDLookupEx") == 0) {
      pattern = "BulkCDLookupEx[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "CDLookupGetStatus") == 0) {
      pattern = "CDLookupGetStatus[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "UploadMessages") == 0) {
      pattern = "UploadMessages[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "GetOperationActivity") == 0) {
      pattern = "GetOperationActivity[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "RequestAlbumCover") == 0) {
      pattern = "RequestAlbumCover[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "RGetTrackPosition") == 0) {
      pattern = "RGetTrackPosition[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "RGetTrackName") == 0) {
      pattern = "RGetTrackName[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "RGetAlbumArtist") == 0) {
      pattern = "RGetAlbumArtist[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "RGetPlayerStatus") == 0) {
      pattern = "RGetPlayerStatus[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "RGetRepeat") == 0) {
      pattern = "RGetRepeat[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "RGetShuffle") == 0) {
      pattern = "RGetShuffle[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "RGetPlayingCheckSum") == 0) {
      pattern = "RGetPlayingCheckSum[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "RGetDetailedTrackInfo") == 0) {
      pattern = "RGetDetailedTrackInfo[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "RGetLastPlayerError") == 0) {
      pattern = "RGetLastPlayerError[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetExtCountContributors") == 0) {
      pattern = "GetExtCountContributors[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtCountContributorsForDevice") == 0) {
      pattern = "GetExtCountContributorsForDevice[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtCountContributorsForShare") == 0) {
      pattern = "GetExtCountContributorsForShare[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtCountContributorsForServer") == 0) {
      pattern = "GetExtCountContributorsForServer[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtCountAlbumsByContributor") == 0) {
      pattern = "GetExtCountAlbumsByContributor[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtCountAlbumsByContributorForServer") == 0) {
      pattern = "GetExtCountAlbumsByContributorForServer[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtCountAlbumsByContributorForDevice") == 0) {
      pattern = "GetExtCountAlbumsByContributorForDevice[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtCountAlbumsByContributorForShare") == 0) {
      pattern = "GetExtCountAlbumsByContributorForShare[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "vTunerAddRemoveFavourite") == 0) {
      pattern = "vTunerAddRemoveFavourite[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "vTunerPlayById") == 0) {
      pattern = "vTunerPlayById[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "vTunerPlayByIds") == 0) {
      pattern = "vTunerPlayByIds[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "vTunerGetRadioStatisticsChecksum") == 0) {
      pattern = "vTunerGetRadioStatisticsChecksum[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "vTunerSetPresetChannel") == 0) {
      pattern = "vTunerSetPresetChannel[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "vTunerCheckAvailability") == 0) {
      pattern = "vTunerCheckAvailability[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "MoveAlbumToMusicStore") == 0) {
      pattern = "MoveAlbumToMusicStore[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "PromoteShareToMusicStore") == 0) {
      pattern = "PromoteShareToMusicStore[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "DemoteMusicStoreToShare") == 0) {
      pattern = "DemoteMusicStoreToShare[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "RescanMusicStore") == 0) {
      pattern = "RescanMusicStore[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "SetMusicStorePriority") == 0) {
      pattern = "SetMusicStorePriority[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "SetMusicStoreCredentials") == 0) {
      pattern = "SetMusicStoreCredentials[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "MoveAlbumGetStatus") == 0) {
      pattern = "MoveAlbumGetStatus[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtContributorsExist") == 0) {
      pattern = "GetExtContributorsExist[[:space:]+]\"([0-1])\"";
   }
   

   
   else if (strcmp(regex_name, "SetConnOption") == 0) {
      pattern = "SetConnOption[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "SetLength") == 0) {
      pattern = "SetLength[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "EnableField") == 0) {
      pattern = "EnableField[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "DisableField") == 0) {
      pattern = "DisableField[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "RoomIpChanged") == 0) {
      pattern = "RoomIpChanged";
   }
   
   else if (strcmp(regex_name, "MasterIpChanged") == 0) {
      pattern = "MasterIpChanged[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
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
      pattern = "Stop[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "Play") == 0) {
      pattern = "Play[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "Pause") == 0) {
      pattern = "Pause[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "ClearPlaylist") == 0) {
      pattern = "ClearPlaylist[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "FastForward") == 0) {
      pattern = "FastForward[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "FastRewind") == 0) {
      pattern = "FastRewind[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "RandomisePlaylist") == 0) {
      pattern = "RandomisePlaylist[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "SetTrack") == 0) {
      pattern = "SetTrack[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "SetTrackPosition") == 0) {
      pattern = "SetTrackPosition[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "EjectCD") == 0) {
      pattern = "EjectCD[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "SetVolume") == 0) {
      pattern = "SetVolume[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "SetShuffle") == 0) {
      pattern = "SetShuffle[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "SetRepeat") == 0) {
      pattern = "SetRepeat[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "ClearAllPlaying") == 0) {
      pattern = "ClearAllPlaying";
   }
   
   else if (strcmp(regex_name, "RestartDevice") == 0) {
      pattern = "RestartDevice";
   }
   
   else if (strcmp(regex_name, "ChangeCDDBSubGenreAssociation") == 0) {
      pattern = "ChangeCDDBSubGenreAssociation[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "ForceHostUpgrade") == 0) {
      pattern = "ForceHostUpgrade[[:space:]+]\"(-*[0-9]+)\"";
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
      pattern = "EmptyRipShare[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "ClearDownloadFolder") == 0) {
      pattern = "ClearDownloadFolder[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "RGetRegisterClient") == 0) {
      pattern = "RGetRegisterClient[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "RGetClearCommands") == 0) {
      pattern = "RGetClearCommands[[:space:]+]\"(-*[0-9]+)\"";
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
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "EffFormat") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "FilterSearch") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "SortSearch") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetRooms") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetRoomsWithPlayBack") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetRoomsWithRipping") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetNonLinkedRooms") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetLinkedRooms") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetAdvancedStatus") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetUserStatus") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetStatusMessages") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetCurrentPlayList") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetCurrentPlaylistEx") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "GetRippingAlerts") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetAlertDetails") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetRippingStatus") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetRipEncSettings") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetRipEncSettingsEx") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetSettings") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetSettingsEx") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetAvailableValues") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetSystemDrives") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetEncodingQueue") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetEncodingStatus") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetPlayerInstances") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetOutputDevices") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetOutputChannels") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetUpnpMediaRenderers") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetAsio4AllChannels") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetDevices") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "GetDeviceDetails") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "GetExternalStorages") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetNetworkBackup") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetLinkedRoomDetail") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "TestRows") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetBackupJobs") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetBackupJobDetail") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetBackupLogs") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetBackupLogDetail") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetNetworkActiveAdapters") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "ComplexSearchGetAlbums") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "ComplexSearchGetTracks") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "ComplexSearchGetArtists") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "ComplexSearchGetContributors") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetAlbums") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForStore") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtists") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsInSubGenre") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsInSubGenreForDevice") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsInSubGenreForServer") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsInSubGenreForShare") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsInGenre") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsForDevice") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsForShare") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForArtistsForServer") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForDevice") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForShare") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForServer") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForPlaylist") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsSearchAlbumArtist") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetLatestPlayedAlbums") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetNewestAlbums") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetPlayListsByLetter") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetPlaylistsForGenre") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetPlaylistsForSubGenre") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetPlaylistsForSubGenreForDevice") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetPlaylistsForSubGenreForShare") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetPlaylistsForSubGenreForServer") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetUserPlaylistsForDevice") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetUserPlaylistsForShare") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetUserPlaylistsForServer") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetUserPlaylists") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetTopPlayedAlbums") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsOtherInfo") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsOtherInfoForServer") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsOtherInfoForDevice") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsOtherInfoForShare") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsOtherInfoAll") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumDetails") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetTracksAll") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetTrackRange") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetTracksForArtist") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetTracksForDevice") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetTracksForShare") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetTracksForServer") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetTracksForGenre") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetTracksForPlaylist") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "GetTracksForSubGenre") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetTracksOtherInfo") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "GetTracksSearchName") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "AdvancedSearch") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "GetTracksForNamedEntity") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetTracksForAlbumInUPL") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetArtistDetails") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetArtists") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetArtistsInGenre") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetArtistsInSubGenre") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetArtistsInSubGenreForDevice") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetArtistsInSubGenreForServer") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetArtistsInSubGenreForShare") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetArtistsForDevice") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetArtistsForShare") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetArtistsForServer") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetGenres") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetSubGenresForGenre") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetGenresSubGenres") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetSubGenresForDevice") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetSubGenresForShare") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetSubGenresForServer") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetCDDBGenres") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "UndoUserEdits") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetTracksForArtistForServer") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetTracksForArtistForDevice") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetTracksForArtistForShare") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetTracksForSubGenreForServer") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetTracksForSubGenreForDevice") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetTracksForSubGenreForShare") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsWithAlbumLookupMessages") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetAlbumsForDeletion") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetTracksForDeletion") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"";
   }
   
   else if (strcmp(regex_name, "BulkCDLookup") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "CDLookupGetQueue") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetComponentVersions") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumCredits") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsByContributor") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsByContributorForDevice") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsByContributorForShare") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsByContributorForServer") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsByCredit") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsByWork") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsInfo") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetExtContributors") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtContributorsForAlbum") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtContributorsForDevice") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtContributorsForShare") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtContributorsForServer") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtTrackContributors") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtTracksByContributor") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtTracksByWork") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtTracksInfo") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetExtWorks") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   
   else if (strcmp(regex_name, "GetExtContributorDetails") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtTracksByContributorForServer") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtTracksByContributorForDevice") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtTracksByContributorForShare") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetExtAlbumsSearchPeople") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "vTunerLookupById") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "vTunerGetChildNodes") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "vTunerGetMostPlayed") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "vTunerGetLastPlayed") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "vTunerGetPresetChannels") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "vTunerGetNodeFromPlayedUrl") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetStores") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "GetStoreDetail") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-1])\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"";
   }
   
   else if (strcmp(regex_name, "MoveAlbumGetQueue") == 0) {
      pattern = "Record[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"([0-9]+-[0-9]+-[0-9]+)\"[[:space:]+]\"([0-9]+:[0-9]+:[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(-*[0-9]+)\"[[:space:]+]\"(.*)\"";
   }
   

   return pattern;

}
