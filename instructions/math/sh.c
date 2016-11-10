#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

// Shift left int
static int32_t execute_ISHL(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t v2 = popOperandInt(operandStack);
	int32_t v1 = popOperandInt(operandStack);
	uint8_t s = v2 & 0x1F;
	int32_t result = v1 << s;
	pushOperandInt(operandStack, result);
	return 0;
}

Instruction * ISHL(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ISHL;
	return inst;
}

// Arithmetic shift right int
static int32_t execute_ISHR(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t v2 = popOperandInt(operandStack);
	int32_t v1 = popOperandInt(operandStack);
	uint8_t s = v2 & 0x1F;
	int32_t result = v1 >> s;
	pushOperandInt(operandStack, result);
	return 0;
}

Instruction * ISHR(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ISHR;
	return inst;
}

// Logical shift right int
static int32_t execute_IUSHR(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t v2 = popOperandInt(operandStack);
	int32_t v1 = popOperandInt(operandStack);
	uint8_t s = v2 & 0x1F;
	int32_t result = (int32_t)( ((uint32_t) v1) >> s);
	pushOperandInt(operandStack, result);
	return 0;
}

Instruction * IUSHR(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_IUSHR;
	return inst;
}

// Shift left long
static int32_t execute_LSHL(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t v2 = popOperandInt(operandStack);
	int64_t v1 = popOperandLong(operandStack);
	uint8_t s = v2 & 0x3F;
	int64_t result = v1 << s;
	pushOperandLong(operandStack, result);
	return 0;
}

Instruction * LSHL(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LSHL;
	return inst;
}


// Arithmetic shift right long
static int32_t execute_LSHR(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t v2 = popOperandInt(operandStack);
	int64_t v1 = popOperandLong(operandStack);
	uint8_t s = v2 & 0x3F;
	int64_t result = v1 >> s;
	pushOperandLong(operandStack, result);
	return 0;
}

Instruction * LSHR(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LSHR;
	return inst;
}

// Logical shift right long
static int32_t execute_LUSHR(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t v2 = popOperandInt(operandStack);
	int64_t v1 = popOperandLong(operandStack);
	uint8_t s = v2 & 0x3F;
	int64_t result = (int64_t)(((uint64_t)v1) >> s);
	pushOperandLong(operandStack, result);
	return 0;
}

Instruction * LUSHR(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LUSHR;
	return inst;
}