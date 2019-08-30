#include <iostream>
#include "OfdmConvertor.h"
#include "GlobalDefs.h"
#include "Logger.h"
#include "LoggerHelper.h"

namespace Radio80211ah
{
    OfdmConvertor :: OfdmConvertor()
    {
        _constellationMapper = std::shared_ptr<IRadioConvertor>(new Radio80211ah::ConstellationMapper(Radio80211ah::ConstellationType::QPSK));
        _fft = std::shared_ptr<IRadioConvertor>(new Fft(100));  //todo: umv: we should think about more quality scheme of casting double to octet
    }

    OfdmConvertor :: ~OfdmConvertor()
    {
        _constellationMapper.reset();
        _fft.reset();
    }

    std::vector<Radio80211ah::octet>& OfdmConvertor :: Convert(const std::vector<Radio80211ah::octet>& data, Radio80211ah::ConvertionDirection direction)
    {
        if(direction == Radio80211ah::ConvertionDirection::DIRECT)
            return DirectConvert(data);
        return ReverseConvert(data);
    }

    std::vector<Radio80211ah::octet>& OfdmConvertor :: DirectConvert(const std::vector<Radio80211ah::octet>& data)
    {
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "**********OFDM DIRECT CONVERSION STARTED***********");
        //std::vector<Radio80211ah::octet> dataCopy;
        //dataCopy.assign(data.begin(), data.end());
        LogStepDataSize((int)data.size());
        _buffer.clear();
        // constellation
        std::vector<std::complex<double>> mappedData = _constellationMapper->DirectConvert(data);
        LogStepDataSize((int)mappedData.size());
        // data composition
        mappedData = _dataComposer.Compose(mappedData);
        LogStepDataSize((int)mappedData.size());
        // shift
        mappedData = _baseBandShifter.Shift(mappedData);
        LogStepDataSize((int)mappedData.size());
        // ifft
        std::vector<std::complex<double>> dataPortion;
        for(;;)
        {
            // take portion and convert ...
            dataPortion.assign(mappedData.begin(), mappedData.begin() + Radio80211ah::subcarriersNumber);
            std::vector<Radio80211ah::octet> convertedData = _fft->ReverseConvert(dataPortion);
            _buffer.insert(_buffer.end(), convertedData.begin(), convertedData.end());
            std::vector<std::complex<double>> :: iterator it = mappedData.erase(mappedData.begin(), mappedData.begin() + Radio80211ah::subcarriersNumber);
            if(it == mappedData.end())
                break;
        }
        LogStepDataSize((int)_buffer.size());
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "**********OFDM DIRECT CONVERSION FINISHED***********");
        return _buffer;
    }

    std::vector<Radio80211ah::octet>& OfdmConvertor :: ReverseConvert(const std::vector<Radio80211ah::octet>& data)
    {
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "**********OFDM REVERSE CONVERSION STARTED***********");
        _buffer.clear();
        std::vector<Radio80211ah::octet> dataCopy;
        std::vector<Radio80211ah::octet> dataPortion;
        dataCopy.assign(data.begin(), data.end());
        LogStepDataSize((int)dataCopy.size());
        std::vector<std::complex<double>> mappedData;
        // fft
        for(;;)
        {
            dataPortion.assign(dataCopy.begin(), dataCopy.begin() + 2 * Radio80211ah::subcarriersNumber);
            std::vector<std::complex<double>> chunk = _fft->DirectConvert(dataPortion);
            mappedData.insert(mappedData.end(), chunk.begin(), chunk.end());
            std::vector<Radio80211ah::octet>::iterator it = dataCopy.erase(dataCopy.begin(), dataCopy.begin() + 2 * Radio80211ah::subcarriersNumber);
            if(it == dataCopy.end())
                break;
        }
        // unshift
        LogStepDataSize((int)mappedData.size());
        mappedData = _baseBandShifter.Unshift(mappedData);
        // decomposition
        LogStepDataSize((int)mappedData.size());
        mappedData = _dataComposer.Decompose(mappedData);
        // unmapping
        LogStepDataSize((int)mappedData.size());
        _buffer = _constellationMapper->ReverseConvert(mappedData);
        LogStepDataSize((int)_buffer.size());
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "**********OFDM REVERSE CONVERSION FINISHED***********");
        return _buffer;
    }

    void OfdmConvertor :: LogStepDataSize(int size)
    {
        if(Radio80211ah::verboseMode)
        {
            Radio80211ah::LoggerHelper::Clear();
            Radio80211ah::LoggerHelper::AppendStr("size: ");
            Radio80211ah::LoggerHelper::AppendInt(size, std::ios::dec);
            Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, Radio80211ah::LoggerHelper::Get());
        }
    }
}
