#include "../factory.h"
#include "../../rtda/operand_stack.h"

static int32_t fcmp(Frame *frame, InstructionData * instData, bool gFlag)
{
	OperandStack * operandStack = frame->operandStack;
	float v2 = popOperandFloat(operandStack);
	float v1 = popOperandFloat(operandStack);

	if (v1 > v2){
		pushOperandInt(operandStack, 1);
	}
	else if (v1 == v2){
		pushOperandInt(operandStack, 0);
	}
	else if (v1 < v2){
		pushOperandInt(operandStack, -1);
	}
	else if (gFlag){
		pushOperandInt(operandStack, 1);
	}
	else {
		pushOperandInt(operandStack, -1);
	}
	return 0;
}

static int32_t execute_fcmpl(Frame * frame, struct InsturctionData * instData)
{
	fcmp(frame, instData, false);
	return 0;
}

static int32_t execute_fcmpg(Frame * frame, struct InsturctionData * instData)
{
	fcmp(frame, instData, true);
	return 0;
}

Instruction * FCMPL(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_fcmpl;
	return inst;
}

Instruction * FCMPG(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_fcmpg;
	return inst;
}
