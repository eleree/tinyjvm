#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"
#include "../../rtda/thread.h"

// Return void from method
static int32_t execute_RETURN(Frame * frame, struct InsturctionData * instData)
{
	popThreadFrame(frame->thread);
	return 0;
}

Instruction * RETURN(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_RETURN;
	return inst;
}



// Return reference from method
static int32_t execute_ARETURN(Frame * frame, struct InsturctionData * instData)
{
	Thread * thread = frame->thread;
	OperandStack * operandStack = frame->operandStack;

	Frame * currentFrame = popThreadFrame(thread);
	Frame * invokerFrame = getCurrentFrame(thread);

	Object * ref = popOperandRef(currentFrame->operandStack);
	pushOperandRef(invokerFrame->operandStack, ref);
	
	return 0;
}

Instruction * ARETURN(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ARETURN;
	return inst;
}



// Return double from method
static int32_t execute_DRETURN(Frame * frame, struct InsturctionData * instData)
{
	Thread * thread = frame->thread;
	OperandStack * operandStack = frame->operandStack;

	Frame * currentFrame = popThreadFrame(thread);
	Frame * invokerFrame = getCurrentFrame(thread);

	double val = popOperandDouble(currentFrame->operandStack);
	pushOperandDouble(invokerFrame->operandStack, val);

	return 0;
}

Instruction * DRETURN(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DRETURN;
	return inst;
}


// Return float from method
static int32_t execute_FRETURN(Frame * frame, struct InsturctionData * instData)
{
	Thread * thread = frame->thread;
	OperandStack * operandStack = frame->operandStack;

	Frame * currentFrame = popThreadFrame(thread);
	Frame * invokerFrame = getCurrentFrame(thread);

	float val = popOperandFloat(currentFrame->operandStack);
	pushOperandFloat(invokerFrame->operandStack, val);

	return 0;
}

Instruction * FRETURN(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_FRETURN;
	return inst;
}


// Return int from method
static int32_t execute_IRETURN(Frame * frame, struct InsturctionData * instData)
{
	Thread * thread = frame->thread;
	OperandStack * operandStack = frame->operandStack;

	Frame * currentFrame = popThreadFrame(thread);
	Frame * invokerFrame = getCurrentFrame(thread);

	int32_t val = popOperandInt(currentFrame->operandStack);
#if ENABLE_INST_LOCALVAR_DEBUG
	printf("ireturn:%d\n", val);
#endif
	pushOperandInt(invokerFrame->operandStack, val);

	return 0;
}

Instruction * IRETURN(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_IRETURN;
	return inst;
}

// Return int from method
static int32_t execute_LRETURN(Frame * frame, struct InsturctionData * instData)
{
	Thread * thread = frame->thread;
	OperandStack * operandStack = frame->operandStack;

	Frame * currentFrame = popThreadFrame(thread);
	Frame * invokerFrame = getCurrentFrame(thread);

	int64_t val = popOperandLong(currentFrame->operandStack);
	pushOperandLong(invokerFrame->operandStack, val);

	return 0;
}

Instruction * LRETURN(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LRETURN;
	return inst;
}

