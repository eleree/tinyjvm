#include "string_pool.h"
#include "class_loader.h"

// utf8 -> utf16
String * stringToUtf16(const char * s)
{

}

// utf16 -> utf8
String * utf16ToString(uint16_t * s, uint32_t len)
{

}

String goString(Object * jStr)
{

}

Object * jString(ClassLoader *loader,String * goStr )
{
	uint16_t * chars = stringToUtf16(goStr);
	Object * jChars = (Object *)calloc(1, sizeof(Object));
	jChars->data = (void*)chars;
	jChars->dataCount = 0;

	Class * strClass = loadClass(loader, "java/lang/String");
	Object * jStr = newObject(strClass);

	setObectRefVar(jStr, "value", "[C", jChars);

	return jStr;
	
}
