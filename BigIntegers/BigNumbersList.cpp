#include "BigNumbersListElement.h"
#include "BigInteger.h"

void BigNumbersList::push_at(const int & pos, BigNumber * bigNumber)
{
	if (pos <= 0) {
		push_front(bigNumber);
		return;
	}

	if (first == last){
		push_back(bigNumber);
		return;
	}

	Element* curr = first->next;
	int counter = 1;

	while (counter != pos && curr != last)
	{
		counter++;
		curr = curr->next;
	}

	if (counter < pos) {
		push_back(bigNumber);
		return;
	}

	Element* next = curr;
	Element* prev = curr->prev;

	Element* e = new Element;
	e->number = bigNumber;

	e->prev = prev;
	prev->next = e;

	e->next = next;
	next->prev = e;
}

void BigNumbersList::pop_front()
{
	if (first == nullptr)
		throw std::runtime_error("List is empty");

	Element* e = first;

	first = first->next;

	delete e;
}

void BigNumbersList::pop_back()
{
	if (last == nullptr)
		throw std::runtime_error("List is empty");

	Element* e = last;

	last = last->prev;

	delete e;
}

void BigNumbersList::pop_at(const int & pos)
{
	if (pos <= 0) 
	{
		pop_front();
		return;
	}

	int counter = 1;
	Element* curr = first->next;

	while (counter != pos && curr != last)
	{
		counter++;
		curr = curr->next;
	}

	if (curr == last) {
		pop_back();
		return;
	}

	Element* prev = curr->prev;
	Element* next = curr->next;

	prev->next = next;
	next->prev = prev;

	delete curr;
}

const BigNumber * BigNumbersList::front()
{
	if (first == nullptr)
		throw std::invalid_argument("List is empty");

	return first->number;
}

const BigNumber * BigNumbersList::at(const size_t & pos)
{
	if (pos == 0)
		return front();

	Element* curr = first->next;
	int counter = 1;

	while (pos != counter && curr != last)
	{
		curr = curr->next;
		counter++;
	}

	if (curr != last)
		return curr->number;

	if (curr == last && pos != counter)
		throw std::invalid_argument("Invalid access");

	return back();
}

const BigNumber * BigNumbersList::back()
{
	if (last == nullptr)
		throw std::invalid_argument("List is empty");

	return last->number;
}

void BigNumbersList::clear()
{
	while (first != last)
		pop_back();

	delete first;

	first = last = nullptr;
}

void BigNumbersList::sort()
{
	if (first == last)
		return;

	Element* end = last;

	while (end != first)
	{
		Element* largest = first;
		Element* iter = first->next;

		while (iter != end->next)
		{
			if (compare(iter->number, largest->number))
				largest = iter;

			iter = iter->next;
		}

		if (largest != end) 
		{
			BigNumber* tmp = end->number;
			end->number = largest->number;
			largest->number = tmp;
		}

		end = end->prev;
	}
}

bool BigNumbersList::compare(const BigNumber * lhs, const BigNumber * rhs)
{
	return BigInteger(lhs->value().c_str()) > BigInteger(rhs->value().c_str());
}

BigNumbersList::BigNumbersList() : 
	first(nullptr),
	last(nullptr)
{
}

BigNumbersList::~BigNumbersList()
{
	clear();
}

void BigNumbersList::push_front(BigNumber * bigNumber)
{
	Element* e = new Element;

	e->number = bigNumber;
	e->prev = nullptr;
	e->next = first;

	if (last == first) 
	{
		if (last == nullptr)
			last = e;
		else
			last->prev = e;
	}

	first = e;

	if(e->next != nullptr)
		e->next->prev = first;
}

void BigNumbersList::push_back(BigNumber * bigNumber)
{
	Element* e = new Element;

	e->number = bigNumber;
	e->next = nullptr;
	e->prev = last;

	if (first == last)
	{
		if (first == nullptr)
			first = e;
		else
			first->next = e;
	}
	
	last = e;

	if(e->prev != nullptr)
		e->prev->next = last;
}

std::ostream & operator<<(std::ostream & os, const BigNumbersList & rhs)
{
	BigNumbersList::Element* curr = rhs.first;

	do 
	{
		if (curr == nullptr)
			return os;

		os << curr->number->value();

		curr = curr->next;

		if (curr != nullptr)
			os << ", ";

	} while (true);

	return os;
}
