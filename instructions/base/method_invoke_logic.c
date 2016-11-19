#include "../factory.h"
#include "../../rtda/frame.h"
#include "../../rtda/thread.h"
#include "../../rtda/operand_stack.h"
#include "../../rtda/local_vars.h"
#include "../../rtda/heap/slot.h"
#include "../../rtda/heap/constant_pool.h"
#include "../../rtda/heap/cp_symref.h"
#include "../../rtda/heap/field.h"
#include "../../rtda/heap/cp_fieldref.h"


void InvokeMethod(Frame * invokerFrame, Method * method) {
	Thread * thread = invokerFrame->thread;
	Frame * frame = newFrame(thread, method, method->maxLocals, method->maxStack);
	pushThreadFrame(thread, frame);

	int32_t argSlotSlot = method->argSlotCount;
	if (argSlotSlot > 0)
	{
		for (int32_t i = argSlotSlot - 1; i >= 0; i--)
		{
			Slot * slot = popOperandSlot(invokerFrame->operandStack);
			setLocalVarsSlot(frame->localVars, i, slot);
		}
	}
	
	if (isMethodNative(method))
	{
		if (strcmp(method->classMember.name, "registerNatives") == 0)
		{
			popThreadFrame(thread);
		}else{
			printf("native method: %s %s %s\n",method->classMember.attachClass->name,
				method->classMember.name, method->classMember.descriptor);
		}
	}
}
