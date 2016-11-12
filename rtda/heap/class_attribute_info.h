#ifndef __TINY_JVM_ATTRIBUTE_INFO_H__
#define __TINY_JVM_ATTRIBUTE_INFO_H__

#include <string.h>
#include "../../classfile/classfile.h"

void * newCopyAttributeInfo(const char * attrName, void * sourceAttr, ClassFile *classFile);
void copyAttributeInfo(ClassFile * classFile, AttributeInfo * destAttr, AttributeInfo * sourceAttr, uint16_t count);


#endif
