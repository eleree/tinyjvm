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

MethodRef * newMethodRef(ClassFile *classFile, struct ConstantPool * cp, ConstantMethodrefInfo * methodrefInfo)
{
	MethodRef * methodRef = calloc(1, sizeof(MethodRef));
	methodRef->symRef.constantPool = cp;
	methodRef->symRef.className = _strdup(getClassUtf8(classFile, methodrefInfo->classIndex));
	methodRef->name= _strdup(getConstalPoolNameAndTypeName(classFile->constantPoolItem, methodrefInfo->name_and_type_index));;
	methodRef->descriptor = _strdup(getConstalPoolNameAndTypeDescriptor(classFile->constantPoolItem, methodrefInfo->name_and_type_index));;
	return methodRef;
}