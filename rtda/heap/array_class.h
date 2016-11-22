#ifndef __TINY_JVM_HEAP_ARRAY_CLASS_H__
#define __TINY_JVM_HEAP_ARRAY_CLASS_H__

#include "class.h"
#include "class_loader.h"

bool isClassArray(Class * self);
char * toDescriptor(const char * className);
char * toClassName(const char * descriptor);
char * getComponentClassName(char * className);
char * getArrayClassName(const char * className);

#endif