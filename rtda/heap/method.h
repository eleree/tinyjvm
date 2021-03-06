#ifndef __TINY_JVM_HEAP_METHOD_H__
#define __TINY_JVM_HEAP_METHOD_H__

#include "../../rtda/rtda.h"
#include "../../classfile/classfile.h"
#include "class.h"
#include "class_member.h"

struct Class;
struct ExceptionTable;
struct MethodDescriptor;
typedef struct Method
{
	struct ClassMember classMember;
	uint16_t maxStack;
	uint16_t maxLocals;
	uint32_t codeLen;
	uint8_t * code;
	uint16_t argSlotCount;
	struct ExceptionTable * exceptionTable;
	struct ExceptionsAttribute * exceptions;
	LineNumberTableAttribute * lineNumberTable;
	struct MethodDescriptor * parsedDescriptor;
	uint8_t * parameterAnnotationData;
	uint32_t parameterAnnotationDataLen;
	uint8_t * annotationDefaultData;
	uint32_t annotationDefaultDataLen;
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
bool isMethodAccessibleTo(Method * method, struct Class * d);

void addParameterType(MethodDescriptor * methodDesc, const char * t);

MethodDescriptor * parseMethodDescriptor(const char * descriptor);

Method * lookupMethodInClass(struct Class *class, char * name, char *  descriptor);
Method * lookupMethodInInterfaces(struct Class ** ifaces, uint16_t ifacesCount, char * name, char * descriptor);

void InvokeMethod(struct Frame * invokerFrame, struct Method * method);

int32_t getMethodLineNumber(Method * self, int32_t pc);
int32_t findMethodExceptionHander(Method * self, struct Class * exClass, int32_t pc);
bool isMethodConstructor(Method * self);
struct Class* * methodParameterTypes(Method * self);
struct Class* * methodExceptionTypes(Method * self);

#endif