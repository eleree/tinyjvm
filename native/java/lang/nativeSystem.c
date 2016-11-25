#include "../../registry.h"

const char * jlSystem = "java/lang/System";


bool checkArrayCopy(Object * src, Object * dest)
{
	Class * srcClass = src->class;
	Class * destClass = dest->class;
	
	if (!isClassArray(srcClass) || !isClassArray(destClass))
	{
		return false;
	}

	if (isClassPrimitive(componentClass(srcClass)) ||
		isClassPrimitive(componentClass(destClass))
		)
		return srcClass == destClass;
	return true;
}

void  arraycopy(Frame * frame)
{
	LocalVars * vars = frame->localVars;
	Object * src = getLocalVarsRef(vars, 0);
	int32_t srcPos = getLocalVarsInt(vars, 1);
	Object * dest = getLocalVarsRef(vars, 2);
	int32_t destPos = getLocalVarsInt(vars, 3);
	int32_t length = getLocalVarsInt(vars, 4);

	if (src == NULL || dest == NULL)
		panic("java.lang.NullPointerException\n", -1);

	if (!checkArrayCopy(src,dest))
		panic("java.lang.ArrayStoreException\n", -1);

	if (srcPos < 0 || destPos < 0 || length < 0 ||
		srcPos + length > src->dataCount ||
		destPos + length>dest->dataCount)
	{
		panic("java.lang.IndexOutOfBoundsException\n", -1);
	}

	arrayCopy(src, dest, srcPos, destPos, length);
}

void initNativeSystem(void)
{
	registerNativeMethod(jlSystem, "arraycopy", "(Ljava/lang/Object;ILjava/lang/Object;II)V", arraycopy);
}