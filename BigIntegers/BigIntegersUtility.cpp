#include "BigIntegersUtility.h"

bool is_integer(const std::string & str)
{
	if (str.empty())
		return false;

	// checks if the first letter in the string is one of the following: -0123456789
	if (std::string(1, str[0]).find_first_not_of("-0123456789") != std::string::npos)
		return false;

	if (str.size() > 1) 
	{
		// first char can't be 0 if string consists of more that one char
		if (str[0] == '0')
			return false;

		// ensure that whole string except of the fisrt char consists only numbers 0-9
		if (str.find_first_not_of("0123456789", 1) != std::string::npos)
			return false;
	}
	else 
	{
		// ensure that the fisrt (and only) char in the string is not '-'
		if (str[0] == '-')
			return false;
	}

	return true;
}

bool is_negative(const std::string & str)
{
	return str[0] == '-';
}
