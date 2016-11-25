#ifndef __TINY_JVM_INTERPRETER_H__
#define __TINY_JVM_INTERPRETER_H__

#include "classfile\classfile.h"
#include "rtda\heap\class.h"
#include "rtda\heap\method.h"

void interpret(Class * classFile, Method * method, int argc, char ** argv);

#endif