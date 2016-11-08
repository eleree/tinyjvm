#include <stdint.h>
#include "base\bytecode_reader.h"

typedef int32_t (*FetchOperands)(BytecodeReader * bytecodeReader);
typedef int32_t (*Execute)(Frame * frame);

typedef struct Insturction
{
	uint8_t opcode;
	int32_t offset;
	int32_t index;
}Insturction;

int32_t noOperandsInstructionFetchOperands(BytecodeReader * bytecoderReader)
{

}

int32_t branchInstructionFetchOperands(BytecodeReader * bytecoderReader)
{

}

int32_t index8InstructionFetchOperands(BytecodeReader * bytecoderReader)
{

}

int32_t index16InstructionFetchOperands(BytecodeReader * bytecoderReader)
{

}


void newInsturction(uint8_t opcode)
{
	switch (opcode)
	{
	case 0x00:
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
	}
}