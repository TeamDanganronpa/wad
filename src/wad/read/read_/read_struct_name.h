#ifndef WAD_READ_READ__STRUCT_NAME_H
#define WAD_READ_READ__STRUCT_NAME_H

#include <bytepicker/bytepicker.h>
#include <stdint.h>
#include <stdlib.h>

inline char* ReadName(void* PositionalFileReader) {
	uint32_t NameSize;
	PositionalFileReader_Read(PositionalFileReader, &NameSize, 4);
	char* Name;
	if (NameSize == 0) /* For example: root directory */ {
		Name = malloc(1);
		Name[0] = '\0';
	} else {
		Name = malloc(NameSize + 1);
		PositionalFileReader_ReadString(PositionalFileReader, Name, NameSize);
	}
	return Name;
}

#endif // WAD_READ_READ__STRUCT_NAME_H