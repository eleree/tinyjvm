#include "object.h"
#include "class.h"
#include "slot.h"

Object * newObject(struct Class * c)
{
	Object * o =(Object *) calloc(1, sizeof(Object));
	o->class = c;
	//o->slotCount = c->instanceSlotCount;
	//o->fields =(Slot *) calloc(o->slotCount, sizeof(Slot));
	o->dataType = 'R';
	o->data = (Slot *)calloc(c->instanceSlotCount, sizeof(Slot));
	o->dataCount = c->instanceSlotCount;
	return o;
}

bool isObjectInstanceOf(Object * obj, Class * c){
	return isClassAssignableFrom(obj->class, c);
}

Object * getObjectRefVar(Object * self, const char * name, const char * descriptor)
{
	Field * field = getClassField(self->class, name, descriptor, false);
	Slot * slots = getObjectSlots(self);
	return getSlotRef(slots, field->slotId);
}

void setObjectRefVar(Object * self, const char * name, const char *descriptor, Object * ref)
{
	Field * field = getClassField(self->class, name, descriptor, false);
	Slot * slots = getObjectSlots(self);
	setSlotRef(slots, field->slotId, ref);
}


int32_t getObjectIntVar(Object * self, const char * name, const char * descriptor)
{
	Field * field = getClassField(self->class, name, descriptor, false);
	Slot * slots = getObjectSlots(self);
	return getSlotInt(slots, field->slotId);
}

void setObjectIntVar(Object * self, const char * name, const char *descriptor, int32_t val)
{
	Field * field = getClassField(self->class, name, descriptor, false);
	Slot * slots = getObjectSlots(self);
	setSlotInt(slots, field->slotId, val);
}

