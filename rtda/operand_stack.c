#include "rtda.h"
#include <string.h>
#include "heap/class.h"
OperandStack * newOperandStack(uint32_t maxStack)
{
	OperandStack * operandStack = NULL;

	if (maxStack == 0)
		return NULL;	

	operandStack =  calloc(1, sizeof(OperandStack));
	operandStack->maxSize = maxStack;
	operandStack->size = 0;
	operandStack->slots = calloc(maxStack, sizeof(Slot));
	return operandStack;
}

void freeOperandStack(OperandStack* operandStack)
{
	if (operandStack != NULL)
	{
		if (operandStack->maxSize > 0)
			free(operandStack->slots);
		free(operandStack);
	}	
}

void pushOperandInt(OperandStack* operandStack,int32_t val)
{
	uint32_t operandStackSize = operandStack->size;
	operandStack->slots[operandStackSize].num = val;
	operandStack->size++;
}

int32_t popOperandInt(OperandStack* operandStack)
{
	operandStack->size--;
	return operandStack->slots[operandStack->size].num;
}

void pushOperandBoolean(OperandStack* operandStack, bool val)
{
	if (val)
		pushOperandInt(operandStack, 1);
	else
		pushOperandInt(operandStack, 0);
}

bool popOperandBoolean(OperandStack* operandStack)
{
	return popOperandInt(operandStack) == 1;
}

void pushOperandFloat(OperandStack* operandStack, float val)
{
	FloatInt transData;
	transData.floatData = val;
	operandStack->slots[operandStack->size].num = transData.bitsData;
	operandStack->size++;
}

float popOperandFloat(OperandStack* operandStack)
{
	FloatInt transData;	
	operandStack->size--;
	transData.bitsData= operandStack->slots[operandStack->size].num;
	return transData.floatData;
}

void pushOperandLong(OperandStack* operandStack, int64_t val)
{
	operandStack->slots[operandStack->size].num = (uint32_t) val;
	operandStack->slots[operandStack->size+1].num = (uint32_t) (val >> 32);
	operandStack->size += 2;
}

int64_t popOperandLong(OperandStack* operandStack)
{
	LongInt transData;

	operandStack->size -= 2;
	transData.high = operandStack->slots[operandStack->size + 1].num;
	transData.low = operandStack->slots[operandStack->size].num;

	return transData.longData;
}

void pushOperandDouble(OperandStack* operandStack, double val)
{
	DoubleLong transData;
	transData.doubleData = val;
	pushOperandLong(operandStack, transData.bitsData);
}

double popOperandDouble(OperandStack* operandStack)
{
	DoubleLong transData;
	transData.bitsData = popOperandLong(operandStack);
	return  transData.doubleData;
}

void pushOperandRef(OperandStack * operandStack, Object * ref)
{
	//if (ref != NULL)
	//	printf("---Ops Size:%d,Push Ref %s\n", operandStack->size, ref->class->name);
	operandStack->slots[operandStack->size].ref = ref;
	operandStack->size++;
}

Object * popOperandRef(OperandStack * operandStack)
{
	operandStack->size--;
	return operandStack->slots[operandStack->size].ref;
}

void pushOperandSlot(OperandStack * operandStack, Slot * slot)
{
	//memcpy(&operandStack->slots[operandStack->size], slot, sizeof(Slot));
	operandStack->slots[operandStack->size].num = slot->num;
	operandStack->slots[operandStack->size].ref = slot->ref;
	operandStack->size++;
}

Slot * popOperandSlot(OperandStack * operandStack)
{
	Slot * s = calloc(1, sizeof(Slot));;
	operandStack->size--;
	s->num = operandStack->slots[operandStack->size].num;
	s->ref = operandStack->slots[operandStack->size].ref;
	return s;
}


Object * getOperandRefFromTop(OperandStack * self, uint16_t n)
{
	return self->slots[self->size - 1 - n].ref;
}

void clearOperandStack(OperandStack * self)
{
	self->size = 0;
	for (uint32_t i = 0; i < self->maxSize; i++)
	{
		self->slots[i].ref = NULL;
	}
}