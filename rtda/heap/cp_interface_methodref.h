#ifndef __TINY_JVM_HEAP_CP_INTERFACE_METHODREF_H__
#define __TINY_JVM_HEAP_CP_INTERFACE_METHODREF_H__

#include "class.h"
#include "method.h"
#include "cp_symref.h"
#include "cp_memberref.h"

typedef struct  InterfaceMethodRef{
	MemberRef memberRef;
	Method * method;
}InterfaceMethodRef;

Method * resolvedInterfaceMethod(InterfaceMethodRef * self);

#endif