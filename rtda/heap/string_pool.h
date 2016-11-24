#ifndef __TINY_JVM_HEAP_STRING_POOL_H__
#define __TINY_JVM_HEAP_STRING_POOL_H__

#include "class.h"
typedef struct String
{
	uint32_t len;
	uint16_t type;
	uint8_t * data;
}String;

String * stringToUtf16(const char * s);
String * goString(struct Object * jStr);
struct Object * jString(struct ClassLoader *loader, String * goStr);
String * newString(ClassFile *classFile, struct ConstantPool * cp, ConstantStringInfo * stringInfo);

#endif