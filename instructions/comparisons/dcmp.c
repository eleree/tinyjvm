#include "../factory.h"
#include "../../rtda/operand_stack.h"

static int32_t dcmp(Frame *frame, InstructionData * instData, bool gFlag)
{
	OperandStack * operandStack = frame->operandStack;
	double v2 = popOperandDouble(operandStack);
	double v1 = popOperandDouble(operandStack);

	if (v1 > v2){		
		pushOperandInt(operandStack,1);
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

static int32_t execute_dcmpl(Frame * frame, struct InsturctionData * instData)
{
	dcmp(frame, instData, false);
	return 0;
}

static int32_t execute_dcmpg(Frame * frame, struct InsturctionData * instData)
{
	dcmp(frame, instData, true);
	return 0;
}

Instruction * DCMPL(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_dcmpl;
	return inst;
}

Instruction * DCMPG(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_dcmpg;
	return inst;
}
