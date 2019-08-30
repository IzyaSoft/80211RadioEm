#include <iostream>
#include "GlobalDefs.h"
#include "BaseBandShifter.h"
#include "Logger.h"
#include "LoggerHelper.h"


namespace Radio80211ah
{
    std::vector<std::complex<double>>& BaseBandShifter :: Shift(const std::vector<std::complex<double>>& data)
    {
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "**********BASE BAND DIRECT SHIFT STARTED**********");
        ShiftImpl(data, Radio80211ah::ConvertionDirection::DIRECT);
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "**********BASE BAND DIRECT SHIFT FINISHED**********");
        return _buffer;
    }

    std::vector<std::complex<double>>& BaseBandShifter :: Unshift(const std::vector<std::complex<double>>& data)
    {
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "**********BASE BAND REVERSE SHIFT STARTED**********");
        ShiftImpl(data, Radio80211ah::ConvertionDirection::REVERSE);
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "**********BASE BAND REVERSE SHIFT FINISHED**********");
        return _buffer;
    }

    void BaseBandShifter :: ShiftImpl(const std::vector<std::complex<double>>& data, Radio80211ah::ConvertionDirection direction)
    {
        _buffer.clear();
        _dataCopy.clear();
        _dataCopy.assign(data.begin(), data.end());
        if(Radio80211ah::verboseMode)
        {
            if(direction == Radio80211ah::ConvertionDirection::DIRECT)
                Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "Making frequency shift (forming base band signal from original).");
            else Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "Making frequency shift (forming original signal from base band).");
        }

        if(_dataCopy.empty() || (_dataCopy.size() < Radio80211ah::subcarriersNumber) || (_dataCopy.size() % Radio80211ah::subcarriersNumber != 0))
        {
            Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Error, "Input data is incorrect.");
            return;
        }
        std::vector<std::complex<double>> localBuffer;
        while(1)
        {
            localBuffer.assign( _dataCopy.begin(), _dataCopy.begin() + Radio80211ah::subcarriersNumber);
            _buffer.insert(_buffer.end(), localBuffer.begin() + Radio80211ah::subcarriersNumber / 2, localBuffer.end());
            _buffer.insert(_buffer.end(), localBuffer.begin(), localBuffer.begin() + Radio80211ah::subcarriersNumber / 2);
            std::vector<std::complex<double>>::iterator it = _dataCopy.erase(_dataCopy.begin(), _dataCopy.begin() + Radio80211ah::subcarriersNumber);
            if(it == _dataCopy.end())
                break;
        }
        if(Radio80211ah::verboseMode)
        {
            std::string caption = direction == Radio80211ah::ConvertionDirection::DIRECT ? "[BASE_BAND_DIRECT_SHIFT]": "[BASE_BAND_REVERSE_SHIFT]";
            for(unsigned int counter = 0; counter < _buffer.size(); counter++)
            {
                if(_buffer.size() >= Radio80211ah::subcarriersNumber)
                {
                    // printf stf, ltf, sig and data
                    // todo: umv make smarter scheme
                    if(counter == 0)
                        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, caption + " STF OFDM symbol: ");
                    if(counter == Radio80211ah::subcarriersNumber)
                        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, caption + " LTF OFDM symbol: ");
                    // todo: umv: add SIG symbol
                    if(counter > 63 && counter % Radio80211ah::subcarriersNumber == 0)
                        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, caption + " Data OFDM symbol: ");
                }
                Radio80211ah::LoggerHelper::Clear();
                Radio80211ah::LoggerHelper::AppendStr(caption + " complex value with real: ");
                Radio80211ah::LoggerHelper::AppendDouble(_buffer[counter].real(), 5);
                Radio80211ah::LoggerHelper::AppendStr(" and imaginary: ");
                Radio80211ah::LoggerHelper::AppendDouble(_buffer[counter].imag(), 5);
                Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, Radio80211ah::LoggerHelper::Get());
            }
        }
    }
}
