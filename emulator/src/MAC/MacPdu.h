#ifndef MAC_MACPDU_H_
#define MAC_MACPDU_H_

#include "IOsiPdu.h"

namespace Radio80211ah
{
    class MacPdu : public Radio80211ah::IOsiPdu
    {
    public:
        MacPdu();
        ~MacPdu();
        std::vector<Radio80211ah::octet>& EncodePdu(std::vector<Radio80211ah::octet>& upLevelPduData);
        std::vector<Radio80211ah::octet>& DecodePdu(std::vector<Radio80211ah::octet>& currentLevelPduData);
    private:
        std::vector<Radio80211ah::octet> _macData;
        std::vector<Radio80211ah::octet> _ipData;
    };
}

#endif /* MAC_MACPDU_H_ */
