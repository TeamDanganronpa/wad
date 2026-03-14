#ifndef WAD_ERROR_H
#define WAD_ERROR_H

#include <bytepicker/error.h>

#define WAD_ERROR_EOF BYTEPICKER_ERROR_EOF
#define WAD_ERROR_UNEXPECTED_HEADER_SIZE "Unexpected Header Size"
#define WAD_ERROR_ALLOCATE_WADHANDLE "Failed to allocate memory for WADHandle"
#define WAD_ERROR_ALLOCATE_WAD "Failed to allocate memory for WAD"
#define WAD_ERROR_CREATE_PFR "Failed to create PositionalFileReader"
#define WAD_ERROR_PARSE_WAD "Failed to parse WAD"

#endif // WAD_ERROR_H