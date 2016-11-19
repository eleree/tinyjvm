#include "../factory.h"
#include "../../rtda/frame.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"
#include "../../rtda/heap/method.h"
#include "../../rtda/heap/cp_methodref.h"
#include "../../rtda/heap/cp_interface_methodref.h"


static int32_t execute_INVOKE_STATIC(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	ConstantPoolItem * cp = frame->method->classMember.attachClass->constantPool.constantPoolItem;
	MethodRef * methodRef = getClassConstantPoolMethodRef(cp, instData->index);

	Method * method = resolvedMethod(methodRef);

	if (isMethodStatic(method))
	{
		printf("java.lang.IncompatibleClassChangeError\n");
		exit(131);		
	}

	Class * class = method->classMember.attachClass;
	
	if (!class->initStarted)
	{
		revertFrameNextPC(frame);
		return 0;
	}

	InvokeMethod(frame, method);

	return 0;
}

Instruction * INVOKE_STATIC(Instruction * inst)
{
	inst->fetchOperands = index16InstructionFetchOperands;
	inst->execute = execute_INVOKE_STATIC;
	return inst;
}
