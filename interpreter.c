#include "interpreter.h"
#include "rtda\thread.h"
#include "rtda\frame.h"
#include "rtda\local_vars.h"
#include "rtda\heap\method.h"
#include "instructions\factory.h"
#include "instructions\base\bytecode_reader.h"

void dumpLocalVars(Frame * frame)
{
	LocalVars * localVars = frame->localVars;
	if (frame->localVars == NULL)
	{
		printf("frame->localVars is NULL,Not log\n");
		return;
	}
	printf("Local Vars:");
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
void loop(Class * c, Thread * thread, uint8_t * bytecode, uint32_t bytecodeLen)
{
	Frame * frame = NULL;
	//Frame * frame = popThreadFrame(thread);
	
	int32_t pc = 0;
	uint8_t opcode = 0;
	BytecodeReader bytecodeReader;
	for (;;)
	{
		frame = getCurrentFrame(thread);
		
		pc = getFrameNextPC(frame);
		setThreadPC(thread, pc);
		resetBytecodeReader(&bytecodeReader, frame->method->code, frame->method->codeLen, pc);
		opcode = readBytecodeUint8(&bytecodeReader);
		//printf("pc:0x%02x, opcode:0x%02x\n", pc, opcode);
		//dumpLocalVars(frame);
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

void interpret(Class * c, Method * method)
{
	uint16_t maxLocals = method->maxLocals;
	uint16_t maxStack = method->maxStack;
	uint32_t bytecodeLen = method->codeLen;
	uint8_t * bytecode = method->code;

	Thread * thread = newThread();
	Frame * frame = newFrame(thread, method, maxLocals, maxStack);
	pushThreadFrame(thread, frame);

	//Print LocalVars & OperandStack
	loop(c, thread, bytecode, bytecodeLen);
}
