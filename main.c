#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "getopt.h"

#define MAX_JVM_ARGS	8
char classpath[128] = { 0 };
char class[128] = { 0 };
char jvmArgs[MAX_JVM_ARGS][64] = { 0 };
char jrePath[128] = { 0 };

void printUsage(void)
{
	printf("Usage: tinyjvm [--option] class [args...]\n");
}

void startJVM(const char * jrePath, const char * classpath)
{

}

int main(int argc, char ** argv)
{
	int16_t ch;
	static const char *shortOptions = "hc:";
	static struct option longOptions[] = {
		{ "help", no_argument, 0, 'h' },
		{ "classpath", required_argument, 0, 'c' },
		{ "cp", required_argument, 0, 'c'},
		{ "Xjre", required_argument, 0, 'X' },
		{ 0, 0, 0, 0 },
	};

	while ((ch = getopt_long(argc, argv, shortOptions, longOptions, 0)) != -1)
	{
		switch (ch)
		{
			case 'h':
				printUsage();
				exit(0);
				break;
			case 'c':
				strcpy(classpath, optarg);
				printf("classpath:%s\n", classpath);
				break;
			case 'X':
				strcpy(jrePath, optarg);
				printf("jre path:%s\n", jrePath);
				break;
			default:
				break;
		}	
	}
	argc -= optind;
	argv += optind;
	for (int i = 0; i < argc; i++)
	{
		if (i >= MAX_JVM_ARGS)
		{
			printf("Too many args, use the first %d args\n", MAX_JVM_ARGS);
			break;
		}
		
		strncpy((char *)&jvmArgs[i], argv[i],64);
		printf("class:%s,%d,%s\n", class, i, argv[i]);
	}

	startJVM(jrePath, classpath);

	return 0;
}