#ifndef PHY_CONVERTORS_CONSTELLATIONMAPPER_H_
#define PHY_CONVERTORS_CONSTELLATIONMAPPER_H_

#include "IRadioConvertor.h"
#include "ConstellationType.h"
#include <math.h>
#include <map>

namespace Radio80211ah
{
    class ConstellationMapper : public IRadioConvertor
    {
    public:
        ConstellationMapper(Radio80211ah::ConstellationType constellationType);
        ~ConstellationMapper(){}
        std::vector<std::complex<double>>& DirectConvert(const std::vector<Radio80211ah::octet>& data);
        std::vector<Radio80211ah::octet>& ReverseConvert(const std::vector<std::complex<double>>& data);
    private:
        void PutBytes(const std::vector<std::complex<double>>& dataChunk);
        void PutSymbols(Radio80211ah::octet dataOctet);
        void PutQam64Symbols(const std::vector<Radio80211ah::octet>& threeBytesBuffer);
        std::complex<double> GetSymbolComplexValue(Radio80211ah::octet code);
        Radio80211ah::octet GetSymbolBinaryCode(std::complex<double> symbol);
        void InitializeBitsPerSymbolValue();
        void MapConstellationCodes();
        void MapBpsk();
        void MapQpsk();
        void MapQam16();
        void MapQam64();
        void MapQam256();
    private:
        Radio80211ah::ConstellationType _constellationType;
        int _bitsPerSymbol;
        std::vector<std::complex<double>> _symbolsBuffer;
        std::vector<Radio80211ah::octet> _buffer;
        // maps
        std::map<Radio80211ah::octet, std::complex<double>> _bpskMap;
        std::map<Radio80211ah::octet, std::complex<double>> _qpskMap;
        std::map<Radio80211ah::octet, std::complex<double>> _qam16Map;
        std::map<Radio80211ah::octet, std::complex<double>> _qam64Map;
        std::map<Radio80211ah::octet, std::complex<double>> _qam256Map;
        // KMod values
        const double _bpskKmod = 1.0;
        const double _qpskKmod = 1.0 / sqrt(2);
        const double _qam16Kmod = 1.0 / sqrt(10);
        const double _qam64Kmod = 1.0 / sqrt(42);
    };
}
#endif /* PHY_CONVERTORS_SCRAMBLERCONVERTOR_H_ */
