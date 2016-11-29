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

void InitClass(Thread * thread, Class * class);

void initSuperClass(Thread * thread, Class * c)
{
	if(!isClassInterface(c))
	{
		Class * superClass = c->superClass;
		if (superClass != NULL && !superClass->initStarted)
		{
			InitClass(thread, superClass);
		}
	}
}

void scheduleClinit(Thread * thread, Class * c)
{
	Method * clinit = getClassClinitMethod(c);
	if (clinit != NULL)
	{
		Frame * nFrame = newFrame(thread, clinit, clinit->maxLocals, clinit->maxStack);
		pushThreadFrame(thread, nFrame);
	}
}

void InitClass(Thread * thread, Class * c)
{
	startClassInit(c);
	scheduleClinit(thread, c);
	initSuperClass(thread, c);
}