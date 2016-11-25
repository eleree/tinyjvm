#include "../../registry.h"

const char * jlString = "java/lang/String";

// public native String intern();
// ()Ljava/lang/String;
void  intern(Frame * frame)
{
	Object * thisObject = getLocalVarsThis(frame->localVars);

}

void initNativeString(void)
{
	registerNativeMethod(jlString, "getClass", "()Ljava/lang/Class;", intern);
}
