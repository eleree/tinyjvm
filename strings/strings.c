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
