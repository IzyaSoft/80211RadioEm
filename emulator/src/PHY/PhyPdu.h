#ifndef PHY_PHYPDU_H_
#define PHY_PHYPDU_H_

#include <memory>
#include "IOsiPdu.h"
#include "ScramblerConvertor.h"
#include "OfdmConvertor.h"

namespace Radio80211ah
{
    class PhyPdu : public IOsiPdu
    {
    public:
        PhyPdu();
        ~PhyPdu();

        std::vector<Radio80211ah::octet>& EncodePdu(std::vector<Radio80211ah::octet>& upLevelPduData);
        std::vector<Radio80211ah::octet>& DecodePdu(std::vector<Radio80211ah::octet>& currentLevelPduData);
    private:
        std::vector<Radio80211ah::octet> _phyFrame;
        std::vector<Radio80211ah::octet> _macData;
        std::vector<std::shared_ptr<Radio80211ah::IConvertor>> _convertors;
    };
}

#endif /* PHY_PHYPDU_H_ */
