#include "win32_fileapi.h"
#include "debug.h"

bool read_entire_file(const char* FileName, win32_file * File){
	File->FileHandle = CreateFileA(
		FileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	if (File->FileHandle == INVALID_HANDLE_VALUE) {
		OutputDebugStringA("Could not open file");
		return false;
	}
	
	File->FileSize = GetFileSize(
		File->FileHandle,
		NULL
		);
	if (File->FileSize == INVALID_FILE_SIZE) {
		CloseHandle(File->FileHandle);
		return false;
	}
	char * Buffer = (char*)VirtualAlloc(NULL,File->FileSize,MEM_COMMIT,PAGE_READWRITE);
	DWORD NumberOfBytesRead = 0;
	DWORD TotalNumberOfBytesRead = 0;
	while(TotalNumberOfBytesRead < File->FileSize){
		BOOL Result = ReadFile(
			File->FileHandle,
			(LPVOID)Buffer,
			File->FileSize,
			&NumberOfBytesRead,
			NULL
			);
		if(Result == FALSE){
			CloseHandle(File->FileHandle);
			VirtualFree(Buffer,File->FileSize,MEM_RELEASE);
			return false;
		}
		
		TotalNumberOfBytesRead += NumberOfBytesRead;
	}
	Assert(TotalNumberOfBytesRead == File->FileSize);
	File->Data = Buffer;
	File->FileEndPointer = File->Data + File->FileSize;
	return true;
}

bool close_file(win32_file * File){
	BOOL Result = CloseHandle(File->FileHandle);
	if(Result == FALSE){
		return false;
	}
	VirtualFree(File->Data,File->FileSize,MEM_RELEASE);
	return true;
}
