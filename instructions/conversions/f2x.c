#include "../factory.h"
#include "../../rtda/operand_stack.h"

// Convert float to double
static int32_t execute_F2D(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	float f = popOperandFloat(operandStack);
	double d = (double)f;
	pushOperandDouble(operandStack, d);
	return 0;
}

Instruction * F2D(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_F2D;
	return inst;
}

// Convert float to int
static int32_t execute_F2I(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	float f = popOperandFloat(operandStack);
	int32_t i = (int32_t)f;
	pushOperandInt(operandStack, i);
	return 0;
}

Instruction * F2I(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_F2I;
	return inst;
}

// Convert float to long
static int32_t execute_F2L(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	float f = popOperandFloat(operandStack);
	int64_t l = (int64_t)f;
	pushOperandLong(operandStack, l);
	return 0;
}

Instruction * F2L(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_F2L;
	return inst;
}
