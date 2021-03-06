#include "method.h"
#include "exception_table.h"

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
			method->lineNumberTable = getCodeAttrLineNumberTableAttr(codeAttr, classFile);// can't be free directly
			method->exceptionTable = newExceptionTable(codeAttr, method->classMember.attachClass->constantPool.constantPoolItem);
			break;
		}
		method->classMember.annotationData = getClassFileUnparsedAttributeData(classFile, "RuntimeVisibleAnnotations", &method->classMember.annotationDataLen);
		method->parameterAnnotationData = getClassFileUnparsedAttributeData(classFile, "RuntimeVisibleParameterAnnotationsAttribute", &method->parameterAnnotationDataLen);
		method->annotationDefaultData = getClassFileUnparsedAttributeData(classFile, "AnnotationDefault", &method->annotationDefaultDataLen);
	}
}

void calcArgSlotCount(Method * self) {
	MethodDescriptor * parsedDescriptor = parseMethodDescriptor(self->classMember.descriptor);
	ParameterTypesList * parameterTypesList = parsedDescriptor->parameterTypesList;
	for (uint16_t i = 0; i < parsedDescriptor->parameterTypesCount; i++)
	{		
		char * paramType = parameterTypesList->parameterTypes;

		self->argSlotCount++;

		if (strcmp(paramType, "J") == 0 ||
			strcmp(paramType, "D") == 0)
			self->argSlotCount++;

		parameterTypesList = parameterTypesList->next;
	}

	if (!isMethodStatic(self))
	{
		self->argSlotCount++;
	}
}

void injectCodeAttribute(Method * method, const char * returnType)
{
	method->maxStack = 4;//todo
	method->maxLocals = method->argSlotCount;
	switch (returnType[0])
	{
	case 'V':
		method->codeLen = 2;
		method->code = calloc(2, sizeof(uint8_t));
		method->code[0] = 0xfe;
		method->code[1] = 0xb1;
		break;
	case 'L':
	case '[':
		method->codeLen = 2;
		method->code = calloc(2, sizeof(uint8_t));
		method->code[0] = 0xfe;
		method->code[1] = 0xb0;
		break;
	case 'D':
		method->codeLen = 2;
		method->code = calloc(2, sizeof(uint8_t));
		method->code[0] = 0xfe;
		method->code[1] = 0xaf;
		break;
	case 'F':
		method->codeLen = 2;
		method->code = calloc(2, sizeof(uint8_t));
		method->code[0] = 0xfe;
		method->code[1] = 0xae;
		break;
	case 'J':
		method->codeLen = 2;
		method->code = calloc(2, sizeof(uint8_t));
		method->code[0] = 0xfe;
		method->code[1] = 0xad;
		break;
	default:
		method->codeLen = 2;
		method->code = calloc(2, sizeof(uint8_t));
		method->code[0] = 0xfe;
		method->code[1] = 0xac;
		break;
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
		c->methods[i].classMember.attachClass = c;
		copyMethodInfo(&c->methods[i], &classFile->methods[i], classFile);
		copyAttributes(&c->methods[i], &classFile->methods[i], classFile);
		MethodDescriptor * md = parseMethodDescriptor(c->methods[i].classMember.descriptor);
		c->methods[i].parsedDescriptor = md;
		calcArgSlotCount(&c->methods[i]);
		if (isMethodNative(&c->methods[i]))
		{
			injectCodeAttribute(&c->methods[i], md->returnType);
		}
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

bool isMethodSynchronized(Method * method)
{
	return	0 != (method->classMember.accessFlags & ACC_SYNCHRONIZED);
}

bool isMethodBridge(Method * method)
{
	return	0 != (method->classMember.accessFlags & ACC_BRIDGE);
}

bool isMethodVarargs(Method * method)
{
	return	0 != (method->classMember.accessFlags & ACC_VARARGS);
}

bool isMethodNative(Method * method)
{
	return	0 != (method->classMember.accessFlags & ACC_NATIVE);
}

bool isMethodAbstract(Method * method)
{
	return	0 != (method->classMember.accessFlags & ACC_ABSTRACT);
}

bool isMethodStrict(Method * method)
{
	return	0 != (method->classMember.accessFlags & ACC_STRICT);
}

bool isMethodPublic(Method * method)
{
	if (method == NULL)
		return false;

	return	0 != (method->classMember.accessFlags & ACC_PUBLIC);
}

bool isMethodPrivate(Method * method)
{
	if (method == NULL)
		return false;

	return	0 != (method->classMember.accessFlags & ACC_PRIVATE);
}

bool isMethodProtected(Method * method)
{
	if (method == NULL)
		return false;

	return	0 != (method->classMember.accessFlags & ACC_PROTECTED);
}

bool isMethodStatic(Method * method)
{
	if (method == NULL)
		return false;

	return	0 != (method->classMember.accessFlags & ACC_STATIC);
}

bool isMethodFinal(Method * method)
{
	if (method == NULL)
		return false;

	return	0 != (method->classMember.accessFlags & ACC_FINAL);
}

bool isMethodSynthetic(Method * method)
{
	if (method == NULL)
		return false;

	return	0 != (method->classMember.accessFlags & ACC_SYNTHETIC);
}


bool isMethodAccessibleTo(Method * method, Class * d)
{
	Class * c = method->classMember.attachClass;

	if (isMethodPublic(method))
		return true;

	if (isMethodProtected(method))
	{
		return	c == d ||
			strcmp(c->packageName, d->packageName) == 0 ||
			isSubClassOf(d, c);
	}

	if (isMethodPublic(method))
		return true;

	if (!isMethodPrivate(method))
	{
		return strcmp(c->packageName, d->packageName) == 0;
	}

	return d == c;
}

int32_t findMethodExceptionHander(Method * self, Class * exClass, int32_t pc)
{
	ExceptionHandler * handler = findExceptionHandler(self->exceptionTable, exClass, pc);
	if (handler != NULL)
		return handler->handlerPc;

	return -1;
}

int32_t getMethodLineNumber(Method * self, int32_t pc)
{
	if (isMethodNative(self))
		return -2;

	if (self->lineNumberTable == NULL)
		return -1;
	return getLineAttrLineNumber(self->lineNumberTable, pc);
}

bool isMethodConstructor(Method * self)
{
	return !isMethodStatic(self) && strcmp(self->classMember.name, "<init>") == 0;	
}

Class* * methodParameterTypes(Method * self)
{
	ParameterTypesList * paramTypes = NULL;
	if (self->argSlotCount == 0)
		return NULL;
	
	paramTypes = self->parsedDescriptor->parameterTypesList;

	Class* *  paramClasses = calloc(self->parsedDescriptor->parameterTypesCount, sizeof(Class*));
	uint32_t i = 0;
	while (paramTypes != NULL)
	{
		char * paramClassName = toClassName(paramTypes->parameterTypes);
		paramClasses[i++] = loadClass(self->classMember.attachClass->classLoader, paramClassName);
		paramTypes = paramTypes->next;
	}
	return paramClasses;
}

Class* * methodExceptionTypes(Method * self)
{
	uint16_t * exIndexTable = NULL;
	if (self->exceptions == NULL)
		return NULL;
	exIndexTable = self->exceptions->exception_index_table;
	Class* * exClasses = calloc(self->exceptions->number_of_exceptions, sizeof(Class *));
	ConstantPoolItem * cp = self->classMember.attachClass->constantPool.constantPoolItem;

	for (uint16_t i = 0; i < self->exceptions->number_of_exceptions; i++)
	{
		uint16_t exIndex = exIndexTable[i];
		ClassRef * ref = getClassConstantPoolClassRef(cp, exIndex);
		exClasses[i] = resolveClass(&ref->symRef);
	}

	return exClasses;
}
