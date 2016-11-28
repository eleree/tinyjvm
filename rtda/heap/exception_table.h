#ifndef __TINY_JVM_HEAP_EXCEPTION_TABLE_H__
#define __TINY_JVM_HEAP_EXCEPTION_TABLE_H__

#include "class.h"
#include "class_loader.h"
#include "cp_classref.h"
#include "constant_pool.h"

typedef struct ExceptionHandler
{
	int32_t startPc;
	int32_t endPc;
	int32_t handlerPc;
	struct ClassRef *catchType;
}ExceptionHandler;

typedef struct ExceptionTable
{
	int32_t handlerCount;
	ExceptionHandler * exceptionHandler;
}ExceptionTable;

ExceptionTable * newExceptionTable(CodeAttribute * codeAttr, ConstantPoolItem * cp);
ExceptionHandler * findExceptionHandler(ExceptionTable * self, Class * exClass, int32_t pc);

#endif