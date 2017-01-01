#pragma once
#include "BigNumber.h"

class BigNumbersList
{
public:
	BigNumbersList();
	~BigNumbersList();

public:
	void push_front(BigNumber* bigNumber);
	void push_back(BigNumber* bigNumber);

	// Function will add element (bigNumber) at given position (pos).
	// If pos is greater than current size of the list function will act as push_back
	// If pos is negative function will act as push_front
	void push_at(const int& pos, BigNumber* bigNumber);

public:
	void pop_front();
	void pop_back();

	// Function will remove element at given position (pos).
	// If pos is greater than current size of the list function will act as pop_back
	// If pos is negative function will act as pop_front
	void pop_at(const int& pos);

public:
	const BigNumber* front();
	const BigNumber* at(const size_t& pos);
	const BigNumber* back();

public:
	void clear();

public:
	// function will sort list in ascending order
	void sort();

public:
	friend std::ostream& operator<<(std::ostream& os, const BigNumbersList& rhs);

private:
	// function returns true if lhs is greater than rhs and false otherwise
	static bool compare(const BigNumber* lhs, const BigNumber* rhs);

private:
	class Element;

private:
	Element* first;
	Element* last;
};