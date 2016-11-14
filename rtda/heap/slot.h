#ifndef __TINY_JVM_HEAP_SLOT_H__
#define __TINY_JVM_HEAP_SLOT_H__

#include <stdint.h>
#include <string.h>
#include "../../rtda/rtda.h"

void setSlotInt(Slot * slot, uint16_t index, int32_t val);
int32_t getSlotInt(Slot * slot, uint16_t index);

void setSlotFloat(Slot * slot, uint16_t index, float val);
float getSlotFloat(Slot * slot, uint16_t index);

void setSlotLong(Slot * slot, uint16_t index, int64_t val);
int64_t getSlotLong(Slot * slot, uint16_t index);

void setSlotDouble(Slot * slot, uint16_t index, double val);
double getSlotDouble(Slot * slot, uint16_t index);

void setSlotRef(Slot * slot, uint16_t index, Object * ref);
Object * getSlotRef(Slot * slot, uint16_t index);

#endif