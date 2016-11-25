#include "../../registry.h"

const char * jlClass = "java/lang/Class";

// static native Class<?> getPrimitiveClass(String name);
// (Ljava/lang/String;)Ljava/lang/Class;
void  getPrimitiveClass(Frame * frame)
{
	Object * nameObj = getLocalVarsRef(frame->localVars, 0);
	String * name = goString(nameObj);
	ClassLoader * classLoader = frame->method->classMember.attachClass->classLoader;
	Object * jlClass = loadClass(classLoader, name->data)->jClass;

	pushOperandRef(frame->operandStack, jlClass);
}

// private static native boolean desiredAssertionStatus0(Class<?> clazz);
// (Ljava/lang/Class;)Z
void  desiredAssertionStatus0(Frame * frame)
{
	pushOperandBoolean(frame->operandStack, false);
}

// private native String getName0();
// ()Ljava/lang/String;
void  getName0(Frame * frame)
{
	Object * thisObject = getLocalVarsThis(frame->localVars);
	Class * extraClass = (Class *) thisObject->extra;

	String nameStr = { 0 };
	nameStr.data = classJavaName(extraClass);
	nameStr.len = strlen(nameStr.data);
	nameStr.type = STRING_TYPE_UTF8;
	Object * nameObject = jString(extraClass->classLoader, &nameStr);

	pushOperandRef(frame->operandStack, nameObject);
}

void initNativeClass(void)
{	
	registerNativeMethod(jlClass, "getPrimitiveClass", "(Ljava/lang/String;)Ljava/lang/Class;", getPrimitiveClass);
	registerNativeMethod(jlClass, "getName0", "()Ljava/lang/String;", getName0);
	registerNativeMethod(jlClass, "desiredAssertionStatus0", "(Ljava/lang/Class;)Z", desiredAssertionStatus0);
}