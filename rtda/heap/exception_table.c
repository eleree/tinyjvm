#include "exception_table.h"

ClassRef * getCatchType(uint32_t index, ConstantPoolItem * cp)
{
	if (index == 0)
		return NULL;//catch all
	return getClassConstantPoolClassRef(cp, index);
}

ExceptionTable * newExceptionTable(CodeAttribute * codeAttr, ConstantPoolItem * cp)
{
	ExceptionTable * table = calloc(1, sizeof(ExceptionTable));
	table->handlerCount = codeAttr->exception_table_length;
	table->exceptionHandler = calloc(codeAttr->exception_table_length, sizeof(ExceptionHandler));
	for (int32_t i = 0; i < codeAttr->exception_table_length; i++)
	{
		table->exceptionHandler[i].startPc = codeAttr->exception_table[i].start_pc;
		table->exceptionHandler[i].endPc = codeAttr->exception_table[i].end_pc;
		table->exceptionHandler[i].handlerPc = codeAttr->exception_table[i].handler_pc;
		table->exceptionHandler[i].catchType = getCatchType(codeAttr->exception_table[i].catch_type, cp);		
	}
	return table;
}

ExceptionHandler * findExceptionHandler(ExceptionTable * self, Class * exClass, int32_t pc)
{
	for (int32_t i = 0; i < self->handlerCount; i++)
	{
		// jvms: The start_pc is inclusive and end_pc is exclusive
		ExceptionHandler * handler = self->exceptionHandler + i;
		if (pc >= handler->startPc && pc < handler->endPc)
		{
			return handler;
		}

		Class * catchClass = resolveClass(&handler->catchType->symRef);
		if (catchClass == exClass || isClassSuperClassOf(catchClass, exClass))
		{
			return handler;
		}
	}
	return NULL;
}