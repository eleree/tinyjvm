#include "../../registry.h"

#pragma warning(disable:4996)

const char * jlThrowable = "java/lang/Throwable";

typedef struct StackTraceElement {
	char * fileName;
	char * className;
	char * methodName;
	int32_t lineNumber;
}StackTraceElement;

StackTraceElement * createStackTraceElement(Frame * frame)
{
	Method * method = frame->method;
	Class * c = method->classMember.attachClass;
	StackTraceElement * stackTraceElement = calloc(1, sizeof(StackTraceElement));
	//stackTraceElement->fileName = strdup();
	stackTraceElement->className = strdup(c->name);
	stackTraceElement->methodName = strdup(method->classMember.name);
	//stackTraceElement->lineNumber = 
	return stackTraceElement;
}

int32_t distanceToObject(Class * c)
{
	return 0;
}

StackTraceElement * createStackTraceElements(Object * tObj, Thread * thread)
{
	return NULL;
}

// private native Throwable fillInStackTrace(int dummy);
// (I)Ljava/lang/Throwable;
void  fillInStackTrace(Frame * frame)
{

}

void initNativeThrowable(void)
{
	registerNativeMethod(jlThrowable, "fillInStackTrace", "(I)Ljava/lang/Throwable;", fillInStackTrace);
}