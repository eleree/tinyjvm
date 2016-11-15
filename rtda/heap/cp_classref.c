#include "cp_classref.h"

ClassRef * newClassRef(ClassFile * classFile, struct ConstantPool * cp, ConstantClassInfo * classInfo)
{
	ClassRef * classRef = calloc(1, sizeof(ClassRef));
	classRef->symRef.constantPool = cp;
	classRef->symRef.className = _strdup(getClassUtf8(classFile, classInfo->nameIndex));;
	return classRef;
}