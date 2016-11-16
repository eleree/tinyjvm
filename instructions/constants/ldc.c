#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"

static int32_t _ldc(Frame * frame, int32_t index)
{
	OperandStack * operandStack = frame->operandStack;
	ConstantPoolItem * cp = frame->method->classMember.attachClass->constantPool.constantPoolItem;

	pushOperandInt(operandStack, 0);
}

static int32_t execute_LDC(Frame * frame, struct InsturctionData * instData)
{

	return 0;
}
Instruction * LDC(Instruction * inst)
{
	inst->fetchOperands = index8InstructionFetchOperands;
	inst->execute = execute_LDC;
	return inst;
}