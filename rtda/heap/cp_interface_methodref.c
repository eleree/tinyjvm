#include "cp_interface_methodref.h"

void resolvedInterfaceMethod(InterfaceMethodRef * ref)
{
	//ref->symRef.constantPool = cp;
	//ref->symRef.className = _strdup(getClassUtf8(classFile, insteraceMethodRefInfo->name_and_type_index));;
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