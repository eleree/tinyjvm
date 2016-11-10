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
Instruction * IF_ICMPEQ(Instruction * inst);
Instruction * IF_ICMPNE(Instruction * inst);
Instruction * IF_ICMPLT(Instruction * inst);
Instruction * IF_ICMPLE(Instruction * inst);
Instruction * IF_ICMPGT(Instruction * inst);
Instruction * IF_ICMPGE(Instruction * inst);

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

Instruction * LOOKUP_SWITCH(Instruction * inst);
Instruction * TABLE_SWITCH(Instruction * inst);

Instruction * ISTORE(Instruction * inst);
Instruction * ISTORE_0(Instruction * inst);
Instruction * ISTORE_1(Instruction * inst);
Instruction * ISTORE_2(Instruction * inst);
Instruction * ISTORE_3(Instruction * inst);

Instruction * ILOAD(Instruction * inst);
Instruction * ILOAD_0(Instruction * inst);
Instruction * ILOAD_1(Instruction * inst);
Instruction * ILOAD_2(Instruction * inst);
Instruction * ILOAD_3(Instruction * inst);

/* math */
Instruction * DADD(Instruction * inst);
Instruction * FADD(Instruction * inst);
Instruction * IADD(Instruction * inst);
Instruction * LADD(Instruction * inst);

Instruction * IINC(Instruction * inst);
Instruction * IAND(Instruction * inst);
Instruction * LAND(Instruction * inst);

Instruction * DDIV(Instruction * inst);
Instruction * FDIV(Instruction * inst);
Instruction * IDIV(Instruction * inst);
Instruction * LDIV(Instruction * inst);

Instruction * DMUL(Instruction * inst);
Instruction * FMUL(Instruction * inst);
Instruction * IMUL(Instruction * inst);
Instruction * LMUL(Instruction * inst);

Instruction * DSUB(Instruction * inst);
Instruction * FSUB(Instruction * inst);
Instruction * ISUB(Instruction * inst);
Instruction * LSUB(Instruction * inst);

#endif