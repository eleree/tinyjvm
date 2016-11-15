#ifndef __TINY_JVM_HEAP_CP_SYMREF_H__
#define __TINY_JVM_HEAP_CP_SYMREF_H__

#include "class.h"
#include "class_loader.h"

// symbolic reference
typedef struct SymRef {
	struct ConstantPool * constantPool;
	char * className;
	Class * class;
}SymRef;

Class * resolveClass(SymRef * symRef);

#endif