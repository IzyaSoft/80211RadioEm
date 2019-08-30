#ifndef TESTUTILS_SYMBOLSCHECK_H_
#define TESTUTILS_SYMBOLSCHECK_H_

#include <vector>
#include <complex>
#include "gtest/gtest.h"

namespace TestRadio80211ah
{
    void CheckSymbolSequences(std::vector<std::complex<double>>& expected, std::vector<std::complex<double>>& actual, double precision)
    {
        ASSERT_EQ(expected.size(), actual.size());
        for (unsigned int symbolCounter = 0; symbolCounter < expected.size(); symbolCounter++)
        {
            ASSERT_LE(abs(expected[symbolCounter].real() - actual[symbolCounter].real()), precision);
            ASSERT_LE(abs(expected[symbolCounter].imag() - actual[symbolCounter].imag()), precision);
        }
    }

    void CheckBinarySequences(std::vector<Radio80211ah::octet> expected, std::vector<Radio80211ah::octet> actual)
    {
        ASSERT_EQ(expected.size(), actual.size());
        for (unsigned int octetCounter = 0; octetCounter < expected.size(); octetCounter++)
        {
            ASSERT_EQ(expected[octetCounter], actual[octetCounter]);
        }
    }
}

#endif /* TESTUTILS_SYMBOLSCHECK_H_ */
