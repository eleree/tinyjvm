#include "strings.h"

int32_t stringReplace(const char * sourceStr, char * targetStr, int32_t maxLen)
{
	int32_t sourceLen = strlen(sourceStr);

	for (int32_t i = 0; i < sourceLen; i++)
	{
		if (*(sourceStr + i) == '.')
		{
			*(targetStr + i) = '/';
			continue;
		}
		*(targetStr + i) = *(sourceStr + i);
	}

	return 0;
}

int32_t stringCat(char * sourceStr, char * targetStr, int32_t maxLen)
{

	int32_t targeLen = strlen(targetStr);
	int32_t sourceLen = strlen(sourceStr);

	if (sourceStr == NULL || targetStr == NULL)
		return -1;

	for (int i = 0; i < targeLen; i++)
	{
		*(sourceStr + sourceLen + i) = *(targetStr + i);
	}

	return 0;
}

int32_t stringHasSuffix(const char * sourceStr, const char * suffixStr)
{

	int32_t suffixLen = strlen(suffixStr);
	int32_t sourceLen = strlen(sourceStr);

	if (sourceStr == NULL || suffixStr == NULL)
		return -1;

	if (strlen(sourceStr) < strlen(suffixStr))
		return -1;

	for (int32_t i = 0; i < (int32_t)strlen(suffixStr); i++)
	{
		if (*(sourceStr + sourceLen - suffixLen + i) != *(suffixStr + i))
		{
			return -2;
		}
	}

	return 0;
}