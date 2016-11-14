#include "slot.h"

void setSlotInt(Slot * slot, uint16_t index, int32_t val)
{
	slot[index].num = val;
}

int32_t getSlotInt(Slot * slot, uint16_t index)
{
	return slot[index].num;
}

void setSlotFloat(Slot * slot, uint16_t index, float val)
{
	FloatInt transData;
	transData.floatData = val;
	slot[index].num = transData.bitsData;
}

float getSlotFloat(Slot * slot, uint16_t index)
{
	FloatInt transData;
	transData.bitsData = getSlotInt(slot, index);
	return transData.floatData;
}

void setSlotLong(Slot * slot, uint16_t index, int64_t val)
{
	LongInt transData;
	transData.longData = val;
	slot[index].num = transData.low;
	slot[index + 1].num = transData.high;
}

int64_t getSlotLong(Slot * slot, uint16_t index)
{
	LongInt transData;
	transData.low = getSlotInt(slot, index);
	transData.high = getSlotInt(slot, index + 1);
	return transData.longData;
}

void setSlotDouble(Slot * slot, uint16_t index, double val)
{
	DoubleLong transData;
	transData.doubleData = val;
	setSlotLong(slot, index, transData.bitsData);
}

double getSlotDouble(Slot * slot, uint16_t index)
{
	DoubleLong transData;
	transData.bitsData = getSlotLong(slot, index);
	return transData.doubleData;
}


void setSlotRef(Slot * slot, uint16_t index, Object * ref)
{
	slot[index].ref = ref;
}

Object * getSlotRef(Slot * slot, uint16_t index)
{
	return slot[index].ref;
}