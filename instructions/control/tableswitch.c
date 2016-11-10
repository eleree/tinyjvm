#include "../factory.h"
#include "../../rtda/operand_stack.h"

/*
tableswitch
<0-3 byte pad>
defaultbyte1
defaultbyte2
defaultbyte3
defaultbyte4
lowbyte1
lowbyte2
lowbyte3
lowbyte4
highbyte1
highbyte2
highbyte3
highbyte4
jump offsets...
*/
// Access jump table by index and jump
typedef struct TableSwitchData{
	int32_t defaultOffset;
	int32_t low;
	int32_t high;
	int32_t * jumpOffsets;
}TableSwitchData;

static TableSwitchData tableSwitchData;


static int32_t fetchOperands_TABLE_SWITCH(BytecodeReader * bytecoderReader, InstructionData * instData)
{
	skipBytecodePadding(bytecoderReader);
	tableSwitchData.defaultOffset = readBytecodeInt32(bytecoderReader);
	tableSwitchData.low = readBytecodeInt32(bytecoderReader);
	tableSwitchData.high = readBytecodeInt32(bytecoderReader);
	int32_t jumpOffsetsCount = tableSwitchData.high - tableSwitchData.low + 1;
	tableSwitchData.jumpOffsets = calloc(jumpOffsetsCount, sizeof(int32_t));

	readBytecodeInt32s(bytecoderReader, tableSwitchData.jumpOffsets, jumpOffsetsCount);
	return 0;
}

static int32_t execute_TABLE_SWITCH(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t index = popOperandInt(operandStack);
	int32_t offset = 0;

	if (index >= tableSwitchData.low && index <= tableSwitchData.high)
		offset = tableSwitchData.jumpOffsets[index - tableSwitchData.low];
	else
		offset = tableSwitchData.defaultOffset;

	branch(frame, offset);

	free(tableSwitchData.jumpOffsets);
	return 0;
}

Instruction * TABLE_SWITCH(Instruction * inst)
{
	inst->fetchOperands = fetchOperands_TABLE_SWITCH;
	inst->execute = execute_TABLE_SWITCH;
	return inst;
}