#include "MacPdu.h"

namespace Radio80211ah
{
    MacPdu::MacPdu(){}

    MacPdu::~MacPdu(){}

    std::vector<Radio80211ah::octet>& MacPdu::EncodePdu(std::vector<Radio80211ah::octet>& upLevelPduData)
    {
        _macData.clear();
        _macData.assign(upLevelPduData.begin(), upLevelPduData.end());
        return _macData;
    }

    std::vector<Radio80211ah::octet>& MacPdu::DecodePdu(std::vector<Radio80211ah::octet>& currentLevelPduData)
    {
        _ipData.clear();
        _ipData.assign(currentLevelPduData.begin(), currentLevelPduData.end());
        return _ipData;
    }
}
