#ifndef __TINY_JVM_HEAP_CP_METHODREF_H__
#define __TINY_JVM_HEAP_CP_METHODREF_H__

#include "cp_symref.h"
#include "method.h"
#include "cp_memberref.h"

typedef struct  MethodRef{
	MemberRef memberRef;
	Method* method;
}MethodRef;

#endif