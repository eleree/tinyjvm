#include "bytecode_reader.h"

void resetBytecodeReader(BytecodeReader * bytecodeReader,uint8_t * bytecode, uint32_t bytecodeLen, int32_t pc)
{
	bytecodeReader->code = bytecode;
	bytecodeReader->codeLen = bytecodeLen;
	bytecodeReader->pc = pc;
}

int32_t getBytecodeReaderPC(BytecodeReader * bytecodeReader)
{
	return bytecodeReader->pc;
}

int8_t readBytecodeInt8(BytecodeReader * bytecodeReader)
{
	int8_t data = bytecodeReader->code[bytecodeReader->pc];
	bytecodeReader->pc++;
	return data;
}

uint8_t readBytecodeUint8(BytecodeReader * bytecodeReader)
{
	uint8_t data = bytecodeReader->code[bytecodeReader->pc];
	bytecodeReader->pc++;
	return data;
}

uint16_t readBytecodeUint16(BytecodeReader * bytecodeReader)
{
	uint8_t high = readBytecodeUint8(bytecodeReader);
	uint8_t low = readBytecodeUint8(bytecodeReader);
	return high << 8 | low;
}

int16_t readBytecodeInt16(BytecodeReader * bytecodeReader)
{
	return readBytecodeUint16(bytecodeReader);
}

uint32_t readBytecodeUint32(BytecodeReader * bytecodeReader)
{
	uint8_t byte1 = readBytecodeUint8(bytecodeReader);
	uint8_t byte2 = readBytecodeUint8(bytecodeReader);
	uint8_t byte3 = readBytecodeUint8(bytecodeReader);
	uint8_t byte4 = readBytecodeUint8(bytecodeReader);
	return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

int32_t readBytecodeInt32(BytecodeReader * bytecodeReader)
{
	return readBytecodeUint32(bytecodeReader);
}

int32_t * readBytecodeInt32s(BytecodeReader * bytecodeReader, int32_t * int32Data, int32_t int32Count)
{
	for (int32_t i = 0; i < int32Count; i++)
	{
		int32Data[i] = readBytecodeInt32(bytecodeReader);
	}
	return int32Data;
}

void skipBytecodePadding(BytecodeReader * bytecodeReader)
{
	while (bytecodeReader->pc % 4 != 0)
		readBytecodeInt8(bytecodeReader);
}