#include <math.h>
#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

// Remainder double
static int32_t execute_DREM(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	double v2 = popOperandDouble(operandStack);
	double v1 = popOperandDouble(operandStack);
	double result = fmod(v1,v2);
	pushOperandDouble(operandStack, result);
	return 0;
}

Instruction * DREM(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DREM;
	return inst;
}

// Remainder float
static int32_t execute_FREM(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	float v2 = popOperandFloat(operandStack);
	float v1 = popOperandFloat(operandStack);
	float result = (float) fmod(v1, v2);
	pushOperandFloat(operandStack, result);
	return 0;
}

Instruction * FREM(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_FREM;
	return inst;
}


// Remainder int
static int32_t execute_IREM(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t v2 = popOperandInt(operandStack);
	int32_t v1 = popOperandInt(operandStack);
	if (v2 == 0)
	{
		printf("java.lang.ArithmeticException: / by zero");
		exit(1);
	}

	int32_t result = v1 % v2;
	pushOperandInt(operandStack, result);
	return 0;
}

Instruction * IREM(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_IREM;
	return inst;
}

// Remainder long
static int32_t execute_LREM(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int64_t v2 = popOperandLong(operandStack);
	int64_t v1 = popOperandLong(operandStack);
	if (v2 == 0)
	{
		printf("java.lang.ArithmeticException: / by zero");
		exit(1);
	}

	int64_t result = v1 % v2;
	pushOperandLong(operandStack, result);
	return 0;
}

Instruction * LREM(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LREM;
	return inst;
}
