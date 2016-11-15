#include "class.h"
#include "class_attribute_info.h"
#include "method.h"
#include "field.h"
#include "constant_pool.h"
#include "../utils.h"

#pragma warning(disable:4996)

static void newClassName(Class * c, ClassFile * classFile)
{
	uint16_t classNameLen = strlen(getClassName(classFile));
	c->name = calloc(classNameLen + 1, sizeof(char));
	strcpy(c->name, getClassName(classFile));
}

static void newSuperClassName(Class * c, ClassFile * classFile)
{
	uint16_t superClassNameLen = 0;
	if (classFile->superClass == 0)
		return;
	superClassNameLen = strlen(getSuperClassName(classFile));
	c->superClassName = calloc(superClassNameLen + 1, sizeof(char));
	strcpy(c->superClassName, getSuperClassName(classFile));
}

static void newInterfacesName(Class * c, ClassFile * classFile)
{
	c->interfacesCount = classFile->interfaceCount;
	if (c->interfacesCount == 0)
		return;
	c->interfaceNames = calloc(c->interfaceNamesCount, sizeof(char *));
	for (uint16_t i = 0; i < c->interfacesCount; i++)
	{
		uint16_t classNameLen = strlen(getInterfaceName(classFile,i));
		c->interfaceNames[i] = calloc(classNameLen+1,sizeof(char));
		strcpy(c->interfaceNames[i], getInterfaceName(classFile, i));
	}
}

static void newConstantPool(Class * c, ClassFile * classFile)
{
	uint16_t constantPoolCount = classFile->constanPoolCount;
	void * destItem = NULL;
	void * srcItemInfo = NULL;
	if (constantPoolCount == 0)
		return;
	c->constantPool.class = c;
	c->constantPool.constantPoolItem = calloc(constantPoolCount, sizeof(ConstantPoolItem));
	for (uint16_t i = 1; i < constantPoolCount; i++)
	{
		uint8_t tag = ((ConstantClassInfo *)((classFile->constantPoolItem + i)->itemInfo))->tag;
		switch (tag)
		{
		case CONSTATNT_CLASS:
			//destItem = (void *)calloc(1, sizeof(ClassConstantClass));

			//c->constantPool.constantPoolItem[i].itemInfo = (void *)calloc(1, sizeof(ConstantClassInfo));
			//memcpy(c->constantPool.constantPoolItem[i].itemInfo, (classFile->constantPoolItem + i)->itemInfo, sizeof(ConstantClassInfo));
			break;
		case CONSTATNT_FIELDREF:
			break;
		case CONSTATNT_METHODREF:
			break;
		case CONSTATNT_INTERFACE_METHODREF:
			break;
		case CONSTATNT_STRING:	
			break;
		case CONSTATNT_INTEGER:		
			destItem = (void *)calloc(1, sizeof(ClassConstantInteger));
			srcItemInfo = (classFile->constantPoolItem + i)->itemInfo;
			c->constantPool.constantPoolItem[i].itemInfo = destItem;
			((ClassConstantInteger*)destItem)->tag = tag;
			((ClassConstantInteger*)destItem)->val = ((ConstantIntegerInfo*)srcItemInfo)->bytes;
			break;
		case CONSTATNT_FLOAT:
			destItem = (void *)calloc(1, sizeof(ClassConstantFloat));
			srcItemInfo = (classFile->constantPoolItem + i)->itemInfo;
			c->constantPool.constantPoolItem[i].itemInfo = destItem;
			((ClassConstantFloat*)destItem)->tag = tag;
			((ClassConstantFloat*)destItem)->val = intToFloat(((ConstantFloatInfo*)srcItemInfo)->bytes);
			break;
		case CONSTATNT_LONG:
			i++;
			break;
		case CONSTATNT_DOUBLE:
			i++;
			break;
		case CONSTATNT_NAME_AND_TYPE:
			break;
		case CONSTATNT_UTF8:
			break;
		case CONSTATNT_METHOD_HANDLE:
			break;
		case CONSTATNT_METHOD_TYPE:
			break;
		case CONSTATNT_INVOKE_DYNAMIC:
			break;
		default:
			break;
		}
	}
}

static void freeConstantPool(Class * c)
{

}


Class * newClass(ClassFile * classFile)
{
	Class * c = calloc(1, sizeof(Class));
	c->accessFlags = classFile->accessFlags;
	newClassName(c, classFile);
	newSuperClassName(c, classFile);
	newInterfacesName(c, classFile);
	newConstantPool(c, classFile);
	newFields(c, classFile);
	newMethods(c, classFile);
	return c;

}

void freeClass(Class * c)
{
	if (c == NULL)
		return;
	free(c->name);
	free(c->superClassName);
}


Method * getClassStaticMethod(Class * c, const char * name, const char * descriptor)
{
	for (uint16_t i = 0; i < c->methodsCount; i++)
	{
		if (isMethodStatic(c->methods + i) &&
			strcmp(c->methods[i].classMember.name, name) == 0 &&
			strcmp(c->methods[i].classMember.descriptor, descriptor) == 0)
				return (c->methods + i);		
	}
	return NULL;
}

Method * getClassMainMethod(Class * c)
{
	return getClassStaticMethod(c, "main", "([Ljava/lang/String;)V");
}

bool isClassInterface(Class * c)
{
	return false;
}

bool isClassAbstract(Class * c)
{
	return false;
}