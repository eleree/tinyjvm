#include "../../registry.h"

const char * jlFloat = "java/lang/Float";


// public static native int floatToRawIntBits(float value);
// (F)I
void floatToRawIntBits(Frame * frame)
{
	FloatInt transData;
	transData.floatData = getLocalVarsFloat(frame->localVars, 0);
	pushOperandInt(frame->operandStack, transData.bitsData);
}

// public static native float intBitsToFloat(int bits);
// (I)F
void  intBitsToFloat(Frame * frame)
{
	FloatInt transData;
	transData.bitsData = getLocalVarsInt(frame->localVars, 0);
	pushOperandFloat(frame->operandStack, transData.floatData);
}

void initNativeFloat(void)
{
	registerNativeMethod(jlFloat, "floatToRawIntBits", "(F)I", floatToRawIntBits);
	registerNativeMethod(jlFloat, "intBitsToFloat", "(I)F", intBitsToFloat);
}
