#ifndef __TINY_JVM_HEAP_OBJECT_H__
#define __TINY_JVM_HEAP_OBJECT_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Object {
	struct Class* class;
	uint16_t slotCount;
	struct Slot * fields;
}Object;

Object * newObject(struct Class * c);

#endif