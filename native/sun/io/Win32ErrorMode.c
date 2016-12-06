#include "../../registry.h"


void setErrorMode(Frame * frame)
{
	pushOperandLong(frame->operandStack, 0);
}

void initWin32ErrorMode(void)
{	
	registerNativeMethod("sun/io/Win32ErrorMode", "setErrorMode", "(J)J", setErrorMode);
}