#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

// Store long into local variable
int32_t _astore(Frame * frame, int32_t index)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	Object * ref = popOperandRef(operandStack);
	setLocalVarsRef(localVars, index, ref);
	return 0;
}

static int32_t execute_ASTORE(Frame * frame, struct InsturctionData * instData)
{
	return _astore(frame, instData->index);
}

Instruction * ASTORE(Instruction * inst)
{
	inst->fetchOperands = index8InstructionFetchOperands;
	inst->execute = execute_ASTORE;
	return inst;
}

static int32_t  execute_ASTORE_0(Frame * frame, struct InsturctionData * instData)
{
	return _astore(frame, 0);
}

Instruction * ASTORE_0(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ASTORE_0;
	return inst;
}

static int32_t  execute_ASTORE_1(Frame * frame, struct InsturctionData * instData)
{
	return _astore(frame, 1);
}

Instruction * ASTORE_1(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ASTORE_1;
	return inst;
}

static int32_t  execute_ASTORE_2(Frame * frame, struct InsturctionData * instData)
{
	return _astore(frame, 2);
}

Instruction * ASTORE_2(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ASTORE_2;
	return inst;
}

static int32_t  execute_ASTORE_3(Frame * frame, struct InsturctionData * instData)
{
	return _astore(frame, 3);
}

Instruction * ASTORE_3(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ASTORE_3;
	return inst;
}


