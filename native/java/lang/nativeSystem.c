#include "../../registry.h"
#include <time.h>

#pragma warning(disable:4996)

const char * jlSystem = "java/lang/System";


bool checkArrayCopy(Object * src, Object * dest)
{
	Class * srcClass = src->class;
	Class * destClass = dest->class;
	
	if (!isClassArray(srcClass) || !isClassArray(destClass))
	{
		return false;
	}

	if (isClassPrimitive(componentClass(srcClass)) ||
		isClassPrimitive(componentClass(destClass))
		)
		return srcClass == destClass;
	return true;
}

void  arraycopy(Frame * frame)
{
	LocalVars * vars = frame->localVars;
	Object * src = getLocalVarsRef(vars, 0);
	int32_t srcPos = getLocalVarsInt(vars, 1);
	Object * dest = getLocalVarsRef(vars, 2);
	int32_t destPos = getLocalVarsInt(vars, 3);
	int32_t length = getLocalVarsInt(vars, 4);

	if (src == NULL || dest == NULL)
		panic("java.lang.NullPointerException\n", -1);

	if (!checkArrayCopy(src,dest))
		panic("java.lang.ArrayStoreException\n", -1);

	if (srcPos < 0 || destPos < 0 || length < 0 ||
		srcPos + length > src->dataCount ||
		destPos + length>dest->dataCount)
	{
		panic("java.lang.IndexOutOfBoundsException\n", -1);
	}

	arrayCopy(src, dest, srcPos, destPos, length);
}

char * _sysProps[] = {
	"java.version",
	"1.8.0",
	"java.vendor",
	"jvm.go",
	"java.vendor.url",
	"https://github.com/zxh0/jvm.go",
	"java.home",
	"todo",
	"java.class.version",
	"52.0",
	"java.class.path",
	"todo",
	"java.awt.graphicsenv",
	"sun.awt.CGraphicsEnvironment",
	"os.name",
	"windows",   // todo
	"os.arch",
	"amd64", // todo
	"os.version",
	"7.1",             // todo
	"file.separator",
	"/",            // todo os.PathSeparator
	"path.separator",
	":",            // todo os.PathListSeparator
	"line.separator",
	"\n",           // todo
	"user.name",
	"",             // todo
	"user.home",
	"",             // todo
	"user.dir",
	".",            // todo
	"user.country",
	"CN",           // todo
	"file.encoding",
	"UTF-8",
	"sun.stdout.encoding",
	"UTF-8",
	"sun.stderr.encoding",
	"UTF-8",
};

// private static native Properties initProperties(Properties props);
// (Ljava/util/Properties;)Ljava/util/Properties;
void  initProperties(Frame * frame)
{	
	LocalVars * vars = frame->localVars;
	Object * props = getLocalVarsRef(vars, 0);

	pushOperandRef(frame->operandStack, props);
	// public synchronized Object setProperty(String key, String value)	
	Method * setPropMethod = getClassInstanceMethod(props->class, "setProperty", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Object;");
	ClassLoader * classLoader = setPropMethod->classMember.attachClass->classLoader;

	Thread * thread = frame->thread;
	printf("init Porps Size:%d\n", sizeof(_sysProps) / sizeof(char*));
	for (uint16_t i = 0; i < sizeof(_sysProps) / sizeof(char*); i+=2)
	{
		String *  keyStr = calloc(1, sizeof(String));
		String *  valStr = calloc(1, sizeof(String));

		keyStr->data = strdup(_sysProps[i]);
		keyStr->len = strlen(_sysProps[i]);
		Object * jKey = jString(classLoader, keyStr);

		valStr->data = strdup(_sysProps[i + 1]);
		valStr->len = strlen(_sysProps[i + 1]);
		Object * jVal = jString(classLoader, valStr);

		OperandStack * ops = newOperandStack(3);
		pushOperandRef(ops, props);
		pushOperandRef(ops, jKey);
		pushOperandRef(ops, jVal);
		Frame * shimFrame = newShimFrame(thread, ops);
		InvokeMethod(shimFrame, setPropMethod);
	}
}

// private static native void setIn0(InputStream in);
// (Ljava/io/InputStream;)V
void  setIn0(Frame * frame)
{
	//printf("Invoke Native Method %s\n", __FUNCTION__);
	//exit(1);
	LocalVars * vars = frame->localVars;
	Object * in = getLocalVarsRef(vars, 0);
	Class * sysClass = frame->method->classMember.attachClass;
	setClassRefVar(sysClass, "in", "Ljava/io/InputStream;", in);
}

// private static native void setOut0(PrintStream out);
// (Ljava/io/PrintStream;)V
void  setOut0(Frame * frame)
{
	//printf("Invoke Native Method %s\n", __FUNCTION__);
	//exit(1);
	LocalVars * vars = frame->localVars;
	Object * out = getLocalVarsRef(vars, 0);
	Class * sysClass = frame->method->classMember.attachClass;
	setClassRefVar(sysClass, "out", "Ljava/io/PrintStream;", out);
}

// private static native void setErr0(PrintStream err);
// (Ljava/io/PrintStream;)V
void  setErr0(Frame * frame)
{
	//printf("Invoke Native Method %s\n", __FUNCTION__);
	//exit(1);
	LocalVars * vars = frame->localVars;
	Object * err = getLocalVarsRef(vars, 0);
	Class * sysClass = frame->method->classMember.attachClass;
	setClassRefVar(sysClass, "err", "Ljava/io/PrintStream;", err);
}

// public static native long currentTimeMillis();
// ()J
void  currentTimeMillis(Frame * frame)
{
	time_t nowtime = time(NULL);
	pushOperandLong(frame->operandStack, (int64_t)nowtime);
}

void initNativeSystem(void)
{
	registerNativeMethod(jlSystem, "arraycopy", "(Ljava/lang/Object;ILjava/lang/Object;II)V", arraycopy);
	registerNativeMethod(jlSystem, "initProperties", "(Ljava/util/Properties;)Ljava/util/Properties;", initProperties);
	registerNativeMethod(jlSystem, "setIn0", "(Ljava/io/InputStream;)V", setIn0);
	registerNativeMethod(jlSystem, "setOut0", "(Ljava/io/PrintStream;)V", setOut0);
	registerNativeMethod(jlSystem, "setErr0", "(Ljava/io/PrintStream;)V", setErr0);
	registerNativeMethod(jlSystem, "currentTimeMillis", "()J", currentTimeMillis);
}