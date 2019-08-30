#ifndef PHY_CONVERTORS_BASEBANDSHIFTER_H_
#define PHY_CONVERTORS_BASEBANDSHIFTER_H_

#include <vector>
#include <complex>

#include "ConvertionDirection.h"

namespace Radio80211ah
{
    // todo: umv: Shifter is only for 1 MHz, make support for 2, 4, 8 and 16 MHz
    class BaseBandShifter
    {
    public:
        std::vector<std::complex<double>>& Shift(const std::vector<std::complex<double>>& data);
        std::vector<std::complex<double>>& Unshift(const std::vector<std::complex<double>>& data);
    private:
        void ShiftImpl(const std::vector<std::complex<double>>& data, Radio80211ah::ConvertionDirection direction);
    private:
        std::vector<std::complex<double>> _buffer;
        std::vector<std::complex<double>> _dataCopy;
    };
}

#endif /* PHY_CONVERTORS_BASEBANDSHIFTER_H_ */
