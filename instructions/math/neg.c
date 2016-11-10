#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

// Negate double
static int32_t execute_DNEG(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	double val = popOperandDouble(operandStack);
	pushOperandDouble(operandStack, -val);
	return 0;
}

Instruction * DNEG(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DNEG;
	return inst;
}

// Negate float
static int32_t execute_FNEG(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	float val = popOperandFloat(operandStack);
	pushOperandFloat(operandStack, -val);
	return 0;
}

Instruction * FNEG(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_FNEG;
	return inst;
}


// Negate int
static int32_t execute_INEG(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t val = popOperandInt(operandStack);
	pushOperandInt(operandStack, -val);
	return 0;
}

Instruction * INEG(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_INEG;
	return inst;
}

// Negate long
static int32_t execute_LNEG(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int64_t val = popOperandLong(operandStack);
	pushOperandLong(operandStack, -val);
	return 0;
}

Instruction * LNEG(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LNEG;
	return inst;
}



