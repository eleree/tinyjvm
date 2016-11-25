#ifndef __TINY_JVM_HEAP_STRING_POOL_H__
#define __TINY_JVM_HEAP_STRING_POOL_H__

#include "class.h"

enum{
	STRING_TYPE_UTF8 = 0,
	STRING_TYPE_UTF16 = 1,
	STRING_TYPE_MUTF8 = 2,
};

typedef struct String
{
	uint32_t len;
	uint16_t type;
	void * data;
}String;

String * stringToUtf16(const char * s);
String * goString(struct Object * jStr);
struct Object * jString(struct ClassLoader *loader, String * goStr);
String * newString(ClassFile *classFile, struct ConstantPool * cp, ConstantStringInfo * stringInfo);
uint16_t *  decodeMutf8ToUtf16(const char * srcStr, uint32_t srcLen, uint32_t * resultLen);
Object * internString(Object * jStr);

#endif