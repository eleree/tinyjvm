#include "classpath.h"
#include "entry.h"
#include "../strings/strings.h"
#include <windows.h>
#pragma comment(lib, "User32.lib")
#pragma warning(disable:4996)

static char _jrepath[128] = { 0 };
static char _classpath[128] = { 0 };

int32_t parseClasspath(const char * jrepath, const char * classpath)
{
	if (jrepath != NULL)
		strncpy_s(_jrepath, 128, jrepath, 128);

	if (classpath != NULL)
		strncpy_s(_classpath,128, classpath, 128);

	return 0;
}

int32_t bootClasspathReadClass(const char * className, char ** classContent)
{
	int32_t classSize = 0;
	WIN32_FIND_DATA ffd;
	HANDLE hFile = INVALID_HANDLE_VALUE;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	char fullJrePath[128] = { 0 };
	// Find class file directly

	if ((classSize = readDirEntryClass(_jrepath, className, classContent)) > 0)
		return classSize;
		
	// Find all jar files
	strcat(fullJrePath, _jrepath);
	strcat(fullJrePath, "\\*");
	hFind = FindFirstFile(fullJrePath, &ffd);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		printf("Fail to find first file\n");
		return -1;
	}

	do
	{
		char zipFile[128] = { 0 };
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;
	
		if (stringHasSuffix(ffd.cFileName, ".jar") == 0)
		{
			strcat(zipFile, _jrepath);
			strcat(zipFile, "\\");
			strcat(zipFile, ffd.cFileName);
			printf("Reading zip file %s\n",zipFile);
			if ((classSize = readZipEntryClass(zipFile, className, classContent)) > 0)
				return  classSize;
		}
		
		
	} while (FindNextFile(hFind, &ffd) != 0);
	return 0;
}

int32_t extClasspathReadClass(const char * className, char ** classContent)
{
	return 0;
}

int32_t userClasspathReadClass(const char * className, char ** classContent)
{
	return 0;
}

int32_t readClass(const char * className, char ** classContent)
{
	int32_t classSize = 0;
	if (className != NULL)
		printf("class name: %s\n",className);

	if ((classSize = bootClasspathReadClass(className, classContent) )> 0)
	{
		return classSize;
	}

	if ((classSize = extClasspathReadClass(className, classContent))> 0)
	{
		return classSize;
	}

	if ((classSize = userClasspathReadClass(className, classContent))> 0)
	{
		return classSize;
	}

	return 0;
}