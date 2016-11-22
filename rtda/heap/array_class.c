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
		o->data = calloc(count, sizeof(int16_t));
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
		char * objectDesc = calloc(strlen(descriptor) - 1, sizeof(char));
		strncpy(objectDesc, descriptor + 1, strlen(descriptor) - 1);
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
	strcat(name, className);
	return name;
}

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
