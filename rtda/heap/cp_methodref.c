#include "cp_methodref.h"

Method *  resolveMethodRef(MethodRef * methodRef)
{
	return NULL;
}

Method * resolvedMethod(MethodRef * methodRef)
{
	if (methodRef->method == NULL)
		return 	resolveMethodRef(methodRef);
	return methodRef->method;
}