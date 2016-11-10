#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

// Add double
static int32_t execute_DADD(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	double v1 = popOperandDouble(operandStack);
	double v2 = popOperandDouble(operandStack);
	double result = v1 + v2;
	pushOperandDouble(operandStack, result);
	return 0;
}

Instruction * DADD(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DADD;
	return inst;
}

// Add float
static int32_t execute_FADD(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	float v1 = popOperandFloat(operandStack);
	float v2 = popOperandFloat(operandStack);
	float result = v1 + v2;
	pushOperandFloat(operandStack, result);
	return 0;
}

Instruction * FADD(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_FADD;
	return inst;
}

// Add int
static int32_t execute_IADD(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t v1 = popOperandInt(operandStack);
	int32_t v2 = popOperandInt(operandStack);
	int32_t result = v1 + v2;
	pushOperandInt(operandStack, result);
	return 0;
}

Instruction * IADD(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_IADD;
	return inst;
}

// Add long
static int32_t execute_LADD(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int64_t v1 = popOperandLong(operandStack);
	int64_t v2 = popOperandLong(operandStack);
	int64_t result = v1 + v2;
	pushOperandLong(operandStack, result);
	return 0;
}

Instruction * LADD(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LADD;
	return inst;
}