#include "cp_methodref.h"

Method * lookupMethod(Class * class, char * name, char * descriptor)
{
	Method * method = lookupMethodInClass(class, name, descriptor);

	if (method == NULL)
		method = lookupMethodInInterfaces(class->interfaces, class->interfacesCount, name, descriptor);
	
	return method;
}

void resolveMethodRef(MethodRef * methodRef)
{
	Class * d = methodRef->symRef.constantPool->class;
	Class * c = resolveClass(&methodRef->symRef);

	if (isClassInterface(c))
	{
		printf("java.lang.IncompatibleClassChangeError\n");
		exit(139);
	}

	Method * method = lookupMethod(c, methodRef->name, methodRef->descriptor);

	if (method == NULL)
	{
		printf("java.lang.NoSuchMethodError\n");
		exit(139);
	}

	if (!isMethodAccessibleTo(method, d))
	{
		printf("java.lang.IllegalAccessError\n");
		exit(139);
	}

	methodRef->method = method;

}

Method * resolvedMethod(MethodRef * methodRef)
{
	if (methodRef->method == NULL)
		resolveMethodRef(methodRef);
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