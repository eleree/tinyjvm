#include "thread.h"

Thread * newThread(void)
{
	Thread  * thread = NULL;
	thread = calloc(1, sizeof(Thread));
	thread->stack = newStack(1024);
	return thread;
}

int32_t getThreadPC(Thread * thread)
{
	return thread->pc;
}

void setThreadPC(Thread * thread, int32_t pc)
{
	thread->pc = pc;
}

void pushThreadFrame(Thread * thread, Frame * frame)
{
	pushFrame(thread->stack, frame);
}

Frame * popThreadFrame(Thread * thread)
{
	return popFrame(thread->stack);
}

Frame * getCurrentFrame(Thread * thread)
{
	return topFrame(thread->stack);
}

bool isThreadStackEmpty(Thread * thread)
{
	return thread->stack->_top == NULL;
}

Frame* * getThreadFrames(Thread * thread, int32_t skip, int32_t * remain)
{
	/* count total frame */
	Frame * top = thread->stack->_top;

	*remain = thread->stack->size - skip;
	if (skip >= (int32_t) thread->stack->size)
	{
		printf("getThreadFrames skip:%d > stackSize:%d\n", skip, thread->stack->size);
		exit(200);
	}

	Frame * *frames = calloc(thread->stack->size, sizeof(Frame*));

	for (int32_t i = 0; i < skip; i++)
		top = top->lower;
	for (int32_t i = 0; i < *remain; i++)
	{
		frames[i] = top;
		top = top->lower;
	}
	return frames;
}

void clearThreadStack(Thread *thread)
{
	clearStack(thread->stack);
}