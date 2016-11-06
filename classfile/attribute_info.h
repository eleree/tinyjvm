#ifndef __TINY_JVM_ATTRIBUTE_INFO_H__
#define __TINY_JVM_ATTRIBUTE_INFO_H__

#include <string.h>
#include "classfile.h"

void readAttributeInfo(ClassFile * classFile, AttributeInfo * attribute, uint16_t count);
void readClassFields(ClassFile * classFile);
void readClassMethods(ClassFile * classFile);
void readClassAttributes(ClassFile * classFile);

#endif
