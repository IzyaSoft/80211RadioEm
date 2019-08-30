#include "PhyPdu.h"

namespace Radio80211ah
{
    PhyPdu::PhyPdu()
    {
        _convertors.reserve(16);
        const Radio80211ah::octet scramblerInitialValue = 0x11;
        std::shared_ptr<Radio80211ah::IConvertor> scramblerConvertor(new ScramblerConvertor(scramblerInitialValue));
        std::shared_ptr<Radio80211ah::IConvertor> ofdmConvertor(new OfdmConvertor());
        _convertors.push_back(scramblerConvertor);
        _convertors.push_back(ofdmConvertor);
    }

    PhyPdu::~PhyPdu(){}

    std::vector<Radio80211ah::octet>& PhyPdu::EncodePdu(std::vector<Radio80211ah::octet>& upLevelPduData)
    {
        // todo: convert according to 80211ah standard
        _phyFrame.clear();
        std::vector<std::shared_ptr<Radio80211ah::IConvertor>> :: iterator it;
        std::vector<Radio80211ah::octet> inputData;
        inputData.assign(upLevelPduData.begin(), upLevelPduData.end());

        for (it=_convertors.begin(); it != _convertors.end(); it++)
        {
            _phyFrame = (*(it)).get()->Convert(inputData, Radio80211ah::ConvertionDirection::DIRECT);
            inputData.clear();
            inputData.assign(_phyFrame.begin(), _phyFrame.end());
        }

        return _phyFrame;
    }

    std::vector<Radio80211ah::octet>& PhyPdu::DecodePdu(std::vector<Radio80211ah::octet>& currentLevelPduData)
    {
        _macData.clear();
        std::vector<std::shared_ptr<Radio80211ah::IConvertor>> :: reverse_iterator it;
        std::vector<Radio80211ah::octet> inputData;
        inputData.assign(currentLevelPduData.begin(), currentLevelPduData.end());

        for (it =_convertors.rbegin(); it != _convertors.rend(); it++)
        {
            _macData = (*(it)).get()->Convert(inputData, Radio80211ah::ConvertionDirection::REVERSE);
            inputData.clear();
            inputData.assign(_macData.begin(), _macData.end());
        }

        return _macData;
    }
}
