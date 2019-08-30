#include <iostream>
#include "TestScramblerConvertor.h"
#include "TestConstellationMapper.h"
#include "TestCommandLineOptionsParser.h"
#include "TestDataComposer.h"
#include "TestBaseBandShifter.h"
#include "TestFft.h"
#include "gtest/gtest.h"

using namespace std;
using namespace TestRadio80211ah;

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
