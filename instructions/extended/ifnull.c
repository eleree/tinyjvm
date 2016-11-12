#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

static Object * ref = 0;
// Branch if reference is null
static int32_t execute_IFNULL(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	ref = popOperandRef(operandStack);
	if (ref == NULL)
		branch(frame, instData->offset);
	return 0;
}

Instruction * IFNULL(Instruction * inst)
{
	inst->fetchOperands = branchInstructionFetchOperands;
	inst->execute = execute_IFNULL;
	return inst;
}