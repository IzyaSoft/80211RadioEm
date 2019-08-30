#ifndef DATA_LTFSYMBOL_H_
#define DATA_LTFSYMBOL_H_

#include <vector>
#include <complex>
#include <math.h>

namespace Radio80211ah
{
    class LtfSymbol
    {
    public:
        LtfSymbol();
        std::vector<std::complex<double>>& GetLtf(){return _ltf;}
    private:
        void InitLtf();
    private:
        std::vector<std::complex<double>> _ltf;
    };
}
#endif /* DATA_LTFSYMBOL_H_ */
