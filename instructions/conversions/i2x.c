#include "../factory.h"
#include "../../rtda/operand_stack.h"

// Convert int to byte
static int32_t execute_I2B(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t i = popOperandInt(operandStack);
	int8_t b = (int8_t)i;
	pushOperandInt(operandStack, b);
	return 0;
}

Instruction * I2B(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_I2B;
	return inst;
}

// Convert int to char
static int32_t execute_I2C(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t i = popOperandInt(operandStack);
	int16_t c = (int16_t)i;
	pushOperandInt(operandStack, c);
	return 0;
}

Instruction * I2C(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_I2C;
	return inst;
}

// Convert int to short
static int32_t execute_I2S(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t i = popOperandInt(operandStack);
	int16_t s = (int16_t)i;
	pushOperandInt(operandStack, s);
	return 0;
}

Instruction * I2S(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_I2S;
	return inst;
}

// Convert int to long
static int32_t execute_I2L(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t i = popOperandInt(operandStack);
	int64_t l = (int64_t)i;
	pushOperandLong(operandStack, l);
	return 0;
}

Instruction * I2L(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_I2L;
	return inst;
}

// Convert int to float
static int32_t execute_I2F(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t i = popOperandInt(operandStack);
	float f = (float)i;
	pushOperandFloat(operandStack, f);
	return 0;
}

Instruction * I2F(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_I2F;
	return inst;
}

// Convert int to double
static int32_t execute_I2D(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t i = popOperandInt(operandStack);
	double f = (double)i;
	pushOperandDouble(operandStack, f);
	return 0;
}

Instruction * I2D(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_I2D;
	return inst;
}