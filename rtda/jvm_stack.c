#include "rtda.h"
#include "frame.h"

Stack * newStack(uint32_t maxSize)
{
	Stack * stack = calloc(1, sizeof(Stack));
	stack->maxSize = maxSize;
	return stack;
}

void pushFrame(Stack * stack,Frame * frame)
{
	if (stack->size >= stack->maxSize)
	{
		printf("java.lang.StackOverflowError\n");
		exit(1);
	}

	if (stack->_top != NULL)
	{
		frame->lower = stack->_top;
	}
	stack->_top = frame;
	stack->size++;
}

Frame * popFrame(Stack * stack)
{
	Frame * frame = NULL;
	if (stack->_top == NULL)
	{
		printf("jvm stack is empty!\n");
		exit(-1);
	}

	frame = stack->_top;
	stack->_top = stack->_top->lower;
	stack->size--;
	return frame;
}

void freeStack(Stack * stack)
{
	if (stack != NULL)
		free(stack);
}