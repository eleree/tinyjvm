#include "../../registry.h"

// public native long allocateMemory(long bytes);
// (J)J
void allocateMemory(Frame * frame)
{
	LocalVars * vars = frame->localVars;
	int64_t bytes = getLocalVarsLong(vars, 1);

	int64_t address = allocateNativeMemory(bytes);
	pushOperandLong(frame->operandStack, address);
}

// public native long reallocateMemory(long address, long bytes);
// (JJ)J
void reallocateMemory(Frame * frame)
{
	printf("Invoke Native Method %s\n", __FUNCTION__);
	exit(1);
}

// public native void freeMemory(long address);
// (J)V
void freeMemory(Frame * frame)
{
	//printf("Invoke Native Method %s\n", __FUNCTION__);
	//exit(1);
	LocalVars * vars = frame->localVars;
	int64_t address = getLocalVarsLong(vars, 1);
	freeNativeMemory(address);
}

//// public native void putAddress(long address, long x);
//// (JJ)V
//func putAddress(frame *rtda.Frame) {
//	mem_putLong(frame)
//}
//
//// public native long getAddress(long address);
//// (J)J
//func getAddress(frame *rtda.Frame) {
//	mem_getLong(frame)
//}
//
//// public native void putByte(long address, byte x);
//// (JB)V
//func mem_putByte(frame *rtda.Frame) {
//	mem, value := _put(frame)
//	PutInt8(mem, int8(value.(int32)))
//}
//
// public native byte getByte(long address);
// (J)B
void mem_getByte(Frame * frame) 
{
	//printf("Invoke Native Method %s\n", __FUNCTION__);
	//exit(1);
	LocalVars * vars = frame->localVars;
	int64_t address = getLocalVarsLong(vars, 1);
	int64_t memLen = 0;
	uint8_t * mem = memoryAt(address, &memLen);
	uint8_t value = *mem;
	pushOperandInt(frame->operandStack, (int32_t)value);
}


//
//// public native void putShort(long address, short x);
//// (JS)V
//func mem_putShort(frame *rtda.Frame) {
//	mem, value := _put(frame)
//	PutInt16(mem, int16(value.(int32)))
//}
//
//// public native short getShort(long address);
//// (J)S
//func mem_getShort(frame *rtda.Frame) {
//	stack, mem := _get(frame)
//	stack.PushInt(int32(Int16(mem)))
//}
//
//// public native void putChar(long address, char x);
//// (JC)V
//func mem_putChar(frame *rtda.Frame) {
//	mem, value := _put(frame)
//	PutUint16(mem, uint16(value.(int32)))
//}
//
//// public native char getChar(long address);
//// (J)C
//func mem_getChar(frame *rtda.Frame) {
//	stack, mem := _get(frame)
//	stack.PushInt(int32(Uint16(mem)))
//}
//
//// public native void putInt(long address, int x);
//// (JI)V
//func mem_putInt(frame *rtda.Frame) {
//	mem, value := _put(frame)
//	PutInt32(mem, value.(int32))
//}
//
//// public native int getInt(long address);
//// (J)I
//func mem_getInt(frame *rtda.Frame) {
//	stack, mem := _get(frame)
//	stack.PushInt(Int32(mem))
//}
//
// public native void putLong(long address, long x);
// (JJ)V
void mem_putLong(Frame * frame) 
{
	//printf("Invoke Native Method %s\n", __FUNCTION__);
	//exit(1);
	LocalVars * vars = frame->localVars;

	int64_t address = getLocalVarsLong(vars, 1);
	int64_t value = getLocalVarsLong(vars, 3);

	int64_t memLen = 0;
	uint8_t * mem = memoryAt(address, &memLen);

	uint64_t uValue = (uint64_t)value;
	mem[0] = (uValue >> 56) & 0xFF;
	mem[1] = (uValue >> 48) & 0xFF;
	mem[2] = (uValue >> 40) & 0xFF;
	mem[3] = (uValue >> 32) & 0xFF;
	mem[4] = (uValue >> 24) & 0xFF;
	mem[5] = (uValue >> 16) & 0xFF;
	mem[6] = (uValue >> 8) & 0xFF;
	mem[7] = (uValue) & 0xFF;
}


//
//// public native long getLong(long address);
//// (J)J
//func mem_getLong(frame *rtda.Frame) {
//	stack, mem := _get(frame)
//	stack.PushLong(Int64(mem))
//}
//
//// public native void putFloat(long address, float x);
//// (JJ)V
//func mem_putFloat(frame *rtda.Frame) {
//	mem, value := _put(frame)
//	PutFloat32(mem, value.(float32))
//}
//
//// public native float getFloat(long address);
//// (J)J
//func mem_getFloat(frame *rtda.Frame) {
//	stack, mem := _get(frame)
//	stack.PushFloat(Float32(mem))
//}
//
//// public native void putDouble(long address, double x);
//// (JJ)V
//func mem_putDouble(frame *rtda.Frame) {
//	mem, value := _put(frame)
//	PutFloat64(mem, value.(float64))
//}
//
//// public native double getDouble(long address);
//// (J)J
//func mem_getDouble(frame *rtda.Frame) {
//	stack, mem := _get(frame)
//	stack.PushDouble(Float64(mem))
//}
//
//func _put(frame *rtda.Frame) ([]byte, interface{}) {
//	vars := frame.LocalVars()
//	// vars.GetRef(0) // this
//	address := vars.GetLong(1)
//	value := vars.Get(3)
//
//	mem := memoryAt(address)
//	return mem, value
//}
//


//printf("Invoke Native Method %s\n", __FUNCTION__);
//exit(1);
extern void addressSize(Frame * frame);

void initUnsafeMem(void)
{
	registerNativeMethod("sun/misc/Unsafe", "allocateMemory", "(J)J", allocateMemory);
	registerNativeMethod("sun/misc/Unsafe", "reallocateMemory", "(JJ)J", reallocateMemory);
	registerNativeMethod("sun/misc/Unsafe", "freeMemory", "(J)V", freeMemory);
	registerNativeMethod("sun/misc/Unsafe", "addressSize", "()I", addressSize);
		//	_unsafe(putAddress, "putAddress", "(JJ)V")
		//	_unsafe(getAddress, "getAddress", "(J)J")
		//	_unsafe(mem_putByte, "putByte", "(JB)V")
	registerNativeMethod("sun/misc/Unsafe", "getByte", "(J)B", mem_getByte);
		//	_unsafe(mem_putShort, "putShort", "(JS)V")
		//	_unsafe(mem_getShort, "getShort", "(J)S")
		//	_unsafe(mem_putChar, "putChar", "(JC)V")
		//	_unsafe(mem_getChar, "getChar", "(J)C")
		//	_unsafe(mem_putInt, "putInt", "(JI)V")
		//	_unsafe(mem_getInt, "getInt", "(J)I")
	registerNativeMethod("sun/misc/Unsafe", "putLong", "(JJ)V", mem_putLong);
		//	_unsafe(mem_getLong, "getLong", "(J)J")
		//	_unsafe(mem_putFloat, "putFloat", "(JF)V")
		//	_unsafe(mem_getFloat, "getFloat", "(J)F")
		//	_unsafe(mem_putDouble, "putDouble", "(JD)V")
		//	_unsafe(mem_getDouble, "getDouble", "(J)D")
}