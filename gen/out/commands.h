/*
 *  commands.h
 *  libdigifi.new
 *
 *  Created by Tom Booth on 09/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */


#ifndef COMMANDS_H
#define COMMANDS_H

#include "client.h"

typedef struct {
  out_socket *socket;
  int id;
  int count;
  char *name;
  
  void (*callback)(void);
  void *context;
} df_search;

int df_extract_from(df_search *, int start, int end);
void df_free_search(df_search *);

// Generated functions
//



/*!
  Return the name of the current operation
*/
int df_GetCurOp(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Releases any clients connected to Sophia through the serial port. After the serial ports are released Sophia will broadcast the following custom windows message; &quot;SOPHIA HAS ENTERED SERVICE MODE&quot;
*/
int df_ReleaseSerialPort(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the version of the service component and the supported protocol version
*/
int df_Version(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Retrieve a number of rows from a previously executed numbered search
*/
int df_GetRows(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of rows cached from a previously executed numbered search
*/
int df_GetCount(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the error text associated with the last error on this connection
*/
int df_GetLastError(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the error text associated with the supplied error number
*/
int df_LookupError(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Scan the network for DigiFi rooms, and update the internal rooms collection.
*/
int df_FindAllRooms(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Scan the network for DigiFi rooms, and update the internal rooms collection with any new rooms located.
*/
int df_FindNewRooms(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Scan the network for DigiFi rooms, remove from the internal rooms collection any rooms which do not respond.
*/
int df_RemoveOldRooms(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the details of the current mode in which the service is operating (full mode, demo mode etc)
*/
int df_ServiceMode(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Retrieve the offset of a row in a previously executed numbered search which matches a criteria
*/
int df_GetSearchOffset(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Create and populate a new search result with all rows matching filter criteria from a previously executed numbered search
*/
int df_FilterSearch(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Create and populate a new search result with all rows from a previously executed numbered search sorted on the requested column
*/
int df_SortSearch(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Retrieve the current system (device) date and time.
*/
int df_GetSystemTime(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Retrieve the host name and working IP address from the Sophia host.
*/
int df_GetHostDetails(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the current status of the recycle bin process.
*/
int df_GetRecycleBinStatus(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return a setup confirmation checksum
*/
int df_GetSetupVal(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Move to the next track in the current playlist on a specified room
*/
int df_NextTrack(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Move to the previous track in the current playlist on a specified room
*/
int df_PrevTrack(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Remove the specified track from the current playlist in the specified room
*/
int df_RemoveTrack(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Submit album/playlist(s) for playback on a specified room, either replacing the current playlist or adding to it.
*/
int df_PlayAlbums(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Plays all items in a group i.e. Albums, Artists, Genres etc.
*/
int df_PlayAll(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Submit an album/playlist for playback on a specified room, either replacing the current playlist or adding to it.
*/
int df_PlayAlbum(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Submit a track for playback on a specified room, either replacing the current playlist or adding to it.
*/
int df_PlayTrack(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Submit a list of tracks for playback on a specified room, either replacing the current playlist or adding to it.
*/
int df_PlayTracks(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Submit all tracks from a track search for playback on a specified room, either replacing the current playlist or adding to it.
*/
int df_PlayTracksFromSearch(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Submit all tracks from an album/playlist search for playback on a specified room, either replacing the current playlist or adding to it.
*/
int df_PlayAlbumsFromSearch(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Submit an URL for playback on a specified room, either replacing the current playlist or adding to it.
*/
int df_PlayUrl(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Submit a set of URLs for playback on a specified room, either replacing the current playlist or adding to it.
*/
int df_PlayUrls(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Submit a playlist for playback on a specified room.
*/
int df_PlayPlaylist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Generate a random playlist on a specified room for the specified genre/sub-genre.
*/
int df_PlayRandom(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Play a particular artist/album combination on a specified room.
*/
int df_PlayArtistAlbum(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Play the last played album on a specified room.
*/
int df_PlayLastPlayed(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Play the last album ripped on a specified room.
*/
int df_PlayLastRipped(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Play the most popular album on a specified room.
*/
int df_PlayMostPopular(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Determine whether a CD is playing on the selected room.
*/
int df_IsCDPlaying(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the name of the currently playing track on the selected room.
*/
int df_GetTrackName(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the details of the specified track directly from the player..
*/
int df_GetTrackDetailsFromPlayer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the album and artist of the currently playing track on the selected room.
*/
int df_GetAlbumArtist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the track offset (within the track list) of the currently playing track.
*/
int df_GetTrackNum(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the number of tracks in the currently playing playlist/CD.
*/
int df_GetTrackCount(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the status of the shuffle flag in the selected room.
*/
int df_GetShuffle(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the status of the repeat flag in the selected room.
*/
int df_GetRepeat(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the current player status in the selected room. This will be one of the following; Unknown, Stopped, Playing, Paused, Initialising, FinishedPlaylist, Transitioning (UPnP Only), Connecting (DirectSound, Asio only), Buffering (DirectSound, Asio only)
*/
int df_GetPlayerStatus(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the length of the currently playing track in the selected room.
*/
int df_GetTrackLength(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the current play position/location within the current track.
*/
int df_GetTrackPosition(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the current player version number.
*/
int df_GetPlayerVersion(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the player volume level from the selected room.
*/
int df_GetVolume(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Query the status of all playback results.
*/
int df_QueryAllPlayback(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all defined rooms
*/
int df_GetRooms(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all defined rooms with playback capability
*/
int df_GetRoomsWithPlayBack(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all defined rooms with ripping capability
*/
int df_GetRoomsWithRipping(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all non-linked rooms
*/
int df_GetNonLinkedRooms(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all defined linked rooms
*/
int df_GetLinkedRooms(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List the Advanced Status Display
*/
int df_GetAdvancedStatus(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List the Users Status Display
*/
int df_GetUserStatus(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Query for system status messages.
*/
int df_GetStatusMessages(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists the detail of a single Status Message
*/
int df_GetStatusMessageDetail(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List tracks in the current playlist
*/
int df_GetCurrentPlayList(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List tracks in the current playlist
*/
int df_GetCurrentPlaylistEx(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List the current ripping alerts
*/
int df_GetRippingAlerts(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the details of a single alert
*/
int df_GetAlertDetails(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the details of the current ripping status
*/
int df_GetRippingStatus(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all available named ripping/encoding settings
*/
int df_GetRipEncSettings(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all available named ripping/encoding settings. This is the new form of the command, which returns additional UI caption details.
*/
int df_GetRipEncSettingsEx(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all available named system settings
*/
int df_GetSettings(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all available named system settings. This is the new form of the command, which returns additional UI caption details.
*/
int df_GetSettingsEx(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all available values for a setting
*/
int df_GetAvailableValues(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all defined system drives
*/
int df_GetSystemDrives(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List the contents of the encoding queue
*/
int df_GetEncodingQueue(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns a checksum which indicates changes to data in the Artist, Album and Track tables
*/
int df_GetLibraryCheckSum(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Cancel a current ripping session
*/
int df_CancelRipping(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the details of the current encoding status
*/
int df_GetEncodingStatus(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get a list of all possible player instances and include device and source line settings for those already configured.
*/
int df_GetPlayerInstances(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get a list of output devices for a given room or host name.
*/
int df_GetOutputDevices(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get a list of defined output channels for a given room or host name. Note: An output device, or local output device, is a sound card associated with a given host. An external output device is a standalone output device, such as a UPnP media renderer. An output channel is a Cirin player instance, which is associated with either an output device or an external output device.
*/
int df_GetOutputChannels(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Fetch a list of the UPnP media renderer devices on the local network.
*/
int df_GetUpnpMediaRenderers(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return a list of all currently defined Asio4All output channels. The output channels represent the left and right channels of all available Asio4All supported devices. The left channel has the suffix of 1 and the right channel a suffix of 2 (based on the devices seen so far)
*/
int df_GetAsio4AllChannels(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all defined portable devices
*/
int df_GetDevices(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the details of a single external device.
*/
int df_GetDeviceDetails(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all located network shares (which may, or may not, contain music)
*/
int df_GetExternalStorages(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Backup each user playlist to an m3u file stored on the local music store.
*/
int df_BackupUserPlaylists(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Restore each user playlist from an m3u file stored on the local music store. The command BackupUserPlaylists creates the persisted version of the playlists.
*/
int df_RestoreUserPlaylists(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Sets or Unsets a share as the target of a network backup
*/
int df_SetNetworkBackup(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all located network shares which are flagged as backup targets
*/
int df_GetNetworkBackup(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the Details of a single Drive
*/
int df_GetDriveDetail(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the details of a drive, given it's drive letter, obtained by examining the file system.
*/
int df_GetFileSystemDriveDetail(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Adds a new Drive to the DataBase
*/
int df_AddNewDrive(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Updates an existing system drive to the DB
*/
int df_UpdateDrive(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Deletes an existing system drive from the DB
*/
int df_DeleteDrive(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Delete a Room
*/
int df_DeleteRoom(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Delete a LinkedRoom and its related child room references
*/
int df_DeleteLinkedRoom(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get a single System setting for a specified room
*/
int df_GetSingleSystemSetting(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get a single Ripping/Encoding setting for a specified room
*/
int df_GetSingleRipEncSetting(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Update a Single Ripping/Encoding setting Value for a specified room
*/
int df_UpdateSingleRipEncSetting(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Update a single System setting for a specified room
*/
int df_UpdateSingleSystemSetting(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists the details for a single room
*/
int df_GetRoomDetail(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns the details of a single linked room and its related child rooms
*/
int df_GetLinkedRoomDetail(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Add a new linked room and associate it with a child(ren) room(s)
*/
int df_AddNewLinkedRoom(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Update a linked room and its child(ren) room(s)
*/
int df_UpdateLinkedRoom(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Add a new room
*/
int df_AddNewRoom(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Update a room
*/
int df_UpdateRoom(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the Details of a single Genre
*/
int df_GetGenreDetail(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Adds a new Genre to the DataBase
*/
int df_AddNewGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Updates an existing Genre
*/
int df_UpdateGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Delete a Genre and all its related SubGenre's
*/
int df_DeleteGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the Details of a single SubGenre
*/
int df_GetSubGenreDetail(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Add a new SubGenre and associate it with a Genre
*/
int df_AddNewSubGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Updates an existing SubGenre
*/
int df_UpdateSubGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Delete a SubGenre
*/
int df_DeleteSubGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Gets rid of spaces between Genre and SubGenres ordinals
*/
int df_CompactGenreOrdinals(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  (TEST COMMAND) Generate a random resultset based on limits
*/
int df_TestRows(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Save a player instance on a given room.
*/
int df_SavePlayerInstance(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Remove a player instance from a given room.
*/
int df_RemovePlayerInstance(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Force a disconnection of a portable device.
*/
int df_DisconnectDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return a string checksum of connected devices.
*/
int df_DeviceChecksum(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Delete a portable device from the database.
*/
int df_DeleteDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Set the Synchronisation setting on a portable device in the database.
*/
int df_ToggleDeviceSync(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Sets a share or host to be ignored by the share scanning system
*/
int df_IgnoreExternalStorage(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Cancels a scan or pending scan for the supplied external storage share.
*/
int df_ExternalStorageCancelScan(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Activate or deactivate an external storage share. An active external storage share's music is available to the DigiFi.
*/
int df_ActivateExternalStorage(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Adds the supplied external storage updating the database accordingly
*/
int df_AddExternalStorage(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Scans the network for external storage shares and updates the database accordingly.
*/
int df_ScanForExternalStorages(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Schedules a rescan of external storage shares and updates the database accordingly.
*/
int df_RescanExternalStorages(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Forces a share scan on a given external storage share and updates the database accordingly.
*/
int df_ScanExternalStorage(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Removes the record of an offline external storage share. This command will fail if the external storage share is flagged as online.
*/
int df_RemoveExternalStorage(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the Details of a single external storage share
*/
int df_GetExternalStorageDetail(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Updates the details of an existing external storage share. Note: Data elements which are under the control of the ScanManager cannot be modified using this command.
*/
int df_UpdateExternalStorage(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Create a new output channel on the specified host. You identify the host on which the channel is to be created by either specifying the host name or the ID of an existing room on the host.
*/
int df_NewOutputChannel(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Update an output channel on the specified host. You identify the host on which the channel is to be created by either specifying the host name or the ID of an existing room on the host.
*/
int df_UpdateOutputChannel(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Delete an output channel from the specified host. You identify the host on which the channel is to be created by either specifying the host name or the ID of an existing room on the host.
*/
int df_DeleteOutputChannel(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Changes the usage of a drive, between audio store and backup.
*/
int df_SetDriveUsage(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Initiates the backup of the music folder from one drive, onto the backup folder of another drive. Both drives must be defined system drives marked with the correct usage.
*/
int df_BackupDrive(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Attempt to stop the current drive backup process.
*/
int df_StopBackupDrive(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Retrieve the current status of the system backup process.
*/
int df_GetBackupStatus(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Create a new backup job
*/
int df_AddNewBackupJob(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Update an existing backup job. NOTE: A running job cannot be updated.
*/
int df_UpdateBackupJob(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Delete an existing backup job. NOTE: A running job cannot be deleted.
*/
int df_DeleteBackupJob(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the defined backup jobs.
*/
int df_GetBackupJobs(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the details of a single backup job.
*/
int df_GetBackupJobDetail(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all backup log entries, or all entries associated with a given backup job.
*/
int df_GetBackupLogs(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return a single log entry.
*/
int df_GetBackupLogDetail(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Configure a network adapter to use a DHCP obtained IP address.
*/
int df_ChangeNetworkDhcp(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Configure a network adapter to use a static IP address.
*/
int df_ChangeNetworkStatic(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Configure a network adapter to use an auto-IP address. This is an address generated using a range of IP addresses and the adapter's MAC address.
*/
int df_ChangeNetworkAutoIP(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Change the SMB workgroup, to which the DigiFi device belongs.
*/
int df_ChangeNetworkWorkgroup(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Change the name of the DigiFi device. NOTE: This command is exposed from Sophia in order to allow it to be used from other services, but is for internal use only.
*/
int df_ChangeNetworkMachineName(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Change the serial number of the DigiFi device. NOTE: The serial number of a device can only be changed once, and is normally set by the manufacturer, so expect this command to fail :)
*/
int df_ChangeSystemSerialNumber(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Force the device to process the embedded initialisation file. This command is for internal use and not expected to be called for any other purpose.
*/
int df_ProcessEmbeddedInit(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all active (connected) network adapters.
*/
int df_GetNetworkActiveAdapters(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the current SMB workgroup, of which the DigiFi device is a member.
*/
int df_GetNetworkWorkgroup(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified complex search.
*/
int df_ComplexSearchGetAlbums(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Counts all albums associated with a specified complex search.
*/
int df_ComplexSearchCountAlbums(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all tracks associated with a specified complex search.
*/
int df_ComplexSearchGetTracks(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Counts all tracks associated with a specified complex search.
*/
int df_ComplexSearchCountTracks(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all artists associated with a specified complex search.
*/
int df_ComplexSearchGetArtists(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Counts all artists associated with a specified complex search.
*/
int df_ComplexSearchCountArtists(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all contributors associated with a specified complex search.
*/
int df_ComplexSearchGetContributors(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Counts all contributors associated with a specified complex search.
*/
int df_ComplexSearchCountContributors(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums
*/
int df_GetAlbums(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums for a specified music store
*/
int df_GetAlbumsForStore(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified set of artists
*/
int df_GetAlbumsForArtists(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified set of artists, restricted by a specified sub-genre
*/
int df_GetAlbumsForArtistsInSubGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified set of artists, restricted by a specified sub-genre and associated with a specified usb device.
*/
int df_GetAlbumsForArtistsInSubGenreForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified set of artists, restricted by a specified sub-genre and stored on the server's music stores.
*/
int df_GetAlbumsForArtistsInSubGenreForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified set of artists, restricted by a specified sub-genre and stored on the specified network share.
*/
int df_GetAlbumsForArtistsInSubGenreForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified set of artists, restricted by a specified genre
*/
int df_GetAlbumsForArtistsInGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified set of artists, restricted by a specified portable device
*/
int df_GetAlbumsForArtistsForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified set of artists, restricted by a specified network share
*/
int df_GetAlbumsForArtistsForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified set of artists, restricted by the local server storage
*/
int df_GetAlbumsForArtistsForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified portable device
*/
int df_GetAlbumsForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified network share
*/
int df_GetAlbumsForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums stored locally on the server
*/
int df_GetAlbumsForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums in a playlist
*/
int df_GetAlbumsForPlaylist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all albums containing a specified search string withing eiter the artist or album name
*/
int df_GetAlbumsSearchAlbumArtist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  [object Object]
*/
int df_GetLatestPlayedAlbums(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  [object Object]
*/
int df_GetNewestAlbums(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all the playlists with the Artist beginning with a specified letter
*/
int df_GetPlayListsByLetter(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists playlists associated with a specified genre
*/
int df_GetPlaylistsForGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists playlists associated with a specified sub-genre
*/
int df_GetPlaylistsForSubGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists user-defined playlists associated with a specified sub-genre restricted by portable device
*/
int df_GetPlaylistsForSubGenreForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists user-defined playlists associated with a specified sub-genre restricted by network share
*/
int df_GetPlaylistsForSubGenreForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists user-defined playlists associated with a specified sub-genre restricted to the local server
*/
int df_GetPlaylistsForSubGenreForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists user-defined playlists associated with a specified portable device
*/
int df_GetUserPlaylistsForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists user-defined playlists associated with a specified network share
*/
int df_GetUserPlaylistsForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists user-defined playlists stored locally on the server
*/
int df_GetUserPlaylistsForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all user playlists
*/
int df_GetUserPlaylists(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  [object Object]
*/
int df_GetTopPlayedAlbums(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists additional details for requested albums
*/
int df_GetAlbumsOtherInfo(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists additional details for all albums on the local server
*/
int df_GetAlbumsOtherInfoForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists additional details for all albums
*/
int df_GetAlbumsOtherInfoForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists additional details for all albums
*/
int df_GetAlbumsOtherInfoForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists additional details for all albums
*/
int df_GetAlbumsOtherInfoAll(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List the details for a specified album
*/
int df_GetAlbumDetails(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks on the DigiFi
*/
int df_GetTracksAll(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Retrieve a set of tracks based on the supplied startRow, rowCount and Filter expression. This is an optimised routine which is designed for fast track range retrieval from; all available tracks, local server, device or share. It was original created to support &quot;All Songs&quot; functionality in the Henrot service.
*/
int df_GetTrackRange(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified artist
*/
int df_GetTracksForArtist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified portable device
*/
int df_GetTracksForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified network share
*/
int df_GetTracksForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks stored locally on the server
*/
int df_GetTracksForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified genre
*/
int df_GetTracksForGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified playlist
*/
int df_GetTracksForPlaylist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified sub-genre
*/
int df_GetTracksForSubGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists additional track details
*/
int df_GetTracksOtherInfo(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List tracks containing a specified search string within the track name
*/
int df_GetTracksSearchName(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List tracks containing a specified search string within a single or combination of entity names
*/
int df_AdvancedSearch(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for the supplied entity with the specified value.
*/
int df_GetTracksForNamedEntity(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks in a specified album which are part of a user playlist
*/
int df_GetTracksForAlbumInUPL(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the details of a single artist
*/
int df_GetArtistDetails(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all artists
*/
int df_GetArtists(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all artists with albums in a specified genre
*/
int df_GetArtistsInGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all artists with albums in a specified sub-genre
*/
int df_GetArtistsInSubGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all artists with albums in a specified sub-genre, stored on the specified device.
*/
int df_GetArtistsInSubGenreForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all artists with albums in a specified sub-genre, stored on the music server's music stores.
*/
int df_GetArtistsInSubGenreForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all artists with albums in a specified sub-genre, stored on the specified music share.
*/
int df_GetArtistsInSubGenreForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all artists with albums on a specified portable device
*/
int df_GetArtistsForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all artists with albums on a specified network share
*/
int df_GetArtistsForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all artists with albums stored locally on the server
*/
int df_GetArtistsForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all genres
*/
int df_GetGenres(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all sub-genres for a specified genre
*/
int df_GetSubGenresForGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all sub-genres defined, together with the parent genre name
*/
int df_GetGenresSubGenres(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all sub-genres for a specified portable device
*/
int df_GetSubGenresForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all sub-genres for a specified network share
*/
int df_GetSubGenresForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all sub-genres stored locally on the server
*/
int df_GetSubGenresForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all CDDB Genres
*/
int df_GetCDDBGenres(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Save the tracks in the current playlist to a new playlist
*/
int df_SaveCurrentPlayList(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Creates a random playlist based on the specified parameters.
*/
int df_CreateRandomPlaylistEx(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Creates a random playlist based on the specified parameters.
*/
int df_CreateRandomPlaylist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Create a new user-defined playlist, either populated or blank.
*/
int df_CreatePlaylist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Rename a user-defined playlist.
*/
int df_RenamePlaylist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Add Track(s) to a user defined playlist
*/
int df_AddTracksToUserPlaylist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Add Album(s) tracks to a user defined playlist
*/
int df_AddAlbumsToUserPlaylist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Remove all tracks from the given Album(s) from a user defined playlist
*/
int df_RemoveAlbumsFromUserPlaylist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Delete a Track from a User-Defined Playlist
*/
int df_DeleteTrack(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Change a Track position of a User-Defined Playlist
*/
int df_ChangeTrackOrdinal(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Updates an existing user-defined playlist, using the name and tracks supplied.
*/
int df_UpdatePlaylist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Delete an Album
*/
int df_DeleteAlbum(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Rename a specified album's name
*/
int df_RenameAlbum(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Toggle the low quality flag for a specified album
*/
int df_SetAlbumLowQuality(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Rename a specified Track Name
*/
int df_RenameTrack(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Undo's all user edits to an album except for deleted albums and tracks
*/
int df_UndoUserEdits(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Rename a specified Artist Name
*/
int df_RenameArtist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Change the Genre and SubGenre association of an Album
*/
int df_ChangeAlbumSubGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Increment the hit count of one or more albums, or reset the hit count of all albums in the library.
*/
int df_UpdateHitCount(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of albums on the DigiFi.
*/
int df_CountAlbums(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of albums rows associated with the supplied artist
*/
int df_CountAlbumsForArtist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of artists on the DigiFi.
*/
int df_CountArtists(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of genres on the DigiFi.
*/
int df_CountGenres(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of album/playlist rows associated with the supplied sub-genre
*/
int df_CountPlaylistsForSubGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of sub-genre rows associated with the supplied genre
*/
int df_CountSubGenresForGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of tracks on the DigiFi.
*/
int df_CountTracksAll(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of tracks rows associated with the supplied album/playlist
*/
int df_CountTracksForPlaylist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of user playlists on the DigiFi.
*/
int df_CountUserPlaylists(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of attached portable devices on the DigiFi.
*/
int df_CountDevices(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of albums rows associated with the supplied device
*/
int df_CountAlbumsForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of artists on a device attached to the DigiFi.
*/
int df_CountArtistsForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of sub-genre rows associated with the supplied device
*/
int df_CountSubGenresForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of tracks rows associated with the supplied device
*/
int df_CountTracksForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of UserPlaylists rows associated with the supplied device
*/
int df_CountUserPlaylistsForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of attached network shares on the DigiFi.
*/
int df_CountShares(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of albums rows associated with the supplied network share
*/
int df_CountAlbumsForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of artists on a network share attached to the DigiFi.
*/
int df_CountArtistsForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of sub-genre rows associated with the supplied network share
*/
int df_CountSubGenresForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of tracks rows associated with the supplied network share
*/
int df_CountTracksForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of UserPlaylists rows associated with the supplied network share
*/
int df_CountUserPlaylistsForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of albums stored locally on the main DigiFi server.
*/
int df_CountAlbumsForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of artists stored locally on the main DigiFi server.
*/
int df_CountArtistsForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of sub-genre rows stored locally on the main DigiFi server.
*/
int df_CountSubGenresForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of tracks rows stored locally on the main DigiFi server.
*/
int df_CountTracksForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of UserPlaylists stored locally on the main DigiFi server.
*/
int df_CountUserPlaylistsForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of albums rows associated with the supplied artist on the local server.
*/
int df_CountAlbumsForArtistForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of albums rows associated with the supplied artist, on the specified device.
*/
int df_CountAlbumsForArtistForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of albums rows associated with the supplied artist, on the specified share.
*/
int df_CountAlbumsForArtistForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of album/playlist rows associated with the supplied sub-genre, stored on the local server.
*/
int df_CountPlaylistsForSubGenreForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of album/playlist rows associated with the supplied sub-genre, stored on the specified external device.
*/
int df_CountPlaylistsForSubGenreForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of album/playlist rows associated with the supplied sub-genre, stored on the specified external share.
*/
int df_CountPlaylistsForSubGenreForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified artist, stored on the local server.
*/
int df_GetTracksForArtistForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified artist, stored on the specified external device.
*/
int df_GetTracksForArtistForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified artist, stored on the specified external share.
*/
int df_GetTracksForArtistForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified sub-genre stored on the local server.
*/
int df_GetTracksForSubGenreForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified sub-genre stored on the specified external device.
*/
int df_GetTracksForSubGenreForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified sub-genre stored on the specified external share.
*/
int df_GetTracksForSubGenreForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums which have at least one album lookup message associated them.
*/
int df_GetAlbumsWithAlbumLookupMessages(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums for Deletion
*/
int df_GetAlbumsForDeletion(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all tracks for Deletion
*/
int df_GetTracksForDeletion(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Restore a single specified album that was listed for Deletion
*/
int df_RestoreSingleAlbum(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Restore a single specified track off an album that was listed for Deletion
*/
int df_RestoreSingleTrack(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Uploads a new image for an album.
*/
int df_SetCoverImage(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Remove a cover image for the specified album.
*/
int df_RemoveCoverImage(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the cover image ftp path of a specified track.
*/
int df_CheckCoverImage(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Force a Genre/Playlist backup on a specific Host
*/
int df_ForceGenrePlaylistBackup(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Restores Genre,Sub Genre and Playlist assignments with information from an XML file
*/
int df_ForceGenrePlaylistRestore(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Perform a CD lookup for one or more existing albums.
*/
int df_BulkCDLookup(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Add a CD lookup for one or more existing albums to the CD Lookup queue.
*/
int df_BulkCDLookupEx(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns the current status of the CD lookup daemon in Astoria.
*/
int df_CDLookupGetStatus(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns the current CD lookup queue
*/
int df_CDLookupGetQueue(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Forces an upload of messages to central admin site
*/
int df_UploadMessages(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all system component versions
*/
int df_GetComponentVersions(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns the activity of a long operation
*/
int df_GetOperationActivity(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Send a request to the remote administration site for the specified album cover to be sent to the DigiFi (rather than waiting for an overnight run)
*/
int df_RequestAlbumCover(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Repeatedly Get the current play position/location within the current track.
*/
int df_RGetTrackPosition(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Repeatedly Get the name of the currently playing track on the selected room.
*/
int df_RGetTrackName(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Repeatedly Get the album and artist of the currently playing track on the selected room.
*/
int df_RGetAlbumArtist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Repeatedly Get the player status of the selected room. This will be one of the following; Unknown, Stopped, Playing, Paused, Initialising, FinishedPlaylist, Transitioning (UPnP Only), Connecting (DirectSound, Asio only), Buffering (DirectSound, Asio only)
*/
int df_RGetPlayerStatus(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Repeatedly Get the repeat status of the selected room.
*/
int df_RGetRepeat(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Repeatedly Get the shuffle status of the selected room.
*/
int df_RGetShuffle(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Repeatedly returns Tru/False if the Playlist has changed on the selected room.
*/
int df_RGetPlayingCheckSum(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Repeatedly Get detailed information of the currently playing track in the selected room.
*/
int df_RGetDetailedTrackInfo(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Repeatedly returns the last player error on the specified room.
*/
int df_RGetLastPlayerError(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns any credits given an album key
*/
int df_GetExtAlbumCredits(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all albums for a given contributor
*/
int df_GetExtAlbumsByContributor(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all albums for a given contributor restricted by a specified portable device
*/
int df_GetExtAlbumsByContributorForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all albums for a given contributor restricted by a specified network share
*/
int df_GetExtAlbumsByContributorForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all albums for a given contributor restricted by the local server
*/
int df_GetExtAlbumsByContributorForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all albums where the given contributor appears as a credit
*/
int df_GetExtAlbumsByCredit(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all albums for a given classical work
*/
int df_GetExtAlbumsByWork(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all extra information for given albums
*/
int df_GetExtAlbumsInfo(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all contributors
*/
int df_GetExtContributors(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all contributors for a given album
*/
int df_GetExtContributorsForAlbum(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all contributors for a given portable device
*/
int df_GetExtContributorsForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all contributors for a given network share
*/
int df_GetExtContributorsForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all contributors stored locally on the server
*/
int df_GetExtContributorsForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all contributors for given tracks
*/
int df_GetExtTrackContributors(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all tracks for a given contributor
*/
int df_GetExtTracksByContributor(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all tracks for a given classical work
*/
int df_GetExtTracksByWork(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists extra track information given a list of track keys
*/
int df_GetExtTracksInfo(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all classical works
*/
int df_GetExtWorks(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return a single contributor
*/
int df_GetExtContributorDetails(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of contributors of the specified type.
*/
int df_GetExtCountContributors(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of contributors of the specified type on a given attached portable device.
*/
int df_GetExtCountContributorsForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of contributors of the specified type on a given attached network share.
*/
int df_GetExtCountContributorsForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of contributors of the specified type stored locally on the main DigiFi server.
*/
int df_GetExtCountContributorsForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of albums associated with the contributor, of the specified type.
*/
int df_GetExtCountAlbumsByContributor(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of albums associated with the contributor, of the specified type, for the local server.
*/
int df_GetExtCountAlbumsByContributorForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of albums associated with the contributor, of the specified type, for the specified external device.
*/
int df_GetExtCountAlbumsByContributorForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the number of albums associated with the contributor, of the specified type, for the specified external share.
*/
int df_GetExtCountAlbumsByContributorForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all tracks for a given contributor stored on the local server.
*/
int df_GetExtTracksByContributorForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all tracks for a given contributor stored on the specified external device.
*/
int df_GetExtTracksByContributorForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all tracks for a given contributor stored on the specified external share.
*/
int df_GetExtTracksByContributorForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all albums containing a specified search string within a person's name (artist, conductor, composer or performer)
*/
int df_GetExtAlbumsSearchPeople(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns the vTuner Show, Station or Episode that match the id supplied
*/
int df_vTunerLookupById(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Adds or Removes a node to/from the favourites folder
*/
int df_vTunerAddRemoveFavourite(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return all child vTuner nodes using the supplied vTuner URL.
*/
int df_vTunerGetChildNodes(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Submit an station, show or episode for playback on a specified room by using its vTuner ID, either replacing the current playlist or adding to it.
*/
int df_vTunerPlayById(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Submit a list of station, show or episode ID's for playback on a specified room by using its vTuner ID, either replacing the current playlist or adding to it.
*/
int df_vTunerPlayByIds(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return all played stations and episodes in descending order by HitCount
*/
int df_vTunerGetMostPlayed(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return all played stations and episodes in descending order by LastPlayed
*/
int df_vTunerGetLastPlayed(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return a checksum value for a given set of radio statistics.
*/
int df_vTunerGetRadioStatisticsChecksum(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Sets a preset channel to the supplied station, show or episode id.
*/
int df_vTunerSetPresetChannel(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all preset channels and thier associated nodes
*/
int df_vTunerGetPresetChannels(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns the vTuner Show, Station or Episode that match the Url supplied
*/
int df_vTunerGetNodeFromPlayedUrl(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Checks to see if either the primary or backup vTuner servers are available
*/
int df_vTunerCheckAvailability(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Moves an album from its current music store to another music store
*/
int df_MoveAlbumToMusicStore(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Promotes a share to a music store creating, if neccessary, the required filesystem entries. The command will fail if the share is already owned by another server and change ownership is false.
*/
int df_PromoteShareToMusicStore(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Promotes a share to a music store creating, if neccessary, the required filesystem entries. The command will fail if the share is already owned by another server and change ownership is false.
*/
int df_DemoteMusicStoreToShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Requests a full rescan of the specified music store.
*/
int df_RescanMusicStore(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Sets the priority of the music store for newly ripped music.
*/
int df_SetMusicStorePriority(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists music stores
*/
int df_GetStores(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists music stores
*/
int df_GetStoreDetail(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Sets the username and password required for a music store.
*/
int df_SetMusicStoreCredentials(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns the current status of the move album daemon in Astoria.
*/
int df_MoveAlbumGetStatus(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  rEturns the cuurent move album queue
*/
int df_MoveAlbumGetQueue(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Quickly determine if any contributors exist
*/
int df_GetExtContributorsExist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);


/*!
  Change a connection option
*/
int df_SetConnOption(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return current service status. This is a listing of the currently connected clients
*/
int df_Status(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Set the returned length of a field associated with a format list
*/
int df_SetLength(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Enable a field for a specified format list
*/
int df_EnableField(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Disable a field for a specified format list
*/
int df_DisableField(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  This command returns a rowset that lists the effective format for each return field associated with the supplied command, in the context of the supplied format list
*/
int df_EffFormat(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  [Internal] Used by back end services to indicate that one or more room IP addresses have changed.
*/
int df_RoomIpChanged(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  [Internal] Used by back end services to indicate that the master IP address has changed.
*/
int df_MasterIpChanged(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  [Internal] Used by back-end ripping services to set the status of the current ripping operation
*/
int df_SetRippingStatus(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  [Internal] Used by back-end ripping services to set the CD detected flag
*/
int df_SetCDDetected(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Set the current status of the recycle bin process. Called by Astoria.
*/
int df_SetRecycleBinStatus(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Stop current playback on a specified room
*/
int df_Stop(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Start current playback on a specified room
*/
int df_Play(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Pause current playback on a specified room
*/
int df_Pause(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Clear current playlist on a specified room
*/
int df_ClearPlaylist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Fast forward through currently playing track on a specified room
*/
int df_FastForward(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Fast rewind through currently playing track on a specified room
*/
int df_FastRewind(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Randomly re-order the current playlist on a specified room
*/
int df_RandomisePlaylist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Move to the selected track in the current playlist on a specified room
*/
int df_SetTrack(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Move to the entered track position in the currently playing track on a specified room
*/
int df_SetTrackPosition(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Eject a currently playing CD on a specified room
*/
int df_EjectCD(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Set the volume level on a specified room
*/
int df_SetVolume(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Toggle shuffle on a specified room
*/
int df_SetShuffle(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Toggle repeat on a specified room
*/
int df_SetRepeat(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Clear all now playing tracklists in all rooms.
*/
int df_ClearAllPlaying(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Restart the DigiFi device.
*/
int df_RestartDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Change a Single CDDB SubGenre Association
*/
int df_ChangeCDDBSubGenreAssociation(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Perform an upgrade for a specific host
*/
int df_ForceHostUpgrade(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Force a remote Database to rebuild on a specific host the next time the services restart.
*/
int df_ForceDBRebuild(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Purge the image cache on a specific host
*/
int df_PurgeImageCache(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Cancels a request to perform a cd lookup
*/
int df_CDLookupCancel(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Cancels all pending CD lookup requests.
*/
int df_CdLookupCancelAll(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Remove all tracks and albums marked for deletion from the database
*/
int df_EmptyRecycleBin(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Empty the uploads folder on a specified host
*/
int df_EmptyRipShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Empty the download folder on the specified host
*/
int df_ClearDownloadFolder(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Registers a client in preperation for Repeat Gets. This must be called before any RGet commands can be issued.
*/
int df_RGetRegisterClient(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Clears all registered commands on a selected room.
*/
int df_RGetClearCommands(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Removes all the statistics for any item that hasn't been played for n days.
*/
int df_vTunerCleanStatistics(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Clears a preset channel
*/
int df_vTunerClearPresetChannel(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Cancels a request to move an album
*/
int df_MoveAlbumCancel(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Cancels all pending move album requests.
*/
int df_MoveAlbumCancelAll(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);


/*!
  Return current service status. This is a listing of the currently connected clients
*/
int df_Status(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  This command returns a rowset that lists the effective format for each return field associated with the supplied command, in the context of the supplied format list
*/
int df_EffFormat(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Create and populate a new search result with all rows matching filter criteria from a previously executed numbered search
*/
int df_FilterSearch(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Create and populate a new search result with all rows from a previously executed numbered search sorted on the requested column
*/
int df_SortSearch(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all defined rooms
*/
int df_GetRooms(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all defined rooms with playback capability
*/
int df_GetRoomsWithPlayBack(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all defined rooms with ripping capability
*/
int df_GetRoomsWithRipping(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all non-linked rooms
*/
int df_GetNonLinkedRooms(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all defined linked rooms
*/
int df_GetLinkedRooms(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List the Advanced Status Display
*/
int df_GetAdvancedStatus(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List the Users Status Display
*/
int df_GetUserStatus(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Query for system status messages.
*/
int df_GetStatusMessages(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List tracks in the current playlist
*/
int df_GetCurrentPlayList(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List tracks in the current playlist
*/
int df_GetCurrentPlaylistEx(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List the current ripping alerts
*/
int df_GetRippingAlerts(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the details of a single alert
*/
int df_GetAlertDetails(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the details of the current ripping status
*/
int df_GetRippingStatus(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all available named ripping/encoding settings
*/
int df_GetRipEncSettings(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all available named ripping/encoding settings. This is the new form of the command, which returns additional UI caption details.
*/
int df_GetRipEncSettingsEx(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all available named system settings
*/
int df_GetSettings(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all available named system settings. This is the new form of the command, which returns additional UI caption details.
*/
int df_GetSettingsEx(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all available values for a setting
*/
int df_GetAvailableValues(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all defined system drives
*/
int df_GetSystemDrives(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List the contents of the encoding queue
*/
int df_GetEncodingQueue(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get the details of the current encoding status
*/
int df_GetEncodingStatus(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get a list of all possible player instances and include device and source line settings for those already configured.
*/
int df_GetPlayerInstances(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get a list of output devices for a given room or host name.
*/
int df_GetOutputDevices(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Get a list of defined output channels for a given room or host name. Note: An output device, or local output device, is a sound card associated with a given host. An external output device is a standalone output device, such as a UPnP media renderer. An output channel is a Cirin player instance, which is associated with either an output device or an external output device.
*/
int df_GetOutputChannels(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Fetch a list of the UPnP media renderer devices on the local network.
*/
int df_GetUpnpMediaRenderers(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return a list of all currently defined Asio4All output channels. The output channels represent the left and right channels of all available Asio4All supported devices. The left channel has the suffix of 1 and the right channel a suffix of 2 (based on the devices seen so far)
*/
int df_GetAsio4AllChannels(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all defined portable devices
*/
int df_GetDevices(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the details of a single external device.
*/
int df_GetDeviceDetails(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all located network shares (which may, or may not, contain music)
*/
int df_GetExternalStorages(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all located network shares which are flagged as backup targets
*/
int df_GetNetworkBackup(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns the details of a single linked room and its related child rooms
*/
int df_GetLinkedRoomDetail(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  (TEST COMMAND) Generate a random resultset based on limits
*/
int df_TestRows(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the defined backup jobs.
*/
int df_GetBackupJobs(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the details of a single backup job.
*/
int df_GetBackupJobDetail(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all backup log entries, or all entries associated with a given backup job.
*/
int df_GetBackupLogs(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return a single log entry.
*/
int df_GetBackupLogDetail(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all active (connected) network adapters.
*/
int df_GetNetworkActiveAdapters(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified complex search.
*/
int df_ComplexSearchGetAlbums(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all tracks associated with a specified complex search.
*/
int df_ComplexSearchGetTracks(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all artists associated with a specified complex search.
*/
int df_ComplexSearchGetArtists(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all contributors associated with a specified complex search.
*/
int df_ComplexSearchGetContributors(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums
*/
int df_GetAlbums(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums for a specified music store
*/
int df_GetAlbumsForStore(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified set of artists
*/
int df_GetAlbumsForArtists(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified set of artists, restricted by a specified sub-genre
*/
int df_GetAlbumsForArtistsInSubGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified set of artists, restricted by a specified sub-genre and associated with a specified usb device.
*/
int df_GetAlbumsForArtistsInSubGenreForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified set of artists, restricted by a specified sub-genre and stored on the server's music stores.
*/
int df_GetAlbumsForArtistsInSubGenreForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified set of artists, restricted by a specified sub-genre and stored on the specified network share.
*/
int df_GetAlbumsForArtistsInSubGenreForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified set of artists, restricted by a specified genre
*/
int df_GetAlbumsForArtistsInGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified set of artists, restricted by a specified portable device
*/
int df_GetAlbumsForArtistsForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified set of artists, restricted by a specified network share
*/
int df_GetAlbumsForArtistsForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified set of artists, restricted by the local server storage
*/
int df_GetAlbumsForArtistsForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified portable device
*/
int df_GetAlbumsForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums associated with a specified network share
*/
int df_GetAlbumsForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums stored locally on the server
*/
int df_GetAlbumsForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums in a playlist
*/
int df_GetAlbumsForPlaylist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all albums containing a specified search string withing eiter the artist or album name
*/
int df_GetAlbumsSearchAlbumArtist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  [object Object]
*/
int df_GetLatestPlayedAlbums(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  [object Object]
*/
int df_GetNewestAlbums(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all the playlists with the Artist beginning with a specified letter
*/
int df_GetPlayListsByLetter(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists playlists associated with a specified genre
*/
int df_GetPlaylistsForGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists playlists associated with a specified sub-genre
*/
int df_GetPlaylistsForSubGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists user-defined playlists associated with a specified sub-genre restricted by portable device
*/
int df_GetPlaylistsForSubGenreForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists user-defined playlists associated with a specified sub-genre restricted by network share
*/
int df_GetPlaylistsForSubGenreForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists user-defined playlists associated with a specified sub-genre restricted to the local server
*/
int df_GetPlaylistsForSubGenreForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists user-defined playlists associated with a specified portable device
*/
int df_GetUserPlaylistsForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists user-defined playlists associated with a specified network share
*/
int df_GetUserPlaylistsForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists user-defined playlists stored locally on the server
*/
int df_GetUserPlaylistsForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all user playlists
*/
int df_GetUserPlaylists(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  [object Object]
*/
int df_GetTopPlayedAlbums(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists additional details for requested albums
*/
int df_GetAlbumsOtherInfo(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists additional details for all albums on the local server
*/
int df_GetAlbumsOtherInfoForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists additional details for all albums
*/
int df_GetAlbumsOtherInfoForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists additional details for all albums
*/
int df_GetAlbumsOtherInfoForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists additional details for all albums
*/
int df_GetAlbumsOtherInfoAll(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List the details for a specified album
*/
int df_GetAlbumDetails(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks on the DigiFi
*/
int df_GetTracksAll(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Retrieve a set of tracks based on the supplied startRow, rowCount and Filter expression. This is an optimised routine which is designed for fast track range retrieval from; all available tracks, local server, device or share. It was original created to support &quot;All Songs&quot; functionality in the Henrot service.
*/
int df_GetTrackRange(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified artist
*/
int df_GetTracksForArtist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified portable device
*/
int df_GetTracksForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified network share
*/
int df_GetTracksForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks stored locally on the server
*/
int df_GetTracksForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified genre
*/
int df_GetTracksForGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified playlist
*/
int df_GetTracksForPlaylist(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified sub-genre
*/
int df_GetTracksForSubGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists additional track details
*/
int df_GetTracksOtherInfo(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List tracks containing a specified search string within the track name
*/
int df_GetTracksSearchName(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List tracks containing a specified search string within a single or combination of entity names
*/
int df_AdvancedSearch(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for the supplied entity with the specified value.
*/
int df_GetTracksForNamedEntity(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks in a specified album which are part of a user playlist
*/
int df_GetTracksForAlbumInUPL(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return the details of a single artist
*/
int df_GetArtistDetails(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all artists
*/
int df_GetArtists(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all artists with albums in a specified genre
*/
int df_GetArtistsInGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all artists with albums in a specified sub-genre
*/
int df_GetArtistsInSubGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all artists with albums in a specified sub-genre, stored on the specified device.
*/
int df_GetArtistsInSubGenreForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all artists with albums in a specified sub-genre, stored on the music server's music stores.
*/
int df_GetArtistsInSubGenreForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all artists with albums in a specified sub-genre, stored on the specified music share.
*/
int df_GetArtistsInSubGenreForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all artists with albums on a specified portable device
*/
int df_GetArtistsForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all artists with albums on a specified network share
*/
int df_GetArtistsForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all artists with albums stored locally on the server
*/
int df_GetArtistsForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all genres
*/
int df_GetGenres(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all sub-genres for a specified genre
*/
int df_GetSubGenresForGenre(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all sub-genres defined, together with the parent genre name
*/
int df_GetGenresSubGenres(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all sub-genres for a specified portable device
*/
int df_GetSubGenresForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all sub-genres for a specified network share
*/
int df_GetSubGenresForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all sub-genres stored locally on the server
*/
int df_GetSubGenresForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all CDDB Genres
*/
int df_GetCDDBGenres(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Undo's all user edits to an album except for deleted albums and tracks
*/
int df_UndoUserEdits(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified artist, stored on the local server.
*/
int df_GetTracksForArtistForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified artist, stored on the specified external device.
*/
int df_GetTracksForArtistForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified artist, stored on the specified external share.
*/
int df_GetTracksForArtistForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified sub-genre stored on the local server.
*/
int df_GetTracksForSubGenreForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified sub-genre stored on the specified external device.
*/
int df_GetTracksForSubGenreForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all the tracks for a specified sub-genre stored on the specified external share.
*/
int df_GetTracksForSubGenreForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums which have at least one album lookup message associated them.
*/
int df_GetAlbumsWithAlbumLookupMessages(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all albums for Deletion
*/
int df_GetAlbumsForDeletion(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all tracks for Deletion
*/
int df_GetTracksForDeletion(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Perform a CD lookup for one or more existing albums.
*/
int df_BulkCDLookup(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns the current CD lookup queue
*/
int df_CDLookupGetQueue(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all system component versions
*/
int df_GetComponentVersions(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns any credits given an album key
*/
int df_GetExtAlbumCredits(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all albums for a given contributor
*/
int df_GetExtAlbumsByContributor(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all albums for a given contributor restricted by a specified portable device
*/
int df_GetExtAlbumsByContributorForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all albums for a given contributor restricted by a specified network share
*/
int df_GetExtAlbumsByContributorForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all albums for a given contributor restricted by the local server
*/
int df_GetExtAlbumsByContributorForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all albums where the given contributor appears as a credit
*/
int df_GetExtAlbumsByCredit(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all albums for a given classical work
*/
int df_GetExtAlbumsByWork(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all extra information for given albums
*/
int df_GetExtAlbumsInfo(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all contributors
*/
int df_GetExtContributors(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all contributors for a given album
*/
int df_GetExtContributorsForAlbum(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all contributors for a given portable device
*/
int df_GetExtContributorsForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all contributors for a given network share
*/
int df_GetExtContributorsForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all contributors stored locally on the server
*/
int df_GetExtContributorsForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all contributors for given tracks
*/
int df_GetExtTrackContributors(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all tracks for a given contributor
*/
int df_GetExtTracksByContributor(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all tracks for a given classical work
*/
int df_GetExtTracksByWork(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists extra track information given a list of track keys
*/
int df_GetExtTracksInfo(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists all classical works
*/
int df_GetExtWorks(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return a single contributor
*/
int df_GetExtContributorDetails(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all tracks for a given contributor stored on the local server.
*/
int df_GetExtTracksByContributorForServer(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all tracks for a given contributor stored on the specified external device.
*/
int df_GetExtTracksByContributorForDevice(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all tracks for a given contributor stored on the specified external share.
*/
int df_GetExtTracksByContributorForShare(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  List all albums containing a specified search string within a person's name (artist, conductor, composer or performer)
*/
int df_GetExtAlbumsSearchPeople(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns the vTuner Show, Station or Episode that match the id supplied
*/
int df_vTunerLookupById(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return all child vTuner nodes using the supplied vTuner URL.
*/
int df_vTunerGetChildNodes(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return all played stations and episodes in descending order by HitCount
*/
int df_vTunerGetMostPlayed(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Return all played stations and episodes in descending order by LastPlayed
*/
int df_vTunerGetLastPlayed(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns all preset channels and thier associated nodes
*/
int df_vTunerGetPresetChannels(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Returns the vTuner Show, Station or Episode that match the Url supplied
*/
int df_vTunerGetNodeFromPlayedUrl(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists music stores
*/
int df_GetStores(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  Lists music stores
*/
int df_GetStoreDetail(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
  rEturns the cuurent move album queue
*/
int df_MoveAlbumGetQueue(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

