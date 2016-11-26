#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/frame.h"
#include "../../rtda/heap/slot.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"
#include "../../rtda/heap/field.h"
#include "../../rtda/heap/cp_fieldref.h"

// Get static field from class
static int32_t execute_GET_STATIC(Frame * frame, struct InsturctionData * instData)
{
	ConstantPoolItem * cp = frame->method->classMember.attachClass->constantPool.constantPoolItem;
	FieldRef * fieldRef = getClassConstantPoolFieldRef(cp, instData->index);
	Field * field = resolvedField(fieldRef);
	Class * c = field->classMember.attachClass;

	if (!c->initStarted)
	{
		revertFrameNextPC(frame);
		InitClass(frame->thread, c);
		return 0;
	}

	if(!isFieldStatic(field))
	{
		printf("java.lang.IncompatibleClassChangeError\n");
		exit(-1);
	}	

	char * descriptor = field->classMember.descriptor;
	uint16_t slotId = field->slotId;
	Slot * slots = c->staticVars;
	OperandStack * operandStack = frame->operandStack;

	switch(descriptor[0])
	{
	case 'Z':
	case 'B':
	case 'C':
	case 'S':
	case 'I':
		pushOperandInt(operandStack, getSlotInt(slots, slotId));
		break;
	case 'F':
		pushOperandFloat(operandStack, getSlotFloat(slots, slotId));
		break;
	case 'J':
		pushOperandLong(operandStack, getSlotLong(slots, slotId));
		break;
	case 'D':
		pushOperandDouble(operandStack, getSlotDouble(slots, slotId));
		break;
	case 'L':
	case '[':
		pushOperandRef(operandStack, getSlotRef(slots, slotId));
		break;
	default:
		break;
	}

	return 0;
}

Instruction * GET_STATIC(Instruction * inst)
{
	inst->fetchOperands = index16InstructionFetchOperands;
	inst->execute = execute_GET_STATIC;
	return inst;
}
