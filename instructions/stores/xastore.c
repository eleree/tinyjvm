#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/array_class.h"

static void checkNotNil(Object * o)
{
	if (o == NULL)
		panic("java.lang.NullPointerException\n", 154);
}

static void checkIndex(int32_t arrLen, int32_t index)
{
	if (index < 0 || index >= arrLen){
		panic("ArrayIndexOutOfBoundsException\n", 154);
	}
}

// Store into reference array
int32_t execute_AASTORE(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	Object * ref = popOperandRef(operandStack);
	int32_t index = popOperandInt(operandStack);

	Object * arrRef = popOperandRef(operandStack);
	checkNotNil(arrRef);

	Object* * refs = getObjectRefs(arrRef);
	checkIndex(arrRef->dataCount, index);

	refs[index] = ref;

	return 0;
}

Instruction * AASTORE(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_AASTORE;
	return inst;
}


// Store into byte or boolean array
int32_t execute_BASTORE(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	int32_t val = popOperandInt(operandStack);
	int32_t index = popOperandInt(operandStack);

	Object * arrRef = popOperandRef(operandStack);
	checkNotNil(arrRef);

	int8_t * refs = getObjectBytes(arrRef);
	checkIndex(arrRef->dataCount, index);

	refs[index] = (int8_t) val;

	return 0;
}

Instruction * BASTORE(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_BASTORE;
	return inst;
}

// Store into char array
int32_t execute_CASTORE(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	int32_t val = popOperandInt(operandStack);
	int32_t index = popOperandInt(operandStack);

	Object * arrRef = popOperandRef(operandStack);
	checkNotNil(arrRef);

	uint16_t * refs = getObjectChars(arrRef);
	checkIndex(arrRef->dataCount, index);

	refs[index] = (uint16_t)val;

	return 0;
}

Instruction * CASTORE(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_CASTORE;
	return inst;
}


// Store into double array
int32_t execute_DASTORE(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	double val = popOperandDouble(operandStack);
	int32_t index = popOperandInt(operandStack);

	Object * arrRef = popOperandRef(operandStack);
	checkNotNil(arrRef);

	double * doubles = getObjectDoubles(arrRef);
	checkIndex(arrRef->dataCount, index);

	doubles[index] = (double)val;

	return 0;
}

Instruction * DASTORE(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_DASTORE;
	return inst;
}


// Store into float array
int32_t execute_FASTORE(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	float val = popOperandFloat(operandStack);
	int32_t index = popOperandInt(operandStack);

	Object * arrRef = popOperandRef(operandStack);
	checkNotNil(arrRef);

	float * floats = getObjectFloats(arrRef);
	checkIndex(arrRef->dataCount, index);

	floats[index] = (float)val;

	return 0;
}

Instruction * FASTORE(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_FASTORE;
	return inst;
}


// Store into int array
int32_t execute_IASTORE(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	int32_t val = popOperandInt(operandStack);
	int32_t index = popOperandInt(operandStack);

	Object * arrRef = popOperandRef(operandStack);
	checkNotNil(arrRef);

	int32_t * refs = getObjectInts(arrRef);
	checkIndex(arrRef->dataCount, index);

	refs[index] = (int32_t)val;

	return 0;
}

Instruction * IASTORE(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_IASTORE;
	return inst;
}


// Store into long array
int32_t execute_LASTORE(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	int64_t val = popOperandLong(operandStack);
	int32_t index = popOperandInt(operandStack);

	Object * arrRef = popOperandRef(operandStack);
	checkNotNil(arrRef);

	int64_t * refs = getObjectLongs(arrRef);
	checkIndex(arrRef->dataCount, index);

	refs[index] = (int64_t)val;

	return 0;
}

Instruction * LASTORE(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_LASTORE;
	return inst;
}

// Store into short array
int32_t execute_SASTORE(Frame * frame, struct InsturctionData * instData)
{
	OperandStack * operandStack = frame->operandStack;
	LocalVars * localVars = frame->localVars;
	int16_t val = popOperandInt(operandStack);
	int32_t index = popOperandInt(operandStack);

	Object * arrRef = popOperandRef(operandStack);
	checkNotNil(arrRef);

	int16_t * refs = getObjectShorts(arrRef);
	checkIndex(arrRef->dataCount, index);

	refs[index] = (int16_t)val;

	return 0;
}

Instruction * SASTORE(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_SASTORE;
	return inst;
}

