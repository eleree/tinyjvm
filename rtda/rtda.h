#ifndef __TINY_JVM_RTDA_H__
#define __TINY_JVM_RTDA_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "./heap/object.h"

typedef struct Slot{
	int32_t num;
	Object * ref;
}Slot;

typedef struct LocalVars
{
	uint32_t size;
	Slot * slots;
}LocalVars;

typedef struct OperandStack{
	uint32_t maxSize;
	uint32_t size;
	Slot * slots;
}OperandStack;

// stack frame
struct Method;
typedef struct  Frame  {
	struct Frame * lower; // stack is implemented as linked list
	LocalVars * localVars;
	OperandStack * operandStack;
	struct Thread * thread;
	int32_t nextPC;
	struct Method * method;
	// todo
}Frame;

// jvm stack
typedef struct Stack  {
	uint32_t maxSize;
	uint32_t size;
	Frame * _top;// stack is implemented as linked list
}Stack;

typedef struct Thread  {
	int32_t pc;     // the address of the instruction currently being executed
	Stack *stack;
	// todo
}Thread;

typedef union FloatInt
{
	uint32_t bitsData;
	float floatData;
}FloatInt;

typedef union LongInt
{
	struct bitsData{
		uint32_t low;
		uint32_t high;
	};
	int64_t  longData;
}LongInt;

typedef union DoubleLong
{
	uint64_t bitsData;
	double doubleData;
}DoubleLong;

Stack * newStack(uint32_t maxSize);
void pushFrame(Stack * stack, Frame * frame);
Frame * popFrame(Stack * stack);
Frame * topFrame(Stack * stack);
void freeStack(Stack * stack);
void clearStack(Stack* stack);

Object * getLocalVarsRef(LocalVars * localVars, int32_t index);
void setLocalVarsSlot(LocalVars * localVars, int32_t index, Slot * slot);
Object * getLocalVarsThis(LocalVars * self);
bool getLocalVarsBoolean(LocalVars * self, int32_t index);

/* Operand Stack */
Object * getOperandRefFromTop(OperandStack * self, uint16_t n);

#endif