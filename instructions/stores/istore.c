#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

// Store int into local variable
int32_t _istore(Frame * frame, int32_t index)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	int32_t val = popOperandInt(operandStack);
	//printf("_istore %d\n", val);
	//if (val == 260046848)
	//{
	//	printf("aa");
	//}
	setLocalVarsInt(localVars, index, val);
	return 0;
}

static int32_t execute_ISTORE(Frame * frame, struct InsturctionData * instData)
{
	return _istore(frame, instData->index);
}

Instruction * ISTORE(Instruction * inst)
{
	inst->fetchOperands = index8InstructionFetchOperands;
	inst->execute = execute_ISTORE;
	return inst;
}

static int32_t  execute_ISTORE_0(Frame * frame, struct InsturctionData * instData)
{
	return _istore(frame, 0);
}

Instruction * ISTORE_0(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ISTORE_0;
	return inst;
}

static int32_t  execute_ISTORE_1(Frame * frame, struct InsturctionData * instData)
{
	return _istore(frame, 1);
}

Instruction * ISTORE_1(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ISTORE_1;
	return inst;
}

static int32_t  execute_ISTORE_2(Frame * frame, struct InsturctionData * instData)
{
	return _istore(frame, 2);
}

Instruction * ISTORE_2(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ISTORE_2;
	return inst;
}

static int32_t  execute_ISTORE_3(Frame * frame, struct InsturctionData * instData)
{
	return _istore(frame, 3);
}

Instruction * ISTORE_3(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ISTORE_3;
	return inst;
}


