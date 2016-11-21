#include "method.h"

void addParameterType(MethodDescriptor * methodDesc, const char * t)
{
	uint16_t pLen = methodDesc->parameterTypesCount;
	ParameterTypesList * ptList = methodDesc->parameterTypesList;
	ParameterTypesList * prePtList = NULL;

	while (ptList != NULL)
	{
		prePtList = ptList;
		ptList = ptList->next;
	}

	ptList = calloc(1, sizeof(ParameterTypesList));
	ptList->next = NULL;
	ptList->parameterTypes = _strdup(t);

	methodDesc->parameterTypesCount++;
	if (prePtList == NULL)
	{
		methodDesc->parameterTypesList = ptList;
		return;
	}

	prePtList->next = ptList;

	return;
}