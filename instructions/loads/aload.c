#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"

int32_t _aload(Frame * frame, int32_t index)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	Object * val = getLocalVarsRef(localVars, index);
	pushOperandRef(operandStack, val);
	if (val!=NULL && val->dataType == 'R')
	{
		Slot * slots = (Slot *)val->data;
		for (uint16_t i = 0; i < val->dataCount; i++)
		{
			Slot * slot = slots + i;
			slot = slot;
		}
	}
	return 0;
}

int32_t execute_ALOAD(Frame * frame, struct InsturctionData * instData)
{
	return _aload(frame, instData->index);
}

Instruction * ALOAD(Instruction * inst)
{
	inst->fetchOperands = index8InstructionFetchOperands;
	inst->execute = execute_ALOAD;
	return inst;
}

static int32_t execute_ALOAD_0(Frame * frame, struct InsturctionData * instData)
{
	return _aload(frame, 0);
}

Instruction * ALOAD_0(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ALOAD_0;
	return inst;
}

static int32_t execute_ALOAD_1(Frame * frame, struct InsturctionData * instData)
{
	return _aload(frame, 1);
}

Instruction * ALOAD_1(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ALOAD_1;
	return inst;
}

static int32_t execute_ALOAD_2(Frame * frame, struct InsturctionData * instData)
{
	return _aload(frame, 2);
}

Instruction * ALOAD_2(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ALOAD_2;
	return inst;
}

static int32_t execute_ALOAD_3(Frame * frame, struct InsturctionData * instData)
{
	return _aload(frame, 3);
}

Instruction * ALOAD_3(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ALOAD_3;
	return inst;
}
