#include "constant_pool.h"

int16_t getClassContantPoolType(ConstantPoolItem * cp, uint16_t index)
{
	if ((cp + index)->itemInfo != NULL)
		return ((ClassConstantInteger *)((cp + index)->itemInfo))->tag;
	printf("getClassContantPoolType NULL pointer \n ");
	exit(0);
}

int32_t getClassConstantPoolInt(ConstantPoolItem * cp, uint16_t index)
{
	if ((cp + index)->itemInfo != NULL)
		return ((ClassConstantInteger *)((cp + index)->itemInfo))->val;
	return 0;
}


float getClassConstantPoolFloat(ConstantPoolItem * cp, uint16_t index)
{
	if ((cp + index)->itemInfo != NULL)
		return ((ClassConstantFloat *)((cp + index)->itemInfo))->val;
	return 0;
}


int64_t getClassConstantPoolLong(ConstantPoolItem * cp, uint16_t index)
{
	if ((cp + index)->itemInfo != NULL)
		return ((ClassConstantLong *)((cp + index)->itemInfo))->val;
	return 0;
}

double getClassConstantPoolDouble(ConstantPoolItem * cp, uint16_t index)
{
	if ((cp + index)->itemInfo != NULL)
		return ((ClassConstantDouble *)((cp + index)->itemInfo))->val;
	return 0;
}


ClassRef * getClassConstantPoolClassRef(ConstantPoolItem * cp, uint16_t index)
{
	if ((cp + index)->itemInfo != NULL)
		return ((ClassConstantClassRef *)((cp + index)->itemInfo))->classRef;
	return 0;
}

FieldRef * getClassConstantPoolFieldRef(ConstantPoolItem * cp, uint16_t index)
{
	if ((cp + index)->itemInfo != NULL)
		return ((ClassConstantFieldRef *)((cp + index)->itemInfo))->fieldRef;
	return 0;
}

MethodRef * getClassConstantPoolMethodRef(ConstantPoolItem * cp, uint16_t index)
{
	if ((cp + index)->itemInfo != NULL)
		return ((ClassConstantMethodRef *)((cp + index)->itemInfo))->methodRef;
	return 0;
}
