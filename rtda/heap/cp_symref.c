#include "cp_symref.h"

void resolveClassRef(SymRef * symRef)
{
	Class * d = symRef->constantPool->class;
	Class * c = loadClass(d->classLoader, symRef->className);

#if 0
	if (!isClassAccessibleTo(d, c))
	{
		printf("java.lang.IllegalAccessError\n");
		exit(1);
	}
#endif

	symRef->class = c;
}

Class * resolveClass(SymRef * symRef)
{
	if (symRef->class == NULL)
	{
		resolveClassRef(symRef);
	}
	return symRef->class;
}

