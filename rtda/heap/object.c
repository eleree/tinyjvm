#include "object.h"
#include "class.h"

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

bool isObjectInstanceOf(Object * obj, Class * class){
	return isClassAssignableFrom(obj->class, class);
}

Object * getObjectRefVar(Object * self, const char * name, const char * descriptor)
{
	Field * field = getClassField(self->class, name, descriptor, false);
	Slot * slots = getObjectSlots(self);
	return getSlotRef(slots, field->slotId);
}

void setObectRefVar(Object * self, const char * name, const char *descriptor, Object * ref)
{
	Field * field = getClassField(self->class, name, descriptor, false);
	Slot * slots = getObjectSlots(self);
	setSlotRef(slots, field->slotId, ref);
}