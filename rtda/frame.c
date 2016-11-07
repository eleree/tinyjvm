#include "frame.h"
#include "local_vars.h"
#include "operand_stack.h"

Frame * newFrame(uint32_t maxLocals, uint32_t maxStack)
{
	Frame * frame = calloc(1, sizeof(Frame));
	frame->localVars = newLocalVars(maxLocals);
	frame->operandStack = newOperandStack(maxStack);
	return frame;
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
