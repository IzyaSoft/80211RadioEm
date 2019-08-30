#include <ICommandLineOptionValidator.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include "ConfigurationKeys.h"
#include "Logger.h"

namespace Radio80211ah
{
    bool ICommandLineOptionValidator :: Validate(std::vector<Radio80211ah::KeyValueOption> options, bool useWithoutOptions, bool printHelp)
    {
        if(!useWithoutOptions && options.size() < 2)
        {
            Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Info, "Missing arguments, how to use see " + options[0].GetValue() + " " +
                                                                              std::string(HELP_LONG) + " or " + std::string(HELP_SHORT));
            return false;
        }
        bool helpPresent = false;
        std::find_if(options.begin(), options.end(),[&helpPresent](Radio80211ah::KeyValueOption option)
                                                    {
                                                        helpPresent = (strcmp(option.GetKey().c_str(), HELP_LONG) == 0) ||
                                                                      (strcmp(option.GetKey().c_str(), HELP_SHORT) == 0);
                                                        return helpPresent;
                                                    });
        if(helpPresent && options.size() > 2)
        {
            Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Error, std::string(HELP_LONG) + " or " + std::string(HELP_SHORT) +
                                                                              " can't be use simultaneously with other keys.");
            return false;
        }

        bool versionPresent = false;
        std::find_if(options.begin(), options.end(),[&versionPresent](Radio80211ah::KeyValueOption option)
                                                    {
                                                        versionPresent = (strcmp(option.GetKey().c_str(), VERSION_LONG) == 0) ||
                                                                         (strcmp(option.GetKey().c_str(), VERSION_SHORT) == 0);
                                                        return versionPresent;
                                                    });
        if(versionPresent && options.size() > 2)
        {
            Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Error, std::string(VERSION_LONG) + " or " + std::string(VERSION_SHORT) +
                                                                              " can't be use simultaneously with other keys.");
            return false;
        }
        return true;
    }
}
