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

Instruction * ACONST_NULL(Instruction * inst);
Instruction * DCONST_0(Instruction * inst);
Instruction * DCONST_1(Instruction * inst);
Instruction * FCONST_0(Instruction * inst);
Instruction * FCONST_1(Instruction * inst);
Instruction * FCONST_2(Instruction * inst);
Instruction * ICONST_M1(Instruction * inst);
Instruction * ICONST_0(Instruction * inst);
Instruction * ICONST_1(Instruction * inst);
Instruction * ICONST_2(Instruction * inst);
Instruction * ICONST_3(Instruction * inst);
Instruction * ICONST_4(Instruction * inst);
Instruction * ICONST_5(Instruction * inst);
Instruction * LCONST_0(Instruction * inst);
Instruction * LCONST_1(Instruction * inst);
Instruction * BIPUSH(Instruction * inst);
Instruction * SIPUSH(Instruction * inst);

#endif