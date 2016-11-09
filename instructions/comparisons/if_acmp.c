#include "../factory.h"
#include "../../rtda/operand_stack.h"

static bool _acmp(Frame *frame, InstructionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	Object * ref2 = popOperandRef(operandStack);
	Object * ref1 = popOperandRef(operandStack);

	return ref2 == ref1; // todo, need to be Object compare

}

static int32_t execute_if_acmpeq(Frame * frame, struct InsturctionData * instData)
{
	if (_acmp(frame, instData))
	{
		branch(frame, instData->offset);
	}
	return 0;
}

static int32_t execute_if_acmpne(Frame * frame, struct InsturctionData * instData)
{
	if (!_acmp(frame, instData))
	{
		branch(frame, instData->offset);
	}
	return 0;
}

Instruction * IF_ACMPNE(Instruction * inst)
{
	inst->fetchOperands = branchInstructionFetchOperands;
	inst->execute = execute_if_acmpne;
	return inst;
}

Instruction * IF_ACMPEQ(Instruction * inst)
{
	inst->fetchOperands = branchInstructionFetchOperands;
	inst->execute = execute_if_acmpne;
	return inst;
}
