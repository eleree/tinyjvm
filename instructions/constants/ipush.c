#include "../factory.h"
#include "../../rtda/operand_stack.h"

static int32_t value = 0;

static int32_t fetchOperands_BIPUSH(BytecodeReader * bytecoderReader, InstructionData * instData)
{
	value = readBytecodeInt8(bytecoderReader);
	return 0;
}

static int32_t execute_BIPUSH(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	pushOperandInt(operandStack, value);
	return 0;
}

Instruction * BIPUSH(Instruction * inst)
{
	inst->fetchOperands = fetchOperands_BIPUSH;
	inst->execute = execute_BIPUSH;
	return inst;
}

static int32_t fetchOperands_SIPUSH(BytecodeReader * bytecoderReader, InstructionData * instData)
{
	value = readBytecodeInt16(bytecoderReader);
	return 0;
}

static int32_t execute_SIPUSH(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	pushOperandInt(operandStack, value);
	return 0;
}

Instruction * SIPUSH(Instruction * inst)
{
	inst->fetchOperands = fetchOperands_SIPUSH;
	inst->execute = execute_SIPUSH;
	return inst;
}