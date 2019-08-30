#ifndef PHY_CONVERTORS_ICONVERTOR_H_
#define PHY_CONVERTORS_ICONVERTOR_H_

#include <vector>
#include "PlainTypes.h"
#include "ConvertionDirection.h"
#include "GlobalDefs.h"

namespace Radio80211ah
{
    class IConvertor
    {
    public:
        virtual ~IConvertor(){}
        virtual std::vector<Radio80211ah::octet>& Convert(const std::vector<Radio80211ah::octet>& data, Radio80211ah::ConvertionDirection direction) = 0;
    private:
        virtual std::vector<Radio80211ah::octet>& DirectConvert(const std::vector<Radio80211ah::octet>& data) = 0;
        virtual std::vector<Radio80211ah::octet>& ReverseConvert(const std::vector<Radio80211ah::octet>& data) = 0;
    };
}

#endif /* PHY_CONVERTORS_ICONVERTOR_H_ */
