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
}InstructionData;

typedef struct Insturction{
	FetchOperandsFunc fetchOperands;
	ExecuteFunc execute;
}Instruction;

Instruction * newInsturction(uint8_t opcode);
void branch(Frame * frame, int32_t offset);

int32_t noOperandsInstructionFetchOperands(BytecodeReader * bytecoderReader, InstructionData * instData);
int32_t branchInstructionFetchOperands(BytecodeReader * bytecoderReader, InstructionData * instData);
int32_t index8InstructionFetchOperands(BytecodeReader * bytecoderReader, InstructionData * instData);
int32_t index16InstructionFetchOperands(BytecodeReader * bytecoderReader, InstructionData * instData);

#endif
