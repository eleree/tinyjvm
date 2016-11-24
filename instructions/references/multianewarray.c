#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"
#include "../../rtda/heap/array_class.h"

// Create new multidimensional array
typedef struct MultiAnewArrayData{
	uint16_t index;
	uint8_t dimensions;
}MultiAnewArrayData;

static MultiAnewArrayData multiAnewArrayData;

int32_t * popAndCheckCounts(OperandStack * operandStack, int32_t dimensions)
{
	int32_t * counts = calloc(dimensions, sizeof(int32_t));
	for (int32_t i = dimensions - 1; i >= 0; i--)
	{
		counts[i] = popOperandInt(operandStack);
		if (counts[i] < 0)
		{
			panic("java.lang.NegativeArraySizeException", 155);
		}
	}

	return counts;
}

Object * newMultiDimensionalArray(int32_t * counts, int32_t countsLen, Class * arrClass)
{
	int32_t count = counts[0];
	Object * arr = newArray(arrClass, count);

	if (countsLen > 1)
	{
		Object* *	refs = getObjectRefs(arr);
		for (int32_t i = 0; i < arr->dataCount; i++)
		{
			refs[i] = newMultiDimensionalArray(counts + 1, countsLen - 1, componentClass(arrClass));
		}
	}
	return arr;
}

static int32_t fetchOperands_MULTI_ANEW_ARRAY(BytecodeReader * bytecoderReader, InstructionData * instData)
{
	multiAnewArrayData.index = readBytecodeUint16(bytecoderReader);
	multiAnewArrayData.dimensions = readBytecodeUint8(bytecoderReader);
	return 0;
}

int32_t execute_MULTI_ANEW_ARRAY(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	ConstantPoolItem * cp = frame->method->classMember.attachClass->constantPool.constantPoolItem;
	ClassRef * classRef = getClassConstantPoolClassRef(cp, multiAnewArrayData.index);

	Class * arrClass = resolveClass(&classRef->symRef);

	int32_t * counts = popAndCheckCounts(operandStack, multiAnewArrayData.dimensions);
	Object * arr = newMultiDimensionalArray(counts, multiAnewArrayData.dimensions, arrClass);

	pushOperandRef(operandStack, arr);

	free(counts);
	return 0;
}

Instruction * MULTI_ANEW_ARRAY(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_MULTI_ANEW_ARRAY;
	return inst;
}

