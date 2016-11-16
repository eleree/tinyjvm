#ifndef __TINY_JVM_HEAP_CP_CLASSREF_H__
#define __TINY_JVM_HEAP_CP_CLASSREF_H__

#include "class.h"
#include "cp_symref.h"
#include "../../classfile/classfile.h"

typedef struct  ClassRef{
	SymRef symRef;
}ClassRef;

ClassRef * newClassRef(ClassFile * classFile, struct ConstantPool * cp, ConstantClassInfo * classInfo);

#endif