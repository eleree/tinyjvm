#include "method.h"


void copyMethodInfo(Method * method, MethodInfo * methodInfo, ClassFile * classFile)
{
	method->classMember.accessFlags = methodInfo->access_flags;
	method->classMember.descriptor = _strdup(getClassUtf8(classFile, methodInfo->descriptor_index));
	method->classMember.name = _strdup(getClassUtf8(classFile, methodInfo->name_index));
}

static void copyAttributes(Method * method, MethodInfo * methodInfo, ClassFile * classFile)
{
	uint16_t attrCount = methodInfo->attributes_count;
	for (uint16_t i = 0; i < attrCount; i++)
	{
		const char * attrName = getClassUtf8(classFile, methodInfo->attributes[i].attributeNameIndex);
		if (strcmp(attrName, "Code") == 0){
			CodeAttribute * codeAttr = methodInfo->attributes[i].info;
			method->maxLocals = codeAttr->max_locals;
			method->maxStack = codeAttr->max_stack;
			method->codeLen = codeAttr->code_length;
			method->code = calloc(method->codeLen, sizeof(uint8_t));
			memcpy(method->code, codeAttr->code, method->codeLen);
			break;
		}
	}
}

Method * newMethods(struct Class * c, ClassFile * classFile)
{
	c->methodsCount = classFile->methodsCount;
	c->methods = NULL;
	if (c->methodsCount == 0)
		return NULL;

	c->methods = calloc(classFile->methodsCount, sizeof(Method));
	for (uint16_t i = 0; i < c->methodsCount; i++)
	{
		c->methods[i].classMember.classPtr = c;
		copyMethodInfo(&c->methods[i], &classFile->methods[i], classFile);
		copyAttributes(&c->methods[i], &classFile->methods[i], classFile);
	}
 
	return NULL;
}

void freeMethods(Method * method, uint16_t methodCount)
{
	if (methodCount == 0)
		return;

	for (uint16_t i = 0; i < methodCount; i++)
	{
		free(method[i].classMember.name);
		free(method[i].classMember.descriptor);
		if (method[i].codeLen > 0)
			free(method[i].code);
	}

	free(method);
}