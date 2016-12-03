#include "../../registry.h"

// []*Class => Class[]
Object * toClassArr(ClassLoader * classLoader, Class * *interfaces, uint16_t interfacesCount)
{

	Class * classClass = loadClass(classLoader, "java/lang/Class");
	Class * classArrClass = arrayClass(classClass);
	Object * classArr = newArray(classArrClass, interfacesCount);

	if (interfacesCount > 0)
	{
		Object* * classObjs = getObjectRefs(classArr);
		for (uint16_t i = 0; i < interfacesCount; i++)
		{
			Class * c = interfaces[i];
			classObjs[i] = c->jClass;
		}
	}

	return classArr;
}

// []byte => byte[]
Object * toByteArr(ClassLoader * classLoader, uint8_t * goBytes, uint32_t  bytesLen)
{
	if (goBytes != NULL)
	{
		return newByteArray(classLoader, (int8_t *)goBytes, bytesLen);
	}
	return NULL;
}

Object * getSignatureStr(ClassLoader * classLoader, char * signature)
{
	if (signature == NULL)
		return NULL;

	if (strcmp(signature, "") != 0)
	{
		String tempStr = { 0 };
		tempStr.data = signature;
		tempStr.len = strlen(signature);
		return jString(classLoader, &tempStr);
	}
	return NULL;
}
