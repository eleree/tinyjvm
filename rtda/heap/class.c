#include "class.h"
#include "class_attribute_info.h"
#include "method.h"
#include "field.h"
#include "constant_pool.h"
#include "cp_classref.h"
#include "cp_methodref.h"
#include "cp_fieldref.h"
#include "../utils.h"
#include "../../strings/strings.h"

#pragma warning(disable:4996)

static void newClassName(Class * c, ClassFile * classFile)
{
	uint16_t packageNameLen = 0;
	uint16_t classNameIndex = 0;
	uint16_t classNameLen = strlen(getClassName(classFile));

	c->name = calloc(classNameLen + 1, sizeof(char));
	strcpy(c->name, getClassName(classFile));
	
	classNameIndex = stringLastIndex(c->name, "/");
	if (classNameIndex == -1)
	{
		c->packageName = NULL;
		return;
	}
	
	packageNameLen = classNameIndex;
	c->packageName = calloc(packageNameLen+1, sizeof(char));
	strncpy(c->packageName, c->name, classNameIndex);
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
	c->constantPool.constantPoolCount = constantPoolCount;
	c->constantPool.constantPoolItem = calloc(constantPoolCount, sizeof(ConstantPoolItem));
	for (uint16_t i = 1; i < constantPoolCount; i++)
	{
		uint8_t tag = ((ConstantClassInfo *)((classFile->constantPoolItem + i)->itemInfo))->tag;
		switch (tag)
		{
		case CONSTATNT_CLASS:
			destItem = (void *)calloc(1, sizeof(ClassConstantClassRef));
			srcItemInfo = (classFile->constantPoolItem + i)->itemInfo;
			c->constantPool.constantPoolItem[i].itemInfo = destItem;
			((ClassConstantClassRef*)destItem)->tag = tag;
			((ClassConstantClassRef*)destItem)->classRef = newClassRef(classFile, &c->constantPool, srcItemInfo);
			break;
		case CONSTATNT_FIELDREF:
			destItem = (void *)calloc(1, sizeof(ClassConstantFieldRef));
			srcItemInfo = (classFile->constantPoolItem + i)->itemInfo;
			c->constantPool.constantPoolItem[i].itemInfo = destItem;
			((ClassConstantFieldRef*)destItem)->tag = tag;
			((ClassConstantFieldRef*)destItem)->fieldRef = newFieldRef(classFile, &c->constantPool, srcItemInfo);
			break;
		case CONSTATNT_METHODREF:
			destItem = (void *)calloc(1, sizeof(ClassConstantMethodRef));
			srcItemInfo = (classFile->constantPoolItem + i)->itemInfo;
			c->constantPool.constantPoolItem[i].itemInfo = destItem;
			((ClassConstantMethodRef*)destItem)->tag = tag;
			((ClassConstantMethodRef*)destItem)->methodRef = newMethodRef(classFile, &c->constantPool, srcItemInfo);
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
			destItem = (void *)calloc(1, sizeof(ClassConstantLong));
			srcItemInfo = (classFile->constantPoolItem + i)->itemInfo;
			c->constantPool.constantPoolItem[i].itemInfo = destItem;
			((ClassConstantLong*)destItem)->tag = tag;
			((ClassConstantLong*)destItem)->val = intToLong(((ConstantLongInfo*)srcItemInfo)->high_bytes, \
															((ConstantLongInfo*)srcItemInfo)->low_bytes);
			i++;
			break;
		case CONSTATNT_DOUBLE:
			destItem = (void *)calloc(1, sizeof(ClassConstantDouble));
			srcItemInfo = (classFile->constantPoolItem + i)->itemInfo;
			c->constantPool.constantPoolItem[i].itemInfo = destItem;
			((ClassConstantDouble*)destItem)->tag = tag;
			((ClassConstantDouble*)destItem)->val = intToDouble(((ConstantDoubleInfo*)srcItemInfo)->high_bytes, \
				((ConstantDoubleInfo*)srcItemInfo)->low_bytes);
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

Method * getClassClinitMethod(Class * c)
{
	return getClassStaticMethod(c, "<clinit>", "()V");
}

bool isClassInterface(Class * c)
{
	return false;
}

bool isClassAbstract(Class * c)
{
	return false;
}

// self extends iface
bool isClassSubInterfaceOf(Class * thisClass, Class * iface)
{
	for (uint16_t i = 0; i < thisClass->interfacesCount; i++)
	{
		Class * superInterface = thisClass->interfaces[i];
		if (superInterface == iface || isClassSubInterfaceOf(superInterface, iface))
		{
			return true;
		}
	}
	return false;
}

// self implements iface
bool isClassImplements(Class * thisClass, Class * iface)
{
	Class * c = thisClass;

	while (c != NULL)
	{
		for (uint16_t i = 0; i < c->interfacesCount; i++)
		{
			Class * thisIface = c->interfaces[i];
			if (iface == iface || isClassSubInterfaceOf(thisIface, iface))
				return true;
		}
		c = c->superClass;
	}

	return false;
}

bool isClassSubClassOf(Class * thisClass, Class * otherClass)
{
	Class * c = thisClass->superClass;
	while (c != NULL)
	{
		if (c == otherClass)
			return true;;
		
		c = c->superClass;
	}

	return false;
}

bool isClassAssignableFrom(Class * thisClass, Class * otherClass)
{
	Class * s = otherClass;
	Class * t = thisClass;
	if (s == t)
		return true;
	if (!isClassInterface(t))
		return isClassSubClassOf(s, t);
	else
		return isClassImplements(s, t);
}

void startClassInit(Class * c)
{
	c->initStarted = true;
}