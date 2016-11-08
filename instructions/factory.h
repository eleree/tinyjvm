#ifndef __TINY_JVM_FACTORY_H__
#define __TINY_JVM_FACTORY_H__

#include <stdint.h>
#include <stdbool.h>
#include "base\bytecode_reader.h"

struct InsturctionData;
struct Insturction;

typedef int32_t(*FetchOperandsFunc)(BytecodeReader * bytecodeReader, struct InsturctionData * instData);
typedef int32_t(*ExecuteFunc)(Frame * frame, struct InsturctionData * instData);

typedef struct InsturctionData
{
	uint8_t opcode;
	int32_t offset;
	int32_t index;
}InsturctionData;

typedef struct Insturction{
	FetchOperandsFunc fetchOperands;
	ExecuteFunc execute;
}Insturction;

int32_t noOperandsInstructionFetchOperands(BytecodeReader * bytecoderReader, InsturctionData * instData);
int32_t branchInstructionFetchOperands(BytecodeReader * bytecoderReader, InsturctionData * instData);
int32_t index8InstructionFetchOperands(BytecodeReader * bytecoderReader, InsturctionData * instData);
int32_t index16InstructionFetchOperands(BytecodeReader * bytecoderReader, InsturctionData * instData);

#endif
