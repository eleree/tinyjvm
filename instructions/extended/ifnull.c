#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

// Branch if reference is null
static int32_t execute_IFNULL(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	Object * ref = popOperandRef(operandStack);
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

static int32_t execute_IFNONNULL(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	Object * ref = popOperandRef(operandStack);
	if (ref != NULL)
		branch(frame, instData->offset);
	return 0;
}

Instruction * IFNONNULL(Instruction * inst)
{
	inst->fetchOperands = branchInstructionFetchOperands;
	inst->execute = execute_IFNONNULL;
	return inst;
}