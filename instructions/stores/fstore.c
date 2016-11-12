#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

// Store long into local variable
int32_t _fstore(Frame * frame, int32_t index)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	float val = popOperandFloat(operandStack);
	setLocalVarsFloat(localVars, index, val);
	return 0;
}

static int32_t execute_FSTORE(Frame * frame, struct InsturctionData * instData)
{
	return _fstore(frame, instData->index);
}

Instruction * FSTORE(Instruction * inst)
{
	inst->fetchOperands = index8InstructionFetchOperands;
	inst->execute = execute_FSTORE;
	return inst;
}

static int32_t  execute_FSTORE_0(Frame * frame, struct InsturctionData * instData)
{
	return _fstore(frame, 0);
}

Instruction * FSTORE_0(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_FSTORE_0;
	return inst;
}

static int32_t  execute_FSTORE_1(Frame * frame, struct InsturctionData * instData)
{
	return _fstore(frame, 1);
}

Instruction * FSTORE_1(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_FSTORE_1;
	return inst;
}

static int32_t  execute_FSTORE_2(Frame * frame, struct InsturctionData * instData)
{
	return _fstore(frame, 2);
}

Instruction * FSTORE_2(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_FSTORE_2;
	return inst;
}

static int32_t  execute_FSTORE_3(Frame * frame, struct InsturctionData * instData)
{
	return _fstore(frame, 3);
}

Instruction * FSTORE_3(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_FSTORE_3;
	return inst;
}


