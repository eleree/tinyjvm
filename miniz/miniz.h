#ifndef __TINY_JVM_MINIZ_H__
#define __TINY_JVM_MINIZ_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(1) 

typedef  struct _EndCentralDirectoryRecord{
	uint32_t signature; // \x50\x4b\x05\x06
	uint16_t diskNumber; 
	uint16_t centralDirectoryDiskNumber; 
	uint16_t numEntriesThisDisk;
	uint16_t numEntries;
	uint32_t centralDirectorySize;
	uint32_t centralDirectoryOffset;
	uint16_t zipCommentLength;
}EndCentralDirectoryRecord;


typedef struct _LocalFileHeader
{
	uint32_t signature; // \x50\x4b\x03\x04
	uint16_t versionNeededToExtract; // unsupported
	uint16_t generalPurposeBitFlag; // unsupported
	uint16_t compressionMethod;
	uint16_t lastModFileTime;
	uint16_t lastModFileDate;	
	uint32_t crc32;
	uint32_t compressedSize;
	uint32_t uncompressedSize;
	uint16_t fileNameLength;
	uint16_t extraFieldLength; // unsupported
}LocalFileHeader;

typedef struct _CentralDirectoryFileHeader
{
	uint32_t signature; // \x50\x4b\x01\x02
	uint16_t versionMadeBy; // unsupported
	uint16_t versionNeededToExtract; // unsupported
	uint16_t generalPurposeBitFlag; // unsupported
	uint16_t compressionMethod;
	uint16_t lastModFileTime;
	uint16_t lastModFileDate;
	uint32_t crc32;
	uint32_t compressedSize;
	uint32_t uncompressedSize;
	uint16_t fileNameLength;
	uint16_t extraFieldLength; // unsupported
	uint16_t fileCommentLength; // unsupported
	uint16_t diskNumberStart; // unsupported
	uint16_t internalFileAttributes; // unsupported
	uint32_t externalFileAttributes; // unsupported
	uint32_t relativeOffsetOflocalHeader;
}CentralDirectoryFileHeader;

typedef struct _ZipFile
{
	FILE * file;
	CentralDirectoryFileHeader centralDirectoryFileHeader;
	LocalFileHeader localFileHeader;
	EndCentralDirectoryRecord endCentralDirectory;
}ZipFile;

#pragma pack()

typedef struct _ZipStream
{
	uint8_t * stream;
	uint8_t remainBits;
	uint8_t remainBitsNum;
	uint32_t outBytes;
	int32_t totalBytes;
	int32_t status;
}ZipStream;

#define MINIZ_DEFLATE_HEADER_MASK		0x07
#define MINIZ_DEFLATE_HLIT_MASK			0x1F
#define MINIZ_DEFLATE_HDIST_MASK		0x1F
#define MINIZ_DEFLATE_HCLEN_MASK		0x0F

ZipStream * openStream(ZipFile * zipFIle);
uint8_t streamReadBits(ZipStream * zipStream, uint8_t bits);
int32_t closeStream(ZipStream * zipStream);

ZipFile* openZip(const char * zipName);
int32_t listZipFile(ZipFile* zipFile);
int32_t haveZipFile(ZipFile* zipFile, const char * zipFileName);
char * readZipFile(ZipFile* zipFile, const char zipFileName);
int32_t closeZip(ZipFile* zipFile);


#endif