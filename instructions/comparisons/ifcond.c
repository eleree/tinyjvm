#include "../factory.h"
#include "../../rtda/operand_stack.h"


static int32_t execute_IFEQ(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t val = popOperandInt(operandStack);
	if (val == 0)
		branch(frame, instData->offset);
	return 0;
}
Instruction * IFEQ(Instruction * inst)
{
	inst->fetchOperands = branchInstructionFetchOperands;
	inst->execute = execute_IFEQ;
	return inst;
}

static int32_t execute_IFNE(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t val = popOperandInt(operandStack);
	if (val != 0)
		branch(frame, instData->offset);
	return 0;
}
Instruction * IFNE(Instruction * inst)
{
	inst->fetchOperands = branchInstructionFetchOperands;
	inst->execute = execute_IFNE;
	return inst;
}

static int32_t execute_IFLT(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t val = popOperandInt(operandStack);
	if (val < 0)
		branch(frame, instData->offset);
	return 0;
}
Instruction * IFLT(Instruction * inst)
{
	inst->fetchOperands = branchInstructionFetchOperands;
	inst->execute = execute_IFLT;
	return inst;
}

static int32_t execute_IFLE(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t val = popOperandInt(operandStack);
	if (val <= 0)
		branch(frame, instData->offset);
	return 0;
}
Instruction * IFLE(Instruction * inst)
{
	inst->fetchOperands = branchInstructionFetchOperands;
	inst->execute = execute_IFLE;
	return inst;
}

static int32_t execute_IFGT(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t val = popOperandInt(operandStack);
	if (val > 0)
		branch(frame, instData->offset);
	return 0;
}
Instruction * IFGT(Instruction * inst)
{
	inst->fetchOperands = branchInstructionFetchOperands;
	inst->execute = execute_IFGT;
	return inst;
}

static int32_t execute_IFGE(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t val = popOperandInt(operandStack);
	if (val >= 0)
		branch(frame, instData->offset);
	return 0;
}
Instruction * IFGE(Instruction * inst)
{
	inst->fetchOperands = branchInstructionFetchOperands;
	inst->execute = execute_IFGE;
	return inst;
}

