#ifndef DATA_STFSYMBOL_H_
#define DATA_STFSYMBOL_H_

#include <vector>
#include <complex>
#include <math.h>

namespace Radio80211ah
{
    class StfSymbol
    {
    public:
        StfSymbol();
        std::vector<std::complex<double>>& GetStf(){return _stf;}
    private:
        void InitStf();
    private:
        const double _multiplyer = sqrt(2.0/3.0);
        std::vector<std::complex<double>> _stf;
    };
}

#endif /* DATA_STFSYMBOL_H_ */
