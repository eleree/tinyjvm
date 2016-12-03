#include "../../registry.h"

/*
Field(Class<?> declaringClass,
String name,
Class<?> type,
int modifiers,
int slot,
String signature,
byte[] annotations)
*/
const char *  _fieldConstructorDescriptor = 
	""\
	"(Ljava/lang/Class;"\
	"Ljava/lang/String;"\
	"Ljava/lang/Class;"\
	"II"\
	"Ljava/lang/String;"\
	"[B)V";


// private native Field[] getDeclaredFields0(boolean publicOnly);
// (Z)[Ljava/lang/reflect/Field;
void getDeclaredFields0(Frame * frame)
{
	LocalVars * vars = frame->localVars;
	Object * classObj = getLocalVarsThis(vars);
	bool publicOnly = getLocalVarsBoolean(vars, 1);

	uint16_t fieldCount = 0;
	Class * c = classObj->extra;
	Field* * fields = getClassFields(c, publicOnly,&fieldCount);

	ClassLoader *  classLoader = frame->method->classMember.attachClass->classLoader;
	Class * fieldClass = loadClass(classLoader, "java/lang/reflect/Field");

	Object * fieldArr = newArray(arrayClass(fieldClass), fieldCount);

	pushOperandRef(frame->operandStack, fieldArr);

	if (fieldCount > 0)
	{
		Thread * thread = frame->thread;
		Object* * fieldObjs = getObjectRefs(fieldArr);
		Method * fieldConstructor = getClassConstructor(fieldClass, _fieldConstructorDescriptor);
		for (uint16_t i = 0; i < fieldCount; i++)
		{
			Field * goField = fields[i];
			Object * fieldObj = newObject(fieldClass);
			fieldObj->extra = goField;
			fieldObjs[i] = fieldObj;

			OperandStack * ops = newOperandStack(8);
			pushOperandRef(ops, fieldObj);
			pushOperandRef(ops, classObj);
			String tempStr;
			tempStr.data = goField->classMember.name;
			tempStr.len = strlen(goField->classMember.name);
			pushOperandRef(ops, jString(classLoader,&tempStr));
			pushOperandRef(ops, fieldType(goField)->jClass);
			pushOperandInt(ops, goField->classMember.accessFlags);
			pushOperandInt(ops, goField->slotId);
			pushOperandRef(ops, getSignatureStr(classLoader, goField->classMember.signature));
			pushOperandRef(ops, toByteArr(classLoader, goField->classMember.annotationData, goField->classMember.annotationDataLen));

			Frame * shimFrame = newShimFrame(thread, ops);
			pushThreadFrame(thread, shimFrame);

			printf("i:%d\n", i);
			InvokeMethod(shimFrame, fieldConstructor);
		}
	}

}