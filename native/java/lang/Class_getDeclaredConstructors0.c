#include "../../registry.h"

const char * _constructorConstructorDescriptor = 
	""\
	"(Ljava/lang/Class;"\
	"[Ljava/lang/Class;"\
	"[Ljava/lang/Class;"\
	"II"\
	"Ljava/lang/String;"\
	"[B[B)V";


// private native Constructor<T>[] getDeclaredConstructors0(boolean publicOnly);
// (Z)[Ljava/lang/reflect/Constructor;
void getDeclaredConstructors0(Frame * frame)
{
	LocalVars * vars = frame->localVars;
	Object * classObj = getLocalVarsThis(vars);
	bool publicOnly = getLocalVarsBoolean(vars, 1);

	uint16_t constructorsCount = 0;
	Class * c = classObj->extra;
	Method* * constructors = getClassConstructors(c, publicOnly, &constructorsCount);

	ClassLoader *  classLoader = frame->method->classMember.attachClass->classLoader;
	
	Class * constructorClass = loadClass(classLoader, "java/lang/reflect/Constructor");

	Object * constructorArr = newArray(arrayClass(constructorClass), constructorsCount);

	pushOperandRef(frame->operandStack, constructorArr);

	if (constructorsCount > 0)
	{
		Thread * thread = frame->thread;
		Object* * constructorObjs = getObjectRefs(constructorArr);

		Method * constructorInitMethod = getClassConstructor(constructorClass, _constructorConstructorDescriptor);
		for (uint16_t i = 0; i < constructorsCount; i++)
		{
			Method * constructor = constructors[i];

			Object * constructorObj = newObject(constructorClass);
			constructorObj->extra = constructor;
			constructorObjs[i] = constructorObj;

			OperandStack * ops = newOperandStack(9);
			pushOperandRef(ops, constructorObj);
			pushOperandRef(ops, classObj);
			pushOperandRef(ops, toClassArr(classLoader, methodParameterTypes(constructor), constructor->parsedDescriptor->parameterTypesCount));
			if (constructor->exceptions != NULL)
				pushOperandRef(ops, toClassArr(classLoader, methodExceptionTypes(constructor), constructor->exceptions->number_of_exceptions));
			else
				pushOperandRef(ops, toClassArr(classLoader, methodExceptionTypes(constructor), 0));
			pushOperandInt(ops, constructor->classMember.accessFlags);
			pushOperandInt(ops, 0);
			pushOperandRef(ops, getSignatureStr(classLoader, constructor->classMember.signature));         // signature
			pushOperandRef(ops, toByteArr(classLoader, constructor->classMember.annotationData, constructor->classMember.annotationDataLen));
			pushOperandRef(ops, toByteArr(classLoader, constructor->parameterAnnotationData, constructor->parameterAnnotationDataLen));


			Frame * shimFrame = newShimFrame(thread, ops);
			pushThreadFrame(thread, shimFrame);

			// init constructorObj
			InvokeMethod(shimFrame, constructorInitMethod);
		}


	}
}