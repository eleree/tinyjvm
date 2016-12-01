#ifndef __TINY_JVM_FRAME_H__
#define __TINY_JVM_FRMAE_H__

#include <stdint.h>
#include "rtda.h"

Frame * newFrame(Thread * thread, struct Method * method, uint32_t maxLocals, uint32_t maxStack);

LocalVars * getFrameLocalVars(Frame * frame);

OperandStack * getFrameOperandStack(Frame * frame);

int32_t getFrameNextPC(Frame *frame);

void setFrameNextPC(Frame *frame, int32_t nextPC);

void revertFrameNextPC(Frame * frame);

void freeFrame(Frame * frame);

Frame * newShimFrame(Thread * thread, OperandStack * operandStack);

#endif