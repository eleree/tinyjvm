#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"
#
// Invoke instance method;
// special handling for superclass, private, and instance initialization method invocations
static int32_t execute_INVOKE_SPECIAL(Frame * frame, struct InsturctionData * instData)
{
	// hack!
	OperandStack * operandStack = frame->operandStack;
	Class * currentClass = frame->method->classMember.attachClass;
	ConstantPoolItem * cp = frame->method->classMember.attachClass->constantPool.constantPoolItem;
	MethodRef * methodRef = getClassConstantPoolMethodRef(cp, instData->index);
	Class * resolvedClass = resolveClass(&methodRef->symRef);
	Method * resovMethod = resolvedMethod(methodRef);

	if (strcmp(resovMethod->classMember.name, "<init>") == 0 &&
		resovMethod->classMember.attachClass != resolvedClass)
	{
		printf("java.lang.NoSuchMethodError\n");
		exit(141);
	}

	if (isMethodStatic(resovMethod))
	{
		printf("java.lang.IncompatibleClassChangeError\n");
		exit(142);
	}

	Object * ref = getOperandRefFromTop(operandStack, resovMethod->argSlotCount - 1);

	if (ref == NULL)
	{
		printf("java.lang.IncompatibleClassChangeError\n");
		exit(143);
	}

	if (isMethodProtected(resovMethod) &&
		isClassSuperClassOf(resovMethod->classMember.attachClass, currentClass) &&
		strcmp(resovMethod->classMember.attachClass->packageName, currentClass->packageName) == 0 &&
		ref->class != currentClass &&
		!isClassSubClassOf(ref->class, currentClass))
	{
		printf("java.lang.IllegalAccessError\n");
		exit(143);
	}

	Method * methodToBeInvoked = resovMethod;

	if (isClassSuper(currentClass) &&
		isClassSuperClassOf(resolvedClass, currentClass) &&
		strcmp(resolvedClass->name, "<init>") != 0
		)
	{
		methodToBeInvoked = lookupMethodInClass(currentClass->superClass,
			methodRef->name, methodRef->descriptor);
	}

	if (methodToBeInvoked == NULL || isMethodAbstract(methodToBeInvoked))
	{
		printf("java.lang.AbstractMethodError\n");
		exit(143);
	}

	//printf("Invode classs:%s method:%s,desc:%s\n",methodRef->symRef.className, methodRef->name, methodRef->descriptor);
	InvokeMethod(frame, methodToBeInvoked);
	return 0;
}

Instruction * INVOKE_SPECIAL(Instruction * inst)
{
	inst->fetchOperands = index16InstructionFetchOperands;
	inst->execute = execute_INVOKE_SPECIAL;
	return inst;
}
