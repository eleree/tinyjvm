#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"
#include "../../rtda/heap/string_pool.h"

static int32_t _ldc(Frame * frame, int32_t index)
{
	OperandStack * operandStack = frame->operandStack;
	ConstantPoolItem * cp = frame->method->classMember.attachClass->constantPool.constantPoolItem;
	int16_t type = getClassContantPoolType(cp, index);
	ClassLoader * classLoader = frame->method->classMember.attachClass->classLoader;
	switch (type)
	{
	case CONSTATNT_INTEGER:
		pushOperandInt(operandStack, getClassConstantPoolInt(cp, index));
		break;
	case CONSTATNT_FLOAT:
		pushOperandFloat(operandStack, getClassConstantPoolFloat(cp,index));
		break;
	case CONSTATNT_STRING:
		pushOperandRef(operandStack, jString(classLoader, getClassConstantPoolStringRef(cp, index)));
		break;
	case CONSTATNT_CLASS:
		do
		{
			ClassRef * classRef = getClassConstantPoolClassRef(cp, index);
			Object * classObj = resolveClass(&classRef->symRef)->jClass;
			pushOperandRef(operandStack,classObj);
		} while (0);
		break;
	default:
		printf("todo: ldc!\n");
		exit(0);
		break;
	}
	return 0;
}

static int32_t execute_LDC(Frame * frame, struct InsturctionData * instData)
{
	_ldc(frame, instData->index);
	return 0;
}

Instruction * LDC(Instruction * inst)
{
	inst->fetchOperands = index8InstructionFetchOperands;
	inst->execute = execute_LDC;
	return inst;
}


// Push item from run-time constant pool (wide index)
static int32_t execute_LDC_W(Frame * frame, struct InsturctionData * instData)
{
	_ldc(frame, instData->index);
	return 0;
}

Instruction * LDC_W(Instruction * inst)
{
	inst->fetchOperands = index16InstructionFetchOperands;
	inst->execute = execute_LDC_W;
	return inst;
}

// Push long or double from run-time constant pool (wide index)
static int32_t execute_LDC2_W(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	ConstantPoolItem * cp = frame->method->classMember.attachClass->constantPool.constantPoolItem;
	int16_t type = getClassContantPoolType(cp, instData->index);
	switch (type)
	{
	case CONSTATNT_LONG:
		pushOperandLong(operandStack, getClassConstantPoolLong(cp, instData->index));
		break;
	case CONSTATNT_DOUBLE:
		pushOperandDouble(operandStack, getClassConstantPoolDouble(cp, instData->index));
		break;
	default:
		printf("java.lang.ClassFormatError\n");
		exit(0);
		break;
	}
	return 0;
	return 0;
}

Instruction * LDC2_W(Instruction * inst)
{
	inst->fetchOperands = index16InstructionFetchOperands;
	inst->execute = execute_LDC2_W;
	return inst;
}
