#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/slot.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"
#include "../../rtda/heap/object.h"

// Check whether object is of given type
static int32_t execute_CHECK_CAST(Frame * frame, struct InsturctionData * instData)
{
	ConstantPoolItem * cp = NULL;
	OperandStack * operandStack = frame->operandStack;
	Object * ref = popOperandRef(operandStack);

	pushOperandRef(operandStack, ref);
	if (ref == NULL)
		return 0;

	cp = frame->method->classMember.attachClass->constantPool.constantPoolItem;
	ClassRef * classRef = getClassConstantPoolClassRef(cp, instData->index);
	Class * c = resolveClass(&classRef->symRef);

	if (!isObjectInstanceOf(ref, c))
	{
		printf("java.lang.ClassCastException\n");
		exit(-1);
	}

	return 0;
}

Instruction * CHECK_CAST(Instruction * inst)
{
	inst->fetchOperands = index16InstructionFetchOperands;
	inst->execute = execute_CHECK_CAST;
	return inst;
}
