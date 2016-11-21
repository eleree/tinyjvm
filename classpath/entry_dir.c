#include "entry.h"
#include "../strings/strings.h"
#include <stdio.h>
#include <windows.h>
#pragma comment(lib, "User32.lib")
#pragma warning(disable:4996)

int32_t readDirEntryClass(const char * path, const char * className, char ** classContent)
{
	HANDLE hFile;
	char fullClassName[128] = { 0 };
	char * classBuffer = NULL;
	DWORD dwActualRead = 0;
	DWORD dwFileSize = 0;

	strcat(fullClassName, path);
	strcat(fullClassName, "/");
	strcat(fullClassName, className);
	if (stringHasSuffix(className,".class") != 0)
		strcat(fullClassName, ".class");

	*classContent = NULL;

	hFile = CreateFile(fullClassName,               // file to open
		GENERIC_READ,          // open for reading
		FILE_SHARE_READ,       // share for reading
		NULL,                  // default security
		OPEN_EXISTING,         // existing file only
		FILE_ATTRIBUTE_NORMAL, // normal file
		NULL);                 // no attr. template

	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("Directly open class file failed\n");
		return -1;
	}
	
	dwFileSize = GetFileSize(hFile, NULL);
	classBuffer = (char *)calloc((size_t)dwFileSize, 1);
	if (classBuffer == NULL)
		return -2;
	//printf("File size:%d\n", dwFileSize);

	if (ReadFile(hFile, classBuffer, dwFileSize, &dwActualRead, NULL) == FALSE)
	{
		printf("Failed to read file with 0x%02x\n", GetLastError());
		free(classBuffer);
		CloseHandle(hFile);
		return -3;
	}

	*classContent = classBuffer;

	CloseHandle(hFile);
	printf("Load class: %s from path:%s successfully,size:%d\n", className, path, dwFileSize);
	return (int32_t) dwFileSize;
}