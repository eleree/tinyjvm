#include "frame.h"
#include "local_vars.h"
#include "operand_stack.h"
#include "heap\method.h"

#pragma warning(disable:4996)

Frame * newShimFrame(Thread * thread, OperandStack * operandStack)
{
	Frame * frame = calloc(1, sizeof(Frame));
	Method * method = calloc(1, sizeof(Method));
	Class * c = calloc(1, sizeof(Class));
	c->name = strdup("~shim");

	method->classMember.accessFlags = ACC_STATIC;
	method->classMember.name = strdup("<return>");
	method->classMember.attachClass = c;
	method->code = calloc(1, sizeof(uint8_t));
	method->codeLen = 1;
	method->code[0] = 0xb1;

	frame->localVars = newLocalVars(0);
	frame->operandStack = newOperandStack(0);
	frame->thread = thread;
	frame->method = method;
	return frame;
}