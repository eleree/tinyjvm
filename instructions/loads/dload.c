#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

int32_t _dload(Frame * frame, int32_t index)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	double val = getLocalVarsDouble(localVars, index);
	pushOperandDouble(operandStack, val);
	return 0;
}

int32_t execute_DLOAD(Frame * frame, struct InsturctionData * instData)
{
	return _dload(frame, instData->index);
}

Instruction * DLOAD(Instruction * inst)
{
	inst->fetchOperands = index8InstructionFetchOperands;
	inst->execute = execute_DLOAD;
	return inst;
}

static int32_t execute_DLOAD_0(Frame * frame, struct InsturctionData * instData)
{
	return _dload(frame, 0);
}

Instruction * DLOAD_0(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DLOAD_0;
	return inst;
}

static int32_t execute_DLOAD_1(Frame * frame, struct InsturctionData * instData)
{
	return _dload(frame, 1);
}

Instruction * DLOAD_1(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DLOAD_1;
	return inst;
}

static int32_t execute_DLOAD_2(Frame * frame, struct InsturctionData * instData)
{
	return _dload(frame, 2);
}

Instruction * DLOAD_2(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DLOAD_2;
	return inst;
}

static int32_t execute_DLOAD_3(Frame * frame, struct InsturctionData * instData)
{
	return _dload(frame, 3);
}

Instruction * DLOAD_3(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DLOAD_3;
	return inst;
}
