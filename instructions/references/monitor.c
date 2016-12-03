#include "../factory.h"
#include "../../rtda/frame.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"
#include "../../rtda/heap/method.h"
#include "../../rtda/heap/cp_methodref.h"
#include "../../rtda/heap/cp_interface_methodref.h"

static int32_t execute_MONITOR_ENTER(Frame * frame, struct InsturctionData * instData)
{
	Object * ref = popOperandRef(frame->operandStack);
	if (ref == NULL)
		panic("java.lang.NullPointerException", 11);
	return 0;
}

// Enter monitor for object
Instruction * MONITOR_ENTER(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_MONITOR_ENTER;
	return inst;
}


static int32_t execute_MONITOR_EXIT(Frame * frame, struct InsturctionData * instData)
{
	Object * ref = popOperandRef(frame->operandStack);
	if (ref == NULL)
		panic("java.lang.NullPointerException", 11);
	return 0;
}

// Exit monitor for object
Instruction * MONITOR_EXIT(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_MONITOR_EXIT;
	return inst;
}