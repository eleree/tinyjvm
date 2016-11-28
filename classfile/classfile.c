#include "classfile.h"
#include "attribute_info.h"

#pragma warning(disable:4996)

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

uint16_t * readClassUint16s(ClassFile * classFile)
{
	uint16_t needLen = readClassUint16(classFile);
	uint16_t * data = calloc(needLen, sizeof(uint16_t));
	for (int i = 0; i < 2; i++)
	{
		data[i] = *(classFile->data++);
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

void readClassInterfaces(ClassFile * classFile)
{
	classFile->interfaceCount = readClassUint16(classFile);	
	classFile->interfaces = calloc(classFile->interfaceCount, sizeof(uint16_t));
	for (int i = 0; i < classFile->interfaceCount; i++)
	{
		classFile->interfaces[i] = readClassUint16(classFile);
	}	
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

void * constantMethodrefInfo(void)
{
	return calloc(1, sizeof(ConstantMethodrefInfo));
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
	switch (tag)
	{
	case CONSTATNT_CLASS:
		((ConstantClassInfo*)itemInfo)->tag = tag;
		((ConstantClassInfo*)itemInfo)->nameIndex = readClassUint16(classFile);
		break;
	case CONSTATNT_FIELDREF:
		((ConstantFieldrefInfo*)itemInfo)->tag = tag;
		((ConstantFieldrefInfo*)itemInfo)->classIndex = readClassUint16(classFile);
		((ConstantFieldrefInfo*)itemInfo)->name_and_type_index = readClassUint16(classFile);
		break;
	case CONSTATNT_METHODREF:
		((ConstantMethodrefInfo*)itemInfo)->tag = tag;
		((ConstantMethodrefInfo*)itemInfo)->classIndex = readClassUint16(classFile);
		((ConstantMethodrefInfo*)itemInfo)->name_and_type_index = readClassUint16(classFile);
		break;
	case CONSTATNT_INTERFACE_METHODREF:
		((ConstantInterfaceMethodrefInfo*)itemInfo)->tag = tag;
		((ConstantInterfaceMethodrefInfo*)itemInfo)->class_index = readClassUint16(classFile);
		((ConstantInterfaceMethodrefInfo*)itemInfo)->name_and_type_index = readClassUint16(classFile);
		break;
	case CONSTATNT_STRING:
		((ConstantStringInfo*)itemInfo)->tag = tag;
		((ConstantStringInfo*)itemInfo)->string_index = readClassUint16(classFile);
		break;
	case CONSTATNT_INTEGER:
		((ConstantIntegerInfo*)itemInfo)->tag = tag;
		((ConstantIntegerInfo*)itemInfo)->bytes = readClassUint32(classFile);
		break;
	case CONSTATNT_FLOAT:
		((ConstantFloatInfo*)itemInfo)->tag = tag;
		((ConstantFloatInfo*)itemInfo)->bytes = readClassUint32(classFile);
		break;
	case CONSTATNT_LONG:
		((ConstantLongInfo*)itemInfo)->tag = tag;
		((ConstantLongInfo*)itemInfo)->high_bytes = readClassUint32(classFile);
		((ConstantLongInfo*)itemInfo)->low_bytes = readClassUint32(classFile);
		break;
	case CONSTATNT_DOUBLE:
		((ConstantDoubleInfo*)itemInfo)->tag = tag;
		((ConstantDoubleInfo*)itemInfo)->high_bytes = readClassUint32(classFile);
		((ConstantDoubleInfo*)itemInfo)->low_bytes = readClassUint32(classFile);
		break;
	case CONSTATNT_NAME_AND_TYPE:
		((ConstantNameAndTypeInfo*)itemInfo)->tag = tag;
		((ConstantNameAndTypeInfo*)itemInfo)->name_index = readClassUint16(classFile);
		((ConstantNameAndTypeInfo*)itemInfo)->descriptor_index = readClassUint16(classFile);
		break;
	case CONSTATNT_UTF8:
		((ConstantUtf8Info*)itemInfo)->tag = tag;
		((ConstantUtf8Info*)itemInfo)->length = readClassUint16(classFile);
		((ConstantUtf8Info*)itemInfo)->bytes = calloc(((ConstantUtf8Info*)itemInfo)->length + 1, sizeof(uint8_t));
		((ConstantUtf8Info*)itemInfo)->bytes[((ConstantUtf8Info*)itemInfo)->length] = '\0';
		for (uint16_t i = 0; i < ((ConstantUtf8Info*)itemInfo)->length; i++)
		{
			((ConstantUtf8Info*)itemInfo)->bytes[i] = readClassUint8(classFile);
		}
		break;
	case CONSTATNT_METHOD_HANDLE:
		((ConstantMethodHandleInfo*)itemInfo)->tag = tag;
		((ConstantMethodHandleInfo*)itemInfo)->reference_kind = readClassUint8(classFile);
		((ConstantMethodHandleInfo*)itemInfo)->reference_index = readClassUint16(classFile);
		break;
	case CONSTATNT_METHOD_TYPE:
		((ConstantMethodTypeInfo*)itemInfo)->tag = tag;
		((ConstantMethodTypeInfo*)itemInfo)->descriptor_index = readClassUint16(classFile);;
		break;
	case CONSTATNT_INVOKE_DYNAMIC:
		((ConstantInvokeDynamicInfo*)itemInfo)->tag = tag;
		((ConstantInvokeDynamicInfo*)itemInfo)->bootstrap_method_attr_index = readClassUint16(classFile);;
		((ConstantInvokeDynamicInfo*)itemInfo)->name_and_type_index = readClassUint16(classFile);;
		break;
	}

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
	classFile->constantPoolItem = calloc(classFile->constanPoolCount, sizeof(ConstantPoolItem));

	for (uint32_t i = 1; i < classFile->constanPoolCount; i++)
	{
		void * itemInfo = NULL;
		uint8_t tag = readClassUint8(classFile);
		itemInfo = newConstantInfo(tag);
		readConstantInfo(classFile, tag, itemInfo);
		classFile->constantPoolItem[i].itemInfo = itemInfo;

		if (tag == CONSTATNT_LONG || tag == CONSTATNT_DOUBLE)
			i++;
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
	classFile->accessFlags = readClassUint16(classFile);
	classFile->thisClass = readClassUint16(classFile);
	classFile->superClass = readClassUint16(classFile);
	//printClassInfo(classFile);
	readClassInterfaces(classFile);
	readClassFields(classFile);
	readClassMethods(classFile);
	readClassAttributes(classFile);
	return classFile;
}

uint16_t getClassUtf8Len(ClassFile * classFile, uint16_t utf8Index)
{
	ConstantUtf8Info * itemInfo = (ConstantUtf8Info *)(classFile->constantPoolItem + utf8Index)->itemInfo;

	/* java.lang.Objec */
	if (utf8Index == 0)
		return 0;

	if (classFile == NULL)
		return 0;

	if (itemInfo->tag != CONSTATNT_UTF8)
	{
		switch (itemInfo->tag)
		{
		case CONSTATNT_CLASS:
			return getClassUtf8Len(classFile, ((ConstantClassInfo*)itemInfo)->nameIndex);
			break;
		case CONSTATNT_FIELDREF:
			return getClassUtf8Len(classFile, ((ConstantFieldrefInfo*)itemInfo)->name_and_type_index);
			break;
		case CONSTATNT_METHODREF:
			return getClassUtf8Len(classFile, ((ConstantMethodrefInfo*)itemInfo)->name_and_type_index);
			break;
		case CONSTATNT_INTERFACE_METHODREF:
			break;
		case CONSTATNT_STRING:
			return getClassUtf8Len(classFile, ((ConstantStringInfo*)itemInfo)->string_index);
			break;
		case CONSTATNT_INTEGER:
			break;
		case CONSTATNT_FLOAT:
		case CONSTATNT_LONG:
			break;
		case CONSTATNT_DOUBLE:
			break;
		case CONSTATNT_NAME_AND_TYPE:
			return getClassUtf8Len(classFile, ((ConstantNameAndTypeInfo*)itemInfo)->name_index);
			break;
		case CONSTATNT_UTF8:
			break;
		case CONSTATNT_METHOD_HANDLE:
		case CONSTATNT_METHOD_TYPE:
		case CONSTATNT_INVOKE_DYNAMIC:
			break;
		default:
			return 0;
			break;
		}
	}

	return itemInfo->length;
}

const char * getClassUtf8(ClassFile * classFile, uint16_t utf8Index)
{
	ConstantUtf8Info * itemInfo = (ConstantUtf8Info *)(classFile->constantPoolItem + utf8Index)->itemInfo;

	/* java.lang.Objec */
	if (utf8Index == 0)
		return NULL;

	if (classFile == NULL)
		return NULL;

	if (itemInfo->tag != CONSTATNT_UTF8)
	{
		switch (itemInfo->tag)
		{
		case CONSTATNT_CLASS:
			return getClassUtf8(classFile, ((ConstantClassInfo*)itemInfo)->nameIndex);
			break;
		case CONSTATNT_FIELDREF:
			return getClassUtf8(classFile, ((ConstantFieldrefInfo*)itemInfo)->name_and_type_index);
			break;
		case CONSTATNT_METHODREF:
			return getClassUtf8(classFile, ((ConstantMethodrefInfo*)itemInfo)->name_and_type_index);
			break;
		case CONSTATNT_INTERFACE_METHODREF:
			break;
		case CONSTATNT_STRING:			
			return getClassUtf8(classFile, ((ConstantStringInfo*)itemInfo)->string_index);
			break;
		case CONSTATNT_INTEGER:
			break;
		case CONSTATNT_FLOAT:
		case CONSTATNT_LONG:
			break;
		case CONSTATNT_DOUBLE:
			break;
		case CONSTATNT_NAME_AND_TYPE:
			return getClassUtf8(classFile, ((ConstantNameAndTypeInfo*)itemInfo)->name_index);			
			break;
		case CONSTATNT_UTF8:
			break;
		case CONSTATNT_METHOD_HANDLE:
		case CONSTATNT_METHOD_TYPE:
		case CONSTATNT_INVOKE_DYNAMIC:
			break;
		default:
			return NULL;
			break;
		}		
	}

	return itemInfo->bytes;
}

MethodInfo * getMainMethod(ClassFile * classFile)
{
	MethodInfo * methodInfo;
	if (classFile == NULL || classFile->methodsCount == 0)
		return NULL;
	for (int i = 0; i < classFile->methodsCount; i++)
	{
		methodInfo = (classFile->methods) +i;
		const char * methodName = getClassUtf8(classFile, methodInfo->name_index);
		const char * methodDesc = getClassUtf8(classFile, methodInfo->descriptor_index);
		if (strcmp(methodName, "main") == 0 && strcmp(methodDesc, "([Ljava/lang/String;)V") == 0)
			return methodInfo;
	}
	return NULL;
}

CodeAttribute * getMethodCodeAttribute(ClassFile * classFile, MethodInfo * methodInfo)
{
	if (classFile == NULL || methodInfo == NULL)
		return NULL;
	for (int i = 0; i < methodInfo->attributes_count; i++)
	{
		AttributeInfo * attrInfo = (methodInfo->attributes) + i;
		const char * attrName = getClassUtf8(classFile, attrInfo->attributeNameIndex);
		if (strcmp(attrName, "Code") == 0)
			return attrInfo->info;
	}
	return NULL;
}

const char * getClassName(ClassFile * classFile)
{
	return getClassUtf8(classFile, classFile->thisClass);
}

const char * getSuperClassName(ClassFile * classFile)
{
	return getClassUtf8(classFile, classFile->superClass);
}

const char * getInterfaceName(ClassFile * classFile, uint16_t index)
{
	if (index > classFile->constanPoolCount)
		return NULL;
	return getClassUtf8(classFile, index);
}

int32_t printClassInfo(ClassFile * classFile)
{
	printf("Class Magic Number: 0x%x\n", classFile->header.magicNumber);
	printf("Minor Version: 0x%x\n", classFile->header.minorVersion);
	printf("Major Version: 0x%x\n", classFile->header.majorVersion);
	for (uint16_t i = 1; i < classFile->constanPoolCount; i++)
	{
		uint16_t refIndex = 0;
		ConstantUtf8Info * refUtf8 = NULL;
		uint8_t tag = ((ConstantClassInfo *)((classFile->constantPoolItem + i)->itemInfo))->tag;
		void * itemInfo = (classFile->constantPoolItem + i)->itemInfo;
		printf("####%d ", i);
		switch (tag)
		{
			case CONSTATNT_CLASS:
				refIndex = ((ConstantClassInfo*)itemInfo)->nameIndex;
				refUtf8 = (ConstantUtf8Info*)(classFile->constantPoolItem + refIndex);
				//printf("Class:\n");
				//printf("  name_index:%d -> %s \n", refIndex, refUtf8->bytes);
				break;
			case CONSTATNT_FIELDREF:
				printf("Field Ref:\n");
				printf("  class_index:%d\n",((ConstantFieldrefInfo*)itemInfo)->classIndex);
				printf("  name_and_type:index:%d\n",((ConstantFieldrefInfo*)itemInfo)->name_and_type_index);
				break;
			case CONSTATNT_METHODREF:
				printf("Method Ref:\n");
				printf("  class_index:%d\n", ((ConstantMethodrefInfo*)itemInfo)->classIndex);
				printf("  name_and_type_index:%d\n", ((ConstantMethodrefInfo*)itemInfo)->name_and_type_index);
				break;
			case CONSTATNT_INTERFACE_METHODREF:
				printf("Method Ref:\n");
				printf("  class_index:%d\n", ((ConstantInterfaceMethodrefInfo*)itemInfo)->class_index);
				printf("  name_and_type_index:%d\n", ((ConstantInterfaceMethodrefInfo*)itemInfo)->name_and_type_index);
				break;
			case CONSTATNT_STRING:
				refIndex = ((ConstantStringInfo*)itemInfo)->string_index;
				refUtf8 = (ConstantUtf8Info*)(classFile->constantPoolItem + refIndex);
				printf("String:\n");
				printf(" string_index:%d -> %s \n",refIndex, refUtf8);
				break;
			case CONSTATNT_INTEGER:
				printf("Integer: \n");
				printf("  bytes:%d\n", ((ConstantIntegerInfo*)itemInfo)->bytes);
				break;
			case CONSTATNT_FLOAT:
				break;
			case CONSTATNT_LONG:
				i++;
				break;
			case CONSTATNT_DOUBLE:
				i++;
				break;				
			case CONSTATNT_NAME_AND_TYPE:
				printf("NameAndType: \n");
				printf("  name_index:%d\n", ((ConstantNameAndTypeInfo*)itemInfo)->name_index);
				printf("  descriptor_index:%d\n", ((ConstantNameAndTypeInfo*)itemInfo)->descriptor_index);
				break;
			case CONSTATNT_UTF8:
				printf("UTF8: \n  ");
				for (uint16_t i = 0; i < ((ConstantUtf8Info*)itemInfo)->length; i++)
					printf("%c", ((ConstantUtf8Info*)itemInfo)->bytes[i]);
				printf("\n");
				break;
			case CONSTATNT_METHOD_HANDLE:
			case CONSTATNT_METHOD_TYPE:
			case CONSTATNT_INVOKE_DYNAMIC:
				break;
		}		
	}
	printf("Access Flag:0x%02x\n",classFile->accessFlags);
	printf("This class:%d -> %s\n", classFile->thisClass, getClassUtf8(classFile, classFile->thisClass));
	printf("Super class:%d -> %s\n", classFile->superClass, getClassUtf8(classFile, classFile->superClass));
	printf("Interface Count:%d\n", classFile->interfaceCount);
	return 0;

}

void deleteClassFile(ClassFile * classFile)
{
	if (classFile != NULL)
		free(classFile);
}

const char * getConstantPoolUtf8(ConstantPoolItem * constantPool, uint16_t utf8Index)
{
	ConstantUtf8Info * itemInfo = (ConstantUtf8Info *)(constantPool + utf8Index)->itemInfo;

	if (itemInfo->tag != CONSTATNT_UTF8)
		return NULL;

	return itemInfo->bytes;
}

const char * getConstantPoolMutf8(ClassFile * classFile, uint16_t utf8Index)
{
	return getClassUtf8(classFile, utf8Index);
}

uint16_t getConstantPoolMutf8Len(ClassFile * classFile, uint16_t utf8Index)
{
	return getClassUtf8Len(classFile, utf8Index);
}


const char * getConstalPoolNameAndTypeName(ConstantPoolItem * constantPool, uint16_t nameAndTypeIndex)
{
	ConstantNameAndTypeInfo * itemInfo = (ConstantNameAndTypeInfo *)(constantPool + nameAndTypeIndex)->itemInfo;

	if (itemInfo->tag != CONSTATNT_NAME_AND_TYPE)
		return NULL;

	return getConstantPoolUtf8(constantPool, itemInfo->name_index);
}

const char * getConstalPoolNameAndTypeDescriptor(ConstantPoolItem * constantPool, uint16_t nameAndTypeIndex)
{
	ConstantNameAndTypeInfo * itemInfo = (ConstantNameAndTypeInfo *)(constantPool + nameAndTypeIndex)->itemInfo;

	if (itemInfo->tag != CONSTATNT_NAME_AND_TYPE)
		return NULL;

	return getConstantPoolUtf8(constantPool, itemInfo->descriptor_index);
}

SourceFileAttribute * getClassFileSourceFile(ClassFile * classFile)
{
	for (uint16_t i = 0; i < classFile->attributes_count; i++)
	{
		AttributeInfo * attrInfo = (classFile->attributes) + i;
		const char * attrName = getClassUtf8(classFile, attrInfo->attributeNameIndex);
		if (strcmp(attrName, "SourceFile") == 0)
		{
			return (SourceFileAttribute *)attrInfo->info;
		}
	}
	return NULL;	
}

char * getClassSourceFileName(ClassFile * classFile)
{
	SourceFileAttribute * sourceFileAttr = getClassFileSourceFile(classFile);
	if (sourceFileAttr == NULL)
	{
		return strdup("Unknown");
	}
	const char * sourceName = getClassUtf8(classFile, sourceFileAttr->sourcefile_index);

	return strdup(sourceName);
}