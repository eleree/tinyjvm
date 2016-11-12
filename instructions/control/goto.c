#include "../factory.h"

static int32_t execute_GOTO(Frame * frame, struct InsturctionData * instData)
{
	branch(frame, instData->offset);
	return 0;
}

Instruction * GOTO(Instruction * inst)
{
	inst->fetchOperands = branchInstructionFetchOperands;
	inst->execute = execute_GOTO;
	return inst;
}
