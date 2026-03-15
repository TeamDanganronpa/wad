#ifndef WAD_READ_READ_H
#define WAD_READ_READ_H

#include <stdint.h>

struct WADSubfile;
struct WADDirectory;
struct WADFile;
struct WAD;

void* OpenWAD(const char* FilePath, const char* ErrorBuffer);
void DestroyWAD(void* WadHandle);

struct WAD* GetWAD(const void* WadHandle);

uint8_t* GetWADFileData(const void* WadHandle, const char* FilePath, uint32_t* SizeBuffer);
void DestroyWADFileData(void* WadFileData);

#endif // WAD_READ_READ_H