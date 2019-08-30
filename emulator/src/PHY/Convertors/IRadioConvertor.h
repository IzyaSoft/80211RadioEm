#ifndef PHY_CONVERTORS_IRADIOCONVERTOR_H_
#define PHY_CONVERTORS_IRADIOCONVERTOR_H_

#include <vector>
#include <complex>
#include "PlainTypes.h"
#include "GlobalDefs.h"

namespace Radio80211ah
{
    class IRadioConvertor
    {
    public:
        virtual ~IRadioConvertor(){}
        virtual std::vector<std::complex<double>>& DirectConvert(const std::vector<Radio80211ah::octet>& data) = 0;
        virtual std::vector<Radio80211ah::octet>& ReverseConvert(const std::vector<std::complex<double>>& data) = 0;
    };
}

#endif /* PHY_CONVERTORS_IRADIOCONVERTOR_H_ */
