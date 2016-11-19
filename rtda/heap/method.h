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
	uint16_t argSlotCount;
}Method;

typedef struct ParameterTypesList
{
	char * parameterTypes;
	struct ParameterTypesList * next;
}ParameterTypesList;

typedef struct MethodDescriptor
{
	uint16_t parameterTypesCount;
	ParameterTypesList* parameterTypesList;
	char* returnType;
}MethodDescriptor;


typedef struct MethodDescriptorParser {
	char * raw;
	uint16_t offset;
	struct MethodDescriptor * parsed;
}MethodDescriptorParser;

Method * newMethods(struct Class * c, ClassFile * classFile);

bool isMethodSynchronized(Method * method);
bool isMethodBridge(Method * method);
bool isMethodVarargs(Method * method);
bool isMethodNative(Method * method);
bool isMethodAbstract(Method * method);
bool isMethodStrict(Method * method);

bool isMethodPublic(Method * method);
bool isMethodPrivate(Method * method);
bool isMethodProtected(Method * method);
bool isMethodStatic(Method * method);
bool isMethodFinal(Method * method);
bool isMethodSynthetic(Method * method);

void addParameterType(MethodDescriptor * methodDesc, const char * t);

#endif