#include "thread.h"

Thread * newThread(void)
{
	Thread  * thread = NULL;
	thread = calloc(1, sizeof(Thread));
	thread->stack = calloc(1024, sizeof(Stack));
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