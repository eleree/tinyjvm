#include "../factory.h"

static int32_t execute(Frame * frame, struct InsturctionData * instData)
{
	return 0;
}

Instruction * NOP(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute;
	return inst;
}
