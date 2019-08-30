#ifndef CONFIGURATION_COMMANDLINEOPTIONSMANAGER_H_
#define CONFIGURATION_COMMANDLINEOPTIONSMANAGER_H_

#include <memory>
#include "CommandLineOptionsParser.h"
#include "ICommandLineOptionValidator.h"

namespace Radio80211ah
{
    class CommandLineOptionsManager
    {
    public:
        CommandLineOptionsManager(Radio80211ah::ICommandLineOptionValidator* validator, int argc, char** argv, bool linuxStyle = true, bool useSpaces = true, bool interactiveMode = false);
        bool TryGetValue(std::string key, std::string& outValue);
        bool TryGetIntValue(std::string key, int& outValue);
        bool TryGetDoubleValue(std::string key, double& outValue);
        std::vector<KeyValueOption>& GetParsedOptions() {return _programOptions;}
    private:
        std::shared_ptr<Radio80211ah::CommandLineOptionsParser> _parser;
        std::shared_ptr<Radio80211ah::ICommandLineOptionValidator> _validator;
        std::vector<Radio80211ah::KeyValueOption> _programOptions;
    };
}

#endif /* CONFIGURATION_COMMANDLINEOPTIONSMANAGER_H_ */
