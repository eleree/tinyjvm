#include "factory.h"
#include "instructions.h"
#include "../rtda/frame.h"

static Instruction instruction;

int32_t noOperandsInstructionFetchOperands(BytecodeReader * bytecoderReader, InstructionData * instData)
{
	return 0;
}

int32_t branchInstructionFetchOperands(BytecodeReader * bytecoderReader, InstructionData * instData)
{
	instData->offset = readBytecodeInt16(bytecoderReader);
	return 0;
}

int32_t index8InstructionFetchOperands(BytecodeReader * bytecoderReader, InstructionData * instData)
{
	instData->index = readBytecodeUint8(bytecoderReader);
	return 0;
}

int32_t index16InstructionFetchOperands(BytecodeReader * bytecoderReader, InstructionData * instData)
{
	instData->index = readBytecodeUint16(bytecoderReader);
	return 0;
}

void branch(Frame * frame, int32_t offset)
{
	int32_t pc = frame->thread->pc;
	int32_t nextPC = pc + offset;
	setFrameNextPC(frame, nextPC);
}

Instruction * newInsturction(uint8_t opcode)
{

	switch (opcode)
	{
		case 0x00:
			return NOP(&instruction);
		case 0x01:
			return ACONST_NULL(&instruction);
		case 0x02:
			//return iconst_m1
			return ICONST_M1(&instruction);
		case 0x03:
			//return iconst_0
			return ICONST_0(&instruction);
		case 0x04:
			//return iconst_1
			return ICONST_1(&instruction);
		case 0x05:
			//return iconst_2
			return ICONST_2(&instruction);
		case 0x06:
			//return iconst_3
			return ICONST_3(&instruction);
		case 0x07:
			//return iconst_4
			return ICONST_4(&instruction);
		case 0x08:
			//return iconst_5
			return ICONST_5(&instruction);
		case 0x09:
			//return lconst_0
			return LCONST_0(&instruction);
		case 0x0a:
			//return lconst_1
			return LCONST_1(&instruction);
		case 0x0b:
			//return fconst_0
			return FCONST_0(&instruction);
		case 0x0c:
			//return fconst_1
			return FCONST_1(&instruction);
		case 0x0d:
			//return fconst_2
			return FCONST_2(&instruction);
		case 0x0e:
			//return dconst_0
			return DCONST_0(&instruction);
		case 0x0f:
			//return dconst_1
			return DCONST_1(&instruction);
		case 0x10:
			//return &BIPUSH{}
			return BIPUSH(&instruction);
		case 0x11:
			//return &SIPUSH{}
			return SIPUSH(&instruction);

		case 0x12:
			return LDC(&instruction);
		case 0x13:
			//	return &LDC_W{}
			return LDC_W(&instruction);
		case 0x14:
			// 	return &LDC2_W{}
			return LDC2_W(&instruction);
		case 0x15:
			//return &ILOAD{}
			return ILOAD(&instruction);
		case 0x16:
			//return &LLOAD{}
			return LLOAD(&instruction);
		case 0x17:
			//return &FLOAD{}
			return FLOAD(&instruction);
		case 0x18:
			//return &DLOAD{}
			return DLOAD(&instruction);
		case 0x19:
			//return &ALOAD{}
			return ALOAD(&instruction);
		case 0x1a:
			//return iload_0
			return ILOAD_0(&instruction);
		case 0x1b:
			//return iload_1
			return ILOAD_1(&instruction);
		case 0x1c:
			//return iload_2
			return ILOAD_2(&instruction);
		case 0x1d:
			//return iload_3
			return ILOAD_3(&instruction);
		case 0x1e:
			//return lload_0
			return LLOAD_0(&instruction);
		case 0x1f:
			//return lload_1
			return LLOAD_1(&instruction);
		case 0x20:
			//return lload_2
			return LLOAD_2(&instruction);
		case 0x21:
			//return lload_3
			return LLOAD_3(&instruction);
		case 0x22:
			//return fload_0
			return FLOAD_0(&instruction);
		case 0x23:
			//return fload_1
			return FLOAD_1(&instruction);
		case 0x24:
			//return fload_2
			return FLOAD_2(&instruction);
		case 0x25:
			//return fload_3
			return FLOAD_3(&instruction);
		case 0x26:
			//return dload_0
			return DLOAD_0(&instruction);
		case 0x27:
			//return dload_1
			return DLOAD_1(&instruction);
		case 0x28:
			//return dload_2
			return DLOAD_2(&instruction);
		case 0x29:
			//return dload_3
			return DLOAD_3(&instruction);
		case 0x2a:
			//return aload_0
			return ALOAD_0(&instruction);
		case 0x2b:
			//return aload_1
			return ALOAD_1(&instruction);
		case 0x2c:
			//return aload_2
			return ALOAD_2(&instruction);
		case 0x2d:
			//return aload_3
			return ALOAD_3(&instruction);
		case 0x2e:
			// 	return iaload
			return IALOAD(&instruction);				
		case 0x2f:
				// 	return laload
			return LALOAD(&instruction);
		case 0x30:
				// 	return faload
			return FALOAD(&instruction);
		case 0x31:
				// 	return daload
			return DALOAD(&instruction);
		case 0x32:
				// 	return aaload
			return AALOAD(&instruction);
		case 0x33:
				//return baload
			return BALOAD(&instruction);
		case 0x34:
				// 	return caload
			return CALOAD(&instruction);
		case 0x35:
				// 	return saload
			return SALOAD(&instruction);
		case 0x36:
			//return &ISTORE{}
			return ISTORE(&instruction);
		case 0x37:
			//return &LSTORE{}
			return LSTORE(&instruction);
		case 0x38:
			//return &FSTORE{}
			return FSTORE(&instruction);
		case 0x39:
			//return &DSTORE{}
			return DSTORE(&instruction);
		case 0x3a:
			//return &ASTORE{}
			return ASTORE(&instruction);
		case 0x3b:
			//return istore_0
			return ISTORE_0(&instruction);
		case 0x3c:
			//return istore_1
			return ISTORE_1(&instruction);
		case 0x3d:
			//return istore_2
			return ISTORE_2(&instruction);
		case 0x3e:
			//return istore_3
			return ISTORE_3(&instruction);
		case 0x3f:
			//return lstore_0
			return LSTORE_0(&instruction);
		case 0x40:
			//return lstore_1
			return LSTORE_1(&instruction);
		case 0x41:
			//return lstore_2
			return LSTORE_2(&instruction);
		case 0x42:
			//return lstore_3
			return LSTORE_3(&instruction);
		case 0x43:
			//return fstore_0
			return FSTORE_0(&instruction);
		case 0x44:
			//return fstore_1
			return FSTORE_1(&instruction);
		case 0x45:
			//return fstore_2
		case 0x46:
			//return fstore_3
			return FSTORE_3(&instruction);
		case 0x47:
			//return dstore_0
			return DSTORE_0(&instruction);
		case 0x48:
			//return dstore_1
			return DSTORE_1(&instruction);
		case 0x49:
			//return dstore_2
			return DSTORE_2(&instruction);
		case 0x4a:
			//return dstore_3
			return DSTORE_3(&instruction);
		case 0x4b:
			//return astore_0
			return ASTORE_0(&instruction);
		case 0x4c:
			//return astore_1
			return ASTORE_1(&instruction);
		case 0x4d:
			//return astore_2
			return ASTORE_2(&instruction);
		case 0x4e:
			//return astore_3
			return ASTORE_3(&instruction);
		case 0x4f:
				// 	return iastore
			return IASTORE(&instruction);
		case 0x50:
				// 	return lastore
			return LASTORE(&instruction);
		case 0x51:
				// 	return fastore
			return FASTORE(&instruction);
		case 0x52:
				// 	return dastore
			return DASTORE(&instruction);
		case 0x53:
				// 	return aastore
			return AASTORE(&instruction);
		case 0x54:
				// 	return bastore
			return BASTORE(&instruction);
		case 0x55:
				// 	return castore
			return CASTORE(&instruction);
		case 0x56:
				// 	return sastore
			return SASTORE(&instruction);
		case 0x57:
			//return pop
			return POP(&instruction);
		case 0x58:
			//return pop2
			return POP2(&instruction);
		case 0x59:
			//return dup
			return DUP(&instruction);
		case 0x5a:
			//return dup_x1
			return DUP_X1(&instruction);
		case 0x5b:
			//return dup_x2
			return DUP_X2(&instruction);
		case 0x5c:
			//return dup2
			return DUP2(&instruction);
		case 0x5d:
			//return dup2_x1
			return DUP2_X1(&instruction);
		case 0x5e:
			//return dup2_x2
			return DUP2_X2(&instruction);
		case 0x5f:
			//return swap
			return SWAP(&instruction);
		case 0x60:
			//return iadd
			return IADD(&instruction);
		case 0x61:
			//return ladd
			return LADD(&instruction);
		case 0x62:
			//return fadd
			return FADD(&instruction);
		case 0x63:
			//return dadd
			return DADD(&instruction);
		case 0x64:
			//return isub
			return ISUB(&instruction);
		case 0x65:
			//return lsub
			return LSUB(&instruction);
		case 0x66:
			//return fsub
			return FSUB(&instruction);
		case 0x67:
			//return dsub
			return DSUB(&instruction);
		case 0x68:
			//return imul
			return IMUL(&instruction);
		case 0x69:
			//return lmul
			return LMUL(&instruction);
		case 0x6a:
			//return fmul
			return FMUL(&instruction);
		case 0x6b:
			//return dmul
			return DMUL(&instruction);
		case 0x6c:
			//return idiv
			return IDIV(&instruction);
		case 0x6d:
			//return ldiv
			return LDIV(&instruction);
		case 0x6e:
			//return fdiv
			return FDIV(&instruction);
		case 0x6f:
			//return ddiv
			return DDIV(&instruction);
		case 0x70:
			//return irem
			return IREM(&instruction);
		case 0x71:
			//return lrem
			return LREM(&instruction);
		case 0x72:
			//return frem
			return FREM(&instruction);
		case 0x73:
			//return drem
			return DREM(&instruction);
		case 0x74:
			//return ineg
			return INEG(&instruction);
		case 0x75:
			//return lneg
			return LNEG(&instruction);
		case 0x76:
			//return fneg
			return FNEG(&instruction);
		case 0x77:
			//return dneg
			return DNEG(&instruction);
		case 0x78:
			//return ishl
			return ISHL(&instruction);
		case 0x79:
			//return lshl
			return LSHL(&instruction);
		case 0x7a:
			//return ishr
			return ISHR(&instruction);
		case 0x7b:
			//return lshr
			return LSHR(&instruction);
		case 0x7c:
			//return iushr
			return IUSHR(&instruction);
		case 0x7d:
			//return lushr
			return IUSHR(&instruction);
		case 0x7e:
			//return iand
			return IAND(&instruction);
		case 0x7f:
			//return land
			return LAND(&instruction);
		case 0x80:
			//return ior
			return IOR(&instruction);
		case 0x81:
			//return lor
			return LOR(&instruction);
		case 0x82:
			//return ixor
			return IXOR(&instruction);
		case 0x83:
			//return lxor
			return LXOR(&instruction);
		case 0x84:
			//return &IINC{}
			return IINC(&instruction);
		case 0x85:
			//return i2l
			return I2L(&instruction);
		case 0x86:
			//return i2f
			return I2F(&instruction);
		case 0x87:
			//return i2d
			return I2D(&instruction);
		case 0x88:
			//return l2i
			return L2I(&instruction);
		case 0x89:
			//return l2f
			return L2F(&instruction);
		case 0x8a:
			//return l2d
			return L2D(&instruction);
		case 0x8b:
			//return f2i
			return F2I(&instruction);
		case 0x8c:
			//return f2l
			return F2L(&instruction);
		case 0x8d:
			//return f2d
			return F2D(&instruction);
		case 0x8e:
			//return d2i
			return D2I(&instruction);
		case 0x8f:
			//return d2l
			return D2L(&instruction);
		case 0x90:
			//return d2f
			return D2F(&instruction);
		case 0x91:
			//return i2b
			return I2B(&instruction);
		case 0x92:
			//return i2c
			return I2C(&instruction);
		case 0x93:
			//return i2s
			return I2S(&instruction);
		case 0x94:
			//return lcmp
			return LCMP(&instruction);
		case 0x95:
			//return fcmpl
			return FCMPL(&instruction);
		case 0x96:
			//return fcmpg
			return FCMPG(&instruction);
		case 0x97:			
			//return dcmpl
			return DCMPL(&instruction);
		case 0x98:
			//return dcmpg
			return DCMPG(&instruction);
		case 0x99:
			//return &IFEQ{}
			return IFEQ(&instruction);
		case 0x9a:
			//return &IFNE{}
			return IFNE(&instruction);
		case 0x9b:
			//return &IFLT{}
			return IFLT(&instruction);
		case 0x9c:
			//return &IFGE{}
			return IFGE(&instruction);
		case 0x9d:
			//return &IFGT{}
			return IFGT(&instruction);
		case 0x9e:
			//return &IFLE{}
			return IFLE(&instruction);
		case 0x9f:
			//return &IF_ICMPEQ{}
			return IF_ICMPEQ(&instruction);
		case 0xa0:
			//return &IF_ICMPNE{}
			return IF_ICMPNE(&instruction);
		case 0xa1:
			//return &IF_ICMPLT{}
			return IF_ICMPLT(&instruction);
		case 0xa2:
			//return &IF_ICMPGE{}
			return IF_ICMPGE(&instruction);
		case 0xa3:
			//return &IF_ICMPGT{}
			return IF_ICMPGT(&instruction);
		case 0xa4:
			//return &IF_ICMPLE{}
			return IF_ICMPLE(&instruction);
		case 0xa5:
			return IF_ACMPEQ(&instruction);
		case 0xa6:
			return IF_ACMPNE(&instruction);
		case 0xa7:
			//return &GOTO{}
			return GOTO(&instruction);
#if 0
			// case 0xa8:
			// 	return &JSR{}
			// case 0xa9:
			// 	return &RET{}
#endif
		case 0xaa:
			//return &TABLE_SWITCH{}
			return TABLE_SWITCH(&instruction);
		case 0xab:
			//return &LOOKUP_SWITCH{}
			return LOOKUP_SWITCH(&instruction);
		case 0xac:
			// 	return ireturn
			return IRETURN(&instruction);
		case 0xad:
			// 	return lreturn
			return LRETURN(&instruction);
		case 0xae:
			// 	return freturn
			return FRETURN(&instruction);
		case 0xaf:
			// 	return dreturn
			return DRETURN(&instruction);
		case 0xb0:
			// 	return areturn
			return ARETURN(&instruction);
		case 0xb1:
			// 	return _return
			return RETURN(&instruction);

		case 0xb2:
			//		return &GET_STATIC{}
			return GET_STATIC(&instruction);
		case 0xb3:
			// 	return &PUT_STATIC{}
			return PUT_STATIC(&instruction);
		case 0xb4:
			// 	return &GET_FIELD{}
			return GET_FIELD(&instruction);
		case 0xb5:
			// 	return &PUT_FIELD{}
			return PUT_FIELD(&instruction);
		case 0xb6:
			//		return &INVOKE_VIRTUAL{}
			return INVOKE_VIRTUAL(&instruction);
		case 0xb7:
			// 	return &INVOKE_SPECIAL{}
			return INVOKE_SPECIAL(&instruction);
		case 0xb8:
			// 	return &INVOKE_STATIC{}
			return INVOKE_STATIC(&instruction);
		case 0xb9:
			// 	return &INVOKE_INTERFACE{}
			return INVOKE_INTERFACE(&instruction);
			// case 0xba:
			// 	return &INVOKE_DYNAMIC{}
		case 0xbb:
			return NEW(&instruction);
		case 0xbc:
			// 	return &NEW_ARRAY{}
			return NEW_ARRAY(&instruction);
			// case 0xbd:
			// 	return &ANEW_ARRAY{}
		case 0xbe:
			// 	return arraylength
			return ARRAY_LENGTH(&instruction);
			// case 0xbf:
			// 	return athrow
			case 0xc0:
			// 	return &CHECK_CAST{}
				return CHECK_CAST(&instruction);
		case 0xc1:
		 	//return &INSTANCE_OF{}
			return INSTANCE_OF(&instruction);
			// case 0xc2:
			// 	return monitorenter
			// case 0xc3:
			// 	return monitorexit
		case 0xc4:
			//return &WIDE{}
			return WIDE(&instruction);
			// case 0xc5:
			// 	return &MULTI_ANEW_ARRAY{}
		case 0xc6:
			//return &IFNULL{}
			return IFNULL(&instruction);
		case 0xc7:
			//return &IFNONNULL{}
			return IFNONNULL(&instruction);
		case 0xc8:
			//return &GOTO_W{}
			return GOTO_W(&instruction);
			// case 0xc9:
			// 	return &JSR_W{}
			// case 0xca: breakpoint
			// case 0xfe: impdep1
			// case 0xff: impdep2
		default:
			printf("Unsupport Instruction:0x%02x\n", opcode);
			exit(1);
			break;
	}
	return NULL;
}