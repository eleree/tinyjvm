#include "registry.h"

#pragma warning(disable:4996)
static NativeMethodList * nativeMethodList;

static void emptyNativeMethod(Frame *frame)
{
	// do nothing
}

NativeMethod findNativeMethod(const char * className, const char * methodName, const char * methodDescriptor)
{
	char * key = calloc(strlen(className) + strlen(methodName) + strlen(methodDescriptor) + 3, sizeof(char));
	strcat(key, className);
	strcat(key, "~");
	strcat(key, methodName);
	strcat(key, "~");
	strcat(key, methodDescriptor);
	
	NativeMethodList * listNode = nativeMethodList;
	while (listNode != NULL)
	{
		if (strcmp(listNode->name, key) == 0)
			return listNode->method;
		listNode = listNode->next;
	}
	
	if (strcmp(methodDescriptor, "()V") == 0 &&
		strcmp(methodName, "registerNatives") == 0)
		return emptyNativeMethod;

	return NULL;
}

void registerNativeMethod(const char * className, const char * methodName, const char * methodDescriptor, NativeMethod method)
{
	char * key = calloc(strlen(className) + strlen(methodName) + strlen(methodDescriptor) + 3, sizeof(char));
	strcat(key, className);
	strcat(key, "~");
	strcat(key, methodName);
	strcat(key, "~");
	strcat(key, methodDescriptor);

	NativeMethod nativeMethod = findNativeMethod(className, methodName,methodDescriptor);
	if (nativeMethod != NULL)
	{
		free(key);
		return;
	}
	

	NativeMethodList * listNewNode = calloc(1, sizeof(NativeMethodList));
	listNewNode->name = key;
	listNewNode->method = method;

	if (nativeMethodList == NULL)
	{
		nativeMethodList = listNewNode;
		return;
	}
	NativeMethodList * listNode = nativeMethodList;
	while (listNode->next != NULL)
	{
		listNode = listNode->next;
	}

	listNode->next = listNewNode;

	return;
}