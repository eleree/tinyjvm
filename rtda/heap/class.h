#ifndef __TINY_JVM_CLASS_H__
#define __TINY_JVM_CLASS_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../rtda.h"
#include "../../classfile/classfile.h"
#include "field.h"
#include "method.h"

struct Method;
struct Field;

typedef struct Class
{
	uint16_t accessFlags;
	char * name;
	char * superClassName;
	uint16_t interfaceNamesCount;
	char * *interfaceNames; // interfaceName  array
	uint16_t constantPoolCount;
	ConstantPoolItem *constantPoolItem; //constantPool array
	uint16_t fieldsCount;
	struct Field *fields;
	uint16_t methodsCount;
	struct Method * methods;
	struct Class * superClass;
	uint16_t interfacesCount;
	struct Class * *interfaces;
	uint32_t instanceSlotCount;
	uint32_t staticSlotCount;
	uint32_t slotCount;
	Slot * staticVars;
}Class;

Class * newClass(ClassFile * classFile);

#endif