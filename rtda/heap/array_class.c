#include "array_class.h"

#pragma warning(disable:4996)

bool isClassArray(Class * self)
{
	return self->name[0] == '[';
}

Class * componentClass(Class * self)
{
	char * componentClassName = getComponentClassName(self->name);
	Class * newLoadClass = loadClass(self->classLoader, componentClassName);
	//free(componentClassName);
	return newLoadClass;
}


Object * newArray(Class * self, uint16_t count)
{
	Object * o = (Object *)calloc(1, sizeof(Object));

	if (!isClassArray(self))
	{
		free(o);
		printf("Not array class: %s\n", self->name);
		exit(150);	
	}
	o->class = self;
	o->dataCount = count;
	o->dataType = self->name[1];
	switch (self->name[1])
	{
	case 'Z':
		o->data = calloc(count, sizeof(int8_t));
		break;
	case 'B':
		o->data = calloc(count, sizeof(int8_t));
		break;
	case 'C':
		o->data = calloc(count, sizeof(uint16_t));
		break;
	case 'S':
		o->data = calloc(count, sizeof(int16_t));
		break;
	case 'I':
		o->data = calloc(count, sizeof(int32_t));
		break;
	case 'J':
		o->data = calloc(count, sizeof(int64_t));
		break;
	case 'F':
		o->data = calloc(count, sizeof(float));
		break;
	case 'D':
		o->data = calloc(count, sizeof(double));
		break;
	default:
		o->dataType = 'O';
		o->data = calloc(count, sizeof(Object*));
		break;
	}
	return o;
}

// [XXX => [XXX
// int  => I
// XXX  => LXXX;
char * toDescriptor(const char * className)
{
	if (className[0] == '[')
		return strdup(className);

	if (strcmp(className, "void") == 0)
		return strdup("V");
	else if (strcmp(className, "boolean") == 0)
		return strdup("Z");
	else if (strcmp(className, "byte") == 0)
		return strdup("B");
	else if (strcmp(className, "short") == 0)
		return strdup("S");
	else if (strcmp(className, "int") == 0)
		return strdup("I");
	else if (strcmp(className, "long") == 0)
		return strdup("J");
	else if (strcmp(className, "char") == 0)
		return strdup("C");
	else if (strcmp(className, "float") == 0)
		return strdup("F");
	else if (strcmp(className, "double") == 0)
		return strdup("D");
	else{

	}

	char * objectDesc = calloc(strlen(className) + 3, sizeof(char));
	strcat(objectDesc, "L");
	strcat(objectDesc, className);
	strcat(objectDesc, ";");

	return objectDesc;
}

// [XXX  => [XXX
// LXXX; => XXX
// I     => int
char * toClassName(const char * descriptor)
{
	if (descriptor[0] == '[')
		return strdup(descriptor);

	if (descriptor[0] == 'L')
	{
		uint32_t objectDescLen = strlen(descriptor);
		char * objectDesc = calloc(strlen(descriptor) + 1, sizeof(char));
		strncpy(objectDesc, descriptor + 1, strlen(descriptor) - 2);
		return objectDesc;
	}

	if (strcmp(descriptor, "V") == 0)
		return strdup("V");
	else if (strcmp(descriptor, "Z") == 0)
		return strdup("boolean");
	else if (strcmp(descriptor, "B") == 0)
		return strdup("byte");
	else if (strcmp(descriptor, "S") == 0)
		return strdup("short");
	else if (strcmp(descriptor, "I") == 0)
		return strdup("int");
	else if (strcmp(descriptor, "J") == 0)
		return strdup("long");
	else if (strcmp(descriptor, "C") == 0)
		return strdup("char");
	else if (strcmp(descriptor, "F") == 0)
		return strdup("float");
	else if (strcmp(descriptor, "D") == 0)
		return strdup("double");
	else{
		printf("Invalid descriptor: %s", descriptor);
		exit(150);
	}
}

char * getArrayClassName(const char * className)
{
	char * name = calloc(strlen(className) + 2, sizeof(char));
	strcat(name, "[");
	char * nameToDesc = toDescriptor(className);	
	strcat(name, nameToDesc); 
	//free(nameToDesc);
	return name;
}

// [[XXX -> [XXX
// [LXXX; -> XXX
// [I -> int
char * getComponentClassName(char * className)
{
	if (className[0] == '[')
	{
		char * componentTypeDescriptor = className + 1;
		return toClassName(componentTypeDescriptor);
	}
	printf("Not array: %s", className);
	exit(150);
}


void arrayCopy(Object * srcArray, Object * destArray, int32_t srcPos, int32_t dstPos, int32_t length)
{
	switch (srcArray->dataType)
	{
	case 'Z':
		for (int32_t i = 0; i < length; i++)
		{
			int8_t * src = (int8_t*)srcArray->data;
			int8_t * dst = (int8_t*)destArray->data;
			dst[i+dstPos] = src[i+srcPos];
		}
		break;
	case 'B':
		for (int32_t i = 0; i < length; i++)
		{
			int8_t * src = (int8_t*)srcArray->data;
			int8_t * dst = (int8_t*)destArray->data;
			dst[i + dstPos] = src[i + srcPos];
		}
		break;
	case 'C':
		for (int32_t i = 0; i < length; i++)
		{
			int16_t * src = (int16_t*)srcArray->data;
			int16_t * dst = (int16_t*)destArray->data;
			dst[i + dstPos] = src[i + srcPos];
		}
		break;
	case 'S':
		for (int32_t i = 0; i < length; i++)
		{
			int16_t * src = (int16_t*)srcArray->data;
			int16_t * dst = (int16_t*)destArray->data;
			dst[i + dstPos] = src[i + srcPos];
		}		
		break;
	case 'I':
		for (int32_t i = 0; i < length; i++)
		{
			int32_t * src = (int32_t*)srcArray->data;
			int32_t * dst = (int32_t*)destArray->data;
			dst[i + dstPos] = src[i + srcPos];
		}
		break;
	case 'J':
		for (int32_t i = 0; i < length; i++)
		{
			int64_t * src = (int64_t*)srcArray->data;
			int64_t * dst = (int64_t*)destArray->data;
			dst[i + dstPos] = src[i + srcPos];
		}
		break;
	case 'F':
		for (int32_t i = 0; i < length; i++)
		{
			float * src = (float*)srcArray->data;
			float * dst = (float*)destArray->data;
			dst[i + dstPos] = src[i + srcPos];
		}
		break;
	case 'D':
		for (int32_t i = 0; i < length; i++)
		{
			double * src = (double*)srcArray->data;
			double * dst = (double*)destArray->data;
			dst[i + dstPos] = src[i + srcPos];
		}
		break;
	default:
		for (int32_t i = 0; i < length; i++)
		{
			Object* * src = (Object**)srcArray->data;
			Object* * dst = (Object**)destArray->data;
			dst[i + dstPos] = src[i + srcPos];
		}
		break;
	}
}

Object * newByteArray(ClassLoader * classLoader, int8_t * bytes, uint32_t count)
{
	Object * o = (Object *)calloc(1, sizeof(Object));
	o->class = loadClass(classLoader, "[B");;
	o->dataCount = count;
	o->dataType = 'B';
	o->data = calloc(count, sizeof(int8_t));

	for (uint32_t i = 0; i < count; i++)
		((int8_t*)(o->data))[i] = bytes[i];

	return o;
}