#ifndef __TINY_JVM_THREAD_H__
#define __TINY_JVM_THREAD_H__

#include "rtda.h"

Thread * newThread(void);

int32_t getThreadPC(Thread * thread);
void setThreadPC(Thread * thread, int32_t pc);
void pushThreadFrame(Thread * thread, Frame * frame);
Frame * popThreadFrame(Thread * thread);
Frame * getCurrentFrame(Thread * thread);

bool isThreadStackEmpty(Thread * thread);
Frame* * getThreadFrames(Thread * threak, int32_t skip, int32_t * remain);
void clearThreadStack(Thread *thread);

#endif