#ifndef PHY_CONVERTORS_OFDMCONVERTOR_H_
#define PHY_CONVERTORS_OFDMCONVERTOR_H_

#include <memory>
#include "IConvertor.h"
#include "ConstellationMapper.h"
#include "BaseBandShifter.h"
#include "Fft.h"
#include "DataComposer.h"

namespace Radio80211ah
{
    class OfdmConvertor : public Radio80211ah::IConvertor
    {
    public:
        OfdmConvertor();
        ~OfdmConvertor();
        std::vector<Radio80211ah::octet>& Convert(const std::vector<Radio80211ah::octet>& data, Radio80211ah::ConvertionDirection direction);
    private:
        std::vector<Radio80211ah::octet>& DirectConvert(const std::vector<Radio80211ah::octet>& data);
        std::vector<Radio80211ah::octet>& ReverseConvert(const std::vector<Radio80211ah::octet>& data);
        void LogStepDataSize(int size);
    private:
        std::vector<Radio80211ah::octet> _buffer;
        std::shared_ptr<Radio80211ah::IRadioConvertor> _constellationMapper;
        std::shared_ptr<Radio80211ah::IRadioConvertor> _fft;
        Radio80211ah::DataComposer _dataComposer;
        Radio80211ah::BaseBandShifter _baseBandShifter;
    };
}

#endif /* PHY_CONVERTORS_OFDMCONVERTOR_H_ */
