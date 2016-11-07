#ifndef __TINY_JVM_OPERAND_STACK_H__
#define __TINY_JVM_OPERAND_STACK_H__

#include "rtda.h"

OperandStack * newOperandStack(uint32_t maxStack);
void freeOperandStack(OperandStack* operandStack);

void pushOperandInt(OperandStack* operandStack, int32_t val);
int32_t popOperandInt(OperandStack* operandStack, int32_t val);

void pushOperandFloat(OperandStack* operandStack, float val);
float popOperandFloat(OperandStack* operandStack);

void pushOperandLong(OperandStack* operandStack, int64_t val);
int64_t popOperandLong(OperandStack* operandStack);

void pushOperandDouble(OperandStack* operandStack, double val);
double popOperandDouble(OperandStack* operandStack);

void pushOperandRef(OperandStack * operandStack, Object * ref);
Object * popOperandRef(OperandStack * operandStack);

#endif