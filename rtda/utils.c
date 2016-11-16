#include "utils.h"

float intToFloat(int32_t i)
{
	FloatInt transData;
	transData.bitsData = i;
	return transData.floatData;
}

int32_t floatToInt(float f)
{
	FloatInt transData;
	transData.floatData = f;
	return (int32_t)transData.bitsData;
}

int64_t intToLong(uint32_t high, uint32_t low)
{
	LongInt transData;
	transData.high = high;
	transData.low = low;
	return transData.longData;
}

double longToDouble(uint64_t l)
{
	DoubleLong transData;
	transData.bitsData = l;
	return transData.doubleData;
}

double intToDouble(uint32_t high, uint32_t low)
{
	return longToDouble(intToLong(high, low));
}

int64_t doubleToLong(double d)
{
	DoubleLong transData;
	transData.doubleData = d;
	return (int64_t)transData.bitsData;
}

