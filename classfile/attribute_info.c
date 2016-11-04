#include "attribute_info.h"


void readCodeAttributeInfo(ClassFile * classFile)
{
	CodeAttribute * codeAttr = calloc(1, sizeof(CodeAttribute));
}

void * newAttributeInfo(const char * attrName, uint32_t attrLen, ClassFile * classFile)
{
	if (attrName == NULL)
		return NULL;
	if (strcmp("Code", attrName) == 0){
		readCodeAttributeInfo(classFile);
	}else if (strcmp("ConstantValue", attrName) == 0){
	}
	else if (strcmp("Deprecated", attrName) == 0){
	}
	else if (strcmp("Exceptions", attrName) == 0){
	}
	else if (strcmp("LineNumberTable", attrName) == 0){
	}
	else if (strcmp("LocalVariableTable", attrName) == 0){
	}
	else if (strcmp("Source", attrName) == 0){
	}
	else if (strcmp("Synthetic", attrName) == 0){
	}else{

	}
	
	return NULL;
}

void readAttributeInfo(ClassFile * classFile, AttributeInfo * attribute, uint16_t count)
{
	for (uint16_t i = 0; i < count; i++)
	{
		uint16_t attrNameIndex = readClassUint16(classFile);
		const char * attrName = getClassUtf8(classFile, attrNameIndex);
		uint16_t attrLen = readClassUint16(classFile);

		attribute[i].info = newAttributeInfo(attrName, attrLen, classFile);
		attribute[i].attributeLength = attrLen;
		attribute[i].attributeNameIndex = attrNameIndex;
	}
}

void readFields(ClassFile * classFile)
{
	classFile->fieldsCount = readClassUint16(classFile);
	if (classFile->fieldsCount == 0)
		return;
	classFile->fields = calloc(classFile->fieldsCount, sizeof(FieldInfo));
	for (uint16_t i = 0; i < classFile->fieldsCount; i++)
	{

	}
}

void readMethods(ClassFile * classFile)
{
	classFile->methodsCount = readClassUint16(classFile);
	if (classFile->methodsCount == 0)
		return;
	classFile->methods = calloc(classFile->methodsCount, sizeof(MethodInfo));
	for (uint16_t i = 0; i < classFile->methodsCount; i++)
	{
		(classFile->methods + i)->access_flags = readClassUint16(classFile);
		(classFile->methods + i)->name_index = readClassUint16(classFile);
		(classFile->methods + i)->attributes_count = readClassUint16(classFile);
		readAttributeInfo(classFile, (classFile->methods + i)->attributes, (classFile->methods + i)->attributes_count);
	}
}