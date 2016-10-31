#include "entry.h"
#include <stdio.h>
#include <windows.h>
#pragma comment(lib, "User32.lib")
#pragma warning(disable:4996)

int64_t readDirEntryClass(const char * path, const char * className, char ** classContent)
{
	HANDLE hFile;
	HANDLE hSearch;
	WIN32_FIND_DATA FileData;
	LARGE_INTEGER filesize;
	char fullClassName[128] = { 0 };
	strcat(fullClassName, path);
	strcat(fullClassName, "/");
	strcat(fullClassName, className);

	hSearch = FindFirstFile(fullClassName, &FileData);
	if (hSearch == INVALID_HANDLE_VALUE)
	{
		printf("No file found.\n");
		return -1;
	}
	filesize.HighPart = FileData.nFileSizeHigh;
	filesize.LowPart = FileData.nFileSizeLow;
	printf("File size:%d\n", filesize.QuadPart);
	hFile = CreateFile(fullClassName,               // file to open
		GENERIC_READ,          // open for reading
		FILE_SHARE_READ,       // share for reading
		NULL,                  // default security
		OPEN_EXISTING,         // existing file only
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, // normal file
		NULL);                 // no attr. template

	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("Directly open class file failed\n");
		return -1;
	}
	return 0;
}