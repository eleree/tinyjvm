#ifndef __TINY_JVM_STRINGS_H__
#define __TINY_JVM_STRINGS_H__

#include <stdint.h>
#include <string.h>

int32_t stringReplace(const char * souceStr, char * targetStr, int32_t maxLen);
int32_t stringCat(char * sourceStr, char * targetStr, int32_t maxLen);
int32_t stringHasSuffix(const char * sourceStr, const char * suffixStr);

#endif