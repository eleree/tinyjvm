#include "field.h"

void copyFieldInfo(Field * field, FieldInfo * fieldInfo, ClassFile * classFile)
{
	field->classMember.accessFlags = fieldInfo->access_flags;
	field->classMember.descriptor = _strdup(getClassUtf8(classFile, fieldInfo->descriptor_index));
	field->classMember.name = _strdup(getClassUtf8(classFile, fieldInfo->name_index));
}

static void copyAttributes(Field * field, FieldInfo * fieldInfo, ClassFile * classFile)
{
	uint16_t attrCount = fieldInfo->attributes_count;
	for (uint16_t i = 0; i < attrCount; i++)
	{
		const char * attrName = getClassUtf8(classFile, fieldInfo->attributes[i].attributeNameIndex);
		if (strcmp(attrName, "ConstantValue") == 0){
			ConstantValueAttribute * constAttr = fieldInfo->attributes[i].info;
			field[i].constValueIndex = constAttr->constantvalue_index;
			break;
		}
	}
}

Field * newFields(struct Class * c, ClassFile * classFile)
{
	c->fieldsCount = classFile->fieldsCount;
	c->fields = NULL;
	if (c->fieldsCount == 0)
		return NULL;
	
	c->fields = calloc(classFile->fieldsCount, sizeof(Field));
	for (uint16_t i = 0; i < c->fieldsCount; i++)
	{
		c->fields[i].classMember.attachClass = c;
		copyFieldInfo(&c->fields[i], &classFile->fields[i], classFile);
		copyAttributes(&c->fields[i], &classFile->fields[i], classFile);
	}

	return NULL;
}


bool isFieldVolatile(Field * field)
{
	return 0 != (field->classMember.accessFlags & ACC_VOLATILE);
}

bool isFieldTransient(Field * field)
{
	return 0 != (field->classMember.accessFlags & ACC_TRANSIENT);
}

bool isFieldEnum(Field * field)
{
	return 0 != (field->classMember.accessFlags & ACC_ENUM);
}

bool isFieldLongOrDouble(Field * field)
{
	if (field->classMember.descriptor[0] == 'J' || field->classMember.descriptor[0] == 'D')
		return true;

	return false;
}


bool isFieldPublic(Field * field)
{
	if (field == NULL)
		return false;

	return	0 != (field->classMember.accessFlags & ACC_PUBLIC);
}

bool isFieldPrivate(Field * field)
{
	if (field == NULL)
		return false;

	return	0 != (field->classMember.accessFlags & ACC_PRIVATE);
}

bool isFieldProtected(Field * field)
{
	if (field == NULL)
		return false;

	return	0 != (field->classMember.accessFlags & ACC_PROTECTED);
}

bool isFieldStatic(Field * field)
{
	if (field == NULL)
		return false;

	return	0 != (field->classMember.accessFlags & ACC_STATIC);
}

bool isFieldFinal(Field * field)
{
	if (field == NULL)
		return false;

	return	0 != (field->classMember.accessFlags & ACC_FINAL);
}

bool isFieldSynthetic(Field * field)
{
	if (field == NULL)
		return false;

	return	0 != (field->classMember.accessFlags & ACC_SYNTHETIC);
}

bool isFieldAccessibleTo(Field * field, Class * d)
{
	Class * c = field->classMember.attachClass;

	if (isFieldProtected(field))
	{
		return	c == d || 
				strcmp(c->packageName,d->packageName) == 0 ||
				isSubClassOf(d,c);
	}

	if (isFieldPublic(field))
		return true;

	if (!isFieldPrivate(field))
	{
		return strcmp(c->packageName, d->packageName) == 0;
	}

	return d == c;
}

//refelction
Class * fieldType(Field * self)
{
	char * className = toClassName(self->classMember.descriptor);
	return loadClass(self->classMember.attachClass->classLoader, className);
}