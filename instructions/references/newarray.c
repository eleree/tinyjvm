#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"
#include "../../rtda/heap/array_class.h"

enum
{
	//Array Type  atype
	AT_BOOLEAN = 4,
	AT_CHAR = 5,
	AT_FLOAT = 6,
	AT_DOUBLE = 7,
	AT_BYTE = 8,
	AT_SHORT = 9,
	AT_INT = 10,
	AT_LONG = 11,
};

// Create new array
typedef struct NewArrayData {
	uint8_t atype;
}NewArrayData;

static NewArrayData newArrayData;

static int32_t fetchOperands_NEW_ARRAY(BytecodeReader * bytecoderReader, InstructionData * instData)
{
	newArrayData.atype = readBytecodeUint8(bytecoderReader);
	return 0;
}

Class * getPrimitiveArrayClass(ClassLoader * classLoader, uint8_t atype)
{
	switch (atype)
	{
	case AT_BOOLEAN:
		return loadClass(classLoader, "[Z");
		break;
	case AT_BYTE:
		return loadClass(classLoader, "[B");
		break;
	case AT_CHAR:
		return loadClass(classLoader, "[C");
		break;
	case AT_FLOAT:
		return loadClass(classLoader, "[F");
		break;
	case AT_DOUBLE:
		return loadClass(classLoader, "[D");
		break;
	case AT_SHORT:
		return loadClass(classLoader, "[S");
		break;
	case AT_INT:
		return loadClass(classLoader, "[I");
		break;
	case AT_LONG:
		return loadClass(classLoader, "[J");
		break;
	}
	return NULL;
}

static int32_t execute_NEW_ARRAY(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	int32_t count = popOperandInt(operandStack);
	if (count < 0)
		panic("java.lang.NegativeArraySizeException", 154);

	ClassLoader *  classLoader = frame->method->classMember.attachClass->classLoader;
	Class * arrClass = getPrimitiveArrayClass(classLoader, newArrayData.atype);
	Object * arr = newArray(arrClass, count);
	pushOperandRef(operandStack, arr);
	return 0;
}

Instruction * NEW_ARRAY(Instruction * inst)
{
	inst->fetchOperands = fetchOperands_NEW_ARRAY;
	inst->execute = execute_NEW_ARRAY;
	return inst;
}
