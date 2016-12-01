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
	char * signature;
	struct Class * attachClass;
	uint8_t * annotationData;
	uint32_t annotationDataLen;
}ClassMember;

#endif