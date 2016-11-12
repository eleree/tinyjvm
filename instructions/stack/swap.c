#include "../factory.h"
#include "../../rtda/operand_stack.h"

// Convert float to double
static int32_t execute_SWAP(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	Slot * slot1 = popOperandSlot(operandStack);
	Slot * slot2 = popOperandSlot(operandStack);
	pushOperandSlot(operandStack, slot1);
	pushOperandSlot(operandStack, slot2);

	return 0;
}

Instruction * SWAP(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_SWAP;
	return inst;
}

