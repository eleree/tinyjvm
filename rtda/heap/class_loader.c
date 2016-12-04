#include "class_loader.h"
#include "../../classfile/classfile.h"
#include "../../classpath/classpath.h"
#include "../../rtda/rtda.h"

#include "class.h"
#include "slot.h"
#include "constant_pool.h"

#pragma warning(disable:4996)

void loadBasicClasses(ClassLoader * classLoader)
{
	Class * jlClassClass = loadClass(classLoader, "java/lang/Class");

	ClassList * classList = classLoader->classList;
	while (classList != NULL)
	{
		if (classList->classPtr->jClass == NULL)
		{
			classList->classPtr->jClass = newObject(jlClassClass);
			classList->classPtr->jClass->extra = classList->classPtr;
			classList->classPtr->jClass->extraType = 'c';
			classList->classPtr->jClass->extraCount = 1;
		}
		classList = classList->next;
	}
}

void addClassList(ClassLoader * classLoader, Class * newClass);

void loadPrimitiveClass(ClassLoader * classLoader, const char * className)
{
	Class * c = calloc(1, sizeof(Class));
	c->accessFlags = ACC_PUBLIC;
	c->name = strdup(className);
	c->classLoader = classLoader;
	c->initStarted = true;
	c->jClass = newObject(loadClass(classLoader,"java/lang/Class"));
	c->jClass->extra = c;
	c->jClass->extraType = 'c';
	c->jClass->extraCount = 1;
	addClassList(classLoader, c);
}

void loadPrimitiveClasses(ClassLoader * classLoader)
{
	loadPrimitiveClass(classLoader, "void");
	loadPrimitiveClass(classLoader, "boolean");
	loadPrimitiveClass(classLoader, "byte");
	loadPrimitiveClass(classLoader, "short");
	loadPrimitiveClass(classLoader, "int");
	loadPrimitiveClass(classLoader, "long");
	loadPrimitiveClass(classLoader, "char");
	loadPrimitiveClass(classLoader, "float");
	loadPrimitiveClass(classLoader, "double");
}

ClassLoader * newClassLoader(void)
{
	ClassLoader * newClassLoader = calloc(1, sizeof(ClassLoader));
	loadBasicClasses(newClassLoader);
	loadPrimitiveClasses(newClassLoader);
	return newClassLoader;
}

void addClassList(ClassLoader * classLoader, Class * newClass)
{
	ClassList * classList = classLoader->classList;
	ClassList * preClassList = NULL;
	while (classList != NULL)
	{
		if (strcmp(classList->className, newClass->name) == 0)
			return;
		
		preClassList = classList;
		classList = classList->next;
	}

	classList = calloc(1, sizeof(ClassList));
	classList->className = _strdup(newClass->name);
	classList->classPtr = newClass;
	classList->next = NULL;

	if (preClassList == NULL)
		classLoader->classList = classList;

	if (preClassList != NULL)
		preClassList->next = classList;

	return;
}

void resolveSuperClass(ClassLoader * classLoader, Class * subClass)
{
	if (strcmp(subClass->name, "java/lang/Object") != 0)
		subClass->superClass = loadClass(classLoader, subClass->superClassName);
}

void resolveInterfaces(ClassLoader * classLoader, Class * subClass)
{
	if (subClass->interfacesCount == 0)
		return;
	if (subClass->interfaceNamesCount != subClass->interfacesCount)
		printf("Interface Name Count != Interface Count, maybe this is a BUG.\n");

	subClass->interfaces = calloc(subClass->interfacesCount, sizeof(Class *));
	for (uint16_t i = 0; i < subClass->interfacesCount; i++)
	{
		subClass->interfaces[i] = loadClass(classLoader, subClass->interfaceNames[i]);
	}
}

void calcInstanceFieldSlotIds(Class * class)
{
	uint16_t slotId = 0;
	if (class->superClass != NULL)
	{
		slotId = class->superClass->instanceSlotCount;
	}
	for (uint16_t i = 0; i < class->fieldsCount; i++)
	{
		if (!isFieldStatic(&class->fields[i]))
		{
			class->fields[i].slotId = slotId;
			slotId++;
			if (isFieldLongOrDouble(&class->fields[i]))
				slotId++;
		}
	}
	class->instanceSlotCount = slotId;
}

void calcStaticFieldSlotIds(Class * class)
{
	uint16_t slotId = 0;
	for (uint16_t i = 0; i < class->fieldsCount; i++)
	{
		if (isFieldStatic(&class->fields[i]))
		{
			class->fields[i].slotId = slotId;
			slotId++;
			if (isFieldLongOrDouble(&class->fields[i]))
				slotId++;
		}
	}

	class->staticSlotCount = slotId;
}

void initStaticFinalVar(Class * c, Field * field) 
{
	Slot * staticVars = c->staticVars;
	ConstantPoolItem * constantPool = c->constantPool.constantPoolItem;
	uint16_t cpIndex = field->constValueIndex;
	uint16_t slotId = field->slotId;
	int32_t int32Val = 0;
	int64_t int64Val = 0;
	float floatVal = 0;
	double doubleVal = 0;

	if (cpIndex > 0)
	{
		switch (field->classMember.descriptor[0])
		{
		case 'Z':
		case 'B':
		case 'C':
		case 'S':
		case 'I':
			int32Val = getClassConstantPoolInt(constantPool, cpIndex);
			setSlotInt(staticVars, slotId, int32Val);
			break;
		case 'J':
			int64Val = getClassConstantPoolLong(constantPool, cpIndex);
			setSlotLong(staticVars, slotId, int64Val);
		case 'F':
			floatVal = getClassConstantPoolFloat(constantPool, cpIndex);
			setSlotFloat(staticVars, slotId, floatVal);
		case 'D':
			doubleVal = getClassConstantPoolDouble(constantPool, cpIndex);
			setSlotDouble(staticVars, slotId, doubleVal);
			break;
		}
		if (strcmp(field->classMember.descriptor, "Ljava/lang/String;") == 0)
		{
			String * s = getClassConstantPoolStringRef(constantPool, cpIndex);
			Object * jStr = jString(c->classLoader, s);
			setSlotRef(staticVars, slotId, jStr);
		}
	}
}

void allocAndInitStaticVars(Class * class)
{
	class->staticVars = NULL;
	if (class->staticSlotCount == 0)
		return;
	class->staticVars = calloc(class->staticSlotCount, sizeof(Slot));
	for (uint16_t i = 0; i < class->fieldsCount; i++)
	{
		if (isFieldStatic(class->fields + i) && isFieldFinal(class->fields + i))
		{
			initStaticFinalVar(class, class->fields + i);
		}
	}

}

void verify(Class * class) 
{

}

void prepare(Class * class) {
	calcInstanceFieldSlotIds(class);
	calcStaticFieldSlotIds(class);
	allocAndInitStaticVars(class);
}

Class * parseClassFile(char * classContent, int32_t classSize)
{
	ClassFile * classFile = NULL;

	classFile = parseClassData(classContent, classSize);

	return newClass(classFile);
}

void linkClass(ClassLoader * classLoader, Class * c)
{
	verify(c);
	prepare(c);
}

void defineClass(ClassLoader * classLoader, Class * c)
{
	resolveSuperClass(classLoader, c);
	resolveInterfaces(classLoader, c);
	addClassList(classLoader, c);
}

Class * loadNonArrayClass(ClassLoader * classLoader, const char * className)
{
	int32_t classSize = 0;
	char * classContent = NULL;
	Class * loadClass = NULL;
	classSize = readClass(className, &classContent);
	if (classSize > 0 && classContent != NULL){
#if 0
		printf("class size:%d,class data:[", classSize);
		for (int32_t i = 0; i < classSize; i++)
		{
			printf("0x%02x ", classContent[i]);
		}
		printf("]\n");
#endif
	}
	if (classSize <= 0)
	{
		printf("Could not found target class\n");
		exit(127);
	}

	loadClass = parseClassFile(classContent, classSize);
	loadClass->classLoader = classLoader;

	defineClass(classLoader, loadClass);

	linkClass(classLoader, loadClass);

	//printf("[Loaded %s\n", loadClass->name);
	return loadClass;
}

Class * loadArrayClass(ClassLoader * classLoader, const char * className)
{
	Class * c = calloc(1, sizeof(Class));

	c->accessFlags = ACC_PUBLIC;
	c->name = strdup(className);
	c->classLoader = classLoader;
	c->initStarted = true;
	c->superClass = loadClass(classLoader, "java/lang/Object");
	c->interfacesCount = 2;
	c->interfaces = calloc(2, sizeof(Class *));
	c->interfaces[0] = loadClass(classLoader, "java/lang/Cloneable");
	c->interfaces[1] = loadClass(classLoader, "java/io/Serializable");

	addClassList(classLoader, c);

	return c;
}

Class * loadClass(ClassLoader * classLoader, const char * className)
{
	Class * c = NULL;
	ClassList * classList = classLoader->classList;
	//if (classLoader->classList == NULL)
	//	return loadNonArrayClass(classLoader, className);

	while (classList!=NULL)
	{
		if (strcmp(classList->className, className) == 0)
			return classList->classPtr;

		classList = classList->next;
	}

	if (className[0] == '[')
		c =  loadArrayClass(classLoader, className);
	else
		c = loadNonArrayClass(classLoader, className);

	classList = classLoader->classList;
	while (classList != NULL)
	{
		if (strcmp("java/lang/Class", classList->className) == 0)
		{
			if (classList->classPtr != NULL)
			{
				c->jClass = newObject(classList->classPtr);
				c->jClass->extra = c;
				c->jClass->extraType = 'c';
				c->jClass->dataCount = 1;
			}
		}
		classList = classList->next;
	}

	return c;
	}

