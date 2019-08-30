#ifndef PHY_CONVERTORS_TESTDATACOMPOSER_H_
#define PHY_CONVERTORS_TESTDATACOMPOSER_H_

#include <memory>
#include <string>
#include "gtest/gtest.h"
#include "SymbolsCheck.h"
#include "DataComposer.h"


namespace TestRadio80211ah
{
    std::vector<std::complex<double>> emptyData;
    Radio80211ah::StfSymbol stf;
    Radio80211ah::LtfSymbol ltf;

    void TestComposeImplAndCheck(std::vector<std::complex<double>>& data, std::vector<std::complex<double>>& expected,
                                 bool useStf = true, bool useLtf = true, int dataSubcarriier = 1000)
    {
        std::shared_ptr<Radio80211ah::DataComposer> dataComposer = std::shared_ptr<Radio80211ah::DataComposer>(new Radio80211ah::DataComposer);
        std::vector<std::complex<double>> actual = dataComposer->Compose(data, useStf, useLtf, dataSubcarriier);
        CheckSymbolSequences(expected, actual, 0);
        dataComposer.reset();
    }

    void TestDecomposeImplAndCheck(std::vector<std::complex<double>>& data, std::vector<std::complex<double>>& expected)
    {
        std::shared_ptr<Radio80211ah::DataComposer> dataComposer = std::shared_ptr<Radio80211ah::DataComposer>(new Radio80211ah::DataComposer);
        std::vector<std::complex<double>> actual = dataComposer->Decompose(data);
        CheckSymbolSequences(expected, actual, 0);
        dataComposer.reset();
    }

    TEST(DataComposer, ComposeStfOnly)
    {
        std::vector<std::complex<double>> expected = stf.GetStf();
        TestComposeImplAndCheck(emptyData, expected, true, false);
    }

    TEST(DataComposer, ComposeStfAndLtfOnly)
    {
        std::vector<std::complex<double>> expected = stf.GetStf();
        std::vector<std::complex<double>> ltfData = ltf.GetLtf();
        expected.insert(expected.end(), ltfData.begin(), ltfData.end());
        TestComposeImplAndCheck(emptyData, expected, true, true);
    }

    TEST(DataComposer, ComposeStfLtfPlusDataLessThanOnePortion)
    {
        std::vector<std::complex<double>> data = {std::complex<double>(3, 3), std::complex<double>(4, 4), std::complex<double>(5, 5),
                                                  std::complex<double>(6, 6), std::complex<double>(7, 7)};
        std::vector<std::complex<double>> expected = stf.GetStf();
        std::vector<std::complex<double>> ltfData = ltf.GetLtf();
        expected.insert(expected.end(), ltfData.begin(), ltfData.end());
        for(int counter = 0; counter < 3; counter++)
            expected.push_back(std::complex<double>(0, 0));
        expected.insert(expected.end(), data.begin(), data.end());
        expected.push_back(std::complex<double>(0, 0));
        expected.push_back(std::complex<double>(1, 0));
        for(int counter = 0; counter < 13; counter++)
            expected.push_back(std::complex<double>(0, 0));
        expected.push_back(std::complex<double>(1, 0));
        for(int counter = 0; counter < 8; counter++)
            expected.push_back(std::complex<double>(0, 0));
        TestComposeImplAndCheck(data, expected);
    }

    TEST(DataComposer, ComposeStfLtfPlusExactOneDataPortion)
    {
        std::vector<std::complex<double>> data = {std::complex<double>(3, 3), std::complex<double>(4, 4), std::complex<double>(5, 5),
                                                  std::complex<double>(6, 6), std::complex<double>(7, 7), std::complex<double>(8, 8)};
        std::vector<std::complex<double>> expected = stf.GetStf();
        std::vector<std::complex<double>> ltfData = ltf.GetLtf();
        expected.insert(expected.end(), ltfData.begin(), ltfData.end());
        for(int counter = 0; counter < 3; counter++)
            expected.push_back(std::complex<double>(0, 0));
        expected.insert(expected.end(), data.begin(), data.end());
        expected.push_back(std::complex<double>(1, 0));
        for(int counter = 0; counter < 13; counter++)
            expected.push_back(std::complex<double>(0, 0));
        expected.push_back(std::complex<double>(1, 0));
        for(int counter = 0; counter < 8; counter++)
            expected.push_back(std::complex<double>(0, 0));
        TestComposeImplAndCheck(data, expected);
    }

    TEST(DataComposer, ComposeStfLtfPlusDataWithTwoJaggledDataPortions)
    {
        std::vector<std::complex<double>> dataPortion1 = {std::complex<double>(3, 3), std::complex<double>(4, 4), std::complex<double>(5, 5),
                                                          std::complex<double>(6, 6), std::complex<double>(7, 7), std::complex<double>(8, 8)};
        std::vector<std::complex<double>> dataPortion2 = {std::complex<double>(9, 9), std::complex<double>(10, 10)};
        std::vector<std::complex<double>> data;
        data.insert(data.end(), dataPortion1.begin(), dataPortion1.end());
        data.insert(data.end(), dataPortion2.begin(), dataPortion2.end());
        std::vector<std::complex<double>> expected = stf.GetStf();
        std::vector<std::complex<double>> ltfData = ltf.GetLtf();
        expected.insert(expected.end(), ltfData.begin(), ltfData.end());
        for(int counter = 0; counter < 3; counter++)
            expected.push_back(std::complex<double>(0, 0));
        expected.insert(expected.end(), dataPortion1.begin(), dataPortion1.end());
        expected.push_back(std::complex<double>(1, 0));
        expected.insert(expected.end(), dataPortion2.begin(), dataPortion2.end());
        for(int counter = 0; counter < 11; counter++)
            expected.push_back(std::complex<double>(0, 0));
        expected.push_back(std::complex<double>(1, 0));
        for(int counter = 0; counter < 8; counter++)
            expected.push_back(std::complex<double>(0, 0));
        TestComposeImplAndCheck(data, expected);
    }

    TEST(DataComposer, ComposeStfLtfPlusDataWithOneFullOfdmDataSymbol)
    {
        std::vector<std::complex<double>> dataPortion1 = {std::complex<double>(3, 3), std::complex<double>(4, 4), std::complex<double>(5, 5),
                                                          std::complex<double>(6, 6), std::complex<double>(7, 7), std::complex<double>(8, 8)};
        std::vector<std::complex<double>> dataPortion2 = {std::complex<double>(9, 9), std::complex<double>(10, 10), std::complex<double>(11, 11),
                                                          std::complex<double>(12, 12), std::complex<double>(13, 13), std::complex<double>(14, 14)};
        std::vector<std::complex<double>> dataPortion3 = {std::complex<double>(15, 15), std::complex<double>(16, 16), std::complex<double>(17, 17),
                                                          std::complex<double>(18, 18), std::complex<double>(19, 19), std::complex<double>(20, 20)};
        std::vector<std::complex<double>> dataPortion4 = {std::complex<double>(21, 21), std::complex<double>(22, 22), std::complex<double>(23, 23),
                                                          std::complex<double>(24, 24), std::complex<double>(25, 25), std::complex<double>(26, 26)};
        std::vector<std::complex<double>> data;
        data.insert(data.end(), dataPortion1.begin(), dataPortion1.end());
        data.insert(data.end(), dataPortion2.begin(), dataPortion2.end());
        data.insert(data.end(), dataPortion3.begin(), dataPortion3.end());
        data.insert(data.end(), dataPortion4.begin(), dataPortion4.end());
        std::vector<std::complex<double>> expected = stf.GetStf();
        std::vector<std::complex<double>> ltfData = ltf.GetLtf();
        expected.insert(expected.end(), ltfData.begin(), ltfData.end());
        for(int counter = 0; counter < 3; counter++)
            expected.push_back(std::complex<double>(0, 0));
        expected.insert(expected.end(), dataPortion1.begin(), dataPortion1.end());
        expected.push_back(std::complex<double>(1, 0));
        expected.insert(expected.end(), dataPortion2.begin(), dataPortion2.end());
        expected.push_back(std::complex<double>(0, 0));
        expected.insert(expected.end(), dataPortion3.begin(), dataPortion3.end());
        expected.push_back(std::complex<double>(1, 0));
        expected.insert(expected.end(), dataPortion4.begin(), dataPortion4.end());
        expected.push_back(std::complex<double>(0, 0));
        expected.push_back(std::complex<double>(0, 0));
        TestComposeImplAndCheck(data, expected);
    }

    TEST(DataComposer, ComposeStfLtfPlusDataWithTwoJaggledOfdmDataSymbols)
    {
        std::vector<std::complex<double>> dataPortion1 = {std::complex<double>(3, 3), std::complex<double>(4, 4), std::complex<double>(5, 5),
                                                          std::complex<double>(6, 6), std::complex<double>(7, 7), std::complex<double>(8, 8)};
        std::vector<std::complex<double>> dataPortion2 = {std::complex<double>(9, 9), std::complex<double>(10, 10), std::complex<double>(11, 11),
                                                          std::complex<double>(12, 12), std::complex<double>(13, 13), std::complex<double>(14, 14)};
        std::vector<std::complex<double>> dataPortion3 = {std::complex<double>(15, 15), std::complex<double>(16, 16), std::complex<double>(17, 17),
                                                          std::complex<double>(18, 18), std::complex<double>(19, 19), std::complex<double>(20, 20)};
        std::vector<std::complex<double>> dataPortion4 = {std::complex<double>(21, 21), std::complex<double>(22, 22), std::complex<double>(23, 23),
                                                          std::complex<double>(24, 24), std::complex<double>(25, 25), std::complex<double>(26, 26)};
        std::vector<std::complex<double>> dataPortion5 = {std::complex<double>(27, 27), std::complex<double>(28, 28), std::complex<double>(29, 29)};
        std::vector<std::complex<double>> data;
        data.insert(data.end(), dataPortion1.begin(), dataPortion1.end());
        data.insert(data.end(), dataPortion2.begin(), dataPortion2.end());
        data.insert(data.end(), dataPortion3.begin(), dataPortion3.end());
        data.insert(data.end(), dataPortion4.begin(), dataPortion4.end());
        data.insert(data.end(), dataPortion5.begin(), dataPortion5.end());
        std::vector<std::complex<double>> expected = stf.GetStf();
        std::vector<std::complex<double>> ltfData = ltf.GetLtf();
        expected.insert(expected.end(), ltfData.begin(), ltfData.end());
        // first OFDM symbol
        for(int counter = 0; counter < 3; counter++)
            expected.push_back(std::complex<double>(0, 0));
        expected.insert(expected.end(), dataPortion1.begin(), dataPortion1.end());
        expected.push_back(std::complex<double>(1, 0));
        expected.insert(expected.end(), dataPortion2.begin(), dataPortion2.end());
        expected.push_back(std::complex<double>(0, 0));
        expected.insert(expected.end(), dataPortion3.begin(), dataPortion3.end());
        expected.push_back(std::complex<double>(1, 0));
        expected.insert(expected.end(), dataPortion4.begin(), dataPortion4.end());
        expected.push_back(std::complex<double>(0, 0));
        expected.push_back(std::complex<double>(0, 0));
        // second OFDM Symbol
        for(int counter = 0; counter < 3; counter++)
            expected.push_back(std::complex<double>(0, 0));
        expected.insert(expected.end(), dataPortion5.begin(), dataPortion5.end());
        for(int counter = 0; counter < 3; counter++)
            expected.push_back(std::complex<double>(0, 0));
        expected.push_back(std::complex<double>(1, 0));
        for(int counter = 0; counter < 13; counter++)
            expected.push_back(std::complex<double>(0, 0));
        expected.push_back(std::complex<double>(1, 0));
        for(int counter = 0; counter < 8; counter++)
            expected.push_back(std::complex<double>(0, 0));

        TestComposeImplAndCheck(data, expected);
    }

    //todo: umv: add tests for checking compose on specific subcarrier

    TEST(DataComposer, DecomposeStfSymbol)
    {
        std::vector<std::complex<double>> data = stf.GetStf();
        TestDecomposeImplAndCheck(data, emptyData);
    }

    TEST(DataComposer, DecomposeStfAndLtfSymbols)
    {
        std::vector<std::complex<double>> data = stf.GetStf();
        std::vector<std::complex<double>> ltfData = ltf.GetLtf();
        data.insert(data.end(), ltfData.begin(), ltfData.end());
        TestDecomposeImplAndCheck(data, emptyData);
    }

    TEST(DataComposer, DecomposeDataWithStfAndLtfAndOneOfdmDataSymbol)
    {
        std::vector<std::complex<double>> expected;
        std::vector<std::complex<double>> data = stf.GetStf();
        std::vector<std::complex<double>> ltfData = ltf.GetLtf();
        data.insert(data.end(), ltfData.begin(), ltfData.end());
        std::vector<std::complex<double>> dataPortion1 = {std::complex<double>(3, 3), std::complex<double>(4, 4), std::complex<double>(5, 5),
                                                          std::complex<double>(6, 6), std::complex<double>(7, 7), std::complex<double>(8, 8)};
        std::vector<std::complex<double>> dataPortion2 = {std::complex<double>(9, 9), std::complex<double>(10, 10), std::complex<double>(11, 11),
                                                          std::complex<double>(12, 12), std::complex<double>(13, 13), std::complex<double>(14, 14)};
        std::vector<std::complex<double>> dataPortion3 = {std::complex<double>(15, 15), std::complex<double>(16, 16), std::complex<double>(17, 17),
                                                          std::complex<double>(18, 18), std::complex<double>(19, 19), std::complex<double>(20, 20)};
        std::vector<std::complex<double>> dataPortion4 = {std::complex<double>(21, 21), std::complex<double>(22, 22), std::complex<double>(23, 23),
                                                          std::complex<double>(24, 24), std::complex<double>(25, 25), std::complex<double>(26, 26)};

        expected.insert(expected.end(), dataPortion1.begin(), dataPortion1.end());
        expected.insert(expected.end(), dataPortion2.begin(), dataPortion2.end());
        expected.insert(expected.end(), dataPortion3.begin(), dataPortion3.end());
        expected.insert(expected.end(), dataPortion4.begin(), dataPortion4.end());
        for(int counter = 0; counter < 3; counter++)
            data.push_back(std::complex<double>(0, 0));
        data.insert(data.end(), dataPortion1.begin(), dataPortion1.end());
        data.push_back(std::complex<double>(1, 0));
        data.insert(data.end(), dataPortion2.begin(), dataPortion2.end());
        data.push_back(std::complex<double>(0, 0));
        data.insert(data.end(), dataPortion3.begin(), dataPortion3.end());
        data.push_back(std::complex<double>(1, 0));
        data.insert(data.end(), dataPortion4.begin(), dataPortion4.end());
        data.push_back(std::complex<double>(0, 0));
        data.push_back(std::complex<double>(0, 0));
        TestDecomposeImplAndCheck(data, expected);
    }

    TEST(DataComposer, DecomposeDataWithStfAndLtfAndTwoJaggledOfdmDataSymbols)
    {
        std::vector<std::complex<double>> expected;
        std::vector<std::complex<double>> data = stf.GetStf();
        std::vector<std::complex<double>> ltfData = ltf.GetLtf();
        data.insert(data.end(), ltfData.begin(), ltfData.end());
        std::vector<std::complex<double>> dataPortion1 = {std::complex<double>(3, 3), std::complex<double>(4, 4), std::complex<double>(5, 5),
                                                          std::complex<double>(6, 6), std::complex<double>(7, 7), std::complex<double>(8, 8)};
        std::vector<std::complex<double>> dataPortion2 = {std::complex<double>(9, 9), std::complex<double>(10, 10), std::complex<double>(11, 11),
                                                          std::complex<double>(12, 12), std::complex<double>(13, 13), std::complex<double>(14, 14)};
        std::vector<std::complex<double>> dataPortion3 = {std::complex<double>(15, 15), std::complex<double>(16, 16), std::complex<double>(17, 17),
                                                          std::complex<double>(18, 18), std::complex<double>(19, 19), std::complex<double>(20, 20)};
        std::vector<std::complex<double>> dataPortion4 = {std::complex<double>(21, 21), std::complex<double>(22, 22), std::complex<double>(23, 23),
                                                          std::complex<double>(24, 24), std::complex<double>(25, 25), std::complex<double>(26, 26)};
        std::vector<std::complex<double>> dataPortion5 = {std::complex<double>(31, 31), std::complex<double>(32, 32), std::complex<double>(33, 33),
                                                          std::complex<double>(34, 34), std::complex<double>(35, 35)};

        expected.insert(expected.end(), dataPortion1.begin(), dataPortion1.end());
        expected.insert(expected.end(), dataPortion2.begin(), dataPortion2.end());
        expected.insert(expected.end(), dataPortion3.begin(), dataPortion3.end());
        expected.insert(expected.end(), dataPortion4.begin(), dataPortion4.end());
        expected.insert(expected.end(), dataPortion5.begin(), dataPortion5.end());
        // First OFDM Symbol
        for(int counter = 0; counter < 3; counter++)
            data.push_back(std::complex<double>(0, 0));
        data.insert(data.end(), dataPortion1.begin(), dataPortion1.end());
        data.push_back(std::complex<double>(1, 0));
        data.insert(data.end(), dataPortion2.begin(), dataPortion2.end());
        data.push_back(std::complex<double>(0, 0));
        data.insert(data.end(), dataPortion3.begin(), dataPortion3.end());
        data.push_back(std::complex<double>(1, 0));
        data.insert(data.end(), dataPortion4.begin(), dataPortion4.end());
        data.push_back(std::complex<double>(0, 0));
        data.push_back(std::complex<double>(0, 0));

        // Second OFDM Symbol
        for(int counter = 0; counter < 3; counter++)
            data.push_back(std::complex<double>(0, 0));
        data.insert(data.end(), dataPortion5.begin(), dataPortion5.end());
        data.push_back(std::complex<double>(0, 0));
        data.push_back(std::complex<double>(1, 0));
        for(int counter = 0; counter < 6; counter++)
            data.push_back(std::complex<double>(0, 0));
        data.push_back(std::complex<double>(0, 0));
        for(int counter = 0; counter < 6; counter++)
            data.push_back(std::complex<double>(0, 0));
        data.push_back(std::complex<double>(1, 0));
        for(int counter = 0; counter < 6; counter++)
            data.push_back(std::complex<double>(0, 0));
        data.push_back(std::complex<double>(0, 0));
        data.push_back(std::complex<double>(0, 0));
        TestDecomposeImplAndCheck(data, expected);
    }
}

#endif /* PHY_CONVERTORS_TESTDATACOMPOSER_H_ */
