#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"

// Invoke instance method;
// special handling for superclass, private, and instance initialization method invocations
static int32_t execute_INVOKE_SPECIAL(Frame * frame, struct InsturctionData * instData)
{
	// hack!
	OperandStack * operandStack = frame->operandStack;
	popOperandRef(operandStack);

	return 0;
}

Instruction * INVOKE_SPECIAL(Instruction * inst)
{
	inst->fetchOperands = index16InstructionFetchOperands;
	inst->execute = execute_INVOKE_SPECIAL;
	return inst;
}
