#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

int32_t _iload(Frame * frame, int32_t index)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	int32_t val = getLocalVarsInt(localVars, index);
	//printf("_iload %d index:%d\n", val, index);
#if ENABLE_ARRAY_DEBUG
	printf("[");
	uint16_t size = localVars->size;
	for (uint16_t i = 0; i < size; i++)
	{
		Slot * slot = localVars->slots + i;
		printf("%d:%d ", i, slot->num);
	}
	printf("]\n");
#endif

	pushOperandInt(operandStack,val);
	return 0;
}

int32_t execute_ILOAD(Frame * frame, struct InsturctionData * instData)
{
	return _iload(frame, instData->index);
}

Instruction * ILOAD(Instruction * inst)
{
	inst->fetchOperands = index8InstructionFetchOperands;
	inst->execute = execute_ILOAD;
	return inst;
}

static int32_t execute_ILOAD_0(Frame * frame, struct InsturctionData * instData)
{
	return _iload(frame, 0);
}

Instruction * ILOAD_0(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ILOAD_0;
	return inst;
}

static int32_t execute_ILOAD_1(Frame * frame, struct InsturctionData * instData)
{
	return _iload(frame, 1);
}

Instruction * ILOAD_1(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ILOAD_1;
	return inst;
}

static int32_t execute_ILOAD_2(Frame * frame, struct InsturctionData * instData)
{
	return _iload(frame, 2);
}

Instruction * ILOAD_2(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ILOAD_2;
	return inst;
}

static int32_t execute_ILOAD_3(Frame * frame, struct InsturctionData * instData)
{
	return _iload(frame, 3);
}

Instruction * ILOAD_3(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ILOAD_3;
	return inst;
}


