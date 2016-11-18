#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/slot.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"
#include "../../rtda/heap/object.h"



static int32_t execute_INSTANCE_OF(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	Object * ref = popOperandRef(operandStack);

	if (ref == NULL)
	{
		pushOperandInt(operandStack, 0);
		return 0;
	}
	ConstantPoolItem * cp = frame->method->classMember.attachClass->constantPool.constantPoolItem;
	ClassRef * classRef = getClassConstantPoolClassRef(cp, instData->index);
	Class * class = resolveClass(&classRef->symRef);

	if (isObjectInstanceOf(ref, class))
		pushOperandInt(operandStack, 1);
	else
		pushOperandInt(operandStack, 0);

	return 0;
}

Instruction * INSTANCE_OF(Instruction * inst)
{
	inst->fetchOperands = index16InstructionFetchOperands;
	inst->execute = execute_INSTANCE_OF;
	return inst;
}
