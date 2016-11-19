#include "method.h"

Method * lookupMethodInClass(Class *class, char * name, char *  descriptor)
{
	Class * c = class;
	while (c != NULL)
	{
		for (uint16_t i = 0; i < c->methodsCount; i++)
		{
			Method * method = c->methods + i;
			if (strcmp(method->classMember.name, name) == 0 &&
				strcmp(method->classMember.descriptor, descriptor) == 0)
				return method;
		}
		c = c->superClass;
	}
	return NULL;
}

Method * lookupMethodInInterfaces(Class ** ifaces, uint16_t ifacesCount, char * name, char * descriptor)
{
	Method * method = NULL;
	for (uint16_t i = 0; i < ifacesCount; i++)
	{
		Class * iface = *(ifaces + i);
		for (uint16_t m = 0; m < iface->methodsCount; m++)
		{
			method = iface->methods + m;
			if (strcmp(method->classMember.name, name) == 0 &&
				strcmp(method->classMember.descriptor, descriptor) == 0)
				return method;
		}
		method = lookupMethodInInterfaces(iface->interfaces, iface->interfacesCount, name, descriptor);
		if (method != NULL)
			return method;
	}
	return NULL;
}