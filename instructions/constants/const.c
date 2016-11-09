#include "../factory.h"
#include "../../rtda/operand_stack.h"

// Push double
static int32_t execute_ACONST_NULL(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	pushOperandRef(operandStack, NULL);
	return 0;
}

Instruction * ACONST_NULL(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ACONST_NULL;
	return inst;
}


static int32_t execute_DCONST_0(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	pushOperandDouble(operandStack, 0.0);
	return 0;
}

Instruction * DCONST_0(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DCONST_0;
	return inst;
}

static int32_t execute_DCONST_1(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	pushOperandDouble(operandStack, 1.0);
	return 0;
}

Instruction * DCONST_1(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DCONST_1;
	return inst;
}

// Push float
static int32_t execute_FCONST_0(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	pushOperandFloat(operandStack, 0.0);
	return 0;
}

Instruction * FCONST_0(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_FCONST_0;
	return inst;
}

static int32_t execute_FCONST_1(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	pushOperandFloat(operandStack, 1.0);
	return 0;
}

Instruction * FCONST_1(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_FCONST_1;
	return inst;
}

static int32_t execute_FCONST_2(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	pushOperandFloat(operandStack, 2.0);
	return 0;
}

Instruction * FCONST_2(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_FCONST_2;
	return inst;
}

// Push int constant
static int32_t execute_ICONST_M1(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	pushOperandInt(operandStack, -1);
	return 0;
}

Instruction * ICONST_M1(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ICONST_M1;
	return inst;
}

static int32_t execute_ICONST_0(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	pushOperandInt(operandStack, 0);
	return 0;
}

Instruction * ICONST_0(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ICONST_0;
	return inst;
}

static int32_t execute_ICONST_1(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	pushOperandInt(operandStack, 1);
	return 0;
}

Instruction * ICONST_1(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ICONST_1;
	return inst;
}


static int32_t execute_ICONST_2(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	pushOperandInt(operandStack, 2);
	return 0;
}

Instruction * ICONST_2(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ICONST_2;
	return inst;
}

static int32_t execute_ICONST_3(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	pushOperandInt(operandStack, 3);
	return 0;
}

Instruction * ICONST_3(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ICONST_3;
	return inst;
}

static int32_t execute_ICONST_4(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	pushOperandInt(operandStack, 4);
	return 0;
}

Instruction * ICONST_4(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ICONST_4;
	return inst;
}

static int32_t execute_ICONST_5(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	pushOperandInt(operandStack, 5);
	return 0;
}

Instruction * ICONST_5(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ICONST_5;
	return inst;
}

// Push long constant
static int32_t execute_LCONST_0(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	pushOperandLong(operandStack, 0);
	return 0;
}

Instruction * LCONST_0(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LCONST_0;
	return inst;
}

static int32_t execute_LCONST_1(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	pushOperandLong(operandStack, 1);
	return 0;
}

Instruction * LCONST_1(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LCONST_1;
	return inst;
}