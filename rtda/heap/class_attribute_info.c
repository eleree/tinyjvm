#include "class_attribute_info.h"

void * copyCodeAttributeInfo(ClassFile * classFile, void * sourceAttr)
{
	CodeAttribute * codeAttr = calloc(1, sizeof(CodeAttribute));
	CodeAttribute * srcAttr = (CodeAttribute*)sourceAttr;
	codeAttr->max_stack = srcAttr->max_stack;
	codeAttr->max_locals = srcAttr->max_locals;
	codeAttr->code_length = srcAttr->code_length;
	codeAttr->code = calloc(codeAttr->code_length, sizeof(uint8_t));
	for (uint32_t i = 0; i < codeAttr->code_length; i++)
		codeAttr->code[i] = srcAttr->code[i];
	codeAttr->exception_table_length = srcAttr->exception_table_length;
	codeAttr->exception_table = calloc(codeAttr->exception_table_length, sizeof(ExceptionTableEntry));
	for (uint16_t i = 0; i < codeAttr->exception_table_length; i++)
	{
		codeAttr->exception_table[i].start_pc = srcAttr->exception_table[i].start_pc;
		codeAttr->exception_table[i].end_pc = srcAttr->exception_table[i].end_pc;
		codeAttr->exception_table[i].handler_pc = srcAttr->exception_table[i].handler_pc;
		codeAttr->exception_table[i].catch_type = srcAttr->exception_table[i].catch_type;
	}
	codeAttr->attributes_count = srcAttr->attributes_count;
	codeAttr->attributes = NULL;
	if (codeAttr->attributes_count != 0)
	{
		codeAttr->attributes = calloc(codeAttr->attributes_count, sizeof(AttributeInfo));
		for (uint16_t i = 0; i < codeAttr->attributes_count; i++)
		{
			//readAttributeInfo(classFile, codeAttr->attributes, 1);
			copyAttributeInfo(classFile,codeAttr->attributes+i, srcAttr->attributes,1);
		}
	}

	return codeAttr;
}

void * copyConstantValueAttributeInfo(ClassFile * classFile, void * sourceAttr)
{
	//ConstantValueAttribute * constantValueAttr = 
	return NULL;
}

void * copyDeprecatedAttributeInfo(ClassFile * classFile, void * sourceAttr)
{
	return NULL;
}

void * copyLineNumberTableAttributeInfo(ClassFile * classFile, void * sourceAttr)
{
	return NULL;
}

void * copyExceptionsAttributeInfo(ClassFile * classFile, void * sourceAttr)
{
	return NULL;
}

void * copyLocalVariableTableAttributeInfo(ClassFile * classFile, void * sourceAttr)
{
	return NULL;
}

void * copySourceFileAttributeInfo(ClassFile * classFile, void * sourceAttr)
{
	return NULL;
}

void * copySignatureAttributeInfo(ClassFile * classFile, void * sourceAttr)
{
	return NULL;
}

void * copyUnparsedAttributeInfo(ClassFile * classFile, void * sourceAttr)
{
	return NULL;
}

void * newCopyAttributeInfo(const char * attrName, void * sourceAttr, ClassFile *classFile)
{
	if (attrName == NULL)
		return NULL;
	if (strcmp("Code", attrName) == 0){
		return copyCodeAttributeInfo(classFile, sourceAttr);
	}
	else if (strcmp("ConstantValue", attrName) == 0){
		return copyConstantValueAttributeInfo(classFile, sourceAttr);
	}
	else if (strcmp("Deprecated", attrName) == 0){
		return copyDeprecatedAttributeInfo(classFile, sourceAttr);
	}
	else if (strcmp("Exceptions", attrName) == 0){
		return copyExceptionsAttributeInfo(classFile, sourceAttr);
	}
	else if (strcmp("LineNumberTable", attrName) == 0){
		return copyLineNumberTableAttributeInfo(classFile, sourceAttr);
	}
	else if (strcmp("LocalVariableTable", attrName) == 0){
		return copyLocalVariableTableAttributeInfo(classFile, sourceAttr);
	}
	else if (strcmp("Source", attrName) == 0){
		return copySourceFileAttributeInfo(classFile, sourceAttr);
	}
	else if (strcmp("Synthetic", attrName) == 0){
		return copySignatureAttributeInfo(classFile, sourceAttr);
	}
	else{
		return copyUnparsedAttributeInfo(classFile, sourceAttr);
	}

	return NULL;
}


void copyAttributeInfo(ClassFile * classFile, AttributeInfo * destAttr, AttributeInfo * sourceAttr, uint16_t count)
{
	for (uint16_t i = 0; i < count; i++)
	{
		uint16_t attrNameIndex = sourceAttr[i].attributeNameIndex;
		const char * attrName = getClassUtf8(classFile, attrNameIndex);
		uint32_t attrLen = sourceAttr[i].attributeLength;

		destAttr[i].info = newCopyAttributeInfo(attrName, sourceAttr[i].info, classFile); //Factory to copy info
		destAttr[i].attributeNameIndex = attrNameIndex;
		destAttr[i].attributeLength = attrLen;
	}
}
