#ifndef WAD_WAD_STRUCT_H
#define WAD_WAD_STRUCT_H

#include <stdint.h>

typedef struct WADSubfile {
	char* Name;

	uint8_t IsFile; // 0 - true, 1 - false
} WADSubfile;

typedef struct WADDirectory {
	char* Name;

	uint32_t NumberOfSubfiles;
	WADSubfile* Subfiles;
} WADDirectory;

typedef struct WADFile {
	char* Name;

	uint64_t Size, Offset;
} WADFile;

typedef struct WAD {
	char Magic[4];

	uint32_t MajorVersion, MinorVersion;

	// This should be header size and header

	uint32_t NumberOfFiles;
	WADFile* Files;

	uint32_t NumberOfDirectories;
	WADDirectory* Directories;
} WAD;

#endif // WAD_WAD_STRUCT_H