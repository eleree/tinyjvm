#include "../factory.h"
#include "../../rtda/operand_stack.h"

static int32_t execute_IF_ICMPEQ(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t v2 = popOperandInt(operandStack);
	int32_t v1 = popOperandInt(operandStack);

	if (v1 == v2)
	{
		branch(frame, instData->offset);
	}

	return 0;
}
Instruction * IF_ICMPEQ(Instruction * inst)
{
	inst->fetchOperands = branchInstructionFetchOperands;
	inst->execute = execute_IF_ICMPEQ;
	return inst;
}


static int32_t execute_IF_ICMPNE(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t v2 = popOperandInt(operandStack);
	int32_t v1 = popOperandInt(operandStack);

	if (v1 != v2)
	{
		branch(frame, instData->offset);
	}

	return 0;
}
Instruction * IF_ICMPNE(Instruction * inst)
{
	inst->fetchOperands = branchInstructionFetchOperands;
	inst->execute = execute_IF_ICMPNE;
	return inst;
}

static int32_t execute_IF_CMPLT(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t v2 = popOperandInt(operandStack);
	int32_t v1 = popOperandInt(operandStack);

	if ( v1 < v2 )
	{
		branch(frame, instData->offset);
	}

	return 0;
}
Instruction * IF_ICMPLT(Instruction * inst)
{
	inst->fetchOperands = branchInstructionFetchOperands;
	inst->execute = execute_IF_CMPLT;
	return inst;
}

static int32_t execute_IF_ICMPLE(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t v2 = popOperandInt(operandStack);
	int32_t v1 = popOperandInt(operandStack);

	if (v1 <= v2)
	{
		branch(frame, instData->offset);
	}

	return 0;
}
Instruction * IF_ICMPLE(Instruction * inst)
{
	inst->fetchOperands = branchInstructionFetchOperands;
	inst->execute = execute_IF_ICMPLE;
	return inst;
}

static int32_t execute_IF_ICMPGT(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t v2 = popOperandInt(operandStack);
	int32_t v1 = popOperandInt(operandStack);

	if (v1 > v2)
	{
		branch(frame, instData->offset);
	}

	return 0;
}
Instruction * IF_ICMPGT(Instruction * inst)
{
	inst->fetchOperands = branchInstructionFetchOperands;
	inst->execute = execute_IF_ICMPGT;
	return inst;
}


static int32_t execute_IF_ICMPGE(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t v2 = popOperandInt(operandStack);
	int32_t v1 = popOperandInt(operandStack);

	if (v1 >= v2)
	{
		branch(frame, instData->offset);
	}

	return 0;
}
Instruction * IF_ICMPGE(Instruction * inst)
{
	inst->fetchOperands = branchInstructionFetchOperands;
	inst->execute = execute_IF_ICMPGE;
	return inst;
}