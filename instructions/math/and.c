#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

// Boolean AND int
static int32_t execute_IAND(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t v1 = popOperandInt(operandStack);
	int32_t v2 = popOperandInt(operandStack);
	int32_t result = v1 + v2;
	pushOperandInt(operandStack, result);
	return 0;
}

Instruction * IAND(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_IAND;
	return inst;
}

// Boolean AND long
static int32_t execute_LAND(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int64_t v1 = popOperandLong(operandStack);
	int64_t v2 = popOperandLong(operandStack);
	int64_t result = v1 & v2;
	pushOperandLong(operandStack, result);
	return 0;
}

Instruction * LAND(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LAND;
	return inst;
}