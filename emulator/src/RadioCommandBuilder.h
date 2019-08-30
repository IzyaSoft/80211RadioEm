#ifndef CONFIGURATION_RADIOCOMMANDBUILDER_H_
#define CONFIGURATION_RADIOCOMMANDBUILDER_H_

#include <vector>
#include "CommandLineOptionsManager.h"
#include "RadioCommand.h"

namespace Radio80211ah
{
    class RadioCommandBuilder
    {
    public:
        static Radio80211ah::RadioCommand Build(Radio80211ah::CommandLineOptionsManager& manager);
    };
}

#endif /* CONFIGURATION_RADIOCOMMANDBUILDER_H_ */
