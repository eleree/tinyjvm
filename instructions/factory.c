#include "factory.h"
#include "instructions.h"

static Insturction instruction;

int32_t noOperandsInstructionFetchOperands(BytecodeReader * bytecoderReader, InsturctionData * instData)
{
	return 0;
}

int32_t branchInstructionFetchOperands(BytecodeReader * bytecoderReader, InsturctionData * instData)
{
	instData->offset = readBytecodeInt16(bytecoderReader);
	return 0;
}

int32_t index8InstructionFetchOperands(BytecodeReader * bytecoderReader, InsturctionData * instData)
{
	instData->index = readBytecodeUint8(bytecoderReader);
	return 0;
}

int32_t index16InstructionFetchOperands(BytecodeReader * bytecoderReader, InsturctionData * instData)
{
	instData->index = readBytecodeUint16(bytecoderReader);
	return 0;
}


Insturction * newInsturction(uint8_t opcode)
{
	switch (opcode)
	{
	case 0x00:
		return nop(&instruction);
		break;
	case 0x01:
		break;
	case 0x02:
		break;
	case 0x03:
		break;
	case 0x04:
		break;
	case 0x05:
		break;
	case 0x06:
		break;
	case 0x97:
		return dcmpl(&instruction);
	}
	return NULL;
}