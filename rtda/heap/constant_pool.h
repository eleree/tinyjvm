#ifndef __TINY_JVM_HEAP_CONSTANT_POOL_H__
#define __TINY_JVM_HEAP_CONSTANT_POOL_H__

#include "class.h"
#include "cp_symref.h"
#include "../../classfile/classfile.h"
#include "cp_classref.h"
#include "cp_fieldref.h"
#include "cp_methodref.h"

typedef struct ClassConstantInteger{
	uint8_t tag;
	int32_t val;
}ClassConstantInteger;

typedef struct ClassConstantFloat{
	uint8_t tag;
	float val;
}ClassConstantFloat;

typedef struct ClassConstantLong{
	uint8_t tag;
	int64_t val;
}ClassConstantLong;

typedef struct ClassConstantDouble{
	uint8_t tag;
	double val;
}ClassConstantDouble;

typedef struct ClassConstantString{
	uint8_t tag;
	char * str;
}ClassConstantString;

typedef struct ClassConstantClassRef{
	uint8_t tag;
	ClassRef * classRef;
}ClassConstantClassRef;

typedef struct ClassConstantFieldRef{
	uint8_t tag;
	FieldRef * fieldRef;
}ClassConstantFieldRef;

typedef struct ClassConstantMethodRef{
	uint8_t tag;
	MethodRef * methodRef;
}ClassConstantMethodRef;


int32_t getClassConstantPoolInt(ConstantPoolItem * cp, uint16_t index);
float getClassConstantPoolFloat(ConstantPoolItem * cp, uint16_t index);
int64_t getClassConstantPoolLong(ConstantPoolItem * cp, uint16_t index);
double getClassConstantPoolDouble(ConstantPoolItem * cp, uint16_t index);

#endif