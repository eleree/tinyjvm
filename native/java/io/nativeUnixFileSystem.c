#include "../../registry.h"

const char * unixfs = "java/io/UnixFileSystem";

// private native String canonicalize0(String path) throws IOException;
// (Ljava/lang/String;)Ljava/lang/String;
void canonicalize0(Frame * frame)
{
	printf("Invoke Native Method %s\n", __FUNCTION__);
	exit(0);
}

// public native int getBooleanAttributes0(File f);
// (Ljava/io/File;)I
void getBooleanAttributes0(Frame * frame) 
{
	printf("Invoke Native Method %s\n", __FUNCTION__);
	exit(0);
}

void initNativeUnixFileSystem(void)
{
	registerNativeMethod(unixfs, "canonicalize0", "(Ljava/lang/String;)Ljava/lang/String;", canonicalize0);
	registerNativeMethod(unixfs, "getBooleanAttributes0", "(Ljava/io/File;)I", getBooleanAttributes0);	
}
