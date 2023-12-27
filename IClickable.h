#pragma once
#include "EventManager.h"
class IClickable
{
	virtual bool OnClick(EventDetails* details) = 0;
};

