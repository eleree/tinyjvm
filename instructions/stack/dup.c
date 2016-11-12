#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"


// Duplicate the top operand stack value
static int32_t execute_DUP(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	Slot * slot = popOperandSlot(operandStack);
	pushOperandSlot(operandStack,slot);
	pushOperandSlot(operandStack, slot);
	return 0;
}

Instruction * DUP(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DUP;
	return inst;
}

// Duplicate the top operand stack value and insert two values down
static int32_t execute_DUP_X1(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	Slot * slot1 = popOperandSlot(operandStack);
	Slot * slot2 = popOperandSlot(operandStack);
	pushOperandSlot(operandStack, slot1);
	pushOperandSlot(operandStack, slot2);
	pushOperandSlot(operandStack, slot1);
	return 0;
}

Instruction * DUP_X1(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DUP_X1;
	return inst;
}


// Duplicate the top operand stack value and insert two or three values down
static int32_t execute_DUP_X2(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	Slot * slot1 = popOperandSlot(operandStack);
	Slot * slot2 = popOperandSlot(operandStack);
	Slot * slot3 = popOperandSlot(operandStack);
	pushOperandSlot(operandStack, slot1);
	pushOperandSlot(operandStack, slot3);
	pushOperandSlot(operandStack, slot2);
	pushOperandSlot(operandStack, slot1);
	return 0;
}

Instruction * DUP_X2(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DUP_X2;
	return inst;
}


// Duplicate the top one or two operand stack values
static int32_t execute_DUP2(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	Slot * slot1 = popOperandSlot(operandStack);
	Slot * slot2 = popOperandSlot(operandStack);
	pushOperandSlot(operandStack, slot2);
	pushOperandSlot(operandStack, slot1);
	pushOperandSlot(operandStack, slot2);
	pushOperandSlot(operandStack, slot1);
	return 0;
}

Instruction * DUP2(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DUP2;
	return inst;
}

// Duplicate the top one or two operand stack values
static int32_t execute_DUP2_X1(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	Slot * slot1 = popOperandSlot(operandStack);
	Slot * slot2 = popOperandSlot(operandStack);
	Slot * slot3 = popOperandSlot(operandStack);

	pushOperandSlot(operandStack, slot2);		
	pushOperandSlot(operandStack, slot1);
	pushOperandSlot(operandStack, slot3);
	pushOperandSlot(operandStack, slot2);
	pushOperandSlot(operandStack, slot1);

	return 0;
}

Instruction * DUP2_X1(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DUP2_X1;
	return inst;
}

// Duplicate the top one or two operand stack values and insert two, three, or four values down
static int32_t execute_DUP2_X2(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	Slot * slot1 = popOperandSlot(operandStack);
	Slot * slot2 = popOperandSlot(operandStack);
	Slot * slot3 = popOperandSlot(operandStack);
	Slot * slot4 = popOperandSlot(operandStack);

	pushOperandSlot(operandStack, slot2);
	pushOperandSlot(operandStack, slot1);
	pushOperandSlot(operandStack, slot4);
	pushOperandSlot(operandStack, slot3);
	pushOperandSlot(operandStack, slot2);
	pushOperandSlot(operandStack, slot1);

	return 0;
}

Instruction * DUP2_X2(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DUP2_X2;
	return inst;
}