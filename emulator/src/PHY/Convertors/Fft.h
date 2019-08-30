#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <complex>
#include <IRadioConvertor.h>

namespace Radio80211ah
{
    class Fft : public IRadioConvertor
    {
    public:
        Fft(int scaleFactor = 1):_scaleFactor(scaleFactor){}
        std::vector<std::complex<double>>& DirectConvert(const std::vector<octet>& data) override;
        std::vector<octet>& ReverseConvert(const std::vector<std::complex<double>>& data) override;
        void Transform(std::vector<std::complex<double>>& data, bool forward, bool bitReversal);
    private:
        void ComputeTwiddleFactors(size_t numberOfSamples, bool forward, bool bitReversal);
        void PermuteDataIntoBitReversedOrder(std::vector<std::complex<double>>& data) const;
        size_t BitReverse(size_t value, size_t numberOfBits) const;
        void Invert(std::vector<std::complex<double>>& data) const;
    private:
        int _scaleFactor;
        std::vector<std::complex<double>> _twiddleFactors;
        std::vector<std::complex<double>> _incomingData;
        std::vector<Radio80211ah::octet> _outgoingData;
    };
}

inline size_t Radio80211ah::Fft::BitReverse(size_t value, size_t numberOfBits) const
{
    size_t bitReversedValue = 0;

    for (size_t i = 0; i < numberOfBits; ++i)
    {
        bitReversedValue = (bitReversedValue << 1) | (value & 1);
        value >>= 1;
    }

    return bitReversedValue;
}
