#ifndef WAD_READ_READ__WADDIRECTORY_H
#define WAD_READ_READ__WADDIRECTORY_H

#include <string.h>

#include "wad/read/read_/read_struct_name.h"
#include "wad/read/read_/read_WADSubfile.h"
#include "wad/wad_struct.h"

inline WADDirectory ReadWADDirectory(void* PositionalFileReader) {
	WADDirectory WadDir;
	WadDir.Name = ReadName(PositionalFileReader);

	PositionalFileReader_Read(PositionalFileReader, &WadDir.NumberOfSubfiles, 4);
	WadDir.Subfiles = malloc(sizeof(WADSubfile) * WadDir.NumberOfSubfiles);
	for (size_t i = 0; i < WadDir.NumberOfSubfiles; i++) {
		WADSubfile Subfile = ReadWADSubfile(PositionalFileReader);
		memmove(&WadDir.Subfiles[i], &Subfile, sizeof(WADSubfile));
	}
	return WadDir;
}

#endif // WAD_READ_READ__WADDIRECTORY_H