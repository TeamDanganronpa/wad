#include "read.h"

#include <bytepicker/bytepicker.h>
#include <stdlib.h>
#include <string.h>

#include "wad/error.h"
#include "wad/read/read_/read_WADDirectory.h"
#include "wad/read/read_/read_WADFile.h"
#include "wad/wad_struct.h"

typedef struct {
	void* PositionalFileReader;
	size_t RawDataStartOffset;
	WAD* Wad;
} WADHandle;

void WriteError(const char* ErrorBuffer, const char* Error) {
	if (ErrorBuffer) ErrorBuffer = Error;
}

void* OpenWAD(const char* FilePath, const char* ErrorBuffer) {
	WADHandle* WadHandle = malloc(sizeof(WADHandle));
	if (!WadHandle) {
		WriteError(ErrorBuffer, WAD_ERROR_ALLOCATE_WADHANDLE);
		return NULL;
	}

	WadHandle->Wad = malloc(sizeof(WAD));
	if (!WadHandle->Wad) {
		WriteError(ErrorBuffer, WAD_ERROR_ALLOCATE_WAD);
		return NULL;
	}

	WadHandle->PositionalFileReader = CreatePositionalFileReader(FilePath);
	if (!WadHandle->PositionalFileReader) {
		WriteError(ErrorBuffer, WAD_ERROR_CREATE_PFR);
		return NULL;
	}

	const char* Result = NULL;
	Result = PositionalFileReader_Read(WadHandle->PositionalFileReader, WadHandle->Wad->Magic, 4);
	if (Result) {
		WriteError(ErrorBuffer, Result);
		return NULL;
	}

	Result = PositionalFileReader_Read(WadHandle->PositionalFileReader, &WadHandle->Wad->MajorVersion, 4);
	if (Result) {
		WriteError(ErrorBuffer, Result);
		return NULL;
	}

	Result = PositionalFileReader_Read(WadHandle->PositionalFileReader, &WadHandle->Wad->MinorVersion, 4);
	if (Result) {
		WriteError(ErrorBuffer, Result);
		return NULL;
	}

	uint32_t __HeaderSize;
	PositionalFileReader_Read(WadHandle->PositionalFileReader, &__HeaderSize, 4);
	if (__HeaderSize > 0) {
		WriteError(ErrorBuffer, WAD_ERROR_UNEXPECTED_HEADER_SIZE);
		return NULL;
	}

	PositionalFileReader_Read(WadHandle->PositionalFileReader, &WadHandle->Wad->NumberOfFiles, 4);
	WadHandle->Wad->Files = malloc(sizeof(WADFile) * WadHandle->Wad->NumberOfFiles);
	for (size_t i = 0; i < WadHandle->Wad->NumberOfFiles; ++i) {
		WADFile WadFile = ReadWADFile(WadHandle->PositionalFileReader);
		memmove(&WadHandle->Wad->Files[i], &WadFile, sizeof(WADFile));
	}

	PositionalFileReader_Read(WadHandle->PositionalFileReader, &WadHandle->Wad->NumberOfDirectories, 4);
	WadHandle->Wad->Directories = malloc(sizeof(WADDirectory) * WadHandle->Wad->NumberOfDirectories);
	for (size_t i = 0; i < WadHandle->Wad->NumberOfDirectories; ++i) {
		WADDirectory WadDir = ReadWADDirectory(WadHandle->PositionalFileReader);
		memmove(&WadHandle->Wad->Directories[i], &WadDir, sizeof(WADDirectory));
	}

	WadHandle->RawDataStartOffset = PositionalFileWriter_GetPosition(WadHandle->PositionalFileReader);
	return WadHandle;
}

void DestroyWAD(void* WadHandle) {
	// TODO: Free all fields in WAD
	if (WadHandle) {
		WADHandle* WH = WadHandle;
		if (WH->PositionalFileReader) DestroyPositionalFileReader(WH->PositionalFileReader);

		for (size_t i = 0; i < WH->Wad->NumberOfFiles; ++i) free(WH->Wad->Files[i].Name);
		for (size_t i = 0; i < WH->Wad->NumberOfDirectories; ++i) free(WH->Wad->Directories[i].Name);
		free(WH);
	}
}

WAD* GetWAD(const void* WadHandle) {
	if (!WadHandle) return NULL;
	return ((WADHandle*)WadHandle)->Wad;
}

#include <stdio.h>

uint8_t* GetWADFileData(const void* WadHandle, const char* FilePath, uint32_t* SizeBuffer) {
	if (!WadHandle || !FilePath) return NULL;

	WADHandle* WH = WadHandle;

	size_t OffsetStart = 0, Size = 0;

	for (size_t i = 0; i < WH->Wad->NumberOfFiles; ++i)
		if (strcmp(WH->Wad->Files[i].Name,  FilePath) == 0) {
			OffsetStart = WH->Wad->Files[i].Offset;
			Size = WH->Wad->Files[i].Size;
			break;
		}
	if (OffsetStart == 0 || Size == 0) return NULL;
	uint8_t* FileData = malloc(Size);
	if (!FileData) return NULL;

	PositionalFileReader_SetPosition(WH->PositionalFileReader, WH->RawDataStartOffset + OffsetStart);
	PositionalFileReader_Read(WH->PositionalFileReader, FileData, Size);
	*SizeBuffer = Size;
	return FileData;
}

void DestroyWADFileData(void* WadFileData) {
	if (WadFileData) free(WadFileData);
}