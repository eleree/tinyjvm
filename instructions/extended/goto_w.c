#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

static int32_t offset = 0;
// Branch always (wide index)
static int32_t fetchOperands_GOTO_W(BytecodeReader * bytecoderReader, InstructionData * instData)
{
	offset = readBytecodeInt32(bytecoderReader);
	return 0;
}

static int32_t execute_GOTO_W(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	branch(frame, offset);
	return 0;
}

Instruction * GOTO_W(Instruction * inst)
{
	inst->fetchOperands = fetchOperands_GOTO_W;
	inst->execute = execute_GOTO_W;
	return inst;
}