#ifndef __TINY_JVM_REGISTRY_H__
#define __TINY_JVM_REGISTRY_H__

#include "../rtda/heap/class.h"
#include "../rtda/heap/object.h"
#include "../rtda/heap/string_pool.h"
#include "../rtda/operand_stack.h"
#include "../rtda/heap/method.h"
#include "../rtda/heap/class_loader.h"
#include "../rtda/local_vars.h"
#include "../rtda/heap/array_class.h"
#include "../rtda/thread.h"
typedef void (*NativeMethod)(Frame *frame);

typedef struct NativeMethodList
{
	char * name;
	NativeMethod method;
	struct NativeMethodList * next;
}NativeMethodList;

typedef struct StackTraceElement {
	char * fileName;
	char * className;
	char * methodName;
	int32_t lineNumber;
}StackTraceElement;

NativeMethod findNativeMethod(const char * className, const char * methodName, const char * methodDescriptor);
void registerNativeMethod(const char * className, const char * methodName, const char * methodDescriptor, NativeMethod method);

void initNativeClass(void);
void initNativeDouble(void);
void initNativeFloat(void);
void initNativeObject(void);
void initNativeString(void);
void initNativeSystem(void);
void initVM(void);
void initNativeThrowable(void);

#endif