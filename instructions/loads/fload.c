#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

// _fload has beed defined in LIBCMTD.lib
int32_t fload(Frame * frame, int32_t index)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	float val = getLocalVarsFloat(localVars, index);
	pushOperandFloat(operandStack, val);
	return 0;
}

int32_t execute_FLOAD(Frame * frame, struct InsturctionData * instData)
{
	return fload(frame, instData->index);
}

Instruction * FLOAD(Instruction * inst)
{
	inst->fetchOperands = index8InstructionFetchOperands;
	inst->execute = execute_FLOAD;
	return inst;
}

static int32_t execute_FLOAD_0(Frame * frame, struct InsturctionData * instData)
{
	return fload(frame, 0);
}

Instruction * FLOAD_0(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_FLOAD_0;
	return inst;
}

static int32_t execute_FLOAD_1(Frame * frame, struct InsturctionData * instData)
{
	return fload(frame, 1);
}

Instruction * FLOAD_1(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_FLOAD_1;
	return inst;
}

static int32_t execute_FLOAD_2(Frame * frame, struct InsturctionData * instData)
{
	return fload(frame, 2);
}

Instruction * FLOAD_2(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_FLOAD_2;
	return inst;
}

static int32_t execute_FLOAD_3(Frame * frame, struct InsturctionData * instData)
{
	return fload(frame, 3);
}

Instruction * FLOAD_3(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_FLOAD_3;
	return inst;
}
