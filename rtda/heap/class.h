#ifndef __TINY_JVM_CLASS_H__
#define __TINY_JVM_CLASS_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../rtda.h"
#include "../../classfile/classfile.h"
#include "field.h"
#include "method.h"

struct Method;
struct Field;
struct Class;
struct ClassLoader;

typedef struct ConstantPool
{
	struct Class * class;
	uint16_t constantPoolCount;
	ConstantPoolItem *constantPoolItem; //constantPool array
};

typedef struct Class
{
	uint16_t accessFlags;
	char * name;
	char * packageName;
	char * superClassName;
	uint16_t interfaceNamesCount;
	char * *interfaceNames; // interfaceName  array
	struct ConstantPool constantPool;
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
	struct ClassLoader * classLoader;
}Class;

enum {
	ACC_PUBLIC = 0x0001, // class field method
	ACC_PRIVATE = 0x0002, //       field method
	ACC_PROTECTED = 0x0004, //       field method
	ACC_STATIC = 0x0008, //       field method
	ACC_FINAL = 0x0010, // class field method
	ACC_SUPER = 0x0020, // class
	ACC_SYNCHRONIZED = 0x0020, //             method
	ACC_VOLATILE = 0x0040, //       field
	ACC_BRIDGE = 0x0040, //             method
	ACC_TRANSIENT = 0x0080, //       field
	ACC_VARARGS = 0x0080, //             method
	ACC_NATIVE = 0x0100, //             method
	ACC_INTERFACE = 0x0200, // class
	ACC_ABSTRACT = 0x0400, // class       method
	ACC_STRICT = 0x0800, //             method
	ACC_SYNTHETIC = 0x1000, // class field method
	ACC_ANNOTATION = 0x2000, // class
	ACC_ENUM = 0x4000 // class field
};

Class * newClass(ClassFile * classFile);
struct Method * getClassMainMethod(Class * c);
bool isClassInterface(Class * c);
bool isClassAbstract(Class * c);


bool isSubClassOf(Class * thisClass, Class * otherClass);

#endif