#include "stdafx.h"
#include "CppUnitTest.h"
#include <complex>
#include "BigComplexInteger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BigComplexIntegersUnitTest
{
	TEST_CLASS(BigComplexIntegerUnitTest)
	{
	public:
		TEST_METHOD(BigComplexIntegerEmptyConstructorTest)
		{
			BigComplexInteger bigCpxInteger;
			Assert::AreEqual(std::string("0"), bigCpxInteger.real()->value());
			Assert::AreEqual(std::string("0"), bigCpxInteger.imag()->value());
		}

		TEST_METHOD(BigComplexIntegerIntegerConstructorTest)
		{
			const int real = -27819;
			BigComplexInteger bigCpxInteger(real);
			Assert::AreEqual(std::to_string(real), bigCpxInteger.real()->value());
			Assert::AreEqual(std::string("0"), bigCpxInteger.imag()->value());
		}

		TEST_METHOD(BigComplexIntegerComplexIntegerConstructorTest)
		{
			const int real = -27819;
			const int imag = 749823;

			BigComplexInteger bigCpxInteger(real, imag);
			Assert::AreEqual(std::to_string(real), bigCpxInteger.real()->value());
			Assert::AreEqual(std::to_string(imag), bigCpxInteger.imag()->value());
		}

		TEST_METHOD(BigComplexIntegerStringConstructorTest)
		{
			const std::string real = "-27819";
			BigComplexInteger bigCpxInteger(real.c_str());
			Assert::AreEqual(real, bigCpxInteger.real()->value());
			Assert::AreEqual(std::string("0"), bigCpxInteger.imag()->value());
		}

		TEST_METHOD(BigComplexIntegerComplexStringConstructorTest)
		{
			const std::string real = "-27819";
			const std::string imag = "749823";

			BigComplexInteger bigCpxInteger(real.c_str(), imag.c_str());
			Assert::AreEqual(real, bigCpxInteger.real()->value());
			Assert::AreEqual(imag, bigCpxInteger.imag()->value());
		}

		TEST_METHOD(BigComplexIntegerCopyConstructorTest)
		{
			BigComplexInteger bigCpxInteger("84923", "379812");
			BigComplexInteger bigCpxIntegerOther(bigCpxInteger);

			Assert::AreEqual(bigCpxInteger.real()->value(), bigCpxIntegerOther.real()->value());
			Assert::AreEqual(bigCpxInteger.imag()->value(), bigCpxIntegerOther.imag()->value());
		}

		TEST_METHOD(BigComplexIntegerMoveConstructorTest)
		{
			BigComplexInteger bigCpxIntegerOther(BigComplexInteger("84923", "379812"));

			Assert::AreEqual(std::string("84923"), bigCpxIntegerOther.real()->value());
			Assert::AreEqual(std::string("379812"), bigCpxIntegerOther.imag()->value());
		}

		TEST_METHOD(BigComplexIntegerCopyAssignmentOperatorTest)
		{
			BigComplexInteger bigCpxInteger("84923", "379812");
			BigComplexInteger bigCpxIntegerOther = bigCpxInteger;

			Assert::AreEqual(bigCpxInteger.real()->value(), bigCpxIntegerOther.real()->value());
			Assert::AreEqual(bigCpxInteger.imag()->value(), bigCpxIntegerOther.imag()->value());
		}

		TEST_METHOD(BigComplexIntegerMoveAssignmentOperatorTest)
		{
			BigComplexInteger bigCpxIntegerOther = BigComplexInteger("84923", "379812");

			Assert::AreEqual(std::string("84923"), bigCpxIntegerOther.real()->value());
			Assert::AreEqual(std::string("379812"), bigCpxIntegerOther.imag()->value());
		}

		TEST_METHOD(BigComplexIntegerInputStreamTest)
		{
			Assert::ExpectException<std::invalid_argument>([]() {			
				BigComplexInteger bigCpxInteger;
				std::stringstream sstream;
				sstream << "";
				sstream >> bigCpxInteger;
			});

			{
				BigComplexInteger bigCpxInteger;
				std::stringstream sstream;
				sstream << "4820";
				sstream >> bigCpxInteger;

				Assert::AreEqual(std::string("4820"), bigCpxInteger.real()->value());
				Assert::AreEqual(std::string("0"), bigCpxInteger.imag()->value());
			}

			{
				BigComplexInteger bigCpxInteger;
				std::stringstream sstream;
				sstream << "378921 -2982";
				sstream >> bigCpxInteger;

				Assert::AreEqual(std::string("378921"), bigCpxInteger.real()->value());
				Assert::AreEqual(std::string("-2982"), bigCpxInteger.imag()->value());
			}
		}

		TEST_METHOD(BigComplexIntegerOutputStreamTest)
		{
			{
				BigComplexInteger bigCpxInteger(2782, 831);
				std::stringstream sstream;
				sstream << bigCpxInteger;
				std::string output;
				std::getline(sstream, output);

				Assert::AreEqual(std::string("2782 831"), output);
			}

			{
				BigComplexInteger bigCpxInteger(2782);
				std::stringstream sstream;
				sstream << bigCpxInteger;
				std::string output;
				std::getline(sstream, output);

				Assert::AreEqual(std::string("2782 0"), output);
			}
		}

		TEST_METHOD(BigComplexIntegerAdditionAssignmentOperatorTest)
		{
			int real = -100;
			int imag = 381;
			BigComplexInteger bigCpxInteger(real, imag);
			bigCpxInteger += 291;
			real += 291;
			Assert::AreEqual(std::to_string(real), bigCpxInteger.real()->value());
			Assert::AreEqual(std::to_string(imag), bigCpxInteger.imag()->value());

			bigCpxInteger += BigComplexInteger(21, 81);
			real += 21;
			imag += 81;
			Assert::AreEqual(std::to_string(real), bigCpxInteger.real()->value());
			Assert::AreEqual(std::to_string(imag), bigCpxInteger.imag()->value());

			bigCpxInteger += BigComplexInteger(0, 81);
			real += 0;
			imag += 81;
			Assert::AreEqual(std::to_string(real), bigCpxInteger.real()->value());
			Assert::AreEqual(std::to_string(imag), bigCpxInteger.imag()->value());
		}

		TEST_METHOD(BigComplexIntegerAdditionOperatorTest)
		{
			int real1 = 100, real2 = 8921;
			int imag1 = 381, imag2 = -9831;

			auto sum = BigComplexInteger(real1, imag1) + BigComplexInteger(real2, imag2);

			Assert::AreEqual(std::to_string(real1 + real2), sum.real()->value());
			Assert::AreEqual(std::to_string(imag1 + imag2), sum.imag()->value());
		}

		TEST_METHOD(BigComplexIntegerSubstractionAssignmentOperatorTest)
		{
			int real = -100;
			int imag = 381;
			BigComplexInteger bigCpxInteger(real, imag);
			bigCpxInteger -= 291;
			real -= 291;
			Assert::AreEqual(std::to_string(real), bigCpxInteger.real()->value());
			Assert::AreEqual(std::to_string(imag), bigCpxInteger.imag()->value());

			bigCpxInteger -= BigComplexInteger(21, 81);
			real -= 21;
			imag -= 81;
			Assert::AreEqual(std::to_string(real), bigCpxInteger.real()->value());
			Assert::AreEqual(std::to_string(imag), bigCpxInteger.imag()->value());

			bigCpxInteger -= BigComplexInteger(0, 81);
			real -= 0;
			imag -= 81;
			Assert::AreEqual(std::to_string(real), bigCpxInteger.real()->value());
			Assert::AreEqual(std::to_string(imag), bigCpxInteger.imag()->value());
		}

		TEST_METHOD(BigComplexIntegerSubstractionOperatorTest)
		{
			int real1 = 100, real2 = 8921;
			int imag1 = 381, imag2 = -9831;

			auto sum = BigComplexInteger(real1, imag1) - BigComplexInteger(real2, imag2);

			Assert::AreEqual(std::to_string(real1 - real2), sum.real()->value());
			Assert::AreEqual(std::to_string(imag1 - imag2), sum.imag()->value());
		}

		TEST_METHOD(BigComplexIntegerGreaterThanTest)
		{
			int value1 = 2931, value2 = 8829;

			Assert::AreEqual(true, BigComplexInteger(value2, 381) > value1);
			Assert::AreEqual(false, BigComplexInteger(-value2, 8731) > BigComplexInteger(value1));
			Assert::AreEqual(false, BigComplexInteger(-value2, -287981) > -value1);
			Assert::AreEqual(true, BigComplexInteger(value2, -3892) > BigComplexInteger(-value1));

			Assert::ExpectException<std::invalid_argument>([]() {
				BigComplexInteger(2891, -291) > BigComplexInteger(721, 772);
			});
		}

		TEST_METHOD(BigComplexIntegerLessThanTest)
		{
			int value1 = 2931, value2 = 8829;

			Assert::AreEqual(false, BigComplexInteger(value2, 381) < value1);
			Assert::AreEqual(true, BigComplexInteger(-value2, 8731) < BigComplexInteger(value1));
			Assert::AreEqual(true, BigComplexInteger(-value2, -287981) < -value1);
			Assert::AreEqual(false, BigComplexInteger(value2, -3892) < BigComplexInteger(-value1));

			Assert::ExpectException<std::invalid_argument>([]() {
				BigComplexInteger(2891, -291) < BigComplexInteger(721, 772);
			});
		}

		TEST_METHOD(BigComplexIntegerGreateEqualThanTest)
		{
			int value1 = 2931, value2 = 8829;

			Assert::AreEqual(true, BigComplexInteger(value2, 381) > value1);
			Assert::AreEqual(false, BigComplexInteger(-value2, 8731) > BigComplexInteger(value1));
			Assert::AreEqual(false, BigComplexInteger(-value2, -287981) > -value1);
			Assert::AreEqual(true, BigComplexInteger(value2, -3892) > BigComplexInteger(-value1));
			Assert::AreEqual(true, BigComplexInteger(value2, -3892) >= BigComplexInteger(value2));

			Assert::ExpectException<std::invalid_argument>([]() {
				BigComplexInteger(2891, -291) >= BigComplexInteger(721, 772);
			});
		}

		TEST_METHOD(BigComplexIntegerLessEqualThanTest)
		{
			int value1 = 2931, value2 = 8829;

			Assert::AreEqual(false, BigComplexInteger(value2, 381) <= value1);
			Assert::AreEqual(true, BigComplexInteger(-value2, 8731) <= BigComplexInteger(value1));
			Assert::AreEqual(true, BigComplexInteger(-value2, -287981) <= -value1);
			Assert::AreEqual(false, BigComplexInteger(value2, -3892) <= BigComplexInteger(-value1));
			Assert::AreEqual(true, BigComplexInteger(value2, -3892) <= BigComplexInteger(value2));

			Assert::ExpectException<std::invalid_argument>([]() {
				BigComplexInteger(2891, -291) <= BigComplexInteger(721, 772);
			});
		}

		TEST_METHOD(BigComplexIntegerEqualityTest)
		{
			Assert::AreEqual(true, BigComplexInteger(0, -287981) == BigComplexInteger(0, -287981));
			Assert::AreEqual(false, BigComplexInteger(2891, -772) == BigComplexInteger(2891, 772));
			Assert::AreEqual(true, BigComplexInteger(2891, 772) == BigComplexInteger(2891, 772));
			Assert::AreEqual(true ,BigComplexInteger(2891) == BigComplexInteger(2891, 772));
		}

		TEST_METHOD(BigComplexIntegerInequalityTest)
		{
			Assert::AreEqual(false, BigComplexInteger(0, -287981) != BigComplexInteger(0, -287981));
			Assert::AreEqual(true, BigComplexInteger(2891, -772) != BigComplexInteger(2891, 772));
			Assert::AreEqual(false, BigComplexInteger(2891, 772) != BigComplexInteger(2891, 772));
			Assert::AreEqual(false, BigComplexInteger(2891) != BigComplexInteger(2891, 772));
		}

		TEST_METHOD(BigComplexIntegerMultiplicationAssignmentOperatorTest)
		{
			std::complex<float> cpx(291,-821);
			BigComplexInteger bigCpxInteger(291, -821);

			cpx *= std::complex<float>(291, 731);
			bigCpxInteger *= BigComplexInteger(291, 731);

			Assert::AreEqual(std::to_string(static_cast<int>(cpx.real())), bigCpxInteger.real()->value());
			Assert::AreEqual(std::to_string(static_cast<int>(cpx.imag())), bigCpxInteger.imag()->value());
		}

		TEST_METHOD(BigComplexIntegerMultiplicationOperatorTest)
		{
			auto cpx = std::complex<float>(291, -821) * std::complex<float>(291, 731);
			auto bigCpxInteger = BigComplexInteger(291, -821) * BigComplexInteger(291, 731);

			Assert::AreEqual(std::to_string(static_cast<int>(cpx.real())), bigCpxInteger.real()->value());
			Assert::AreEqual(std::to_string(static_cast<int>(cpx.imag())), bigCpxInteger.imag()->value());
		}

		TEST_METHOD(BigComplexIntegerMultiplicationAssignmentDivisionOperatorTest)
		{
			std::complex<float> cpx(291, -821);
			BigComplexInteger bigCpxInteger(291, -821);

			cpx /= std::complex<float>(291, 731);
			bigCpxInteger /= BigComplexInteger(291, 731);

			Assert::AreEqual(std::to_string(static_cast<int>(cpx.real())), bigCpxInteger.real()->value());
			Assert::AreEqual(std::to_string(static_cast<int>(cpx.imag())), bigCpxInteger.imag()->value());
		}

		TEST_METHOD(BigComplexIntegerDivisionOperatorTest)
		{
			auto cpx = std::complex<float>(291, -821) / std::complex<float>(291, 731);
			auto bigCpxInteger = BigComplexInteger(291, -821) / BigComplexInteger(291, 731);

			Assert::AreEqual(std::to_string(static_cast<int>(cpx.real())), bigCpxInteger.real()->value());
			Assert::AreEqual(std::to_string(static_cast<int>(cpx.imag())), bigCpxInteger.imag()->value());
		}
		
	};
}