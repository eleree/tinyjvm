#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"
#include "../../rtda/heap/array_class.h"

static int32_t execute_ANEW_ARRAY(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	ConstantPoolItem * cp = frame->method->classMember.attachClass->constantPool.constantPoolItem;
	ClassRef * classRef = getClassConstantPoolClassRef(cp, instData->index);
	Class * componentClass = resolveClass(&classRef->symRef);

	// if componentClass.InitializationNotStarted() {
	// 	thread := frame.Thread()
	// 	frame.SetNextPC(thread.PC()) // undo anewarray
	// 	thread.InitClass(componentClass)
	// 	return
	// }

	int32_t count = popOperandInt(operandStack);
	if (count < 0)
	{
		panic("java.lang.NegativeArraySizeException\n", 152);
	}
	
	Class * arrClass = arrayClass(componentClass);

	Object * arr = newArray(arrClass, count);

	pushOperandRef(operandStack, arr);
	return 0;
}

Instruction * ANEW_ARRAY(Instruction * inst)
{
	inst->fetchOperands = index16InstructionFetchOperands;
	inst->execute = execute_ANEW_ARRAY;
	return inst;
}
