#ifndef __TINY_JVM_LOCAL_VARS_H__
#define __TINY_JVM_LOCAL_VARS_H__

#include "rtda.h"

LocalVars * newLocalVars(uint32_t maxLocals);
void freeLocalVars(LocalVars * localVars);

void setLocalVarsInt(LocalVars * localVars, int32_t index, int32_t val);
int32_t getLocalVarsInt(LocalVars * localVars, int32_t index);

void setLocalVarsFloat(LocalVars * localVars, int32_t index, float val);
float getLocalVarsFloat(LocalVars * localVars, int32_t index);

void setLocalVarsLong(LocalVars * localVars, int32_t index, int64_t val);
int64_t getLocalVarsLong(LocalVars * localVars, int64_t index);

void setLocalVarsDouble(LocalVars * localVars, int32_t index, double val);
double getLocalVarsDouble(LocalVars * localVars, int32_t index);

void setLocalVarsRef(LocalVars * localVars, int32_t index, Object * ref);
Object * getLocalVarsRef(LocalVars * localVars, int32_t index);

#endif