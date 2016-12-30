#include "BigInteger.h"
#include "BigIntegersUtility.h"
#include <algorithm>
#include <vector>

BigInteger::BigInteger() : 
	value_size(1),
	is_value_negative(false)
{
	_value = new char[value_size + 1],
	_value[0] = '0';
	_value[1] = '\0';
}

BigInteger::BigInteger(const int & value)
{
	is_value_negative = value < 0;

	auto str = std::to_string(std::abs(value));

	value_size = str.size();

	_value = new char[value_size + 1];

	std::reverse(str.begin(), str.end());

	strcpy(_value, str.c_str());
}

BigInteger::BigInteger(const char * value)
{
	if (value == nullptr)
		throw std::invalid_argument("Input value is nullptr");

	std::string str(value);

	if(!is_integer(str))
		throw std::invalid_argument("Input string is not covertable to int");

	is_value_negative = is_negative(str);

	std::reverse(str.begin(), str.end());

	if(is_value_negative)
		str.pop_back();	// get rid of '-' char

	value_size = str.size();

	_value = new char[value_size + 1];

	strcpy(_value, str.c_str());
}

BigInteger::BigInteger(const BigInteger & other) : 
	value_size(other.value_size),
	is_value_negative(other.is_value_negative),
	_value(nullptr)
{
	_value = new char[value_size + 1];
	strcpy(_value, other._value);
}

BigInteger::BigInteger(BigInteger && other) : 
	value_size(std::move(other.value_size)),
	_value(std::move(other._value)),
	is_value_negative(std::move(other.is_value_negative))
{
	other._value = nullptr;
}

BigInteger::~BigInteger()
{
	if (_value != nullptr)
		delete[] _value;
}

std::string BigInteger::value() const
{
	std::string tmp(_value);

	if (is_value_negative)
		tmp.push_back('-');

	std::reverse(tmp.begin(), tmp.end());

	return tmp;
}

BigInteger & BigInteger::operator=(const BigInteger & rhs)
{
	if (&rhs == this)
		return *this;

	if (nullptr != _value)
		delete[] _value;

	value_size = rhs.value_size;
	is_value_negative = rhs.is_value_negative;

	_value = new char[value_size + 1];
	strcpy(_value, rhs._value);

	return *this;
}

BigInteger & BigInteger::operator=(BigInteger && rhs)
{
	if (&rhs == this)
		return *this;

	if (nullptr != _value)
		delete[] _value;

	value_size = std::move(rhs.value_size);
	is_value_negative = std::move(rhs.is_value_negative);

	_value = std::move(rhs._value);
	rhs._value = nullptr;

	return *this;
}

BigInteger & BigInteger::operator+=(const BigInteger & rhs)
{
	if (!is_value_negative && !rhs.is_value_negative ||
		is_value_negative && rhs.is_value_negative)
	{
		*this = add(*this, rhs);
	}
	else if (is_value_negative)
	{
		*this = substract(rhs, (-*this));
	}
	else
	{
		*this = substract(*this, (-rhs));
	}

	return *this;
}

BigInteger & BigInteger::operator-=(const BigInteger & rhs)
{
	return (*this += (-rhs));
}

BigInteger & BigInteger::operator*=(const BigInteger & rhs)
{
	return (*this = multiply(*this, rhs));
}

BigInteger & BigInteger::operator/=(const BigInteger & rhs)
{
	return (*this = divide(*this, rhs));
}

std::istream & operator >> (std::istream & is, BigInteger & rhs)
{
	std::string str;
	is >> str;

	rhs = BigInteger(str.c_str());

	return is;
}

std::ostream & operator<<(std::ostream & os, const BigInteger & rhs)
{
	os << rhs.value();

	return os;
}

BigInteger operator+(BigInteger lhs, const BigInteger & rhs)
{
	lhs += rhs;
	return lhs;
}

BigInteger operator-(BigInteger lhs, const BigInteger & rhs)
{
	lhs -= rhs;
	return lhs;
}

bool operator<(const BigInteger & lhs, const BigInteger & rhs)
{
	if (lhs.is_value_negative && !rhs.is_value_negative)
		return true;
	else if (!lhs.is_value_negative && rhs.is_value_negative)
		return false;
	else if (lhs.value_size < rhs.value_size)
		return !(lhs.is_value_negative && rhs.is_value_negative);
	else if (lhs.value_size > rhs.value_size)
		return (lhs.is_value_negative && rhs.is_value_negative);
	else
	{
		for (int i = lhs.value_size - 1; i >= 0; i--)
		{
			if (lhs._value[i] - '0' < rhs._value[i] - '0')
				return !lhs.is_value_negative;
			else if (lhs._value[i] - '0' > rhs._value[i] - '0')
				return lhs.is_value_negative;
		}

		return false;
	}
}

bool operator>(const BigInteger & lhs, const BigInteger & rhs)
{
	return rhs < lhs;
}

bool operator<=(const BigInteger& lhs, const BigInteger& rhs)
{
	return !(lhs > rhs);
}

bool operator>=(const BigInteger& lhs, const BigInteger& rhs)
{
	return !(lhs < rhs);
}

bool operator==(const BigInteger& lhs, const BigInteger& rhs)
{
	return !(lhs > rhs) && !(lhs < rhs);
}

bool operator!=(const BigInteger& lhs, const BigInteger& rhs)
{
	return !(lhs == rhs);
}

BigInteger operator*(BigInteger lhs, const BigInteger & rhs)
{
	return lhs *= rhs;
}

BigInteger operator/(BigInteger lhs, const BigInteger & rhs)
{
	return lhs /= rhs;
}

BigInteger operator-(const BigInteger & rhs)
{
	BigInteger out(rhs);
	out.is_value_negative = !out.is_value_negative;
	return out;
}

BigInteger abs(const BigInteger & rhs)
{
	BigInteger out(rhs);
	out.is_value_negative = false;
	return out;

}

BigInteger operator!(BigInteger rhs)
{
	if(rhs.is_value_negative)
		throw std::invalid_argument("Factorial for negative values in undefined");

	if (rhs == 1 || rhs == 0)
		return rhs;

	BigInteger product(rhs);

	while (rhs > 1) {
		rhs -= 1;
		product *= rhs;
	}

	return product;
}

BigInteger add(const BigInteger & lhs, const BigInteger & rhs)
{
	int remainder = 0;
	int pos = 0;
	size_t maxSize = std::max(lhs.value_size, rhs.value_size);

	std::string product;
	product.reserve(maxSize);

	do
	{
		int lvalue = (pos < lhs.value_size ? lhs._value[pos] - '0' : 0);
		int rvalue = (pos < rhs.value_size ? rhs._value[pos] - '0' : 0);

		int sum = lvalue + rvalue + remainder;
		remainder = sum / 10;
		sum %= 10;

		product.push_back('0' + sum);

		pos++;

	} while (remainder != 0 || pos < maxSize);

	if (rhs.is_value_negative)
		product.push_back('-');

	std::reverse(product.begin(), product.end());

	return BigInteger(product.c_str());
}

BigInteger substract(const BigInteger & lhs, const BigInteger & rhs)
{
	int remainder = 0;
	int pos = 0;
	size_t maxSize = std::max(lhs.value_size, rhs.value_size);

	std::string product;
	product.reserve(maxSize);

	if (lhs < rhs) 
	{
		BigInteger output(substract(rhs, lhs));
		output.is_value_negative = true;
		return output;
	}

	do
	{
		int lvalue = (pos < lhs.value_size ? lhs._value[pos] - '0' : 0);
		int rvalue = (pos < rhs.value_size ? rhs._value[pos] - '0' : 0);

		int sub = lvalue - rvalue - remainder;

		remainder = 0;

		if (sub < 0) 
		{
			sub += 10;
			remainder = 1;
		}

		product.push_back('0' + sub);

		pos++;

	} while (remainder != 0 || pos < maxSize);

	while (product.size() != 1 && product.back() == '0')
		product.pop_back();

	std::reverse(product.begin(), product.end());

	return BigInteger(product.c_str());
}

BigInteger multiply(const BigInteger & lhs, const BigInteger & rhs)
{
	std::vector<int> values;
	const size_t maxSize = lhs.value_size + rhs.value_size;
	values.resize(maxSize, 0);

	for (int i = 0; i < lhs.value_size; i++)
	{
		for (int j = 0; j < rhs.value_size; j++)
		{
			values[i + j] += ((lhs._value[i] - '0') * (rhs._value[j] - '0'));
		}
	}

	for (int pos = 0; pos < maxSize; pos++)
	{
		int val = values[pos];
		int remainder = val / 10;
		values[pos] = val % 10;

		if (remainder > 0)
			values[pos + 1] += remainder;
	}

	std::string product;
	product.resize(values.size());

	for (int i = 0; i < values.size(); i++)
		product[i] = values[i] + '0';

	while (product.size() != 1 && product.back() == '0')
		product.pop_back();

	if (lhs.is_value_negative != rhs.is_value_negative)
		product.push_back('-');

	std::reverse(product.begin(), product.end());

	return BigInteger(product.c_str());
}

BigInteger divide(BigInteger lhs, BigInteger rhs)
{
	if (rhs == 0)
		throw std::invalid_argument("Division by 0");

	const bool output_negative = (lhs.is_value_negative != rhs.is_value_negative);

	lhs = abs(lhs);
	rhs = abs(rhs);

	if (lhs < rhs)
		return 0;

	std::string product_s;
	const size_t maxSize = std::max(lhs.value_size, rhs.value_size);
	product_s.reserve(maxSize);
	std::string reminder_s("0");

	for (int i = lhs.value_size - 1; i >= 0; i--)
	{
		if (lhs._value[i] != '0' || reminder_s.front() != '0')
		{
			if (reminder_s.front() == '0')
				reminder_s.clear();

			reminder_s.push_back(lhs._value[i]);
		}

		BigInteger reminder(reminder_s.c_str());

		if (reminder >= rhs)
		{
			int val = 1;

			BigInteger divider(rhs);

			while ((divider + rhs) <= reminder) {
				divider += rhs;
				val++;
			}

			reminder -= divider;

			reminder_s = reminder._value;
			std::reverse(reminder_s.begin(), reminder_s.end());

			product_s.push_back(val + '0');
		}
		else
		{
			product_s.push_back('0');
		}
	}

	while (product_s.size() != 1 && product_s.front() == '0')
		product_s.erase(product_s.begin());

	BigInteger product(product_s.c_str());
	product.is_value_negative = output_negative;

	return product;
}
