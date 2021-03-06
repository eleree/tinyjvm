#include "../../registry.h"

const char * jlDouble = "java/lang/Double";

// public static native long doubleToRawLongBits(double value);
// (D)J
void doubleToRawLongBits(Frame * frame)
{
	DoubleLong transData;
	transData.doubleData = getLocalVarsDouble(frame->localVars, 0);
	int64_t d = (int64_t)(transData.bitsData);
	int64_t i = d / 2;
	pushOperandLong(frame->operandStack, transData.bitsData);
}

// public static native double longBitsToDouble(long bits);
// (J)D
void  longBitsToDouble(Frame * frame)
{
	DoubleLong transData;
	transData.bitsData = getLocalVarsLong(frame->localVars, 0);
	pushOperandDouble(frame->operandStack, transData.doubleData);
}

void initNativeDouble(void)
{
	registerNativeMethod(jlDouble, "doubleToRawLongBits", "(D)J", doubleToRawLongBits);
	registerNativeMethod(jlDouble, "longBitsToDouble", "(J)D", longBitsToDouble);
}
