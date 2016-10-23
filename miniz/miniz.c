#include "miniz.h"

#pragma warning(disable : 4996)

/* Swap bytes in 32 bit value.  */
#define __bswap_constant_32(x) \
	((((x)& 0xff000000) >> 24) | (((x)& 0x00ff0000) >> 8) | \
	(((x)& 0x0000ff00) << 8) | (((x)& 0x000000ff) << 24)

static const unsigned char mirrorbytes[256] = {
	0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
	0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
	0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
	0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
	0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
	0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
	0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
	0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
	0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
	0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
	0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
	0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
	0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
	0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
	0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
	0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
	0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
	0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
	0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
	0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
	0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
	0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
	0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
	0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
	0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
	0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
	0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
	0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
	0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
	0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
	0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
	0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff,
};

ZipStream * openStream(ZipFile * zipFile)
{
	char * deflateData = NULL;
	ZipStream * zipStream = (ZipStream *)calloc(1, sizeof(ZipStream));
	fseek(zipFile->file, zipFile->localFileHeader.fileNameLength + sizeof(LocalFileHeader), SEEK_SET);
	deflateData = (char *)calloc(zipFile->localFileHeader.compressedSize, 1);
	fread(deflateData, 1, zipFile->localFileHeader.compressedSize, zipFile->file);
	zipStream->stream = (uint8_t *)deflateData;
	zipStream->outBytes = 0;
	zipStream->totalBytes = zipFile->localFileHeader.compressedSize;
	return zipStream;
}

uint8_t streamReadByte(ZipStream * zipStream)
{
	uint8_t streamData = zipStream->stream[zipStream->outBytes];
	zipStream->outBytes++;
	return streamData;
}

uint8_t streamReadBits(ZipStream * zipStream, uint8_t bitsNum)
{
	uint8_t resultBits = 0x0;
	uint8_t needByte = 0x00;
	if (bitsNum <= zipStream->remainBitsNum)
	{
		resultBits |= zipStream->remainBits;
		resultBits &= (0xFF >> (8 - bitsNum));
		zipStream->remainBits >>= bitsNum;
		zipStream->remainBitsNum -= bitsNum;
		return resultBits;
	}

	needByte = streamReadByte(zipStream);
	
	resultBits |= zipStream->remainBits;
	resultBits &= (0xFF >> (8 - zipStream->remainBitsNum));

	resultBits |= (needByte << zipStream->remainBitsNum);
	resultBits &= (0xFF >> (8 - bitsNum));
	zipStream->remainBits = needByte >>  (bitsNum - zipStream->remainBitsNum);
	zipStream->remainBitsNum = 8 - (bitsNum -zipStream->remainBitsNum);
	
	return resultBits;
}

int32_t closeStream(ZipStream * zipStream)
{
	return 0;
}

void reverseCCL(uint8_t * ccl)
{
	uint8_t tempCCL[19] = { 0 };
	uint8_t reverseLoc[19] = {16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15};
	for (int i = 0; i < 19; i++)
	{
		tempCCL[reverseLoc[i]] = ccl[i];
	}
	for (int i = 0; i < 19; i++)
	{
		ccl[i] = tempCCL[i];
	}
}

int32_t readZipLocalHeader(ZipFile * zipFile, LocalFileHeader * localHeader)
{
	char * deflateData = NULL;
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
	printf("fileNameLength :0x%04x\n", localHeader->fileNameLength);

	memcpy(&zipFile->localFileHeader, localHeader, sizeof(LocalFileHeader));

	ZipStream *  zipStream = openStream(zipFile);
	uint8_t Header = 0;
	uint8_t HCLEN = 0;
	uint8_t HLIT = 0;
	uint8_t HDIST = 0;
	Header = streamReadBits(zipStream, 3);
	HLIT = streamReadBits(zipStream, 5);
	HDIST = streamReadBits(zipStream, 5);
	HCLEN = streamReadBits(zipStream, 4);

	uint8_t CCLNum = HCLEN + 4;
	uint16_t CL1Num = HLIT + 257;
	uint16_t CL2Num = HDIST + 1;
	uint8_t CCL[19] = { 0 };

	printf("Header:0x%02x\n", Header);
	printf("HLIT:0x%02x\n", HLIT);
	printf("HDIST:0x%02x\n", HDIST);
	printf("HCLEN:0x%02x\n", HCLEN);
	for (int i = 0; i < CCLNum; i++)
	{
		CCL[i] = streamReadBits(zipStream, 3);
		printf("CCL%d:0x%02x\n", i, CCL[i]);
	}
	
	reverseCCL(CCL);

	for (int i = 0; i < 19; i++)
	{
		printf("Reversed CCL%d:0x%02x\n", i, CCL[i]);
	}

#define MAX_BITS 5
	typedef struct Tree{
		uint8_t Code;
		uint8_t Len;
	}Tree;
	uint8_t code = 0;
	uint8_t bl_count[] = { 0,0,1,5,2 };
	uint8_t next_code[11] = {0};
	for (int bits = 1; bits <= MAX_BITS; bits++) {
		code = (code + bl_count[bits - 1]) << 1;
		next_code[bits] = code;
	}
	for (int i = 0; i < MAX_BITS; i++)
	{
		printf("%d\n",next_code[i]);
	}
	
	Tree tree[20] = { { 'A', 3 }, { 'B', 3 }, { 'C', 3 }, { 'D', 3 }	\
	, { 'E', 3 }, { 'F', 2 }, { 'G', 4 }, { 'H', 4 } };
	uint8_t max_code = 8;
	
	for (int n = 0; n <= max_code; n++) {
		int len = tree[n].Len;
		if (len != 0) {
			tree[n].Code = next_code[len];
			next_code[len]++;
		}
	}
	printf("Code:\n");
	for (int i = 0; i < max_code; i++)
	{
		printf("0x%02x\n", tree[i].Code);
	}
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
//	CentralDirectoryFileHeader centralHeader;
//	EndCentralDirectoryRecord endRecord;

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