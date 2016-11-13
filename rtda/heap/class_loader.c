#include "class_loader.h"
#include "../../classfile/classfile.h"
#include "../../classpath/classpath.h"
#include "class.h"
ClassLoader * newClassLoader(void)
{
	return calloc(1, sizeof(ClassLoader));
}

Class * loadNonArrayClass(ClassLoader * classLoader, const char * className)
{
	int32_t classSize = 0;
	char * classContent = NULL;
	ClassFile * classFile = NULL;
	classSize = readClass(className, &classContent);
	if (classSize > 0 && classContent != NULL){
		printf("class size:%d,class data:[", classSize);
		for (int32_t i = 0; i < classSize; i++)
		{
			printf("0x%02x ", classContent[i]);
		}
		printf("]\n");
	}
	classFile = parseClassData(classContent, classSize);
	
	return newClass(classFile);
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

