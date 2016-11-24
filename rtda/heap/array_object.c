#include "object.h"
#include "slot.h"

int8_t * getObjectBytes(Object * self)
{
	if (self->dataType != 'B')
		panic("Invaild Object Array", 150);
	return (int8_t*)self->data;
}

int16_t * getObjectShorts(Object * self)
{
	return (int16_t*)self->data;
}

int32_t * getObjectInts(Object * self)
{
	return (int32_t*)self->data;
}

int64_t * getObjectLongs(Object * self)
{
	return (int64_t*)self->data;
}

uint16_t * getObjectChars(Object * self)
{
	return (uint16_t*)self->data;
}

float * getObjectFloats(Object * self)
{
	return (float*)self->data;
}

double * getObjectDoubles(Object * self)
{
	return (double*)self->data;
}

Object* * getObjectRefs(Object * self)
{
	return (Object**)self->data;
}

Slot * getObjectSlots(Object * self)
{
	return (Slot*)self->data;
}

int32_t arrayLength(Object * self)
{
	return self->dataCount;
}