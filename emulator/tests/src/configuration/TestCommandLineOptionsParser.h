#ifndef CONFIGURATION_TESTCOMMANDLINEOPTIONSPARSER_H_
#define CONFIGURATION_TESTCOMMANDLINEOPTIONSPARSER_H_

#include <vector>
#include "CommandLineOptionsParser.h"
#include "gtest/gtest.h"

namespace TestRadio80211ah
{
    std::vector<std::string> linuxCommandLinePrefixes = {"-", "--"};
    std::vector<std::string> windowsCommandLinePrefixes = {"/"};
    std::vector<std::string> keyValueSeparatorViaEquals = {"="};
    std::vector<std::string> keyValueSeparatorViaSpace = {};

    //std::string simpleValidString = "./emulator --help";
    //std::string simpleValidString2 = "./emulator -l \"abcdefgh\" --verbose";
    char* onlyHelpOption[] = {"./emulator", "--help"};
    std::vector<Radio80211ah::KeyValueOption> expectedOnlyHelpOptions = {Radio80211ah::KeyValueOption(EXECUTION_PATH_KEY, "./emulator"),
                                                                         Radio80211ah::KeyValueOption("--help", "")};
    char* optionsWithRealValues[] = {"./emulator", "-l", "abcdefgh", "--verbose"};
    std::vector<Radio80211ah::KeyValueOption> expectedOptionsWithRealValues = {Radio80211ah::KeyValueOption(EXECUTION_PATH_KEY, "./emulator"),
                                                                               Radio80211ah::KeyValueOption("-l", "abcdefgh"),
                                                                               Radio80211ah::KeyValueOption("--verbose", "")};
    char* optionsWithRealValuesSeparatedWithEquals[] = {"./emulator", "-l=abcdefgh", "--device=/dev/usb1", "--subcarrier=2"};
    std::vector<Radio80211ah::KeyValueOption> expectedOptionsWithRealValuesSeparatedWithEquals = {Radio80211ah::KeyValueOption(EXECUTION_PATH_KEY, "./emulator"),
                                                                                                  Radio80211ah::KeyValueOption("-l", "abcdefgh"),
                                                                                                  Radio80211ah::KeyValueOption("--device", "/dev/usb1"),
                                                                                                  Radio80211ah::KeyValueOption("--subcarrier", "2")};
    char* optionsWithoutPrefixes[] = {"./emulator", "abc", "def=def", "aaa", "lll"};
    std::vector<Radio80211ah::KeyValueOption> expectedOptionsWithoutPrefixes = {Radio80211ah::KeyValueOption(EXECUTION_PATH_KEY, "./emulator")};
    char* optionsWithRealValuesSeparatedWithEqualsWinStyle[] = {".\\emulator.exe", "/l=abcdefgh", "/device=usb1", "/subcarrier=2"};
    std::vector<Radio80211ah::KeyValueOption> expectedOptionsWithRealValuesSeparatedWithEqualsWinStyle = {Radio80211ah::KeyValueOption(EXECUTION_PATH_KEY, ".\\emulator.exe"),
                                                                                                      Radio80211ah::KeyValueOption("/l", "abcdefgh"),
                                                                                                      Radio80211ah::KeyValueOption("/device", "usb1"),
                                                                                                      Radio80211ah::KeyValueOption("/subcarrier", "2")};

    void CheckOptions(std::vector<Radio80211ah::KeyValueOption> expected, std::vector<Radio80211ah::KeyValueOption> actual)
    {
        ASSERT_EQ(expected.size(), actual.size());
        for(unsigned int optionCounter = 0; optionCounter < expected.size(); optionCounter++)
        {
            ASSERT_STREQ(expected[optionCounter].GetKey().c_str(), actual[optionCounter].GetKey().c_str());
            ASSERT_STREQ(expected[optionCounter].GetKey().c_str(), actual[optionCounter].GetKey().c_str());
        }
    }

    TEST(CommandLineOptionsParser, SimpleOnlyKeysLinuxStyle)
    {
        Radio80211ah::CommandLineOptionsParser parser(linuxCommandLinePrefixes, keyValueSeparatorViaSpace);
        std::vector<Radio80211ah::KeyValueOption> actual = parser.Parse(2, onlyHelpOption);
        CheckOptions(expectedOnlyHelpOptions, actual);
    }

    TEST(CommandLineOptionsParser, KeysSeparatedWithValuesViaSpaceLinuxStyle)
    {
        Radio80211ah::CommandLineOptionsParser parser(linuxCommandLinePrefixes, keyValueSeparatorViaSpace);
        std::vector<Radio80211ah::KeyValueOption> actual = parser.Parse(4, optionsWithRealValues);
        CheckOptions(expectedOptionsWithRealValues, actual);
    }

    TEST(CommandLineOptionsParser, KeysSeparatedWithValuesViaEqualsLinuxStyle)
    {
        Radio80211ah::CommandLineOptionsParser parser(linuxCommandLinePrefixes, keyValueSeparatorViaEquals);
        std::vector<Radio80211ah::KeyValueOption> actual = parser.Parse(4, optionsWithRealValuesSeparatedWithEquals);
        CheckOptions(expectedOptionsWithRealValuesSeparatedWithEquals, actual);
    }

    TEST(CommandLineOptionsParser, KeysWithoutPrefixes)
    {
        Radio80211ah::CommandLineOptionsParser parser(linuxCommandLinePrefixes, keyValueSeparatorViaEquals);
        std::vector<Radio80211ah::KeyValueOption> actual = parser.Parse(4, optionsWithoutPrefixes);
        CheckOptions(expectedOptionsWithoutPrefixes, actual);
    }

    TEST(CommandLineOptionsParser, KeysSeparatedWithValuesViaEqualsWindowsStyle)
    {
        Radio80211ah::CommandLineOptionsParser parser(windowsCommandLinePrefixes, keyValueSeparatorViaEquals);
        std::vector<Radio80211ah::KeyValueOption> actual = parser.Parse(4, optionsWithRealValuesSeparatedWithEqualsWinStyle);
        CheckOptions(expectedOptionsWithRealValuesSeparatedWithEqualsWinStyle, actual);
    }
}


#endif /* CONFIGURATION_TESTCOMMANDLINEOPTIONSPARSER_H_ */
