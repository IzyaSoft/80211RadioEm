#ifndef PHY_CONVERTORS_SCRAMBLERCONVERTOR_H_
#define PHY_CONVERTORS_SCRAMBLERCONVERTOR_H_

#include "IConvertor.h"

namespace Radio80211ah
{
    class ScramblerConvertor : public IConvertor
    {
    public:
        ScramblerConvertor(Radio80211ah::octet initialState);
        ~ScramblerConvertor(){}
        std::vector<Radio80211ah::octet>& Convert(const std::vector<Radio80211ah::octet>& data, Radio80211ah::ConvertionDirection direction);
    private:
        std::vector<Radio80211ah::octet>& DirectConvert(const std::vector<Radio80211ah::octet>& data);
        std::vector<Radio80211ah::octet>& ReverseConvert(const std::vector<Radio80211ah::octet>& data);
        Radio80211ah::octet GetNextScramblerValue(Radio80211ah::octet currentShiftRegisterValue, Radio80211ah::ConvertionDirection direction);
        Radio80211ah::octet GetPolynomialValue(Radio80211ah::octet  currentShiftRegisterValue);
    private:
        std::vector<Radio80211ah::octet> _buffer;
        Radio80211ah::octet _initialShiftRegisterValue;
        Radio80211ah::octet _shiftRegisterValue;
	};
}
#endif /* PHY_CONVERTORS_SCRAMBLERCONVERTOR_H_ */
