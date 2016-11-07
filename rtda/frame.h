#ifndef __TINY_JVM_FRAME_H__
#define __TINY_JVM_FRMAE_H__

#include <stdint.h>
#include "rtda.h"

Frame * newFrame(uint32_t maxLocals, uint32_t maxStack);
void freeFrame(Frame * frame);

#endif