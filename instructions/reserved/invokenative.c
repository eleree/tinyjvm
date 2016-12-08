#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"
#include "../../rtda/heap/method.h"
#include "../../rtda/heap/cp_interface_methodref.h"
#include "../../native/registry.h"

// Invoke native method
static int32_t execute_INVOKE_NATIVE(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	ConstantPoolItem * cp = frame->method->classMember.attachClass->constantPool.constantPoolItem;
	Method * method = frame->method;
	char * className = method->classMember.attachClass->name;
	char * methodName = method->classMember.name;
	char * methodDescriptor = method->classMember.descriptor;

	NativeMethod nativeMethod = findNativeMethod(className, methodName, methodDescriptor);
	if (nativeMethod == NULL)
	{
		printf("methodInfo:%s.%s %s\n", className, methodName, methodDescriptor);
		panic("java.lang.UnsatisfiedLinkError", 12);
	}

#if ENABLE_NATIVE_METHOD_DEBUG
	printf("Native Method %s.%s%s\n", className, methodName, methodDescriptor);
#endif

	nativeMethod(frame);
	return 0;
}

Instruction * INVOKE_NATIVE(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_INVOKE_NATIVE;
	return inst;
}