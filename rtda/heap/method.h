#ifndef __TINY_JVM_HEAP_METHOD_H__
#define __TINY_JVM_HEAP_METHOD_H__

#include "../../rtda/rtda.h"
#include "../../classfile/classfile.h"
#include "class.h"
#include "class_member.h"

struct Class;
typedef struct Method
{
	struct ClassMember classMember;
	uint16_t maxStack;
	uint16_t maxLocals;
	uint32_t codeLen;
	uint8_t * code;
}Method;

Method * newMethods(struct Class * c, ClassFile * classFile);

bool isMethodPublic(Method * method);
bool isMethodPrivate(Method * method);
bool isMethodProtected(Method * method);
bool isMethodStatic(Method * method);
bool isMethodFinal(Method * method);
bool isMethodSynthetic(Method * method);

#endif