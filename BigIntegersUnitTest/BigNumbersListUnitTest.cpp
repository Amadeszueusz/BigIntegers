#include "stdafx.h"
#include "CppUnitTest.h"
#include <complex>
#include "BigNumbersList.h"
#include "BigInteger.h"
#include "BigComplexInteger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BigNumbersListUnitTest
{
	TEST_CLASS(BigNumbersListUnitTest)
	{
	public:
		TEST_METHOD(BigNumbersListPushFrontTest)
		{
			BigNumbersList list;

			list.push_front(new BigInteger("10"));
			Assert::AreEqual(std::string("10"), list.front()->value());

			list.push_front(new BigInteger("3891"));
			Assert::AreEqual(std::string("3891"), list.front()->value());
		}

		TEST_METHOD(BigNumbersListPushBackTest)
		{
			BigNumbersList list;

			list.push_back(new BigInteger("10"));
			Assert::AreEqual(std::string("10"), list.back()->value());

			list.push_back(new BigInteger("3891"));
			Assert::AreEqual(std::string("3891"), list.back()->value());

			list.push_back(new BigInteger("89391"));
			Assert::AreEqual(std::string("89391"), list.back()->value());
		}

		TEST_METHOD(BigNumbersListPushAtTest)
		{
			BigNumbersList list;

			list.push_at(-10, new BigInteger("10"));
			Assert::AreEqual(std::string("10"), list.front()->value());

			list.push_at(0, new BigInteger("321"));
			Assert::AreEqual(std::string("321"), list.at(0)->value());

			list.push_at(423, new BigInteger("43"));
			Assert::AreEqual(std::string("43"), list.back()->value());

		}

		TEST_METHOD(BigNumbersListPopFrontTest)
		{
			BigNumbersList list;
			list.push_front(new BigInteger("10"));
			list.push_front(new BigInteger("8129"));
			list.push_front(new BigInteger("-291"));

			list.pop_front();
			Assert::AreEqual(std::string("8129"), list.front()->value());
			list.pop_front();
			Assert::AreEqual(std::string("10"), list.front()->value());
		}

		TEST_METHOD(BigNumbersListPopBackTest)
		{
			BigNumbersList list;
			list.push_back(new BigInteger("10"));
			list.push_back(new BigInteger("8129"));
			list.push_back(new BigInteger("-291"));

			list.pop_back();
			Assert::AreEqual(std::string("8129"), list.back()->value());
			list.pop_back();
			Assert::AreEqual(std::string("10"), list.back()->value());
		}

		TEST_METHOD(BigNumbersListPopAtTest)
		{
			BigNumbersList list;
			list.push_back(new BigInteger("10"));
			list.push_back(new BigInteger("8129"));
			list.push_back(new BigInteger("-291"));

			list.pop_at(0);
			Assert::AreEqual(std::string("8129"), list.front()->value());
			list.pop_at(1);
			Assert::AreEqual(std::string("8129"), list.back()->value());
		}

		TEST_METHOD(BigNumbersListClearTest)
		{
			BigNumbersList list;
			list.push_back(new BigInteger("10"));
			list.push_back(new BigInteger("8129"));
			list.push_back(new BigInteger("-291"));
			list.push_front(new BigInteger("-321"));
			list.push_front(new BigInteger("-53245234"));

			list.clear();

			Assert::ExpectException<std::invalid_argument>([&]() { list.front(); });
			Assert::ExpectException<std::invalid_argument>([&]() { list.back(); });
		}

		TEST_METHOD(BigNumbersListOutputOperatorTest)
		{
			BigNumbersList list;
			list.push_back(new BigInteger("10"));
			list.push_back(new BigComplexInteger("8129"));
			list.push_front(new BigInteger("-291"));
			std::stringstream sstream;
			sstream << list;
			std::string out;
			std::getline(sstream, out);

			Assert::AreEqual(std::string("-291, 10, 8129"), out);
		}

		TEST_METHOD(BigNumbersListSortTest)
		{
			BigNumbersList list;
			list.push_back(new BigInteger("212"));
			list.push_back(new BigInteger("8129"));
			list.push_back(new BigInteger("-21"));
			list.push_back(new BigInteger("737718"));
			list.push_back(new BigInteger("493"));

			list.sort();

			std::stringstream sstream;
			sstream << list;
			std::string out;
			std::getline(sstream, out);

			Assert::AreEqual(std::string("-21, 212, 493, 8129, 737718"), out);
		}
	};
}