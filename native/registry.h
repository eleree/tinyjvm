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
#include "../rtda/frame.h"
#include "../rtda/heap/slot.h"
#include "../rtda/heap/string_pool.h"

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
void initNativeThread(void);

void initNativeUnixFileSystem(void);
void initNativeFileOutputStream(void);
void initNativeFileDescriptor(void);

void initUnsafe(void);
void initReflect(void);
void initNativeFileDescriptor(void);
void initAccessController(void);
void initConstructorAccessorImpl(void);
void initUnsafeMem(void);

Object * toClassArr(ClassLoader * classLoader, Class * *interfaces, uint16_t interfacesCount);
Object * getSignatureStr(ClassLoader * classLoader, char * signature);
Object * toByteArr(ClassLoader * classLoader, uint8_t * goBytes, uint32_t  bytesLen);

void getDeclaredFields0(Frame * frame);
void getDeclaredConstructors0(Frame * frame);

/* */
int64_t allocateNativeMemory(int64_t size);
int64_t reallocateNativeMemory(int64_t address, int64_t size);
uint8_t * memoryAt(int64_t address, int64_t * bytesLen);
void freeNativeMemory(int64_t address);

#endif