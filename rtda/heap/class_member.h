#ifndef __TINY_JVM_HEAP_CLASS_MEMBER_H__
#define __TINY_JVM_HEAP_CLASS_MEMBER_H__

#include "../../rtda/rtda.h"
#include "../../classfile/classfile.h"

struct Class;
typedef struct ClassMember
{
	uint16_t accessFlags;
	char * name;
	char * descriptor;
	struct Class * attachClass;
}ClassMember;

#endif