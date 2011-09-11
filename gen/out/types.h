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
   
   String StatusSettingName
   
   String StatusSettingValue
   
} type_1;

void type_1_free(type_1* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->StatusSettingName);
      
      free(ptr->StatusSettingValue);
      
      free(ptr);
   }
}

typedef struct {
   
   Number FilterSearch_Return
   
} type_2;

void type_2_free(type_2* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->FilterSearch_Return);
      
      free(ptr);
   }
}

typedef struct {
   
   Number RoomKey
   
   String IPAddress
   
   Number Channel
   
   String Name
   
   String ShortName
   
   Boolean IsMultiRoom
   
   Boolean PlaybackCapability
   
   Boolean RippingCapability
   
   Boolean MusicManagementCapability
   
   Number RoomID
   
   String HostName
   
} type_3;

void type_3_free(type_3* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->RoomKey);
      
      free(ptr->IPAddress);
      
      free(ptr->Channel);
      
      free(ptr->Name);
      
      free(ptr->ShortName);
      
      free(ptr->IsMultiRoom);
      
      free(ptr->PlaybackCapability);
      
      free(ptr->RippingCapability);
      
      free(ptr->MusicManagementCapability);
      
      free(ptr->RoomID);
      
      free(ptr->HostName);
      
      free(ptr);
   }
}

typedef struct {
   
   Number MessageAddress
   
   String Severity
   
   String Category
   
   Date DateCreated
   
   Time TimeCreated
   
   Number Tag
   
} type_4;

void type_4_free(type_4* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->MessageAddress);
      
      free(ptr->Severity);
      
      free(ptr->Category);
      
      free(ptr->DateCreated);
      
      free(ptr->TimeCreated);
      
      free(ptr->Tag);
      
      free(ptr);
   }
}

typedef struct {
   
   Number TrackKey
   
   String Name
   
   String SortName
   
   String Type
   
   Time Length
   
   Date Created
   
   Date LastModified
   
   Number Ordinal
   
   Boolean ExtendedInfoAvail
   
   Number Storage
   
   Number SampleRate
   
   Number BitsPerSample
   
   Number ChannelCount
   
   Number Source
   
} type_5;

void type_5_free(type_5* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->TrackKey);
      
      free(ptr->Name);
      
      free(ptr->SortName);
      
      free(ptr->Type);
      
      free(ptr->Length);
      
      free(ptr->Created);
      
      free(ptr->LastModified);
      
      free(ptr->Ordinal);
      
      free(ptr->ExtendedInfoAvail);
      
      free(ptr->Storage);
      
      free(ptr->SampleRate);
      
      free(ptr->BitsPerSample);
      
      free(ptr->ChannelCount);
      
      free(ptr->Source);
      
      free(ptr);
   }
}

typedef struct {
   
   Number TrackKey
   
   String Name
   
   String SortName
   
   String Type
   
   Time Length
   
   Date Created
   
   Date LastModified
   
   Number Ordinal
   
   Boolean ExtendedInfoAvail
   
   Number Storage
   
   Number SampleRate
   
   Number BitsPerSample
   
   Number ChannelCount
   
   Number AlbumKey
   
   String AlbumName
   
   Number ArtistKey
   
   String ArtistName
   
   String SubGenre
   
   String CoverURL
   
   Number BitRate
   
   Number Source
   
   Boolean CoverAvailable
   
   Boolean Hidden
   
} type_6;

void type_6_free(type_6* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->TrackKey);
      
      free(ptr->Name);
      
      free(ptr->SortName);
      
      free(ptr->Type);
      
      free(ptr->Length);
      
      free(ptr->Created);
      
      free(ptr->LastModified);
      
      free(ptr->Ordinal);
      
      free(ptr->ExtendedInfoAvail);
      
      free(ptr->Storage);
      
      free(ptr->SampleRate);
      
      free(ptr->BitsPerSample);
      
      free(ptr->ChannelCount);
      
      free(ptr->AlbumKey);
      
      free(ptr->AlbumName);
      
      free(ptr->ArtistKey);
      
      free(ptr->ArtistName);
      
      free(ptr->SubGenre);
      
      free(ptr->CoverURL);
      
      free(ptr->BitRate);
      
      free(ptr->Source);
      
      free(ptr->CoverAvailable);
      
      free(ptr->Hidden);
      
      free(ptr);
   }
}

typedef struct {
   
   Number AlertKey
   
   String Severity
   
   String Category
   
   Date Created
   
   Time Time
   
} type_7;

void type_7_free(type_7* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->AlertKey);
      
      free(ptr->Severity);
      
      free(ptr->Category);
      
      free(ptr->Created);
      
      free(ptr->Time);
      
      free(ptr);
   }
}

typedef struct {
   
   Number AlertKey
   
   String Severity
   
   String Category
   
   String Module
   
   String Message
   
   Date Created
   
   Date Modified
   
   Date Sent
   
   String UserMessage
   
} type_8;

void type_8_free(type_8* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->AlertKey);
      
      free(ptr->Severity);
      
      free(ptr->Category);
      
      free(ptr->Module);
      
      free(ptr->Message);
      
      free(ptr->Created);
      
      free(ptr->Modified);
      
      free(ptr->Sent);
      
      free(ptr->UserMessage);
      
      free(ptr);
   }
}

typedef struct {
   
   String Artist
   
   String Album
   
   Number Tracks
   
   Number TracksRipped
   
   Number Errors
   
   Time TimeTaken
   
   Time TimeLeft
   
   String Track
   
   Number TrackPercent
   
   String UserMessage
   
   String LookupProviderUsed
   
   String Destination
   
} type_9;

void type_9_free(type_9* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->Artist);
      
      free(ptr->Album);
      
      free(ptr->Tracks);
      
      free(ptr->TracksRipped);
      
      free(ptr->Errors);
      
      free(ptr->TimeTaken);
      
      free(ptr->TimeLeft);
      
      free(ptr->Track);
      
      free(ptr->TrackPercent);
      
      free(ptr->UserMessage);
      
      free(ptr->LookupProviderUsed);
      
      free(ptr->Destination);
      
      free(ptr);
   }
}

typedef struct {
   
   String RegistryKey
   
   String Value
   
   Boolean ReadOnly
   
   String Default
   
   Number MaxLength
   
} type_10;

void type_10_free(type_10* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->RegistryKey);
      
      free(ptr->Value);
      
      free(ptr->ReadOnly);
      
      free(ptr->Default);
      
      free(ptr->MaxLength);
      
      free(ptr);
   }
}

typedef struct {
   
   String RegistryKey
   
   String Value
   
   Boolean ReadOnly
   
   String Default
   
   Number MaxLength
   
   Number ValueType
   
   String TabCaption
   
   String Category
   
   String Caption
   
   String ShortTabCaption
   
   String ShortCategory
   
   String ShortCaption
   
   String Description
   
} type_11;

void type_11_free(type_11* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->RegistryKey);
      
      free(ptr->Value);
      
      free(ptr->ReadOnly);
      
      free(ptr->Default);
      
      free(ptr->MaxLength);
      
      free(ptr->ValueType);
      
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

typedef struct {
   
   Number GetAvailableValues_Return
   
   Number ValueType_Return
   
} type_12;

void type_12_free(type_12* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->GetAvailableValues_Return);
      
      free(ptr->ValueType_Return);
      
      free(ptr);
   }
}

typedef struct {
   
   Number DriveKey
   
   String DriveLetter
   
   Boolean IsPrimary
   
   String RootPath
   
   String SharePath
   
   Number Usage
   
   Date LastBackup
   
} type_13;

void type_13_free(type_13* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->DriveKey);
      
      free(ptr->DriveLetter);
      
      free(ptr->IsPrimary);
      
      free(ptr->RootPath);
      
      free(ptr->SharePath);
      
      free(ptr->Usage);
      
      free(ptr->LastBackup);
      
      free(ptr);
   }
}

typedef struct {
   
   String Value
   
} type_14;

void type_14_free(type_14* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->Value);
      
      free(ptr);
   }
}

typedef struct {
   
   String Artist
   
   String Album
   
   String Track
   
   String Activity
   
   Number Max
   
   Number Progress
   
} type_15;

void type_15_free(type_15* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->Artist);
      
      free(ptr->Album);
      
      free(ptr->Track);
      
      free(ptr->Activity);
      
      free(ptr->Max);
      
      free(ptr->Progress);
      
      free(ptr);
   }
}

typedef struct {
   
   Number Key
   
   String Name
   
   Number OutputDeviceID
   
   Number SourceLineID
   
} type_16;

void type_16_free(type_16* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->Key);
      
      free(ptr->Name);
      
      free(ptr->OutputDeviceID);
      
      free(ptr->SourceLineID);
      
      free(ptr);
   }
}

typedef struct {
   
   String Name
   
   Number OutputDeviceID
   
} type_17;

void type_17_free(type_17* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->Name);
      
      free(ptr->OutputDeviceID);
      
      free(ptr);
   }
}

typedef struct {
   
   String FriendlyName
   
   String UDN
   
   String Manufacturer
   
   String ModelNumber
   
   String SupportedExtensions
   
} type_18;

void type_18_free(type_18* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->FriendlyName);
      
      free(ptr->UDN);
      
      free(ptr->Manufacturer);
      
      free(ptr->ModelNumber);
      
      free(ptr->SupportedExtensions);
      
      free(ptr);
   }
}

typedef struct {
   
   Number ChannelNumber
   
   String ChannelDescription
   
} type_19;

void type_19_free(type_19* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->ChannelNumber);
      
      free(ptr->ChannelDescription);
      
      free(ptr);
   }
}

typedef struct {
   
   Number DeviceKey
   
   String Name
   
   String SerialNumber
   
   String Type
   
   String State
   
   String LastState
   
   Date LastConnected
   
   Number Connections
   
   Boolean Sync
   
} type_20;

void type_20_free(type_20* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->DeviceKey);
      
      free(ptr->Name);
      
      free(ptr->SerialNumber);
      
      free(ptr->Type);
      
      free(ptr->State);
      
      free(ptr->LastState);
      
      free(ptr->LastConnected);
      
      free(ptr->Connections);
      
      free(ptr->Sync);
      
      free(ptr);
   }
}

typedef struct {
   
   Number StorageKey
   
   String IPAddress
   
   String HostName
   
   String ShareName
   
   String FullSharePath
   
   String State
   
   String LastState
   
   Boolean Active
   
   Date Created
   
   Date Modified
   
   Date LastScanDate
   
   Time LastScanTime
   
   String UserName
   
   String Password
   
   String ScanIgnore
   
} type_21;

void type_21_free(type_21* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->StorageKey);
      
      free(ptr->IPAddress);
      
      free(ptr->HostName);
      
      free(ptr->ShareName);
      
      free(ptr->FullSharePath);
      
      free(ptr->State);
      
      free(ptr->LastState);
      
      free(ptr->Active);
      
      free(ptr->Created);
      
      free(ptr->Modified);
      
      free(ptr->LastScanDate);
      
      free(ptr->LastScanTime);
      
      free(ptr->UserName);
      
      free(ptr->Password);
      
      free(ptr->ScanIgnore);
      
      free(ptr);
   }
}

typedef struct {
   
   Number RoomKey
   
   String IPAddress
   
   Number Channel
   
   String RoomName
   
   String ShortName
   
   Boolean IsMultiRoom
   
   Boolean PlaybackCapability
   
   Boolean RippingCapability
   
   Boolean MusicManagementCapability
   
   Number RoomID
   
   String HostName
   
   Date Created
   
   Date Modified
   
   Number ChildRoomCount
   
} type_22;

void type_22_free(type_22* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->RoomKey);
      
      free(ptr->IPAddress);
      
      free(ptr->Channel);
      
      free(ptr->RoomName);
      
      free(ptr->ShortName);
      
      free(ptr->IsMultiRoom);
      
      free(ptr->PlaybackCapability);
      
      free(ptr->RippingCapability);
      
      free(ptr->MusicManagementCapability);
      
      free(ptr->RoomID);
      
      free(ptr->HostName);
      
      free(ptr->Created);
      
      free(ptr->Modified);
      
      free(ptr->ChildRoomCount);
      
      free(ptr);
   }
}

typedef struct {
   
   Number RoomKey
   
   String IPAddress
   
   Number Channel
   
   String RoomName
   
   String ShortName
   
   Boolean IsMultiRoom
   
   Boolean PlaybackCapability
   
   Boolean RippingCapability
   
   Boolean MusicManagementCapability
   
   Number RoomID
   
   String HostName
   
   Date Created
   
   Date Modified
   
} type_23;

void type_23_free(type_23* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->RoomKey);
      
      free(ptr->IPAddress);
      
      free(ptr->Channel);
      
      free(ptr->RoomName);
      
      free(ptr->ShortName);
      
      free(ptr->IsMultiRoom);
      
      free(ptr->PlaybackCapability);
      
      free(ptr->RippingCapability);
      
      free(ptr->MusicManagementCapability);
      
      free(ptr->RoomID);
      
      free(ptr->HostName);
      
      free(ptr->Created);
      
      free(ptr->Modified);
      
      free(ptr);
   }
}

typedef struct {
   
   String Col1
   
   String Col2
   
   String Col3
   
   String Col4
   
   String Col5
   
   String Col6
   
} type_24;

void type_24_free(type_24* ptr) {
   if (ptr == NULL) { return; }
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

typedef struct {
   
   Number BackupJobKey
   
   Number SourceDriveKey
   
   Number DestinationDriveKey
   
   String Name
   
   Number BackupType
   
   Number BackupPeriod
   
   Number PeriodValue
   
   Date RunDate
   
   Time RunTime
   
   Date NextRunDate
   
   Time NextRunTime
   
   Date LastRunDate
   
   Time LastRunTime
   
   Number JobStatus
   
   Number LastResult
   
} type_25;

void type_25_free(type_25* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->BackupJobKey);
      
      free(ptr->SourceDriveKey);
      
      free(ptr->DestinationDriveKey);
      
      free(ptr->Name);
      
      free(ptr->BackupType);
      
      free(ptr->BackupPeriod);
      
      free(ptr->PeriodValue);
      
      free(ptr->RunDate);
      
      free(ptr->RunTime);
      
      free(ptr->NextRunDate);
      
      free(ptr->NextRunTime);
      
      free(ptr->LastRunDate);
      
      free(ptr->LastRunTime);
      
      free(ptr->JobStatus);
      
      free(ptr->LastResult);
      
      free(ptr);
   }
}

typedef struct {
   
   Number BackupLogKey
   
   Number BackupJobKey
   
   Number ExecutionType
   
   String Name
   
   Number BackupType
   
   String SourcePath
   
   String DestinationPath
   
   Date StartDate
   
   Time StartTime
   
   Date FinishDate
   
   Time FinishTime
   
   Number Result
   
   Number TotalFolders
   
   Number TotalFiles
   
   Number TotalKiloBytes
   
   Number TotalErrors
   
} type_26;

void type_26_free(type_26* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->BackupLogKey);
      
      free(ptr->BackupJobKey);
      
      free(ptr->ExecutionType);
      
      free(ptr->Name);
      
      free(ptr->BackupType);
      
      free(ptr->SourcePath);
      
      free(ptr->DestinationPath);
      
      free(ptr->StartDate);
      
      free(ptr->StartTime);
      
      free(ptr->FinishDate);
      
      free(ptr->FinishTime);
      
      free(ptr->Result);
      
      free(ptr->TotalFolders);
      
      free(ptr->TotalFiles);
      
      free(ptr->TotalKiloBytes);
      
      free(ptr->TotalErrors);
      
      free(ptr);
   }
}

typedef struct {
   
   Number BackupLogKey
   
   Number BackupJobKey
   
   Number ExecutionType
   
   String Name
   
   Number BackupType
   
   String SourcePath
   
   String DestinationPath
   
   Date StartDate
   
   Time StartTime
   
   Date FinishDate
   
   Time FinishTime
   
   Number Result
   
   Number TotalFolders
   
   Number TotalFiles
   
   Number TotalKiloBytes
   
   Number TotalErrors
   
   String ErrorDetail
   
} type_27;

void type_27_free(type_27* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->BackupLogKey);
      
      free(ptr->BackupJobKey);
      
      free(ptr->ExecutionType);
      
      free(ptr->Name);
      
      free(ptr->BackupType);
      
      free(ptr->SourcePath);
      
      free(ptr->DestinationPath);
      
      free(ptr->StartDate);
      
      free(ptr->StartTime);
      
      free(ptr->FinishDate);
      
      free(ptr->FinishTime);
      
      free(ptr->Result);
      
      free(ptr->TotalFolders);
      
      free(ptr->TotalFiles);
      
      free(ptr->TotalKiloBytes);
      
      free(ptr->TotalErrors);
      
      free(ptr->ErrorDetail);
      
      free(ptr);
   }
}

typedef struct {
   
   Number DeviceID
   
   String Description
   
   String MacAddress
   
   Boolean DhcpEnabled
   
   String IpAddress
   
   String SubnetMask
   
   String DefaultGateway
   
   String DnsServer
   
} type_28;

void type_28_free(type_28* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->DeviceID);
      
      free(ptr->Description);
      
      free(ptr->MacAddress);
      
      free(ptr->DhcpEnabled);
      
      free(ptr->IpAddress);
      
      free(ptr->SubnetMask);
      
      free(ptr->DefaultGateway);
      
      free(ptr->DnsServer);
      
      free(ptr);
   }
}

typedef struct {
   
   Number PlaylistKey
   
   String Name
   
   Number ArtistKey
   
   String ArtistName
   
   Boolean IsAlbum
   
   Date Created
   
   Date LastModified
   
   Number HitCount
   
   Boolean ExtendedInfoAvail
   
   Number Storage
   
} type_29;

void type_29_free(type_29* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->PlaylistKey);
      
      free(ptr->Name);
      
      free(ptr->ArtistKey);
      
      free(ptr->ArtistName);
      
      free(ptr->IsAlbum);
      
      free(ptr->Created);
      
      free(ptr->LastModified);
      
      free(ptr->HitCount);
      
      free(ptr->ExtendedInfoAvail);
      
      free(ptr->Storage);
      
      free(ptr);
   }
}

typedef struct {
   
   Number TrackKey
   
   String Name
   
   String SortName
   
   String Type
   
   Time Length
   
   Date Created
   
   Date LastModified
   
   Number Ordinal
   
   Boolean ExtendedInfoAvail
   
   Number Storage
   
   Number SampleRate
   
   Number BitsPerSample
   
   Number ChannelCount
   
} type_30;

void type_30_free(type_30* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->TrackKey);
      
      free(ptr->Name);
      
      free(ptr->SortName);
      
      free(ptr->Type);
      
      free(ptr->Length);
      
      free(ptr->Created);
      
      free(ptr->LastModified);
      
      free(ptr->Ordinal);
      
      free(ptr->ExtendedInfoAvail);
      
      free(ptr->Storage);
      
      free(ptr->SampleRate);
      
      free(ptr->BitsPerSample);
      
      free(ptr->ChannelCount);
      
      free(ptr);
   }
}

typedef struct {
   
   Number ContributorKey
   
   String Name
   
   Number ContributorType
   
} type_31;

void type_31_free(type_31* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->ContributorKey);
      
      free(ptr->Name);
      
      free(ptr->ContributorType);
      
      free(ptr);
   }
}

typedef struct {
   
   Number PlaylistKey
   
   String Name
   
   Number ArtistKey
   
   String ArtistName
   
   Boolean IsAlbum
   
   Date Created
   
   Date LastModified
   
   Number HitCount
   
   Boolean ExtendedInfoAvail
   
   Number Storage
   
   Number GenreKey
   
   String Genre
   
   Number SubGenreKey
   
   String SubGenre
   
   Number TrackCount
   
   Boolean LowQuality
   
   Number StorageKey
   
   String StorageName
   
   Number ProviderUsed
   
   String CoverURL
   
   Boolean CoverAvailable
   
} type_32;

void type_32_free(type_32* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->PlaylistKey);
      
      free(ptr->Name);
      
      free(ptr->ArtistKey);
      
      free(ptr->ArtistName);
      
      free(ptr->IsAlbum);
      
      free(ptr->Created);
      
      free(ptr->LastModified);
      
      free(ptr->HitCount);
      
      free(ptr->ExtendedInfoAvail);
      
      free(ptr->Storage);
      
      free(ptr->GenreKey);
      
      free(ptr->Genre);
      
      free(ptr->SubGenreKey);
      
      free(ptr->SubGenre);
      
      free(ptr->TrackCount);
      
      free(ptr->LowQuality);
      
      free(ptr->StorageKey);
      
      free(ptr->StorageName);
      
      free(ptr->ProviderUsed);
      
      free(ptr->CoverURL);
      
      free(ptr->CoverAvailable);
      
      free(ptr);
   }
}

typedef struct {
   
   Number PlaylistKey
   
   String Name
   
   Number ArtistKey
   
   String ArtistName
   
   Boolean IsAlbum
   
   Date Created
   
   Date LastModified
   
   Number HitCount
   
   Boolean ExtendedInfoAvail
   
   Number Storage
   
   String Genre
   
   Number TrackCount
   
   String CoverImage
   
} type_33;

void type_33_free(type_33* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->PlaylistKey);
      
      free(ptr->Name);
      
      free(ptr->ArtistKey);
      
      free(ptr->ArtistName);
      
      free(ptr->IsAlbum);
      
      free(ptr->Created);
      
      free(ptr->LastModified);
      
      free(ptr->HitCount);
      
      free(ptr->ExtendedInfoAvail);
      
      free(ptr->Storage);
      
      free(ptr->Genre);
      
      free(ptr->TrackCount);
      
      free(ptr->CoverImage);
      
      free(ptr);
   }
}

typedef struct {
   
   Number TrackKey
   
   String Name
   
   String SortName
   
   String Type
   
   Time Length
   
   Date Created
   
   Date LastModified
   
   Number Ordinal
   
   Boolean ExtendedInfoAvail
   
   Number Storage
   
   Number SampleRate
   
   Number BitsPerSample
   
   Number ChannelCount
   
   Boolean Hidden
   
} type_34;

void type_34_free(type_34* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->TrackKey);
      
      free(ptr->Name);
      
      free(ptr->SortName);
      
      free(ptr->Type);
      
      free(ptr->Length);
      
      free(ptr->Created);
      
      free(ptr->LastModified);
      
      free(ptr->Ordinal);
      
      free(ptr->ExtendedInfoAvail);
      
      free(ptr->Storage);
      
      free(ptr->SampleRate);
      
      free(ptr->BitsPerSample);
      
      free(ptr->ChannelCount);
      
      free(ptr->Hidden);
      
      free(ptr);
   }
}

typedef struct {
   
   Number TrackKey
   
   String Name
   
   String SortName
   
   String Type
   
   Time Length
   
   Date Created
   
   Date LastModified
   
   Number Ordinal
   
   Boolean ExtendedInfoAvail
   
   Number Storage
   
   Number SampleRate
   
   Number BitsPerSample
   
   Number ChannelCount
   
   Number AlbumKey
   
   String AlbumName
   
   Number ArtistKey
   
   String ArtistName
   
   String SubGenre
   
   String CoverURL
   
   Number BitRate
   
   Boolean CoverAvailable
   
} type_35;

void type_35_free(type_35* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->TrackKey);
      
      free(ptr->Name);
      
      free(ptr->SortName);
      
      free(ptr->Type);
      
      free(ptr->Length);
      
      free(ptr->Created);
      
      free(ptr->LastModified);
      
      free(ptr->Ordinal);
      
      free(ptr->ExtendedInfoAvail);
      
      free(ptr->Storage);
      
      free(ptr->SampleRate);
      
      free(ptr->BitsPerSample);
      
      free(ptr->ChannelCount);
      
      free(ptr->AlbumKey);
      
      free(ptr->AlbumName);
      
      free(ptr->ArtistKey);
      
      free(ptr->ArtistName);
      
      free(ptr->SubGenre);
      
      free(ptr->CoverURL);
      
      free(ptr->BitRate);
      
      free(ptr->CoverAvailable);
      
      free(ptr);
   }
}

typedef struct {
   
   Number GenreKey
   
   String Genre
   
   Date Created
   
   Date LastModified
   
   Number GenreOrdinal
   
   Number Storage
   
} type_36;

void type_36_free(type_36* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->GenreKey);
      
      free(ptr->Genre);
      
      free(ptr->Created);
      
      free(ptr->LastModified);
      
      free(ptr->GenreOrdinal);
      
      free(ptr->Storage);
      
      free(ptr);
   }
}

typedef struct {
   
   Number SubGenreKey
   
   String SubGenre
   
   Date Created
   
   Date LastModified
   
   Number SubGenreOrdinal
   
} type_37;

void type_37_free(type_37* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->SubGenreKey);
      
      free(ptr->SubGenre);
      
      free(ptr->Created);
      
      free(ptr->LastModified);
      
      free(ptr->SubGenreOrdinal);
      
      free(ptr);
   }
}

typedef struct {
   
   Number SubGenreKey
   
   String SubGenre
   
   Number GenreKey
   
   String Genre
   
   Number GenreOrdinal
   
   Number SubGenreOrdinal
   
   Number Storage
   
} type_38;

void type_38_free(type_38* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->SubGenreKey);
      
      free(ptr->SubGenre);
      
      free(ptr->GenreKey);
      
      free(ptr->Genre);
      
      free(ptr->GenreOrdinal);
      
      free(ptr->SubGenreOrdinal);
      
      free(ptr->Storage);
      
      free(ptr);
   }
}

typedef struct {
   
   Number CDDBGenreKey
   
   String Name
   
   Number SubGenreKey
   
   String SubGenreName
   
} type_39;

void type_39_free(type_39* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->CDDBGenreKey);
      
      free(ptr->Name);
      
      free(ptr->SubGenreKey);
      
      free(ptr->SubGenreName);
      
      free(ptr);
   }
}

typedef struct {
   
   Number PlaylistKey
   
   Boolean Success
   
   String Message
   
} type_40;

void type_40_free(type_40* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->PlaylistKey);
      
      free(ptr->Success);
      
      free(ptr->Message);
      
      free(ptr);
   }
}

typedef struct {
   
   Number QueueKey
   
   String Status
   
   Number Retries
   
   String LastError
   
   Date CreatedDate
   
   Time CreatedTime
   
   Date ModifiedDate
   
   Time ModifiedTime
   
   Date LastRetryDate
   
   Time LastRetryTime
   
   Number AlbumKey
   
   String AlbumName
   
} type_41;

void type_41_free(type_41* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->QueueKey);
      
      free(ptr->Status);
      
      free(ptr->Retries);
      
      free(ptr->LastError);
      
      free(ptr->CreatedDate);
      
      free(ptr->CreatedTime);
      
      free(ptr->ModifiedDate);
      
      free(ptr->ModifiedTime);
      
      free(ptr->LastRetryDate);
      
      free(ptr->LastRetryTime);
      
      free(ptr->AlbumKey);
      
      free(ptr->AlbumName);
      
      free(ptr);
   }
}

typedef struct {
   
   Number CreditKey
   
   Number PlaylistKey
   
   String Description
   
   Number ContributorKey
   
   String ContributorName
   
} type_42;

void type_42_free(type_42* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->CreditKey);
      
      free(ptr->PlaylistKey);
      
      free(ptr->Description);
      
      free(ptr->ContributorKey);
      
      free(ptr->ContributorName);
      
      free(ptr);
   }
}

typedef struct {
   
   Number PlaylistKey
   
   Number Discs
   
   Number DiscNumber
   
   String CatalogID
   
   String ImageURL
   
} type_43;

void type_43_free(type_43* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->PlaylistKey);
      
      free(ptr->Discs);
      
      free(ptr->DiscNumber);
      
      free(ptr->CatalogID);
      
      free(ptr->ImageURL);
      
      free(ptr);
   }
}

typedef struct {
   
   Number TrackKey
   
   Number ContributorKey
   
   String Name
   
   Number ContributorType
   
} type_44;

void type_44_free(type_44* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->TrackKey);
      
      free(ptr->ContributorKey);
      
      free(ptr->Name);
      
      free(ptr->ContributorType);
      
      free(ptr);
   }
}

typedef struct {
   
   Number TrackKey
   
   String CompositionDate
   
   String Part
   
   String PerformanceDate
   
   String Work
   
} type_45;

void type_45_free(type_45* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->TrackKey);
      
      free(ptr->CompositionDate);
      
      free(ptr->Part);
      
      free(ptr->PerformanceDate);
      
      free(ptr->Work);
      
      free(ptr);
   }
}

typedef struct {
   
   String Name
   
   Number NodeType
   
   String UrlBookmark
   
   String UrlPlay
   
   String UrlChildren
   
   String UrlChildrenBackup
   
   String ID
   
   String Description
   
   String ParentDescription
   
   String Format
   
   String Language
   
   String City
   
   String State
   
   String Country
   
   String Location
   
   Number Bandwidth
   
   String MimeType
   
   Number ReliabilityRating
   
} type_46;

void type_46_free(type_46* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->Name);
      
      free(ptr->NodeType);
      
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
      
      free(ptr->Bandwidth);
      
      free(ptr->MimeType);
      
      free(ptr->ReliabilityRating);
      
      free(ptr);
   }
}

typedef struct {
   
   Number Key
   
   Number HitCount
   
   Date LastPlayed
   
   Time LastPlayedTime
   
   Date Created
   
   Time CreatedTime
   
   String Name
   
   Number NodeType
   
   String UrlBookmark
   
   String UrlPlay
   
   String UrlChildren
   
   String UrlChildrenBackup
   
   String ID
   
   String Description
   
   String ParentDescription
   
   String Format
   
   String Language
   
   String City
   
   String State
   
   String Country
   
   String Location
   
   Number Bandwidth
   
   String MimeType
   
   Number ReliabilityRating
   
} type_47;

void type_47_free(type_47* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->Key);
      
      free(ptr->HitCount);
      
      free(ptr->LastPlayed);
      
      free(ptr->LastPlayedTime);
      
      free(ptr->Created);
      
      free(ptr->CreatedTime);
      
      free(ptr->Name);
      
      free(ptr->NodeType);
      
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
      
      free(ptr->Bandwidth);
      
      free(ptr->MimeType);
      
      free(ptr->ReliabilityRating);
      
      free(ptr);
   }
}

typedef struct {
   
   Number Key
   
   Number ChannelNumber
   
   String ChannelName
   
   Date Modified
   
   Time ModifiedTime
   
   Date Created
   
   Time CreatedTime
   
   String Name
   
   Number NodeType
   
   String UrlBookmark
   
   String UrlPlay
   
   String UrlChildren
   
   String UrlChildrenBackup
   
   String ID
   
   String Description
   
   String ParentDescription
   
   String Format
   
   String Language
   
   String City
   
   String State
   
   String Country
   
   String Location
   
   Number Bandwidth
   
   String MimeType
   
   Number ReliabilityRating
   
} type_48;

void type_48_free(type_48* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->Key);
      
      free(ptr->ChannelNumber);
      
      free(ptr->ChannelName);
      
      free(ptr->Modified);
      
      free(ptr->ModifiedTime);
      
      free(ptr->Created);
      
      free(ptr->CreatedTime);
      
      free(ptr->Name);
      
      free(ptr->NodeType);
      
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
      
      free(ptr->Bandwidth);
      
      free(ptr->MimeType);
      
      free(ptr->ReliabilityRating);
      
      free(ptr);
   }
}

typedef struct {
   
   Number MusicStoreKey
   
   String Path
   
   Boolean Local
   
   String IPAddress
   
   Boolean Online
   
   Date Created
   
   Date LastModified
   
   String State
   
   Number Priority
   
   Date LastConnected
   
} type_49;

void type_49_free(type_49* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->MusicStoreKey);
      
      free(ptr->Path);
      
      free(ptr->Local);
      
      free(ptr->IPAddress);
      
      free(ptr->Online);
      
      free(ptr->Created);
      
      free(ptr->LastModified);
      
      free(ptr->State);
      
      free(ptr->Priority);
      
      free(ptr->LastConnected);
      
      free(ptr);
   }
}

typedef struct {
   
   Boolean GetStoreDetail_Success
   
} type_50;

void type_50_free(type_50* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->GetStoreDetail_Success);
      
      free(ptr);
   }
}

typedef struct {
   
   Number MusicStoreKey
   
   String Path
   
   Boolean Local
   
   String IPAddress
   
   Boolean Online
   
   Date Created
   
   Date LastModified
   
   String State
   
   Number Priority
   
   Date LastConnected
   
   String Username
   
   String Password
   
   Date LastScanned
   
   String SpaceUsed
   
   String SpaceAvailable
   
   Number NumberOfAlbums
   
} type_51;

void type_51_free(type_51* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->MusicStoreKey);
      
      free(ptr->Path);
      
      free(ptr->Local);
      
      free(ptr->IPAddress);
      
      free(ptr->Online);
      
      free(ptr->Created);
      
      free(ptr->LastModified);
      
      free(ptr->State);
      
      free(ptr->Priority);
      
      free(ptr->LastConnected);
      
      free(ptr->Username);
      
      free(ptr->Password);
      
      free(ptr->LastScanned);
      
      free(ptr->SpaceUsed);
      
      free(ptr->SpaceAvailable);
      
      free(ptr->NumberOfAlbums);
      
      free(ptr);
   }
}

typedef struct {
   
   Number QueueKey
   
   String Status
   
   Number Retries
   
   String LastError
   
   Date CreatedDate
   
   Time CreatedTime
   
   Date ModifiedDate
   
   Time ModifiedTime
   
   Date LastRetryDate
   
   Time LastRetryTime
   
   Number AlbumKey
   
   Number StoreKey
   
   String AlbumName
   
} type_52;

void type_52_free(type_52* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->QueueKey);
      
      free(ptr->Status);
      
      free(ptr->Retries);
      
      free(ptr->LastError);
      
      free(ptr->CreatedDate);
      
      free(ptr->CreatedTime);
      
      free(ptr->ModifiedDate);
      
      free(ptr->ModifiedTime);
      
      free(ptr->LastRetryDate);
      
      free(ptr->LastRetryTime);
      
      free(ptr->AlbumKey);
      
      free(ptr->StoreKey);
      
      free(ptr->AlbumName);
      
      free(ptr);
   }
}

typedef struct {
   
   String Version_Service
   
   String Version_Protocol
   
   String Version_CommandDef
   
   String Version_System
   
} type_53;

void type_53_free(type_53* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->Version_Service);
      
      free(ptr->Version_Protocol);
      
      free(ptr->Version_CommandDef);
      
      free(ptr->Version_System);
      
      free(ptr);
   }
}

typedef struct {
   
   Date GetSystemTime_Date
   
   Time GetSystemTime_Time
   
} type_54;

void type_54_free(type_54* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->GetSystemTime_Date);
      
      free(ptr->GetSystemTime_Time);
      
      free(ptr);
   }
}

typedef struct {
   
   Boolean IsBusy
   
   String Status
   
   Number PercentComplete
   
} type_55;

void type_55_free(type_55* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->IsBusy);
      
      free(ptr->Status);
      
      free(ptr->PercentComplete);
      
      free(ptr);
   }
}

typedef struct {
   
   Number TrackKey
   
   String Name
   
   String Type
   
   Time Length
   
   Number Source
   
} type_56;

void type_56_free(type_56* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->TrackKey);
      
      free(ptr->Name);
      
      free(ptr->Type);
      
      free(ptr->Length);
      
      free(ptr->Source);
      
      free(ptr);
   }
}

typedef struct {
   
   Number Source
   
   String Name
   
   String Album
   
   String Artist
   
   String Genre
   
   String Comment
   
   Time Length
   
} type_57;

void type_57_free(type_57* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->Source);
      
      free(ptr->Name);
      
      free(ptr->Album);
      
      free(ptr->Artist);
      
      free(ptr->Genre);
      
      free(ptr->Comment);
      
      free(ptr->Length);
      
      free(ptr);
   }
}

typedef struct {
   
   Time TrackLength
   
} type_58;

void type_58_free(type_58* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->TrackLength);
      
      free(ptr);
   }
}

typedef struct {
   
   Boolean CDPlaying
   
   String TrackName
   
   String Album
   
   String Artist
   
   Number TrackNumber
   
   Number TrackCount
   
   Boolean Shuffle
   
   Boolean Repeat
   
   String Status
   
   Time TrackLength
   
   Time TrackPosition
   
   String Version
   
   Number Volume
   
} type_59;

void type_59_free(type_59* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->CDPlaying);
      
      free(ptr->TrackName);
      
      free(ptr->Album);
      
      free(ptr->Artist);
      
      free(ptr->TrackNumber);
      
      free(ptr->TrackCount);
      
      free(ptr->Shuffle);
      
      free(ptr->Repeat);
      
      free(ptr->Status);
      
      free(ptr->TrackLength);
      
      free(ptr->TrackPosition);
      
      free(ptr->Version);
      
      free(ptr->Volume);
      
      free(ptr);
   }
}

typedef struct {
   
   String Message
   
   String Category
   
   Date DateCreated
   
} type_60;

void type_60_free(type_60* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->Message);
      
      free(ptr->Category);
      
      free(ptr->DateCreated);
      
      free(ptr);
   }
}

typedef struct {
   
   Number SuccessCount
   
   String SuccessNames
   
   Number PartialCount
   
   String PartialNames
   
   Number FailureCount
   
   String FailureNames
   
} type_61;

void type_61_free(type_61* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->SuccessCount);
      
      free(ptr->SuccessNames);
      
      free(ptr->PartialCount);
      
      free(ptr->PartialNames);
      
      free(ptr->FailureCount);
      
      free(ptr->FailureNames);
      
      free(ptr);
   }
}

typedef struct {
   
   Number DriveKey
   
   String DriveLetter
   
   Boolean Primary
   
   String RootPath
   
   String SharePath
   
   Date Created
   
   Date Modified
   
   Number Usage
   
   Date LastBackup
   
} type_62;

void type_62_free(type_62* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->DriveKey);
      
      free(ptr->DriveLetter);
      
      free(ptr->Primary);
      
      free(ptr->RootPath);
      
      free(ptr->SharePath);
      
      free(ptr->Created);
      
      free(ptr->Modified);
      
      free(ptr->Usage);
      
      free(ptr->LastBackup);
      
      free(ptr);
   }
}

typedef struct {
   
   String DriveLetter
   
   String RootPath
   
   String SharePath
   
   Number Usage
   
} type_63;

void type_63_free(type_63* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->DriveLetter);
      
      free(ptr->RootPath);
      
      free(ptr->SharePath);
      
      free(ptr->Usage);
      
      free(ptr);
   }
}

typedef struct {
   
   Boolean UpdateDrive_Return
   
   String UpdateDrive_ErrorMessage
   
} type_64;

void type_64_free(type_64* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->UpdateDrive_Return);
      
      free(ptr->UpdateDrive_ErrorMessage);
      
      free(ptr);
   }
}

typedef struct {
   
   Number RoomKey
   
   String IPAddress
   
   Number Channel
   
   String RoomName
   
   Number ShortName
   
   Boolean IsMultiRoom
   
   Boolean PlaybackCapability
   
   Boolean RippingCapability
   
   Boolean MusicManagementCapability
   
   Number RoomID
   
   String HostName
   
   Number Created
   
   Number Modified
   
} type_65;

void type_65_free(type_65* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->RoomKey);
      
      free(ptr->IPAddress);
      
      free(ptr->Channel);
      
      free(ptr->RoomName);
      
      free(ptr->ShortName);
      
      free(ptr->IsMultiRoom);
      
      free(ptr->PlaybackCapability);
      
      free(ptr->RippingCapability);
      
      free(ptr->MusicManagementCapability);
      
      free(ptr->RoomID);
      
      free(ptr->HostName);
      
      free(ptr->Created);
      
      free(ptr->Modified);
      
      free(ptr);
   }
}

typedef struct {
   
   Number SubGenreKey
   
   Number GenreKey
   
   String SubGenreName
   
   Date Created
   
   Date Modified
   
   Number Ordinal
   
} type_66;

void type_66_free(type_66* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->SubGenreKey);
      
      free(ptr->GenreKey);
      
      free(ptr->SubGenreName);
      
      free(ptr->Created);
      
      free(ptr->Modified);
      
      free(ptr->Ordinal);
      
      free(ptr);
   }
}

typedef struct {
   
   Boolean AddExternalStorage_Success
   
   String AddExternalStorage_Message
   
   Number AddExternalStorage_Key
   
   String AddExternalStorage_Hostname
   
   String AddExternalStorage_IPAddress
   
   String AddExternalStorage_ShareName
   
   String AddExternalStorage_Username
   
   String AddExternalStorage_Password
   
} type_67;

void type_67_free(type_67* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->AddExternalStorage_Success);
      
      free(ptr->AddExternalStorage_Message);
      
      free(ptr->AddExternalStorage_Key);
      
      free(ptr->AddExternalStorage_Hostname);
      
      free(ptr->AddExternalStorage_IPAddress);
      
      free(ptr->AddExternalStorage_ShareName);
      
      free(ptr->AddExternalStorage_Username);
      
      free(ptr->AddExternalStorage_Password);
      
      free(ptr);
   }
}

typedef struct {
   
   Boolean SetDriveUsage_Success
   
   Boolean SetDriveUsage_DriveInUse
   
   String SetDriveUsage_Message
   
} type_68;

void type_68_free(type_68* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->SetDriveUsage_Success);
      
      free(ptr->SetDriveUsage_DriveInUse);
      
      free(ptr->SetDriveUsage_Message);
      
      free(ptr);
   }
}

typedef struct {
   
   String Backup_SourceDrive
   
   String Backup_DestDrive
   
   String Backup_Type
   
   String Backup_Status
   
   String Backup_CurrentFile
   
   String Backup_LastError
   
   Time Backup_TimeTaken
   
   Time Backup_TimeRemaining
   
   Number Backup_SourceFileCount
   
   Number Backup_SourceFolderCount
   
   Long Backup_SourceByteCount
   
   Number Backup_ProcessedFileCount
   
   Number Backup_ProcessedFolderCount
   
   Long Backup_ProcessedByteCount
   
   Number Backup_ErrorCount
   
   Number Backup_ErrorFileCount
   
   Long Backup_ErrorByteCount
   
} type_69;

void type_69_free(type_69* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->Backup_SourceDrive);
      
      free(ptr->Backup_DestDrive);
      
      free(ptr->Backup_Type);
      
      free(ptr->Backup_Status);
      
      free(ptr->Backup_CurrentFile);
      
      free(ptr->Backup_LastError);
      
      free(ptr->Backup_TimeTaken);
      
      free(ptr->Backup_TimeRemaining);
      
      free(ptr->Backup_SourceFileCount);
      
      free(ptr->Backup_SourceFolderCount);
      
      free(ptr->Backup_SourceByteCount);
      
      free(ptr->Backup_ProcessedFileCount);
      
      free(ptr->Backup_ProcessedFolderCount);
      
      free(ptr->Backup_ProcessedByteCount);
      
      free(ptr->Backup_ErrorCount);
      
      free(ptr->Backup_ErrorFileCount);
      
      free(ptr->Backup_ErrorByteCount);
      
      free(ptr);
   }
}

typedef struct {
   
   Boolean Running
   
   Number AlbumKey
   
   String AlbumName
   
   Number Progress
   
} type_70;

void type_70_free(type_70* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->Running);
      
      free(ptr->AlbumKey);
      
      free(ptr->AlbumName);
      
      free(ptr->Progress);
      
      free(ptr);
   }
}

typedef struct {
   
   String TrackName_Return
   
   Number TrackSource_Return
   
   String TrackPath_Return
   
} type_71;

void type_71_free(type_71* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->TrackName_Return);
      
      free(ptr->TrackSource_Return);
      
      free(ptr->TrackPath_Return);
      
      free(ptr);
   }
}

typedef struct {
   
   Number TrackKey
   
   String TrackName
   
   Number AlbumKey
   
   String Album
   
   Number ArtistKey
   
   String Artist
   
   Number GenreKey
   
   String Genre
   
   Time Length
   
   Number Source
   
   String TrackPath
   
} type_72;

void type_72_free(type_72* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->TrackKey);
      
      free(ptr->TrackName);
      
      free(ptr->AlbumKey);
      
      free(ptr->Album);
      
      free(ptr->ArtistKey);
      
      free(ptr->Artist);
      
      free(ptr->GenreKey);
      
      free(ptr->Genre);
      
      free(ptr->Length);
      
      free(ptr->Source);
      
      free(ptr->TrackPath);
      
      free(ptr);
   }
}

typedef struct {
   
   Boolean Running
   
   Number AlbumKey
   
   String AlbumName
   
   Number SourceStoreKey
   
   Number DestinationStoreKey
   
   Number Progress
   
} type_73;

void type_73_free(type_73* ptr) {
   if (ptr == NULL) { return; }
   else {
      
      free(ptr->Running);
      
      free(ptr->AlbumKey);
      
      free(ptr->AlbumName);
      
      free(ptr->SourceStoreKey);
      
      free(ptr->DestinationStoreKey);
      
      free(ptr->Progress);
      
      free(ptr);
   }
}


#endif
