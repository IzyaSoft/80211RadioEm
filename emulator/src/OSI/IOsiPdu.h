#ifndef OSI_IOSIPDU_H_
#define OSI_IOSIPDU_H_

#include <vector>
#include "PlainTypes.h"

namespace Radio80211ah
{
    enum class OsiLevel : unsigned int
    {
        PHY = 1,
        MAC,
        NETWORK,
        TRANSPORT,
        SESSION,
        PRESENTATION,
        APPLICATION
    };

    class IOsiPdu
    {
    public:
        virtual ~IOsiPdu() {}

        void SetPduLevel(OsiLevel pduLevel) { _pduLevel = pduLevel; }
        OsiLevel GetPduLevel() const { return _pduLevel; }

        virtual std::vector<Radio80211ah::octet>& EncodePdu(std::vector<Radio80211ah::octet>& upLevelPduData) = 0;
        virtual std::vector<Radio80211ah::octet>& DecodePdu(std::vector<Radio80211ah::octet>& currentLevelPduData) = 0;
    private:
        OsiLevel _pduLevel;
    };
}

#endif
