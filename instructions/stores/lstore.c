#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

// Store long into local variable
int32_t _lstore(Frame * frame, int32_t index)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	int64_t val = popOperandLong(operandStack);
	printf("_lstore:%lld\n", val);
	setLocalVarsLong(localVars, index, val);
	return 0;
}

static int32_t execute_LSTORE(Frame * frame, struct InsturctionData * instData)
{
	return _lstore(frame, instData->index);
}

Instruction * LSTORE(Instruction * inst)
{
	inst->fetchOperands = index8InstructionFetchOperands;
	inst->execute = execute_LSTORE;
	return inst;
}

static int32_t  execute_LSTORE_0(Frame * frame, struct InsturctionData * instData)
{
	return _lstore(frame, 0);
}

Instruction * LSTORE_0(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LSTORE_0;
	return inst;
}

static int32_t  execute_LSTORE_1(Frame * frame, struct InsturctionData * instData)
{
	return _lstore(frame, 1);
}

Instruction * LSTORE_1(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LSTORE_1;
	return inst;
}

static int32_t  execute_LSTORE_2(Frame * frame, struct InsturctionData * instData)
{
	return _lstore(frame, 2);
}

Instruction * LSTORE_2(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LSTORE_2;
	return inst;
}

static int32_t  execute_LSTORE_3(Frame * frame, struct InsturctionData * instData)
{
	return _lstore(frame, 3);
}

Instruction * LSTORE_3(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LSTORE_3;
	return inst;
}


