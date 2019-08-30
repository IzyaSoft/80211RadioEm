#include <math.h>
#include <iostream>
#include <algorithm>
#include "ConstellationMapper.h"
#include "Logger.h"
#include "LoggerHelper.h"

namespace Radio80211ah
{
    ConstellationMapper :: ConstellationMapper(Radio80211ah::ConstellationType constellationType)
    {
        _constellationType = constellationType;
        if(Radio80211ah::verboseMode)
        {
            Radio80211ah::LoggerHelper::Clear();
            Radio80211ah::LoggerHelper::AppendStr("Constellation type is: ");
            switch(constellationType)
            {
                case Radio80211ah::ConstellationType::BPSK:
                     Radio80211ah::LoggerHelper::AppendStr("BPSK");
                     break;
                case Radio80211ah::ConstellationType::QPSK:
                     Radio80211ah::LoggerHelper::AppendStr("QPSK");
                     break;
                case Radio80211ah::ConstellationType::QAM16:
                     Radio80211ah::LoggerHelper::AppendStr("QAM16");
                     break;
                case Radio80211ah::ConstellationType::QAM64:
                     Radio80211ah::LoggerHelper::AppendStr("QAM64");
                     break;
                case Radio80211ah::ConstellationType::QAM256:
                     Radio80211ah::LoggerHelper::AppendStr("QAM256");
                     break;
            }
            Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, Radio80211ah::LoggerHelper::Get());
        }
        MapConstellationCodes();
        InitializeBitsPerSymbolValue();
    }

    std::vector<std::complex<double>>& ConstellationMapper :: DirectConvert(const std::vector<Radio80211ah::octet>& data)
    {
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "**********CONSTELLATION MAPPING STARTED***********");
        _symbolsBuffer.clear();
        _symbolsBuffer.reserve((data.size() * 8) / _bitsPerSymbol);
        std::vector<Radio80211ah::octet> threeBytesBuffer;  // for QAM-64 in 3 bytes could be mapped 4 symbols 4 * 6 = 24  = 8 * 3
        threeBytesBuffer.reserve(3);
        for(std::vector<Radio80211ah::octet>::const_iterator it = data.begin(); it != data.end(); it++)
        {
            if(_constellationType != Radio80211ah::ConstellationType::QAM64)
                PutSymbols(*it);
            else
            {
                threeBytesBuffer.push_back(*it);
                if(threeBytesBuffer.size() == 3)
                {
                    PutQam64Symbols(threeBytesBuffer);
                    threeBytesBuffer.clear();
                }
            }
        }

        if(threeBytesBuffer.size() != 0)
            PutQam64Symbols(threeBytesBuffer);
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "**********CONSTELLATION MAPPING* FINISHED**********");
        return _symbolsBuffer;
    }

    std::vector<Radio80211ah::octet>& ConstellationMapper :: ReverseConvert(const std::vector<std::complex<double>>& data)
    {
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "**********CONSTELLATION UNMAPPING STARTED***********");
        _buffer.clear();
        _buffer.reserve((data.size() *_bitsPerSymbol) / 8);
        std::vector<std::complex<double>> dataChunk;
        unsigned int chunkSize = _constellationType != Radio80211ah::ConstellationType::QAM64 ? 8 / _bitsPerSymbol : 4;
        dataChunk.reserve(chunkSize);
        for(std::vector<std::complex<double>>::const_iterator it = data.begin(); it != data.end(); it++)
        {
            dataChunk.push_back(*it);
            if(dataChunk.size() == chunkSize)
            {
                PutBytes(dataChunk);
                dataChunk.clear();
            }
        }
        if(!dataChunk.empty())
            PutBytes(dataChunk);
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "**********CONSTELLATION UNMAPPING FINISHED***********");
        return _buffer;
    }

    void ConstellationMapper :: PutBytes(const std::vector<std::complex<double>>& dataChunk)
    {
        Radio80211ah::octet dataOctet = 0;
        int counter = 0;
        if(_constellationType != Radio80211ah::ConstellationType::QAM64)
        {
            // if non QAM64 we have symbol that assembles in 1 octet
            for(std::vector<std::complex<double>>::const_iterator it = dataChunk.begin(); it != dataChunk.end(); it++)
            {
                Radio80211ah::octet code = GetSymbolBinaryCode(*it);
                code <<= _bitsPerSymbol * counter;
                dataOctet += code;
                counter++;
            }
            _buffer.push_back(dataOctet);
        }
        else
        {
            Radio80211ah::octet remainBits = 0;
            bool firstSymbol = true;
            for(std::vector<std::complex<double>>::const_iterator it = dataChunk.begin(); it != dataChunk.end(); it++)
            {
                Radio80211ah::octet code = GetSymbolBinaryCode(*it);
                if(firstSymbol)
                {
                    remainBits = 8 - _bitsPerSymbol + remainBits;
                    dataOctet += code;
                    firstSymbol = false;
                    continue;
                }
                dataOctet += code << (8 - remainBits);
                _buffer.push_back(dataOctet);
                remainBits = 8 - _bitsPerSymbol + remainBits;
                if(_bitsPerSymbol != remainBits)
                   dataOctet = code & (Radio80211ah::octet)(pow(2, (_bitsPerSymbol - remainBits)));
                else
                {
                    dataOctet += code << (8 - _bitsPerSymbol);
                    _buffer.push_back(dataOctet);
                }
            }
        }
    }

    void ConstellationMapper :: PutSymbols(Radio80211ah::octet dataOctet)
    {
        if(_constellationType != Radio80211ah::ConstellationType::QAM64)
        {
            Radio80211ah::octet slice;
            Radio80211ah::octet mask = (Radio80211ah::octet)(pow(2, _bitsPerSymbol)) - 1;
            if(Radio80211ah::verboseMode)
            {
                Radio80211ah::LoggerHelper::Clear();
                Radio80211ah::LoggerHelper::AppendStr("[CONST_MAPPER] Octet: ");
                Radio80211ah::LoggerHelper::AppendInt((int)dataOctet, std::ios::hex|std::ios::showbase);
                Radio80211ah::LoggerHelper::AppendStr(" was mapped into following points: ");
                Radio80211ah::LoggerHelper::AppendStr("\n\r");
            }

            for (int sliceNumber = 0; sliceNumber < 8 / _bitsPerSymbol; sliceNumber++)
            {
                slice = (dataOctet >> (_bitsPerSymbol * sliceNumber)) & mask;
                std::complex<double> symbol = GetSymbolComplexValue(slice);
                _symbolsBuffer.push_back(symbol);
                if(Radio80211ah::verboseMode)
                {
                    Radio80211ah::LoggerHelper::AppendStr("complex number with real: ");
                    Radio80211ah::LoggerHelper::AppendDouble(symbol.real(), 5);
                    Radio80211ah::LoggerHelper::AppendStr(" and imaginary: ");
                    Radio80211ah::LoggerHelper::AppendDouble(symbol.imag(), 5);
                    Radio80211ah::LoggerHelper::AppendStr("\n\r");
                }
            }
            if(Radio80211ah::verboseMode)
                Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, Radio80211ah::LoggerHelper::Get());
        }
    }

    //todo: umv: add logging when QAM64 will be ready
    void ConstellationMapper :: PutQam64Symbols(const std::vector<Radio80211ah::octet>& threeBytesBuffer)
    {
        Radio80211ah::octet slice;
        Radio80211ah::octet remainBits = 0;
        Radio80211ah::octet remain;
        bool firstSymbol = true;
        for(std::vector<Radio80211ah::octet>::const_iterator it = threeBytesBuffer.begin(); it != threeBytesBuffer.end(); it++)
        {
            if(firstSymbol)
            {
                slice = (*it) & (Radio80211ah::octet)((pow(2, _bitsPerSymbol) - 1));
                remain = (*it) >> _bitsPerSymbol;
                _symbolsBuffer.push_back(GetSymbolComplexValue(slice));
                firstSymbol = false;
            }
            else
            {
                slice = (((*it) << remainBits) & ((Radio80211ah::octet)(pow(2, _bitsPerSymbol)) - 1)) + remain;
                _symbolsBuffer.push_back(GetSymbolComplexValue(slice));
            }

            remainBits = 8 - _bitsPerSymbol + remainBits;
            if(!firstSymbol)
                remain = (*it) >> remainBits;
            //handle 4th byte (remainBits == 6)
            if(remainBits == _bitsPerSymbol)
                _symbolsBuffer.push_back(GetSymbolComplexValue(remain));
        }
    }

    std::complex<double> ConstellationMapper :: GetSymbolComplexValue(Radio80211ah::octet code)
    {
        std::map<Radio80211ah::octet, std::complex<double>> :: iterator it;
        if(_constellationType == Radio80211ah::ConstellationType::BPSK)
            it = _bpskMap.find(code);
        else if(_constellationType == Radio80211ah::ConstellationType::QPSK)
            it = _qpskMap.find(code);
        else if(_constellationType == Radio80211ah::ConstellationType::QAM16)
            it = _qam16Map.find(code);
        else if(_constellationType == Radio80211ah::ConstellationType::QAM64)
            it = _qam64Map.find(code);
        else it = _qam256Map.find(code);
        //todo: umv: potentially unsafe code, we should check iterator validity
        return it->second;
    }

    Radio80211ah::octet ConstellationMapper :: GetSymbolBinaryCode(std::complex<double> symbol)
    {
        Radio80211ah::octet symbolCode = 0;
        std::map<Radio80211ah::octet, std::complex<double>> selectedMap;
        if(_constellationType == Radio80211ah::ConstellationType::BPSK)
            selectedMap = _bpskMap;
        else if(_constellationType == Radio80211ah::ConstellationType::QPSK)
            selectedMap = _qpskMap;
        else if(_constellationType == Radio80211ah::ConstellationType::QAM16)
            selectedMap = _qam16Map;
        else if(_constellationType == Radio80211ah::ConstellationType::QAM64)
            selectedMap = _qam64Map;
        else selectedMap = _qam256Map;

        //double precision = _precision;
        /*std::map<Radio80211ah::octet, std::complex<double>> :: iterator it = std::find_if(selectedMap.begin(), selectedMap.end(),
                                                                                          [symbol, precision](std::pair<Radio80211ah::octet, std::complex<double>> item)
                                                                                          {
                                                                                              return item.second.real() == symbol.real() &&
                                                                                                     item.second.imag() == symbol.imag();
                                                                                          });*/
        std::map<Radio80211ah::octet, std::complex<double>> :: iterator it, foundIt;
        //double reDelta = 1000, imDelta = 1000;
        double moduleDiff = 1000 , angleDiff = 1000;
        for(it = selectedMap.begin(); it != selectedMap.end(); it++)
        {
            if((fabs(std::abs((*it).second) - std::abs(symbol)) <= moduleDiff) && fabs(std::arg((*it).second) - std::arg(symbol)) <= angleDiff)
            {
                moduleDiff = fabs(std::abs((*it).second) - std::abs(symbol));
                angleDiff = fabs(std::arg((*it).second) - std::arg(symbol));
                foundIt = it;
            }
        }

        symbolCode = foundIt->first;
        if(Radio80211ah::verboseMode)
        {
            Radio80211ah::LoggerHelper::Clear();
            Radio80211ah::LoggerHelper::AppendStr("[CONST_UNMAPPER]Complex value with real: ");
            Radio80211ah::LoggerHelper::AppendDouble(symbol.real(), 5);
            Radio80211ah::LoggerHelper::AppendStr(" and imaginary: ");
            Radio80211ah::LoggerHelper::AppendDouble(symbol.imag(), 5);
            Radio80211ah::LoggerHelper::AppendStr(" encoded as ");
            Radio80211ah::LoggerHelper::AppendInt((int)symbolCode, std::ios::hex|std::ios::showbase);
            Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, Radio80211ah::LoggerHelper::Get());
        }
        return symbolCode;
    }

    void ConstellationMapper :: InitializeBitsPerSymbolValue()
    {
        if(_constellationType == Radio80211ah::ConstellationType::BPSK)
            _bitsPerSymbol = 1;
        if(_constellationType == Radio80211ah::ConstellationType::QPSK)
            _bitsPerSymbol = 2;
        if(_constellationType == Radio80211ah::ConstellationType::QAM16)
            _bitsPerSymbol = 4;
        if(_constellationType == Radio80211ah::ConstellationType::QAM64)
            _bitsPerSymbol = 6;
        if(_constellationType == Radio80211ah::ConstellationType::QAM256)
            _bitsPerSymbol = 8;
    }

    void ConstellationMapper :: MapConstellationCodes()
    {
        MapBpsk();
        MapQpsk();
        MapQam16();
        MapQam64();
        MapQam256();
    }

    void ConstellationMapper :: MapBpsk()
    {
        _bpskMap.insert(std::pair<Radio80211ah::octet, std::complex<double>>(0, std::complex<double>(- 1 * _bpskKmod, 0)));
        _bpskMap.insert(std::pair<Radio80211ah::octet, std::complex<double>>(1, std::complex<double>(1 * _bpskKmod, 0)));
    }

    void ConstellationMapper :: MapQpsk()
    {
        _qpskMap.insert(std::pair<Radio80211ah::octet, std::complex<double>>(0, std::complex<double>(- 1 * _qpskKmod, - 1 * _qpskKmod)));
        _qpskMap.insert(std::pair<Radio80211ah::octet, std::complex<double>>(1, std::complex<double>(1 * _qpskKmod, - 1 * _qpskKmod)));
        _qpskMap.insert(std::pair<Radio80211ah::octet, std::complex<double>>(2, std::complex<double>(1 * _qpskKmod, 1 * _qpskKmod)));
        _qpskMap.insert(std::pair<Radio80211ah::octet, std::complex<double>>(3, std::complex<double>(- 1 * _qpskKmod, 1 * _qpskKmod)));
    }

    void ConstellationMapper :: MapQam16()
    {
        _qam16Map.insert(std::pair<Radio80211ah::octet, std::complex<double>>(0, std::complex<double>(-3 * _qam16Kmod, - 3 * _qam16Kmod)));
        _qam16Map.insert(std::pair<Radio80211ah::octet, std::complex<double>>(1, std::complex<double>(3 * _qam16Kmod, - 3 * _qam16Kmod)));
        _qam16Map.insert(std::pair<Radio80211ah::octet, std::complex<double>>(2, std::complex<double>(1 * _qam16Kmod, - 3 * _qam16Kmod)));
        _qam16Map.insert(std::pair<Radio80211ah::octet, std::complex<double>>(3, std::complex<double>(- 1 * _qam16Kmod, - 3 * _qam16Kmod)));

        _qam16Map.insert(std::pair<Radio80211ah::octet, std::complex<double>>(4, std::complex<double>(- 1 * _qam16Kmod, 3 * _qam16Kmod)));
        _qam16Map.insert(std::pair<Radio80211ah::octet, std::complex<double>>(5, std::complex<double>(1 * _qam16Kmod, 3 * _qam16Kmod)));
        _qam16Map.insert(std::pair<Radio80211ah::octet, std::complex<double>>(6, std::complex<double>(3 * _qam16Kmod, 3 * _qam16Kmod)));
        _qam16Map.insert(std::pair<Radio80211ah::octet, std::complex<double>>(7, std::complex<double>(- 3 * _qam16Kmod, 3 * _qam16Kmod)));

        _qam16Map.insert(std::pair<Radio80211ah::octet, std::complex<double>>(8, std::complex<double>(-3 * _qam16Kmod, 1 * _qam16Kmod)));
        _qam16Map.insert(std::pair<Radio80211ah::octet, std::complex<double>>(9, std::complex<double>(3 * _qam16Kmod, 1 * _qam16Kmod)));
        _qam16Map.insert(std::pair<Radio80211ah::octet, std::complex<double>>(10, std::complex<double>(1 * _qam16Kmod, 1 * _qam16Kmod)));
        _qam16Map.insert(std::pair<Radio80211ah::octet, std::complex<double>>(11, std::complex<double>(- 1 * _qam16Kmod, 1 * _qam16Kmod)));\

        _qam16Map.insert(std::pair<Radio80211ah::octet, std::complex<double>>(12, std::complex<double>(- 1 * _qam16Kmod, - 1 * _qam16Kmod)));
        _qam16Map.insert(std::pair<Radio80211ah::octet, std::complex<double>>(13, std::complex<double>(1 * _qam16Kmod, - 1 * _qam16Kmod)));
        _qam16Map.insert(std::pair<Radio80211ah::octet, std::complex<double>>(14, std::complex<double>(3 * _qam16Kmod, - 1 * _qam16Kmod)));
        _qam16Map.insert(std::pair<Radio80211ah::octet, std::complex<double>>(15, std::complex<double>(- 3 * _qam16Kmod, - 1 * _qam16Kmod)));
    }

    void ConstellationMapper :: MapQam64()
    {
        // todo: umv map 64 values
    }

    void ConstellationMapper :: MapQam256()
    {
        // todo: umv map 256 values
    }

}
