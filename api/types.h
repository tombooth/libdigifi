/*
 *  types.h
 *  libdigifi.new
 *
 *  Created by Tom Booth on 09/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */


#ifndef TYPES_H
#define TYPES_H

typedef enum {
	DF_STORAGE_UNKNOWN = 0,
	DF_STORAGE_SERVER = 1,
	DF_STORAGE_NETWORK = 2,
	DF_STORAGE_PORTABLE = 3
} df_storagetype;


typedef struct {
	unsigned int hours;
	unsigned int minutes;
	unsigned int seconds;
} df_time;

typedef struct {
	unsigned int year;
	unsigned int month;
	unsigned int day;
} df_date;

typedef struct {
	int key;
	char *name;
	int albumkey;
	char *albumname;
	int artistkey;
	char *artistname;
	int genrekey;
	char *genrename;
	df_time *length;
	int source;
	char *path;
} df_detailedtrack;

typedef struct {
	char *name;
	int source;
	char *path;
} df_trackname;

// Get types

typedef struct {
	int AddNewDrive_Return;
	char* AddNewDrive_ErrorMessage;
} df_newdriveresult;

typedef struct {
	int ServiceMode_ModeValue;
	char* ServiceMode_ModeName;
} df_servicemode;

typedef struct {
	int DriveKey;
	char* DriveLetter;
	int Primary;
	char* RootPath;
	char* SharePath;
	df_date Created;
	df_date Modified;
	int Usage;
	df_date LastBackup;
} df_drivedetail;

typedef struct {
	int StorageKey;
	char* IPAddress;
	char* HostName;
	char* ShareName;
	char* FullSharePath;
	char* State;
	char* LastState;
	int Active;
	df_date Created;
	df_date Modified;
	df_date LastScanDate;
	df_time LastScanTime;
	char* UserName;
	char* Password;
	char* ScanIgnore;
} df_extstoragedetail;

typedef struct {
	int TrackKey;
	char* Name;
	char* Type;
	df_time Length;
	int Source;
} df_trkname;

typedef struct {
	int RescanMusicStore_Success;
	char* RescanMusicStore_Message;
} df_rescanresult;

typedef struct {
	char* Message;
	char* Category;
	df_date DateCreated;
} df_messagedetail;

typedef struct {
	char* DriveLetter;
	char* RootPath;
	char* SharePath;
	int Usage;
} df_fsdrivedetail;

typedef struct {
	int AddExternalStorage_Success;
	char* AddExternalStorage_Message;
	int AddExternalStorage_Key;
	char* AddExternalStorage_Hostname;
	char* AddExternalStorage_IPAddress;
	char* AddExternalStorage_ShareName;
	char* AddExternalStorage_Username;
	char* AddExternalStorage_Password;
} df_extstorageresult;

typedef struct {
	df_date GetSystemTime_Date;
	df_time GetSystemTime_Time;
} df_systemtime;

typedef struct {
	int DemoteMusicStoreToShare_Success;
	char* DemoteMusicStoreToShare_Message;
} df_demoteresult;

typedef struct {
	char* Album;
	char* Artist;
} df_albumartist;

typedef struct {
	int SetMusicStorePriority_Success;
	char* SetMusicStorePriority_Message;
} df_musicstorepriorityresult;

typedef struct {
	char* Backup_SourceDrive;
	char* Backup_DestDrive;
	char* Backup_Type;
	char* Backup_Status;
	char* Backup_CurrentFile;
	char* Backup_LastError;
	df_time Backup_TimeTaken;
	df_time Backup_TimeRemaining;
	int Backup_SourceFileCount;
	int Backup_SourceFolderCount;
	long Backup_SourceByteCount;
	int Backup_ProcessedFileCount;
	int Backup_ProcessedFolderCount;
	long Backup_ProcessedByteCount;
	int Backup_ErrorCount;
	int Backup_ErrorFileCount;
	long Backup_ErrorByteCount;
} df_backupstatus;

typedef struct {
	char* CoverImageName;
	char* CoverImageURI;
} df_coverimage;

typedef struct {
	int CDPlaying;
	char* TrackName;
	char* Album;
	char* Artist;
	int TrackNumber;
	int TrackCount;
	int Shuffle;
	int Repeat;
	char* Status;
	df_time TrackLength;
	df_time TrackPosition;
	char* Version;
	int Volume;
} df_queryplayback;

typedef struct {
	char* GetHostDetails_Name;
	char* GetHostDetails_Address;
} df_hostdetails;

typedef struct {
	int StopBackupDrive_Success;
	char* StopBackupDrive_Message;
} df_stopbackupdriveresult;

typedef struct {
	char* Version_Service;
	char* Version_Protocol;
	char* Version_CommandDef;
	char* Version_System;
} df_version;

typedef struct {
	int RoomKey;
	char* IPAddress;
	int Channel;
	char* RoomName;
	int ShortName;
	int IsMultiRoom;
	int PlaybackCapability;
	int RippingCapability;
	int MusicManagementCapability;
	int RoomID;
	char* HostName;
	int Created;
	int Modified;
} df_room;

typedef struct {
	int Running;
	int AlbumKey;
	char* AlbumName;
	int SourceStoreKey;
	int DestinationStoreKey;
	int Progress;
} df_movealbumstatus;

typedef struct {
	int BackupDrive_Success;
	char* BackupDrive_Message;
} df_backupresult;

typedef struct {
	int GetSearchOffset_Return;
	int GetSearchOffset_Count;
} df_searchoffset;

typedef struct {
	int Running;
	int AlbumKey;
	char* AlbumName;
	int Progress;
} df_type0;

typedef struct {
	int GenreKey;
	char* GenreName;
	df_date Created;
	df_date Modified;
	int Ordinal;
	int Storage;
} df_genre;

typedef struct {
	int Source;
	char* Name;
	char* Album;
	char* Artist;
	char* Genre;
	char* Comment;
	df_time Length;
} df_trackfromplayer;

typedef struct {
	int SetDriveUsage_Success;
	int SetDriveUsage_DriveInUse;
	char* SetDriveUsage_Message;
} df_driveusageresult;

typedef struct {
	int SubGenreKey;
	int GenreKey;
	char* SubGenreName;
	df_date Created;
	df_date Modified;
	int Ordinal;
} df_subgenre;

typedef struct {
	int PromoteShareToMusicStore_Success;
	char* PromoteShareToMusicStore_Message;
} df_promoteshare;

typedef struct {
	int UpdateDrive_Return;
	char* UpdateDrive_ErrorMessage;
} df_updatedrivedetails;





// Row types

struct __df_driverow {
	struct __df_driverow *next;

	int DriveKey;
	char* DriveLetter;
	int IsPrimary;
	char* RootPath;
	char* SharePath;
	int Usage;
	df_date LastBackup;
};

typedef struct __df_driverow df_driverow;

struct __df_outputdevicerow {
	struct __df_outputdevicerow *next;

	char* Name;
	int OutputDeviceID;
};

typedef struct __df_outputdevicerow df_outputdevicerow;

struct __df_type1row {
	struct __df_type1row *next;

	char* Artist;
	char* Album;
	int Tracks;
	int TracksRipped;
	int Errors;
	df_time TimeTaken;
	df_time TimeLeft;
	char* Track;
	int TrackPercent;
	char* UserMessage;
	char* LookupProviderUsed;
	char* Destination;
};

typedef struct __df_type1row df_type1row;

struct __df_settingsexrow {
	struct __df_settingsexrow *next;

	char* RegistryKey;
	char* Value;
	int ReadOnly;
	char* Default;
	int MaxLength;
	int ValueType;
	char* TabCaption;
	char* Category;
	char* Caption;
	char* ShortTabCaption;
	char* ShortCategory;
	char* ShortCaption;
	char* Description;
};

typedef struct __df_settingsexrow df_settingsexrow;

struct __df_effformatrow {
	struct __df_effformatrow *next;

	char* FieldName;
	char* FormatSource;
};

typedef struct __df_effformatrow df_effformatrow;

struct __df_artistrow {
	struct __df_artistrow *next;

	int ArtistKey;
	char* Name;
};

typedef struct __df_artistrow df_artistrow;

struct __df_type0row {
	struct __df_type0row *next;

	int TrackKey;
	char* Name;
	char* SortName;
	char* Type;
	df_time Length;
	df_date Created;
	df_date LastModified;
	int Ordinal;
	int ExtendedInfoAvail;
	int Storage;
	int SampleRate;
	int BitsPerSample;
	int ChannelCount;
	int AlbumKey;
	char* AlbumName;
	int ArtistKey;
	char* ArtistName;
	char* SubGenre;
	char* CoverURL;
	int BitRate;
	int Source;
	int CoverAvailable;
	int Hidden;
};

typedef struct __df_type0row df_type0row;

struct __df_tracksotherrow {
	struct __df_tracksotherrow *next;

	int TrackKey;
	char* Name;
	char* SortName;
	char* Type;
	df_time Length;
	df_date Created;
	df_date LastModified;
	int Ordinal;
	int ExtendedInfoAvail;
	int Storage;
	int SampleRate;
	int BitsPerSample;
	int ChannelCount;
	int AlbumKey;
	char* AlbumName;
	int ArtistKey;
	char* ArtistName;
	char* SubGenre;
	char* CoverURL;
	int BitRate;
};

typedef struct __df_tracksotherrow df_tracksotherrow;

struct __df_exttrackinforow {
	struct __df_exttrackinforow *next;

	int TrackKey;
	char* CompositionDate;
	char* Part;
	char* PerformanceDate;
	char* Work;
};

typedef struct __df_exttrackinforow df_exttrackinforow;

struct __df_outputchannelrow {
	struct __df_outputchannelrow *next;

	char* InitString;
	int ChannelID;
};

typedef struct __df_outputchannelrow df_outputchannelrow;

struct __df_currplaylistexrow {
	struct __df_currplaylistexrow *next;

	int TrackKey;
	char* Name;
	char* SortName;
	char* Type;
	df_time Length;
	df_date Created;
	df_date LastModified;
	int Ordinal;
	int ExtendedInfoAvail;
	int Storage;
	int SampleRate;
	int BitsPerSample;
	int ChannelCount;
	int AlbumKey;
	char* AlbumName;
	int ArtistKey;
	char* ArtistName;
	char* SubGenre;
	char* CoverURL;
	int BitRate;
	int Source;
};

typedef struct __df_currplaylistexrow df_currplaylistexrow;

struct __df_extcontributorrow {
	struct __df_extcontributorrow *next;

	int ContributorKey;
	char* Name;
	int ContributorType;
};

typedef struct __df_extcontributorrow df_extcontributorrow;

struct __df_encodingstatusrow {
	struct __df_encodingstatusrow *next;

	char* Artist;
	char* Album;
	char* Track;
	char* Activity;
	int Max;
	int Progress;
};

typedef struct __df_encodingstatusrow df_encodingstatusrow;

struct __df_vtunerpresetrow {
	struct __df_vtunerpresetrow *next;

	int Key;
	int ChannelNumber;
	char* ChannelName;
	df_date Modified;
	df_time ModifiedTime;
	df_date Created;
	df_time CreatedTime;
	char* Name;
	int NodeType;
	char* UrlBookmark;
	char* UrlPlay;
	char* UrlChildren;
	char* UrlChildrenBackup;
	char* ID;
	char* Description;
	char* ParentDescription;
	char* Format;
	char* Language;
	char* City;
	char* State;
	char* Country;
	char* Location;
	int Bandwidth;
	char* MimeType;
	int ReliabilityRating;
};

typedef struct __df_vtunerpresetrow df_vtunerpresetrow;

struct __df_albumrow {
	struct __df_albumrow *next;

	int PlaylistKey;
	char* Name;
	int ArtistKey;
	char* ArtistName;
	int IsAlbum;
	df_date Created;
	df_date LastModified;
	int HitCount;
	int ExtendedInfoAvail;
	int Storage;
};

typedef struct __df_albumrow df_albumrow;

struct __df_trackrow {
	struct __df_trackrow *next;

	int TrackKey;
	char* Name;
	char* SortName;
	char* Type;
	df_time Length;
	df_date Created;
	df_date LastModified;
	int Ordinal;
	int ExtendedInfoAvail;
	int Storage;
	int SampleRate;
	int BitsPerSample;
	int ChannelCount;
};

typedef struct __df_trackrow df_trackrow;

struct __df_settingsrow {
	struct __df_settingsrow *next;

	char* RegistryKey;
	char* Value;
	int ReadOnly;
	char* Default;
	int MaxLength;
};

typedef struct __df_settingsrow df_settingsrow;

struct __df_linkedroomdetailrow {
	struct __df_linkedroomdetailrow *next;

	int RoomKey;
	char* IPAddress;
	int Channel;
	char* RoomName;
	char* ShortName;
	int IsMultiRoom;
	int PlaybackCapability;
	int RippingCapability;
	int MusicManagementCapability;
	int RoomID;
	char* HostName;
	df_date Created;
	df_date Modified;
};

typedef struct __df_linkedroomdetailrow df_linkedroomdetailrow;

struct __df_albumdetailrow {
	struct __df_albumdetailrow *next;

	int PlaylistKey;
	char* Name;
	int ArtistKey;
	char* ArtistName;
	int IsAlbum;
	df_date Created;
	df_date LastModified;
	int HitCount;
	int ExtendedInfoAvail;
	int Storage;
	char* Genre;
	int TrackCount;
	char* CoverImage;
};

typedef struct __df_albumdetailrow df_albumdetailrow;

struct __df_genrerow {
	struct __df_genrerow *next;

	int GenreKey;
	char* Genre;
	df_date Created;
	df_date LastModified;
	int GenreOrdinal;
	int Storage;
};

typedef struct __df_genrerow df_genrerow;

struct __df_type4row {
	struct __df_type4row *next;

	int QueueKey;
	char* Status;
	int Retries;
	char* LastError;
	df_date CreatedDate;
	df_time CreatedTime;
	df_date ModifiedDate;
	df_time ModifiedTime;
	df_date LastRetryDate;
	df_time LastRetryTime;
	int AlbumKey;
};

typedef struct __df_type4row df_type4row;

struct __df_mediarendererrow {
	struct __df_mediarendererrow *next;

	char* FriendlyName;
	char* UDN;
	char* Manufacturer;
	char* ModelNumber;
	char* SupportedExtensions;
};

typedef struct __df_mediarendererrow df_mediarendererrow;

struct __df_subgenrerow {
	struct __df_subgenrerow *next;

	int SubGenreKey;
	char* SubGenre;
	df_date Created;
	df_date LastModified;
	int SubGenreOrdinal;
};

typedef struct __df_subgenrerow df_subgenrerow;

struct __df_statusmessagerow {
	struct __df_statusmessagerow *next;

	int MessageAddress;
	char* Severity;
	char* Category;
	df_date DateCreated;
	df_time TimeCreated;
	int Tag;
};

typedef struct __df_statusmessagerow df_statusmessagerow;

struct __df_type3row {
	struct __df_type3row *next;

	int TrackKey;
	char* Name;
	char* SortName;
	char* Type;
	df_time Length;
	df_date Created;
	df_date LastModified;
	int Ordinal;
	int ExtendedInfoAvail;
	int Storage;
	int SampleRate;
	int BitsPerSample;
	int ChannelCount;
	int AlbumKey;
	char* AlbumName;
	int ArtistKey;
	char* ArtistName;
	char* SubGenre;
	char* CoverURL;
	int BitRate;
	int CoverAvailable;
};

typedef struct __df_type3row df_type3row;

struct __df_exttrackcontribrow {
	struct __df_exttrackcontribrow *next;

	int TrackKey;
	int ContributorKey;
	char* Name;
	int ContributorType;
};

typedef struct __df_exttrackcontribrow df_exttrackcontribrow;

struct __df_vtunerplayedrow {
	struct __df_vtunerplayedrow *next;

	int Key;
	int HitCount;
	df_date LastPlayed;
	df_time LastPlayedTime;
	df_date Created;
	df_time CreatedTime;
	char* Name;
	int NodeType;
	char* UrlBookmark;
	char* UrlPlay;
	char* UrlChildren;
	char* UrlChildrenBackup;
	char* ID;
	char* Description;
	char* ParentDescription;
	char* Format;
	char* Language;
	char* City;
	char* State;
	char* Country;
	char* Location;
	int Bandwidth;
	char* MimeType;
	int ReliabilityRating;
};

typedef struct __df_vtunerplayedrow df_vtunerplayedrow;

struct __df_cddbgenrerow {
	struct __df_cddbgenrerow *next;

	int CDDBGenreKey;
	char* Name;
	int SubGenreKey;
	char* SubGenreName;
};

typedef struct __df_cddbgenrerow df_cddbgenrerow;

struct __df_playerinstancerow {
	struct __df_playerinstancerow *next;

	int Key;
	char* Name;
	int OutputDeviceID;
	int SourceLineID;
};

typedef struct __df_playerinstancerow df_playerinstancerow;

struct __df_albumotherrow {
	struct __df_albumotherrow *next;

	int PlaylistKey;
	char* Name;
	int ArtistKey;
	char* ArtistName;
	int IsAlbum;
	df_date Created;
	df_date LastModified;
	int HitCount;
	int ExtendedInfoAvail;
	int Storage;
	int GenreKey;
	char* Genre;
	int SubGenreKey;
	char* SubGenre;
	int TrackCount;
	int LowQuality;
	int StorageKey;
	char* StorageName;
	int ProviderUsed;
};

typedef struct __df_albumotherrow df_albumotherrow;

struct __df_roomrow {
	struct __df_roomrow *next;

	int RoomKey;
	char* IPAddress;
	int Channel;
	char* Name;
	char* ShortName;
	int IsMultiRoom;
	int PlaybackCapability;
	int RippingCapability;
	int MusicManagementCapability;
	int RoomID;
	char* HostName;
};

typedef struct __df_roomrow df_roomrow;

struct __df_currentplaylistrow {
	struct __df_currentplaylistrow *next;

	int TrackKey;
	char* Name;
	char* SortName;
	char* Type;
	df_time Length;
	df_date Created;
	df_date LastModified;
	int Ordinal;
	int ExtendedInfoAvail;
	int Storage;
	int SampleRate;
	int BitsPerSample;
	int ChannelCount;
	int Source;
};

typedef struct __df_currentplaylistrow df_currentplaylistrow;

struct __df_storerow {
	struct __df_storerow *next;

	int MusicStoreKey;
	char* Path;
	int Local;
	char* IPAddress;
	int Online;
	df_date Created;
	df_date LastModified;
	char* State;
	int Priority;
	df_date LastConnected;
};

typedef struct __df_storerow df_storerow;

struct __df_statusrow {
	struct __df_statusrow *next;

	char* StatusSettingName;
	char* StatusSettingValue;
};

typedef struct __df_statusrow df_statusrow;

struct __df_networkadaptorrow {
	struct __df_networkadaptorrow *next;

	int DeviceID;
	char* Description;
	char* MacAddress;
	int DhcpEnabled;
	char* IpAddress;
	char* SubnetMask;
	char* DefaultGateway;
	char* DnsServer;
};

typedef struct __df_networkadaptorrow df_networkadaptorrow;

struct __df_extworksrow {
	struct __df_extworksrow *next;

	char* Work;
};

typedef struct __df_extworksrow df_extworksrow;

struct __df_backuplogdetailrow {
	struct __df_backuplogdetailrow *next;

	int BackupLogKey;
	int BackupJobKey;
	int ExecutionType;
	char* Name;
	int BackupType;
	char* SourcePath;
	char* DestinationPath;
	df_date StartDate;
	df_time StartTime;
	df_date FinishDate;
	df_time FinishTime;
	int Result;
	int TotalFolders;
	int TotalFiles;
	int TotalKiloBytes;
	int TotalErrors;
	char* ErrorDetail;
};

typedef struct __df_backuplogdetailrow df_backuplogdetailrow;

struct __df_extalbumcreditrow {
	struct __df_extalbumcreditrow *next;

	int CreditKey;
	int PlaylistKey;
	char* Description;
	int ContributorKey;
	char* ContributorName;
};

typedef struct __df_extalbumcreditrow df_extalbumcreditrow;

struct __df_trackrangerow {
	struct __df_trackrangerow *next;

	int TrackKey;
	char* Name;
	char* SortName;
	char* Type;
	df_time Length;
	df_date Created;
	df_date LastModified;
	int Ordinal;
	int ExtendedInfoAvail;
	int Storage;
	int SampleRate;
	int BitsPerSample;
	int ChannelCount;
	int AllTracksOffset;
};

typedef struct __df_trackrangerow df_trackrangerow;

struct __df_keyvaluerow {
	struct __df_keyvaluerow *next;

	char* Name;
	char* Value;
};

typedef struct __df_keyvaluerow df_keyvaluerow;

struct __df_backuplogrow {
	struct __df_backuplogrow *next;

	int BackupLogKey;
	int BackupJobKey;
	int ExecutionType;
	char* Name;
	int BackupType;
	char* SourcePath;
	char* DestinationPath;
	df_date StartDate;
	df_time StartTime;
	df_date FinishDate;
	df_time FinishTime;
	int Result;
	int TotalFolders;
	int TotalFiles;
	int TotalKiloBytes;
	int TotalErrors;
};

typedef struct __df_backuplogrow df_backuplogrow;

struct __df_tracksforplaylistrow {
	struct __df_tracksforplaylistrow *next;

	int TrackKey;
	char* Name;
	char* SortName;
	char* Type;
	df_time Length;
	df_date Created;
	df_date LastModified;
	int Ordinal;
	int ExtendedInfoAvail;
	int Storage;
	int SampleRate;
	int BitsPerSample;
	int ChannelCount;
	int Hidden;
};

typedef struct __df_tracksforplaylistrow df_tracksforplaylistrow;

struct __df_rippingalertrow {
	struct __df_rippingalertrow *next;

	int AlertKey;
	char* Severity;
	char* Category;
	df_date Created;
	df_time Time;
};

typedef struct __df_rippingalertrow df_rippingalertrow;

struct __df_rippingstatusrow {
	struct __df_rippingstatusrow *next;

	char* Artist;
	char* Album;
	int Tracks;
	int TracksRipped;
	int Errors;
	df_time TimeTaken;
	df_time TimeLeft;
	char* Track;
	int TrackPercent;
	char* UserMessage;
	char* LookupProviderUsed;
};

typedef struct __df_rippingstatusrow df_rippingstatusrow;

struct __df_extalbuminforow {
	struct __df_extalbuminforow *next;

	int PlaylistKey;
	int Discs;
	int DiscNumber;
	char* CatalogID;
	char* ImageURL;
};

typedef struct __df_extalbuminforow df_extalbuminforow;

struct __df_backupjobrow {
	struct __df_backupjobrow *next;

	int BackupJobKey;
	int SourceDriveKey;
	int DestinationDriveKey;
	char* Name;
	int BackupType;
	int BackupPeriod;
	int PeriodValue;
	df_date RunDate;
	df_time RunTime;
	df_date NextRunDate;
	df_time NextRunTime;
	df_date LastRunDate;
	df_time LastRunTime;
	int JobStatus;
	int LastResult;
};

typedef struct __df_backupjobrow df_backupjobrow;

struct __df_genressubgenresrow {
	struct __df_genressubgenresrow *next;

	int SubGenreKey;
	char* SubGenre;
	int GenreKey;
	char* Genre;
	int GenreOrdinal;
	int SubGenreOrdinal;
	int Storage;
};

typedef struct __df_genressubgenresrow df_genressubgenresrow;

struct __df_alertdetailrow {
	struct __df_alertdetailrow *next;

	int AlertKey;
	char* Severity;
	char* Category;
	char* Module;
	char* Message;
	df_date Created;
	df_date Modified;
	df_date Sent;
	char* UserMessage;
};

typedef struct __df_alertdetailrow df_alertdetailrow;

struct __df_encodingqueuerow {
	struct __df_encodingqueuerow *next;

	char* Value;
};

typedef struct __df_encodingqueuerow df_encodingqueuerow;

struct __df_movealbumgetqueuerow {
	struct __df_movealbumgetqueuerow *next;

	int QueueKey;
	char* Status;
	int Retries;
	char* LastError;
	df_date CreatedDate;
	df_time CreatedTime;
	df_date ModifiedDate;
	df_time ModifiedTime;
	df_date LastRetryDate;
	df_time LastRetryTime;
	int AlbumKey;
	int StoreKey;
};

typedef struct __df_movealbumgetqueuerow df_movealbumgetqueuerow;

struct __df_type2row {
	struct __df_type2row *next;

	int PlaylistKey;
	char* Name;
	int ArtistKey;
	char* ArtistName;
	int IsAlbum;
	df_date Created;
	df_date LastModified;
	int HitCount;
	int ExtendedInfoAvail;
	int Storage;
	int GenreKey;
	char* Genre;
	int SubGenreKey;
	char* SubGenre;
	int TrackCount;
	int LowQuality;
	int StorageKey;
	char* StorageName;
	int ProviderUsed;
	char* CoverURL;
	int CoverAvailable;
};

typedef struct __df_type2row df_type2row;

struct __df_storedetailrow {
	struct __df_storedetailrow *next;

	int MusicStoreKey;
	char* Path;
	int Local;
	char* IPAddress;
	int Online;
	df_date Created;
	df_date LastModified;
	char* State;
	int Priority;
	df_date LastConnected;
	char* Username;
	char* Password;
	df_date LastScanned;
	char* SpaceUsed;
	char* SpaceAvailable;
	int NumberOfAlbums;
};

typedef struct __df_storedetailrow df_storedetailrow;

struct __df_externalstoragerow {
	struct __df_externalstoragerow *next;

	int StorageKey;
	char* IPAddress;
	char* HostName;
	char* ShareName;
	char* FullSharePath;
	char* State;
	char* LastState;
	int Active;
	df_date Created;
	df_date Modified;
	df_date LastScanDate;
	df_time LastScanTime;
	char* UserName;
	char* Password;
	char* ScanIgnore;
};

typedef struct __df_externalstoragerow df_externalstoragerow;

struct __df_bulklookuprow {
	struct __df_bulklookuprow *next;

	int PlaylistKey;
	int Success;
	char* Message;
};

typedef struct __df_bulklookuprow df_bulklookuprow;

struct __df_vtunernoderow {
	struct __df_vtunernoderow *next;

	char* Name;
	int NodeType;
	char* UrlBookmark;
	char* UrlPlay;
	char* UrlChildren;
	char* UrlChildrenBackup;
	char* ID;
	char* Description;
	char* ParentDescription;
	char* Format;
	char* Language;
	char* City;
	char* State;
	char* Country;
	char* Location;
	int Bandwidth;
	char* MimeType;
	int ReliabilityRating;
};

typedef struct __df_vtunernoderow df_vtunernoderow;

struct __df_devicerow {
	struct __df_devicerow *next;

	int DeviceKey;
	char* Name;
	char* SerialNumber;
	char* Type;
	char* State;
	char* LastState;
	df_date LastConnected;
	int Connections;
	int Sync;
};

typedef struct __df_devicerow df_devicerow;








#endif


