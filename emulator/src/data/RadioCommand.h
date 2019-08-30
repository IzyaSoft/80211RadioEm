#ifndef DATA_RADIOCOMMAND_H_
#define DATA_RADIOCOMMAND_H_

#include <string>
#include <vector>
#include "OfdmSymbols.h"
#include "ConvertionDirection.h"

namespace Radio80211ah
{
    struct RadioCommand
    {
        bool _useSelectedSymbols;   // 1 - symbols, 0 - content of line or file
        std::vector<Radio80211ah::OfdmSymbols> _transmissionSymbols;
        std::string _transmissionContent;
        bool _useDevice;
        int _transmissionRepeat;
        std::string _selectedDevice;
        int _useDefinedSubcarrier;
        Radio80211ah::ConvertionDirection _direction;
        bool _round;
    };
};

#endif /* DATA_RADIOCOMMAND_H_ */
