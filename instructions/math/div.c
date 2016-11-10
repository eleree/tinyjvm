#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"


// Divide double
static int32_t execute_DDIV(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	double v2 = popOperandDouble(operandStack);
	double v1 = popOperandDouble(operandStack);
	double result = v1 / v2;
	pushOperandDouble(operandStack, result);
	return 0;
}

Instruction * DDIV(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DDIV;
	return inst;
}

// Divide float
static int32_t execute_FDIV(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	float v2 = popOperandFloat(operandStack);
	float v1 = popOperandFloat(operandStack);
	float result = v1 / v2;
	pushOperandFloat(operandStack, result);
	return 0;
}

Instruction * FDIV(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_FDIV;
	return inst;
}


// Divide int
static int32_t execute_IDIV(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t v2 = popOperandInt(operandStack);
	int32_t v1 = popOperandInt(operandStack);
	if (v2 == 0)
	{
		printf("java.lang.ArithmeticException: / by zero");
		exit(1);
	}

	int32_t result = v1 / v2;
	pushOperandInt(operandStack, result);
	return 0;
}

Instruction * IDIV(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_IDIV;
	return inst;
}

// Divide long
static int32_t execute_LDIV(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int64_t v2 = popOperandLong(operandStack);
	int64_t v1 = popOperandLong(operandStack);
	if (v2 == 0)
	{
		printf("java.lang.ArithmeticException: / by zero");
		exit(1);
	}

	int64_t result = v1 / v2;
	pushOperandLong(operandStack, result);
	return 0;
}

Instruction * LDIV(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LDIV;
	return inst;
}
