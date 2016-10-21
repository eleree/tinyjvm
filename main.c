#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "getopt.h"
#include "classpath\classpath.h"
#include "strings\strings.h"

#include "miniz\miniz.h"

#define MAX_JVM_ARGS	8
char classpath[128] = { 0 };
char className[128] = { 0 };
char jvmArgs[MAX_JVM_ARGS][64] = { 0 };
char jrepath[128] = { 0 };

void printUsage(void)
{
	printf("Usage: tinyjvm [--option] class [args...]\n");
}

void startJVM(const char * jrepath, const char * classpath, const char * className)
{
	int32_t classSize = 0;
	char * classContent = NULL;
	char * fullClassName = (char *)calloc(128, 1);
	parseClasspath(jrepath, classpath);
	stringReplace(className, fullClassName, 128);
	stringCat(fullClassName, ".class", 128);
	classSize = readClass(fullClassName, &classContent);
	if (classSize > 0){
		printf("class size:%d,class data:[]", classSize);
	}
}

void testMiniz(void)
{
	ZipFile * zipFile;
	printf("Test Miniz Apis\n");
	zipFile =  openZip("./Desktop.zip");
	if (zipFile == NULL)
	{

	}

	if (zipFile != NULL)
		free(zipFile);
	exit(0);
}

int main(int argc, char ** argv)
{
	testMiniz();

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
				strcpy(jrepath, optarg);
				printf("jre path:%s\n", jrepath);
				break;
			default:
				break;
		}	
	}
	argc -= optind;
	argv += optind;
	if (argc == 0)
	{
		printf("Please specify a class\n");
		exit(0);
	}
	for (int i = 0; i < argc; i++)
	{
		if (i >= MAX_JVM_ARGS)
		{
			printf("Too many args, use the first %d args\n", MAX_JVM_ARGS);
			break;
		}
		if (i == 0)
		{
			strncpy(className, argv[i], 64);
			continue;
		}
		
		strncpy((char *)&jvmArgs[i], argv[i],64);
		printf("Args:%d,%s\n", i, argv[i]);
	}

	startJVM(jrepath, classpath, className);

	return 0;
}