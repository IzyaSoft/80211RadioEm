//============================================================================
// Name        : emulator.cpp
// Author      : Ushakov Michael
// Version     :
// Copyright   : Ushakov Michael aka EvilLord (EasySoft group)
// Description : Emulator of 802.11ah standard
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <string.h>
#include <stdio.h>

#include "Logger.h"
#include "GlobalDefs.h"
#include "ConfigurationKeys.h"
#include "NestedOptions.h"
#include "CommandLineOptionsManager.h"
#include "RadioCommandBuilder.h"
#include "VirtualDevice.h"

int main(int argc, char** argv)
{
    Radio80211ah::LoggerWrapper::Init();
    Radio80211ah::CommandLineOptionsManager cmdOptionsManager(new Radio80211ah::ICommandLineOptionValidator(), argc, argv);
    std::string outValue;
    if(cmdOptionsManager.TryGetValue(HELP_LONG, outValue) || cmdOptionsManager.TryGetValue(HELP_SHORT, outValue))
    {
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Info, Radio80211ah::helpMessage);
        return 0;
    }

    if(cmdOptionsManager.TryGetValue(VERSION_LONG, outValue) || cmdOptionsManager.TryGetValue(VERSION_SHORT, outValue))
    {
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Info, Radio80211ah::emulatorVersion);
        return 0;
    }

    if(cmdOptionsManager.TryGetValue(VERBOSE_LONG, outValue) || cmdOptionsManager.TryGetValue(VERBOSE_SHORT, outValue))
        Radio80211ah::verboseMode = true;
     Radio80211ah::VirtualDevice radioEmulator;

    if(cmdOptionsManager.TryGetValue(INTERACTIVE_MODE_LONG, outValue) || cmdOptionsManager.TryGetValue(INTERACTIVE_MODE_SHORT, outValue))
    {
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Info, "Welcome to 802.11ah emulator INTERACTIVE mode");
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Info, "For detailed info type \"help\", for exit type \"quit\"");
        std::string inputCmd;
        inputCmd.reserve(1024);
        std::vector<char*> parameters;
        parameters.reserve(16);
        while(1)
        {
            std::getline(std::cin, inputCmd);
            char* element;
            char* cInputCmd = (char*)inputCmd.c_str();
            element = strtok(cInputCmd, (const char*)" ");
            while(element != NULL)
            {
                parameters.push_back(element);
                element = strtok(NULL, (const char*)" ");
            }
            if(strcmp(parameters[0], "quit") == 0)
            {
                Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Info, "Exiting from emulator, see log file for details.");
                return 0;
            }
            if(strcmp(parameters[0], Radio80211ah::helpCommand.c_str()) == 0)
                Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Info, Radio80211ah::interactiveOptions);
            else
            {
                cmdOptionsManager = Radio80211ah::CommandLineOptionsManager(new Radio80211ah::ICommandLineOptionValidator(),
                                                                            parameters.size(), parameters.data(),
                                                                            true, true, true);
                Radio80211ah::RadioCommand commandArgs = Radio80211ah::RadioCommandBuilder::Build(cmdOptionsManager);
                std::string commandType;
                bool result = cmdOptionsManager.TryGetValue(COMMAND_KEY, commandType);
                if(result)
                {
                    if(cmdOptionsManager.TryGetValue(VERBOSE_LONG, outValue) || cmdOptionsManager.TryGetValue(VERBOSE_SHORT, outValue))
                        Radio80211ah::verboseMode = true;

                    if(strcmp(commandType.c_str(), Radio80211ah::sendCommand.c_str()) == 0 || strcmp(commandType.c_str(), Radio80211ah::convertCommand.c_str()) == 0)
                        radioEmulator.Execute(Radio80211ah::RadioCommandBuilder::Build(cmdOptionsManager));
                }
            }
            Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Info, "Enter another command, for details see \"help\"");
            parameters.clear();
        }

    }
    else
        radioEmulator.Execute(Radio80211ah::RadioCommandBuilder::Build(cmdOptionsManager));
    return 0;
}
