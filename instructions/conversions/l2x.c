#include "../factory.h"
#include "../../rtda/operand_stack.h"


// Convert long to double
static int32_t execute_L2D(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int64_t l = popOperandLong(operandStack);
	double f = (double)l;
	pushOperandDouble(operandStack, f);
	return 0;
}

Instruction * L2D(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_L2D;
	return inst;
}

// Convert long to float
static int32_t execute_L2F(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int64_t l = popOperandLong(operandStack);
	float f = (float)l;
	pushOperandFloat(operandStack, f);
	return 0;
}

Instruction * L2F(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_L2F;
	return inst;
}

// Convert long to int
static int32_t execute_L2I(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int64_t l = popOperandLong(operandStack);
	int32_t i = (int32_t)l;
	//printf("L22I L:%x\n", l);
	printf("L22I l:%d i:%d s:%d\n",i,operandStack->size);
	pushOperandInt(operandStack, i);
	return 0;
}

Instruction * L2I(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_L2I;
	return inst;
}
