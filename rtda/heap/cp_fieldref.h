#ifndef __TINY_JVM_HEAP_CP_FIELDREF_H__
#define __TINY_JVM_HEAP_CP_FIELDREF_H__

#include "class.h"
#include "field.h"
#include "cp_symref.h"
#include "cp_memberref.h"
#include "../../classfile/classfile.h"

typedef struct  FieldRef{
	/* SymRef*/
	SymRef symRef;

	/* MemberRef */
	char * name;
	char * descriptor;

	/* Field */
	Field * field;
}FieldRef;

FieldRef * newFieldRef(ClassFile *classFile, struct ConstantPool * cp, ConstantFieldrefInfo * fieldRefInfo);

#endif