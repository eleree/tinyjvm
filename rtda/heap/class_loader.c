#include "class_loader.h"
#include "../../classfile/classfile.h"
#include "../../classpath/classpath.h"
#include "class.h"


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

}

void calcStaticFieldSlotIds(Class * class)
{

}

void allocAndInitStaticVars(Class * class)
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

	resolveSuperClass(classLoader, loadClass);
	resolveInterfaces(classLoader, loadClass);
	addClassList(classLoader, loadClass);

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

