#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/slot.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"
#include "../../rtda/heap/field.h"
#include "../../rtda/heap/cp_fieldref.h"

// Set field in object
static int32_t execute_PUT_FIELD(Frame * frame, struct InsturctionData * instData)
{
	Method * currentMethod = frame->method;
	Class * currentClass = currentMethod->classMember.attachClass;

	ConstantPoolItem * cp = frame->method->classMember.attachClass->constantPool.constantPoolItem;
	FieldRef * fieldRef = getClassConstantPoolFieldRef(cp, instData->index);
	Field * field = resolvedField(fieldRef);
	Class * c = field->classMember.attachClass;

	if (isFieldStatic(field))
	{
		printf("java.lang.IncompatibleClassChangeError\n");
		exit(-1);
	}

	if (isFieldFinal(field))
	{
		if (currentClass != c ||
			strcmp(currentMethod->classMember.name, "<init>") != 0)
		{
			printf("java.lang.IllegalAccessError\n");
			exit(-1);
		}
	}

	char * descriptor = field->classMember.descriptor;
	uint16_t slotId = field->slotId;
	OperandStack * operandStack = frame->operandStack;

	Object * ref = NULL;
	Object * refVal = NULL;
	int32_t int32Val = 0;
	int64_t int64Val = 0;
	float floatVal = 0;
	double doubleVal = 0;
	Slot * slots = NULL;

	switch (descriptor[0])
	{
	case 'Z':
	case 'B':
	case 'C':
	case 'S':
	case 'I':
		int32Val = popOperandInt(operandStack);
		ref = popOperandRef(operandStack);
		if (ref == NULL)
		{
			printf("java.lang.NullPointerException\n");
			exit(-1);
		}
		//slots = ref->fields;
		slots = getObjectSlots(ref);
		setSlotInt(slots, slotId, int32Val);
		break;
	case 'F':
		floatVal = popOperandFloat(operandStack);
		ref = popOperandRef(operandStack);
		if (ref == NULL)
		{
			printf("java.lang.NullPointerException\n");
			exit(-1);
		}
		//slots = ref->fields;
		slots = getObjectSlots(ref);
		setSlotFloat(slots, slotId, floatVal);
		break;
	case 'J':
		int64Val = popOperandLong(operandStack);
		ref = popOperandRef(operandStack);
		if (ref == NULL)
		{
			printf("java.lang.NullPointerException\n");
			exit(-1);
		}
		//slots = ref->fields;
		slots = getObjectSlots(ref);
		setSlotLong(slots, slotId, int64Val);
		break;
	case 'D':
		doubleVal = popOperandDouble(operandStack);
		ref = popOperandRef(operandStack);
		if (ref == NULL)
		{
			printf("java.lang.NullPointerException\n");
			exit(-1);
		}
		//slots = ref->fields;
		slots = getObjectSlots(ref);
		setSlotDouble(slots, slotId, doubleVal);
		break;
	case 'L':
	case '[':
		refVal = popOperandRef(operandStack);
		ref = popOperandRef(operandStack);
		if (ref == NULL)
		{
			printf("java.lang.NullPointerException\n");
			exit(-1);
		}
		//slots = ref->fields;
		slots = getObjectSlots(ref);
		setSlotRef(slots, slotId, refVal);	
		break;
	default:
		break;
	}

	return 0;
}

Instruction * PUT_FIELD(Instruction * inst)
{
	inst->fetchOperands = index16InstructionFetchOperands;
	inst->execute = execute_PUT_FIELD;
	return inst;
}
