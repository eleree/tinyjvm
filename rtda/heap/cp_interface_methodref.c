#include "cp_interface_methodref.h"

Method * lookupInterfaceMethod(Class * iface, char * name, char * descriptor)
{
	for (uint16_t i = 0; i < iface->methodsCount; i++)
	{
		Method * method = iface->methods + i;
		if (strcmp(method->classMember.name, name) == 0 &&
			strcmp(method->classMember.descriptor, descriptor) == 0)
			return method;
	}
	return lookupMethodInInterfaces(iface->interfaces, iface->interfacesCount, name, descriptor);
}

void resolveInterfaceMethodRef(InterfaceMethodRef * self)
{
	Class * d = self->memberRef.symRef.constantPool->class;
	Class * c = resolveClass(&self->memberRef.symRef);

	if (!isClassInterface(c))
	{
		printf("java.lang.IncompatibleClassChangeError\n");
		exit(129);
	}

	Method * method = lookupInterfaceMethod(c, self->memberRef.name, self->memberRef.descriptor);
	if (method == NULL)
	{
		printf("java.lang.NoSuchMethodError\n");
		exit(130);
	}

	if (!isMethodAccessibleTo(method, d))
	{
		printf("java.lang.NoSuchMethodError\n");
		exit(131);
	}

	self->method = method;
}

Method * resolvedInterfaceMethod(InterfaceMethodRef * self)
{
	if (self->method == NULL)
	{
		resolveInterfaceMethodRef(self);
	}
	return self->method;
}

InterfaceMethodRef * newInterfaceMethodRef(ClassFile * classFile, struct ConstantPool * cp, ConstantInterfaceMethodrefInfo * insteraceMethodRefInfo)
{
	InterfaceMethodRef * ref = calloc(1, sizeof(InterfaceMethodRef));

	ref->memberRef.symRef.constantPool = cp;
	ref->memberRef.symRef.className = _strdup(getClassUtf8(classFile, insteraceMethodRefInfo->class_index));
	ref->memberRef.name = _strdup(getConstalPoolNameAndTypeName(classFile->constantPoolItem, insteraceMethodRefInfo->name_and_type_index));
	ref->memberRef.descriptor = _strdup(getConstalPoolNameAndTypeDescriptor(classFile->constantPoolItem, insteraceMethodRefInfo->name_and_type_index));;

	return ref;
}