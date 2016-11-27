#include "object.h"
#include "slot.h"

Object * cloneObject(Object * self)
{
	Object * newObject = calloc(1, sizeof(Object));
	int32_t count = self->dataCount;
	newObject->class = self->class;
	switch (self->dataType)
	{
	case 'Z':
		newObject->data = calloc(count, sizeof(int8_t));
		for (int32_t i = 0; i < count; i++)
		{
			int8_t * src = (int8_t*)self->data;
			int8_t * dst = (int8_t*)newObject->data;
			dst[i] = src[i];
		}
		break;
	case 'B':
		newObject->data = calloc(count, sizeof(int8_t));
		for (int32_t i = 0; i < count; i++)
		{
			int8_t * src = (int8_t*)self->data;
			int8_t * dst = (int8_t*)newObject->data;
			dst[i] = src[i];
		}
		break;
	case 'C':
		newObject->data = calloc(count, sizeof(int16_t));
		for (int32_t i = 0; i < count; i++)
		{
			int16_t * src = (int16_t*)self->data;
			int16_t * dst = (int16_t*)newObject->data;
			dst[i] = src[i];
		}
		break;
	case 'S':
		newObject->data = calloc(count, sizeof(int16_t));
		for (int32_t i = 0; i < count; i++)
		{
			int16_t * src = (int16_t*)self->data;
			int16_t * dst = (int16_t*)newObject->data;
			dst[i] = src[i];
		}
		break;
	case 'I':
		newObject->data = calloc(count, sizeof(int32_t));
		for (int32_t i = 0; i < count; i++)
		{
			int32_t * src = (int32_t*)self->data;
			int32_t * dst = (int32_t*)newObject->data;
			dst[i] = src[i];
		}
		break;
	case 'J':
		newObject->data = calloc(count, sizeof(int64_t));
		for (int32_t i = 0; i < count; i++)
		{
			int64_t * src = (int64_t*)self->data;
			int64_t * dst = (int64_t*)newObject->data;
			dst[i] = src[i];
		}
		break;
	case 'F':
		newObject->data = calloc(count, sizeof(float));
		for (int32_t i = 0; i < count; i++)
		{
			float * src = (float*)self->data;
			float * dst = (float*)newObject->data;
			dst[i] = src[i];
		}
		break;
	case 'D':
		newObject->data = calloc(count, sizeof(double));
		for (int32_t i = 0; i < count; i++)
		{
			double * src = (double*)self->data;
			double * dst = (double*)newObject->data;
			dst[i] = src[i];
		}
		break;
	case 'R':
		newObject->data = calloc(count, sizeof(Slot));
		for (int32_t i = 0; i < count; i++)
		{
			Slot * src = (Slot*)self->data;
			Slot * dst = (Slot*)newObject->data;
			dst[i].num = src[i].num;
			dst[i].ref = src[i].ref;
		}
		break;
	default:
		newObject->data = calloc(count, sizeof(Object*));
		for (int32_t i = 0; i < count; i++)
		{
			Object* * src = (Object**)self->data;
			Object* * dst = (Object**)newObject->data;
			dst[i] = src[i];
		}
		break;
	}
	return newObject;
}