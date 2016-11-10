#include "../factory.h"
#include "../../rtda/operand_stack.h"

/*
lookupswitch
<0-3 byte pad>
defaultbyte1
defaultbyte2
defaultbyte3
defaultbyte4
npairs1
npairs2
npairs3
npairs4
match-offset pairs...
*/
// Access jump table by key match and jump
typedef struct LookSwitchData{
	int32_t defaultOffset;
	int32_t npairs;
	int32_t * matchOffsets;
}LookSwitchData;

static LookSwitchData lookSwitchData;

static int32_t fetchOperands_LOOKUP_SWITCH(BytecodeReader * bytecoderReader, InstructionData * instData)
{
	skipBytecodePadding(bytecoderReader);
	lookSwitchData.defaultOffset = readBytecodeInt32(bytecoderReader);
	lookSwitchData.npairs = readBytecodeInt32(bytecoderReader);
	lookSwitchData.matchOffsets = calloc(lookSwitchData.npairs * 2, sizeof(int32_t));
	readBytecodeInt32s(bytecoderReader, lookSwitchData.matchOffsets, lookSwitchData.npairs * 2);
	return 0;
}

static int32_t execute_LOOKUP_SWITCH(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t key = popOperandInt(operandStack);
	for (int32_t i = 0; i < lookSwitchData.npairs * 2; i += 2)
	{
		if (lookSwitchData.matchOffsets[i] == key)
		{
			int32_t offset = lookSwitchData.matchOffsets[i + 1];
			branch(frame, offset);
			free(lookSwitchData.matchOffsets);
			return 0;
		}
	}
	branch(frame, lookSwitchData.defaultOffset);
	free(lookSwitchData.matchOffsets);
	return 0;
}

Instruction * LOOKUP_SWITCH(Instruction * inst)
{
	inst->fetchOperands = fetchOperands_LOOKUP_SWITCH;
	inst->execute = execute_LOOKUP_SWITCH;
	return inst;
}