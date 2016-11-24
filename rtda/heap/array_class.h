#ifndef __TINY_JVM_HEAP_ARRAY_CLASS_H__
#define __TINY_JVM_HEAP_ARRAY_CLASS_H__

#include "class.h"
#include "class_loader.h"

Object * newArray(Class * self, uint16_t count);

bool isClassArray(Class * self);
char * toDescriptor(const char * className);
char * toClassName(const char * descriptor);
char * getComponentClassName(char * className);
char * getArrayClassName(const char * className);

Class * componentClass(Class * self);

int8_t * getObjectBytes(Object * self);
int16_t * getObjectShorts(Object * self);
int32_t * getObjectInts(Object * self);
int64_t * getObjectLongs(Object * self);
uint16_t * getObjectChars(Object * self);
float * getObjectFloats(Object * self);
double * getObjectDoubles(Object * self);
Object* * getObjectRefs(Object * self);
Slot * getObjectSlots(Object * self);

#endif