#ifndef VIRTUALDEVICE_H_
#define VIRTUALDEVICE_H_

#include <memory>
#include <vector>
#include "PlainTypes.h"
#include "RadioCommand.h"

class IOsiPdu;

namespace Radio80211ah
{
    class IOsiPdu;

    class VirtualDevice
    {
    public:
        VirtualDevice();
        void Execute(Radio80211ah::RadioCommand command);
        std::vector<Radio80211ah::octet>& Encode(std::vector<Radio80211ah::octet>& dataToEncode);
        std::vector<Radio80211ah::octet>& Decode(std::vector<Radio80211ah::octet>& dataToDecode);
    private:
        std::shared_ptr<IOsiPdu> _phyLayer;
        std::shared_ptr<IOsiPdu> _macLayer;
    };
}

#endif /* VIRTUALDEVICE_H_ */
