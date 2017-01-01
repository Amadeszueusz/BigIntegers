#include "BigComplexInteger.h"

BigComplexInteger::BigComplexInteger() :
	_real(new BigInteger),
	_imag(new BigInteger)
{
}

BigComplexInteger::BigComplexInteger(const int & real) :
	_real(new BigInteger(real)),
	_imag(new BigInteger)
{
}

BigComplexInteger::BigComplexInteger(const int & real, const int & imag) : 
	_real(new BigInteger(real)),
	_imag(new BigInteger(imag))
{
}

BigComplexInteger::BigComplexInteger(const char * real) : 
	_real(new BigInteger(real)),
	_imag(new BigInteger)
{
}

BigComplexInteger::BigComplexInteger(const char * real, const char * imag) : 
	_real(new BigInteger(real)),
	_imag(new BigInteger(imag))
{
}

BigComplexInteger::BigComplexInteger(const BigComplexInteger & other) : 
	_real(new BigInteger(*other._real)),
	_imag(new BigInteger(*other._imag))
{
}

BigComplexInteger::BigComplexInteger(BigComplexInteger && other) : 
	_real(std::move(other._real)),
	_imag(std::move(other._imag))
{
	other._real = other._imag = nullptr;
}

BigComplexInteger::~BigComplexInteger()
{
	if (nullptr != _real)
		delete _real;
	if (nullptr != _imag)
		delete _imag;
}

std::string BigComplexInteger::value() const
{
	return _real->value();
}

BigComplexInteger & BigComplexInteger::operator=(const BigComplexInteger & rhs)
{
	_real = rhs._real;
	_imag = rhs._imag;

	return *this;
}

BigComplexInteger & BigComplexInteger::operator=(BigComplexInteger && rhs)
{
	_real = std::move(rhs._real);
	rhs._real = nullptr;
	_imag = std::move(rhs._imag);
	rhs._imag = nullptr;
	
	return *this;
}

BigComplexInteger & BigComplexInteger::operator+=(const BigComplexInteger & rhs)
{
	*_real += *rhs._real;
	*_imag += *rhs._imag;

	return *this;
}

BigComplexInteger & BigComplexInteger::operator-=(const BigComplexInteger & rhs)
{
	*_real -= *rhs._real;
	*_imag -= *rhs._imag;

	return *this;
}

BigComplexInteger & BigComplexInteger::operator*=(const BigComplexInteger & rhs)
{
	auto realOut = ((*_real) * (*rhs._real)) - ((*_imag) * (*rhs._imag));
	auto imagOut = ((*_real) * (*rhs._imag)) + ((*_imag) * (*rhs._real));

	*_real = realOut;
	*_imag = imagOut;

	return *this;
}

BigComplexInteger & BigComplexInteger::operator/=(const BigComplexInteger & rhs)
{
	auto divisor = ((*rhs._real) * (*rhs._real)) + ((*rhs._imag) * (*rhs._imag));

	if (divisor == 0)
		throw std::invalid_argument("Division by 0");

	auto realOut = ((*_real) * (*rhs._real)) + ((*_imag) * (*rhs._imag));
	auto imagOut = ((*_imag) * (*rhs._real)) - ((*_real) * (*rhs._imag));

	*_real = (realOut / divisor);
	*_imag = (imagOut / divisor);

	return *this;
}

const BigInteger * BigComplexInteger::real() const
{
	return _real;
}

const BigInteger * BigComplexInteger::imag() const
{
	return _imag;
}

std::istream & operator >> (std::istream & is, BigComplexInteger & rhs)
{
	is >> *rhs._real;

	if (is.peek() != std::istream::traits_type::eof())
		is >> *rhs._imag;
	else
		*rhs._imag = BigInteger();

	return is;
}

std::ostream & operator<<(std::ostream & os, const BigComplexInteger & rhs)
{
	os << *rhs._real << " " << *rhs._imag;

	return os;
}

BigComplexInteger operator+(BigComplexInteger lhs, const BigComplexInteger & rhs)
{
	lhs += rhs;
	return lhs;
}

BigComplexInteger operator-(BigComplexInteger lhs, const BigComplexInteger & rhs)
{
	lhs -= rhs;
	return lhs;
}

BigComplexInteger operator*(BigComplexInteger lhs, const BigComplexInteger & rhs)
{
	lhs *= rhs;
	return lhs;
}

BigComplexInteger operator/(BigComplexInteger lhs, const BigComplexInteger & rhs)
{
	lhs /= rhs;
	return lhs;
}

bool operator<(const BigComplexInteger & lhs, const BigComplexInteger & rhs)
{
	if (*lhs._imag != 0 && *rhs._imag != 0)
		throw std::invalid_argument("Undefined operation");

	return (*lhs._real < *rhs._real);
}

bool operator>(const BigComplexInteger & lhs, const BigComplexInteger & rhs)
{
	if (*lhs._imag != 0 && *rhs._imag != 0)
		throw std::invalid_argument("Undefined operation");

	return *lhs._real > *rhs._real;
}

bool operator<=(const BigComplexInteger & lhs, const BigComplexInteger & rhs)
{
	if (*lhs._imag != 0 && *rhs._imag != 0)
		throw std::invalid_argument("Undefined operation");

	return *lhs._real <= *rhs._real;
}

bool operator>=(const BigComplexInteger & lhs, const BigComplexInteger & rhs)
{
	if (*lhs._imag != 0 && *rhs._imag != 0)
		throw std::invalid_argument("Undefined operation");

	return *lhs._real >= *rhs._real;
}

bool operator==(const BigComplexInteger & lhs, const BigComplexInteger & rhs)
{
	if (*lhs._imag != 0 && *rhs._imag != 0)
		return (*lhs._real == *rhs._real) && (*lhs._imag == *rhs._imag);

	return (*lhs._real == *rhs._real);
}

bool operator!=(const BigComplexInteger & lhs, const BigComplexInteger & rhs)
{
	return !(lhs == rhs);
}

