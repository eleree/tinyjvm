#include "constant_pool.h"

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
