#pragma once
#include "BigInteger.h"

class BigComplexInteger : public BigNumber
{
public:
	BigComplexInteger();
	BigComplexInteger(const int& real);
	BigComplexInteger(const int& real, const int& imag);
	BigComplexInteger(const char* real);
	BigComplexInteger(const char* real, const char* imag);
	BigComplexInteger(const BigComplexInteger& other);
	BigComplexInteger(BigComplexInteger&& other);

	~BigComplexInteger();

public:
	std::string value() const override;

public:
	BigComplexInteger& operator=(const BigComplexInteger& rhs);
	BigComplexInteger& operator=(BigComplexInteger&& rhs);

public:
	friend std::istream& operator >> (std::istream& is, BigComplexInteger& rhs);
	friend std::ostream& operator<<(std::ostream& os, const BigComplexInteger& rhs);

public:
	BigComplexInteger& operator+=(const BigComplexInteger& rhs);
	BigComplexInteger& operator-=(const BigComplexInteger& rhs);
	friend BigComplexInteger operator+(BigComplexInteger lhs, const BigComplexInteger& rhs);
	friend BigComplexInteger operator-(BigComplexInteger lhs, const BigComplexInteger& rhs);

public:
	BigComplexInteger& operator*=(const BigComplexInteger& rhs);
	friend BigComplexInteger operator*(BigComplexInteger lhs, const BigComplexInteger& rhs);
	BigComplexInteger& operator/=(const BigComplexInteger& rhs);
	friend BigComplexInteger operator/(BigComplexInteger lhs, const BigComplexInteger& rhs);

public:
	friend bool operator< (const BigComplexInteger& lhs, const BigComplexInteger& rhs);
	friend bool operator> (const BigComplexInteger& lhs, const BigComplexInteger& rhs);
	friend bool operator<=(const BigComplexInteger& lhs, const BigComplexInteger& rhs);
	friend bool operator>=(const BigComplexInteger& lhs, const BigComplexInteger& rhs);
	friend bool operator==(const BigComplexInteger& lhs, const BigComplexInteger& rhs);
	friend bool operator!=(const BigComplexInteger& lhs, const BigComplexInteger& rhs);

public:
	const BigInteger* real() const;
	const BigInteger* imag() const;

private:
	BigInteger* _real;
	BigInteger* _imag;
};