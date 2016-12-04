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
	//printf("Invoke Native Method %s\n", __FUNCTION__);
	//exit(1);
	LocalVars * vars = frame->localVars;
	Object * jField = getLocalVarsRef(vars, 1);
	int64_t offset = getObjectIntVar(jField, "slot", "I");
	pushOperandLong(frame->operandStack, offset);
}

bool _casObj(Object * obj, Slot * fields, int64_t offset, Object * expected, Object * newVal)
{
	Object * current = getSlotRef(fields, (uint16_t)offset);
	if (current == expected)
	{
		setSlotRef(fields, (uint16_t)offset, newVal);
		return true;
	}else
		return false;
}

bool _casArr(Object* *objs, int64_t offset, Object * expected, Object * newVal)
{
	Object * current = objs[offset];
	if (current == expected)
	{
		objs[offset] = newVal;
		return true;
	}	
	else
		return false;
}

// public final native boolean compareAndSwapObject(Object o, long offset, Object expected, Object x)
// (Ljava/lang/Object;JLjava/lang/Object;Ljava/lang/Object;)Z
void compareAndSwapObject(Frame * frame)
{
	//printf("Invoke Native Method %s\n", __FUNCTION__);
	//exit(1);
	LocalVars * vars = frame->localVars;
	Object * obj = getLocalVarsRef(vars, 1);
	Object * fields = obj->data;
	int64_t offset = getLocalVarsLong(vars, 2);
	Object * expected = getLocalVarsRef(vars, 4);
	Object * newVal = getLocalVarsRef(vars, 5);

	if (obj->dataType == 'R')
	{
		Slot * anys = obj->data;
		bool swapped = _casObj(obj, anys, offset, expected, newVal);
		pushOperandBoolean(frame->operandStack, swapped);
	}else if (obj->dataType == 'O')
	{
		Object* *objs = obj->data;
		bool swapped = _casArr(objs, offset, expected, newVal);
		pushOperandBoolean(frame->operandStack, swapped);
	}else
		panic("Native Unsafe getObject", -1);

}

// public native boolean getInt(Object o, long offset);
// (Ljava/lang/Object;J)I
void  getInt(Frame * frame)
{
	//printf("Invoke Native Method %s\n", __FUNCTION__);
	//exit(1);

	LocalVars * vars = frame->localVars;
	Object * obj = getLocalVarsRef(vars, 1);
	Object * fields = obj->data;
	int64_t offset = getLocalVarsLong(vars, 2);
	if (obj->dataType == 'R')
	{
		int32_t  val = getSlotInt(obj->data, (uint16_t)offset);
		pushOperandInt(frame->operandStack, val);
	}else if (obj->dataType == 'I')
	{
		int32_t * shorts = obj->data;
		pushOperandInt(frame->operandStack, (int32_t)shorts[offset]);
	}else
	{
		panic("Native Unsafe getInt", -1);
	}
}

// public final native boolean compareAndSwapInt(Object o, long offset, int expected, int x);
// (Ljava/lang/Object;JII)Z
void compareAndSwapInt(Frame * frame)
{
	//printf("Invoke Native Method %s\n", __FUNCTION__);
	//exit(1);
	LocalVars * vars = frame->localVars;
	Object * obj = getLocalVarsRef(vars, 1);
	int64_t offset = getLocalVarsLong(vars, 2);
	int32_t expected = getLocalVarsInt(vars, 4);
	int32_t newVal = getLocalVarsInt(vars, 5);
	if (obj->dataType == 'R'){
		int32_t oldVal = getSlotInt(obj->data, (uint16_t)offset);
		if (oldVal == expected)
		{
			setSlotInt(obj->data, (uint16_t)offset, newVal);
			pushOperandBoolean(frame->operandStack, true);
		}else
			pushOperandBoolean(frame->operandStack, false);
	}
	else if (obj->dataType == 'I'){
		int32_t * ints = obj->data;
		int32_t oldVal = ints[offset];
		if (oldVal == expected)
		{
			ints[offset] = newVal;
			pushOperandBoolean(frame->operandStack, true);
		}else
			pushOperandBoolean(frame->operandStack, false);
	}else
		panic("todo: compareAndSwapInt\n", 123);
}

// public native Object getObject(Object o, long offset);
// (Ljava/lang/Object;J)Ljava/lang/Object;
void getObject(Frame * frame)
{
	//printf("Invoke Native Method %s\n", __FUNCTION__);
	//exit(1);
	LocalVars * vars = frame->localVars;
	Object * obj = getLocalVarsRef(vars, 1);
	int64_t offset = getLocalVarsLong(vars, 2);
	
	if (obj->dataType == 'R')
	{
		Slot * slots = obj->data;
		Object * x = getSlotRef(slots, (uint16_t)offset);
		pushOperandRef(frame->operandStack, x);
	}else if (obj->dataType == 'O'){
		Object* * objs = obj->data;
		Object * x = objs[offset];
		pushOperandRef(frame->operandStack, x);
	}else
		panic("getObject\n", 123);
}

// public final native boolean compareAndSwapLong(Object o, long offset, long expected, long x);
// (Ljava/lang/Object;JJJ)Z
void compareAndSwapLong(Frame * frame)
{
	//printf("Invoke Native Method %s\n", __FUNCTION__);
	//exit(1);

	LocalVars * vars = frame->localVars;
	Object * obj = getLocalVarsRef(vars, 1);
	int64_t offset = getLocalVarsLong(vars, 2);
	int64_t expected = getLocalVarsLong(vars, 4);
	int64_t newVal = getLocalVarsLong(vars, 6);

	if (obj->dataType == 'R'){
		int64_t oldVal = getSlotLong(obj->data, (uint16_t)offset);
		if (oldVal == expected)
		{
			setSlotLong(obj->data, (uint16_t)offset, newVal);
			pushOperandBoolean(frame->operandStack, true);
		}
		else
			pushOperandBoolean(frame->operandStack, false);
	}
	else if (obj->dataType == 'I'){
		int64_t * longs = obj->data;
		int64_t oldVal = longs[offset];
		if (oldVal == expected)
		{
			longs[offset] = newVal;
			pushOperandBoolean(frame->operandStack, true);
		}
		else
			pushOperandBoolean(frame->operandStack, false);
	}
	else
		panic("todo: compareAndSwapLong\n", 123);
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