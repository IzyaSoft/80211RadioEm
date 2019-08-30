#include <utility>
#include <algorithm>
#include <iostream>
#include "Fft.h"
#include "GlobalDefs.h"
#include "Logger.h"
#include "LoggerHelper.h"

std::vector<std::complex<double>>& Radio80211ah::Fft::DirectConvert(const std::vector<Radio80211ah::octet>& data)
{
    Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "**********FAST FOURIER TRANSFORMATION STARTED**********");
    const size_t numberOfComplexNumbers = data.size() / 2;
    _incomingData.clear();
    _incomingData.reserve(numberOfComplexNumbers);

    for (size_t o = 0; o < data.size(); o += 2)
    {
        char real = (char)data[o];
        char imaginary = (char)data[o + 1];
        if(Radio80211ah::verboseMode)
        {
            Radio80211ah::LoggerHelper::Clear();
            Radio80211ah::LoggerHelper::AppendStr("[FFT] Real value ");
            Radio80211ah::LoggerHelper::AppendChar(real, std::ios::dec);
            Radio80211ah::LoggerHelper::AppendStr(" converted into ");
            Radio80211ah::LoggerHelper::AppendDouble(real /(double)_scaleFactor, 5);
            Radio80211ah::LoggerHelper::AppendStr(" [FFT] Imaginary value ");
            Radio80211ah::LoggerHelper::AppendChar(imaginary, std::ios::dec);
            Radio80211ah::LoggerHelper::AppendStr(" converted into ");
            Radio80211ah::LoggerHelper::AppendDouble(imaginary / (double)_scaleFactor, 5);
            Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, Radio80211ah::LoggerHelper::Get());
        }
        _incomingData.push_back(std::complex<double>((double)real / (double)_scaleFactor, (double)imaginary / (double)_scaleFactor));
    }
    Transform(_incomingData, true, true);
    Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "**********FAST FOURIER TRANSFORMATION FINISHED**********");
    return _incomingData;
}

std::vector<Radio80211ah::octet>& Radio80211ah::Fft::ReverseConvert(const std::vector<std::complex<double>>& data)
{
    Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "**********INVERSE FAST FOURIER TRANSFORMATION STARTED**********");
    const size_t numberOfOctets = data.size() * 2;
    _outgoingData.clear();
    _outgoingData.reserve(numberOfOctets);
    //.resize(numberOfOctets);
    std::vector<std::complex<double>> dataCopy;
    dataCopy.assign(data.begin(), data.end());
    Transform(dataCopy, false, true);

    for(std::vector<std::complex<double>>::iterator it = dataCopy.begin(); it != dataCopy.end(); it++)
    {
        char castedReal = (char)((*it).real() * _scaleFactor);
        char castedImaginary = (char)((*it).imag() * _scaleFactor);
        if(Radio80211ah::verboseMode)
        {
            Radio80211ah::LoggerHelper::Clear();
            //Radio80211ah::LoggerHelper::AppendStr("\n\r");
            Radio80211ah::LoggerHelper::AppendStr("[IFFT] Complex Real: ");
            Radio80211ah::LoggerHelper::AppendDouble((*it).real(), 5);
            Radio80211ah::LoggerHelper::AppendStr(" casted as: ");
            Radio80211ah::LoggerHelper::AppendInt((unsigned char)castedReal, std::ios::hex|std::ios::showbase);
            //
            Radio80211ah::LoggerHelper::AppendStr(" [IFFT] Complex Imaginary: ");
            Radio80211ah::LoggerHelper::AppendDouble((*it).imag(), 5);
            Radio80211ah::LoggerHelper::AppendStr(" casted as: ");
            Radio80211ah::LoggerHelper::AppendInt((unsigned char)castedImaginary, std::ios::hex|std::ios::showbase);
            Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, Radio80211ah::LoggerHelper::Get());
        }
        _outgoingData.push_back(castedReal);
        _outgoingData.push_back(castedImaginary);
    }
    Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "**********INVERSE FAST FOURIER TRANSFORMATION FINISHED**********");
    return _outgoingData;
}

void Radio80211ah::Fft::Transform(std::vector<std::complex<double>>& data, bool forward, bool bitReversal)
{
    ComputeTwiddleFactors(data.size(), forward, false);

    if (bitReversal)
        PermuteDataIntoBitReversedOrder(data);

    for (size_t problemSize = 2; problemSize <= data.size(); problemSize <<= 1)
    {
        const size_t problemHalfSize = problemSize / 2;

        for (size_t group = 0; group < data.size(); group += problemSize)
        {
            size_t twiddleFactorIndex = 0;

            for (size_t butterfly = group; butterfly < group + problemHalfSize; ++butterfly)
            {
                const std::complex<double> temp = data[butterfly + problemHalfSize] * _twiddleFactors[twiddleFactorIndex];

                data[butterfly + problemHalfSize] = data[butterfly] - temp;
                data[butterfly] += temp;

                twiddleFactorIndex += data.size() / problemSize;
            }
        }
    }

    if (!forward)
        Invert(data);
}

void Radio80211ah::Fft::ComputeTwiddleFactors(size_t numberOfSamples, bool forward, bool bitReversal)
{
    _twiddleFactors.resize(numberOfSamples / 2);

    for (size_t i = 0; i < (numberOfSamples / 2); ++i)
    {
        const double angle = (2.0 * M_PI * static_cast<double>(i) / static_cast<double>(numberOfSamples)) * (forward ? -1.0 : 1.0);
        _twiddleFactors[bitReversal ? BitReverse(i, static_cast<size_t>(log2(numberOfSamples)) - 1) : i] = std::complex<double>(cos(angle), sin(angle));
    }
}

void Radio80211ah::Fft::PermuteDataIntoBitReversedOrder(std::vector<std::complex<double>>& data) const
{
    for (size_t index = 0; index < data.size(); ++index)
    {
        const size_t bitReversedIndex = BitReverse(index, static_cast<size_t>(log2(data.size())));

        if (bitReversedIndex <= index)
            continue;

        std::swap(data[index], data[bitReversedIndex]);
    }
}

void Radio80211ah::Fft::Invert(std::vector<std::complex<double>>& data) const
{
    std::for_each(data.begin(), data.end(), [&data](std::complex<double>& sample)
    {
        sample *= 1.0 / static_cast<double>(data.size());
    });
}
