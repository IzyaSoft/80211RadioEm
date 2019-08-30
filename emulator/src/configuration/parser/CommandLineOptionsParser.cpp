#include <string.h>
#include "CommandLineOptionsParser.h"

namespace Radio80211ah
{
    CommandLineOptionsParser :: CommandLineOptionsParser(std::vector<std::string>& optionPrefixes, std::vector<std::string>& keyValueSeparators, bool interactiveMode)
    {
       _optionPrefixes.assign(optionPrefixes.begin(), optionPrefixes.end());
       _keyValueSeparators.assign(keyValueSeparators.begin(), keyValueSeparators.end());
       _interactiveMode = interactiveMode;
    }

    std::vector<KeyValueOption>& CommandLineOptionsParser :: Parse(int argc, char** argv)
    {
        try
        {
            _programOptions.reserve(argc);
            std::string firstKey = _interactiveMode ? COMMAND_KEY : EXECUTION_PATH_KEY;
            _programOptions.push_back(Radio80211ah::KeyValueOption (firstKey, argv[0]));
            for(int argCounter = 1; argCounter < argc; argCounter++)
            {
                std::string argumentString(argv[argCounter]);
                if(CheckIsKey(argumentString))
                {
                    // probably could be a value ...
                    // 1. key and value in the one string i.e. key=value
                    if(CheckValueIsPresent(argumentString))
                    {
                        std::string separator = GetKeyValueSeparator(argumentString);
                        int index = argumentString.find(separator);
                        _programOptions.push_back(Radio80211ah::KeyValueOption (argumentString.substr(0, index), argumentString.substr(index + separator.size())));
                        continue;
                    }
                    if(argCounter + 1 < argc)
                    {
                        std::string nextArgumentString(argv[argCounter + 1]);
                        // 2. key and value were separated with space and placed in 2 different elements
                        if(!CheckIsKey(nextArgumentString))
                        {
                            _programOptions.push_back(Radio80211ah::KeyValueOption (argumentString, nextArgumentString));
                            continue;
                        }
                    }
                    // 3. option contains only key and no value
                    _programOptions.push_back(Radio80211ah::KeyValueOption (argumentString, std::string ()));
                }
            }
            return _programOptions;
        }
        catch(...)
        {
            _programOptions.clear();
            return _programOptions;
        }
    }

    std::string& CommandLineOptionsParser :: GetKeyValueSeparator(std::string& argumentString)
    {
        std::vector<std::string>:: iterator it;
        for(it = _keyValueSeparators.begin(); it != _keyValueSeparators.end(); it++)
            if(argumentString.find(*it) != std::string::npos)
                        return (*it);
        throw ("Something goes wrong!");
    }

    bool CommandLineOptionsParser :: CheckValueIsPresent(std::string& argumentString)
    {
        std::vector<std::string>:: iterator it;
        for(it = _keyValueSeparators.begin(); it != _keyValueSeparators.end(); it++)
            if(argumentString.find(*it) != std::string::npos)
                return true;
        return false;
    }

    bool CommandLineOptionsParser :: CheckIsKey(std::string& argumentString)
    {
       std::vector<std::string>:: iterator it;
       for(it = _optionPrefixes.begin(); it!= _optionPrefixes.end(); it++)
           if(strncmp((*it).c_str(), argumentString.c_str(), (*it).size()) == 0)
               return true;
       return false;
    }
}
