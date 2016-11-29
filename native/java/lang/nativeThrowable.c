#include "../../registry.h"

#pragma warning(disable:4996)

const char * jlThrowable = "java/lang/Throwable";

StackTraceElement * createStackTraceElement(Frame * frame)
{
	Method * method = frame->method;
	Class * c = method->classMember.attachClass;
	StackTraceElement * stackTraceElement = calloc(1, sizeof(StackTraceElement));
	stackTraceElement->fileName = strdup(c->sourceFile);
	stackTraceElement->className = strdup(c->name);
	stackTraceElement->methodName = strdup(method->classMember.name);
	stackTraceElement->lineNumber = getMethodLineNumber(method, frame->nextPC-1);
	return stackTraceElement;
}

int32_t distanceToObject(Class * testClass)
{
	int32_t distance = 0;
	Class * c = testClass->superClass;
	while (c != NULL)
	{
		distance++;
		c = c->superClass;
	}
	
	return distance;
}

StackTraceElement* * createStackTraceElements(Object * tObj, Thread * thread, int32_t * elementCount)
{
	int32_t skip = distanceToObject(tObj->class) + 2;
	int32_t remainFrame = 0;

	Frame* * frames = getThreadFrames(thread, skip, &remainFrame);
	StackTraceElement* *stes = calloc(remainFrame, sizeof(StackTraceElement*));

	for (int32_t i = 0; i < remainFrame; i++)
	{
		stes[i] = createStackTraceElement(frames[i]);
	}

	*elementCount = remainFrame;

	return stes;
}

// private native Throwable fillInStackTrace(int dummy);
// (I)Ljava/lang/Throwable;
void  fillInStackTrace(Frame * frame)
{
	Object * thisObject = getLocalVarsThis(frame->localVars);
	pushOperandRef(frame->operandStack,thisObject);
	int32_t stesSize;
	StackTraceElement* *stes = createStackTraceElements(thisObject, frame->thread, &stesSize);
	thisObject->extra = (void*)stes;
	thisObject->extraCount = stesSize;
	thisObject->extraType = 'e';
}

void initNativeThrowable(void)
{
	registerNativeMethod(jlThrowable, "fillInStackTrace", "(I)Ljava/lang/Throwable;", fillInStackTrace);
}