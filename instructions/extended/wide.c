#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

static int32_t opcode = 0;
static int32_t wIndex = 0;
static int32_t wConst = 0;

// Extend local variable index by additional bytes
static int32_t fetchOperands_WIDE(BytecodeReader * bytecoderReader, InstructionData * instData)
{
	
	opcode = readBytecodeUint8(bytecoderReader);
	switch (opcode)
	{
	case 0x15:
	case 0x16:
	case 0x17:
	case 0x18:
	case 0x19:
	case 0x36:
	case 0x37:
	case 0x38:
	case 0x39:
	case 0x3a:
		instData->index = readBytecodeUint16(bytecoderReader);
		break;
	case 0x84:
		wIndex = readBytecodeUint16(bytecoderReader);
		wConst = readBytecodeInt16(bytecoderReader);
		break;
	case 0xa9:
		printf("Unsupported opcode: 0xa9!\n");
		exit(-1);
	default:
		break;
	}
	return 0;
}


static int32_t execute_WIDE_IINC(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	int32_t val = getLocalVarsInt(localVars, wIndex);
	val += wConst;
	printf("Wide: index:%d,const %d\n", wIndex, wConst);
	setLocalVarsInt(localVars, wIndex, val);
	return 0;
}

static int32_t execute_WIDE(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	Instruction * instruction = newInsturction(opcode);
	switch (opcode)
	{
	case 0x15:
	case 0x16:
	case 0x17:
	case 0x18:
	case 0x19:
	case 0x36:
	case 0x37:
	case 0x38:
	case 0x39:
	case 0x3a:
		printf("Wide Error\n");
		exit(-2);
		break;
	case 0x84:
		execute_WIDE_IINC(frame, NULL);
		break;
	case 0xa9:
		break;
	}
	return 0;
}


Instruction * WIDE(Instruction * inst)
{
	inst->fetchOperands = fetchOperands_WIDE;
	inst->execute = execute_WIDE;

	return inst;
}