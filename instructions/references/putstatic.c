#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/slot.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"
#include "../../rtda/heap/field.h"
#include "../../rtda/heap/cp_fieldref.h"

// Set static field in class
static int32_t execute_PUT_STATIC(Frame * frame, struct InsturctionData * instData)
{
	Method * currentMethod = frame->method;
	Class * currentClass = currentMethod->classMember.attachClass;

	ConstantPoolItem * cp = frame->method->classMember.attachClass->constantPool.constantPoolItem;
	FieldRef * fieldRef = getClassConstantPoolFieldRef(cp, instData->index);
	Field * field = resolvedField(fieldRef);
	Class * class = field->classMember.attachClass;

	if (!isFieldStatic(field))
	{
		printf("java.lang.IncompatibleClassChangeError\n");
		exit(-1);
	}

	if (isFieldFinal(field))
	{
		if (currentClass != class ||
			strcmp(currentMethod->classMember.name, "<clinit>") != 0)
		{
			printf("java.lang.IllegalAccessError\n");
			exit(-1);
		}
	}

	char * descriptor = field->classMember.descriptor;
	uint16_t slotId = field->slotId;
	Slot * slots = class->staticVars;
	OperandStack * operandStack = frame->operandStack;

	switch (descriptor[0])
	{
	case 'Z':
	case 'B':
	case 'C':
	case 'S':
	case 'I':
		setSlotInt(slots, slotId, popOperandInt(operandStack));
		break;
	case 'F':
		setSlotFloat(slots, slotId, popOperandFloat(operandStack));
		break;
	case 'J':
		setSlotLong(slots, slotId, popOperandLong(operandStack));
		break;
	case 'D':
		setSlotDouble(slots, slotId, popOperandDouble(operandStack));
		break;
	case 'L':
	case '[':
		setSlotRef(slots, slotId, popOperandRef(operandStack));
		break;
	default:
		break;
	}

	return 0;
}

Instruction * PUT_STATIC(Instruction * inst)
{
	inst->fetchOperands = index16InstructionFetchOperands;
	inst->execute = execute_PUT_STATIC;
	return inst;
}
