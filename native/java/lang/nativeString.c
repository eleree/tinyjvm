#include "../../registry.h"

const char * jlString = "java/lang/String";

// public native String intern();
// ()Ljava/lang/String;
void  intern(Frame * frame)
{
	Object * thisObject = getLocalVarsThis(frame->localVars);
	Object * interned = internString(thisObject);
	printf("intern: %s\n",(char * )(goString(thisObject)->data));
	pushOperandRef(frame->operandStack, interned);
}

void initNativeString(void)
{
	registerNativeMethod(jlString, "intern", "()Ljava/lang/String;", intern);
}
