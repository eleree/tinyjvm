#include "../factory.h"
#include "../../rtda/operand_stack.h"

// Pop the top operand stack value
static int32_t execute_POP(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	popOperandSlot(operandStack);
	return 0;
}

Instruction * POP(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_POP;
	return inst;
}


// Pop the top one or two operand stack values
static int32_t execute_POP2(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	popOperandSlot(operandStack);
	popOperandSlot(operandStack);
	return 0;
}

Instruction * POP2(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_POP2;
	return inst;
}