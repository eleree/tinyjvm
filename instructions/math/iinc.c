#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

typedef struct IINCData{
	uint32_t Index;
	int32_t Const;
}IINCData;

static IINCData iincData;

static int32_t fetchOperands_IINC(BytecodeReader * bytecoderReader, InstructionData * instData)
{
	iincData.Index = readBytecodeInt8(bytecoderReader);
	iincData.Const = readBytecodeInt8(bytecoderReader);
	return 0;
}

static int32_t execute_IINC(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	int32_t val = getLocalVarsInt(localVars, iincData.Index);
	val += iincData.Const;
	setLocalVarsInt(localVars, iincData.Index, val);
	return 0;
}

Instruction * IINC(Instruction * inst)
{
	inst->fetchOperands = fetchOperands_IINC;
	inst->execute = execute_IINC;
	return inst;
}