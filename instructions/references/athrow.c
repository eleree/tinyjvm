#include "../factory.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/slot.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"
#include "../../rtda/heap/field.h"
#include "../../rtda/heap/cp_fieldref.h"
#include "../../rtda/thread.h"
#include "../../rtda/frame.h"
#include "../../native/registry.h"
bool findAndGotoExceptionHandler(Thread * thread, Object * ex)
{
	for (;;)
	{
		Frame * frame = getCurrentFrame(thread);
		int32_t pc = frame->nextPC - 1;
		int32_t handlerPC = findMethodExceptionHander(frame->method, ex->class, pc);
		if (handlerPC > 0)
		{
			OperandStack * operandStack = frame->operandStack;
			clearOperandStack(operandStack);
			pushOperandRef(operandStack, ex);
			setFrameNextPC(frame, handlerPC);
			return true;
		}

		popThreadFrame(thread);
		if (isThreadStackEmpty(thread))
			break;
	}

	return false;
}


void handleUncaughtException(Thread *thread, Object * ex)
{
	clearThreadStack(thread);
	Object * jMsg = getObjectRefVar(ex,"detailMessage", "Ljava/lang/String;");
	String * goMsg = goString(jMsg);
	printf("%s:%s\n", classJavaName(ex->class), goMsg->data);
	StackTraceElement* *stes = (StackTraceElement* *)ex->extra;
	for (int32_t i = 0; i < ex->extraCount; i++)
	{
		printf("\tat %s%s(%s:%d)\n",stes[i]->className,stes[i]->methodName,stes[i]->fileName,stes[i]->lineNumber);
	}
}

// Throw exception or error
static int32_t execute_ATHROW(Frame * frame, struct InsturctionData * instData)
{
	ConstantPoolItem * cp = NULL;
	OperandStack * operandStack = frame->operandStack;
	Object * ex = popOperandRef(operandStack);

	if (ex == NULL)
		panic("java.lang.NullPointerException\n", 160);

	Thread * thread = frame->thread;
	if (!findAndGotoExceptionHandler(thread, ex))
		handleUncaughtException(thread, ex);

	return 0;
}

Instruction * ATHROW(Instruction * inst)
{
	inst->fetchOperands = noOperandsInstructionFetchOperands;
	inst->execute = execute_ATHROW;
	return inst;
}
