#include "interpreter.h"
#include "rtda\thread.h"
#include "rtda\frame.h"
#include "rtda\local_vars.h"
#include "rtda\heap\method.h"
#include "instructions\factory.h"
#include "instructions\base\bytecode_reader.h"
#include "rtda\heap\class_loader.h"
#include "native/registry.h"

char * opcodeName[256]=
{
	"", // 0x00
	"", // 0x01 
	"",
};

static uint64_t instIndex = 0;
void dumpLocalVars(Frame * frame)
{
	LocalVars * localVars = frame->localVars;
	if (frame->localVars == NULL)
	{
		printf("  frame->localVars is NULL,Not log\n");
		return;
	}
	printf("  Local Vars:");
	for (uint32_t i = 0; i < localVars->size; i++)
	{
		printf("%d,", getLocalVarsInt(localVars,i));
	}
	printf("\n");
}

#if 0
void loop(ClassFile * classFIle, Thread * thread, uint8_t * bytecode,uint32_t bytecodeLen)
{
	Frame * frame = popThreadFrame(thread);
	int32_t pc = 0;
	uint8_t opcode = 0;
	BytecodeReader bytecodeReader;
	for (;;)
	{
		pc = getFrameNextPC(frame);
		setThreadPC(thread, pc);
		resetBytecodeReader(&bytecodeReader, bytecode, bytecodeLen, pc);
		opcode = readBytecodeUint8(&bytecodeReader);
		printf("pc:0x%02x, opcode:0x%02x\n", pc, opcode);
		dumpLocalVars(frame);
		Instruction * inst = newInsturction(opcode);
		InstructionData instData = { 0 };
		if (inst != NULL)
		{
			inst->fetchOperands(&bytecodeReader, &instData);
			setFrameNextPC(frame, getBytecodeReaderPC(&bytecodeReader));
			inst->execute(frame, &instData);
		}
		
	}
}

void interpret(ClassFile * classFile, MethodInfo * methodInfo)
{
	CodeAttribute * codeAttr = getMethodCodeAttribute(classFile, methodInfo);
	uint16_t maxLocals = codeAttr->max_locals;
	uint16_t maxStack = codeAttr->max_stack;
	uint32_t bytecodeLen = codeAttr->code_length;
	uint8_t * bytecode = codeAttr->code;

	Thread * thread = newThread();
	Frame * frame = newFrame(thread,maxLocals, maxStack);
	pushThreadFrame(thread, frame);

	//Print LocalVars & OperandStack
	loop(classFile, thread, bytecode, bytecodeLen);
}
#endif
void initNative(void)
{
	initNativeClass();
	initNativeDouble();
	initNativeFloat();
	initNativeObject();
	initNativeString();
	initNativeSystem();
	initVM();
	initNativeThrowable();
	initUnsafe();
	initReflect();
	initNativeFileDescriptor();
	initAccessController();
	initNativeThread();
	initConstructorAccessorImpl();
	initUnsafeMem();
	initSignal();
	initWin32ErrorMode();
	initNativeFileOutputStream();
}

Object * createArgsArray(ClassLoader * classLoader, char ** argv, int argc)
{
	Class * stringClass = loadClass(classLoader, "java/lang/String");
	Class * arrClass = arrayClass(stringClass);
	Object * argsArr = newArray(arrClass, argc);
	Object* * jArgs = getObjectRefs(argsArr);
	for (int32_t i = 0; i < argc; i++)
	{
		String utf8Str = { 0 };
		utf8Str.data = argv[i];
		utf8Str.len = strlen(argv[i]);
		jArgs[i] = jString(classLoader, &utf8Str);
	}

	return argsArr;
}

void loop(Class * c, Thread * thread, uint8_t * bytecode, uint32_t bytecodeLen)
{
	Frame * frame = NULL;
	//Frame * frame = popThreadFrame(thread);
	
	int32_t pc = 0;
	uint8_t opcode = 0;
	BytecodeReader bytecodeReader;
	initNative();
	
	for (;;)
	{
		frame = getCurrentFrame(thread);
		
		pc = getFrameNextPC(frame);
		setThreadPC(thread, pc);
		resetBytecodeReader(&bytecodeReader, frame->method->code, frame->method->codeLen, pc);
		opcode = readBytecodeUint8(&bytecodeReader);

#if 0
		//printf("%d\n", instIndex++);
		//if (instIndex >= 18942)
		{
			//for (uint16_t i = 0; i < totalFrams(thread->stack); i++)
			//	printf(" ");
			printf("%s.%s() #%2d *0x%02x index:%d\n", frame->method->classMember.attachClass->name,
				frame->method->classMember.name, pc, opcode, instIndex);
			//printf("%s.%s() #%2d\n", frame->method->classMember.attachClass->name,
			//	frame->method->classMember.name, pc, opcode, instIndex);
		}
		//printf("  %s\n", frame->method->classMember.name);
		//printf("  %s\n", frame->method->classMember.descriptor);
		//printf("  pc:0x%02x, opcode:0x%02x\n", pc, opcode);
		//dumpLocalVars(frame);
#endif 
		//if (strcmp("sun/misc/FDBigInteger", frame->method->classMember.attachClass->name) == 0)
			//strcmp("put", frame->method->classMember.name) == 0)
		//	printf("probe");
		//	printf("probe\n");
		//	printf("%s.%s() #%2d *0x%02x index:%d\n", frame->method->classMember.attachClass->name,
		//	frame->method->classMember.name, pc, opcode, instIndex);

		instIndex++;
		if (instIndex > 32000)
		{
		//	exit(0);
		//	printf("probe\n");
		}
		Instruction * inst = newInsturction(opcode);
		InstructionData instData = { 0 };
		if (inst != NULL)
		{
			inst->fetchOperands(&bytecodeReader, &instData);
			setFrameNextPC(frame, getBytecodeReaderPC(&bytecodeReader));
			inst->execute(frame, &instData);
		}

		if (isThreadStackEmpty(thread))
			break;
	}
}

void interpretThread(Thread * thread)
{
	loop(NULL, thread, NULL, 0);
}

void interpret(Class * c, Method * method, Thread * thread, int argc, char ** argv)
{
	uint16_t maxLocals = method->maxLocals;
	uint16_t maxStack = method->maxStack;
	uint32_t bytecodeLen = method->codeLen;
	uint8_t * bytecode = method->code;

	Frame * frame = newFrame(thread, method, maxLocals, maxStack);
	pushThreadFrame(thread, frame);

	Object * jArgs = createArgsArray(c->classLoader, argv, argc);
	setLocalVarsRef(frame->localVars, 0, jArgs);
	//Print LocalVars & OperandStack
	loop(c, thread, bytecode, bytecodeLen);
}
