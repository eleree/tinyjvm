#include "object.h"
#include "class.h"

Object * newObject(struct Class * c)
{
	Object * o =(Object *) calloc(1, sizeof(Object));
	o->class = c;
	o->slotCount = c->instanceSlotCount;
	o->fields =(Slot *) calloc(o->slotCount, sizeof(Slot));
	return o;
}

bool isObjectInstanceOf(Object * obj, Class * class){
	return isClassAssignableFrom(obj->class, class);
}
