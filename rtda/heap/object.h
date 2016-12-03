#ifndef __TINY_JVM_HEAP_OBJECT_H__
#define __TINY_JVM_HEAP_OBJECT_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Object {
	struct Class* class;
	//uint16_t slotCount;
	//struct Slot * fields;
	int32_t  dataCount;
	uint16_t dataType;
	void * data;

	int32_t extraCount;
	uint16_t extraType;
	void * extra;
}Object;

Object * newObject(struct Class * c);
bool isObjectInstanceOf(Object * obj, struct Class * class);

struct Slot * getObjectSlots(Object * self);

void setSlotRef(struct Slot * slot, uint16_t index, Object * ref);
Object * getSlotRef(struct Slot * slot, uint16_t index);

Object * getObjectRefVar(Object * self, const char * name, const char * descriptor);
void setObjectRefVar(Object * self, const char * name, const char *descriptor, Object * ref);
int32_t getObjectIntVar(Object * self, const char * name, const char * descriptor);
void setObjectIntVar(Object * self, const char * name, const char *descriptor, int32_t val);

Object * cloneObject(Object * self);

#define panic(message,code) do{\
	printf("%s,code:%d", message, code); \
	exit(code); \
}while(0);

#endif