#include "class.h"

bool isSubClassOf(Class * thisClass, Class * otherClass)
{
	Class *  c = thisClass->superClass;

	while (c != NULL)
	{
		c = c->superClass;
		if (c == otherClass)
			return true;
	}

	return false;
}