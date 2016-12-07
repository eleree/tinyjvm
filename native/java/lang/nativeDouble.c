#include "../../registry.h"

const char * jlDouble = "java/lang/Double";

// public static native long doubleToRawLongBits(double value);
// (D)J
void doubleToRawLongBits(Frame * frame)
{
	DoubleLong transData;

	transData.doubleData = getLocalVarsDouble(frame->localVars, 0);
	pushOperandLong(frame->operandStack, transData.bitsData);
}

// public static native double longBitsToDouble(long bits);
// (J)D
void  longBitsToDouble(Frame * frame)
{
	DoubleLong transData;
	transData.bitsData = getLocalVarsLong(frame->localVars, 0);
	printf("+++%f\n", transData.doubleData);
	pushOperandDouble(frame->operandStack, transData.doubleData);
}

void initNativeDouble(void)
{
	registerNativeMethod(jlDouble, "doubleToRawLongBits", "(D)J", doubleToRawLongBits);
	registerNativeMethod(jlDouble, "longBitsToDouble", "(J)D", longBitsToDouble);
}
