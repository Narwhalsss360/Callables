#include "Callables.h"

void Callable::operator()(any_ptr pointer)
{
	invoke(pointer);
}

VoidCallableVoid::VoidCallableVoid(VoidFunctionVoid function)
	: function(function)
{
}

void VoidCallableVoid::invoke(any_ptr pointer)
{
	if (function)
		function();
}

VoidCallableAny::VoidCallableAny(VoidFunctionAny function)
	: function(function)
{
}

void VoidCallableAny::invoke(any_ptr pointer)
{
	if (function)
		function(pointer);
}