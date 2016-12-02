#include "../../registry.h"

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
	"x64_86", // todo
	"os.version",
	"",             // todo
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
	printf("Invoke Native Method %s\n", __FUNCTION__);
	LocalVars * vars = frame->localVars;
	Object * props = getLocalVarsRef(vars, 0);

	pushOperandRef(frame->operandStack, props);
	// public synchronized Object setProperty(String key, String value)	
	Method * setPropMethod = getClassInstanceMethod(props->class, "setProperty", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Object;");
	ClassLoader * classLoader = setPropMethod->classMember.attachClass->classLoader;

	Thread * thread = frame->thread;
	for (uint16_t i = 0; i < sizeof(_sysProps) / sizeof(char*)/2; i+=2)
	{
		String tempStr;
		tempStr.data = _sysProps[i];
		tempStr.len = strlen(_sysProps[i]);
		Object * jKey = jString(classLoader, &tempStr);

		tempStr.data = _sysProps[i+1];
		tempStr.len = strlen(_sysProps[i+1]);
		Object * jVal = jString(classLoader, &tempStr);

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
	printf("Invoke Native Method %s\n", __FUNCTION__);
	exit(1);
}

// private static native void setOut0(PrintStream out);
// (Ljava/io/PrintStream;)V
void  setOut0(Frame * frame)
{
	printf("Invoke Native Method %s\n", __FUNCTION__);
	exit(1);
}

// private static native void setErr0(PrintStream err);
// (Ljava/io/PrintStream;)V
void  setErr0(Frame * frame)
{
	printf("Invoke Native Method %s\n", __FUNCTION__);
	exit(1);
}

// public static native long currentTimeMillis();
// ()J
void  currentTimeMillis(Frame * frame)
{
	printf("Invoke Native Method %s\n", __FUNCTION__);
	exit(1);
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