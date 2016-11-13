#ifndef __TINY_JVM_HEAP_FIELD_H__
#define __TINY_JVM_HEAP_FIELD_H__

#include "../../classfile/classfile.h"
#include "class.h"
#include "class_member.h"

struct Class;
typedef struct Field
{
	struct ClassMember classMember;
	uint16_t constValueIndex;
	uint16_t slotId;
}Field;

Field * newFields(struct Class * c, ClassFile * classFile);

#endif