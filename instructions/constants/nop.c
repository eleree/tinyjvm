#include "../factory.h"

static int32_t execute(Frame * frame, struct InsturctionData * instData)
{
	return 0;
}

Insturction * nop(Insturction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute;
	return inst;
}
