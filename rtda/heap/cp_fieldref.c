#include "cp_fieldref.h"

#pragma warning(disable:4996)

FieldRef * newFieldRef(ClassFile *classFile, struct ConstantPool * cp, ConstantFieldrefInfo * fieldRefInfo)
{
	FieldRef * fieldRef = calloc(1, sizeof(FieldRef));
	fieldRef->field = NULL;
	fieldRef->symRef.constantPool = cp;
	fieldRef->symRef.className = strdup(getClassUtf8(classFile, fieldRefInfo->classIndex));
	fieldRef->name = strdup(getConstalPoolNameAndTypeName(classFile->constantPoolItem, fieldRefInfo->name_and_type_index));
	fieldRef->descriptor = strdup(getConstalPoolNameAndTypeDescriptor(classFile->constantPoolItem, fieldRefInfo->name_and_type_index));;
	return fieldRef;
}

Field * lookupField(Class * c, char * name, char * descriptor)
{
	for (uint16_t i = 0; i < c->fieldsCount; i++)
	{
		if (strcmp(c->fields[i].classMember.name, name) == 0 &&
			strcmp(c->fields[i].classMember.descriptor, descriptor) == 0)
			return c->fields + i;
	}

	for (uint16_t i = 0; i < c->interfacesCount; i++)
	{
		Field * field = lookupField(c->interfaces[i], name, descriptor);
		if (field != NULL)
			return field;
	}

	if (c->superClass != NULL)
		return lookupField(c->superClass, name, descriptor);

	return NULL;
}

void resolvedFieldRef(FieldRef * fieldRef)
{
	//Class * d = fieldRef->symRef.class;
	Class * c = resolveClass(&fieldRef->symRef);
	Field * field = lookupField(c, fieldRef->name, fieldRef->descriptor);

	if (field == NULL)
	{
		printf("java.lang.NoSuchFieldError\n");
		exit(-1);
	}

	if(!isFieldAccessibleTo(field,c)) {
		printf("java.lang.IllegalAccessError\n");
		exit(-1);
	}

	fieldRef->field = field;
}

Field * resolvedField(FieldRef * fieldRef)
{
	if (fieldRef->field == NULL)
	{
		resolvedFieldRef(fieldRef);
	}

	return fieldRef->field;
}