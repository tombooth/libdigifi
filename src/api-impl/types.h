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
 

#include <stdlib.h>
 
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
    int capabilities;
    char *streamid;
} df_detailedtrack;

typedef struct {
	char *name;
	int source;
	char *path;
    int capabilities;
    char *streamid;
} df_trackname;











struct __type_2 {
   struct __type_2 *next;

   
      int SearchNumber;
      char* StatusSettingName;
      char* StatusSettingValue;
};

typedef struct __type_2 type_2;



void type_2_free(type_2* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->StatusSettingName);
      free(ptr->StatusSettingValue);
      free(ptr);
   }
}










typedef struct {
   
      int SearchNumber;
      char* CommandName;
} type_3;



void type_3_free(type_3* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->CommandName);
      free(ptr);
   }
}










struct __type_4 {
   struct __type_4 *next;

   
      int SearchNumber;
      char* CommandName;
      char* FieldName;
      char* FormatSource;
};

typedef struct __type_4 type_4;



void type_4_free(type_4* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->CommandName);
      free(ptr->FieldName);
      free(ptr->FormatSource);
      free(ptr);
   }
}










typedef struct {
   
      int SearchNumber;
      int TargetSearchNumber;
      int FilterSearch_Return;
} type_5;













struct __type_6 {
   struct __type_6 *next;

   
      int SearchNumber;
      int TargetSearchNumber;
};

typedef struct __type_6 type_6;













typedef struct {
   
      int SearchNumber;
      int GetRooms_Return;
} type_7;













struct __type_8 {
   struct __type_8 *next;

   
      int SearchNumber;
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

typedef struct __type_8 type_8;



void type_8_free(type_8* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->IPAddress);
      free(ptr->Name);
      free(ptr->ShortName);
      free(ptr->HostName);
      free(ptr);
   }
}










struct __type_9 {
   struct __type_9 *next;

   
      int SearchNumber;
      int MessageAddress;
      char* Severity;
      char* Category;
      df_date DateCreated;
      df_time TimeCreated;
      int Tag;
};

typedef struct __type_9 type_9;



void type_9_free(type_9* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Severity);
      free(ptr->Category);
      free(ptr);
   }
}










struct __type_10 {
   struct __type_10 *next;

   
      int SearchNumber;
      int RoomID;
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

typedef struct __type_10 type_10;



void type_10_free(type_10* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Name);
      free(ptr->SortName);
      free(ptr->Type);
      free(ptr);
   }
}










struct __type_11 {
   struct __type_11 *next;

   
      int SearchNumber;
      int RoomID;
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

typedef struct __type_11 type_11;



void type_11_free(type_11* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Name);
      free(ptr->SortName);
      free(ptr->Type);
      free(ptr->AlbumName);
      free(ptr->ArtistName);
      free(ptr->SubGenre);
      free(ptr->CoverURL);
      free(ptr);
   }
}










struct __type_12 {
   struct __type_12 *next;

   
      int SearchNumber;
      int AlertKey;
      char* Severity;
      char* Category;
      df_date Created;
      df_time Time;
};

typedef struct __type_12 type_12;



void type_12_free(type_12* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Severity);
      free(ptr->Category);
      free(ptr);
   }
}










struct __type_13 {
   struct __type_13 *next;

   
      int SearchNumber;
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

typedef struct __type_13 type_13;



void type_13_free(type_13* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Severity);
      free(ptr->Category);
      free(ptr->Module);
      free(ptr->Message);
      free(ptr->UserMessage);
      free(ptr);
   }
}










struct __type_14 {
   struct __type_14 *next;

   
      int SearchNumber;
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

typedef struct __type_14 type_14;



void type_14_free(type_14* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Artist);
      free(ptr->Album);
      free(ptr->Track);
      free(ptr->UserMessage);
      free(ptr->LookupProviderUsed);
      free(ptr->Destination);
      free(ptr);
   }
}










struct __type_15 {
   struct __type_15 *next;

   
      int SearchNumber;
      char* RegistryKey;
      char* Value;
      int ReadOnly;
      char* Default;
      int MaxLength;
};

typedef struct __type_15 type_15;



void type_15_free(type_15* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->RegistryKey);
      free(ptr->Value);
      free(ptr->Default);
      free(ptr);
   }
}










struct __type_16 {
   struct __type_16 *next;

   
      int SearchNumber;
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

typedef struct __type_16 type_16;



void type_16_free(type_16* ptr) {
   if (ptr == 0) { return; }
   else {
      
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
}










struct __type_17 {
   struct __type_17 *next;

   
      int SearchNumber;
      int DriveKey;
      char* DriveLetter;
      int IsPrimary;
      char* RootPath;
      char* SharePath;
      int Usage;
      df_date LastBackup;
};

typedef struct __type_17 type_17;



void type_17_free(type_17* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->DriveLetter);
      free(ptr->RootPath);
      free(ptr->SharePath);
      free(ptr);
   }
}










struct __type_18 {
   struct __type_18 *next;

   
      int SearchNumber;
      char* Value;
};

typedef struct __type_18 type_18;



void type_18_free(type_18* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Value);
      free(ptr);
   }
}










struct __type_19 {
   struct __type_19 *next;

   
      int SearchNumber;
      char* Artist;
      char* Album;
      char* Track;
      char* Activity;
      int Max;
      int Progress;
};

typedef struct __type_19 type_19;



void type_19_free(type_19* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Artist);
      free(ptr->Album);
      free(ptr->Track);
      free(ptr->Activity);
      free(ptr);
   }
}










struct __type_20 {
   struct __type_20 *next;

   
      int SearchNumber;
      int Key;
      char* Name;
      int OutputDeviceID;
      int SourceLineID;
};

typedef struct __type_20 type_20;



void type_20_free(type_20* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Name);
      free(ptr);
   }
}










struct __type_21 {
   struct __type_21 *next;

   
      int SearchNumber;
      char* Name;
      int OutputDeviceID;
};

typedef struct __type_21 type_21;



void type_21_free(type_21* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Name);
      free(ptr);
   }
}










struct __type_22 {
   struct __type_22 *next;

   
      int SearchNumber;
      char* FriendlyName;
      char* UDN;
      char* Manufacturer;
      char* ModelNumber;
      char* SupportedExtensions;
};

typedef struct __type_22 type_22;



void type_22_free(type_22* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->FriendlyName);
      free(ptr->UDN);
      free(ptr->Manufacturer);
      free(ptr->ModelNumber);
      free(ptr->SupportedExtensions);
      free(ptr);
   }
}










struct __type_23 {
   struct __type_23 *next;

   
      int SearchNumber;
      int ChannelNumber;
      char* ChannelDescription;
};

typedef struct __type_23 type_23;



void type_23_free(type_23* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->ChannelDescription);
      free(ptr);
   }
}










struct __type_24 {
   struct __type_24 *next;

   
      int SearchNumber;
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

typedef struct __type_24 type_24;



void type_24_free(type_24* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Name);
      free(ptr->SerialNumber);
      free(ptr->Type);
      free(ptr->State);
      free(ptr->LastState);
      free(ptr);
   }
}










struct __type_25 {
   struct __type_25 *next;

   
      int SearchNumber;
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

typedef struct __type_25 type_25;



void type_25_free(type_25* ptr) {
   if (ptr == 0) { return; }
   else {
      
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
}










typedef struct {
   
      int SearchNumber;
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
      int ChildRoomCount;
} type_26;



void type_26_free(type_26* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->IPAddress);
      free(ptr->RoomName);
      free(ptr->ShortName);
      free(ptr->HostName);
      free(ptr);
   }
}










struct __type_27 {
   struct __type_27 *next;

   
      int SearchNumber;
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

typedef struct __type_27 type_27;



void type_27_free(type_27* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->IPAddress);
      free(ptr->RoomName);
      free(ptr->ShortName);
      free(ptr->HostName);
      free(ptr);
   }
}










struct __type_28 {
   struct __type_28 *next;

   
      int SearchNumber;
      char* Col1;
      char* Col2;
      char* Col3;
      char* Col4;
      char* Col5;
      char* Col6;
};

typedef struct __type_28 type_28;



void type_28_free(type_28* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Col1);
      free(ptr->Col2);
      free(ptr->Col3);
      free(ptr->Col4);
      free(ptr->Col5);
      free(ptr->Col6);
      free(ptr);
   }
}










struct __type_29 {
   struct __type_29 *next;

   
      int SearchNumber;
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

typedef struct __type_29 type_29;



void type_29_free(type_29* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Name);
      free(ptr);
   }
}










struct __type_30 {
   struct __type_30 *next;

   
      int SearchNumber;
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

typedef struct __type_30 type_30;



void type_30_free(type_30* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Name);
      free(ptr->SourcePath);
      free(ptr->DestinationPath);
      free(ptr);
   }
}










struct __type_31 {
   struct __type_31 *next;

   
      int SearchNumber;
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

typedef struct __type_31 type_31;



void type_31_free(type_31* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Name);
      free(ptr->SourcePath);
      free(ptr->DestinationPath);
      free(ptr->ErrorDetail);
      free(ptr);
   }
}










struct __type_32 {
   struct __type_32 *next;

   
      int SearchNumber;
      int DeviceID;
      char* Description;
      char* MacAddress;
      int DhcpEnabled;
      char* IpAddress;
      char* SubnetMask;
      char* DefaultGateway;
      char* DnsServer;
};

typedef struct __type_32 type_32;



void type_32_free(type_32* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Description);
      free(ptr->MacAddress);
      free(ptr->IpAddress);
      free(ptr->SubnetMask);
      free(ptr->DefaultGateway);
      free(ptr->DnsServer);
      free(ptr);
   }
}










struct __type_33 {
   struct __type_33 *next;

   
      int SearchNumber;
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

typedef struct __type_33 type_33;



void type_33_free(type_33* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Name);
      free(ptr->ArtistName);
      free(ptr);
   }
}










struct __type_34 {
   struct __type_34 *next;

   
      int SearchNumber;
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

typedef struct __type_34 type_34;



void type_34_free(type_34* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Name);
      free(ptr->SortName);
      free(ptr->Type);
      free(ptr);
   }
}










struct __type_35 {
   struct __type_35 *next;

   
      int SearchNumber;
      int ContributorKey;
      char* Name;
      int ContributorType;
};

typedef struct __type_35 type_35;



void type_35_free(type_35* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Name);
      free(ptr);
   }
}










struct __type_36 {
   struct __type_36 *next;

   
      int SearchNumber;
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

typedef struct __type_36 type_36;



void type_36_free(type_36* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Name);
      free(ptr->ArtistName);
      free(ptr->Genre);
      free(ptr->SubGenre);
      free(ptr->StorageName);
      free(ptr->CoverURL);
      free(ptr);
   }
}










struct __type_37 {
   struct __type_37 *next;

   
      int SearchNumber;
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

typedef struct __type_37 type_37;



void type_37_free(type_37* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Name);
      free(ptr->ArtistName);
      free(ptr->Genre);
      free(ptr->CoverImage);
      free(ptr);
   }
}










struct __type_38 {
   struct __type_38 *next;

   
      int SearchNumber;
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

typedef struct __type_38 type_38;



void type_38_free(type_38* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Name);
      free(ptr->SortName);
      free(ptr->Type);
      free(ptr);
   }
}










struct __type_39 {
   struct __type_39 *next;

   
      int SearchNumber;
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

typedef struct __type_39 type_39;



void type_39_free(type_39* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Name);
      free(ptr->SortName);
      free(ptr->Type);
      free(ptr);
   }
}










struct __type_40 {
   struct __type_40 *next;

   
      int SearchNumber;
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

typedef struct __type_40 type_40;



void type_40_free(type_40* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Name);
      free(ptr->SortName);
      free(ptr->Type);
      free(ptr->AlbumName);
      free(ptr->ArtistName);
      free(ptr->SubGenre);
      free(ptr->CoverURL);
      free(ptr);
   }
}










struct __type_41 {
   struct __type_41 *next;

   
      int SearchNumber;
      int GenreKey;
      char* Genre;
      df_date Created;
      df_date LastModified;
      int GenreOrdinal;
      int Storage;
};

typedef struct __type_41 type_41;



void type_41_free(type_41* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Genre);
      free(ptr);
   }
}










struct __type_42 {
   struct __type_42 *next;

   
      int SearchNumber;
      int SubGenreKey;
      char* SubGenre;
      df_date Created;
      df_date LastModified;
      int SubGenreOrdinal;
};

typedef struct __type_42 type_42;



void type_42_free(type_42* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->SubGenre);
      free(ptr);
   }
}










struct __type_43 {
   struct __type_43 *next;

   
      int SearchNumber;
      int SubGenreKey;
      char* SubGenre;
      int GenreKey;
      char* Genre;
      int GenreOrdinal;
      int SubGenreOrdinal;
      int Storage;
};

typedef struct __type_43 type_43;



void type_43_free(type_43* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->SubGenre);
      free(ptr->Genre);
      free(ptr);
   }
}










struct __type_44 {
   struct __type_44 *next;

   
      int SearchNumber;
      int CDDBGenreKey;
      char* Name;
      int SubGenreKey;
      char* SubGenreName;
};

typedef struct __type_44 type_44;



void type_44_free(type_44* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Name);
      free(ptr->SubGenreName);
      free(ptr);
   }
}










struct __type_45 {
   struct __type_45 *next;

   
      int SearchNumber;
      int PlaylistKey;
      int Success;
      char* Message;
};

typedef struct __type_45 type_45;



void type_45_free(type_45* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Message);
      free(ptr);
   }
}










struct __type_46 {
   struct __type_46 *next;

   
      int SearchNumber;
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
      char* AlbumName;
};

typedef struct __type_46 type_46;



void type_46_free(type_46* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Status);
      free(ptr->LastError);
      free(ptr->AlbumName);
      free(ptr);
   }
}










struct __type_47 {
   struct __type_47 *next;

   
      int SearchNumber;
      int CreditKey;
      int PlaylistKey;
      char* Description;
      int ContributorKey;
      char* ContributorName;
};

typedef struct __type_47 type_47;



void type_47_free(type_47* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Description);
      free(ptr->ContributorName);
      free(ptr);
   }
}










struct __type_48 {
   struct __type_48 *next;

   
      int SearchNumber;
      int PlaylistKey;
      int Discs;
      int DiscNumber;
      char* CatalogID;
      char* ImageURL;
};

typedef struct __type_48 type_48;



void type_48_free(type_48* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->CatalogID);
      free(ptr->ImageURL);
      free(ptr);
   }
}










struct __type_49 {
   struct __type_49 *next;

   
      int SearchNumber;
      int TrackKey;
      int ContributorKey;
      char* Name;
      int ContributorType;
};

typedef struct __type_49 type_49;



void type_49_free(type_49* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Name);
      free(ptr);
   }
}










struct __type_50 {
   struct __type_50 *next;

   
      int SearchNumber;
      int TrackKey;
      char* CompositionDate;
      char* Part;
      char* PerformanceDate;
      char* Work;
};

typedef struct __type_50 type_50;



void type_50_free(type_50* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->CompositionDate);
      free(ptr->Part);
      free(ptr->PerformanceDate);
      free(ptr->Work);
      free(ptr);
   }
}










struct __type_51 {
   struct __type_51 *next;

   
      int SearchNumber;
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

typedef struct __type_51 type_51;



void type_51_free(type_51* ptr) {
   if (ptr == 0) { return; }
   else {
      
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
}










struct __type_52 {
   struct __type_52 *next;

   
      int SearchNumber;
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

typedef struct __type_52 type_52;



void type_52_free(type_52* ptr) {
   if (ptr == 0) { return; }
   else {
      
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
}










struct __type_53 {
   struct __type_53 *next;

   
      int SearchNumber;
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

typedef struct __type_53 type_53;



void type_53_free(type_53* ptr) {
   if (ptr == 0) { return; }
   else {
      
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
}










struct __type_54 {
   struct __type_54 *next;

   
      int SearchNumber;
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

typedef struct __type_54 type_54;



void type_54_free(type_54* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Path);
      free(ptr->IPAddress);
      free(ptr->State);
      free(ptr);
   }
}










typedef struct {
   
      int SearchNumber;
      int GetStoreDetail_Success;
} type_55;













struct __type_56 {
   struct __type_56 *next;

   
      int SearchNumber;
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

typedef struct __type_56 type_56;



void type_56_free(type_56* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Path);
      free(ptr->IPAddress);
      free(ptr->State);
      free(ptr->Username);
      free(ptr->Password);
      free(ptr->SpaceUsed);
      free(ptr->SpaceAvailable);
      free(ptr);
   }
}










struct __type_57 {
   struct __type_57 *next;

   
      int SearchNumber;
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
      char* AlbumName;
};

typedef struct __type_57 type_57;



void type_57_free(type_57* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Status);
      free(ptr->LastError);
      free(ptr->AlbumName);
      free(ptr);
   }
}


















typedef struct {
   
      char* Version_Service;
      char* Version_Protocol;
      char* Version_CommandDef;
      char* Version_System;
} type_60;



void type_60_free(type_60* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Version_Service);
      free(ptr->Version_Protocol);
      free(ptr->Version_CommandDef);
      free(ptr->Version_System);
      free(ptr);
   }
}










typedef struct {
   
      df_date GetSystemTime_Date;
      df_time GetSystemTime_Time;
} type_61;













typedef struct {
   
      char* GetHostDetails_Name;
      char* GetHostDetails_Address;
} type_62;



void type_62_free(type_62* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->GetHostDetails_Name);
      free(ptr->GetHostDetails_Address);
      free(ptr);
   }
}










typedef struct {
   
      int IsBusy;
      char* Status;
      int PercentComplete;
} type_63;



void type_63_free(type_63* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Status);
      free(ptr);
   }
}










typedef struct {
   
      int RoomID;
      int TrackKey;
      char* Name;
      char* Type;
      df_time Length;
      int Source;
} type_64;



void type_64_free(type_64* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Name);
      free(ptr->Type);
      free(ptr);
   }
}










typedef struct {
   
      int RoomID;
      int Source;
      char* Name;
      char* Album;
      char* Artist;
      char* Genre;
      char* Comment;
      df_time Length;
} type_65;



void type_65_free(type_65* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Name);
      free(ptr->Album);
      free(ptr->Artist);
      free(ptr->Genre);
      free(ptr->Comment);
      free(ptr);
   }
}










typedef struct {
   
      int RoomID;
      char* Album;
      char* Artist;
} type_66;



void type_66_free(type_66* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Album);
      free(ptr->Artist);
      free(ptr);
   }
}










typedef struct {
   
      int RoomID;
      df_time TrackLength;
} type_67;













typedef struct {
   
      int RoomID;
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
} type_68;



void type_68_free(type_68* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->TrackName);
      free(ptr->Album);
      free(ptr->Artist);
      free(ptr->Status);
      free(ptr->Version);
      free(ptr);
   }
}










typedef struct {
   
      char* Key;
      char* Message;
      char* Category;
      df_date DateCreated;
} type_69;



void type_69_free(type_69* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Key);
      free(ptr->Message);
      free(ptr->Category);
      free(ptr);
   }
}










typedef struct {
   
      int SuccessCount;
      char* SuccessNames;
      int PartialCount;
      char* PartialNames;
      int FailureCount;
      char* FailureNames;
} type_70;



void type_70_free(type_70* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->SuccessNames);
      free(ptr->PartialNames);
      free(ptr->FailureNames);
      free(ptr);
   }
}










typedef struct {
   
      char* DriveAddress;
      int DriveKey;
      char* DriveLetter;
      int Primary;
      char* RootPath;
      char* SharePath;
      df_date Created;
      df_date Modified;
      int Usage;
      df_date LastBackup;
} type_71;



void type_71_free(type_71* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->DriveAddress);
      free(ptr->DriveLetter);
      free(ptr->RootPath);
      free(ptr->SharePath);
      free(ptr);
   }
}










typedef struct {
   
      char* DriveLetter;
      char* DriveLetterOut;
      char* RootPath;
      char* SharePath;
      int Usage;
} type_72;



void type_72_free(type_72* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->DriveLetter);
      free(ptr->DriveLetterOut);
      free(ptr->RootPath);
      free(ptr->SharePath);
      free(ptr);
   }
}










typedef struct {
   
      char* DriveLetter;
      int AddNewDrive_Return;
      char* AddNewDrive_ErrorMessage;
} type_73;



void type_73_free(type_73* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->DriveLetter);
      free(ptr->AddNewDrive_ErrorMessage);
      free(ptr);
   }
}










typedef struct {
   
      char* DriveKey;
      int UpdateDrive_Return;
      char* UpdateDrive_ErrorMessage;
} type_74;



void type_74_free(type_74* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->DriveKey);
      free(ptr->UpdateDrive_ErrorMessage);
      free(ptr);
   }
}










typedef struct {
   
      char* DriveKey;
      int DeleteDrive_Return;
} type_75;



void type_75_free(type_75* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->DriveKey);
      free(ptr);
   }
}










typedef struct {
   
      char* RoomName;
      int AddNewLinkedRoom_Return;
} type_76;



void type_76_free(type_76* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->RoomName);
      free(ptr);
   }
}










typedef struct {
   
      char* GenreAddress;
      int GenreKey;
      char* GenreName;
      df_date Created;
      df_date Modified;
      int Ordinal;
      int Storage;
} type_77;



void type_77_free(type_77* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->GenreAddress);
      free(ptr->GenreName);
      free(ptr);
   }
}










typedef struct {
   
      char* SubGenreAddress;
      int SubGenreKey;
      int GenreKey;
      char* SubGenreName;
      df_date Created;
      df_date Modified;
      int Ordinal;
} type_78;



void type_78_free(type_78* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->SubGenreAddress);
      free(ptr->SubGenreName);
      free(ptr);
   }
}










typedef struct {
   
      int AddExternalStorage_Success;
      char* AddExternalStorage_Message;
      int AddExternalStorage_Key;
      char* AddExternalStorage_Hostname;
      char* AddExternalStorage_IPAddress;
      char* AddExternalStorage_ShareName;
      char* AddExternalStorage_Username;
      char* AddExternalStorage_Password;
} type_79;



void type_79_free(type_79* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->AddExternalStorage_Message);
      free(ptr->AddExternalStorage_Hostname);
      free(ptr->AddExternalStorage_IPAddress);
      free(ptr->AddExternalStorage_ShareName);
      free(ptr->AddExternalStorage_Username);
      free(ptr->AddExternalStorage_Password);
      free(ptr);
   }
}










typedef struct {
   
      char* StorageAddress;
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
} type_80;



void type_80_free(type_80* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->StorageAddress);
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
}










typedef struct {
   
      char* DriveKey;
      int SetDriveUsage_Success;
      int SetDriveUsage_DriveInUse;
      char* SetDriveUsage_Message;
} type_81;



void type_81_free(type_81* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->DriveKey);
      free(ptr->SetDriveUsage_Message);
      free(ptr);
   }
}










typedef struct {
   
      char* SourceDriveKey;
      char* DestDriveKey;
      int BackupDrive_Success;
      char* BackupDrive_Message;
} type_82;



void type_82_free(type_82* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->SourceDriveKey);
      free(ptr->DestDriveKey);
      free(ptr->BackupDrive_Message);
      free(ptr);
   }
}










typedef struct {
   
      int StopBackupDrive_Success;
      char* StopBackupDrive_Message;
} type_83;



void type_83_free(type_83* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->StopBackupDrive_Message);
      free(ptr);
   }
}










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
} type_84;



void type_84_free(type_84* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Backup_SourceDrive);
      free(ptr->Backup_DestDrive);
      free(ptr->Backup_Type);
      free(ptr->Backup_Status);
      free(ptr->Backup_CurrentFile);
      free(ptr->Backup_LastError);
      free(ptr);
   }
}










typedef struct {
   
      char* SourceDriveAddress;
      char* DestinationDriveAddress;
      int AddNewBackupJob_Return;
} type_85;



void type_85_free(type_85* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->SourceDriveAddress);
      free(ptr->DestinationDriveAddress);
      free(ptr);
   }
}










typedef struct {
   
      char* AlbumKey;
      char* TrackKey;
      int RestoreSingleTrack_Return;
} type_86;



void type_86_free(type_86* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->AlbumKey);
      free(ptr->TrackKey);
      free(ptr);
   }
}










typedef struct {
   
      char* Address;
      char* CoverImageName;
      char* CoverImageURI;
} type_87;



void type_87_free(type_87* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->Address);
      free(ptr->CoverImageName);
      free(ptr->CoverImageURI);
      free(ptr);
   }
}










typedef struct {
   
      int Running;
      int AlbumKey;
      char* AlbumName;
      int Progress;
} type_88;



void type_88_free(type_88* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->AlbumName);
      free(ptr);
   }
}










typedef struct {
   
      int RoomID;
      char* TrackName_Return;
      int TrackSource_Return;
      char* TrackPath_Return;
} type_89;



void type_89_free(type_89* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->TrackName_Return);
      free(ptr->TrackPath_Return);
      free(ptr);
   }
}










typedef struct {
   
      int RoomID;
      int TrackKey;
      char* TrackName;
      int AlbumKey;
      char* Album;
      int ArtistKey;
      char* Artist;
      int GenreKey;
      char* Genre;
      df_time Length;
      int Source;
      char* TrackPath;
} type_90;



void type_90_free(type_90* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->TrackName);
      free(ptr->Album);
      free(ptr->Artist);
      free(ptr->Genre);
      free(ptr->TrackPath);
      free(ptr);
   }
}










typedef struct {
   
      int Running;
      int AlbumKey;
      char* AlbumName;
      int SourceStoreKey;
      int DestinationStoreKey;
      int Progress;
} type_91;



void type_91_free(type_91* ptr) {
   if (ptr == 0) { return; }
   else {
      
      free(ptr->AlbumName);
      free(ptr);
   }
}






#endif
