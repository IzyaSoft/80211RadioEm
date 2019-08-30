#include <iostream>
#include <algorithm>
#include "ScramblerConvertor.h"
#include "GlobalDefs.h"
#include "Logger.h"
#include "LoggerHelper.h"

namespace Radio80211ah
{

    #define BIT7 0x40
    #define BIT4 0x08
    #define BIT0 0x01
    #define SHIFTED_BIT4 0x10

    ScramblerConvertor :: ScramblerConvertor(Radio80211ah::octet initialState)
    {
        _initialShiftRegisterValue = initialState;
        _shiftRegisterValue = _initialShiftRegisterValue;
        _buffer.reserve(1000);
        if(Radio80211ah::verboseMode)
        {
            Radio80211ah::LoggerHelper::Clear();
            Radio80211ah::LoggerHelper::AppendStr("Initial scrambler value ");
            Radio80211ah::LoggerHelper::AppendInt((int)_shiftRegisterValue, std::ios::hex|std::ios::showbase);
            Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, Radio80211ah::LoggerHelper::Get());
        }
    }

    std::vector<Radio80211ah::octet>& ScramblerConvertor :: Convert(const std::vector<Radio80211ah::octet>& data, Radio80211ah::ConvertionDirection direction)
    {
        if(direction == Radio80211ah::ConvertionDirection::DIRECT)
            return DirectConvert(data);
        return ReverseConvert(data);
    }

    std::vector<Radio80211ah::octet>& ScramblerConvertor :: DirectConvert(const std::vector<Radio80211ah::octet>& data)
    {
        // scrambling
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "********SCRAMBLER STARTED**********");
        _buffer.clear();
        _buffer.reserve(data.size());
        Radio80211ah::octet scramblerValue = _initialShiftRegisterValue;
        Radio80211ah::octet scrambledOctet;
        for(std::vector<Radio80211ah::octet>::const_iterator it = data.begin(); it != data.end(); it++)
        {
            scrambledOctet = 0;
            for(Radio80211ah::octet bitCounter = 0; bitCounter < 8 ; bitCounter++)
            {
                Radio80211ah::octet selectedDataBit = ((*it) & (1 << bitCounter));
                Radio80211ah::octet bitValue = (GetPolynomialValue(scramblerValue) > 0 ? 1: 0) ^ (selectedDataBit > 0 ? 1: 0);
                        //(bool)((*it) & (1 << bitCounter));
                scramblerValue = GetNextScramblerValue(scramblerValue, Radio80211ah::ConvertionDirection::DIRECT);
                if(Radio80211ah::verboseMode)
                {
                    Radio80211ah::LoggerHelper::Clear();
                    Radio80211ah::LoggerHelper::AppendStr("[SCRAMBLER] Selected bit: ");
                    Radio80211ah::LoggerHelper::AppendInt((int)selectedDataBit, std::ios::dec);
                    Radio80211ah::LoggerHelper::AppendStr(" was encoded as: ");
                    Radio80211ah::LoggerHelper::AppendInt((int)bitValue, std::ios::dec);
                    Radio80211ah::LoggerHelper::AppendStr(" next scrambler value: ");
                    Radio80211ah::LoggerHelper::AppendInt((int)scramblerValue, std::ios::dec);
                    Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, Radio80211ah::LoggerHelper::Get());
                }
                scrambledOctet += bitValue << bitCounter;
            }
            _buffer.push_back(scrambledOctet);
        }
        _shiftRegisterValue = scramblerValue;
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "********SCRAMBLER FINISHED**********");
        return _buffer;
    }

    std::vector<Radio80211ah::octet>& ScramblerConvertor :: ReverseConvert(const std::vector<Radio80211ah::octet>& data)
    {
        // descrambling
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug,  "********DESCRAMBLER STARTED**********");
        _buffer.clear();
        _buffer.reserve(data.size());
        Radio80211ah::octet scramblerValue = _initialShiftRegisterValue;
        Radio80211ah::octet descrambledOctet;
        for(std::vector<Radio80211ah::octet>::const_iterator it = data.begin(); it != data.end(); it++)
        {
            descrambledOctet = 0;
            for(Radio80211ah::octet bitCounter = 0; bitCounter < 8 ; bitCounter++)
            {
                //todo: umv: simply copy-past but it could be an issue
                Radio80211ah::octet selectedDataBit = ((*it) & (1 << bitCounter)) > 0 ? 1: 0;
                Radio80211ah::octet bitValue = (GetPolynomialValue(scramblerValue) > 0 ? 1 : 0) ^ (selectedDataBit > 0 ? 1: 0);
                scramblerValue = GetNextScramblerValue(scramblerValue, Radio80211ah::ConvertionDirection::DIRECT);
                descrambledOctet += bitValue << bitCounter;
            }
            _buffer.push_back(descrambledOctet);
            if(Radio80211ah::verboseMode)
            {
                Radio80211ah::LoggerHelper::Clear();
                Radio80211ah::LoggerHelper::AppendStr("[DESCRAMBLER]Descrambled octet ");
                Radio80211ah::LoggerHelper::AppendInt((int)descrambledOctet, std::ios::dec);
                Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, Radio80211ah::LoggerHelper::Get());
            }
        }
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug,  "********DESCRAMBLER FINISHED**********");
        //_shiftRegisterValue = scramblerValue;
       // std::reverse(_buffer.begin(), _buffer.end());
        return _buffer;
    }

    Radio80211ah::octet ScramblerConvertor :: GetNextScramblerValue(Radio80211ah::octet currentShiftRegisterValue, Radio80211ah::ConvertionDirection direction)
    {
        Radio80211ah::octet value = currentShiftRegisterValue;
        if(direction == Radio80211ah::ConvertionDirection::DIRECT)
        {
            Radio80211ah::octet lsb = GetPolynomialValue(currentShiftRegisterValue);
            value <<= 1;
            value += lsb ? 1 : 0;
        }
        else
        {
            Radio80211ah::octet msb = 0;
            if(currentShiftRegisterValue & BIT0)
                msb = (currentShiftRegisterValue & SHIFTED_BIT4) > 0 ? 0 : BIT7;
            else
                msb = (currentShiftRegisterValue & SHIFTED_BIT4) > 0 ? BIT7 : 0;

            value >>= 1;
            value |= msb ? 1 : 0;
        }

        value &= 0x7F;
        return value;
    }

    Radio80211ah::octet ScramblerConvertor :: GetPolynomialValue(Radio80211ah::octet currentShiftRegisterValue)
    {
        return ((currentShiftRegisterValue & BIT4) > 0 ? 1: 0) ^ ((currentShiftRegisterValue & BIT7) > 0 ? 1: 0);
    }

}
