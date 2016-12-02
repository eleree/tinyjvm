#include "../../registry.h"

const char * miscUnsafe = "sun/misc/Unsafe";

// public native int arrayBaseOffset(Class<?> type);
// (Ljava/lang/Class;)I
void arrayBaseOffset(Frame * frame)
{
	pushOperandInt(frame->operandStack, 0);	
}

// public native int arrayIndexScale(Class<?> type);
// (Ljava/lang/Class;)I
void arrayIndexScale(Frame * frame)
{
	pushOperandInt(frame->operandStack, 1);
}

// public native int addressSize();
// ()I
void addressSize(Frame * frame)
{
	pushOperandInt(frame->operandStack, 8);// todo unsafe.Sizeof(int)
}

// public native long objectFieldOffset(Field field);
// (Ljava/lang/reflect/Field;)J
void objectFieldOffset(Frame * frame)
{
	printf("Invoke Native Method %s\n", __FUNCTION__);
	exit(1);
}

// public final native boolean compareAndSwapObject(Object o, long offset, Object expected, Object x)
// (Ljava/lang/Object;JLjava/lang/Object;Ljava/lang/Object;)Z
void compareAndSwapObject(Frame * frame)
{
	printf("Invoke Native Method %s\n", __FUNCTION__);
	exit(1);
}

// public native boolean getInt(Object o, long offset);
// (Ljava/lang/Object;J)I
void  getInt(Frame * frame)
{
	printf("Invoke Native Method %s\n", __FUNCTION__);
	exit(1);
}

// public final native boolean compareAndSwapInt(Object o, long offset, int expected, int x);
// (Ljava/lang/Object;JII)Z
void compareAndSwapInt(Frame * frame)
{
	printf("Invoke Native Method %s\n", __FUNCTION__);
	exit(1);
}

// public native Object getObject(Object o, long offset);
// (Ljava/lang/Object;J)Ljava/lang/Object;
void getObject(Frame * frame)
{
	printf("Invoke Native Method %s\n", __FUNCTION__);
	exit(1);
}

// public final native boolean compareAndSwapLong(Object o, long offset, long expected, long x);
// (Ljava/lang/Object;JJJ)Z
void compareAndSwapLong(Frame * frame)
{
	printf("Invoke Native Method %s\n", __FUNCTION__);
	exit(1);
}

void initUnsafe(void)
{
	
	registerNativeMethod(miscUnsafe, "arrayBaseOffset", "(Ljava/lang/Class;)I", arrayBaseOffset);
	registerNativeMethod(miscUnsafe, "arrayIndexScale", "(Ljava/lang/Class;)I", arrayIndexScale);
	registerNativeMethod(miscUnsafe, "addressSize", "()I", addressSize);
	registerNativeMethod(miscUnsafe, "objectFieldOffset", "(Ljava/lang/reflect/Field;)J", objectFieldOffset);
	registerNativeMethod(miscUnsafe, "compareAndSwapObject", "(Ljava/lang/Object;JLjava/lang/Object;Ljava/lang/Object;)Z", compareAndSwapObject);
	registerNativeMethod(miscUnsafe, "getIntVolatile", "(Ljava/lang/Object;J)I", getInt);
	registerNativeMethod(miscUnsafe, "compareAndSwapInt", "(Ljava/lang/Object;JII)Z", compareAndSwapInt);
	registerNativeMethod(miscUnsafe, "getObjectVolatile", "(Ljava/lang/Object;J)Ljava/lang/Object;", getObject);
	registerNativeMethod(miscUnsafe, "compareAndSwapLong", "(Ljava/lang/Object;JJJ)Z", compareAndSwapLong);

}