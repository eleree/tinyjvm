#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"
#include "../../rtda/heap/cp_methodref.h"

// Invoke instance method; dispatch based on class
static int32_t execute_INVOKE_VIRTUAL(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	ConstantPoolItem * cp = frame->method->classMember.attachClass->constantPool.constantPoolItem;
	MethodRef * methodRef = getClassConstantPoolMethodRef(cp, instData->index);

	if (strcmp(methodRef->name, "println") == 0)
	{
		if (strncmp(methodRef->descriptor, "(Z)V",4)==0)
		{
			printf("%d\n", popOperandInt(operandStack));
		}
		else if (strncmp(methodRef->descriptor, "(C)V", 4) == 0)
		{
			printf("%c\n", popOperandInt(operandStack));
		}
		else if (strncmp(methodRef->descriptor, "(I)V", 4) == 0)
		{
			printf("%d\n", popOperandInt(operandStack));
		}
		else if (strncmp(methodRef->descriptor, "(B)V", 4) == 0)
		{
			printf("%d\n", popOperandInt(operandStack));
		}
		else if (strncmp(methodRef->descriptor, "(S)V", 4) == 0)
		{
			printf("%d\n", popOperandInt(operandStack));
		}
		else if (strncmp(methodRef->descriptor, "(F)V", 4) == 0)
		{
			printf("%f\n", popOperandInt(operandStack));
		}
		else if (strncmp(methodRef->descriptor, "(J)V", 4) == 0)
		{
			printf("%lld\n", popOperandInt(operandStack));
		}
		else if (strncmp(methodRef->descriptor, "(D)V", 4) == 0)
		{
			printf("%llf\n", popOperandInt(operandStack));
		}
		else
		{
			printf("println:%s\n", methodRef->descriptor);
			exit(-1);
		}
		popOperandRef(operandStack);
	}

	return 0;
}

Instruction * INVOKE_VIRTUAL(Instruction * inst)
{
	inst->fetchOperands = index16InstructionFetchOperands;
	inst->execute = execute_INVOKE_VIRTUAL;
	return inst;
}
