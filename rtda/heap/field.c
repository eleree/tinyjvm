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
		c->fields[i].classMember.classPtr = c;
		copyFieldInfo(&c->fields[i], &classFile->fields[i], classFile);
		copyAttributes(&c->fields[i], &classFile->fields[i], classFile);
	}

	return NULL;
}