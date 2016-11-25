#include "../../registry.h"

const char * jlClass = "java/lang/Class";

void  getPrimitiveClass(Frame * frame)
{

}

void  desiredAssertionStatus0(Frame * frame)
{

}


void  getName0(Frame * frame)
{

}

void initNativeClass(void)
{	
	registerNativeMethod(jlClass, "getPrimitiveClass", "(Ljava/lang/String;)Ljava/lang/Class;", getPrimitiveClass);
	registerNativeMethod(jlClass, "getName0", "()Ljava/lang/String;", getName0);
	registerNativeMethod(jlClass, "desiredAssertionStatus0", "(Ljava/lang/Class;)Z", desiredAssertionStatus0);
}