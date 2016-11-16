#include "cp_fieldref.h"

FieldRef * newFieldRef(ClassFile *classFile, struct ConstantPool * cp, ConstantFieldrefInfo * fieldRefInfo)
{
	FieldRef * fieldRef = calloc(1, sizeof(fieldRef));
	fieldRef->symRef.constantPool = cp;
	fieldRef->symRef.className = _strdup(getClassName(classFile));
	fieldRef->name = _strdup(getConstalPoolNameAndTypeName(classFile->constantPoolItem, fieldRefInfo->name_and_type_index));;
	fieldRef->descriptor = _strdup(getConstalPoolNameAndTypeDescriptor(classFile->constantPoolItem, fieldRefInfo->name_and_type_index));;
	return fieldRef;
}