#include "classfile.h"


int32_t readClassBytes(ClassFile * classFile)
{
	return 0;
}

uint8_t readClassUint8(ClassFile * classFile)
{
	return 0;
}

uint16_t readClassUint16(ClassFile * classFile)
{
	return 0;
}

uint32_t readClassUint32(ClassFile * classFile)
{
	uint32_t data = 0x00;
	for (int i = 0; i < 4; i++)
	{
		data |= *(classFile->data);
		data <<= 8;
		classFile->data++;
	}

	return data;
}

uint64_t readClassUint64(ClassFile * classFile)
{
	uint64_t data = 0x00;
	for (int i = 0; i < 8; i++)
	{
		data |= *(classFile->data);
		data <<= 8;
		classFile->data++;
	}
		
	return data;
}


ClassFile * parseClassData(uint8_t classData, uint64_t classSize)
{

	return NULL;
}

int32_t printClassInfo(ClassFile * classFile)
{
	printf("Class Name: \n");
	return 0;
}