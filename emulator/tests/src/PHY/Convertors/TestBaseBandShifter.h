#ifndef PHY_CONVERTORS_TESTBASEBANDSHIFTER_H_
#define PHY_CONVERTORS_TESTBASEBANDSHIFTER_H_

#include <memory>
#include <string>
#include "gtest/gtest.h"
#include "SymbolsCheck.h"
#include "BaseBandShifter.h"


namespace TestRadio80211ah
{
    Radio80211ah::BaseBandShifter shifter;

    std::vector<std::complex<double>> knownSequence =
    {
        std::complex<double>(-16, -16), std::complex<double>(-15, -15),
        std::complex<double>(-14, -14), std::complex<double>(-13, -13),
        std::complex<double>(-12, -12), std::complex<double>(-11, -11),
        std::complex<double>(-10, -10), std::complex<double>(-9, -9),
        std::complex<double>(-8, -8), std::complex<double>(-7, -7),
        std::complex<double>(-6, -6), std::complex<double>(-5, -5),
        std::complex<double>(-4, -4), std::complex<double>(-3, -3),
        std::complex<double>(-2, -2), std::complex<double>(-1, -1),

        std::complex<double>(0, 0), std::complex<double>(1, 1),
        std::complex<double>(2, 2), std::complex<double>(3, 3),
        std::complex<double>(4, 4), std::complex<double>(5, 5),
        std::complex<double>(6, 6), std::complex<double>(7, 7),
        std::complex<double>(8, 8), std::complex<double>(9, 9),
        std::complex<double>(10, 10), std::complex<double>(11, 11),
        std::complex<double>(12, 12), std::complex<double>(13, 13),
        std::complex<double>(14, 14), std::complex<double>(15, 15)
    };

    std::vector<std::complex<double>> shiftedKnownSequence =
    {
        std::complex<double>(0, 0), std::complex<double>(1, 1),
        std::complex<double>(2, 2), std::complex<double>(3, 3),
        std::complex<double>(4, 4), std::complex<double>(5, 5),
        std::complex<double>(6, 6), std::complex<double>(7, 7),
        std::complex<double>(8, 8), std::complex<double>(9, 9),
        std::complex<double>(10, 10), std::complex<double>(11, 11),
        std::complex<double>(12, 12), std::complex<double>(13, 13),
        std::complex<double>(14, 14), std::complex<double>(15, 15),

        std::complex<double>(-16, -16), std::complex<double>(-15, -15),
        std::complex<double>(-14, -14), std::complex<double>(-13, -13),
        std::complex<double>(-12, -12), std::complex<double>(-11, -11),
        std::complex<double>(-10, -10), std::complex<double>(-9, -9),
        std::complex<double>(-8, -8), std::complex<double>(-7, -7),
        std::complex<double>(-6, -6), std::complex<double>(-5, -5),
        std::complex<double>(-4, -4), std::complex<double>(-3, -3),
        std::complex<double>(-2, -2), std::complex<double>(-1, -1)
    };

    TEST(BaseBandSequence, Shift)
    {
        std::vector<std::complex<double>> actual = shifter.Shift(knownSequence);
        CheckSymbolSequences(shiftedKnownSequence, actual, 0);
    }

    TEST(BaseBandSequence, Unshift)
    {
        std::vector<std::complex<double>> actual = shifter.Unshift(shiftedKnownSequence);
        CheckSymbolSequences(knownSequence, actual, 0);
    }
}

#endif /* PHY_CONVERTORS_TESTBASEBANDSHIFTER_H_ */
