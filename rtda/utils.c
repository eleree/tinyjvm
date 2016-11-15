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

double longToDouble(int64_t l)
{
	DoubleLong transData;
	transData.bitsData = l;
	return transData.doubleData;
}

int64_t doubleToLong(double d)
{
	DoubleLong transData;
	transData.doubleData = d;
	return (int64_t)transData.bitsData;
}

