#include "frame.h"
#include "local_vars.h"
#include "operand_stack.h"

Frame * newFrame(Thread * thread, struct Method * method, uint32_t maxLocals, uint32_t maxStack)
{
	Frame * frame = calloc(1, sizeof(Frame));
	frame->localVars = newLocalVars(maxLocals);
	frame->operandStack = newOperandStack(maxStack);
	frame->thread = thread;
	frame->method = method;
	return frame;
}

LocalVars * getFrameLocalVars(Frame * frame)
{
	return frame->localVars;
}

OperandStack * getFrameOperandStack(Frame * frame)
{
	return frame->operandStack;
}

int32_t getFrameNextPC(Frame *frame)
{
	return frame->nextPC;
}

void setFrameNextPC(Frame *frame, int32_t nextPC)
{
	frame->nextPC = nextPC;
}

void freeFrame(Frame * frame)
{
	if (frame != NULL)
	{
		freeLocalVars(frame->localVars);
		freeOperandStack(frame->operandStack);
		free(frame);
	}
}
