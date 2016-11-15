#ifndef __TINY_JVM_HEAP_CP_MEMBERREF_H__
#define __TINY_JVM_HEAP_CP_MEMBERREF_H__

#include "cp_symref.h"

typedef struct  MemberRef {
	SymRef symRef;
	char * name;
	char * descriptor;
}MemberRef;

#endif