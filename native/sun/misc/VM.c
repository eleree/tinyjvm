#include "../../registry.h"

#pragma warning(disable:4996)

/*
void initialize(Frame * frame)
{
	Class * vmClass = frame->method->classMember.attachClass;
	Object * savedProps = getClassRefVar(vmClass, "savedProps", "Ljava/util/Properties;");
	String * foo = calloc(1, sizeof(String));
	String * bar = calloc(1, sizeof(String));
	foo->data = strdup("foo");
	foo->len = 3;
	bar->data = strdup("bar");
	bar->len = 3;
	Object * key = jString(vmClass->classLoader, foo);
	Object * val = jString(vmClass->classLoader, bar);

	pushOperandRef(frame->operandStack, savedProps);
	pushOperandRef(frame->operandStack, key);
	pushOperandRef(frame->operandStack, val);

	Class * propsClass = loadClass(vmClass->classLoader, "java/util/Properties");
	Method * setPropMethod = getClassInstanceMethod(propsClass, "setProperty",
		"(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Object;");

	InvokeMethod(frame, setPropMethod);
}
*/
void initialize(Frame * frame)
{
	ClassLoader * classLoader = frame->method->classMember.attachClass->classLoader;

	Class * jlSysClass = loadClass(classLoader, "java/lang/System");
	Method * initSysClass = getClassStaticMethod(jlSysClass, "initializeSystemClass", "()V");
	InvokeMethod(frame, initSysClass);
}
void initVM(void)
{
	registerNativeMethod("sun/misc/VM", "initialize", "()V", initialize);
}