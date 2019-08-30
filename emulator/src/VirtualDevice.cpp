#include <iostream>
#include <iomanip>
#include "VirtualDevice.h"
#include <PhyPdu.h>
#include <MacPdu.h>
#include "LoggerHelper.h"
#include "Logger.h"

namespace Radio80211ah
{
    VirtualDevice::VirtualDevice(): _phyLayer(new PhyPdu()), _macLayer(new MacPdu()) {}

    void VirtualDevice::Execute(Radio80211ah::RadioCommand command)
    {
        std::vector<Radio80211ah::octet> outputData;
        std::vector<Radio80211ah::octet> inputData;
        inputData.assign(command._transmissionContent.begin(), command._transmissionContent.end());
        if(command._round || command._direction == Radio80211ah::ConvertionDirection::DIRECT)
        {
            outputData = Encode(inputData);
            Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Info, "Encoded data: ");
            Radio80211ah::LoggerHelper::Clear();
            Radio80211ah::LoggerHelper::AppendStr("\n\r");
            for (unsigned int octetCounter = 0; octetCounter < outputData.size(); octetCounter++)
            {
                Radio80211ah::LoggerHelper::AppendInt((int)outputData[octetCounter], std::ios::hex|std::ios::showbase);
                Radio80211ah::LoggerHelper::AppendStr(" ");
                if(octetCounter > 0 && (octetCounter + 1) % 8  == 0)
                    Radio80211ah::LoggerHelper::AppendStr("\n\r");
            }
            Radio80211ah::LoggerHelper::AppendStr("\n\r");
            Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Info, Radio80211ah::LoggerHelper::Get());
            Radio80211ah::LoggerHelper::Clear();
        }
        if(command._round || command._direction == Radio80211ah::ConvertionDirection::REVERSE)
        {
            std::vector<Radio80211ah::octet> revertedOutpudData = Decode(outputData);
            std::string outputString;
            outputString.assign(revertedOutpudData.begin(), revertedOutpudData.end());
            Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Info, "Decoded data: ");
            Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Info, outputString);
        }

        if(command._useDevice)
        {
            //todo: umv: add code here 4 real IO
        }
    }

    std::vector<Radio80211ah::octet>& VirtualDevice::Encode(std::vector<Radio80211ah::octet>& dataToEncode)
    {
        std::vector<Radio80211ah::octet> macData;
        macData = _macLayer.get()->EncodePdu(dataToEncode);

        return _phyLayer.get()->EncodePdu(macData);
    }

    std::vector<Radio80211ah::octet>& VirtualDevice::Decode(std::vector<Radio80211ah::octet>& dataToDecode)
    {
        std::vector<Radio80211ah::octet> phyData;
        phyData = _phyLayer.get()->DecodePdu(dataToDecode);

        return _macLayer.get()->DecodePdu(phyData);
    }
}
