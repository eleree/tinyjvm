#ifndef __TINY_JVM_INTERPRETER_H__
#define __TINY_JVM_INTERPRETER_H__

#include "classfile\classfile.h"

void interpret(ClassFile * classFile, MethodInfo * methodInfo);

#endif