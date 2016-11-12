#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

int32_t _lload(Frame * frame, int32_t index)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	int64_t val = getLocalVarsLong(localVars, index);
	pushOperandLong(operandStack, val);
	return 0;
}

int32_t execute_LLOAD(Frame * frame, struct InsturctionData * instData)
{
	return _lload(frame, instData->index);
}

Instruction * LLOAD(Instruction * inst)
{
	inst->fetchOperands = index8InstructionFetchOperands;
	inst->execute = execute_LLOAD;
	return inst;
}

static int32_t execute_LLOAD_0(Frame * frame, struct InsturctionData * instData)
{
	return _lload(frame, 0);
}

Instruction * LLOAD_0(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LLOAD_0;
	return inst;
}

static int32_t execute_LLOAD_1(Frame * frame, struct InsturctionData * instData)
{
	return _lload(frame, 1);
}

Instruction * LLOAD_1(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LLOAD_1;
	return inst;
}

static int32_t execute_LLOAD_2(Frame * frame, struct InsturctionData * instData)
{
	return _lload(frame, 2);
}

Instruction * LLOAD_2(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LLOAD_2;
	return inst;
}

static int32_t execute_LLOAD_3(Frame * frame, struct InsturctionData * instData)
{
	return _lload(frame, 3);
}

Instruction * LLOAD_3(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LLOAD_3;
	return inst;
}
