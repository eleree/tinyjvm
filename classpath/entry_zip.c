#include "entry.h"
#include "../strings/strings.h"

int32_t readZipEntryClass(const char * zippath, const char * className, char ** classContent)
{
	if (stringHasSuffix(zippath, ".jar") == 0 || stringHasSuffix(zippath, ".JAR") == 0 ||
		stringHasSuffix(zippath, ".zip") == 0 || stringHasSuffix(zippath, ".ZIP") == 0)
	{

	}
	return 0;
}