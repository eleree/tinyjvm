#ifndef __TINY_JVM_HEAP_UTILS_H__
#define __TINY_JVM_HEAP_UTILS_H__

#include "rtda.h"

float intToFloat(int32_t i);
int32_t floatToInt(float f);
double longToDouble(uint64_t l);
int64_t doubleToLong(double d);
int64_t intToLong(uint32_t high, uint32_t low);
double intToDouble(uint32_t high, uint32_t low);

#endif