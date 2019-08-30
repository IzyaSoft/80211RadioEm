#ifndef PHY_CONVERTORS_TESTCONSTELLATIONMAPPER_H_
#define PHY_CONVERTORS_TESTCONSTELLATIONMAPPER_H_

#include <vector>
#include <memory>
#include <math.h>
#include "gtest/gtest.h"
#include "SymbolsCheck.h"
#include "ConstellationMapper.h"


namespace TestRadio80211ah
{
    double defaultPrecision = 0.0001;
    double qpskKmod = 1 / sqrt(2);
    double qam16Kmod = 1 / sqrt(10);
    std::vector<Radio80211ah::octet> knownBinSequence = {2, 9, 0x3A, 0x4D}; // 0b00000011 0b00001001 0b00111010 0b01001101

    void TestDirectConversion(Radio80211ah::ConstellationType constellationType, std::vector<std::complex<double>> expected)
    {
        std::shared_ptr<Radio80211ah::IRadioConvertor> constellationMapper(new Radio80211ah::ConstellationMapper(constellationType));
        std::vector<std::complex<double>> actual = constellationMapper->DirectConvert(knownBinSequence);
        CheckSymbolSequences(expected, actual, defaultPrecision);
        constellationMapper.reset();
    }

    void TestReverseConversion(Radio80211ah::ConstellationType constellationType, std::vector<std::complex<double>> sequence)
    {
        std::shared_ptr<Radio80211ah::IRadioConvertor> constellationMapper(new Radio80211ah::ConstellationMapper(constellationType));
        std::vector<Radio80211ah::octet> actual = constellationMapper->ReverseConvert(sequence);
        CheckBinarySequences(knownBinSequence, actual);
        constellationMapper.reset();
    }

    TEST(ConstellationMapper, MapBinToBpsk)
    {
        std::vector<std::complex<double>> expected =
        {
            // 2
            std::complex<double>(-1, 0), std::complex<double>(1, 0), std::complex<double>(-1, 0), std::complex<double>(-1, 0),
            std::complex<double>(-1, 0), std::complex<double>(-1, 0), std::complex<double>(-1, 0), std::complex<double>(-1, 0),
            // 9
            std::complex<double>(1, 0), std::complex<double>(-1, 0), std::complex<double>(-1, 0), std::complex<double>(1, 0),
            std::complex<double>(-1, 0), std::complex<double>(-1, 0), std::complex<double>(-1, 0), std::complex<double>(-1, 0),
            // 0x3A
            std::complex<double>(-1, 0), std::complex<double>(1, 0), std::complex<double>(-1, 0), std::complex<double>(1, 0),
            std::complex<double>(1, 0), std::complex<double>(1, 0), std::complex<double>(-1, 0), std::complex<double>(-1, 0),
            // 0x4D
            std::complex<double>(1, 0), std::complex<double>(-1, 0), std::complex<double>(1, 0), std::complex<double>(1, 0),
            std::complex<double>(-1, 0), std::complex<double>(-1, 0), std::complex<double>(1, 0), std::complex<double>(-1, 0)
        };
        TestDirectConversion(Radio80211ah::ConstellationType::BPSK, expected);
    }

    TEST(ConstellationMapper, MapBinToQpsk)
    {
        std::vector<std::complex<double>> expected =
        {
            // 2
            std::complex<double>(1 * qpskKmod, 1 * qpskKmod), std::complex<double>(-1 * qpskKmod, -1 * qpskKmod),
            std::complex<double>(-1 * qpskKmod, -1 * qpskKmod), std::complex<double>(-1 * qpskKmod, -1 * qpskKmod),
            // 9
            std::complex<double>(1 * qpskKmod, -1 * qpskKmod), std::complex<double>(1 * qpskKmod, 1 * qpskKmod),
            std::complex<double>(-1 * qpskKmod, -1 * qpskKmod), std::complex<double>(-1 * qpskKmod, -1 * qpskKmod),
            // 0x3A
            std::complex<double>(1 * qpskKmod, 1 * qpskKmod), std::complex<double>(1 * qpskKmod, 1 * qpskKmod),
            std::complex<double>(-1 * qpskKmod, 1 * qpskKmod), std::complex<double>(-1 * qpskKmod, -1 * qpskKmod),
            // 0x4D
            std::complex<double>(1 * qpskKmod, -1 * qpskKmod), std::complex<double>(-1 * qpskKmod, 1 * qpskKmod),
            std::complex<double>(-1 * qpskKmod, -1 * qpskKmod), std::complex<double>(1 * qpskKmod, -1 * qpskKmod)
        };
        TestDirectConversion(Radio80211ah::ConstellationType::QPSK, expected);
    }

    TEST(ConstellationMapper, MapBinToQam16)
    {
        std::vector<std::complex<double>> expected =
        {
            // 2
            std::complex<double>(1 * qam16Kmod, -3 * qam16Kmod), std::complex<double>(-3 * qam16Kmod, -3 * qam16Kmod),
            // 9
            std::complex<double>(3 * qam16Kmod, 1 * qam16Kmod), std::complex<double>(-3 * qam16Kmod, -3 * qam16Kmod),
            // 0x3A
            std::complex<double>(1 * qam16Kmod, 1 * qam16Kmod), std::complex<double>(-1 * qam16Kmod, -3 * qam16Kmod),
            // 0x4D
            std::complex<double>(1 * qam16Kmod, -1 * qam16Kmod), std::complex<double>(-1 * qam16Kmod, 3 * qam16Kmod)
        };
        TestDirectConversion(Radio80211ah::ConstellationType::QAM16, expected);
    }

    TEST(ConstellationMapper, MapExactBpskToBin)
    {
        std::vector<std::complex<double>> mappedKnownSequence =
        {
            // 2
            std::complex<double>(-1, 0), std::complex<double>(1, 0), std::complex<double>(-1, 0), std::complex<double>(-1, 0),
            std::complex<double>(-1, 0), std::complex<double>(-1, 0), std::complex<double>(-1, 0), std::complex<double>(-1, 0),
            // 9
            std::complex<double>(1, 0), std::complex<double>(-1, 0), std::complex<double>(-1, 0), std::complex<double>(1, 0),
            std::complex<double>(-1, 0), std::complex<double>(-1, 0), std::complex<double>(-1, 0), std::complex<double>(-1, 0),
            // 0x3A
            std::complex<double>(-1, 0), std::complex<double>(1, 0), std::complex<double>(-1, 0), std::complex<double>(1, 0),
            std::complex<double>(1, 0), std::complex<double>(1, 0), std::complex<double>(-1, 0), std::complex<double>(-1, 0),
            // 0x4D
            std::complex<double>(1, 0), std::complex<double>(-1, 0), std::complex<double>(1, 0), std::complex<double>(1, 0),
            std::complex<double>(-1, 0), std::complex<double>(-1, 0), std::complex<double>(1, 0), std::complex<double>(-1, 0)
        };
        TestReverseConversion(Radio80211ah::ConstellationType::BPSK, mappedKnownSequence);
    }

    TEST(ConstellationMapper, MapExactQpskToBin)
    {
        std::vector<std::complex<double>> mappedKnownSequence =
        {
            // 2
            std::complex<double>(1 * qpskKmod, 1 * qpskKmod), std::complex<double>(-1 * qpskKmod, -1 * qpskKmod),
            std::complex<double>(-1 * qpskKmod, -1 * qpskKmod), std::complex<double>(-1 * qpskKmod, -1 * qpskKmod),
            // 9
            std::complex<double>(1 * qpskKmod, -1 * qpskKmod), std::complex<double>(1 * qpskKmod, 1 * qpskKmod),
            std::complex<double>(-1 * qpskKmod, -1 * qpskKmod), std::complex<double>(-1 * qpskKmod, -1 * qpskKmod),
            // 0x3A
            std::complex<double>(1 * qpskKmod, 1 * qpskKmod), std::complex<double>(1 * qpskKmod, 1 * qpskKmod),
            std::complex<double>(-1 * qpskKmod, 1 * qpskKmod), std::complex<double>(-1 * qpskKmod, -1 * qpskKmod),
            // 0x4D
            std::complex<double>(1 * qpskKmod, -1 * qpskKmod), std::complex<double>(-1 * qpskKmod, 1 * qpskKmod),
            std::complex<double>(-1 * qpskKmod, -1 * qpskKmod), std::complex<double>(1 * qpskKmod, -1 * qpskKmod)
        };
        TestReverseConversion(Radio80211ah::ConstellationType::QPSK, mappedKnownSequence);
    }

    TEST(ConstellationMapper, MapExactQam16ToBin)
    {
        std::vector<std::complex<double>> mappedKnownSequence=
        {
            // 2
            std::complex<double>(1 * qam16Kmod, -3 * qam16Kmod), std::complex<double>(-3 * qam16Kmod, -3 * qam16Kmod),
            // 9
            std::complex<double>(3 * qam16Kmod, 1 * qam16Kmod), std::complex<double>(-3 * qam16Kmod, -3 * qam16Kmod),
            // 0x3A
            std::complex<double>(1 * qam16Kmod, 1 * qam16Kmod), std::complex<double>(-1 * qam16Kmod, -3 * qam16Kmod),
            // 0x4D
            std::complex<double>(1 * qam16Kmod, -1 * qam16Kmod), std::complex<double>(-1 * qam16Kmod, 3 * qam16Kmod)
        };
        TestReverseConversion(Radio80211ah::ConstellationType::QAM16, mappedKnownSequence);
    }

    TEST(ConstellationMapper, MapNearestBpskToBin)
    {
        std::vector<std::complex<double>> mappedKnownSequence =
        {
            // 2
            std::complex<double>(-1.1, 0), std::complex<double>(1, 0.1), std::complex<double>(-1, 0), std::complex<double>(-1, 0),
            std::complex<double>(-1.2, 0), std::complex<double>(-1, 0), std::complex<double>(-1, 0.1), std::complex<double>(-1, 0),
            // 9
            std::complex<double>(1, 0), std::complex<double>(-1, 0), std::complex<double>(-1.3, 0), std::complex<double>(1, 0),
            std::complex<double>(-1, 0), std::complex<double>(-1, 0), std::complex<double>(-1, 0), std::complex<double>(-1, 0),
            // 0x3A
            std::complex<double>(-1, 0), std::complex<double>(1, 0), std::complex<double>(-1, 0), std::complex<double>(1, 0),
            std::complex<double>(1.5, 0), std::complex<double>(1.2, 0), std::complex<double>(-1, 0), std::complex<double>(-1, 0),
            // 0x4D
            std::complex<double>(1, 0), std::complex<double>(-1, 0), std::complex<double>(1.4, 0), std::complex<double>(1, 0),
            std::complex<double>(-1, 0), std::complex<double>(-1, 0), std::complex<double>(1, 0), std::complex<double>(-1, 0)
        };
        TestReverseConversion(Radio80211ah::ConstellationType::BPSK, mappedKnownSequence);
    }

    TEST(ConstellationMapper, MapNearestQpskToBin)
    {
        std::vector<std::complex<double>> mappedKnownSequence =
        {
            // 2
            std::complex<double>(1.3 * qpskKmod, 1 * qpskKmod), std::complex<double>(-1 * qpskKmod, -1 * qpskKmod),
            std::complex<double>(-1 * qpskKmod, -1 * qpskKmod), std::complex<double>(-1.5 * qpskKmod, -1.7 * qpskKmod),
            // 9.7
            std::complex<double>(1 * qpskKmod, -1 * qpskKmod), std::complex<double>(1.2 * qpskKmod, 1.1 * qpskKmod),
            std::complex<double>(-1 * qpskKmod, -1 * qpskKmod), std::complex<double>(-1 * qpskKmod, -1 * qpskKmod),
            // 0x3A
            std::complex<double>(1.9 * qpskKmod, 1.2 * qpskKmod), std::complex<double>(1 * qpskKmod, 1 * qpskKmod),
            std::complex<double>(-1 * qpskKmod, 1 * qpskKmod), std::complex<double>(-1.9 * qpskKmod, -1.9 * qpskKmod),
            // 0x4D
            std::complex<double>(1 * qpskKmod, -1 * qpskKmod), std::complex<double>(-1 * qpskKmod, 1 * qpskKmod),
            std::complex<double>(-1 * qpskKmod, -1 * qpskKmod), std::complex<double>(1 * qpskKmod, -1 * qpskKmod)
        };
        TestReverseConversion(Radio80211ah::ConstellationType::QPSK, mappedKnownSequence);
    }

    TEST(ConstellationMapper, MapNearestQam16ToBin)
    {
        std::vector<std::complex<double>> mappedKnownSequence=
        {
            // 2
            std::complex<double>(1.4 * qam16Kmod, -3.3 * qam16Kmod), std::complex<double>(-3.5 * qam16Kmod, -2.7 * qam16Kmod),
            // 9
            std::complex<double>(3 * qam16Kmod, 1 * qam16Kmod), std::complex<double>(-3.9 * qam16Kmod, -3.1 * qam16Kmod),
            // 0x3A
            std::complex<double>(1.5 * qam16Kmod, 1.1 * qam16Kmod), std::complex<double>(-1 * qam16Kmod, -3 * qam16Kmod),
            // 0x4D
            std::complex<double>(1.4 * qam16Kmod, -1.4 * qam16Kmod), std::complex<double>(-1 * qam16Kmod, 3 * qam16Kmod)
        };
        TestReverseConversion(Radio80211ah::ConstellationType::QAM16, mappedKnownSequence);
    }
}

#endif /* PHY_CONVERTORS_TESTCONSTELLATIONMAPPER_H_ */
