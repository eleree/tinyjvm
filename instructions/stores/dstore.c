#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

// Store long into local variable
int32_t _dstore(Frame * frame, int32_t index)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	double val = popOperandDouble(operandStack);
	setLocalVarsDouble(localVars, index, val);
	return 0;
}

static int32_t execute_DSTORE(Frame * frame, struct InsturctionData * instData)
{
	return _dstore(frame, instData->index);
}

Instruction * DSTORE(Instruction * inst)
{
	inst->fetchOperands = index8InstructionFetchOperands;
	inst->execute = execute_DSTORE;
	return inst;
}

static int32_t  execute_DSTORE_0(Frame * frame, struct InsturctionData * instData)
{
	return _dstore(frame, 0);
}

Instruction * DSTORE_0(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DSTORE_0;
	return inst;
}

static int32_t  execute_DSTORE_1(Frame * frame, struct InsturctionData * instData)
{
	return _dstore(frame, 1);
}

Instruction * DSTORE_1(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DSTORE_1;
	return inst;
}

static int32_t  execute_DSTORE_2(Frame * frame, struct InsturctionData * instData)
{
	return _dstore(frame, 2);
}

Instruction * DSTORE_2(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DSTORE_2;
	return inst;
}

static int32_t  execute_DSTORE_3(Frame * frame, struct InsturctionData * instData)
{
	return _dstore(frame, 3);
}

Instruction * DSTORE_3(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DSTORE_3;
	return inst;
}


