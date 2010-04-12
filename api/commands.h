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


// Generated functions
//

// Get commands

void df_newdriveresult_free(df_newdriveresult *ptr);
void df_servicemode_free(df_servicemode *ptr);
void df_drivedetail_free(df_drivedetail *ptr);
void df_extstoragedetail_free(df_extstoragedetail *ptr);
void df_trkname_free(df_trkname *ptr);
void df_rescanresult_free(df_rescanresult *ptr);
void df_messagedetail_free(df_messagedetail *ptr);
void df_fsdrivedetail_free(df_fsdrivedetail *ptr);
void df_extstorageresult_free(df_extstorageresult *ptr);
void df_systemtime_free(df_systemtime *ptr);
void df_demoteresult_free(df_demoteresult *ptr);
void df_albumartist_free(df_albumartist *ptr);
void df_musicstorepriorityresult_free(df_musicstorepriorityresult *ptr);
void df_backupstatus_free(df_backupstatus *ptr);
void df_coverimage_free(df_coverimage *ptr);
void df_queryplayback_free(df_queryplayback *ptr);
void df_hostdetails_free(df_hostdetails *ptr);
void df_stopbackupdriveresult_free(df_stopbackupdriveresult *ptr);
void df_version_free(df_version *ptr);
void df_room_free(df_room *ptr);
void df_movealbumstatus_free(df_movealbumstatus *ptr);
void df_backupresult_free(df_backupresult *ptr);
void df_searchoffset_free(df_searchoffset *ptr);
void df_type0_free(df_type0 *ptr);
void df_genre_free(df_genre *ptr);
void df_trackfromplayer_free(df_trackfromplayer *ptr);
void df_driveusageresult_free(df_driveusageresult *ptr);
void df_subgenre_free(df_subgenre *ptr);
void df_promoteshare_free(df_promoteshare *ptr);
void df_updatedrivedetails_free(df_updatedrivedetails *ptr);
/*!
Activate or deactivate an external storage share. An active external storage share's music is available to the DigiFi.
StorageKey: The storage key value to use for this command.
ActiveFlag: The flag to use for activating or deactivating the external storage share.
ClearPlaying: If true then clear all rooms playing music from this device first (only used when deactivating a share).
*/
int df_ActivateExternalStorage(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context);

/*!
Add Album(s) tracks to a user defined playlist
UserPlaylistKey: The absolute or relative address of the playlist to have tracks added to
AlbumKey: The absolute or relative addresses of the Album(s) to be added to the playlist (Space sperated)
*/
int df_AddAlbumsToUserPlaylist(df_connection *conn, char* UserPlaylistKey, char* AlbumKey, void (*callback)(int, void*), void *context);

/*!
Adds the supplied external storage updating the database accordingly
SharePath: The UNC path to the external stoage to add
Username: The name of the user used to connect to the resource, leave blank to use default credentials
Password: The encoded password used to connect to the resource, leave blank to use default credentials
Activate: Should the external storage be activated as soon as it's added to the database.
ForceAdd: Should the share be added to the database even if the validation fails. If this value is true Activate option will be maintained but the share will not automatiucally be entered onto the scan list.
*/
int df_AddExternalStorage(df_connection *conn, char* SharePath, char* Username, char* Password, int Activate, int ForceAdd, void (*callback)(df_extstorageresult*, void*), void *context);

/*!
Create a new backup job
SourceDriveAddress: The absolute or relative address of the Drive to back up music from.
DestinationDriveAddress: The absolute or relative address of the Drive to back up music to.
Name: The name of the backup job (can be empty).
BackupType: The type of backup being scheduled (0 - full backup, 1 - differential backup).
BackupPeriod: A value which determines how often the backup job will run (0 - once only, 1 - daily, 2 - weekly, 3 - monthly).
PeriodValue: A value which indicates when in the given period the backup job will run. Day of the week for weeklies, day of the month for monthlies, ignored for run once jobs.
RunDate: The date on which the job will be run. This is only used by run once jobs.
RunTime: The time at which the job will be run. This is used to construct the next run date and time for all job types.
*/
int df_AddNewBackupJob(df_connection *conn, char* SourceDriveAddress, char* DestinationDriveAddress, char* Name, int BackupType, int BackupPeriod, int PeriodValue, df_date RunDate, df_time RunTime, void (*callback)(int, void*), void *context);

/*!
Adds a new Drive to the DataBase
DriveLetter: The Name you want to assign to the new Drive
PrimaryDrive: Specify if the new Drive should be set to Primary
RootPath: Combined with the Drive Letter, Root Path is the Local Path
SharePath: The address of where the music share is
Usage: The usage of the drive. 0 = audio store (default), 1 = backup.
BadPathBehaviour: Determines how the command will handle a non-existent root path. 0 = [None] Command returns error (default), 1 = [Ignore] Command will ignore a bad path and save the row regardless, 2 = [Create] The command will attempt to create the root path .
*/
int df_AddNewDrive(df_connection *conn, char* DriveLetter, int PrimaryDrive, char* RootPath, char* SharePath, int Usage, int BadPathBehaviour, void (*callback)(df_newdriveresult*, void*), void *context);

/*!
Adds a new Genre to the DataBase
GenreName: The Name you want to assign to the new Genre
Ordinal: The Position in the list of Genres
*/
int df_AddNewGenre(df_connection *conn, char* GenreName, int Ordinal, void (*callback)(int, void*), void *context);

/*!
Add a new linked room and associate it with a child(ren) room(s)
RoomName: The Name of the linked Room
ShortName: Linked rooms short name(3 characters)
RoomID: An ID used to determine the Room
ChildRoomKey: The absolute or relative addresses of a Child Room to be linked with the new room (space seperated)
*/
int df_AddNewLinkedRoom(df_connection *conn, char* RoomName, char* ShortName, int RoomID, char* ChildRoomKey, void (*callback)(int, void*), void *context);

/*!
Add a new room
RoomIP: The IP address of the Room
Channel: The Channel of the room
RoomName: The unique name of the linked Room
ShortName: Rooms unique short name(3 characters)
PlaybackCapability: If the room has playback capability
RippingCapability: If the room has ripping capability
MusicManagementCapability: If the room has music management capability
RoomID: A unique ID used to determine the Room
HostName: The network name of the host which provides the room.
*/
int df_AddNewRoom(df_connection *conn, char* RoomIP, int Channel, char* RoomName, char* ShortName, int PlaybackCapability, int RippingCapability, int MusicManagementCapability, int RoomID, char* HostName, void (*callback)(int, void*), void *context);

/*!
Add a new SubGenre and associate it with a Genre
GenreKey: The absolute or relative address of the Genre to be associated with the new SubGenre
SubGenreName: The new SubGenre name you want to add
Ordinal: The Position in the list of SubGenres
*/
int df_AddNewSubGenre(df_connection *conn, char* GenreKey, char* SubGenreName, int Ordinal, void (*callback)(int, void*), void *context);

/*!
Add Track(s) to a user defined playlist
UserPlaylistKey: The absolute or relative address of the playlist to have tracks added to
TrackKey: The absolute or relative addresses of tracks to be added to the playlist (Space sperated)
*/
int df_AddTracksToUserPlaylist(df_connection *conn, char* UserPlaylistKey, char* TrackKey, void (*callback)(int, void*), void *context);

/*!
Initiates the backup of the music folder from one drive, onto the backup folder of another drive. Both drives must be defined system drives marked with the correct usage.
SourceDriveKey: The absolute or relative address of the source drive. This drive must be marked as an audio drive. If this drive contains the AppPath then all the DigiFi binaries will also be backed up (and covers etc).
DestDriveKey: The absolute or relative address of the destination drive. This drive must be marked as a backup drive.
BackupType: The type of backup to perform. This can take one of the values: 0 (Full), 1 (Differential).
NoFileCheck: If this parameter is set to true then the backup process will not check for suspicious files.
*/
int df_BackupDrive(df_connection *conn, char* SourceDriveKey, char* DestDriveKey, int BackupType, int NoFileCheck, void (*callback)(df_backupresult*, void*), void *context);

/*!
Add a CD lookup for one or more existing albums to the CD Lookup queue.
LookupProviderUsed: A code indicating the minimum level of lookup provider to use for the selection. (0 = No Match Found, 1 = FreeDB local database, 2 = FreeDB online query, 3 = AMG local database, 4 = AMG online query, 5 = Manual changes made to album)
Interval: Lookup interval in days. This is the number of days since the last lookup, and controls which albums will be selected.
AlbumKey: The absolute or relative addresses of specific Album(s) to use
*/
int df_BulkCDLookupEx(df_connection *conn, int LookupProviderUsed, int Interval, char* AlbumKey, void (*callback)(int, void*), void *context);

/*!
Returns the current status of the CD lookup daemon in Astoria.
*/
int df_CDLookupGetStatus(df_connection *conn, void (*callback)(df_type0*, void*), void *context);

/*!
Cancel a current ripping session
RoomID: The room ID to use for this command.
*/
int df_CancelRipping(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context);

/*!
Change the Genre and SubGenre association of an Album
AlbumKey: The absolute or relative address of the Album
SubGenreKey: The absolute or relative address of the Sub Genre
*/
int df_ChangeAlbumSubGenre(df_connection *conn, char* AlbumKey, char* SubGenreKey, void (*callback)(char*, void*), void *context);

/*!
Configure a network adapter to use an auto-IP address. This is an address generated using a range of IP addresses and the adapter's MAC address.
DeviceID: The device ID of the adapter to configure (as returned by GetActiveNetworkAdapters).
AutoIpRange: The range of addresses from which the address will be selected. The range is expressed as a minimum and maximum address, separated by a colon.
DefaultGateway: The IP address of the default gateway.
DnsServer: The IP address of the DNS server. This can be a comma separated list of addresses.
RestartDevice: If true then restart the DigiFi device if the command is successful. Defaults to False.
*/
int df_ChangeNetworkAutoIP(df_connection *conn, int DeviceID, char* AutoIpRange, char* DefaultGateway, char* DnsServer, int RestartDevice, void (*callback)(int, void*), void *context);

/*!
Configure a network adapter to use a DHCP obtained IP address.
DeviceID: The device ID of the adapter to configure (as returned by GetActiveNetworkAdapters).
RestartDevice: If true then restart the DigiFi device if the command is successful. Defaults to False.
*/
int df_ChangeNetworkDhcp(df_connection *conn, int DeviceID, int RestartDevice, void (*callback)(int, void*), void *context);

/*!
Change the name of the DigiFi device. NOTE: This command is exposed from Sophia in order to allow it to be used from other services, but is for internal use only.
MachineName: The new machine name.
*/
int df_ChangeNetworkMachineName(df_connection *conn, char* MachineName, void (*callback)(int, void*), void *context);

/*!
Configure a network adapter to use a static IP address.
DeviceID: The device ID of the adapter to configure (as returned by GetActiveNetworkAdapters).
IpAddress: The static IP address to use.
SubnetMask: The subnet mask to use with the IP address.
DefaultGateway: The IP address of the default gateway.
DnsServer: The IP address of the DNS server. This can be a comma separated list of addresses.
RestartDevice: If true then restart the DigiFi device if the command is successful. Defaults to False.
*/
int df_ChangeNetworkStatic(df_connection *conn, int DeviceID, char* IpAddress, char* SubnetMask, char* DefaultGateway, char* DnsServer, int RestartDevice, void (*callback)(int, void*), void *context);

/*!
Change the SMB workgroup, to which the DigiFi device belongs.
Workgroup: The name of the new workgroup.
*/
int df_ChangeNetworkWorkgroup(df_connection *conn, char* Workgroup, void (*callback)(int, void*), void *context);

/*!
Change the serial number of the DigiFi device. NOTE: The serial number of a device can only be changed once, and is normally set by the manufacturer, so expect this command to fail :)
SerialNumber: The new serial number.
*/
int df_ChangeSystemSerialNumber(df_connection *conn, char* SerialNumber, void (*callback)(int, void*), void *context);

/*!
Change a Track position of a User-Defined Playlist
TrackKey: The absolute or relative address of the Track's ordinal to be changed
PlaylistKey: The absolute or relative address of the Playlist the Track belongs to
Ordinal: The current track position/ordinal within the given playlist.
NewPosition: The Tracks new ordinal position
ReorderPlaylist: Automatically reorder all tracks in the same playlist?
*/
int df_ChangeTrackOrdinal(df_connection *conn, char* TrackKey, char* PlaylistKey, int Ordinal, int NewPosition, int ReorderPlaylist, void (*callback)(int, void*), void *context);

/*!
Get the cover image ftp path of a specified track.
Address: The absolute or relative address of a track to search.
ImageSize: 1 = small (61x61), 2 = medium (126x126), 3 = large (320x320), 4 = extra large (640x640).
AddressType: 1 = track, 2 = album, 3 = cd source (default=1).
Local: Flag determining the format of the response. FTP location vs local path (default=0).
Protocol: The protocol to use for the return path, if the Local parameter is false (0). This can be either "FTP" (for backward compatibility) or "HTTP" (default).
ImageFormat: The format of the cover image file. This must be "JPG", since "BMP" is no longer supported. "JPG" is the default.
*/
int df_CheckCoverImage(df_connection *conn, char* Address, int ImageSize, int AddressType, int Local, char* Protocol, char* ImageFormat, void (*callback)(df_coverimage*, void*), void *context);

/*!
Gets rid of spaces between Genre and SubGenres ordinals
*/
int df_CompactGenreOrdinals(df_connection *conn, void (*callback)(int, void*), void *context);

/*!
Counts all albums associated with a specified complex search.
SearchParameter: Psuedo SQL to apply to the search.
*/
int df_ComplexSearchCountAlbums(df_connection *conn, char* SearchParameter, void (*callback)(int, void*), void *context);

/*!
Counts all artists associated with a specified complex search.
SearchParameter: Psuedo SQL to apply to the search.
*/
int df_ComplexSearchCountArtists(df_connection *conn, char* SearchParameter, void (*callback)(int, void*), void *context);

/*!
Counts all contributors associated with a specified complex search.
Type: Contributor Type
SearchParameter: Psuedo SQL to apply to the search.
*/
int df_ComplexSearchCountContributors(df_connection *conn, int Type, char* SearchParameter, void (*callback)(int, void*), void *context);

/*!
Counts all tracks associated with a specified complex search.
SearchParameter: Psuedo SQL to apply to the search.
*/
int df_ComplexSearchCountTracks(df_connection *conn, char* SearchParameter, void (*callback)(int, void*), void *context);

/*!
Return the number of albums on the DigiFi.
*/
int df_CountAlbums(df_connection *conn, void (*callback)(int, void*), void *context);

/*!
Return the number of albums rows associated with the supplied artist
Address: The absolute or relative address of an artist
*/
int df_CountAlbumsForArtist(df_connection *conn, char* Address, void (*callback)(int, void*), void *context);

/*!
Return the number of albums rows associated with the supplied artist, on the specified device.
Address: The absolute or relative address of an artist
DeviceAddress: The absolute or relative address of an external device.
*/
int df_CountAlbumsForArtistForDevice(df_connection *conn, char* Address, char* DeviceAddress, void (*callback)(int, void*), void *context);

/*!
Return the number of albums rows associated with the supplied artist on the local server.
Address: The absolute or relative address of an artist
*/
int df_CountAlbumsForArtistForServer(df_connection *conn, char* Address, void (*callback)(int, void*), void *context);

/*!
Return the number of albums rows associated with the supplied artist, on the specified share.
Address: The absolute or relative address of an artist
ShareAddress: The absolute or relative address of an external share.
*/
int df_CountAlbumsForArtistForShare(df_connection *conn, char* Address, char* ShareAddress, void (*callback)(int, void*), void *context);

/*!
Return the number of albums rows associated with the supplied device
Address: The absolute or relative address of a device
*/
int df_CountAlbumsForDevice(df_connection *conn, char* Address, void (*callback)(int, void*), void *context);

/*!
Return the number of albums stored locally on the main DigiFi server.
*/
int df_CountAlbumsForServer(df_connection *conn, void (*callback)(int, void*), void *context);

/*!
Return the number of albums rows associated with the supplied network share
Address: The absolute or relative address of a share
*/
int df_CountAlbumsForShare(df_connection *conn, char* Address, void (*callback)(int, void*), void *context);

/*!
Return the number of artists on the DigiFi.
Allocated: Flag controlling whether only allocated artists should be shown(those with albums). Defaults to False.
*/
int df_CountArtists(df_connection *conn, int Allocated, void (*callback)(int, void*), void *context);

/*!
Return the number of artists on a device attached to the DigiFi.
Address: The absolute or relative address of a device
*/
int df_CountArtistsForDevice(df_connection *conn, char* Address, void (*callback)(int, void*), void *context);

/*!
Return the number of artists stored locally on the main DigiFi server.
*/
int df_CountArtistsForServer(df_connection *conn, void (*callback)(int, void*), void *context);

/*!
Return the number of artists on a network share attached to the DigiFi.
Address: The absolute or relative address of a share
*/
int df_CountArtistsForShare(df_connection *conn, char* Address, void (*callback)(int, void*), void *context);

/*!
Return the number of attached portable devices on the DigiFi.
ActiveOnly: If this parameter is true then only docked devices will be counted. If this parameter is false then all devices will be counted. Defaults to false.
*/
int df_CountDevices(df_connection *conn, int ActiveOnly, void (*callback)(int, void*), void *context);

/*!
Return the number of genres on the DigiFi.
Allocated: Flag controlling whether only allocated genres should be returned. Defaults to False.
*/
int df_CountGenres(df_connection *conn, int Allocated, void (*callback)(int, void*), void *context);

/*!
Return the number of album/playlist rows associated with the supplied sub-genre
Address: The absolute or relative address of a sub-genre
*/
int df_CountPlaylistsForSubGenre(df_connection *conn, char* Address, void (*callback)(int, void*), void *context);

/*!
Return the number of album/playlist rows associated with the supplied sub-genre, stored on the specified external device.
Address: The absolute or relative address of a sub-genre
DeviceAddress: The absolute or relative address of an external device.
*/
int df_CountPlaylistsForSubGenreForDevice(df_connection *conn, char* Address, char* DeviceAddress, void (*callback)(int, void*), void *context);

/*!
Return the number of album/playlist rows associated with the supplied sub-genre, stored on the local server.
Address: The absolute or relative address of a sub-genre
*/
int df_CountPlaylistsForSubGenreForServer(df_connection *conn, char* Address, void (*callback)(int, void*), void *context);

/*!
Return the number of album/playlist rows associated with the supplied sub-genre, stored on the specified external share.
Address: The absolute or relative address of a sub-genre
ShareAddress: The absolute or relative address of an external share.
*/
int df_CountPlaylistsForSubGenreForShare(df_connection *conn, char* Address, char* ShareAddress, void (*callback)(int, void*), void *context);

/*!
Return the number of attached network shares on the DigiFi.
AvailableOnly: If this parameter is true then only shares which are flagged active and with a state of "Online" will be counted. If this parameter is false then all shares will be counted. Defaults to false.
*/
int df_CountShares(df_connection *conn, int AvailableOnly, void (*callback)(int, void*), void *context);

/*!
Return the number of sub-genre rows associated with the supplied device
Address: The absolute or relative address of a device
*/
int df_CountSubGenresForDevice(df_connection *conn, char* Address, void (*callback)(int, void*), void *context);

/*!
Return the number of sub-genre rows associated with the supplied genre
Address: The absolute or relative address of a genre
Allocated: Flag controlling whether only allocated sub-genres should be returned. Defaults to False.
*/
int df_CountSubGenresForGenre(df_connection *conn, char* Address, int Allocated, void (*callback)(int, void*), void *context);

/*!
Return the number of sub-genre rows stored locally on the main DigiFi server.
Allocated: Flag controlling whether only allocated sub-genres should be returned. Defaults to False.
UserDefined: Flag controlling whether additional unallocated userdefined sub-genres should be returned. Defaults to False.
*/
int df_CountSubGenresForServer(df_connection *conn, int Allocated, int UserDefined, void (*callback)(int, void*), void *context);

/*!
Return the number of sub-genre rows associated with the supplied network share
Address: The absolute or relative address of a share
*/
int df_CountSubGenresForShare(df_connection *conn, char* Address, void (*callback)(int, void*), void *context);

/*!
Return the number of tracks on the DigiFi.
*/
int df_CountTracksAll(df_connection *conn, void (*callback)(int, void*), void *context);

/*!
Return the number of tracks rows associated with the supplied device
Address: The absolute or relative address of a device
*/
int df_CountTracksForDevice(df_connection *conn, char* Address, void (*callback)(int, void*), void *context);

/*!
Return the number of tracks rows associated with the supplied album/playlist
Address: The absolute or relative address of an album or playlist
*/
int df_CountTracksForPlaylist(df_connection *conn, char* Address, void (*callback)(int, void*), void *context);

/*!
Return the number of tracks rows stored locally on the main DigiFi server.
*/
int df_CountTracksForServer(df_connection *conn, void (*callback)(int, void*), void *context);

/*!
Return the number of tracks rows associated with the supplied network share
Address: The absolute or relative address of a share
*/
int df_CountTracksForShare(df_connection *conn, char* Address, void (*callback)(int, void*), void *context);

/*!
Return the number of user playlists on the DigiFi.
*/
int df_CountUserPlaylists(df_connection *conn, void (*callback)(int, void*), void *context);

/*!
Return the number of UserPlaylists rows associated with the supplied device
Address: The absolute or relative address of a device
*/
int df_CountUserPlaylistsForDevice(df_connection *conn, char* Address, void (*callback)(int, void*), void *context);

/*!
Return the number of UserPlaylists stored locally on the main DigiFi server.
*/
int df_CountUserPlaylistsForServer(df_connection *conn, void (*callback)(int, void*), void *context);

/*!
Return the number of UserPlaylists rows associated with the supplied network share
Address: The absolute or relative address of a share
*/
int df_CountUserPlaylistsForShare(df_connection *conn, char* Address, void (*callback)(int, void*), void *context);

/*!
Create a new user-defined playlist, either populated or blank.
Name: The name to give to the new playlist.
TrackKey: The absolute or relative address(es) of a track/tracks to assign to the new playlist.
*/
int df_CreatePlaylist(df_connection *conn, char* Name, char* TrackKey, void (*callback)(int, void*), void *context);

/*!
Creates a random playlist based on the specified parameters.
RoomID: The room ID to use for this command.
Genre: The absolute or relative address of a genre to restrict the playlist by.
SubGenre: The absolute or relative address of a sub-genre to restrict the playlist by.
Artists: The absolute or relative addresses of a artists to restrict the playlist by.
Albums: The absolute or relative addresses of a albums to restrict the playlist by.
MaxTracks: The maximum number of tracks that can possibly be returned for the playlist.
Tracks: The absolute or relative addresses of tracks to restrict the playlist by.
*/
int df_CreateRandomPlaylist(df_connection *conn, int RoomID, char* Genre, char* SubGenre, char* Artists, char* Albums, int MaxTracks, char* Tracks, void (*callback)(int, void*), void *context);

/*!
Creates a random playlist based on the specified parameters.
RoomID: The room ID to use for this command.
Replace: Replace the current playlist or add to it.
PlayScope: The scope of the request: All (0), Server (1), Share (2) or Device (3)
ScopeKey: The key for the scope if PlayScope is set to device or share, this could be an abolute or relative address
SubGenre: The absolute or relative address of a sub-genre to restrict the playlist by.
Artists: The absolute or relative addresses of a artists to restrict the playlist by.
Albums: The absolute or relative addresses of a albums to restrict the playlist by.
Tracks: The absolute or relative addresses of tracks to restrict the playlist by.
*/
int df_CreateRandomPlaylistEx(df_connection *conn, int RoomID, int Replace, int PlayScope, char* ScopeKey, char* SubGenre, char* Artists, char* Albums, char* Tracks, void (*callback)(int, void*), void *context);

/*!
Delete an Album
AlbumKey: The absolute or relative address of the Album
*/
int df_DeleteAlbum(df_connection *conn, char* AlbumKey, void (*callback)(int, void*), void *context);

/*!
Delete an existing backup job. NOTE: A running job cannot be deleted.
Address: The absolute or relative address of the backup job to delete.
*/
int df_DeleteBackupJob(df_connection *conn, char* Address, void (*callback)(int, void*), void *context);

/*!
Delete a portable device from the database.
Key: The key value to use for this command.
*/
int df_DeleteDevice(df_connection *conn, int Key, void (*callback)(int, void*), void *context);

/*!
Deletes an existing system drive from the DB
DriveKey: The absolute or relative address of the Drive to be deleted
*/
int df_DeleteDrive(df_connection *conn, char* DriveKey, void (*callback)(int, void*), void *context);

/*!
Delete a Genre and all its related SubGenre's
GenreKey: The absolute or relative address of the Genre to be Deleted
*/
int df_DeleteGenre(df_connection *conn, char* GenreKey, void (*callback)(int, void*), void *context);

/*!
Delete a LinkedRoom and its related child room references
RoomKey: The absolute or relative address of the Room to be Deleted
*/
int df_DeleteLinkedRoom(df_connection *conn, char* RoomKey, void (*callback)(int, void*), void *context);

/*!
Delete an output channel from the specified host. You identify the host on which the channel is to be created by either specifying the host name or the ID of an existing room on the host.
RoomID: The room ID to use for this command. Supply EITHER a RoomID OR a HostName.
HostName: The host name (or host address) to use for this command. Supply EITHER a RoomID OR a HostName.
ChannelNumber: The number of the channel to delete. This command will fail if the channel number is not defined.
*/
int df_DeleteOutputChannel(df_connection *conn, int RoomID, char* HostName, int ChannelNumber, void (*callback)(int, void*), void *context);

/*!
Delete a Room
RoomKey: The absolute or relative address of the Room to be Deleted
*/
int df_DeleteRoom(df_connection *conn, char* RoomKey, void (*callback)(int, void*), void *context);

/*!
Delete a SubGenre
SubGenreKey: The absolute or relative address of the SubGenre to be Deleted
*/
int df_DeleteSubGenre(df_connection *conn, char* SubGenreKey, void (*callback)(int, void*), void *context);

/*!
Delete a Track from a User-Defined Playlist
TrackKey: The absolute or relative address of the Track to be Deleted
PlaylistKey: The absolute or relative address of the Playlist the Track belongs to
Ordinal: The track position/ordinal within the given playlist.
*/
int df_DeleteTrack(df_connection *conn, char* TrackKey, char* PlaylistKey, int Ordinal, void (*callback)(int, void*), void *context);

/*!
Promotes a share to a music store creating, if neccessary, the required filesystem entries. The command will fail if the share is already owned by another server and change ownership is false.
MusicStoreKey: The absolute or relative address of the music store key to demote
Deactivate: If true the commans will ensure the share is marked as inactive after the command completes irrespective of the current state of the active flag.
*/
int df_DemoteMusicStoreToShare(df_connection *conn, char* MusicStoreKey, int Deactivate, void (*callback)(df_demoteresult*, void*), void *context);

/*!
Return a string checksum of connected devices.
*/
int df_DeviceChecksum(df_connection *conn, void (*callback)(char*, void*), void *context);

/*!
Force a disconnection of a portable device.
Key: The key value to use for this command.
ClearPlaying: Clear all rooms playing from this device first?
*/
int df_DisconnectDevice(df_connection *conn, int Key, int ClearPlaying, void (*callback)(int, void*), void *context);

/*!
Cancels a scan or pending scan for the supplied external storage share.
StorageKey: The storage key value to use for this command.
*/
int df_ExternalStorageCancelScan(df_connection *conn, char* StorageKey, void (*callback)(int, void*), void *context);

/*!
Scan the network for DigiFi rooms, and update the internal rooms collection.
TimeoutPerHost: The number of ms to wait per host, before signalling a timeout.
*/
int df_FindAllRooms(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
Scan the network for DigiFi rooms, and update the internal rooms collection with any new rooms located.
TimeoutPerHost: The number of ms to wait per host, before signalling a timeout.
*/
int df_FindNewRooms(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
Force a Genre/Playlist backup on a specific Host
*/
int df_ForceGenrePlaylistBackup(df_connection *conn, void (*callback)(int, void*), void *context);

/*!
Restores Genre,Sub Genre and Playlist assignments with information from an XML file
*/
int df_ForceGenrePlaylistRestore(df_connection *conn, void (*callback)(int, void*), void *context);

/*!
Get the album and artist of the currently playing track on the selected room.
RoomID: The room ID to use for this command.
*/
int df_GetAlbumArtist(df_connection *conn, int RoomID, void (*callback)(df_albumartist*, void*), void *context);

/*!
Retrieve the current status of the system backup process.
*/
int df_GetBackupStatus(df_connection *conn, void (*callback)(df_backupstatus*, void*), void *context);

/*!
Return the number of rows cached from a previously executed numbered search
*/
int df_GetCount(df_connection *conn, void (*callback)(int, void*), void *context);

/*!
Return the name of the current operation
*/
int df_GetCurOp(df_connection *conn, void (*callback)(char*, void*), void *context);

/*!
Get the Details of a single Drive
DriveKey: The absolute or relative address of the Drive to be displayed
*/
int df_GetDriveDetail(df_connection *conn, char* DriveKey, void (*callback)(df_drivedetail*, void*), void *context);

/*!
Return the number of albums associated with the contributor, of the specified type.
Address: Single absolute or relative address of Contributor to locate albums for.
Type: Contributor Type
*/
int df_GetExtCountAlbumsByContributor(df_connection *conn, char* Address, int Type, void (*callback)(int, void*), void *context);

/*!
Return the number of albums associated with the contributor, of the specified type, for the specified external device.
Address: Single absolute or relative address of Contributor to locate albums for.
DeviceAddress: Single absolute or relative address of the external device which contains the albums.
Type: Contributor Type
*/
int df_GetExtCountAlbumsByContributorForDevice(df_connection *conn, char* Address, char* DeviceAddress, int Type, void (*callback)(int, void*), void *context);

/*!
Return the number of albums associated with the contributor, of the specified type, for the local server.
Address: Single absolute or relative address of Contributor to locate albums for.
Type: Contributor Type
*/
int df_GetExtCountAlbumsByContributorForServer(df_connection *conn, char* Address, int Type, void (*callback)(int, void*), void *context);

/*!
Return the number of albums associated with the contributor, of the specified type, for the specified external share.
Address: Single absolute or relative address of Contributor to locate albums for.
ShareAddress: Single absolute or relative address of the external share which contains the albums.
Type: Contributor Type
*/
int df_GetExtCountAlbumsByContributorForShare(df_connection *conn, char* Address, char* ShareAddress, int Type, void (*callback)(int, void*), void *context);

/*!
Return the number of contributors of the specified type.
Type: Contributor Type
*/
int df_GetExtCountContributors(df_connection *conn, int Type, void (*callback)(int, void*), void *context);

/*!
Return the number of contributors of the specified type on a given attached portable device.
Address: The absolute or relative address of a device
Type: Contributor Type
*/
int df_GetExtCountContributorsForDevice(df_connection *conn, char* Address, int Type, void (*callback)(int, void*), void *context);

/*!
Return the number of contributors of the specified type stored locally on the main DigiFi server.
Type: Contributor Type
*/
int df_GetExtCountContributorsForServer(df_connection *conn, int Type, void (*callback)(int, void*), void *context);

/*!
Return the number of contributors of the specified type on a given attached network share.
Address: The absolute or relative address of a share
Type: Contributor Type
*/
int df_GetExtCountContributorsForShare(df_connection *conn, char* Address, int Type, void (*callback)(int, void*), void *context);

/*!
Get the Details of a single external storage share
StorageKey: The absolute or relative address of the external storage share to be fetched
*/
int df_GetExternalStorageDetail(df_connection *conn, char* StorageKey, void (*callback)(df_extstoragedetail*, void*), void *context);

/*!
Get the details of a drive, given it's drive letter, obtained by examining the file system.
DriveLetter: The drive letter of the drive to obtain the details for.
*/
int df_GetFileSystemDriveDetail(df_connection *conn, char* DriveLetter, void (*callback)(df_fsdrivedetail*, void*), void *context);

/*!
Get the Details of a single Genre
GenreKey: The absolute or relative address of the Genre to be displayed
*/
int df_GetGenreDetail(df_connection *conn, char* GenreKey, void (*callback)(df_genre*, void*), void *context);

/*!
Retrieve the host name and working IP address from the Sophia host.
*/
int df_GetHostDetails(df_connection *conn, void (*callback)(df_hostdetails*, void*), void *context);

/*!
Return the error text associated with the last error on this connection
*/
int df_GetLastError(df_connection *conn, void (*callback)(char*, void*), void *context);

/*!
Returns a checksum which indicates changes to data in the Artist, Album and Track tables
RoomID: The room ID to use for this command.
*/
int df_GetLibraryCheckSum(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context);

/*!
Return the current SMB workgroup, of which the DigiFi device is a member.
*/
int df_GetNetworkWorkgroup(df_connection *conn, void (*callback)(char*, void*), void *context);

/*!
Returns the activity of a long operation
RoomID: The room ID to use for this command.
Service: 1 = Astoria, 2 = Ripping, 3 = Encoding
*/
int df_GetOperationActivity(df_connection *conn, int RoomID, int Service, void (*callback)(char*, void*), void *context);

/*!
Get the current player status in the selected room.
RoomID: The room ID to use for this command.
*/
int df_GetPlayerStatus(df_connection *conn, int RoomID, void (*callback)(char*, void*), void *context);

/*!
Get the current player version number.
RoomID: The room ID to use for this command.
*/
int df_GetPlayerVersion(df_connection *conn, int RoomID, void (*callback)(char*, void*), void *context);

/*!
Get the status of the repeat flag in the selected room.
RoomID: The room ID to use for this command.
*/
int df_GetRepeat(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context);

/*!
Lists the details for a single room
RoomKey: The absolute or relative address of the Room details to be displayed
*/
int df_GetRoomDetail(df_connection *conn, char* RoomKey, void (*callback)(df_room*, void*), void *context);

/*!
Retrieve a number of rows from a previously executed numbered search
StartRow: The number of the first row returned. Use 1 to start at the beginning of the results
RowCount: The number of rows to return with this command call. Use -1 to return all rows following the specified start row
FormatList: The name of the format list to use for formatting results
*/
int df_GetRows(df_connection *conn, int StartRow, int RowCount, char* FormatList, void (*callback)(int, void*), void *context);

/*!
Retrieve the offset of a row in a previously executed numbered search which matches a criteria
SearchValue: The string to search for
SearchColumn: The name of the column to match within the search results. An error is returned if the column does not exist in the specified search.
SearchType: Type of search: 1=Contains, 2=Starts With (default), 3=Exact Match, 4=Does Not Contain, 5=Range
*/
int df_GetSearchOffset(df_connection *conn, char* SearchValue, char* SearchColumn, int SearchType, void (*callback)(df_searchoffset*, void*), void *context);

/*!
Return a setup confirmation checksum
*/
int df_GetSetupVal(df_connection *conn, void (*callback)(int, void*), void *context);

/*!
Get the status of the shuffle flag in the selected room.
RoomID: The room ID to use for this command.
*/
int df_GetShuffle(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context);

/*!
Get a single Ripping/Encoding setting for a specified room
RoomID: The room ID to use for this command
SettingName: The Setting name or relative address of the setting to be fetched
*/
int df_GetSingleRipEncSetting(df_connection *conn, int RoomID, char* SettingName, void (*callback)(char*, void*), void *context);

/*!
Get a single System setting for a specified room
RoomID: The room ID to use for this command
SettingName: The Setting name or relative address of the setting to be fetched
*/
int df_GetSingleSystemSetting(df_connection *conn, int RoomID, char* SettingName, void (*callback)(char*, void*), void *context);

/*!
Lists the detail of a single Status Message
Key: Absolute or relative address of the Message to view
*/
int df_GetStatusMessageDetail(df_connection *conn, char* Key, void (*callback)(df_messagedetail*, void*), void *context);

/*!
Get the Details of a single SubGenre
SubGenreKey: The absolute or relative address of the SubGenre to be displayed
*/
int df_GetSubGenreDetail(df_connection *conn, char* SubGenreKey, void (*callback)(df_subgenre*, void*), void *context);

/*!
Retrieve the current system (device) date and time.
*/
int df_GetSystemTime(df_connection *conn, void (*callback)(df_systemtime*, void*), void *context);

/*!
Get the number of tracks in the currently playing playlist/CD.
RoomID: The room ID to use for this command.
*/
int df_GetTrackCount(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context);

/*!
Get the details of the specified track directly from the player..
RoomID: The room ID to use for this command.
TrackPath: The path/URL of the track for which details will be returned..
*/
int df_GetTrackDetailsFromPlayer(df_connection *conn, int RoomID, char* TrackPath, void (*callback)(df_trackfromplayer*, void*), void *context);

/*!
Get the length of the currently playing track in the selected room.
RoomID: The room ID to use for this command.
*/
int df_GetTrackLength(df_connection *conn, int RoomID, void (*callback)(df_time, void*), void *context);

/*!
Get the name of the currently playing track on the selected room.
RoomID: The room ID to use for this command.
*/
int df_GetTrackName(df_connection *conn, int RoomID, void (*callback)(df_trkname*, void*), void *context);

/*!
Get the track offset (within the track list) of the currently playing track.
RoomID: The room ID to use for this command.
*/
int df_GetTrackNum(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context);

/*!
Get the current play position/location within the current track.
RoomID: The room ID to use for this command.
*/
int df_GetTrackPosition(df_connection *conn, int RoomID, void (*callback)(df_time, void*), void *context);

/*!
Get the player volume level from the selected room.
RoomID: The room ID to use for this command.
*/
int df_GetVolume(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context);

/*!
Sets a share or host to be ignored by the share scanning system
StorageKey: The storage key value to use for this command.
IgnoreLevel: How the resources will be ingnored can be one of 3 values. Zero ignored flag is turned off for share or host, One share will be set to be ignored or Two host will be set to be ignored.
*/
int df_IgnoreExternalStorage(df_connection *conn, char* StorageKey, int IgnoreLevel, void (*callback)(int, void*), void *context);

/*!
Determine whether a CD is playing on the selected room.
RoomID: The room ID to use for this command.
*/
int df_IsCDPlaying(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context);

/*!
Return the error text associated with the supplied error number
ErrorCode: The error number to use
*/
int df_LookupError(df_connection *conn, int ErrorCode, void (*callback)(char*, void*), void *context);

/*!
Returns the current status of the move album daemon in Astoria.
*/
int df_MoveAlbumGetStatus(df_connection *conn, void (*callback)(df_movealbumstatus*, void*), void *context);

/*!
Moves an album from its current music store to another music store
Address: The absolute or relative addresses of the albums to move.
MusicStoreKey: The key of the music store the album will be moved to
*/
int df_MoveAlbumToMusicStore(df_connection *conn, char* Address, char* MusicStoreKey, void (*callback)(int, void*), void *context);

/*!
Create a new output channel on the specified host. You identify the host on which the channel is to be created by either specifying the host name or the ID of an existing room on the host.
RoomID: The room ID to use for this command. Supply EITHER a RoomID OR a HostName.
HostName: The host name (or host address) to use for this command. Supply EITHER a RoomID OR a HostName.
ChannelNumber: The number of the new channel to create. This command will fail if the channel number is already in use.
InitString: The initialisation string to use for this channel. The initialisation string describes the device associated with the channel.
*/
int df_NewOutputChannel(df_connection *conn, int RoomID, char* HostName, int ChannelNumber, char* InitString, void (*callback)(int, void*), void *context);

/*!
Move to the next track in the current playlist on a specified room
RoomID: The room ID to use for this command.
*/
int df_NextTrack(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context);

/*!
Submit an album/playlist for playback on a specified room, either replacing the current playlist or adding to it.
RoomID: The room ID to use for this command.
Replace: Replace the current playlist or add to it.
Address: The absolute or relative address of an album/playlist to search.
StartTrack: The track number to start playback from.
*/
int df_PlayAlbum(df_connection *conn, int RoomID, int Replace, char* Address, int StartTrack, void (*callback)(int, void*), void *context);

/*!
Submit album/playlist(s) for playback on a specified room, either replacing the current playlist or adding to it.
RoomID: The room ID to use for this command.
Replace: Replace the current playlist or add to it.
Address: The absolute or relative address of album/playlist(s) to play.
*/
int df_PlayAlbums(df_connection *conn, int RoomID, int Replace, char* Address, void (*callback)(int, void*), void *context);

/*!
Submit all tracks from an album/playlist search for playback on a specified room, either replacing the current playlist or adding to it.
RoomID: The room ID to use for this command.
Replace: Replace the current playlist or add to it.
*/
int df_PlayAlbumsFromSearch(df_connection *conn, int RoomID, int Replace, void (*callback)(int, void*), void *context);

/*!
Plays all items in a group i.e. Albums, Artists, Genres etc.
RoomID: The room ID to use for this command.
Replace: Replace the current playlist or add to it.
PlayScope: The scope of the request: All (0), Server (1), Share (2) or Device (3)
ScopeKey: The key for the scope if PlayScope is set to device or sharthis could be a relative or absolute address
PlayType: The type of entries to play: Artists (0), Albums (1), Genres (2), Performers (3), Playlists (4), Conductors (5) or Composers (6)
Address: The absolute or relative address of album/playlist(s) to play.
*/
int df_PlayAll(df_connection *conn, int RoomID, int Replace, int PlayScope, char* ScopeKey, int PlayType, char* Address, void (*callback)(int, void*), void *context);

/*!
Play a particular artist/album combination on a specified room.
RoomID: The room ID to use for this command.
Artist: The name of the artist to filter on.
Album: The album title to filter on.
Randomise: Randomise tracks before playing?
OnErrorBehaviour: If an error occurs: 1 = Play Nothing, 2 = Play Random (all albums).
*/
int df_PlayArtistAlbum(df_connection *conn, int RoomID, char* Artist, char* Album, int Randomise, int OnErrorBehaviour, void (*callback)(int, void*), void *context);

/*!
Play the last played album on a specified room.
RoomID: The room ID to use for this command.
Randomise: Randomise tracks before playing?
Number: Number of most recently played albums to select. These will be selected in descending order of most recently played. Defaults to 1.
*/
int df_PlayLastPlayed(df_connection *conn, int RoomID, int Randomise, int Number, void (*callback)(int, void*), void *context);

/*!
Play the last album ripped on a specified room.
RoomID: The room ID to use for this command.
Randomise: Randomise tracks before playing?
Number: Number of most recently ripped albums to select. These will be selected in descending order of date/time ripped. Defaults to 1.
*/
int df_PlayLastRipped(df_connection *conn, int RoomID, int Randomise, int Number, void (*callback)(int, void*), void *context);

/*!
Play the most popular album on a specified room.
RoomID: The room ID to use for this command.
Randomise: Randomise tracks before playing?
Number: Number of most popular albums to select. These will be selected in descending order of popularity. Defaults to 1.
*/
int df_PlayMostPopular(df_connection *conn, int RoomID, int Randomise, int Number, void (*callback)(int, void*), void *context);

/*!
Submit a playlist for playback on a specified room.
RoomID: The room ID to use for this command.
PlaylistName: The name of the playlist to play.
Randomise: Randomise tracks before playing?
OnErrorBehaviour: If an error occurs: 1 = Play Nothing, 2 = Play Random (all albums).
*/
int df_PlayPlaylist(df_connection *conn, int RoomID, char* PlaylistName, int Randomise, int OnErrorBehaviour, void (*callback)(int, void*), void *context);

/*!
Generate a random playlist on a specified room for the specified genre/sub-genre.
RoomID: The room ID to use for this command.
Genre: The name of the genre to filter on.
SubGenre: The name of the sub-genre to filter on.
OnErrorBehaviour: If an error occurs: 1 = Play Nothing, 2 = Play Random (all albums).
*/
int df_PlayRandom(df_connection *conn, int RoomID, char* Genre, char* SubGenre, int OnErrorBehaviour, void (*callback)(int, void*), void *context);

/*!
Submit a track for playback on a specified room, either replacing the current playlist or adding to it.
RoomID: The room ID to use for this command.
Replace: Replace the current playlist or add to it.
Address: The absolute or relative address of a track to search.
*/
int df_PlayTrack(df_connection *conn, int RoomID, int Replace, char* Address, void (*callback)(int, void*), void *context);

/*!
Submit a list of tracks for playback on a specified room, either replacing the current playlist or adding to it.
RoomID: The room ID to use for this command.
Replace: Replace the current playlist or add to it.
Address: The absolute or relative addresses of tracks to add.
StartTrack: The track number to start playback from.
*/
int df_PlayTracks(df_connection *conn, int RoomID, int Replace, char* Address, int StartTrack, void (*callback)(int, void*), void *context);

/*!
Submit all tracks from a track search for playback on a specified room, either replacing the current playlist or adding to it.
RoomID: The room ID to use for this command.
Replace: Replace the current playlist or add to it.
StartTrack: The track number to start playback from.
*/
int df_PlayTracksFromSearch(df_connection *conn, int RoomID, int Replace, int StartTrack, void (*callback)(int, void*), void *context);

/*!
Submit an URL for playback on a specified room, either replacing the current playlist or adding to it.
RoomID: The room ID to use for this command.
Replace: Replace the current playlist or add to it.
Url: The URL to play.
*/
int df_PlayUrl(df_connection *conn, int RoomID, int Replace, char* Url, void (*callback)(int, void*), void *context);

/*!
Submit a set of URLs for playback on a specified room, either replacing the current playlist or adding to it.
RoomID: The room ID to use for this command.
Replace: Replace the current playlist or add to it.
Urls: The URLs to be played.
StartTrack: The track number to start playback from.
*/
int df_PlayUrls(df_connection *conn, int RoomID, int Replace, char* Urls, int StartTrack, void (*callback)(int, void*), void *context);

/*!
Move to the previous track in the current playlist on a specified room
RoomID: The room ID to use for this command.
*/
int df_PrevTrack(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context);

/*!
Force the device to process the embedded initialisation file. This command is for internal use and not expected to be called for any other purpose.
*/
int df_ProcessEmbeddedInit(df_connection *conn, void (*callback)(char*, void*), void *context);

/*!
Promotes a share to a music store creating, if neccessary, the required filesystem entries. The command will fail if the share is already owned by another server and change ownership is false.
ShareKey: The absolute or relative address of the share to promote
ChangeOwnership: If true the command will forcibly take owenership of the music store irrecpective of the content of the control file.
*/
int df_PromoteShareToMusicStore(df_connection *conn, char* ShareKey, int ChangeOwnership, void (*callback)(df_promoteshare*, void*), void *context);

/*!
Query the status of all playback results.
RoomID: The room ID to use for this command.
*/
int df_QueryAllPlayback(df_connection *conn, int RoomID, void (*callback)(df_queryplayback*, void*), void *context);

/*!
Releases any clients connected to Sophia through the serial port. After the serial ports are released Sophia will broadcast the following custom windows message; "SOPHIA HAS ENTERED SERVICE MODE"
*/
int df_ReleaseSerialPort(df_connection *conn, void (*callback)(int, void*), void *context);

/*!
Remove all tracks from the given Album(s) from a user defined playlist
UserPlaylistKey: The absolute or relative address of the playlist to have tracks removed
AlbumKey: The absolute or relative addresses of the Album(s) to remove from the playlist (Space sperated)
*/
int df_RemoveAlbumsFromUserPlaylist(df_connection *conn, char* UserPlaylistKey, char* AlbumKey, void (*callback)(int, void*), void *context);

/*!
Remove a cover image for the specified album.
Address: The absolute or relative address of the album whose cover image will be deleted.
*/
int df_RemoveCoverImage(df_connection *conn, char* Address, void (*callback)(char*, void*), void *context);

/*!
Removes the record of an offline external storage share. This command will fail if the external storage share is flagged as online.
StorageKey: The storage key value to use for this command.
*/
int df_RemoveExternalStorage(df_connection *conn, int StorageKey, void (*callback)(int, void*), void *context);

/*!
Scan the network for DigiFi rooms, remove from the internal rooms collection any rooms which do not respond.
TimeoutPerHost: The number of ms to wait per host, before signalling a timeout.
*/
int df_RemoveOldRooms(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);

/*!
Remove a player instance from a given room.
RoomID: The room ID to use for this command.
Key: The instance key to use for this command.
*/
int df_RemovePlayerInstance(df_connection *conn, int RoomID, int Key, void (*callback)(int, void*), void *context);

/*!
Remove the specified track from the current playlist in the specified room
RoomID: The room ID to use for this command.
TrackNumber: The track number to use for this command.
*/
int df_RemoveTrack(df_connection *conn, int RoomID, int TrackNumber, void (*callback)(int, void*), void *context);

/*!
Rename a specified album's name
AlbumKey: The absolute or relative address of the album to be changed
NewAlbumName: The new albums name
*/
int df_RenameAlbum(df_connection *conn, char* AlbumKey, char* NewAlbumName, void (*callback)(char*, void*), void *context);

/*!
Rename a specified Artist Name
AlbumKey: The absolute or relative address of the album to be changed
NewArtistName: The new Artist Name
*/
int df_RenameArtist(df_connection *conn, char* AlbumKey, char* NewArtistName, void (*callback)(char*, void*), void *context);

/*!
Rename a user-defined playlist.
PlaylistKey: The absolute or relative address of a playlist to rename.
NewName: The name to give to the playlist.
*/
int df_RenamePlaylist(df_connection *conn, char* PlaylistKey, char* NewName, void (*callback)(int, void*), void *context);

/*!
Rename a specified Track Name
TrackKey: The absolute or relative address of a Track to be changed
NewTrackName: The new Track Name
*/
int df_RenameTrack(df_connection *conn, char* TrackKey, char* NewTrackName, void (*callback)(char*, void*), void *context);

/*!
Send a request to the remote administration site for the specified album cover to be sent to the DigiFi (rather than waiting for an overnight run)
Address: The absolute or relative address of the album to fetch the cover for.
*/
int df_RequestAlbumCover(df_connection *conn, char* Address, void (*callback)(int, void*), void *context);

/*!
Schedules a rescan of external storage shares and updates the database accordingly.
*/
int df_RescanExternalStorages(df_connection *conn, void (*callback)(int, void*), void *context);

/*!
Requests a full rescan of the specified music store.
MusicStoreKey: The absolute or relative address of the music store to rescan.
*/
int df_RescanMusicStore(df_connection *conn, char* MusicStoreKey, void (*callback)(df_rescanresult*, void*), void *context);

/*!
Restore a single specified album that was listed for Deletion
AlbumKey: The absolute or relative address of the album to be restored
*/
int df_RestoreSingleAlbum(df_connection *conn, char* AlbumKey, void (*callback)(int, void*), void *context);

/*!
Restore a single specified track off an album that was listed for Deletion
AlbumKey: The absolute or relative address of the parent album
TrackKey: The absolute or relative address of the track to be restored
*/
int df_RestoreSingleTrack(df_connection *conn, char* AlbumKey, char* TrackKey, void (*callback)(int, void*), void *context);

/*!
Save the tracks in the current playlist to a new playlist
RoomID: The room ID to use for this command.
NewName: The name to use for the new playlist.
*/
int df_SaveCurrentPlayList(df_connection *conn, int RoomID, char* NewName, void (*callback)(int, void*), void *context);

/*!
Save a player instance on a given room.
RoomID: The room ID to use for this command.
Key: The instance key to use for this command.
OutputDeviceID: The output device ID for the instance.
SourceLineID: The source line ID for the instance.
*/
int df_SavePlayerInstance(df_connection *conn, int RoomID, int Key, int OutputDeviceID, int SourceLineID, void (*callback)(int, void*), void *context);

/*!
Forces a share scan on a given external storage share and updates the database accordingly.
StorageKey: The absolute or relative address of the external storage share to be fetched
*/
int df_ScanExternalStorage(df_connection *conn, char* StorageKey, void (*callback)(int, void*), void *context);

/*!
Scans the network for external storage shares and updates the database accordingly.
*/
int df_ScanForExternalStorages(df_connection *conn, void (*callback)(int, void*), void *context);

/*!
Return the details of the current mode in which the service is operating (full mode, demo mode etc)
*/
int df_ServiceMode(df_connection *conn, void (*callback)(df_servicemode*, void*), void *context);

/*!
Toggle the low quality flag for a specified album
AlbumKey: The absolute or relative address of the album to be changed
LowQuality: Low quality flag
*/
int df_SetAlbumLowQuality(df_connection *conn, char* AlbumKey, int LowQuality, void (*callback)(int, void*), void *context);

/*!
Uploads a new image for an album.
Address: The absolute or relative address of the album to upload cover art for.
ForceOverwrite: If true the image will always be overwritten, if false the command will not overwrite existing image files
ImageData: A serialized version of the image file contents where each byte is represented as a 2 digit hex value
*/
int df_SetCoverImage(df_connection *conn, char* Address, int ForceOverwrite, char* ImageData, void (*callback)(char*, void*), void *context);

/*!
Changes the usage of a drive, between audio store and backup.
DriveKey: The absolute or relative address of the drive to modify.
Usage: The new usage for the drive. This can be 0 (Audio store) or 1 (Backup).
ForceChange: If this is false then the usage of the drive will be changed if it is unused. If the drive is in use then the command will fail. If this is set to true then the usage will be applied regardless of drive status.
*/
int df_SetDriveUsage(df_connection *conn, char* DriveKey, int Usage, int ForceChange, void (*callback)(df_driveusageresult*, void*), void *context);

/*!
Sets the username and password required for a music store.
MusicStoreKey: The absolute or relative address of the music store to set the username and password for
Username: Name of the user to set
Password: Password to use
*/
int df_SetMusicStoreCredentials(df_connection *conn, char* MusicStoreKey, char* Username, char* Password, void (*callback)(int, void*), void *context);

/*!
Sets the priority of the music store for newly ripped music.
MusicStoreKey: The absolute or relative address of the music store to set the priority of.
Priority: The priority to set. -1 for read-only, actual value assigned may be different from requested as priorities (other thane read-only) are kept contiguous.
*/
int df_SetMusicStorePriority(df_connection *conn, char* MusicStoreKey, int Priority, void (*callback)(df_musicstorepriorityresult*, void*), void *context);

/*!
Attempt to stop the current drive backup process.
*/
int df_StopBackupDrive(df_connection *conn, void (*callback)(df_stopbackupdriveresult*, void*), void *context);

/*!
Set the Synchronisation setting on a portable device in the database.
Key: The key value to use for this command.
Sync: Synchronisation setting to use.
*/
int df_ToggleDeviceSync(df_connection *conn, int Key, int Sync, void (*callback)(int, void*), void *context);

/*!
Update an existing backup job. NOTE: A running job cannot be updated.
Address: The absolute or relative address of the backup job to update.
SourceDriveAddress: The absolute or relative address of the Drive to back up music from.
DestinationDriveAddress: The absolute or relative address of the Drive to back up music to.
Name: The name of to give the backup job (can be empty).
BackupType: The type of backup being scheduled (0 - full backup, 1 - differential backup).
BackupPeriod: A value which determines how often the backup job will run (0 - once only, 1 - daily, 2 - weekly, 3 - monthly).
PeriodValue: A value which indicates when in the given period the backup job will run. Day of the week for weeklies, day of the month for monthlies, ignored for run once jobs.
RunDate: The date on which the job will be run. This is only used by run once jobs, to construct the next run date.
RunTime: The time at which the job will be run. This is used to construct the next run date and time for all job types.
*/
int df_UpdateBackupJob(df_connection *conn, char* Address, char* SourceDriveAddress, char* DestinationDriveAddress, char* Name, int BackupType, int BackupPeriod, int PeriodValue, df_date RunDate, df_time RunTime, void (*callback)(int, void*), void *context);

/*!
Updates an existing system drive to the DB
DriveKey: The absolute or relative address of the Drive to be Updated
DriveLetter: The Name you want to assign to the new Drive
PrimaryDrive: Specify if the new Drive should be set to Primary
RootPath: Combined with the Drive Letter, Root Path is the Local Path
SharePath: The address of where the music share is
BadPathBehaviour: Determines how the command will handle a non-existent root path. 0 = [None] Command returns error (default), 1 = [Ignore] Command will ignore a bad path and save the row regardless, 2 = [Create] The command will attempt to create the root path .
*/
int df_UpdateDrive(df_connection *conn, char* DriveKey, char* DriveLetter, int PrimaryDrive, char* RootPath, char* SharePath, int BadPathBehaviour, void (*callback)(df_updatedrivedetails*, void*), void *context);

/*!
Updates the details of an existing external storage share. Note: Data elements which are under the control of the ScanManager cannot be modified using this command.
StorageKey: The absolute or relative address of the external storage share to be Updated
IPAddress: The IP Address of the host which provides the share.
HostName: The name of the host which provides the share.
ShareName: The name of the share.
UserName: User name required to access the host/share.
Password: Password required to access the host/share.
*/
int df_UpdateExternalStorage(df_connection *conn, char* StorageKey, char* IPAddress, char* HostName, char* ShareName, char* UserName, char* Password, void (*callback)(int, void*), void *context);

/*!
Updates an existing Genre
GenreKey: Key Value of Genre to be Updated
GenreName: The new Genre name you want to assign
Ordinal: The new position in the list of Genres
*/
int df_UpdateGenre(df_connection *conn, char* GenreKey, char* GenreName, int Ordinal, void (*callback)(int, void*), void *context);

/*!
Increment the hit count of one or more albums, or reset the hit count of all albums in the library.
Address: The absolute or relative address of the albums to be updated. This can also be the value ALL, if using this command to reset the hit count of all albums.
ResetHitCount: If this is true and the Address is ALL, then the command will reset the hit count of all albums. Otherwise this parameter will be ignored.
*/
int df_UpdateHitCount(df_connection *conn, char* Address, int ResetHitCount, void (*callback)(int, void*), void *context);

/*!
Update a linked room and its child(ren) room(s)
RoomKey: The absolute or relative address of a Linked Room to update
RoomName: The Name of the linked Room
ShortName: Linked rooms short name(3 characters)
RoomID: An ID used to determine the Room
ChildRoomKey: The absolute or relative addresses of a Child Room to be linked with the room (space seperated)
*/
int df_UpdateLinkedRoom(df_connection *conn, char* RoomKey, char* RoomName, char* ShortName, int RoomID, char* ChildRoomKey, void (*callback)(int, void*), void *context);

/*!
Update an output channel on the specified host. You identify the host on which the channel is to be created by either specifying the host name or the ID of an existing room on the host.
RoomID: The room ID to use for this command. Supply EITHER a RoomID OR a HostName.
HostName: The host name (or host address) to use for this command. Supply EITHER a RoomID OR a HostName.
ChannelNumber: The number of the channel to update. This command will fail if the channel number is not defined.
InitString: The initialisation string to use for this channel. The initialisation string describes the device associated with the channel.
*/
int df_UpdateOutputChannel(df_connection *conn, int RoomID, char* HostName, int ChannelNumber, char* InitString, void (*callback)(int, void*), void *context);

/*!
Updates an existing user-defined playlist, using the name and tracks supplied.
PlaylistKey: The absolute or relative address of the Playlist to update.
Name: The name for the playlist.
TrackKey: The absolute or relative address(es) of a track/tracks to assign to the playlist. Any other tracks on the playlist will be removed.
*/
int df_UpdatePlaylist(df_connection *conn, char* PlaylistKey, char* Name, char* TrackKey, void (*callback)(int, void*), void *context);

/*!
Update a room
RoomKey: The absolute or relative address of the Room to be updated
RoomIP: The IP address of the Room
Channel: The Channel of the room
RoomName: The unique name of the linked Room
ShortName: Rooms unique short name(3 characters)
PlaybackCapability: If the room has playback capability
RippingCapability: If the room has ripping capability
MusicManagementCapability: If the room has music management capability
RoomID: A unique ID used to determine the Room
HostName: The network name of the host which provides the room.
*/
int df_UpdateRoom(df_connection *conn, char* RoomKey, char* RoomIP, int Channel, char* RoomName, char* ShortName, int PlaybackCapability, int RippingCapability, int MusicManagementCapability, int RoomID, char* HostName, void (*callback)(int, void*), void *context);

/*!
Update a Single Ripping/Encoding setting Value for a specified room
RoomID: The room ID to use for this command
SettingName: The Setting name or relative address of the setting to be updated
NewValue: The Settings new value
*/
int df_UpdateSingleRipEncSetting(df_connection *conn, int RoomID, char* SettingName, char* NewValue, void (*callback)(char*, void*), void *context);

/*!
Update a single System setting for a specified room
RoomID: The room ID to use for this command
SettingName: The Setting name or relative address of the setting to be updated
NewValue: The Settings new value
*/
int df_UpdateSingleSystemSetting(df_connection *conn, int RoomID, char* SettingName, char* NewValue, void (*callback)(char*, void*), void *context);

/*!
Updates an existing SubGenre
SubGenreKey: The absolute or relative address of the SubGenre to be Updated
GenreKey: The absolute or relative address of a Genre to be associated with the SubGenre
SubGenreName: The new SubGenre name you want to assign
Ordinal: The new position in the list of SubGenres
*/
int df_UpdateSubGenre(df_connection *conn, char* SubGenreKey, char* GenreKey, char* SubGenreName, int Ordinal, void (*callback)(int, void*), void *context);

/*!
Forces an upload of messages to central admin site
*/
int df_UploadMessages(df_connection *conn, void (*callback)(int, void*), void *context);

/*!
Return the version of the service component and the supported protocol version
*/
int df_Version(df_connection *conn, void (*callback)(df_version*, void*), void *context);

/*!
Adds or Removes a node to/from the favourites folder
vTunerUrl: The vTuner URL to use for adding or removing the node to/from the favourites folder.
*/
int df_vTunerAddRemoveFavourite(df_connection *conn, char* vTunerUrl, void (*callback)(int, void*), void *context);

/*!
Checks to see if either the primary or backup vTuner servers are available
*/
int df_vTunerCheckAvailability(df_connection *conn, void (*callback)(int, void*), void *context);

/*!
Submit an station, show or episode for playback on a specified room by using its vTuner ID, either replacing the current playlist or adding to it.
RoomID: The room ID to use for this command.
Replace: Replace the current playlist or add to it.
Address: The absolute or relative address of the station, show or episode to play
*/
int df_vTunerPlayById(df_connection *conn, int RoomID, int Replace, char* Address, void (*callback)(int, void*), void *context);

/*!
Submit a list of station, show or episode ID's for playback on a specified room by using its vTuner ID, either replacing the current playlist or adding to it.
RoomID: The room ID to use for this command.
Replace: Replace the current playlist or add to it.
Address: The absolute or relative addresses of the stations, shows or episodes to play
*/
int df_vTunerPlayByIds(df_connection *conn, int RoomID, int Replace, char* Address, void (*callback)(int, void*), void *context);

/*!
Sets a preset channel to the supplied station, show or episode id.
ChannelNumber: The channel number to assing to, -1 for auto assignment
VTunerID: The station, show or episode ID to assign to the channel
ChannelName: The descriptive name of the station, show or episode that is to be assinged to the channel
*/
int df_vTunerSetPresetChannel(df_connection *conn, int ChannelNumber, char* VTunerID, char* ChannelName, void (*callback)(int, void*), void *context);





// Set commands

/*!
Cancels a request to perform a cd lookup
Address: The absolute or relative address of the queue keys that identify the album request
*/
int df_CDLookupCancel(df_connection *conn, char* Address);

/*!
Change a Single CDDB SubGenre Association
GenreKey: The absolute or relative address of the Genre's SubGenre to be changed
NewSubGenreKey: The absolute or relative address of the new SubGenre key to be associated with the Genre
*/
int df_ChangeCDDBSubGenreAssociation(df_connection *conn, char* GenreKey, char* NewSubGenreKey);

/*!
Clear all now playing tracklists in all rooms.
*/
int df_ClearAllPlaying(df_connection *conn);

/*!
Empty the download folder on the specified host
RoomID: The room ID to use for this command.
*/
int df_ClearDownloadFolder(df_connection *conn, int RoomID);

/*!
Clear current playlist on a specified room
RoomID: The room ID to use for this command.
*/
int df_ClearPlaylist(df_connection *conn, int RoomID);

/*!
Disable a field for a specified format list
FormatList: The ID of the format list to use
FieldName: The name of the field to disable/hide
*/
int df_DisableField(df_connection *conn, char* FormatList, char* FieldName);

/*!
Eject a currently playing CD on a specified room
RoomID: The room ID to use for this command.
*/
int df_EjectCD(df_connection *conn, int RoomID);

/*!
Remove all tracks and albums marked for deletion from the database
*/
int df_EmptyRecycleBin(df_connection *conn);

/*!
Empty the uploads folder on a specified host
RoomID: The room ID to use for this command.
*/
int df_EmptyRipShare(df_connection *conn, int RoomID);

/*!
Enable a field for a specified format list
FormatList: The ID of the format list to use
FieldName: The name of the field to enable/show
*/
int df_EnableField(df_connection *conn, char* FormatList, char* FieldName);

/*!
Fast forward through currently playing track on a specified room
RoomID: The room ID to use for this command.
*/
int df_FastForward(df_connection *conn, int RoomID);

/*!
Fast rewind through currently playing track on a specified room
RoomID: The room ID to use for this command.
*/
int df_FastRewind(df_connection *conn, int RoomID);

/*!
Force a remote Database to rebuild on a specific host the next time the services restart.
*/
int df_ForceDBRebuild(df_connection *conn);

/*!
Perform an upgrade for a specific host
RoomID: The room ID to use for this command.
*/
int df_ForceHostUpgrade(df_connection *conn, int RoomID);

/*!
[Internal] Used by back end services to indicate that the master IP address has changed.
MasterName: The host name of the DigiFi Master
MasterAddress: The IP address of the DigiFi Master
*/
int df_MasterIpChanged(df_connection *conn, char* MasterName, char* MasterAddress);

/*!
Cancels a request to move an album
Address: The absolute or relative address of the queue keys that identify the move album request
*/
int df_MoveAlbumCancel(df_connection *conn, char* Address);

/*!
Pause current playback on a specified room
RoomID: The room ID to use for this command.
*/
int df_Pause(df_connection *conn, int RoomID);

/*!
Start current playback on a specified room
RoomID: The room ID to use for this command.
*/
int df_Play(df_connection *conn, int RoomID);

/*!
Purge the image cache on a specific host
All: Perform purge across all cover art or only those which have been generated.
*/
int df_PurgeImageCache(df_connection *conn, int All);

/*!
Randomly re-order the current playlist on a specified room
RoomID: The room ID to use for this command.
*/
int df_RandomisePlaylist(df_connection *conn, int RoomID);

/*!
Restart the DigiFi device.
*/
int df_RestartDevice(df_connection *conn);

/*!
[Internal] Used by back end services to indicate that one or more room IP addresses have changed.
*/
int df_RoomIpChanged(df_connection *conn);

/*!
[Internal] Used by back-end ripping services to set the CD detected flag
CDDetected: CD detected flag
*/
int df_SetCDDetected(df_connection *conn, int CDDetected);

/*!
Change a connection option
OptionName: The name of the option to change. Currently supported options: FullErrors
OptionValue: The new value for the option
*/
int df_SetConnOption(df_connection *conn, char* OptionName, char* OptionValue);

/*!
Set the returned length of a field associated with a format list
FormatList: The ID of the format list to use
FieldName: The name of the field to format
Length: The maximum string length to set for this field
*/
int df_SetLength(df_connection *conn, char* FormatList, char* FieldName, int Length);

/*!
Toggle repeat on a specified room
RoomID: The room ID to use for this command.
Repeat: The repeat status to use for this command.
*/
int df_SetRepeat(df_connection *conn, int RoomID, int Repeat);

/*!
[Internal] Used by back-end ripping services to set the status of the current ripping operation
Artist: Name of the artist
Album: Name of the album
Tracks: Number of tracks on the CD
TracksRipped: Number of tracks ripped so far
Errors: Number of errors encountered so far
TimeTaken: Time taken so far
TimeLeft: Estimated time remaining to rip the CD
Track: Name of the current track being ripped
TrackPercent: Percentage of current track ripped
UserMessage: Any user messages generated by the ripping operation
LookupProviderUsed: The name of the CD lookup provider that returned information about the CD
SourceFolder: The ripping source folder name
*/
int df_SetRippingStatus(df_connection *conn, char* Artist, char* Album, int Tracks, int TracksRipped, int Errors, df_time TimeTaken, df_time TimeLeft, char* Track, int TrackPercent, char* UserMessage, char* LookupProviderUsed, char* SourceFolder);

/*!
Toggle shuffle on a specified room
RoomID: The room ID to use for this command.
Shuffle: The value to use for this command.
*/
int df_SetShuffle(df_connection *conn, int RoomID, int Shuffle);

/*!
Move to the selected track in the current playlist on a specified room
RoomID: The room ID to use for this command.
TrackNumber: The track number to use for this command.
*/
int df_SetTrack(df_connection *conn, int RoomID, int TrackNumber);

/*!
Move to the entered track position in the currently playing track on a specified room
RoomID: The room ID to use for this command.
PlayPosition: The position to use for this command.
*/
int df_SetTrackPosition(df_connection *conn, int RoomID, df_time PlayPosition);

/*!
Set the volume level on a specified room
RoomID: The room ID to use for this command.
Volume: The volume to use for this command.
*/
int df_SetVolume(df_connection *conn, int RoomID, int Volume);

/*!
Stop current playback on a specified room
RoomID: The room ID to use for this command.
*/
int df_Stop(df_connection *conn, int RoomID);

/*!
Removes all the statistics for any item that hasn't been played for 30 days and does not have a valid id
*/
int df_vTunerCleanStatistics(df_connection *conn);

/*!
Clears a preset channel
ChannelNumber: The channel number to assing to, -1 for auto assignment
*/
int df_vTunerClearPresetChannel(df_connection *conn, int ChannelNumber);





// Row commands

void df_driverow_free(df_driverow *ptr);
void df_outputdevicerow_free(df_outputdevicerow *ptr);
void df_type1row_free(df_type1row *ptr);
void df_settingsexrow_free(df_settingsexrow *ptr);
void df_effformatrow_free(df_effformatrow *ptr);
void df_artistrow_free(df_artistrow *ptr);
void df_type0row_free(df_type0row *ptr);
void df_tracksotherrow_free(df_tracksotherrow *ptr);
void df_exttrackinforow_free(df_exttrackinforow *ptr);
void df_outputchannelrow_free(df_outputchannelrow *ptr);
void df_currplaylistexrow_free(df_currplaylistexrow *ptr);
void df_extcontributorrow_free(df_extcontributorrow *ptr);
void df_encodingstatusrow_free(df_encodingstatusrow *ptr);
void df_vtunerpresetrow_free(df_vtunerpresetrow *ptr);
void df_albumrow_free(df_albumrow *ptr);
void df_trackrow_free(df_trackrow *ptr);
void df_settingsrow_free(df_settingsrow *ptr);
void df_linkedroomdetailrow_free(df_linkedroomdetailrow *ptr);
void df_albumdetailrow_free(df_albumdetailrow *ptr);
void df_genrerow_free(df_genrerow *ptr);
void df_type4row_free(df_type4row *ptr);
void df_mediarendererrow_free(df_mediarendererrow *ptr);
void df_subgenrerow_free(df_subgenrerow *ptr);
void df_statusmessagerow_free(df_statusmessagerow *ptr);
void df_type3row_free(df_type3row *ptr);
void df_exttrackcontribrow_free(df_exttrackcontribrow *ptr);
void df_vtunerplayedrow_free(df_vtunerplayedrow *ptr);
void df_cddbgenrerow_free(df_cddbgenrerow *ptr);
void df_playerinstancerow_free(df_playerinstancerow *ptr);
void df_albumotherrow_free(df_albumotherrow *ptr);
void df_roomrow_free(df_roomrow *ptr);
void df_currentplaylistrow_free(df_currentplaylistrow *ptr);
void df_storerow_free(df_storerow *ptr);
void df_statusrow_free(df_statusrow *ptr);
void df_networkadaptorrow_free(df_networkadaptorrow *ptr);
void df_extworksrow_free(df_extworksrow *ptr);
void df_backuplogdetailrow_free(df_backuplogdetailrow *ptr);
void df_extalbumcreditrow_free(df_extalbumcreditrow *ptr);
void df_trackrangerow_free(df_trackrangerow *ptr);
void df_keyvaluerow_free(df_keyvaluerow *ptr);
void df_backuplogrow_free(df_backuplogrow *ptr);
void df_tracksforplaylistrow_free(df_tracksforplaylistrow *ptr);
void df_rippingalertrow_free(df_rippingalertrow *ptr);
void df_rippingstatusrow_free(df_rippingstatusrow *ptr);
void df_extalbuminforow_free(df_extalbuminforow *ptr);
void df_backupjobrow_free(df_backupjobrow *ptr);
void df_genressubgenresrow_free(df_genressubgenresrow *ptr);
void df_alertdetailrow_free(df_alertdetailrow *ptr);
void df_encodingqueuerow_free(df_encodingqueuerow *ptr);
void df_movealbumgetqueuerow_free(df_movealbumgetqueuerow *ptr);
void df_type2row_free(df_type2row *ptr);
void df_storedetailrow_free(df_storedetailrow *ptr);
void df_externalstoragerow_free(df_externalstoragerow *ptr);
void df_bulklookuprow_free(df_bulklookuprow *ptr);
void df_vtunernoderow_free(df_vtunernoderow *ptr);
void df_devicerow_free(df_devicerow *ptr);
/*!
List tracks containing a specified search string within a single or combination of entity names
EntityName: The entity name to search: album, artist, track, genre, composer, performer or conductor
SearchString: The string to look for in the entity named in EntityName
SearchType: Type of search: 1=Contains (default), 2=Begins With, 3=Exact Match, 4=Not Containing, 5=Not Exact Match
Match: Type of match with second rule: 1=All, 2=Any
EntityName2: The entity name to search: album, artist, track, genre, composer, performer or conductor
SearchString2: The string to look for in the entity named in EntityName2
SearchType2: Type of search: 1=Contains (default), 2=Begins With, 3=Exact Match, 4=Not Containing, 5=Not Exact Match
RemoteImagePath: If true a URL will be returned that can be used to download the cover art, otherwise a locl path will be retruned
ImageSize: The size of image required. 1 = small (61x61), 2 = medium (126x126), 3 = large (320x320), 4 = extra large (640x640).
*/
int df_AdvancedSearch(df_connection *conn, char* EntityName, char* SearchString, int SearchType, int Match, char* EntityName2, char* SearchString2, int SearchType2, int RemoteImagePath, int ImageSize, void (*callback)(int, df_type3row*, void*), void *context);

/*!
Perform a CD lookup for one or more existing albums.
AllAlbums: Perform lookup across all albums satisfying other criteria or only those for which a lookup has not been successful.
Interval: Lookup interval in days. This is the number of days since the last lookup, and controls which albums will be selected.
IgnoreProviderUsed: If this parameter is true then any lookup provider can be used to locate a match for the album. If this is false then last provider used for a given album will be set as a minimum provider. It basically means that if set to false, then a FreeDB match will not override an AMG match (for example).
AlbumKey: The absolute or relative addresses of specific Album(s) to use
*/
int df_BulkCDLookup(df_connection *conn, int AllAlbums, int Interval, int IgnoreProviderUsed, char* AlbumKey, void (*callback)(int, df_bulklookuprow*, void*), void *context);

/*!
Returns the current CD lookup queue
*/
int df_CDLookupGetQueue(df_connection *conn, void (*callback)(int, df_type4row*, void*), void *context);

/*!
Lists all albums associated with a specified complex search.
SearchParameter: Psuedo SQL to apply to the search.
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_ComplexSearchGetAlbums(df_connection *conn, char* SearchParameter, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists all artists associated with a specified complex search.
SearchParameter: Psuedo SQL to apply to the search.
*/
int df_ComplexSearchGetArtists(df_connection *conn, char* SearchParameter, void (*callback)(int, df_artistrow*, void*), void *context);

/*!
Lists all contributors associated with a specified complex search.
Type: Contributor Type
SearchParameter: Psuedo SQL to apply to the search.
*/
int df_ComplexSearchGetContributors(df_connection *conn, int Type, char* SearchParameter, void (*callback)(int, df_extcontributorrow*, void*), void *context);

/*!
Lists all tracks associated with a specified complex search.
SearchParameter: Psuedo SQL to apply to the search.
*/
int df_ComplexSearchGetTracks(df_connection *conn, char* SearchParameter, void (*callback)(int, df_trackrow*, void*), void *context);

/*!
List the Advanced Status Display
*/
int df_GetAdvancedStatus(df_connection *conn, void (*callback)(int, df_keyvaluerow*, void*), void *context);

/*!
List the details for a specified album
Address: The absolute or relative address of an album to search
*/
int df_GetAlbumDetails(df_connection *conn, char* Address, void (*callback)(int, df_albumdetailrow*, void*), void *context);

/*!
Lists all albums
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetAlbums(df_connection *conn, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists all albums associated with a specified set of artists
Address: Mutliple absolute or relative addresses of artists to search(space seperated)
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetAlbumsForArtists(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists all albums associated with a specified set of artists, restricted by a specified portable device
Address: Mutliple absolute or relative addresses of artists to search(space seperated)
DeviceAddress: Absolute or relative address of a device to search
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetAlbumsForArtistsForDevice(df_connection *conn, char* Address, char* DeviceAddress, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists all albums associated with a specified set of artists, restricted by the local server storage
Address: Mutliple absolute or relative addresses of artists to search(space seperated)
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetAlbumsForArtistsForServer(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists all albums associated with a specified set of artists, restricted by a specified network share
Address: Mutliple absolute or relative addresses of artists to search(space seperated)
ShareAddress: Absolute or relative address of a share to search
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetAlbumsForArtistsForShare(df_connection *conn, char* Address, char* ShareAddress, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists all albums associated with a specified set of artists, restricted by a specified genre
Address: Mutliple absolute or relative addresses of artists to search(space seperated)
GenreAddress: Absolute or relative address of a genre to search
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetAlbumsForArtistsInGenre(df_connection *conn, char* Address, char* GenreAddress, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists all albums associated with a specified set of artists, restricted by a specified sub-genre
Address: Mutliple absolute or relative addresses of artists to search(space seperated)
SubGenreAddress: Multiple absolute or relative addresses of sub-genres to search(space separated)
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetAlbumsForArtistsInSubGenre(df_connection *conn, char* Address, char* SubGenreAddress, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists all albums for Deletion
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetAlbumsForDeletion(df_connection *conn, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists all albums associated with a specified portable device
Address: Absolute or relative address of device to search
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetAlbumsForDevice(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists all albums in a playlist
Address: Absolute or relative address of the playlist to search
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetAlbumsForPlaylist(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists all albums stored locally on the server
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetAlbumsForServer(df_connection *conn, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists all albums associated with a specified network share
Address: Absolute or relative address of share to search
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetAlbumsForShare(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists all albums for a specified music store
StoreKey: The key of the store to retrieve albums for.
IncludeDeleted: Should delete albums be included in the results.
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetAlbumsForStore(df_connection *conn, char* StoreKey, int IncludeDeleted, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists additional details for requested albums
Address: Mutliple absolute or relative addresses of albums to search(space seperated)
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
RemoteImagePath: If true a URL will be returned that can be used to download the cover art, otherwise a locl path will be retruned
ImageSize: The size of image required. 1 = small (61x61), 2 = medium (126x126), 3 = large (320x320), 4 = extra large (640x640).
*/
int df_GetAlbumsOtherInfo(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, int RemoteImagePath, int ImageSize, void (*callback)(int, df_type2row*, void*), void *context);

/*!
Lists additional details for all albums
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
RemoteImagePath: If true a URL will be returned that can be used to download the cover art, otherwise a locl path will be retruned
ImageSize: The size of image required. 1 = small (61x61), 2 = medium (126x126), 3 = large (320x320), 4 = extra large (640x640).
*/
int df_GetAlbumsOtherInfoAll(df_connection *conn, char* SortColumn, char* SortOrder, int RemoteImagePath, int ImageSize, void (*callback)(int, df_type2row*, void*), void *context);

/*!
Lists additional details for all albums
Address: The absolute or relative address of a device to search
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
RemoteImagePath: If true a URL will be returned that can be used to download the cover art, otherwise a locl path will be retruned
ImageSize: The size of image required. 1 = small (61x61), 2 = medium (126x126), 3 = large (320x320), 4 = extra large (640x640).
*/
int df_GetAlbumsOtherInfoForDevice(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, int RemoteImagePath, int ImageSize, void (*callback)(int, df_type2row*, void*), void *context);

/*!
Lists additional details for all albums on the local server
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
RemoteImagePath: If true a URL will be returned that can be used to download the cover art, otherwise a locl path will be retruned
ImageSize: The size of image required. 1 = small (61x61), 2 = medium (126x126), 3 = large (320x320), 4 = extra large (640x640).
*/
int df_GetAlbumsOtherInfoForServer(df_connection *conn, char* SortColumn, char* SortOrder, int RemoteImagePath, int ImageSize, void (*callback)(int, df_type2row*, void*), void *context);

/*!
Lists additional details for all albums
Address: The absolute or relative address of a device to search
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
RemoteImagePath: If true a URL will be returned that can be used to download the cover art, otherwise a locl path will be retruned
ImageSize: The size of image required. 1 = small (61x61), 2 = medium (126x126), 3 = large (320x320), 4 = extra large (640x640).
*/
int df_GetAlbumsOtherInfoForShare(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, int RemoteImagePath, int ImageSize, void (*callback)(int, df_type2row*, void*), void *context);

/*!
List all albums containing a specified search string withing eiter the artist or album name
SearchString: The string to look for in albums or artist names
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
SearchType: Type of search: 1=Contains (default), 2=Starts With, 3=Exact Match, 4=Does Not Contain
*/
int df_GetAlbumsSearchAlbumArtist(df_connection *conn, char* SearchString, char* SortColumn, char* SortOrder, int SearchType, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists all albums which have at least one album lookup message associated them.
*/
int df_GetAlbumsWithAlbumLookupMessages(df_connection *conn, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Get the details of a single alert
Address: The absolute or relative address of an alert to search
*/
int df_GetAlertDetails(df_connection *conn, char* Address, void (*callback)(int, df_alertdetailrow*, void*), void *context);

/*!
Return the details of a single artist
Address: The absolute or relative address of an artist to locate
*/
int df_GetArtistDetails(df_connection *conn, char* Address, void (*callback)(int, df_artistrow*, void*), void *context);

/*!
Lists all artists
Allocated: Flag controlling whether only allocated artists should be shown(those with albums). Defaults to False.
*/
int df_GetArtists(df_connection *conn, int Allocated, void (*callback)(int, df_artistrow*, void*), void *context);

/*!
Lists all artists with albums on a specified portable device
Address: The absolute or relative address of a device to search
*/
int df_GetArtistsForDevice(df_connection *conn, char* Address, void (*callback)(int, df_artistrow*, void*), void *context);

/*!
Lists all artists with albums stored locally on the server
*/
int df_GetArtistsForServer(df_connection *conn, void (*callback)(int, df_artistrow*, void*), void *context);

/*!
Lists all artists with albums on a specified network share
Address: The absolute or relative address of a share to search
*/
int df_GetArtistsForShare(df_connection *conn, char* Address, void (*callback)(int, df_artistrow*, void*), void *context);

/*!
Lists all artists with albums in a specified genre
Address: The absolute or relative address of a genre to search
*/
int df_GetArtistsInGenre(df_connection *conn, char* Address, void (*callback)(int, df_artistrow*, void*), void *context);

/*!
Lists all artists with albums in a specified sub-genre
Address: Multiple absolute or relative addresses of sub-genres to search(space separated)
*/
int df_GetArtistsInSubGenre(df_connection *conn, char* Address, void (*callback)(int, df_artistrow*, void*), void *context);

/*!
List all available values for a setting
Address: The Setting name or relative address of a registry value
*/
int df_GetAvailableValues(df_connection *conn, char* Address, void (*callback)(int, df_keyvaluerow*, void*), void *context);

/*!
Return the details of a single backup job.
Address: The address (absolute or relative) of the specific backup job.
*/
int df_GetBackupJobDetail(df_connection *conn, char* Address, void (*callback)(int, df_backupjobrow*, void*), void *context);

/*!
List all the defined backup jobs.
*/
int df_GetBackupJobs(df_connection *conn, void (*callback)(int, df_backupjobrow*, void*), void *context);

/*!
Return a single log entry.
Address: The address of the backup log entry.
*/
int df_GetBackupLogDetail(df_connection *conn, char* Address, void (*callback)(int, df_backuplogdetailrow*, void*), void *context);

/*!
List all backup log entries, or all entries associated with a given backup job.
Address: The optional address of the parent backup job. If this is omitted then all log entries will be returned.
*/
int df_GetBackupLogs(df_connection *conn, char* Address, void (*callback)(int, df_backuplogrow*, void*), void *context);

/*!
Lists all CDDB Genres
*/
int df_GetCDDBGenres(df_connection *conn, void (*callback)(int, df_cddbgenrerow*, void*), void *context);

/*!
Lists all system component versions
RoomID: The room ID to use for this command
*/
int df_GetComponentVersions(df_connection *conn, int RoomID, void (*callback)(int, df_keyvaluerow*, void*), void *context);

/*!
List tracks in the current playlist
RoomID: The room ID to use for this command.
*/
int df_GetCurrentPlayList(df_connection *conn, int RoomID, void (*callback)(int, df_currentplaylistrow*, void*), void *context);

/*!
List tracks in the current playlist
RoomID: The room ID to use for this command.
RemoteImagePath: If true a URL will be returned that can be used to download the cover art, otherwise a locl path will be retruned
ImageSize: The size of image required. 1 = small (61x61), 2 = medium (126x126), 3 = large (320x320), 4 = extra large (640x640).
*/
int df_GetCurrentPlaylistEx(df_connection *conn, int RoomID, int RemoteImagePath, int ImageSize, void (*callback)(int, df_type0row*, void*), void *context);

/*!
Return the details of a single external device.
DeviceAddress: The absolute or relative address of a device to locate.
*/
int df_GetDeviceDetails(df_connection *conn, char* DeviceAddress, void (*callback)(int, df_devicerow*, void*), void *context);

/*!
List all defined portable devices
ActiveOnly: If this parameter is true then only docked devices will be returned. If this parameter is false then all devices will be returned. Defaults to false.
*/
int df_GetDevices(df_connection *conn, int ActiveOnly, void (*callback)(int, df_devicerow*, void*), void *context);

/*!
List the contents of the encoding queue
RoomID: The room ID to use for this command.
*/
int df_GetEncodingQueue(df_connection *conn, int RoomID, void (*callback)(int, df_encodingqueuerow*, void*), void *context);

/*!
Get the details of the current encoding status
RoomID: The room ID to use for this command.
*/
int df_GetEncodingStatus(df_connection *conn, int RoomID, void (*callback)(int, df_encodingstatusrow*, void*), void *context);

/*!
Returns any credits given an album key
Address: Mutliple absolute or relative addresses of albums to search(space seperated)
*/
int df_GetExtAlbumCredits(df_connection *conn, char* Address, void (*callback)(int, df_extalbumcreditrow*, void*), void *context);

/*!
Returns all albums for a given contributor
Address: Absolute or relative address of contributor to search
Type: Contributor Type
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetExtAlbumsByContributor(df_connection *conn, char* Address, int Type, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Returns all albums for a given contributor restricted by a specified portable device
Address: Absolute or relative address of contributor to search
DeviceAddress: Absolute or relative address of a portable device
Type: Contributor Type
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetExtAlbumsByContributorForDevice(df_connection *conn, char* Address, char* DeviceAddress, int Type, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Returns all albums for a given contributor restricted by the local server
Address: Absolute or relative address of contributor to search
Type: Contributor Type
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetExtAlbumsByContributorForServer(df_connection *conn, char* Address, int Type, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Returns all albums for a given contributor restricted by a specified network share
Address: Absolute or relative address of contributor to search
ShareAddress: Absolute or relative address of a network share
Type: Contributor Type
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetExtAlbumsByContributorForShare(df_connection *conn, char* Address, char* ShareAddress, int Type, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Returns all albums where the given contributor appears as a credit
Address: Absolute or relative address of contributor to search
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetExtAlbumsByCredit(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Returns all albums for a given classical work
Work: Classical work to search
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetExtAlbumsByWork(df_connection *conn, char* Work, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Returns all extra information for given albums
Address: Mutliple absolute or relative addresses of albums to search(space seperated)
*/
int df_GetExtAlbumsInfo(df_connection *conn, char* Address, void (*callback)(int, df_extalbuminforow*, void*), void *context);

/*!
List all albums containing a specified search string within a person's name (artist, conductor, composer or performer)
SearchString: The string to look for in persons' names
SearchType: Type of search: 1=Contains (default), 2=Starts With, 3=Exact Match, 4=Does Not Contain
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetExtAlbumsSearchPeople(df_connection *conn, char* SearchString, int SearchType, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Return a single contributor
Address: Single absolute or relative address of Contributor to return.
Type: Contributor Type
*/
int df_GetExtContributorDetails(df_connection *conn, char* Address, int Type, void (*callback)(int, df_extcontributorrow*, void*), void *context);

/*!
Returns all contributors
Type: Contributor Type
*/
int df_GetExtContributors(df_connection *conn, int Type, void (*callback)(int, df_extcontributorrow*, void*), void *context);

/*!
Returns all contributors for a given album
Address: Absolute or relative address of an album to search
Type: Contributor Type
*/
int df_GetExtContributorsForAlbum(df_connection *conn, char* Address, int Type, void (*callback)(int, df_extcontributorrow*, void*), void *context);

/*!
Returns all contributors for a given portable device
Address: Absolute or relative address of portable device to search(space seperated)
Type: Contributor Type
*/
int df_GetExtContributorsForDevice(df_connection *conn, char* Address, int Type, void (*callback)(int, df_extcontributorrow*, void*), void *context);

/*!
Returns all contributors stored locally on the server
Type: Contributor Type
*/
int df_GetExtContributorsForServer(df_connection *conn, int Type, void (*callback)(int, df_extcontributorrow*, void*), void *context);

/*!
Returns all contributors for a given network share
Address: Absolute or relative address of network share to search(space seperated)
Type: Contributor Type
*/
int df_GetExtContributorsForShare(df_connection *conn, char* Address, int Type, void (*callback)(int, df_extcontributorrow*, void*), void *context);

/*!
Returns all contributors for given tracks
Address: Mutliple absolute or relative addresses of tracks to search(space seperated)
Type: Contributor Type
*/
int df_GetExtTrackContributors(df_connection *conn, char* Address, int Type, void (*callback)(int, df_exttrackcontribrow*, void*), void *context);

/*!
Returns all tracks for a given contributor
Address: Absolute or relative address of contributor to search
Type: Contributor Type
Album: Absolute or relative address of album to filter on
*/
int df_GetExtTracksByContributor(df_connection *conn, char* Address, int Type, char* Album, void (*callback)(int, df_trackrow*, void*), void *context);

/*!
Returns all tracks for a given contributor stored on the specified external device.
Address: Absolute or relative address of contributor to search
DeviceAddress: Absolute or relative address of an external device.
Type: Contributor Type
Album: Absolute or relative address of album to filter on
*/
int df_GetExtTracksByContributorForDevice(df_connection *conn, char* Address, char* DeviceAddress, int Type, char* Album, void (*callback)(int, df_trackrow*, void*), void *context);

/*!
Returns all tracks for a given contributor stored on the local server.
Address: Absolute or relative address of contributor to search
Type: Contributor Type
Album: Absolute or relative address of album to filter on
*/
int df_GetExtTracksByContributorForServer(df_connection *conn, char* Address, int Type, char* Album, void (*callback)(int, df_trackrow*, void*), void *context);

/*!
Returns all tracks for a given contributor stored on the specified external share.
Address: Absolute or relative address of contributor to search
ShareAddress: Absolute or relative address of an external share.
Type: Contributor Type
Album: Absolute or relative address of album to filter on
*/
int df_GetExtTracksByContributorForShare(df_connection *conn, char* Address, char* ShareAddress, int Type, char* Album, void (*callback)(int, df_trackrow*, void*), void *context);

/*!
Returns all tracks for a given classical work
Work: Classical work description to search
*/
int df_GetExtTracksByWork(df_connection *conn, char* Work, void (*callback)(int, df_trackrow*, void*), void *context);

/*!
Lists extra track information given a list of track keys
Address: Mutliple absolute or relative addresses of tracks to search(space seperated)
*/
int df_GetExtTracksInfo(df_connection *conn, char* Address, void (*callback)(int, df_exttrackinforow*, void*), void *context);

/*!
Lists all classical works
*/
int df_GetExtWorks(df_connection *conn, void (*callback)(int, df_extworksrow*, void*), void *context);

/*!
List all located network shares (which may, or may not, contain music)
AvailableOnly: If this parameter is true then only shares which are flagged active and with a state of "Online" will be returned. If this parameter is false then all shares will be returned. Defaults to false.
*/
int df_GetExternalStorages(df_connection *conn, int AvailableOnly, void (*callback)(int, df_externalstoragerow*, void*), void *context);

/*!
Lists all genres
Allocated: Flag controlling whether only allocated genres should be returned. Defaults to False.
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetGenres(df_connection *conn, int Allocated, char* SortColumn, char* SortOrder, void (*callback)(int, df_genrerow*, void*), void *context);

/*!
Lists all sub-genres defined, together with the parent genre name
Allocated: Flag controlling whether only allocated sub-genres should be shown. Defaults to False.
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetGenresSubGenres(df_connection *conn, int Allocated, char* SortColumn, char* SortOrder, void (*callback)(int, df_genressubgenresrow*, void*), void *context);

/*!
Lists the albums played most recently
TopCount: How many of the latest albums are required back in the results
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetLatestPlayedAlbums(df_connection *conn, int TopCount, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Returns the details of a single linked room and its related child rooms
RoomKey: The absolute or relative address of the Room details to be displayed
*/
int df_GetLinkedRoomDetail(df_connection *conn, char* RoomKey, void (*callback)(int, df_linkedroomdetailrow*, void*), void *context);

/*!
List all defined linked rooms
LocalOnly: This parameter is not used, and is included for compatibility for the other GetRooms style commands.
*/
int df_GetLinkedRooms(df_connection *conn, int LocalOnly, void (*callback)(int, df_roomrow*, void*), void *context);

/*!
List all active (connected) network adapters.
IncludeWireless: If true then wireless adapters will be included in the returned results, otherwise only wired adapters will be returned.
*/
int df_GetNetworkActiveAdapters(df_connection *conn, int IncludeWireless, void (*callback)(int, df_networkadaptorrow*, void*), void *context);

/*!
Lists the newest played albums (ie. those that have been ripped most recently)
TopCount: How many of the newest albums are required back in the results
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetNewestAlbums(df_connection *conn, int TopCount, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
List all non-linked rooms
LocalOnly: If true then only return rooms local to the host running Sophia
*/
int df_GetNonLinkedRooms(df_connection *conn, int LocalOnly, void (*callback)(int, df_roomrow*, void*), void *context);

/*!
Get a list of defined output channels for a given room or host name. Note: An output device, or local output device, is a sound card associated with a given host. An external output device is a standalone output device, such as a UPnP media renderer. An output channel is a Cirin player instance, which is associated with either an output device or an external output device.
RoomID: The room ID to use for this command. Supply EITHER a RoomID OR a HostName.
HostName: The host name (or host address) to use for this command. Supply EITHER a RoomID OR a HostName.
*/
int df_GetOutputChannels(df_connection *conn, int RoomID, char* HostName, void (*callback)(int, df_outputchannelrow*, void*), void *context);

/*!
Get a list of output devices for a given room or host name.
RoomID: The room ID to use for this command. Supply EITHER a RoomID OR a HostName.
HostName: The host name (or host address) to use for this command. Supply EITHER a RoomID OR a HostName.
AsioOutputs: If true then return local Asio outputs, otherwise return local DirectSound outputs.
*/
int df_GetOutputDevices(df_connection *conn, int RoomID, char* HostName, int AsioOutputs, void (*callback)(int, df_outputdevicerow*, void*), void *context);

/*!
Lists all the playlists with the Artist beginning with a specified letter
SearchLetter: The first letter of the playlists to search for
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetPlayListsByLetter(df_connection *conn, char* SearchLetter, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Get a list of all possible player instances and include device and source line settings for those already configured.
RoomID: The room ID to use for this command.
*/
int df_GetPlayerInstances(df_connection *conn, int RoomID, void (*callback)(int, df_playerinstancerow*, void*), void *context);

/*!
Lists playlists associated with a specified genre
Address: The absolute or relative address of a genre to search
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetPlaylistsForGenre(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists playlists associated with a specified sub-genre
Address: The absolute or relative address of a sub-genre to search
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetPlaylistsForSubGenre(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists user-defined playlists associated with a specified sub-genre restricted by portable device
Address: The absolute or relative address of a sub-genre to search
DeviceAddress: The absolute or relative address of a device
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetPlaylistsForSubGenreForDevice(df_connection *conn, char* Address, char* DeviceAddress, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists user-defined playlists associated with a specified sub-genre restricted to the local server
Address: The absolute or relative address of a sub-genre to search
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetPlaylistsForSubGenreForServer(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists user-defined playlists associated with a specified sub-genre restricted by network share
Address: The absolute or relative address of a sub-genre to search
ShareAddress: The absolute or relative address of a share
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetPlaylistsForSubGenreForShare(df_connection *conn, char* Address, char* ShareAddress, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
List all available named ripping/encoding settings
RoomID: The room ID to use for this command.
*/
int df_GetRipEncSettings(df_connection *conn, int RoomID, void (*callback)(int, df_settingsrow*, void*), void *context);

/*!
List all available named ripping/encoding settings. This is the new form of the command, which returns additional UI caption details.
RoomID: The room ID to use for this command.
*/
int df_GetRipEncSettingsEx(df_connection *conn, int RoomID, void (*callback)(int, df_settingsexrow*, void*), void *context);

/*!
List the current ripping alerts
*/
int df_GetRippingAlerts(df_connection *conn, void (*callback)(int, df_rippingalertrow*, void*), void *context);

/*!
Get the details of the current ripping status
RoomID: The room ID to use for this command.
*/
int df_GetRippingStatus(df_connection *conn, int RoomID, void (*callback)(int, df_type1row*, void*), void *context);

/*!
List all defined rooms
LocalOnly: If true then only return rooms local to the host running Sophia
*/
int df_GetRooms(df_connection *conn, int LocalOnly, void (*callback)(int, df_roomrow*, void*), void *context);

/*!
List all defined rooms with playback capability
LocalOnly: If true then only return rooms local to the host running Sophia
*/
int df_GetRoomsWithPlayBack(df_connection *conn, int LocalOnly, void (*callback)(int, df_roomrow*, void*), void *context);

/*!
List all defined rooms with ripping capability
LocalOnly: If true then only return rooms local to the host running Sophia
*/
int df_GetRoomsWithRipping(df_connection *conn, int LocalOnly, void (*callback)(int, df_roomrow*, void*), void *context);

/*!
List all available named system settings
RoomID: The room ID to use for this command.
*/
int df_GetSettings(df_connection *conn, int RoomID, void (*callback)(int, df_settingsrow*, void*), void *context);

/*!
List all available named system settings. This is the new form of the command, which returns additional UI caption details.
RoomID: The room ID to use for this command.
*/
int df_GetSettingsEx(df_connection *conn, int RoomID, void (*callback)(int, df_settingsexrow*, void*), void *context);

/*!
Query for system status messages.
MessageDate: The Date of status message to return. The value "0001-01-01" is treated as unspecified, if you want to ignore this parameter.
Category: The category of status messages to return.
Tag: The tag value of status messages to return.
*/
int df_GetStatusMessages(df_connection *conn, df_date MessageDate, char* Category, int Tag, void (*callback)(int, df_statusmessagerow*, void*), void *context);

/*!
Lists music stores
MusicStoreKey: The absolute or relative address of the music store whose values are to be retrieved
*/
int df_GetStoreDetail(df_connection *conn, char* MusicStoreKey, void (*callback)(int, df_storedetailrow*, void*), void *context);

/*!
Lists music stores
IncludeReadOnly: Should read only music store be included in the result set.
MusicStoreType: The type of music store to be returned, could be All, Local or Remote
*/
int df_GetStores(df_connection *conn, int IncludeReadOnly, int MusicStoreType, void (*callback)(int, df_storerow*, void*), void *context);

/*!
Lists all sub-genres for a specified portable device
Address: The absolute or relative address of a device to search
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetSubGenresForDevice(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_subgenrerow*, void*), void *context);

/*!
Lists all sub-genres for a specified genre
Address: The absolute or relative address of a genre to search
Allocated: Flag controlling whether only allocated sub-genres should be returned. Defaults to False.
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetSubGenresForGenre(df_connection *conn, char* Address, int Allocated, char* SortColumn, char* SortOrder, void (*callback)(int, df_subgenrerow*, void*), void *context);

/*!
Lists all sub-genres stored locally on the server
Allocated: Flag controlling whether only allocated sub-genres should be returned. Defaults to False.
UserDefined: Flag controlling whether additional unallocated userdefined sub-genres should be returned. Defaults to False.
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetSubGenresForServer(df_connection *conn, int Allocated, int UserDefined, char* SortColumn, char* SortOrder, void (*callback)(int, df_subgenrerow*, void*), void *context);

/*!
Lists all sub-genres for a specified network share
Address: The absolute or relative address of a network share to search
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetSubGenresForShare(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_subgenrerow*, void*), void *context);

/*!
List all defined system drives
*/
int df_GetSystemDrives(df_connection *conn, void (*callback)(int, df_driverow*, void*), void *context);

/*!
Lists the top played albums (ie. those that have been played the most number of times)
TopCount: How many of the topmost albums are required back in the results
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetTopPlayedAlbums(df_connection *conn, int TopCount, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Retrieve a set of tracks based on the supplied startRow, rowCount and Filter expression. This is an optimised routine which is designed for fast track range retrieval from; all available tracks, local server, device or share. It was original created to support "All Songs" functionality in the Henrot service.
StartRow: The offset of the first row to retrieve. This is relative to any filter expression.
RowCount: The number of rows to return. If there are less rows matching the Filter expression than requested then additional following rows will be added to the row set.
Filter: A filter expression. Only tracks whose SortName begins with this expression will be returned. The filter should not contain any wildcard characters.
Address: The absolute or relative address of a device or share (if required). This parameter is mandatory if the storage parameter is 2 or 3.
Storage: Where is the music stored? 0 = All music, 1 = Local Server, 2 = Network, 3 = Portable.
*/
int df_GetTrackRange(df_connection *conn, int StartRow, int RowCount, char* Filter, char* Address, int Storage, void (*callback)(int, df_trackrangerow*, void*), void *context);

/*!
List all the tracks on the DigiFi
*/
int df_GetTracksAll(df_connection *conn, void (*callback)(int, df_trackrow*, void*), void *context);

/*!
List all the tracks in a specified album which are part of a user playlist
Address: The absolute or relative address of an album to search
*/
int df_GetTracksForAlbumInUPL(df_connection *conn, char* Address, void (*callback)(int, df_trackrow*, void*), void *context);

/*!
List all the tracks for a specified artist
Address: The absolute or relative address of an artist to locate rows for.
*/
int df_GetTracksForArtist(df_connection *conn, char* Address, void (*callback)(int, df_trackrow*, void*), void *context);

/*!
List all the tracks for a specified artist, stored on the specified external device.
Address: The absolute or relative address of an artist to locate rows for.
DeviceAddress: The absolute or relative address of an external device.
*/
int df_GetTracksForArtistForDevice(df_connection *conn, char* Address, char* DeviceAddress, void (*callback)(int, df_trackrow*, void*), void *context);

/*!
List all the tracks for a specified artist, stored on the local server.
Address: The absolute or relative address of an artist to locate rows for.
*/
int df_GetTracksForArtistForServer(df_connection *conn, char* Address, void (*callback)(int, df_trackrow*, void*), void *context);

/*!
List all the tracks for a specified artist, stored on the specified external share.
Address: The absolute or relative address of an artist to locate rows for.
ShareAddress: The absolute or relative address of an external share.
*/
int df_GetTracksForArtistForShare(df_connection *conn, char* Address, char* ShareAddress, void (*callback)(int, df_trackrow*, void*), void *context);

/*!
Lists all tracks for Deletion
RemoteImagePath: If true a URL will be returned that can be used to download the cover art, otherwise a locl path will be retruned
ImageSize: The size of image required. 1 = small (61x61), 2 = medium (126x126), 3 = large (320x320), 4 = extra large (640x640).
*/
int df_GetTracksForDeletion(df_connection *conn, int RemoteImagePath, int ImageSize, void (*callback)(int, df_type3row*, void*), void *context);

/*!
List all the tracks for a specified portable device
Address: The absolute or relative address of a portable device to locate rows for.
*/
int df_GetTracksForDevice(df_connection *conn, char* Address, void (*callback)(int, df_trackrow*, void*), void *context);

/*!
List all the tracks for a specified genre
Address: The absolute or relative address of a genre to locate rows for
*/
int df_GetTracksForGenre(df_connection *conn, char* Address, void (*callback)(int, df_trackrow*, void*), void *context);

/*!
List all the tracks for the supplied entity with the specified value.
EntityName: The name of the entity to use for applying the search. Supported entities: album, artist, playlist, genre, track, composer, conductor, performer.
EntityValue: The value to search for.
ExactMatch: If true then an exact match on entity will be performed, otherwise a partial match will be used.
*/
int df_GetTracksForNamedEntity(df_connection *conn, char* EntityName, char* EntityValue, int ExactMatch, void (*callback)(int, df_trackrow*, void*), void *context);

/*!
List all the tracks for a specified playlist
Address: The absolute or relative address of a playlist to search
ShowHidden: If this is true then hidden tracks associated with the playlist will be returned. Defaults to False.
*/
int df_GetTracksForPlaylist(df_connection *conn, char* Address, int ShowHidden, void (*callback)(int, df_tracksforplaylistrow*, void*), void *context);

/*!
List all the tracks stored locally on the server
*/
int df_GetTracksForServer(df_connection *conn, void (*callback)(int, df_trackrow*, void*), void *context);

/*!
List all the tracks for a specified network share
Address: The absolute or relative address of a network share to locate rows for.
*/
int df_GetTracksForShare(df_connection *conn, char* Address, void (*callback)(int, df_trackrow*, void*), void *context);

/*!
List all the tracks for a specified sub-genre
Address: The absolute or relative address of a sub-genre to locate rows for.
*/
int df_GetTracksForSubGenre(df_connection *conn, char* Address, void (*callback)(int, df_trackrow*, void*), void *context);

/*!
List all the tracks for a specified sub-genre stored on the specified external device.
Address: The absolute or relative address of a sub-genre to locate rows for.
DeviceAddress: The absolute or relative address of an external device.
*/
int df_GetTracksForSubGenreForDevice(df_connection *conn, char* Address, char* DeviceAddress, void (*callback)(int, df_trackrow*, void*), void *context);

/*!
List all the tracks for a specified sub-genre stored on the local server.
Address: The absolute or relative address of a sub-genre to locate rows for.
*/
int df_GetTracksForSubGenreForServer(df_connection *conn, char* Address, void (*callback)(int, df_trackrow*, void*), void *context);

/*!
List all the tracks for a specified sub-genre stored on the specified external share.
Address: The absolute or relative address of a sub-genre to locate rows for.
ShareAddress: The absolute or relative address of an external share.
*/
int df_GetTracksForSubGenreForShare(df_connection *conn, char* Address, char* ShareAddress, void (*callback)(int, df_trackrow*, void*), void *context);

/*!
Lists additional track details
Address: The track(s) absolute or relative address
RemoteImagePath: If true a URL will be returned that can be used to download the cover art, otherwise a locl path will be retruned
ImageSize: The size of image required. 1 = small (61x61), 2 = medium (126x126), 3 = large (320x320), 4 = extra large (640x640).
*/
int df_GetTracksOtherInfo(df_connection *conn, char* Address, int RemoteImagePath, int ImageSize, void (*callback)(int, df_type3row*, void*), void *context);

/*!
List tracks containing a specified search string within the track name
SearchString: The string to look for in track names
SearchType: Type of search: 1=Contains (default), 2=Starts With, 3=Exact Match, 4=Does Not Contain
RemoteImagePath: If true a URL will be returned that can be used to download the cover art, otherwise a locl path will be retruned
ImageSize: The size of image required. 1 = small (61x61), 2 = medium (126x126), 3 = large (320x320), 4 = extra large (640x640).
*/
int df_GetTracksSearchName(df_connection *conn, char* SearchString, int SearchType, int RemoteImagePath, int ImageSize, void (*callback)(int, df_type3row*, void*), void *context);

/*!
Fetch a list of the UPnP media renderer devices on the local network.
*/
int df_GetUpnpMediaRenderers(df_connection *conn, void (*callback)(int, df_mediarendererrow*, void*), void *context);

/*!
Lists all user playlists
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetUserPlaylists(df_connection *conn, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists user-defined playlists associated with a specified portable device
Address: The absolute or relative address of a device to search
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetUserPlaylistsForDevice(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists user-defined playlists stored locally on the server
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetUserPlaylistsForServer(df_connection *conn, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
Lists user-defined playlists associated with a specified network share
Address: The absolute or relative address of a share to search
SortColumn: The column name(s) to use when sorting the results. Multiple columns can be supplied delimited by a comma.
SortOrder: The sort order to use in sorting the results (ASC or DESC). If multiple columns supplied for SortColumn then corresponding orders can be supplied delimited by a comma.
*/
int df_GetUserPlaylistsForShare(df_connection *conn, char* Address, char* SortColumn, char* SortOrder, void (*callback)(int, df_albumrow*, void*), void *context);

/*!
List the Users Status Display
*/
int df_GetUserStatus(df_connection *conn, void (*callback)(int, df_keyvaluerow*, void*), void *context);

/*!
rEturns the cuurent move album queue
*/
int df_MoveAlbumGetQueue(df_connection *conn, void (*callback)(int, df_movealbumgetqueuerow*, void*), void *context);

/*!
Return current service status. This is a listing of the currently connected clients
*/
int df_Status(df_connection *conn, void (*callback)(int, df_statusrow*, void*), void *context);

/*!
Undo's all user edits to an album except for deleted albums and tracks
AlbumKeys: The absolute or relative addresses of specific Album(s) to use
*/
int df_UndoUserEdits(df_connection *conn, char* AlbumKeys, void (*callback)(int, df_bulklookuprow*, void*), void *context);

/*!
Return all child vTuner nodes using the supplied vTuner URL.
vTunerUrl: The vTuner URL to use for locating child nodes. If nothing is supplied then the root nodes will be returned.
vTunerBackupUrl: The vTuner backup URL to use for locating child nodes. If nothing is supplied then the root nodes will be returned.
*/
int df_vTunerGetChildNodes(df_connection *conn, char* vTunerUrl, char* vTunerBackupUrl, void (*callback)(int, df_vtunernoderow*, void*), void *context);

/*!
Return all played stations and episodes in descending order by LastPlayed
*/
int df_vTunerGetLastPlayed(df_connection *conn, void (*callback)(int, df_vtunerplayedrow*, void*), void *context);

/*!
Return all played stations and episodes in descending order by HitCount
*/
int df_vTunerGetMostPlayed(df_connection *conn, void (*callback)(int, df_vtunerplayedrow*, void*), void *context);

/*!
Returns the vTuner Show, Station or Episode that match the Url supplied
URLPlayed: The URL that was played to use for locating the node.
*/
int df_vTunerGetNodeFromPlayedUrl(df_connection *conn, char* URLPlayed, void (*callback)(int, df_vtunernoderow*, void*), void *context);

/*!
Returns all preset channels and thier associated nodes
*/
int df_vTunerGetPresetChannels(df_connection *conn, void (*callback)(int, df_vtunerpresetrow*, void*), void *context);

/*!
Returns the vTuner Show, Station or Episode that match the id supplied
vTunerId: The vTuner ID to use for locating child nodes.
vTunerLookupType: The type of node to search for. For a lookup by ID this can be 3 - Station, 4 - Show or 5 - Episode
*/
int df_vTunerLookupById(df_connection *conn, char* vTunerId, int vTunerLookupType, void (*callback)(int, df_vtunernoderow*, void*), void *context);












#endif




