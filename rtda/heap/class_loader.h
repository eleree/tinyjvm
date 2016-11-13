#ifndef __TINY_JVM_CLASS_LOADER_H__
#define __TINY_JVM_CLASS_LOADER_H__

#include "class.h"

typedef struct ClassList
{
	char * className;
	struct Class * classPtr;
	struct ClassList * next;	
}ClassList;

typedef struct CLassLoader
{
	ClassList * classList;
}ClassLoader;

ClassLoader * newClassLoader(void);
Class * loadClass(ClassLoader * classLoader, const char * className);

#endif