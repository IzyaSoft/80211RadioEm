#ifndef PHY_CONVERTORS_SCRAMBLERTEST_H
#define PHY_CONVERTORS_SCRAMBLERTEST_H

#include <memory>
#include <string>
#include "ScramblerConvertor.h"
#include "gtest/gtest.h"

namespace TestRadio80211ah
{
    const Radio80211ah::octet scramblerInitialValue = 0x11;
    std::string testMessage = "Test_Message";

    //std::vector<Radio80211ah::octet>& ConvertTestMessageAndCheck(std::shared_ptr<Radio80211ah::IConvertor>& scrambler);

    //todo: umv: optimization -> common code should be moved to common functions
    TEST(ScramblerConvertor, TestScrambling)
    {
        std::shared_ptr<Radio80211ah::IConvertor> scrambler(new Radio80211ah::ScramblerConvertor(scramblerInitialValue));
        std::vector<Radio80211ah::octet> dataToEncode;
        dataToEncode.assign(testMessage.begin(), testMessage.end());
        std::vector<Radio80211ah::octet> encodedData = scrambler.get()->Convert(dataToEncode, Radio80211ah::ConvertionDirection::DIRECT);
        std::string encodedString;
        encodedString.assign(encodedData.begin(), encodedData.end());
        std::vector<Radio80211ah::octet> expectedData = {216, 203, 126, 18, 186, 241, 224, 153, 56, 208, 132, 106};
        std::string expectedString;
        expectedString.assign(expectedData.begin(), expectedData.end());
        ASSERT_STREQ(expectedString.c_str(), encodedString.c_str());
        scrambler.reset();
    }

    //todo: umv: optimization -> common code should be moved to common functions
    TEST(ScramblerConvertor, TestDescrambling)
    {
        std::shared_ptr<Radio80211ah::IConvertor> scrambler(new Radio80211ah::ScramblerConvertor(scramblerInitialValue));
        std::vector<Radio80211ah::octet> dataToEncode;
        dataToEncode.assign(testMessage.begin(), testMessage.end());
        std::vector<Radio80211ah::octet> encodedData = scrambler.get()->Convert(dataToEncode, Radio80211ah::ConvertionDirection::DIRECT);
        std::string encodedString;
        encodedString.assign(encodedData.begin(), encodedData.end());
        std::vector<Radio80211ah::octet> expectedData = {216, 203, 126, 18, 186, 241, 224, 153, 56, 208, 132, 106};
        std::string expectedString;
        expectedString.assign(expectedData.begin(), expectedData.end());
        ASSERT_STREQ(expectedString.c_str(), encodedString.c_str());
        encodedData = scrambler.get()->Convert(encodedData, Radio80211ah::ConvertionDirection::REVERSE);
        std::vector<Radio80211ah::octet> viceVersaExpectedData = {'T', 'e', 's', 't', '_', 'M', 'e', 's', 's', 'a', 'g', 'e'};
        encodedString.assign(encodedData.begin(), encodedData.end());
        std::string viceVersaExpectedString;
        viceVersaExpectedString.assign(viceVersaExpectedData.begin(), viceVersaExpectedData.end());
        ASSERT_STREQ(viceVersaExpectedString.c_str(), encodedString.c_str());
        scrambler.reset();
    }

    /*std::vector<Radio80211ah::octet>& ConvertTestMessageAndCheck(std::shared_ptr<Radio80211ah::IConvertor>& scrambler)
    {
        std::vector<Radio80211ah::octet> dataToEncode;
        dataToEncode.assign(testMessage.begin(), testMessage.end());
        static std::vector<Radio80211ah::octet> encodedData = scrambler.get()->Convert(dataToEncode, Radio80211ah::ConvertionDirection::DIRECT);
        std::string encodedString;
        encodedString.assign(encodedData.begin(), encodedData.end());
        std::vector<Radio80211ah::octet> expectedData = {216, 203, 126, 18, 186, 241, 224, 153, 56, 208, 132, 106};
        std::string expectedString;
        expectedString.assign(expectedData.begin(), expectedData.end());
        ASSERT_STREQ(expectedString.c_str(), encodedString.c_str());
        return encodedData;
    }*/
};

#endif
