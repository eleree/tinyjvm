#ifndef __TINY_JVM_ENTRY_H__
#define __TINY_JVM_ENTRY_H__

#include <stdint.h>

int32_t readZipEntryClass(const char * zippath, const char * className, char ** classContent);
int32_t readDirEntryClass(const char * path, const char * className, char ** classContent);

#endif