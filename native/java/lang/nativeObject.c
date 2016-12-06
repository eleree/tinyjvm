#include "../../registry.h"
#include <time.h>

const char * jlObject = "java/lang/Object";
static int32_t random = 3;
// public final native Class<?> getClass();
// ()Ljava/lang/Class;
void  getClass(Frame * frame)
{
	Object * thisObject = getLocalVarsThis(frame->localVars);
	Object * jClass = thisObject->class->jClass;
	pushOperandRef(frame->operandStack, jClass);
}

// public native int hashCode();
// ()I
void  hashCode(Frame * frame)
{
	srand(time(NULL));
	Object * thisObject = getLocalVarsThis(frame->localVars);
	int32_t hash = (int32_t)thisObject + rand() + random;
	pushOperandInt(frame->operandStack, hash);
}

// protected native Object clone() throws CloneNotSupportedException;
// ()Ljava/lang/Object;
void  clone(Frame * frame)
{
	Object * thisObject = getLocalVarsThis(frame->localVars);
	Class * cloneable = loadClass(thisObject->class->classLoader, "java/lang/Cloneable");
	if (!isClassImplements(thisObject->class, cloneable))
	{
		panic("java.lang.CloneNotSupportedException\n", 123);
	}
	pushOperandRef(frame->operandStack, cloneObject(thisObject));
}

void  notifyAll(Frame * frame)
{
	//todo
}

void initNativeObject(void)
{
	registerNativeMethod(jlObject, "getClass", "()Ljava/lang/Class;", getClass);
	registerNativeMethod(jlObject, "hashCode", "()I", hashCode);
	registerNativeMethod(jlObject, "clone", "()Ljava/lang/Object;", clone);
	registerNativeMethod(jlObject, "notifyAll", "()V", notifyAll);
}

