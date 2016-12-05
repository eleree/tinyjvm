#include "../../registry.h"


Method * _getGoMethod(Object * methodObj, bool isConstructor)
{
	if (methodObj->extra != NULL)
		return methodObj->extra;
	if (isConstructor)
	{
		Object * root = getObjectRefVar(methodObj, "root", "Ljava/lang/reflect/Constructor;");
		return root->extra;
	}else{
		Object * root = getObjectRefVar(methodObj, "root", "Ljava/lang/reflect/Method;");
		return root->extra;
	}
}

Method * getGoMethod(Object * methodObj) 
{
	return _getGoMethod(methodObj, false);
}

Method * getGoConstructor(Object * constructorObj)
{
	return _getGoMethod(constructorObj, true);
}

OperandStack* convertArgs(Object * this, Object* argArr, Method * method)
{
	OperandStack * ops = NULL;

	if (method->argSlotCount == 0)
		return NULL;

	ops = newOperandStack(method->argSlotCount);

	if (!isMethodStatic(method))
	{
		pushOperandRef(ops, this);
	}

	if (method->argSlotCount == 1 && !isMethodStatic(method))
		return ops;

	return ops;
}

// private static native Object newInstance0(Constructor<?> c, Object[] os)
// throws InstantiationException, IllegalArgumentException, InvocationTargetException;
// (Ljava/lang/reflect/Constructor;[Ljava/lang/Object;)Ljava/lang/Object;
static void  newInstance0(Frame * frame)
{
	//printf("Invoke Native Method %s\n", __FUNCTION__);
	//exit(1);
	LocalVars * vars = frame->localVars;
	Object * constructorObj = getLocalVarsRef(vars, 0);
	Object * argArrObj = getLocalVarsRef(vars, 1);

	Method * goConstructor = getGoConstructor(constructorObj);

	Class * goClass = goConstructor->classMember.attachClass;
	if (!goClass->initStarted)
	{
		revertFrameNextPC(frame);
		InitClass(frame->thread, goClass);
		return;
	}

	Object * obj = newObject(goClass);
	pushOperandRef(frame->operandStack, obj);

	// call <init>
	OperandStack * ops = convertArgs(obj, argArrObj, goConstructor);

	Frame * shimFrame = newShimFrame(frame->thread, ops);
	pushThreadFrame(frame->thread, shimFrame);

	InvokeMethod(shimFrame, goConstructor);	
}

void initConstructorAccessorImpl(void)
{
	registerNativeMethod("sun/reflect/NativeConstructorAccessorImpl", "newInstance0", "(Ljava/lang/reflect/Constructor;[Ljava/lang/Object;)Ljava/lang/Object;", newInstance0);
}