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

void initSuperClass(Thread * thread, Class * class)
{

}

void scheduleClinit(Thread * thread, Class * class)
{

}

void InitClass(Thread * thread, Class * class)
{
	startClassInit(class);
	scheduleClinit(thread, class);
	initSuperClass(thread, class);
}