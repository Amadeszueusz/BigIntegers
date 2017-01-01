#pragma once
#include <string>

class BigNumber
{
public:
	virtual ~BigNumber();
	virtual std::string value() const = 0;
};