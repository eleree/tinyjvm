#include "../../registry.h"

// @CallerSensitive
// public static native <T> T
//     doPrivileged(PrivilegedExceptionAction<T> action)
//     throws PrivilegedActionException;
// (Ljava/security/PrivilegedExceptionAction;)Ljava/lang/Object;

// @CallerSensitive
// public static native <T> T doPrivileged(PrivilegedAction<T> action);
// (Ljava/security/PrivilegedAction;)Ljava/lang/Object;
static void  doPrivileged(Frame * frame)
{
	LocalVars * vars = frame->localVars;
	Object * action = getLocalVarsRef(vars, 0);

	OperandStack * stack = frame->operandStack;
	pushOperandRef(stack, action);

	Method * method = getClassInstanceMethod(action->class, "run", "()Ljava/lang/Object;");

	InvokeMethod(frame, method);
}

// private static native AccessControlContext getStackAccessControlContext();
// ()Ljava/security/AccessControlContext;
void  getStackAccessControlContext(Frame * frame)
{
	// todo
	pushOperandRef(frame->operandStack, NULL);
}

void initAccessController(void)
{
	registerNativeMethod("java/security/AccessController", "doPrivileged", "(Ljava/security/PrivilegedAction;)Ljava/lang/Object;", doPrivileged);
	registerNativeMethod("java/security/AccessController", "doPrivileged", "(Ljava/security/PrivilegedExceptionAction;)Ljava/lang/Object;", doPrivileged);
	registerNativeMethod("java/security/AccessController", "getStackAccessControlContext", "()Ljava/security/AccessControlContext;", getStackAccessControlContext);

}