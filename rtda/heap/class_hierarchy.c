#include "class.h"
#include "array_class.h"
bool isSubClassOf(Class * thisClass, Class * otherClass)
{
	Class *  c = thisClass->superClass;

	while (c != NULL)
	{
		if (c == otherClass)
			return true;
		c = c->superClass;
	}

	return false;
}

bool isClassAssignableFrom(Class * thisClass, Class * otherClass)
{
	Class * s = otherClass;
	Class * t = thisClass;
	if (s == t)
		return true;
	if (!isClassArray(s))
	{
		if (!isClassInterface(s))
		{
			if (!isClassInterface(t))
				// t is not interface
				return isClassSubClassOf(s, t);
			else
				// t is interface
				return isClassImplements(s, t);
		}
		else{
			// s is interface
			if (!isClassInterface(t))
			{
				// t is not interface
				return isClassJlObject(t);
			}
			else{
				// t is interface
				return isClassSubInterfaceOf(t, s);
			}

		}
	}else{
		// s is array
		if (!isClassArray(t))
		{
			if (!isClassInterface(t))
			{
				// t is class
				return  isClassJlObject(t);
			}else{
				// t is interface
				return isClassJlCloneable(t) || isClassJioSerializable(t);
			}

		}else{
			// t is array
			Class * sc = componentClass(s);
			Class * tc = componentClass(t);
			return sc == tc || isClassAssignableFrom(tc, sc);
		}
	}

}
