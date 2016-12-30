#pragma once
#include <string>

class BigInteger
{
public:
	BigInteger();
	BigInteger(const int& value);
	BigInteger(const char* value);
	BigInteger(const BigInteger& other);
	BigInteger(BigInteger&& other);

	~BigInteger();

public:
	std::string value() const;

public:
	BigInteger& operator=(const BigInteger& rhs);
	BigInteger& operator=(BigInteger&& rhs);

public:
	friend std::istream& operator>>(std::istream& is, BigInteger& rhs);
	friend std::ostream& operator<<(std::ostream& os, const BigInteger& rhs);

public:
	BigInteger& operator+=(const BigInteger& rhs);
	BigInteger& operator-=(const BigInteger& rhs);
	friend BigInteger operator+(BigInteger lhs, const BigInteger& rhs);
	friend BigInteger operator-(BigInteger lhs, const BigInteger& rhs);

public:
	friend bool operator< (const BigInteger& lhs, const BigInteger& rhs);
	friend bool operator> (const BigInteger& lhs, const BigInteger& rhs);
	friend bool operator<=(const BigInteger& lhs, const BigInteger& rhs);
	friend bool operator>=(const BigInteger& lhs, const BigInteger& rhs);
	friend bool operator==(const BigInteger& lhs, const BigInteger& rhs);
	friend bool operator!=(const BigInteger& lhs, const BigInteger& rhs);

public:
	BigInteger& operator*=(const BigInteger& rhs);
	friend BigInteger operator*(BigInteger lhs, const BigInteger& rhs);
	BigInteger& operator/=(const BigInteger& rhs);
	friend BigInteger operator/(BigInteger lhs, const BigInteger& rhs);

public:
	friend BigInteger operator-(const BigInteger& rhs);
	friend BigInteger abs(const BigInteger& rhs);

public:
	friend BigInteger operator!(BigInteger rhs);

private:
	friend BigInteger add(const BigInteger& lhs, const BigInteger& rhs);
	friend BigInteger substract(const BigInteger& lhs, const BigInteger& rhs);
	friend BigInteger multiply(const BigInteger& lhs, const BigInteger& rhs);
	friend BigInteger divide(BigInteger lhs, BigInteger rhs);

private:
	char* _value;
	size_t value_size;
	bool is_value_negative;
};