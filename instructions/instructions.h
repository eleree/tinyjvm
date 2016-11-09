#ifndef __TINY_JVM_INSTRUCTIONS_H__
#define __TINY_JVM_INSTRUCTIONS_H__

#include "factory.h"

Instruction * NOP(Instruction * inst);
Instruction * DCMPL(Instruction * inst);
Instruction * DCMPG(Instruction * inst);
Instruction * GOTO(Instruction * inst);

// comparisons
Instruction * IF_ACMPNE(Instruction * inst);
Instruction * IF_ACMPEQ(Instruction * inst);

#endif