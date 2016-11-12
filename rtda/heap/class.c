#include "class.h"
#include "class_attribute_info.h"

#pragma warning(disable:4996)

static void newClassName(Class * c, ClassFile * classFile)
{
	uint16_t classNameLen = strlen(getClassName(classFile));
	c->name = calloc(classNameLen + 1, sizeof(char));
	strcpy(c->name, getClassName(classFile));
}

static void newSuperClassName(Class * c, ClassFile * classFile)
{
	uint16_t superClassNameLen = strlen(getClassName(classFile));
	c->superClassName = calloc(superClassNameLen + 1, sizeof(char));
	strcpy(c->superClassName, getClassName(classFile));
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
	if (constantPoolCount == 0)
		return;
	c->constantPoolItem = calloc(constantPoolCount, sizeof(ConstantPoolItem));
	for (uint16_t i = 0; i < constantPoolCount; i++)
	{
		uint8_t tag = ((ConstantClassInfo *)((classFile->constantPoolItem + i)->itemInfo))->tag;
		switch (tag)
		{
		case CONSTATNT_CLASS:
			c->constantPoolItem[i].itemInfo = (void *) calloc(1, sizeof(ConstantClassInfo));
			memcpy(c->constantPoolItem[i].itemInfo, (classFile->constantPoolItem + i)->itemInfo, sizeof(ConstantClassInfo));
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
			break;
		case CONSTATNT_FLOAT:
			break;
		case CONSTATNT_LONG:
			break;
		case CONSTATNT_DOUBLE:
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



static void newFields(Class * c, ClassFile * classFile)
{
	c->fieldsCount = classFile->fieldsCount;
	if (c->fieldsCount == 0)
		return;
	c->fields = calloc(c->fieldsCount, sizeof(FieldInfo));
	for (uint16_t i = 0; i < c->fieldsCount; i++)
	{
		(c->fields + i)->access_flags = (classFile->fields + i)->access_flags;
		(c->fields + i)->name_index = (classFile->fields + i)->name_index;
		(c->fields + i)->attributes_count = (classFile->fields + i)->attributes_count;
		copyAttributeInfo(classFile, (c->fields+i)->attributes, (classFile->fields + i)->attributes, (c->fields + i)->attributes_count);
	}
}

static void freeFields(Class * c, ClassFile * classFile)
{

}


static void newMethods(Class * c, ClassFile * classFile)
{

}

static void freeMethods(Class * c, ClassFile * classFile)
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