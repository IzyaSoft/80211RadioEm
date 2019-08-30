#include <iostream>
#include <fstream>
#include <sstream>
#include "RadioCommandBuilder.h"
#include "ConfigurationKeys.h"
#include "GlobalDefs.h"
#include "Logger.h"

namespace Radio80211ah
{
    std::string stfSymbol = "[STF]";
    std::string ltfSymbol = "[LTF]";

    Radio80211ah::RadioCommand RadioCommandBuilder::Build(Radio80211ah::CommandLineOptionsManager& manager)
    {
        Radio80211ah::RadioCommand command;
        std::string outValue;
        int outIntValue;
        // 1. Selecting data source
        if(manager.TryGetValue(TRANSMIT_SYMBOLS_LONG, outValue) || manager.TryGetValue(TRANSMIT_SYMBOLS_LONG, outValue))
        {
            int stfPosition = outValue.find(stfSymbol);
            int ltfPosition = outValue.find(ltfSymbol);
            if(stfPosition != -1)//std::string::npos)
                command._transmissionSymbols.push_back(Radio80211ah::OfdmSymbols::STF);
            if(ltfPosition != -1)//std::string::npos)
                command._transmissionSymbols.push_back(Radio80211ah::OfdmSymbols::LTF);
            command._useSelectedSymbols = true;
        }
        else
        {
            command._useSelectedSymbols = false;
            if(manager.TryGetValue(CONVERT_LINE_SHORT, outValue) || manager.TryGetValue(CONVERT_LINE_LONG, outValue))
                command._transmissionContent = outValue;
            else if(manager.TryGetValue(CONVERT_FILE_SHORT, outValue) || manager.TryGetValue(CONVERT_FILE_LONG, outValue))
            {
                std::ifstream dataFile (outValue.c_str());
                if(dataFile.is_open())
                {
                    std::stringstream sstream;
                    sstream << dataFile.rdbuf();
                    dataFile.close();
                    command._transmissionContent = sstream.str();
                    if(Radio80211ah::verboseMode)
                    {
                        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Info, "File content before encoding:");
                        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Info, sstream.str());
                    }
                }
            }
        }
        if(manager.TryGetValue(CONVERT_ROUND_LONG, outValue))
            command._round = true;
        else
        {
            command._direction = !(manager.TryGetValue(CONVERT_REVERSE_LONG, outValue) && !manager.TryGetValue(CONVERT_REVERSE_SHORT, outValue))
                               ? Radio80211ah::ConvertionDirection::DIRECT
                               : Radio80211ah::ConvertionDirection::REVERSE;
        }

        // 2. USB device usage subcarrier selection and retransmission
        if(manager.TryGetValue(TRANSMIT_VIA_DEVICE_LONG, outValue) || manager.TryGetValue(TRANSMIT_VIA_DEVICE_SHORT, outValue))
        {
            command._selectedDevice = outValue;
            command._useDevice = true;
        }
        if(command._useDevice)
        {
            if(manager.TryGetIntValue(USE_SUBCARRIER_SHORT, outIntValue) || manager.TryGetIntValue(USE_SUBCARRIER_LONG, outIntValue))
                command._useDefinedSubcarrier = outIntValue;
            if(manager.TryGetIntValue(REPEAT_TRANSMISSION_SHORT, outIntValue) || manager.TryGetIntValue(REPEAT_TRANSMISSION_LONG, outIntValue))
                command._transmissionRepeat = outIntValue;
        }
        return command;
    }
}
