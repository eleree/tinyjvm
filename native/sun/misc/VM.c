#include "../../registry.h"

void initialize(Frame * frame)
{
	Class * vmClass = frame->method->classMember.attachClass;
	Object * savedProps = getClassRefVar(vmClass, "savedProps", "Ljava/util/Properties;");
	String foo;
	String bar;
	foo.data = "foo";
	foo.len = 3;
	bar.data = "bar";
	bar.len = 3;
	Object * key = jString(vmClass->classLoader, &foo);
	Object * val = jString(vmClass->classLoader, &bar);

	pushOperandRef(frame->operandStack, savedProps);
	pushOperandRef(frame->operandStack, key);
	pushOperandRef(frame->operandStack, val);

	Class * propsClass = loadClass(vmClass->classLoader, "java/util/Properties");
	Method * setPropMethod = getClassInstanceMethod(propsClass, "setProperty",
		"(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Object;");

	InvokeMethod(frame, setPropMethod);
}

void initVM(void)
{
	registerNativeMethod("sun/misc/VM", "initialize", "()V", initialize);
}