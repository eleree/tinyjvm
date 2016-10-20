#ifndef __TINY_JVM_CLASSPATH_H__
#define __TINY_JVM_CLASSPATH_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int32_t parseClasspath(const char * jrepath, const char * classpath);
int32_t readClass(const char * className, char ** classContent);

#endif