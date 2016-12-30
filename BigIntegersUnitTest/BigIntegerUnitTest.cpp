#include "stdafx.h"
#include "CppUnitTest.h"

#include "BigInteger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BigIntegersUnitTest
{		
	TEST_CLASS(BigIntegerUnitTest)
	{
	public:
		
		TEST_METHOD(BigIntegerEmptyConstructorTest)
		{
			BigInteger bigInteger;
			Assert::AreEqual(std::string("0"), bigInteger.value());
		}

		TEST_METHOD(BigIntegerIntegerConstructorTest)
		{
			BigInteger bigIntegerNegative(-10);
			Assert::AreEqual(std::string("-10"), bigIntegerNegative.value());

			BigInteger bigIntegerPositive(1231);
			Assert::AreEqual(std::string("1231"), bigIntegerPositive.value());
		}

		TEST_METHOD(BigIntegerStringConstructorTest)
		{
			{
				auto func = [] {BigInteger bitInt(nullptr); };
				Assert::ExpectException<std::invalid_argument>(func);
			}

			{
				auto func = [] {BigInteger bitInt("-"); };
				Assert::ExpectException<std::invalid_argument>(func);
			}

			{
				auto func = [] {BigInteger bitInt("01"); };
				Assert::ExpectException<std::invalid_argument>(func);
			}

			{
				auto func = [] {BigInteger bitInt("0iusahco8hqbjsa"); };
				Assert::ExpectException<std::invalid_argument>(func);
			}

			{
				BigInteger bitInt("-09221");
				Assert::AreEqual(std::string("-09221"), bitInt.value());
			}

			{
				BigInteger bitInt("221");
				Assert::AreEqual(std::string("221"), bitInt.value());
			}
		}

		TEST_METHOD(BigIntegerCopyConstructorTest)
		{
			const std::string value = "-121";
			BigInteger bigInt(value.c_str());
			BigInteger otherBigInt(bigInt);
			Assert::AreEqual(bigInt.value(), otherBigInt.value());
			Assert::AreEqual(value, otherBigInt.value());
		}

		TEST_METHOD(BigIntegerMoveConstructorTest)
		{
			const std::string value = "12342";
			auto func = [value]() {return BigInteger(value.c_str()); };
			BigInteger bigInt(func());
			Assert::AreEqual(value, bigInt.value());
		}

		TEST_METHOD(BigIntegerCopyAssignmentOperatorTest)
		{
			const std::string value = "98174";
			BigInteger bigInt;
			BigInteger otherBigInt(value.c_str());
			bigInt = otherBigInt;
			Assert::AreEqual(value, bigInt.value());
		}

		TEST_METHOD(BigIntegerMoveAssignmentOperatorTest)
		{
			const std::string value = "98174";
			BigInteger bigInt;
			bigInt = BigInteger(value.c_str());
			Assert::AreEqual(value, bigInt.value());
		}

		TEST_METHOD(BigIntegerInputOperatorTest)
		{
			const std::string value = "88310";
			std::stringstream ss;
			ss << value;
			BigInteger bigInt;
			ss >> bigInt;
			Assert::AreEqual(value, bigInt.value());
		}

		TEST_METHOD(BigIntegerOutputOperatorTest)
		{
			const std::string value = "88310";
			BigInteger bigInt(value.c_str());
			std::stringstream ss;
			ss << bigInt;
			std::string str;
			ss >> str;
			Assert::AreEqual(value, str);
		}

		TEST_METHOD(BigIntegerAdditionAssignmentOperatorTest)
		{
			{
				const int initValue = 34312;
				const int value = 87812;
				BigInteger bigInt(initValue);
				bigInt += value;
				Assert::AreEqual(bigInt.value(), BigInteger(initValue + value).value());
			}

			{
				const int initValue = -34312;
				const int value = 87812;
				BigInteger bigInt(initValue);
				bigInt += value;
				Assert::AreEqual(bigInt.value(), BigInteger(initValue + value).value());
			}

			{
				const int initValue = 34312;
				const int value = -87812;
				BigInteger bigInt(initValue);
				bigInt += value;
				Assert::AreEqual(bigInt.value(), BigInteger(initValue + value).value());
			}

			{
				const int initValue = -34312;
				const int value = -87812;
				BigInteger bigInt(initValue);
				bigInt += value;
				Assert::AreEqual(bigInt.value(), BigInteger(initValue + value).value());
			}
		}

		TEST_METHOD(BigIntegerSubstractionAssignmentOperatorTest)
		{
			{
				const int initValue = 34312;
				const int value = 87812;
				BigInteger bigInt(initValue);
				bigInt -= value;
				Assert::AreEqual(bigInt.value(), BigInteger(initValue - value).value());
			}

			{
				const int initValue = -34312;
				const int value = 87812;
				BigInteger bigInt(initValue);
				bigInt -= value;
				Assert::AreEqual(bigInt.value(), BigInteger(initValue - value).value());
			}

			{
				const int initValue = 34312;
				const int value = -87812;
				BigInteger bigInt(initValue);
				bigInt -= value;
				Assert::AreEqual(bigInt.value(), BigInteger(initValue - value).value());
			}

			{
				const int initValue = -34312;
				const int value = -87812;
				BigInteger bigInt(initValue);
				bigInt -= value;
				Assert::AreEqual(bigInt.value(), BigInteger(initValue - value).value());
			}
		}

		TEST_METHOD(BigIntegerSubstractionOperatorTest)
		{
			int lValue = 8893, rValue = 78923;

			Assert::AreEqual(std::to_string(lValue - rValue), (BigInteger(lValue) - BigInteger(rValue)).value());
			Assert::AreEqual(std::to_string(lValue - rValue * (-1)), (BigInteger(lValue) - BigInteger(rValue* (-1))).value());
			Assert::AreEqual(std::to_string(lValue* (-1) - rValue * (-1)), (BigInteger(lValue* (-1)) - BigInteger(rValue* (-1))).value());
			Assert::AreEqual(std::to_string(lValue* (-1) - rValue), (BigInteger(lValue* (-1)) - BigInteger(rValue)).value());
		}

		TEST_METHOD(BigIntegerAdditionOperatorTest)
		{
			int lValue = 8893, rValue = 78923;

			Assert::AreEqual(std::to_string(lValue + rValue), (BigInteger(lValue) + BigInteger(rValue)).value());
			Assert::AreEqual(std::to_string(lValue + rValue * (-1)), (BigInteger(lValue) + BigInteger(rValue* (-1))).value());
			Assert::AreEqual(std::to_string(lValue* (-1) + rValue * (-1)), (BigInteger(lValue* (-1)) + BigInteger(rValue* (-1))).value());
			Assert::AreEqual(std::to_string(lValue* (-1) + rValue), (BigInteger(lValue* (-1)) + BigInteger(rValue)).value());
		}

		TEST_METHOD(BigIntegerAdditiveInversonTest)
		{
			int value = 8371;

			Assert::AreEqual(std::to_string(-value), (-BigInteger(value)).value());
			Assert::AreEqual(std::to_string(value), (-(-BigInteger(value))).value());
		}

		TEST_METHOD(BigIntegerGreaterThanTest)
		{
			int value1 = 2931, value2 = 8829;

			Assert::AreEqual(true, BigInteger(value2) > value1);
			Assert::AreEqual(false, BigInteger(-value2) > value1);
			Assert::AreEqual(false, BigInteger(-value2) > -value1);
			Assert::AreEqual(true, BigInteger(value2) > -value1);
		}

		TEST_METHOD(BigIntegerGreaterEqualThanTest)
		{
			int value1 = 2931, value2 = 8829;

			Assert::AreEqual(true, BigInteger(value2) >= value2);
			Assert::AreEqual(false, BigInteger(-value2) >= value1);
		}

		TEST_METHOD(BigIntegerLessThanTest)
		{
			int value1 = 2931, value2 = 8829;

			Assert::AreEqual(false, BigInteger(value2) < value1);
			Assert::AreEqual(true, BigInteger(-value2) < value1);
			Assert::AreEqual(true, BigInteger(-value2) < -value1);
			Assert::AreEqual(false, BigInteger(value2) < -value1);
		}

		TEST_METHOD(BigIntegerLessEqualThanTest)
		{
			int value1 = 2931, value2 = 8829;

			Assert::AreEqual(true, BigInteger(value2) <= value2);
			Assert::AreEqual(true, BigInteger(-value2) <= value1);
		}

		TEST_METHOD(BigIntegerEqualityTest)
		{
			int value1 = 2931, value2 = 8829;

			Assert::AreEqual(true, BigInteger(value2) == BigInteger(value2));
			Assert::AreEqual(false, BigInteger(value1) == BigInteger(value2));
			Assert::AreEqual(false, BigInteger(-value2) == BigInteger(value2));
		}

		TEST_METHOD(BigIntegerInequalityTest)
		{
			int value1 = 2931, value2 = 8829;

			Assert::AreEqual(false, BigInteger(value2) != BigInteger(value2));
			Assert::AreEqual(true, BigInteger(value1) != BigInteger(value2));
			Assert::AreEqual(true, BigInteger(-value2) != BigInteger(value2));
		}

		TEST_METHOD(BigIntegerDivisionAssignmentOperatorTest)
		{
			{
				const int initValue = 87812;
				const int value = 2442;
				BigInteger bigInt(initValue);
				bigInt /= value;
				Assert::AreEqual(bigInt.value(), BigInteger(initValue / value).value());
			}

			{
				const int initValue = 87812;
				const int value = 2442;
				BigInteger bigInt(initValue);
				bigInt /= value;
				Assert::AreEqual(bigInt.value(), BigInteger(initValue / value).value());
			}

			{
				const int initValue = 87812;
				const int value = 2442;
				BigInteger bigInt(initValue);
				bigInt /= value;
				Assert::AreEqual(bigInt.value(), BigInteger(initValue / value).value());
			}

			{
				const int initValue = 87812;
				const int value = 2442;
				BigInteger bigInt(initValue);
				bigInt /= value;
				Assert::AreEqual(bigInt.value(), BigInteger(initValue / value).value());
			}

			{
				const int initValue = 2442;
				const int value = 87812;
				BigInteger bigInt(initValue);
				bigInt /= value;
				Assert::AreEqual(bigInt.value(), BigInteger(initValue / value).value());
			}

			{
				Assert::ExpectException<std::invalid_argument>([]() {
					const int initValue = 2442;
					const int value = 0;
					BigInteger bigInt(initValue); 
					bigInt.operator/=(value);
				});
			}
		}

		TEST_METHOD(BigIntegerDivisionOperatorTest)
		{
			int lValue = 78923, rValue = 2442;

			Assert::AreEqual(std::to_string(lValue / rValue), (BigInteger(lValue) / BigInteger(rValue)).value());
			Assert::AreEqual(std::to_string(lValue / (rValue * (-1))), (BigInteger(lValue) / BigInteger(rValue* (-1))).value());
			Assert::AreEqual(std::to_string((lValue* (-1)) / (rValue * (-1))), (BigInteger(lValue* (-1)) / BigInteger(rValue* (-1))).value());
			Assert::AreEqual(std::to_string((lValue* (-1)) / rValue), (BigInteger(lValue* (-1)) / BigInteger(rValue)).value());
		}

		TEST_METHOD(BigIntegerMultiplicationAssignmentOperatorTest)
		{
			{
				const int initValue = 87812;
				const int value = 2442;
				BigInteger bigInt(initValue);
				bigInt *= value;
				Assert::AreEqual(bigInt.value(), BigInteger(initValue * value).value());
			}

			{
				const int initValue = 87812;
				const int value = 2442;
				BigInteger bigInt(initValue);
				bigInt *= value;
				Assert::AreEqual(bigInt.value(), BigInteger(initValue * value).value());
			}

			{
				const int initValue = 87812;
				const int value = 2442;
				BigInteger bigInt(initValue);
				bigInt *= value;
				Assert::AreEqual(bigInt.value(), BigInteger(initValue * value).value());
			}

			{
				const int initValue = 87812;
				const int value = 2442;
				BigInteger bigInt(initValue);
				bigInt *= value;
				Assert::AreEqual(bigInt.value(), BigInteger(initValue * value).value());
			}

			{
				const int initValue = 87812;
				const int value = 0;
				BigInteger bigInt(initValue);
				bigInt *= value;
				Assert::AreEqual(bigInt.value(), BigInteger(initValue * value).value());
			}
		}

		TEST_METHOD(BigIntegerMultiplicationTest)
		{
			int lValue = 923, rValue = 2442;

			Assert::AreEqual(std::to_string(lValue * rValue), (BigInteger(lValue) * BigInteger(rValue)).value());
			Assert::AreEqual(std::to_string(lValue * (rValue * (-1))), (BigInteger(lValue) * BigInteger(rValue* (-1))).value());
			Assert::AreEqual(std::to_string((lValue* (-1)) * (rValue * (-1))), (BigInteger(lValue* (-1)) * BigInteger(rValue* (-1))).value());
			Assert::AreEqual(std::to_string((lValue* (-1)) * rValue), (BigInteger(lValue* (-1)) * BigInteger(rValue)).value());
		}

		TEST_METHOD(BigIntegerAbsoluteValueTest)
		{
			int value = 231;

			Assert::AreEqual(std::to_string(abs(value)), abs(BigInteger(value)).value());
			Assert::AreEqual(std::to_string(abs(-value)), abs(BigInteger(-value)).value());
		}

		TEST_METHOD(BigIntegerFactorialTest)
		{
			auto factorial_f = [](int val) {
				if (val == 1 || val == 0)
					return val;

				int product = val;

				while (val > 1) {
					val -= 1;
					product *= val;
				}

				return product;
			};

			int factorial = 7;

			Assert::AreEqual(std::to_string(factorial_f(factorial)), (!BigInteger(factorial)).value());
			Assert::ExpectException<std::invalid_argument>([factorial]() {!BigInteger(-factorial); });
		}
	};
}