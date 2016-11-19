#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"
#include "../../rtda/heap/method.h"
#include "../../rtda/heap/cp_interface_methodref.h"

// Invoke interface method
typedef struct InvokeInterface{
	uint16_t index;
	uint8_t count;
	uint8_t zero;
}InvokeInterface;

static InvokeInterface  invokeInterface;

static int32_t fetchOperands_INVOKE_INTERFACE(BytecodeReader * bytecoderReader, InstructionData * instData)
{
	invokeInterface.index = readBytecodeInt16(bytecoderReader);
	readBytecodeInt8(bytecoderReader);
	readBytecodeInt8(bytecoderReader);
	return 0;
}

static int32_t execute_INVOKE_INTERFACE(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	ConstantPoolItem * cp = frame->method->classMember.attachClass->constantPool.constantPoolItem;
	InterfaceMethodRef * methodRef = getClassConstantPoolInterfaceMethodRef(cp, invokeInterface.index);

	Method * resolvedMethod = resolvedInterfaceMethod(methodRef);

	if (isMethodStatic(resolvedMethod) || isMethodPrivate(resolvedMethod))
	{
		printf("java.lang.IncompatibleClassChangeError\n");
		exit(131);
	}

	Object * ref = getOperandRefFromTop(operandStack, resolvedMethod->argSlotCount - 1);

	if (ref == NULL)
	{
		printf("java.lang.NullPointerException\n"); //todo
		exit(132);
	}

	if (!isClassImplements(ref->class, resolveClass(&methodRef->memberRef.symRef)))
	{
		printf("java.lang.IncompatibleClassChangeError\n"); //todo
		exit(133);
	}

	Method * methodToBeInvoked = lookupMethodInClass(ref->class, methodRef->memberRef.name,
		methodRef->memberRef.descriptor);

	if (methodToBeInvoked == NULL || isMethodAbstract(methodToBeInvoked))
	{
		printf("java.lang.AbstractMethodError\n"); 
		exit(133);
	}

	if (!isMethodPublic(methodToBeInvoked))
	{
		printf("java.lang.IllegalAccessError\n");
		exit(133);
	}

	InvokeMethod(frame, methodToBeInvoked);

	return 0;
}

Instruction * INVOKE_INTERFACE(Instruction * inst)
{
	inst->fetchOperands = fetchOperands_INVOKE_INTERFACE;
	inst->execute = execute_INVOKE_INTERFACE;
	return inst;
}
