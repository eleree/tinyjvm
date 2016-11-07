#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "getopt.h"
#include "classpath\classpath.h"
#include "classfile\classfile.h"
#include "strings\strings.h"

#include "miniz\minizip.h"
#include "rtda\frame.h"
#include "rtda\local_vars.h"
#include "rtda\operand_stack.h"

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
	ClassFile * classFile = NULL;

	parseClasspath(jrepath, classpath);
	stringReplace(className, fullClassName, 128);
	stringCat(fullClassName, ".class", 128);
	classSize = readClass(fullClassName, &classContent);
	if (classSize > 0 && classContent != NULL){
		printf("class size:%d,class data:[", classSize);
		for(int32_t i = 0; i < classSize; i++)
		{
			printf("0x%02x ", classContent[i]);
		}
		printf("]\n");
	}

	classFile = parseClassData(classContent, classSize);
	printClassInfo(classFile);

	if (classContent != NULL)
		free(classContent);
}

void testMiniz(void)
{
	ZipFile * zipFile;
	printf("Test Miniz Apis\n");
	zipFile =  openZip("E:/2016/tinyjvm/Debug/test.zip");
	if (zipFile == NULL)
	{

	}

	if (zipFile != NULL)
		free(zipFile);
	exit(0);
}
int testSSHZlib(int argc, char **argv);

void testLocalVars(LocalVars * localVars)
{
	setLocalVarsInt(localVars, 0, 100);
	setLocalVarsInt(localVars, 1, -100);
	setLocalVarsLong(localVars, 2, 2997924580i64);
	setLocalVarsLong(localVars, 4, -2997924580i64);
	setLocalVarsFloat(localVars, 6, 3.1415926f);
	setLocalVarsDouble(localVars, 7, 2.71828182845);
	setLocalVarsRef(localVars, 9, NULL);
	printf("%d\n", getLocalVarsInt(localVars, 0));
	printf("%d\n", getLocalVarsInt(localVars, 1));
	printf("%lld\n", getLocalVarsLong(localVars, 2));
	printf("%lld\n", getLocalVarsLong(localVars, 4));
	printf("%f\n", getLocalVarsFloat(localVars, 6));
	printf("%f\n", getLocalVarsDouble(localVars, 7));
}

void testOperandStack(OperandStack * operandStack)
{
	pushOperandInt(operandStack, 100);
	pushOperandInt(operandStack, -100);
	pushOperandLong(operandStack, 2997924580);
	pushOperandLong(operandStack, -2997924580i64);
	pushOperandFloat(operandStack, 3.1415926f);
	pushOperandDouble(operandStack, 2.71828182845);
	pushOperandRef(operandStack, NULL);

	popOperandRef(operandStack); 
	printf("%f\n", popOperandDouble(operandStack));
	printf("%f\n", popOperandFloat(operandStack));
	printf("%lld\n", popOperandLong(operandStack));
	printf("%lld\n", popOperandLong(operandStack));
	printf("%d\n", popOperandInt(operandStack));
	printf("%d\n", popOperandInt(operandStack));

}

void testStack(void)
{
	Frame * f = newFrame(100, 100);
	printf("Test Local Vars:\n");
	testLocalVars(f->localVars);
	printf("Test Operand Stack:\n");
	testOperandStack(f->operandStack);
}

//extern void testMinizWrapper(void);
int main(int argc, char ** argv)
{	
	testStack();
	//testMinizWrapper();
	//testMiniz();
	//testSSHZlib(argc, argv);
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