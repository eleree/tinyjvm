#include "string_pool.h"
#include "class_loader.h"
#include "object.h"

#pragma warning(disable:4996)


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
	String * s = calloc(1, sizeof(String));
	Object * charArr = getObjectRefVar(jStr, "value", "[C");
	uint16_t * utf16Arr = (uint16_t*) charArr->data;
	char * utf8Arr = calloc(charArr->dataCount+1, sizeof(char));
	s->data = utf8Arr;
	for(uint16_t i = 0; i < charArr->dataCount; i++)
	{
		if (utf16Arr[i] < 127)
			((char *)s->data)[i] = (char)utf16Arr[i];
	}
	s->len = charArr->dataCount;
	
	return s;
}

// mutf8 string -> java.lang.String
Object * jString(ClassLoader *loader, String * mutf8Str)
{
	Object * jChars = (Object *)calloc(1, sizeof(Object));
	uint32_t charsLen = 0;
	uint16_t * chars = decodeMutf8ToUtf16(mutf8Str->data, mutf8Str->len, &charsLen);
	jChars->data = (void *)chars;
	jChars->dataCount =(uint16_t) charsLen;
	jChars->dataType = 'u';

	Class * strClass = loadClass(loader, "java/lang/String");
	Object * jStr = newObject(strClass);

	setObectRefVar(jStr, "value", "[C", jChars);

	return jStr;
}

uint16_t *  decodeMutf8ToUtf16(const char * srcStr, uint32_t srcLen, uint32_t * resultLen)
{
	uint32_t utflen = srcLen;
	uint16_t * chararr = calloc(utflen, sizeof(uint16_t));

	uint16_t c, char2, char3 = 0;
	uint32_t count = 0;
	uint32_t chararr_count = 0;

	while (count < utflen)
	{
		c = (uint16_t)(srcStr[count]);
		if (c>127)
			break;
		count++;
		chararr[chararr_count] = c;
		chararr_count++;
	}

	while (count < utflen)
	{
		c = (uint16_t)(srcStr[count]);
		switch (c >> 4)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			count++;
			chararr[chararr_count] = c;
			chararr_count++;
			break;
		case 12:
		case 13:
			/* 110x xxxx   10xx xxxx*/
			count += 2;
			if( count > utflen){
				panic("malformed input: partial character at end",-1);
			}
			char2 = (uint16_t)(srcStr[count - 1]);
			if ((char2 & 0xC0 )!= 0x80 ){
				panic("malformed input around byte",-1);
			}
			chararr[chararr_count] = c & 0x1F << 6 | char2 & 0x3F;
			chararr_count++;
			break;
		case 14:
			/* 1110 xxxx  10xx xxxx  10xx xxxx*/
			count += 3;
			if (count > utflen){
				panic("malformed input: partial character at end", -1);
			}
			char2 = (uint16_t)(srcStr[count - 2]);
			char3 = (uint16_t)(srcStr[count - 1]);
			if( (char2 & 0xC0) != 0x80 || (char3 & 0xC0) != 0x80 ){
				panic("malformed input around byte %v", (count - 1));
			}
			chararr[chararr_count] = c & 0x0F << 12 | char2 & 0x3F << 6 | char3 & 0x3F << 0;
			chararr_count++;
			break;
		}
	}
	*resultLen = chararr_count;
	return chararr;
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
	const char * mutf8Str = getConstantPoolMutf8(classFile, stringInfo->string_index);
	uint16_t mutf8StrLen = getConstantPoolMutf8Len(classFile, stringInfo->string_index);
	s->type = STRING_TYPE_MUTF8;
	s->data = strdup(mutf8Str);
	s->len = mutf8StrLen;
	return s;
}