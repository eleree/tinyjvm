#include "classfile.h"


int32_t readClassBytes(ClassFile * classFile)
{
	return 0;
}

uint8_t readClassUint8(ClassFile * classFile)
{
	uint8_t data = 0x00;
	data |= *(classFile->data++);

	return data;
}

uint16_t readClassUint16(ClassFile * classFile)
{
	uint16_t data = 0x00;
	for (int i = 0; i < 2; i++)
	{
		data <<= 8;
		data |= *(classFile->data++);
	}

	return data;
}

uint32_t readClassUint32(ClassFile * classFile)
{
	uint32_t data = 0x00;
	for (int i = 0; i < 4; i++)
	{
		data <<= 8;
		data |= *(classFile->data++);
	}

	return data;
}

uint64_t readClassUint64(ClassFile * classFile)
{
	uint64_t data = 0x00;
	for (int i = 0; i < 8; i++)
	{
		data <<= 8;
		data |= *(classFile->data++);		
	}
		
	return data;
}

void readAndCheckMagic(ClassFile * classFile)
{
	classFile->header.magicNumber = readClassUint32(classFile);
	if (classFile->header.magicNumber != 0xCAFEBABE)
	{
		printf("java.lang.ClassFormatError: magic!");
		exit(0);
	}
}

void readAndCheckVersion(ClassFile * classFile)
{
	classFile->header.minorVersion = readClassUint16(classFile);
	classFile->header.majorVersion = readClassUint16(classFile);
	switch (classFile->header.majorVersion)
	{
	case 45:
		return;
		break;
	case 46:
	case 47:
	case 48:
	case 49:
	case 50:
	case 51:
	case 52:
		if (classFile->header.minorVersion == 0)
			return;
		break;
	default:
		break;
	}
	printf("java.lang.UnsupportedClassVersionError!\n");
	exit(0);
}

// Malloc Constant Pool Item Functions
void * constantIntegerInfo(void)
{
	return calloc(1, sizeof(ConstantIntegerInfo));
}

void * constantFloatInfo(void)
{
	return calloc(1, sizeof(ConstantFloatInfo));
}

void * constantLongInfo(void)
{
	return calloc(1, sizeof(ConstantLongInfo));
}

void * constantDoubleInfo(void)
{
	return calloc(1, sizeof(ConstantDoubleInfo));
}

void * constantUtf8Info(void)
{
	return calloc(1, sizeof(ConstantUtf8Info));
}

void * constantStringInfo(void)
{
	return calloc(1, sizeof(ConstantStringInfo));
}

void * constantClassInfo(void)
{
	return calloc(1, sizeof(ConstantClassInfo));
}

void * constantFieldrefInfo(void)
{
	return calloc(1, sizeof(ConstantFieldrefInfo));
}

void * constantInterfaceMethodrefInfo(void)
{
	return calloc(1, sizeof(ConstantInterfaceMethodrefInfo));
}

void * constantNameAndTypeInfo(void)
{
	return calloc(1, sizeof(ConstantNameAndTypeInfo));
}

void * constantMethodTypeInfo(void)
{
	return calloc(1, sizeof(ConstantMethodTypeInfo));
}

void * constantMethodHandleInfo(void)
{
	return calloc(1, sizeof(ConstantMethodHandleInfo));
}

void * constantInvokeDynamicInfo(void)
{
	return calloc(1, sizeof(ConstantInvokeDynamicInfo));
}

int32_t readConstantInfo(ClassFile * classFile, uint8_t tag, void * itemInfo)
{
	ConstantPoolItem * rootItem = &classFile->constantPoolItem;
	while (rootItem->next != NULL)
		rootItem = rootItem->next;

	switch (tag)
	{
	case CONSTATNT_CLASS:
		((ConstantClassInfo*)itemInfo)->tag = tag;
		((ConstantClassInfo*)itemInfo)->nameIndex = readClassUint16(classFile);
	case CONSTATNT_FIELDREF:
	case CONSTATNT_METHODREF:
	case CONSTATNT_INTERFACE_METHODREF:
	case CONSTATNT_STRING:
	case CONSTATNT_INTEGER:
		((ConstantIntegerInfo*)itemInfo)->tag = tag;
		((ConstantIntegerInfo*)itemInfo)->bytes = readClassUint32(classFile);
		break;
	case CONSTATNT_FLOAT:
	case CONSTATNT_LONG:
	case CONSTATNT_DOUBLE:
	case CONSTATNT_NAME_AND_TYPE:
	case CONSTATNT_UTF8:
	case CONSTATNT_METHOD_HANDLE:
	case CONSTATNT_METHOD_TYPE:
	case CONSTATNT_INVOKE_DYNAMIC:
		break;
	}

	rootItem->next = (ConstantPoolItem*)calloc(1, sizeof(ConstantPoolItem));
	rootItem->next->tag = tag;
	rootItem->next->next = NULL;
	rootItem->next->itemInfo = itemInfo;

	return 0;
}

void * newConstantInfo(uint8_t tag)
{
	switch (tag)
	{
	case CONSTATNT_CLASS:
		return constantClassInfo();
	case CONSTATNT_FIELDREF:
		return constantFieldrefInfo();
	case CONSTATNT_METHODREF:
		return constantMethodrefInfo();
	case CONSTATNT_INTERFACE_METHODREF:
		return constantInterfaceMethodrefInfo();
	case CONSTATNT_STRING:
		return constantStringInfo();
	case CONSTATNT_INTEGER:
		return constantIntegerInfo();		
	case CONSTATNT_FLOAT:
		return constantFloatInfo();
	case CONSTATNT_LONG:
		return constantLongInfo();
	case CONSTATNT_DOUBLE:
		return constantDoubleInfo();
	case CONSTATNT_NAME_AND_TYPE:
		return constantNameAndTypeInfo();
	case CONSTATNT_UTF8:
		return constantUtf8Info();
	case CONSTATNT_METHOD_HANDLE:
		return constantMethodHandleInfo();
	case CONSTATNT_METHOD_TYPE:
		return constantMethodTypeInfo();
	case CONSTATNT_INVOKE_DYNAMIC:
		return constantInvokeDynamicInfo();
	default:
			break;
	}
	return NULL;
}

void readConstantPool(ClassFile * classFile)
{
	classFile->constanPoolCount = readClassUint16(classFile);
	for (uint32_t i = 0; i < classFile->constanPoolCount; i++)
	{
		void * itemInfo = NULL;
		uint8_t tag = readClassUint8(classFile);
		itemInfo = newConstantInfo(tag);
		readConstantInfo(classFile, tag, itemInfo);
	}
	
}

ClassFile * parseClassData(uint8_t * classData, uint64_t classSize)
{
	
	ClassFile * classFile = (ClassFile *)calloc(1, sizeof(ClassFile));

	classFile->data = classData;
	classFile->size = classSize;
	readAndCheckMagic(classFile);
	readAndCheckVersion(classFile);
	readConstantPool(classFile);
	return classFile;
}

int32_t printClassInfo(ClassFile * classFile)
{
	printf("Class Magic Number: 0x%x\n", classFile->header.magicNumber);
	printf("Minor Version: 0x%x\n", classFile->header.minorVersion);
	printf("Major Version: 0x%x\n", classFile->header.majorVersion);
	return 0;
}

void deleteClassFile(ClassFile * classFile)
{
	if (classFile != NULL)
		free(classFile);
}