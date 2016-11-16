#ifndef __TINY_JVM_HEAP_CP_METHODREF_H__
#define __TINY_JVM_HEAP_CP_METHODREF_H__

#include "cp_symref.h"
#include "method.h"
#include "cp_memberref.h"

typedef struct  MethodRef{
	SymRef symRef;

	/* MemberRef */
	char * name;
	char * descriptor;

	/* Method */
	Method* method;
}MethodRef;

MethodRef * newMethodRef(ClassFile *classFile, struct ConstantPool * cp, ConstantMethodrefInfo * methodrefInfo);

#endif