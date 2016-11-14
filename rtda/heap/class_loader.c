#include "class_loader.h"
#include "../../classfile/classfile.h"
#include "../../classpath/classpath.h"
#include "../../rtda/rtda.h"

#include "class.h"
#include "slot.h"

ClassLoader * newClassLoader(void)
{
	return calloc(1, sizeof(ClassLoader));
}

void addClassList(ClassLoader * classLoader, Class * newClass)
{

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

void initStaticFinalVar(Class * class, Field * field) 
{
	Slot * staticVars = class->staticVars;
	ConstantPoolItem * constantPool = class->constantPoolItem;
	uint16_t cpIndex = field->constValueIndex;
	uint16_t slotId = field->slotId;
	int32_t int32Val = 0;
	int64_t int64Val = 0;

	if (cpIndex > 0)
	{
		switch (field->classMember.descriptor[0])
		{
		case 'Z':
		case 'B':
		case 'C':
		case 'S':
		case 'I':
			// int32Val =  getConstantInt(cpIndex);
			setSlotInt(staticVars, slotId, int32Val);
			break;
		case 'J':
		case 'F':
		case 'D':
			break;
		}
		if (strcmp(field->classMember.descriptor, "Ljava/lang/String;") == 0)
		{
			printf("todo\n");
			exit(1);
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

void linkClass(ClassLoader * classLoader, Class * class)
{
	verify(class);
	prepare(class);
}

void defineClass(ClassLoader * classLoader, Class * class)
{
	resolveSuperClass(classLoader, class);
	resolveInterfaces(classLoader, class);
	addClassList(classLoader, class);
}

Class * loadNonArrayClass(ClassLoader * classLoader, const char * className)
{
	int32_t classSize = 0;
	char * classContent = NULL;
	Class * loadClass = NULL;
	classSize = readClass(className, &classContent);
	if (classSize > 0 && classContent != NULL){
		printf("class size:%d,class data:[", classSize);
		for (int32_t i = 0; i < classSize; i++)
		{
			printf("0x%02x ", classContent[i]);
		}
		printf("]\n");
	}
	loadClass = parseClassFile(classContent, classSize);

	defineClass(classLoader, loadClass);

	linkClass(classLoader, loadClass);

	return loadClass;
}

Class * loadClass(ClassLoader * classLoader, const char * className)
{
	ClassList * classList = classLoader->classList;
	if (classLoader->classList == NULL)
		return loadNonArrayClass(classLoader, className);

	while (classList!=NULL)
	{
		if (strcmp(classList->className, className) == 0)
			return classList->classPtr;

		classList = classList->next;
	}

	return loadNonArrayClass(classLoader, className);
	}

