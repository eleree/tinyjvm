#include "classpath.h"

static char _jrepath[128] = { 0 };
static char _classpath[128] = { 0 };

int32_t parseClasspath(const char * jrepath, const char * classpath)
{
	if (jrepath != NULL)
		strncpy_s(_jrepath, 128, jrepath, 128);
	if (classpath != NULL)
		strncpy_s(_classpath,128, classpath, 128);

	return 0;
}

int32_t readClass(const char * className)
{
	if (className != NULL)
		printf("class name: %s\n",className);
	return 0;
}