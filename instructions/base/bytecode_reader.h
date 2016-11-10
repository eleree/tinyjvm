#ifndef __TINY_JVM_BYTECODE_READER_H__
#define __TINY_JVM_BYTECODE_READER_H__

#include "../../rtda/rtda.h"

typedef struct BytecodeReader
{
	uint32_t codeLen;
	uint8_t * code;
	int32_t pc;
}BytecodeReader;

void resetBytecodeReader(BytecodeReader * bytecodeReader, uint8_t * bytecode, uint32_t bytecodeLen, int32_t pc);
int32_t getBytecodeReaderPC(BytecodeReader * bytecodeReader);
int8_t readBytecodeInt8(BytecodeReader * bytecodeReader);
uint8_t readBytecodeUint8(BytecodeReader * bytecodeReader);
uint16_t readBytecodeUint16(BytecodeReader * bytecodeReader);
int16_t readBytecodeInt16(BytecodeReader * bytecodeReader);
int32_t readBytecodeInt32(BytecodeReader * bytecodeReader);
uint32_t readBytecodeUint32(BytecodeReader * bytecodeReader);
int32_t * readBytecodeInt32s(BytecodeReader * bytecodeReader, int32_t * int32Data, int32_t int32Count);
void skipBytecodePadding(BytecodeReader * bytecodeReader);
#endif