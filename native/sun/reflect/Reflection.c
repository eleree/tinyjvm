#include "../../registry.h"

// public static native Class<?> getCallerClass();
// ()Ljava/lang/Class;
void  getCallerClass(Frame * frame)
{
	// top0 is sun/reflect/Reflection
	// top1 is the caller of getCallerClass()
	// top2 is the caller of method
	int32_t remain = 0;
	Frame * callerFrame = getThreadFrames(frame->thread, 0, &remain)[2];
	Object * callerClass = callerFrame->method->classMember.attachClass->jClass;
	pushOperandRef(frame->operandStack, callerClass);
}

// public static native int getClassAccessFlags(Class<?> type);
// (Ljava/lang/Class;)I
void  getClassAccessFlags(Frame * frame)
{
	//printf("Invoke Native Method %s\n", __FUNCTION__);
	//exit(1);
	LocalVars * vars = frame->localVars;
	Object * _type = getLocalVarsRef(vars, 0);
	Class * goClass = _type->extra;
	
	uint16_t flags = goClass->accessFlags;

	pushOperandInt(frame->operandStack, (int32_t)flags);

}

void initReflect(void)
{
	registerNativeMethod("sun/reflect/Reflection", "getCallerClass", "()Ljava/lang/Class;", getCallerClass);
	registerNativeMethod("sun/reflect/Reflection", "getClassAccessFlags", "(Ljava/lang/Class;)I", getClassAccessFlags);

}