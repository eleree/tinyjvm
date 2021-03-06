#include "attribute_info.h"


CodeAttribute * readCodeAttributeInfo(ClassFile * classFile)
{
	CodeAttribute * codeAttr = calloc(1, sizeof(CodeAttribute));
	codeAttr->max_stack = readClassUint16(classFile);
	codeAttr->max_locals = readClassUint16(classFile);
	codeAttr->code_length = readClassUint32(classFile);
	codeAttr->code = calloc(codeAttr->code_length, sizeof(uint8_t));
	for (uint32_t i = 0; i < codeAttr->code_length; i++)
		codeAttr->code[i] = readClassUint8(classFile);
	codeAttr->exception_table_length = readClassUint16(classFile);
	codeAttr->exception_table = calloc(codeAttr->exception_table_length, sizeof(ExceptionTableEntry));
	for (uint16_t i = 0; i < codeAttr->exception_table_length; i++)
	{
		codeAttr->exception_table[i].start_pc = readClassUint16(classFile);
		codeAttr->exception_table[i].end_pc = readClassUint16(classFile);
		codeAttr->exception_table[i].handler_pc = readClassUint16(classFile);
		codeAttr->exception_table[i].catch_type = readClassUint16(classFile);
	}
	codeAttr->attributes_count = readClassUint16(classFile);
	codeAttr->attributes = NULL;
	if (codeAttr->attributes_count != 0)
	{
		codeAttr->attributes = calloc(codeAttr->attributes_count, sizeof(AttributeInfo));
		for (uint16_t i = 0; i < codeAttr->attributes_count; i++)
		{
			readAttributeInfo(classFile, codeAttr->attributes + i, 1);
		}
	}
		
	return codeAttr;
}

LineNumberTableAttribute * getCodeAttrLineNumberTableAttr(CodeAttribute * codeAttr, ClassFile* classFile)
{
	uint16_t attrCount = codeAttr->attributes_count;
	for (uint16_t i = 0; i < attrCount; i++)
	{
		const char * attrName = getClassUtf8(classFile, codeAttr->attributes[i].attributeNameIndex);
		if (strcmp(attrName, "LineNumberTable") == 0)
		{
			return codeAttr->attributes[i].info;
		}
	}
	return NULL;
}

SourceFileAttribute * readSourceFileAttributeInfo(ClassFile * classFile)
{
	SourceFileAttribute * sourceFileAttr = calloc(1, sizeof(SourceFileAttribute));
	sourceFileAttr->sourcefile_index = readClassUint16(classFile);
	return sourceFileAttr;
}

LineNumberTableAttribute * readLineNumberTableAttributeInfo(ClassFile * classFile)
{
	LineNumberTableAttribute * lineNumberTableAttr = calloc(1, sizeof(LineNumberTableAttribute));

	lineNumberTableAttr->line_number_table_length = readClassUint16(classFile);
	lineNumberTableAttr->line_number_table = NULL;
	if (lineNumberTableAttr->line_number_table_length != 0)
	{
		lineNumberTableAttr->line_number_table = calloc(lineNumberTableAttr->line_number_table_length, sizeof(LineNumberTableEntry));
		for (uint16_t i = 0; i < lineNumberTableAttr->line_number_table_length; i++)
		{
			lineNumberTableAttr->line_number_table[i].startPc = readClassUint16(classFile);
			lineNumberTableAttr->line_number_table[i].lineNumber = readClassUint16(classFile);
		}
	}
	
	return lineNumberTableAttr;
}

int32_t getLineAttrLineNumber(LineNumberTableAttribute * self, int32_t pc)
{
	for (int32_t i = self->line_number_table_length - 1; i >= 0; i--)
	{
		LineNumberTableEntry * entry = &self->line_number_table[i];
		if (pc >= entry->startPc)
			return entry->lineNumber;
	}

	return -1;
}

LocalVariableTableAttribute * readLocalVariableTableAttributeInfo(ClassFile * classFile)
{
	LocalVariableTableAttribute * localVariableTableAttributeAttr = calloc(1, sizeof(LocalVariableTableAttribute));

	localVariableTableAttributeAttr->local_variable_table_length = readClassUint16(classFile);
	localVariableTableAttributeAttr->local_variable_table = NULL;

	if (localVariableTableAttributeAttr->local_variable_table_length != 0)
	{
		localVariableTableAttributeAttr->local_variable_table = calloc(localVariableTableAttributeAttr->local_variable_table_length, sizeof(LocalVariableTableEntry));
		for (uint16_t i = 0; i < localVariableTableAttributeAttr->local_variable_table_length; i++)
		{
			localVariableTableAttributeAttr->local_variable_table[i].startPc = readClassUint16(classFile);
			localVariableTableAttributeAttr->local_variable_table[i].length = readClassUint16(classFile);
			localVariableTableAttributeAttr->local_variable_table[i].nameIndex = readClassUint16(classFile);
			localVariableTableAttributeAttr->local_variable_table[i].descriptorIndex = readClassUint16(classFile);
			localVariableTableAttributeAttr->local_variable_table[i].index = readClassUint16(classFile);
		}
	}

	return localVariableTableAttributeAttr;
}

SignatureAttribute *readSignatureAttributeInfo(ClassFile* classFile)
{
	SignatureAttribute * signatureAttr = calloc(1, sizeof(SignatureAttribute));

	signatureAttr->signature_index = readClassUint16(classFile);

	return signatureAttr;
}

InnerClassesAttribute  *readInnerClassAttributeInfo(ClassFile* classFile)
{
	InnerClassesAttribute * innerClassesAttr = calloc(1, sizeof(InnerClassesAttribute));
	innerClassesAttr->number_of_classes = readClassUint16(classFile);
	InnerClassesAttributeItem * classItem = calloc(innerClassesAttr->number_of_classes, sizeof(InnerClassesAttributeItem));
	for (uint16_t i = 0; i < innerClassesAttr->number_of_classes; i++)
	{
		classItem[i].inner_class_info_index = readClassUint8(classFile);
		classItem[i].outer_class_info_index = readClassUint16(classFile);
		classItem[i].inner_name_index = readClassUint16(classFile);
		classItem[i].inner_class_access_flags = readClassUint16(classFile);
	}

	return innerClassesAttr;
}

SyntheticAttribute * readSyntheticAttributeInfo(ClassFile * classFile)
{
	return NULL;
}

DeprecatedAttribute * readDeprecatedAttributeInfo(ClassFile * classFile)
{
	return calloc(1, sizeof(DeprecatedAttribute));
}

ExceptionsAttribute * readExceptionsAttributeInfo(ClassFile * classFile)
{
	ExceptionsAttribute * exceptionAttr =  calloc(1, sizeof(ExceptionsAttribute));
	exceptionAttr->number_of_exceptions = readClassUint16(classFile);
	exceptionAttr->exception_index_table = calloc(exceptionAttr->number_of_exceptions, sizeof(uint16_t));
	for (uint16_t i = 0; i < exceptionAttr->number_of_exceptions; i++)
	{
		exceptionAttr->exception_index_table[i] = readClassUint16(classFile);
	}
	return exceptionAttr;
}

ConstantValueAttribute * readConstantValueAttributeInfo(ClassFile * classFile)
{
	ConstantValueAttribute * constantValueAttr = calloc(1, sizeof(ConstantValueAttribute));

	constantValueAttr->constantvalue_index = readClassUint16(classFile);

	return constantValueAttr;
}

UnparsedAttribute * readUnparsedAttributeInfo(ClassFile * classFile, uint32_t attrLen )
{
	UnparsedAttribute * unparsedAttr = calloc(1, sizeof(UnparsedAttribute));

	unparsedAttr->bytes_length = attrLen;

	if (attrLen == 0)
		return NULL;
	unparsedAttr->bytes = calloc(attrLen, sizeof(uint8_t));
	for (uint32_t i = 0; i < attrLen; i++)
		unparsedAttr->bytes[i] = readClassUint8(classFile);

	return unparsedAttr;
}

static void * newAttributeInfo(const char * attrName, uint32_t attrLen, ClassFile * classFile)
{
	if (attrName == NULL)
		return NULL;
	if (strcmp("Code", attrName) == 0){
		return readCodeAttributeInfo(classFile);
	}else if (strcmp("ConstantValue", attrName) == 0){
		return readConstantValueAttributeInfo(classFile);
	}
	else if (strcmp("Deprecated", attrName) == 0){
		return readDeprecatedAttributeInfo(classFile);
	}
	else if (strcmp("Exceptions", attrName) == 0){
		return readExceptionsAttributeInfo(classFile);
	}
	else if (strcmp("LineNumberTable", attrName) == 0){
		return readLineNumberTableAttributeInfo(classFile);
	}
	else if (strcmp("LocalVariableTable", attrName) == 0){
		return readLocalVariableTableAttributeInfo(classFile);
	}
	else if (strcmp("SourceFile", attrName) == 0){
		return readSourceFileAttributeInfo(classFile);
	}else if (strcmp("Synthetic", attrName) == 0){

	}else if (strcmp("InnerClasses", attrName) == 0){
		return readInnerClassAttributeInfo(classFile);
	}else if (strcmp("Signature", attrName) == 0){
		return readSignatureAttributeInfo(classFile);
	}else{
		return readUnparsedAttributeInfo(classFile, attrLen);
	}
	
	return NULL;
}

void readAttributeInfo(ClassFile * classFile, AttributeInfo * attribute, uint16_t count)
{
	for (uint16_t i = 0; i < count; i++)
	{
		uint16_t attrNameIndex = readClassUint16(classFile);
		const char * attrName = getClassUtf8(classFile, attrNameIndex);
		uint32_t attrLen = readClassUint32(classFile);

		attribute[i].info = newAttributeInfo(attrName, attrLen, classFile);
		attribute[i].attributeLength = attrLen;
		attribute[i].attributeNameIndex = attrNameIndex;
	}
}

void readClassFields(ClassFile * classFile)
{
	classFile->fieldsCount = readClassUint16(classFile);
	classFile->fields = NULL;
	if (classFile->fieldsCount == 0)
		return;
	classFile->fields = calloc(classFile->fieldsCount, sizeof(FieldInfo));
	for (uint16_t i = 0; i < classFile->fieldsCount; i++)
	{
		(classFile->fields + i)->access_flags = readClassUint16(classFile);
		(classFile->fields + i)->name_index = readClassUint16(classFile);
		(classFile->fields + i)->descriptor_index = readClassUint16(classFile);
		(classFile->fields + i)->attributes_count = readClassUint16(classFile);
		(classFile->fields + i)->attributes = calloc((classFile->fields + i)->attributes_count, sizeof(AttributeInfo));
		readAttributeInfo(classFile, (classFile->fields + i)->attributes, (classFile->fields + i)->attributes_count);
	}
}

void readClassMethods(ClassFile * classFile)
{
	classFile->methodsCount = readClassUint16(classFile);
	classFile->methods = NULL;
	if (classFile->methodsCount == 0)
		return;

	classFile->methods = calloc(classFile->methodsCount, sizeof(MethodInfo));
	for (uint16_t i = 0; i < classFile->methodsCount; i++)
	{
		(classFile->methods + i)->access_flags = readClassUint16(classFile);
		(classFile->methods + i)->name_index = readClassUint16(classFile);
		(classFile->methods + i)->descriptor_index = readClassUint16(classFile);
		(classFile->methods + i)->attributes_count = readClassUint16(classFile);
		(classFile->methods + i)->attributes = calloc((classFile->methods + i)->attributes_count, sizeof(AttributeInfo));
		readAttributeInfo(classFile, (classFile->methods + i)->attributes, (classFile->methods + i)->attributes_count);
	}
}

void readClassAttributes(ClassFile * classFile)
{
	classFile->attributes_count = readClassUint16(classFile);
	classFile->attributes = NULL;
	if (classFile->attributes_count != 0)
	{
		classFile->attributes = calloc(classFile->attributes_count, sizeof(AttributeInfo));
		for (uint16_t i = 0; i < classFile->attributes_count; i++)
			readAttributeInfo(classFile, classFile->attributes + i, 1);
	}	
}