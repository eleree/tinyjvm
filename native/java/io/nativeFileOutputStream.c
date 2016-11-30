#include "../../registry.h"

const char * fos = "java/io/FileOutputStream";

// private native void writeBytes(byte b[], int off, int len, boolean append) throws IOException;
// ([BIIZ)V
void writeBytes(Frame * frame)
{
	LocalVars * vars = frame->localVars;
	Object * b = getLocalVarsRef(vars, 1);
	int32_t off = getLocalVarsInt(vars, 2);
	int32_t len = getLocalVarsInt(vars, 3);

	int8_t * jBytes = (int8_t*)b->data;
	for (int32_t i = off; i < off + len; i++)
		printf("%c", jBytes[i]);

}

void initNativeFileOutputStream(void)
{
	registerNativeMethod(fos, "writeBytes", "([BIIZ)V", writeBytes);
}