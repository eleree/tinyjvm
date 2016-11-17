#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"

// Create new object
static int32_t execute_NEW(Frame * frame, struct InsturctionData * instData)
{
	/* 
	cp := frame.Method().Class().ConstantPool()
	classRef := cp.GetConstant(self.Index).(*heap.ClassRef)
	class := classRef.ResolvedClass()
	// todo: init class

	if class.IsInterface() || class.IsAbstract() {
		panic("java.lang.InstantiationError")
	}

	ref := class.NewObject()
	frame.OperandStack().PushRef(ref)
	*/
	OperandStack * operandStack = frame->operandStack;
	ConstantPoolItem * cp = frame->method->classMember.attachClass->constantPool.constantPoolItem;
	ClassRef * classRef = getClassConstantPoolClassRef(cp, instData->index);
	Class * c = resolveClass(&classRef->symRef);

	if (isClassAbstract(c) || isClassInterface(c))
	{
		printf("java.lang.InstantiationError\n");
		exit(-1);
	}

	pushOperandRef(operandStack, newObject(c));
	
	return 0;
}

Instruction * NEW(Instruction * inst)
{
	inst->fetchOperands = index16InstructionFetchOperands;
	inst->execute = execute_NEW;
	return inst;
}
