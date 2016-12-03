#include "../../registry.h"
#include "../../../strings/strings.h"
#include "../../../rtda/frame.h"

const char * jlClass = "java/lang/Class";


// static native Class<?> getPrimitiveClass(String name);
// (Ljava/lang/String;)Ljava/lang/Class;
void  getPrimitiveClass(Frame * frame)
{
	Object * nameObj = getLocalVarsRef(frame->localVars, 0);
	String * name = goString(nameObj);
	ClassLoader * classLoader = frame->method->classMember.attachClass->classLoader;
	Object * jlClass = loadClass(classLoader, name->data)->jClass;

	pushOperandRef(frame->operandStack, jlClass);
}

// private static native boolean desiredAssertionStatus0(Class<?> clazz);
// (Ljava/lang/Class;)Z
void  desiredAssertionStatus0(Frame * frame)
{
	pushOperandBoolean(frame->operandStack, false);
}

// private native String getName0();
// ()Ljava/lang/String;
void  getName0(Frame * frame)
{
	Object * thisObject = getLocalVarsThis(frame->localVars);
	Class * extraClass = (Class *) thisObject->extra;

	String nameStr = { 0 };
	nameStr.data = classJavaName(extraClass);
	nameStr.len = strlen(nameStr.data);
	nameStr.type = STRING_TYPE_UTF8;
	Object * nameObject = jString(extraClass->classLoader, &nameStr);

	pushOperandRef(frame->operandStack, nameObject);
}

// public native boolean isInterface();
// ()Z
void isInterface(Frame * frame) 
{
	LocalVars * vars = frame->localVars;
	Object * thisObject = getLocalVarsThis(vars);
	Class * c = (Class *)thisObject->extra;
	 
	pushOperandBoolean(frame->operandStack, isClassInterface(c));
}

// public native boolean isPrimitive();
// ()Z
void isPrimitive(Frame * frame)
{
	LocalVars * vars = frame->localVars;
	Object * thisObject = getLocalVarsThis(vars);
	Class * c = (Class *)thisObject->extra;

	pushOperandBoolean(frame->operandStack, isClassPrimitive(c));

}

// private static native Class<?> forName0(String name, boolean initialize,
//                                         ClassLoader loader,
//                                         Class<?> caller)
//     throws ClassNotFoundException;
// (Ljava/lang/String;ZLjava/lang/ClassLoader;Ljava/lang/Class;)Ljava/lang/Class;
void forName0(Frame * frame)
{
	LocalVars * vars = frame->localVars;
	Object * jName = getLocalVarsRef(vars, 0);
	bool initialize = getLocalVarsBoolean(vars, 1);

	String * goName = goString(jName);
	stringReplace(goName->data, goName->data, goName->len);
	Class * goClass = loadClass(frame->method->classMember.attachClass->classLoader, goName->data);

	Object * jClass = goClass->jClass;
	if (initialize && !goClass->initStarted)
	{
		Thread * thread = frame->thread;
		setFrameNextPC(frame, thread->pc);
		InitClass(thread, goClass);
	}else{
		pushOperandRef(frame->operandStack, jClass);
	}
}

// public native int getModifiers();
// ()I
void getModifiers(Frame * frame)
{
	LocalVars * vars = frame->localVars;
	Object * thisObject = getLocalVarsThis(vars);
	Class * c = (Class *)thisObject->extra;

	pushOperandInt(frame->operandStack, c->accessFlags);
}


// public native Class<? super T> getSuperclass();
// ()Ljava/lang/Class;
void getSuperclass(Frame * frame)
{
	LocalVars * vars = frame->localVars;
	Object * thisObject = getLocalVarsThis(vars);
	Class * c = (Class *)thisObject->extra;
	Class * superClass = c->superClass;

	if (superClass != NULL)
		pushOperandRef(frame->operandStack, superClass->jClass);
	else
		pushOperandRef(frame->operandStack, NULL);
}

// private native Class<?>[] getInterfaces0();
// ()[Ljava/lang/Class;
void getInterfaces0(Frame * frame)
{
	LocalVars * vars = frame->localVars;
	Object * thisObject = getLocalVarsThis(vars);
	Class * c = (Class *)thisObject->extra;
	Object * classArr = toClassArr(c->classLoader, c->interfaces, c->interfacesCount);

	pushOperandRef(frame->operandStack, classArr);
}


// public native boolean isArray();
// ()Z
void isArray(Frame * frame)
{
	LocalVars * vars = frame->localVars;
	Object * thisObject = getLocalVarsThis(vars);
	Class * c = (Class *)thisObject->extra;

	pushOperandBoolean(frame->operandStack, isClassArray(c));
}

// public native Class<?> getComponentType();
// ()Ljava/lang/Class;
void getComponentType(Frame * frame)
{
	LocalVars * vars = frame->localVars;
	Object * thisObject = getLocalVarsThis(vars);
	Class * c = (Class *)thisObject->extra;

	Class * component = componentClass(c);
	Object * componentClassObj = component->jClass;

	pushOperandRef(frame->operandStack, componentClassObj);
}


// public native boolean isAssignableFrom(Class<?> cls);
// (Ljava/lang/Class;)Z
void isAssignableFrom(Frame * frame)
{
	LocalVars * vars = frame->localVars;
	Object * thisObject = getLocalVarsThis(vars);
	Object * cls = getLocalVarsRef(vars, 1);

	Class * thisClass = thisObject->extra;
	Class * clsClass = cls->extra;

	bool ok = isClassAssignableFrom(clsClass, thisClass);

	pushOperandBoolean(frame->operandStack, ok);
}

void initNativeClass(void)
{	
	registerNativeMethod(jlClass, "getPrimitiveClass", "(Ljava/lang/String;)Ljava/lang/Class;", getPrimitiveClass);
	registerNativeMethod(jlClass, "getName0", "()Ljava/lang/String;", getName0);
	registerNativeMethod(jlClass, "desiredAssertionStatus0", "(Ljava/lang/Class;)Z", desiredAssertionStatus0);

	registerNativeMethod(jlClass, "isInterface", "()Z", isInterface);
	registerNativeMethod(jlClass, "isPrimitive", "()Z", isPrimitive);
	registerNativeMethod(jlClass, "getDeclaredFields0", "(Z)[Ljava/lang/reflect/Field;", getDeclaredFields0);
	registerNativeMethod(jlClass, "forName0", "(Ljava/lang/String;ZLjava/lang/ClassLoader;Ljava/lang/Class;)Ljava/lang/Class;", forName0);
	registerNativeMethod(jlClass, "getDeclaredConstructors0", "(Z)[Ljava/lang/reflect/Constructor;", getDeclaredConstructors0);
	registerNativeMethod(jlClass, "getModifiers", "()I", getModifiers);
	registerNativeMethod(jlClass, "getSuperclass", "()Ljava/lang/Class;", getSuperclass);
	registerNativeMethod(jlClass, "getInterfaces0", "()[Ljava/lang/Class;", getInterfaces0);
	registerNativeMethod(jlClass, "isArray", "()Z", isArray);
	//registerNativeMethod(jlClass, "getDeclaredMethods0", "(Z)[Ljava/lang/reflect/Method;", getDeclaredMethods0);
	registerNativeMethod(jlClass, "getComponentType", "()Ljava/lang/Class;", getComponentType);
	registerNativeMethod(jlClass, "isAssignableFrom", "(Ljava/lang/Class;)Z", isAssignableFrom);
 
}