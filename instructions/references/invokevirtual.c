#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"
#include "../../rtda/heap/cp_methodref.h"

// Invoke instance method; dispatch based on class
void _println(OperandStack * operandStack, char * descriptor)
{
	if (strncmp(descriptor, "(Z)V", 4) == 0)
	{
		printf("%d\n", popOperandInt(operandStack));
	}
	else if (strncmp(descriptor, "(C)V", 4) == 0)
	{
		printf("%c\n", popOperandInt(operandStack));
	}
	else if (strncmp(descriptor, "(I)V", 4) == 0)
	{
		printf("%d\n", popOperandInt(operandStack));
	}
	else if (strncmp(descriptor, "(B)V", 4) == 0)
	{
		printf("%d\n", popOperandInt(operandStack));
	}
	else if (strncmp(descriptor, "(S)V", 4) == 0)
	{
		printf("%d\n", popOperandInt(operandStack));
	}
	else if (strncmp(descriptor, "(F)V", 4) == 0)
	{
		printf("%f\n", popOperandInt(operandStack));
	}
	else if (strncmp(descriptor, "(J)V", 4) == 0)
	{
		printf("%lld\n", popOperandInt(operandStack));
	}
	else if (strncmp(descriptor, "(D)V", 4) == 0)
	{
		printf("%llf\n", popOperandInt(operandStack));
	}
	else
	{
		printf("println:%s\n", descriptor);
		exit(-1);
	}
	popOperandRef(operandStack);
}

static int32_t execute_INVOKE_VIRTUAL(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	ConstantPoolItem * cp = frame->method->classMember.attachClass->constantPool.constantPoolItem;
	MethodRef * methodRef = getClassConstantPoolMethodRef(cp, instData->index);
	Method * method = resolvedMethod(methodRef);
	Class * currentClass = frame->method->classMember.attachClass;

	if (isMethodStatic(method))
	{
		printf("java.lang.IncompatibleClassChangeError\n");
		exit(134);
	}

	Object * ref = getOperandRefFromTop(frame->operandStack, method->argSlotCount - 1);
	if (ref == NULL)
	{
		// hack!
		if (strcmp(methodRef->name, "println") == 0)
		{
			_println(frame->operandStack, methodRef->descriptor);
			return 0;
		}
		printf("java.lang.NullPointerException\n");
		exit(135);
	}
	
	if (isMethodProtected(method) &&
		isClassSuperClassOf(method->classMember.attachClass, currentClass) &&
		strcmp(method->classMember.attachClass->packageName, currentClass->packageName) != 0 &&
		ref->class != currentClass &&
		!isSubClassOf(ref->class, currentClass)){

		printf("java.lang.IllegalAccessError\n");
		exit(200);			
	}
		
	Method * methodToBeInvoked = lookupMethodInClass(ref->class, methodRef->name,
		methodRef->descriptor);

	if (methodToBeInvoked == NULL || isMethodAbstract(methodToBeInvoked))
	{
		printf("java.lang.AbstractMethodError\n");
		exit(136);
	}

	InvokeMethod(frame, methodToBeInvoked);

	return 0;
}

Instruction * INVOKE_VIRTUAL(Instruction * inst)
{
	inst->fetchOperands = index16InstructionFetchOperands;
	inst->execute = execute_INVOKE_VIRTUAL;
	return inst;
}
