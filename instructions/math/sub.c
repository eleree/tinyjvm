#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

// Subtract double
static int32_t execute_DSUB(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	double v2 = popOperandDouble(operandStack);
	double v1 = popOperandDouble(operandStack);
	double result = v1 - v2;
	pushOperandDouble(operandStack, result);
	return 0;
}

Instruction * DSUB(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DSUB;
	return inst;
}

// Subtract float
static int32_t execute_FSUB(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	float v2 = popOperandFloat(operandStack);
	float v1 = popOperandFloat(operandStack);
	float result = v1 - v2;
	pushOperandFloat(operandStack, result);
	return 0;
}

Instruction * FSUB(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_FSUB;
	return inst;
}

// Subtract int
static int32_t execute_ISUB(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t v2 = popOperandInt(operandStack);
	int32_t v1 = popOperandInt(operandStack);
	int32_t result = v1 - v2;
#if ENABLE_INST_LOCALVAR_DEBUG
	printf("ISUB v1:%d v2:%d result:%d\n", v1, v2, result);
#endif
	pushOperandInt(operandStack, result);
	return 0;
}

Instruction * ISUB(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ISUB;
	return inst;
}

// Subtract long
static int32_t execute_LSUB(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int64_t v2 = popOperandLong(operandStack);
	int64_t v1 = popOperandLong(operandStack);
	int64_t result = v1 - v2;
	pushOperandLong(operandStack, result);
	return 0;
}

Instruction * LSUB(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LSUB;
	return inst;
}