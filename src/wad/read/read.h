#ifndef WAD_READ_READ_H
#define WAD_READ_READ_H

struct WADSubfile;
struct WADDirectory;
struct WADFile;
struct WAD;

void* OpenWAD(const char* FilePath, const char* ErrorBuffer);
void DestroyWAD(void* WadHandle);

struct WAD* GetWAD(const void* WadHandle);

#endif // WAD_READ_READ_H