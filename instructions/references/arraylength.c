#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"
#include "../../rtda/heap/array_class.h"

static int32_t execute_ARRAY_LENGTH(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	Object * arrRef = popOperandRef(operandStack);
	if (arrRef == NULL)
		panic("java.lang.NullPointerException", 151);

	int32_t arrLen = arrRef->dataCount;

	printf("array:%d\n", arrLen);
	

	if (arrRef->dataType == 'I')
	{
		printf("[");
		for (uint16_t i = 0; i < arrRef->dataCount; i++)
		{
			int32_t * int32s = arrRef->data;
			printf("%ld ", int32s[i]);
		}
		printf("]\n");
	}
	
	pushOperandInt(operandStack, arrLen);
	return 0;
}

Instruction * ARRAY_LENGTH(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ARRAY_LENGTH;
	return inst;
}
