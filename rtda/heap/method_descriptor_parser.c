#include "method.h"
#include "../../strings/strings.h"

#pragma warning(disable:4996)

static char * parseFieldType(MethodDescriptorParser * self);

static void causePanic(MethodDescriptorParser * self)
{
	printf("BAD descriptor: %s\n", self->raw);
	exit(128);
}

static uint8_t readUint8(MethodDescriptorParser * self)
{
	uint8_t b = self->raw[self->offset];
	self->offset++;
	return b;
}

static void unreadUint8(MethodDescriptorParser * self)
{
	self->offset--;
}

static void startParams(MethodDescriptorParser * self)
{
	if (readUint8(self) != '(')
		causePanic(self);
}

static void endParams(MethodDescriptorParser * self)
{
	if (readUint8(self) != ')')
		causePanic(self);
}

static void finish(MethodDescriptorParser * self)
{
	if (self->offset != strlen(self->raw))
		causePanic(self);
}


static char * parseObjectType(MethodDescriptorParser * self)
{
	char * unread = &self->raw[self->offset];
	int32_t semicolonIndex = stringIndexRune(unread, ';');
	if (semicolonIndex == -1)
	{
		causePanic(self);
		return NULL;
	}
	else
	{
		uint16_t objStart = self->offset - 1;
		uint16_t objEnd = self->offset + semicolonIndex + 1;
		self->offset = objEnd;
		char * descriptor = calloc(objEnd - objStart + 1, sizeof(char));
		strncpy(descriptor, self->raw + objStart, objEnd - objStart);
		return descriptor;
	}
}

static char * parseArrayType(MethodDescriptorParser * self)
{
	uint16_t arrStart = self->offset - 1;
	parseFieldType(self);
	uint16_t arrEnd = self->offset;
	char * descriptor = calloc(arrEnd - arrStart + 1, sizeof(char));
	strncpy(descriptor, self->raw + arrStart, arrEnd - arrStart);

	return descriptor;		
}

static char * parseFieldType(MethodDescriptorParser * self)
{
	switch(readUint8(self))
	{
	case 'B':
		return _strdup("B");
	case 'C':
		return _strdup("C");
	case 'D':
		return _strdup("D");
	case 'F':
		return _strdup("F");
	case 'I':
		return _strdup("I");
	case 'J':
		return _strdup("J");
	case 'S':
		return _strdup("S");
	case 'Z':
		return _strdup("Z");
	case 'L':
		return parseObjectType(self);
	case '[':
		return parseArrayType(self);
	default:
		unreadUint8(self);
		return "";
	}
	return "";
}

static void parseParamTypes(MethodDescriptorParser * self)
{
	for (;;)
	{
		char * t = parseFieldType(self);
		if (strcmp(t, "") != 0)
			addParameterType(self->parsed, t);
		else
			break;		
	}
}

static void parseReturnType(MethodDescriptorParser * self)
{
	if (readUint8(self) == 'V')
	{
		self->parsed->returnType = _strdup("V");
		return;
	}
	unreadUint8(self);
	char * t = parseFieldType(self);
	if (strcmp(t, "") != 0)
	{
		self->parsed->returnType = t;
		return;
	}

	causePanic(self);
}

static MethodDescriptor * parse(MethodDescriptorParser * self, const char * descriptor)
{
	self->raw = _strdup(descriptor);
	self->parsed = calloc(1, sizeof(MethodDescriptor));
	startParams(self);
	parseParamTypes(self);
	endParams(self);
	parseReturnType(self);
	finish(self);
	return self->parsed;
}

MethodDescriptor * parseMethodDescriptor(const char * descriptor)
{
	MethodDescriptorParser * parser = calloc(1, sizeof(MethodDescriptorParser));
	return parse(parser, descriptor);
}