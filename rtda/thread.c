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

Frame* * getThreadFrames(Thread * threak, int32_t skip, int32_t * remain)
{
	return NULL;
}