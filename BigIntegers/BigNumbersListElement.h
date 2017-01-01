#pragma once
#include "BigNumbersList.h"

class BigNumbersList::Element
{
public:
	~Element();

	BigNumber* number;
	Element* next;
	Element* prev;
};
