#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/array_class.h"

static void checkNotNil(Object * o)
{
	if (o == NULL)
		panic("java.lang.NullPointerException", 154);
}

static void checkIndex(int32_t arrLen, int32_t index)
{
	if (index < 0 || index >= arrLen ){
		panic("ArrayIndexOutOfBoundsException", 154);
	}
}

// Load reference from array
int32_t execute_AALOAD(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	int32_t index = popOperandInt(operandStack);

	Object * arrRef = popOperandRef(operandStack);
	checkNotNil(arrRef);

	Object** refs = getObjectRefs(arrRef);
	checkIndex(arrRef->dataCount, index);
	pushOperandRef(operandStack, refs[index]);
	return 0;
}

Instruction * AALOAD(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_AALOAD;
	return inst;
}


// Load byte or boolean from array
int32_t execute_BALOAD(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	int32_t index = popOperandInt(operandStack);

	Object * arrRef = popOperandRef(operandStack);
	checkNotNil(arrRef);

	int8_t* bytes = getObjectBytes(arrRef);
	checkIndex(arrRef->dataCount, index);
	pushOperandInt(operandStack, bytes[index]);
	return 0;
}

Instruction * BALOAD(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_BALOAD;
	return inst;
}

// Load char from array
int32_t execute_CALOAD(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	int32_t index = popOperandInt(operandStack);

	Object * arrRef = popOperandRef(operandStack);
	checkNotNil(arrRef);

	uint16_t* chars = getObjectChars(arrRef);
	checkIndex(arrRef->dataCount, index);
	//if (arrRef->dataCount == 0x200 && index == 0x00)
	//	printf("CALOAD %d\n", chars[index]);
	pushOperandInt(operandStack, chars[index]);
	return 0;
}

Instruction * CALOAD(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_CALOAD;
	return inst;
}

// Load double from array
int32_t execute_DALOAD(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	int32_t index = popOperandInt(operandStack);

	Object * arrRef = popOperandRef(operandStack);
	checkNotNil(arrRef);

	double* doubles = getObjectDoubles(arrRef);
	checkIndex(arrRef->dataCount, index);
	pushOperandDouble(operandStack, doubles[index]);
	return 0;
}

Instruction * DALOAD(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DALOAD;
	return inst;
}

// Load float from array
int32_t execute_FALOAD(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	int32_t index = popOperandInt(operandStack);

	Object * arrRef = popOperandRef(operandStack);
	checkNotNil(arrRef);

	float* floats = getObjectFloats(arrRef);
	checkIndex(arrRef->dataCount, index);
	pushOperandDouble(operandStack, floats[index]);
	return 0;
}

Instruction * FALOAD(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_FALOAD;
	return inst;
}

// Load int from array
int32_t execute_IALOAD(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	int32_t index = popOperandInt(operandStack);

	Object * arrRef = popOperandRef(operandStack);
	checkNotNil(arrRef);

	int32_t* ints = getObjectInts(arrRef);
	checkIndex(arrRef->dataCount, index);
	pushOperandInt(operandStack, ints[index]);
	return 0;
}

Instruction * IALOAD(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_IALOAD;
	return inst;
}

// Load long from array
int32_t execute_LALOAD(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	int32_t index = popOperandInt(operandStack);

	Object * arrRef = popOperandRef(operandStack);
	checkNotNil(arrRef);

	int64_t* longs = getObjectLongs(arrRef);
	checkIndex(arrRef->dataCount, index);
	pushOperandLong(operandStack, longs[index]);
	return 0;
}

Instruction * LALOAD(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LALOAD;
	return inst;
}

// Load short from array
int32_t execute_SALOAD(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	int32_t index = popOperandInt(operandStack);

	Object * arrRef = popOperandRef(operandStack);
	checkNotNil(arrRef);

	int32_t* shorts = getObjectInts(arrRef);
	checkIndex(arrRef->dataCount, index);
	pushOperandInt(operandStack, shorts[index]);
	return 0;
}

Instruction * SALOAD(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_SALOAD;
	return inst;
}
