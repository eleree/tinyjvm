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
int8_t readBytecodeInt8(BytecodeReader * bytecodeReader);
uint8_t readBytecodeUint8(BytecodeReader * bytecodeReader);
uint16_t readBytecodeUint16(BytecodeReader * bytecodeReader);
int16_t readBytecodeInt16(BytecodeReader * bytecodeReader);
uint32_t readBytecodeUint32(BytecodeReader * bytecodeReader);
void skipBytecodePadding(BytecodeReader * bytecodeReader);
#endif