#ifndef __TINY_JVM_INTERPRETER_H__
#define __TINY_JVM_INTERPRETER_H__

#include "classfile\classfile.h"
#include "rtda\heap\class.h"
#include "rtda\heap\method.h"

void interpretThread(Thread * thread);
void interpret(Class * c, Method * method, Thread * thread, int argc, char ** argv);

#endif