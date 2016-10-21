#include "miniz.h"

#pragma warning(disable : 4996)

/* Swap bytes in 32 bit value.  */
#define __bswap_constant_32(x) \
	((((x)& 0xff000000) >> 24) | (((x)& 0x00ff0000) >> 8) | \
	(((x)& 0x0000ff00) << 8) | (((x)& 0x000000ff) << 24)

int32_t readZipLocalHeader(ZipFile * zipFile, LocalFileHeader * localHeader)
{
	fread(localHeader, 1, sizeof(LocalFileHeader), zipFile->file);
	printf("signature:0x%08x\n", localHeader->signature);
	if (localHeader->signature != 0x04034b50)
	{
		printf("Invaild Local File Header Value:0x%08x\n", localHeader->signature);
		return -1;
	}
	printf("versionNeededToExtract:0x%04x\n", localHeader->versionNeededToExtract);
	printf("generalPurposeBitFlag:0x%04x\n", localHeader->generalPurposeBitFlag);
	printf("compressionMethod:0x%04x\n", localHeader->compressionMethod);
	printf("lastModFileTime:0x%04x\n", localHeader->lastModFileTime);
	printf("lastModFileDate:0x%04x\n", localHeader->lastModFileDate);
	printf("crc32:0x%08x\n", localHeader->crc32);
	printf("compressed size:0x%04x\n", localHeader->compressedSize);
	printf("uncompressed size:0x%04x\n", localHeader->uncompressedSize);
	return 0;
}

int32_t readZipEndCentralDirectoryRecord(ZipFile * zipFile, EndCentralDirectoryRecord * endRecord)
{
	return 0;
}

int32_t readZipCentralDirectoryFileHeader(ZipFile * zipFile, CentralDirectoryFileHeader * centralHeader)
{
	return 0;
}


ZipFile* openZip(const char * zipName)
{
	ZipFile * zipFile = (ZipFile*)calloc(1, sizeof(ZipFile));;

	LocalFileHeader localHeader;
	CentralDirectoryFileHeader centralHeader;
	EndCentralDirectoryRecord endRecord;

	zipFile->file = fopen(zipName, "r");
	if (zipFile->file == NULL)
	{
		free(zipFile);
		return NULL;
	}

	if (readZipLocalHeader(zipFile, &localHeader) != 0)
	{
		free(zipFile);
		return NULL;
	}


	fclose(zipFile->file);
	
	return NULL;
}

int32_t listZipFile(ZipFile* zipFile)
{
	return 0;
}

int32_t haveZipFile(ZipFile* zipFile, const char * zipFileName)
{
	return 0;
}

char * readZipFile(ZipFile* zipFile, const char zipFileName)
{
	return NULL;
}

int32_t closeZip(ZipFile* zipFile)
{
	return 0;
}