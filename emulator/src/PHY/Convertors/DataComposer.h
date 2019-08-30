#ifndef PHY_CONVERTORS_DATACOMPOSER_H_
#define PHY_CONVERTORS_DATACOMPOSER_H_

#include <vector>
#include <complex>
#include "OfdmSymbols.h"
#include "StfSymbol.h"
#include "LtfSymbol.h"

namespace Radio80211ah
{
    const int dataSubcarriers = 24;

    class DataComposer
    {
    public:
        DataComposer() {_buffer.reserve(1024);}
        std::vector<std::complex<double>>& Compose(const std::vector<std::complex<double>>& data,
                                                   bool insertStf = true,
                                                   bool insertLtf = true,
                                                   int dataSubcarrier = 1000);
        std::vector<std::complex<double>>& Decompose(const std::vector<std::complex<double>>& data);
    private:
        void InsertData(std::vector<std::complex<double>>& data);
        void ModifyData(std::vector<std::complex<double>>& data);
    private:
        const unsigned int _dataPortion = 6;
        std::vector<std::complex<double>> _buffer;
        Radio80211ah::StfSymbol _stf;
        Radio80211ah::LtfSymbol _ltf;
    };
}

#endif /* PHY_CONVERTORS_DATACOMPOSER_H_ */
