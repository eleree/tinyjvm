#include "rtda.h"
#include "heap\class.h"
LocalVars * newLocalVars(uint32_t maxLocals)
{
	LocalVars * localVars = NULL;
	if (maxLocals == 0)
		return NULL;
	localVars = calloc(1, sizeof(LocalVars));
	localVars->size = maxLocals;
	localVars->slots = calloc(maxLocals, sizeof(Slot));
	return localVars;
}

void freeLocalVars(LocalVars * localVars)
{
	if (localVars != NULL)
	{
		if (localVars->size > 0)
			free(localVars->slots);
		free(localVars);
	}
}

void setLocalVarsInt(LocalVars * localVars, int32_t index, int32_t val)
{
	localVars->slots[index].num = val;
}

int32_t getLocalVarsInt(LocalVars * localVars, int32_t index)
{
	return localVars->slots[index].num;
}

void setLocalVarsFloat(LocalVars * localVars, int32_t index, float val)
{
	FloatInt transData;
	transData.floatData = val;
	localVars->slots[index].num = transData.bitsData;
}

float getLocalVarsFloat(LocalVars * localVars, int32_t index)
{
	FloatInt transData;
	transData.bitsData = localVars->slots[index].num;
	return transData.floatData;
}

void setLocalVarsLong(LocalVars * localVars, int32_t index, int64_t val)
{
	localVars->slots[index].num =  val & 0xFFFFFFFF;
	localVars->slots[index+1].num = (uint32_t)(val>>32);
}

int64_t getLocalVarsLong(LocalVars * localVars, int64_t index)
{
	LongInt transData;

	transData.high = localVars->slots[index + 1].num;	
	transData.low = localVars->slots[index].num;
	return transData.longData;
}

void setLocalVarsDouble(LocalVars * localVars, int32_t index, double val)
{
	DoubleLong transData;
	transData.doubleData = val;
	setLocalVarsLong(localVars, index, transData.bitsData);	
}

double getLocalVarsDouble(LocalVars * localVars, int32_t index)
{
	DoubleLong transData;

	transData.bitsData = getLocalVarsLong(localVars, index);

	return transData.doubleData;
}

void setLocalVarsRef(LocalVars * localVars, int32_t index, Object * ref)
{
	//if (ref != NULL)
	//	printf("---Vars Size:%d,Push Ref %s\n", localVars->size, ref->class->name);
	localVars->slots[index].ref = ref;
}

Object * getLocalVarsRef(LocalVars * localVars, int32_t index)
{
	return localVars->slots[index].ref;
}

void setLocalVarsSlot(LocalVars * localVars, int32_t index, Slot * slot)
{
	localVars->slots[index].num = slot->num;
	localVars->slots[index].ref = slot->ref;
	//if (slot->ref != NULL)
	//{
	//	printf("---Slot Vars Size:%d,Push Ref %s\n", localVars->size, slot->ref->class->name);
	//}
	
}

Object * getLocalVarsThis(LocalVars * self) 
{
	return getLocalVarsRef(self, 0);
}

bool getLocalVarsBoolean(LocalVars * self, int32_t index)
{
	return getLocalVarsInt(self, index) == 1;
}
