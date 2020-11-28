#ifndef WIN32_FILEAPI_H
#define WIN32_FILEAPI_H

#include <Windows.h>

struct win32_file{
	char* Data;
	char* FileEndPointer;
	HANDLE FileHandle;
	DWORD FileSize;
};
bool read_entire_file(const char* FileName, win32_file * File);
bool close_file(win32_file * File);
#endif