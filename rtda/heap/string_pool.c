#include "string_pool.h"
#include "class_loader.h"

// utf8 -> utf16
String * stringToUtf16(const char * s)
{
	return NULL;
}

// utf16 -> utf8
String * utf16ToString(uint16_t * s, uint32_t len)
{
	return NULL;
}

String * goString(Object * jStr)
{
	return NULL;
}

// mutf8 string -> java.lang.String
Object * jString(ClassLoader *loader, String * mutf8Str)
{
	Object * jChars = (Object *)calloc(1, sizeof(Object));
	jChars->data = mutf8Str->data;
	jChars->dataCount = mutf8Str->len;
	jChars->dataType = 'A';
	Class * strClass = loadClass(loader, "java/lang/String");
	Object * jStr = newObject(strClass);

	setObectRefVar(jStr, "value", "[C", jChars);

	return jStr;
}

char *  decodeMutf8ToUtf8(const char * srcStr, uint16_t srcLen, uint16_t * resultLen)
{
	return NULL;
}

uint16_t * encodeUtf8ToUtf16(const char * utf8Str, uint16_t utf8Len, uint16_t * resultLen)
{
	return NULL;
}

char * decodeUtf16ToUtf8(const uint16_t * utf16Str, uint16_t utf16Len, uint16_t * resultLen)
{
	return NULL;
}

String * newString(ClassFile *classFile, struct ConstantPool * cp, ConstantStringInfo * stringInfo)
{
	String * s = calloc(1, sizeof(String));
	//char * mutf8Str = getConstantPoolMutf8(cp->constantPoolItem, stringInfo->string_index);
	uint16_t mutf8StrLen = getConstantPoolMutf8Len(cp->constantPoolItem, stringInfo->string_index);

	return s;
}