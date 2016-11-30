#include "../../registry.h"

const char * fd = "java/io/FileDescriptor";


// private static native long set(int d);
// (I)J
void set(Frame * frame) {
	// todo
	pushOperandLong(frame->operandStack, 0);
}

void initNativeFileDescriptor(void)
{
	registerNativeMethod(fd, "set", "(I)J", set);
}
