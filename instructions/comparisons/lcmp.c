#include "../factory.h"
#include "../../rtda/operand_stack.h"

static int32_t execute_LCMP(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int64_t v2 = popOperandLong(operandStack);
	int64_t v1 = popOperandLong(operandStack);
	if (v1 > v2)
		pushOperandInt(operandStack, 1);
	else if (v1 == v2)
		pushOperandInt(operandStack, 0);
	else
		pushOperandInt(operandStack, -1);

	return 0;
}

Instruction * LCMP(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LCMP;
	return inst;
}