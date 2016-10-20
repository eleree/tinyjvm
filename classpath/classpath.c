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

int32_t bootClasspathReadClass(const char * className, char ** classContent)
{

	return 0;
}

int32_t extClasspathReadClass(const char * className, char ** classContent)
{
	return 0;
}

int32_t userClasspathReadClass(const char * className, char ** classContent)
{
	return 0;
}

int32_t readClass(const char * className, char ** classContent)
{
	int32_t classSize = 0;
	if (className != NULL)
		printf("class name: %s\n",className);

	if ((classSize = bootClasspathReadClass(className, classContent) )> 0)
	{
		return classSize;
	}

	if ((classSize = extClasspathReadClass(className, classContent))> 0)
	{
		return classSize;
	}

	if ((classSize = userClasspathReadClass(className, classContent))> 0)
	{
		return classSize;
	}

	return 0;
}