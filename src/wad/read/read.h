#ifndef WAD_READ_READ_H
#define WAD_READ_READ_H

#include <stdint.h>

#include "wad/dll_api.h"

struct WADSubfile;
struct WADDirectory;
struct WADFile;
struct WAD;

void* WAD_API OpenWAD(const char* FilePath, const char* ErrorBuffer);
void WAD_API DestroyWAD(void* WadHandle);

struct WAD* WAD_API GetWAD(const void* WadHandle);

uint8_t* WAD_API GetWADFileData(const void* WadHandle, const char* FilePath, uint32_t* SizeBuffer);
void WAD_API DestroyWADFileData(void* WadFileData);

#endif // WAD_READ_READ_H