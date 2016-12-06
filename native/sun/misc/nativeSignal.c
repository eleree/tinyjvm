#include "../../registry.h"

// private static native int findSignal(String string);
// (Ljava/lang/String;)I
void findSignal(Frame * frame)
{
	LocalVars * vars = frame->localVars;
	getLocalVarsRef(vars, 0); //name

	pushOperandInt(frame->operandStack, 0);
}

// private static native long handle0(int i, long l);
// (IJ)J
void handle0(Frame * frame)
{
	LocalVars * vars = frame->localVars;
	getLocalVarsInt(vars, 0); 
	getLocalVarsLong(vars, 1);

	pushOperandLong(frame->operandStack, 0);
}

void initSignal(void)
{
	registerNativeMethod("sun/misc/Signal", "findSignal", "(Ljava/lang/String;)I", findSignal);
	registerNativeMethod("sun/misc/Signal", "handle0", "(IJ)J", handle0);
}