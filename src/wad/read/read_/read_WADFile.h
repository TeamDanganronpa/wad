#ifndef WAD_READ_READ__WADFILE_H
#define WAD_READ_READ__WADFILE_H

#include "wad/read/read_/read_struct_name.h"
#include "wad/wad_struct.h"

inline WADFile ReadWADFile(void* PositionalFileReader) {
	WADFile WadFile;
	WadFile.Name = ReadName(PositionalFileReader);

	PositionalFileReader_Read(PositionalFileReader, &WadFile.Size, 8);
	PositionalFileReader_Read(PositionalFileReader, &WadFile.Offset, 8);
	return WadFile;
}

#endif // WAD_READ_READ__WADFILE_H