#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

// Multiply double
static int32_t execute_DMUL(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	double v2 = popOperandDouble(operandStack);
	double v1 = popOperandDouble(operandStack);
	double result = v1 * v2;
	pushOperandDouble(operandStack, result);
	return 0;
}

Instruction * DMUL(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DMUL;
	return inst;
}

// Multiply float
static int32_t execute_FMUL(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	float v2 = popOperandFloat(operandStack);
	float v1 = popOperandFloat(operandStack);
	float result = v1 * v2;
	pushOperandFloat(operandStack, result);
	return 0;
}

Instruction * FMUL(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_FMUL;
	return inst;
}


// Multiply int
static int32_t execute_IMUL(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t v2 = popOperandInt(operandStack);
	int32_t v1 = popOperandInt(operandStack);
	int32_t result = v1 * v2;

	pushOperandInt(operandStack, result);
	return 0;
}

Instruction * IMUL(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_IMUL;
	return inst;
}

// Multiply long
static int32_t execute_LMUL(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int64_t v2 = popOperandLong(operandStack);
	int64_t v1 = popOperandLong(operandStack);
	int64_t result = v1 * v2;

	pushOperandLong(operandStack, result);
	return 0;
}

Instruction * LMUL(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LMUL;
	return inst;
}
