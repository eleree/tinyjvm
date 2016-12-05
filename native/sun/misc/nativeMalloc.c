#include "../../registry.h"

typedef struct MallocNode
{
	int64_t address;
	uint8_t * bytes;
	int64_t bytesLen;
	struct MallocNode * next;
}MallocNode;

int64_t _nextAddress = 64;

static MallocNode * rootNode = NULL;

void insertMallocNode(int64_t address, uint8_t * bytes, int64_t bytesLen)
{
	MallocNode * newNode = calloc(1, sizeof(MallocNode));
	MallocNode * preNode = rootNode;

	newNode->address = address;
	newNode->bytes = bytes;
	newNode->bytesLen = bytesLen;

	if (rootNode == NULL)
	{
		rootNode = newNode;
		return;
	}

	while (preNode->next != NULL)
		preNode = preNode->next;

	preNode->next = newNode;

	return;
}

MallocNode * findMallocNode(int64_t address)
{
	MallocNode * mallocNode = rootNode;
	while (mallocNode != NULL)
	{
		if (mallocNode->address == address)
			return mallocNode;

		mallocNode = mallocNode->next;
	}
	return NULL;
}

uint8_t * memoryAt(int64_t address, int64_t * bytesLen)
{
	MallocNode * mallocNode = rootNode;
	while (mallocNode != NULL)
	{
		int64_t startAddress = mallocNode->address;
		int64_t endAddress = startAddress + mallocNode->bytesLen;
		if (address >= startAddress && address < endAddress)
		{
			int64_t offset = address - startAddress;
			*bytesLen = mallocNode->bytesLen - offset;
			return mallocNode->bytes + offset;
		}
		mallocNode = mallocNode->next;
	}
	return NULL;
}

int64_t allocateNativeMemory(int64_t size)
{
	uint8_t * mem = calloc((size_t)size, sizeof(uint8_t));
	
	int64_t address = _nextAddress;
	
	insertMallocNode(address, mem, size);

	_nextAddress += size;

	return address;

}



void freeNativeMemory(int64_t address)
{

}

int64_t reallocateNativeMemory(int64_t address, int64_t size)
{
	int64_t memLen = 0;
	uint8_t * mem = NULL;
	if (size == 0)
		return 0;

	if (address == 0)
		return allocateNativeMemory(size);


	mem = memoryAt(address, &memLen);

	if (memLen > size)
		return address;
	else
	{
		int64_t newAddress = allocateNativeMemory(size);
		int64_t newMemLen = 0;
		uint8_t * newMem = memoryAt(newAddress, &newMemLen);
		for (int64_t i = 0; i < newMemLen; i++)
			newMem[i] = mem[i];
		return newAddress;
	}

}