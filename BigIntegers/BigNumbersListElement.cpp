#include "BigNumbersListElement.h"

BigNumbersList::Element::~Element()
{
	if(number != nullptr)
		delete number;
}
