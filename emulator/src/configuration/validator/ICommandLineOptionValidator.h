#ifndef CONFIGURATION_ICOMMANDOPTIONVALIDATOR_H_
#define CONFIGURATION_ICOMMANDOPTIONVALIDATOR_H_

#include <vector>
#include "KeyValueOption.h"

namespace Radio80211ah
{
    class ICommandLineOptionValidator
    {
    public:
        virtual bool Validate(std::vector<Radio80211ah::KeyValueOption> options, bool useWithoutOptions = true, bool printHelp = true);
        virtual ~ICommandLineOptionValidator(){}
    };
}
#endif /* CONFIGURATION_ICOMMANDOPTIONVALIDATOR_H_ */
