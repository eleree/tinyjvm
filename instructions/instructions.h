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

Instruction * LSTORE(Instruction * inst);
Instruction * LSTORE_0(Instruction * inst);
Instruction * LSTORE_1(Instruction * inst);
Instruction * LSTORE_2(Instruction * inst);
Instruction * LSTORE_3(Instruction * inst);

Instruction * FSTORE(Instruction * inst);
Instruction * FSTORE_0(Instruction * inst);
Instruction * FSTORE_1(Instruction * inst);
Instruction * FSTORE_2(Instruction * inst);
Instruction * FSTORE_3(Instruction * inst);

Instruction * DSTORE(Instruction * inst);
Instruction * DSTORE_0(Instruction * inst);
Instruction * DSTORE_1(Instruction * inst);
Instruction * DSTORE_2(Instruction * inst);
Instruction * DSTORE_3(Instruction * inst);

Instruction * ASTORE(Instruction * inst);
Instruction * ASTORE_0(Instruction * inst);
Instruction * ASTORE_1(Instruction * inst);
Instruction * ASTORE_2(Instruction * inst);
Instruction * ASTORE_3(Instruction * inst);

/* extended */
Instruction * GOTO_W(Instruction * inst);
Instruction * IFNULL(Instruction * inst);
Instruction * IFNONNULL(Instruction * inst);
Instruction * WIDE(Instruction * inst);

/* loads */
Instruction * ALOAD(Instruction * inst);
Instruction * ALOAD_0(Instruction * inst);
Instruction * ALOAD_1(Instruction * inst);
Instruction * ALOAD_2(Instruction * inst);
Instruction * ALOAD_3(Instruction * inst);

Instruction * DLOAD(Instruction * inst);
Instruction * DLOAD_0(Instruction * inst);
Instruction * DLOAD_1(Instruction * inst);
Instruction * DLOAD_2(Instruction * inst);
Instruction * DLOAD_3(Instruction * inst);

Instruction * FLOAD(Instruction * inst);
Instruction * FLOAD_0(Instruction * inst);
Instruction * FLOAD_1(Instruction * inst);
Instruction * FLOAD_2(Instruction * inst);
Instruction * FLOAD_3(Instruction * inst);

Instruction * ILOAD(Instruction * inst);
Instruction * ILOAD_0(Instruction * inst);
Instruction * ILOAD_1(Instruction * inst);
Instruction * ILOAD_2(Instruction * inst);
Instruction * ILOAD_3(Instruction * inst);

Instruction * LLOAD(Instruction * inst);
Instruction * LLOAD_0(Instruction * inst);
Instruction * LLOAD_1(Instruction * inst);
Instruction * LLOAD_2(Instruction * inst);
Instruction * LLOAD_3(Instruction * inst);

/* math */
Instruction * DADD(Instruction * inst);
Instruction * FADD(Instruction * inst);
Instruction * IADD(Instruction * inst);
Instruction * LADD(Instruction * inst);

Instruction * IINC(Instruction * inst);
Instruction * IAND(Instruction * inst);
Instruction * LAND(Instruction * inst);

Instruction * IXOR(Instruction * inst);
Instruction * LXOR(Instruction * inst);
Instruction * IOR(Instruction * inst);
Instruction * LOR(Instruction * inst);

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

Instruction * DNEG(Instruction * inst);
Instruction * FNEG(Instruction * inst);
Instruction * INEG(Instruction * inst);
Instruction * LNEG(Instruction * inst);

Instruction * DREM(Instruction * inst);
Instruction * FREM(Instruction * inst);
Instruction * IREM(Instruction * inst);
Instruction * LREM(Instruction * inst);

Instruction * ISHL(Instruction * inst);
Instruction * ISHR(Instruction * inst);
Instruction * IUSHR(Instruction * inst);
Instruction * LSHL(Instruction * inst);
Instruction * LSHR(Instruction * inst);
Instruction * LUSHR(Instruction * inst);

/* stack */
Instruction * DUP(Instruction * inst);
Instruction * DUP_X1(Instruction * inst);
Instruction * DUP_X2(Instruction * inst);
Instruction * DUP2(Instruction * inst);
Instruction * DUP2_X1(Instruction * inst);
Instruction * DUP2_X2(Instruction * inst);

Instruction * POP(Instruction * inst);
Instruction * POP2(Instruction * inst);
Instruction * SWAP(Instruction * inst);

/* Reference */
Instruction * NEW(Instruction * inst);
Instruction * LDC(Instruction * inst);
Instruction * INSTANCE_OF(Instruction * inst);
Instruction * GET_STATIC(Instruction * inst);
Instruction * PUT_STATIC(Instruction * inst);
Instruction * GET_FIELD(Instruction * inst);
Instruction * PUT_FIELD(Instruction * inst);
Instruction * CHECK_CAST(Instruction * inst);
Instruction * INVOKE_VIRTUAL(Instruction * inst);
Instruction * INVOKE_SPECIAL(Instruction * inst);
#endif