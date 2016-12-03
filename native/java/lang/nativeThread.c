#include "../../registry.h"


// public static native Thread currentThread();
// ()Ljava/lang/Thread;
void  currentThread(Frame * frame)
{
	ClassLoader * classLoader = frame->method->classMember.attachClass->classLoader;
	Class * threadClass = loadClass(classLoader, "java/lang/Thread");

	Object * jThread = newObject(threadClass);

	Class * threadGroupClass = loadClass(classLoader, "java/lang/ThreadGroup");
	Object * jGroup = newObject(threadGroupClass);

	setObjectRefVar(jThread, "group", "Ljava/lang/ThreadGroup;", jGroup);
	setObjectIntVar(jThread, "priority", "I", 1);

	pushOperandRef(frame->operandStack, jThread);
}

// private native void setPriority0(int newPriority);
// (I)V
void  setPriority0(Frame * frame)
{
	// vars := frame.LocalVars()
	// this := vars.GetThis()
	// newPriority := vars.GetInt(1))
	// todo
}

// public final native boolean isAlive();
// ()Z
void  isAlive(Frame * frame)
{
	pushOperandBoolean(frame->operandStack, false);
}

// private native void start0();
// ()V
void  start0(Frame * frame)
{
	//todo
}

void initNativeThread(void)
{
	registerNativeMethod("java/lang/Thread", "currentThread", "()Ljava/lang/Thread;", currentThread);
	registerNativeMethod("java/lang/Thread", "setPriority0", "(I)V", setPriority0);
	registerNativeMethod("java/lang/Thread", "isAlive", "()Z", isAlive);
	registerNativeMethod("java/lang/Thread", "start0", "()V", start0);
}