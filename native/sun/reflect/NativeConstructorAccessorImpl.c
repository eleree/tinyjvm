#include "../../registry.h"

// private static native Object newInstance0(Constructor<?> c, Object[] os)
// throws InstantiationException, IllegalArgumentException, InvocationTargetException;
// (Ljava/lang/reflect/Constructor;[Ljava/lang/Object;)Ljava/lang/Object;
static void  newInstance0(Frame * frame)
{
	printf("Invoke Native Method %s\n", __FUNCTION__);
	exit(1);
	/*
	LocalVars * vars = frame->localVars;
	Object * constructorObj = getLocalVarsRef(vars, 0);
	Object * argArrObj 

	pushOperandRef(frame->operandStack, action);
	Method * method = getClassInstanceMethod(action->class, "run", "()Ljava/lang/Object;");

	InvokeMethod(frame, method);
	*/
}

void initConstructorAccessorImpl(void)
{
	registerNativeMethod("sun/reflect/NativeConstructorAccessorImpl", "newInstance0", "(Ljava/lang/reflect/Constructor;[Ljava/lang/Object;)Ljava/lang/Object;", newInstance0);
}