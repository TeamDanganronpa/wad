#ifndef WAD_READ_READ__WADSUBFILE_H
#define WAD_READ_READ__WADSUBFILE_H

#include "wad/read/read_/read_struct_name.h"
#include "wad/wad_struct.h"

inline WADSubfile ReadWADSubfile(void* PositionalFileReader) {
	WADSubfile Subfile;
	Subfile.Name = ReadName(PositionalFileReader);

	PositionalFileReader_Read(PositionalFileReader, &Subfile.IsFile, 1);
	return Subfile;
}

#endif // WAD_READ_READ__WADSUBFILE_H