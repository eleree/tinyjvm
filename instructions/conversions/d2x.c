#include "../factory.h"
#include "../../rtda/operand_stack.h"

// Convert double to float
static int32_t execute_D2F(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	double d = popOperandDouble(operandStack);
	float f = (float)d;
	pushOperandFloat(operandStack, f);
	return 0;
}

Instruction * D2F(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_D2F;
	return inst;
}

// Convert double to int
static int32_t execute_D2I(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	double d = popOperandDouble(operandStack);
	int32_t i = (int32_t)d;
	pushOperandInt(operandStack, i);
	return 0;
}

Instruction * D2I(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_D2I;
	return inst;
}

// Convert double to long
static int32_t execute_D2L(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	double d = popOperandDouble(operandStack);
	int64_t l = (int64_t)d;
	pushOperandLong(operandStack, l);
	return 0;
}

Instruction * D2L(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_D2L;
	return inst;
}
