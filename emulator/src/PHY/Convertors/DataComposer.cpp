#include <iostream>
#include <algorithm>
#include "GlobalDefs.h"
#include "DataComposer.h"
#include "Logger.h"
#include "LoggerHelper.h"

namespace Radio80211ah
{
    //todo: umv: add sig
    std::vector<std::complex<double>>& DataComposer :: Compose(const std::vector<std::complex<double>>& data,
                                                               bool insertStf, bool insertLtf, int dataSubcarrier)
    {
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "*********DATA COMPOSER STARTED*********");
        std::vector<std::complex<double>> originalData;
        originalData.assign(data.begin(), data.end());
        _buffer.clear();
        _buffer.reserve(1024);
        // STF
        if(insertStf)
        {
            std::vector<std::complex<double>> stf = _stf.GetStf();
            _buffer.insert(_buffer.end(), stf.begin(), stf.end());
        }

        // LTF
        if(insertLtf)
        {
            std::vector<std::complex<double>> ltf = _ltf.GetLtf();
            _buffer.insert(_buffer.end(), ltf.begin(), ltf.end());
        }

        // insert pilots, spacing, e.t.c
        std::vector<std::complex<double>> dataCopy;
        const int totalDataSubcarriers = 24;

        if(dataSubcarrier >= Radio80211ah::maximumSubcarrierNumber || dataSubcarrier <= Radio80211ah::minimumSubcarrierNumber)
        {
            while(!originalData.empty())
            {
                if(originalData.size() >= totalDataSubcarriers)
                {
                    dataCopy.assign(originalData.begin(), originalData.begin() + totalDataSubcarriers);
                    originalData.erase(originalData.begin(), originalData.begin() + totalDataSubcarriers);
                }
                else
                {
                    dataCopy.assign(originalData.begin(), originalData.end());
                    originalData.erase(originalData.begin(), originalData.end());
                }
                InsertData(dataCopy);
                dataCopy.clear();
            }
        }
        else
        {
            while(!originalData.empty())
            {
                for(int counter = 0; counter < totalDataSubcarriers; counter++)
                    dataCopy.push_back(std::complex<double>(0.0));
                ModifyData(dataCopy);
                dataCopy[16 + dataSubcarrier] = *(data.begin());
                originalData.erase(originalData.begin(), originalData.begin() + 1);
                _buffer.insert(_buffer.end(), dataCopy.begin(), dataCopy.end());
                dataCopy.clear();
            }
        }
        if(Radio80211ah::verboseMode)
        {
            std::cout.precision(5);
            for(unsigned int counter = 0; counter < _buffer.size(); counter++)
            {
                if(_buffer.size() >= Radio80211ah::subcarriersNumber)
                {
                    // printf stf, ltf, sig and data
                    // todo: umv make smarter scheme
                    if(counter == 0)
                        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "[DATA_COMPOSER] STF OFDM symbol: ");
                    if(counter == Radio80211ah::subcarriersNumber)
                        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "[DATA_COMPOSER] LTF OFDM symbol: ");
                    // todo: umv: add SIG symbol
                    if(counter > 63 && counter % Radio80211ah::subcarriersNumber == 0)
                        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "[DATA_COMPOSER] Data OFDM symbol: ");
                }
                Radio80211ah::LoggerHelper::Clear();
                Radio80211ah::LoggerHelper::AppendStr("[DATA_COMPOSER]complex number with real: ");
                Radio80211ah::LoggerHelper::AppendDouble(_buffer[counter].real(), 5);
                Radio80211ah::LoggerHelper::AppendStr(" and imaginary: ");
                Radio80211ah::LoggerHelper::AppendDouble(_buffer[counter].imag(), 5);
                Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, Radio80211ah::LoggerHelper::Get());
            }
        }
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "*********DATA COMPOSER FINISHED*********");
        return _buffer;
    }

    std::vector<std::complex<double>>& DataComposer :: Decompose(const std::vector<std::complex<double>>& data)
    {
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "*********DATA DECOMPOSER STARTED**********");
        std::vector<std::complex<double>> originalData;
        originalData.assign(data.begin(), data.end());
        _buffer.clear();
        std::vector<std::complex<double>>::iterator it;
        // todo: check is first stf, then ltf and then data
        std::vector<std::complex<double>> symbol;
        if(originalData.size() >= Radio80211ah::subcarriersNumber)
        {
            symbol.assign(originalData.begin(), originalData.begin() + Radio80211ah::subcarriersNumber);
            if(Radio80211ah::verboseMode)
                Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "[DATA_DECOMPOSER]Probably STF symbol received! ");
            // we intentionally do not check due to this symbol also could be noisy
            if(Radio80211ah::verboseMode)
            {
                for(unsigned int counter = 0; counter < Radio80211ah::subcarriersNumber; counter++)
                {
                    Radio80211ah::LoggerHelper::Clear();
                    Radio80211ah::LoggerHelper::AppendStr("[DATA_DECOMPOSER]subcarrier index: ");
                    Radio80211ah::LoggerHelper::AppendInt(counter, std::ios::dec);
                    Radio80211ah::LoggerHelper::AppendDouble(symbol[counter].real(), 5);
                    Radio80211ah::LoggerHelper::AppendStr(" and imaginary: ");
                    Radio80211ah::LoggerHelper::AppendDouble(symbol[counter].imag(), 5);
                    Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, Radio80211ah::LoggerHelper::Get());
                }
            }
        }
        else
            Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Warning, "Received less than 32 subcarries, can't detect symbol");
        it = originalData.erase(originalData.begin(), originalData.begin() + Radio80211ah::subcarriersNumber);
        if(it == originalData.end())
            return _buffer;
        symbol.clear();
        if(data.size() >= Radio80211ah::subcarriersNumber)
        {
            symbol.assign(originalData.begin(), originalData.begin() + Radio80211ah::subcarriersNumber);
            if(Radio80211ah::verboseMode)
                Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "[DATA_DECOMPOSER]Probably LTF symbol received! ");
            // we intentionally do not check due to this symbol also could be noisy
            if(Radio80211ah::verboseMode)
            {
                for(unsigned int counter = 0; counter < Radio80211ah::subcarriersNumber; counter++)
                {
                    Radio80211ah::LoggerHelper::Clear();
                    Radio80211ah::LoggerHelper::AppendStr("[DATA_DECOMPOSER]subcarrier index: ");
                    Radio80211ah::LoggerHelper::AppendInt(counter, std::ios::dec);
                    Radio80211ah::LoggerHelper::AppendDouble(symbol[counter].real(), 5);
                    Radio80211ah::LoggerHelper::AppendStr(" and imaginary: ");
                    Radio80211ah::LoggerHelper::AppendDouble(symbol[counter].imag(), 5);
                    Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, Radio80211ah::LoggerHelper::Get());
                }
            }
        }
        originalData.erase(originalData.begin(), originalData.begin() + Radio80211ah::subcarriersNumber);
        if(it == originalData.end())
            return _buffer;
        symbol.clear();
        while(originalData.size() >= Radio80211ah::subcarriersNumber)
        {
            symbol.assign(originalData.begin(), originalData.begin() + Radio80211ah::subcarriersNumber);

            _buffer.insert(_buffer.end(), symbol.begin() + 3,symbol.begin() + 3 + _dataPortion);
            _buffer.insert(_buffer.end(), symbol.begin() + 10, symbol.begin() + 10 + _dataPortion);
            _buffer.insert(_buffer.end(), symbol.begin() + 17, symbol.begin() + 17 + _dataPortion);
            _buffer.insert(_buffer.end(), symbol.begin() + 24, symbol.begin() + 24 + _dataPortion);
            it = originalData.erase(originalData.begin(), originalData.begin() + Radio80211ah::subcarriersNumber);
            if(it == originalData.end())
                break;
            symbol.clear();
        }
        // remove zeroes
        // todo: umv: trash(zeroes) removing depends on constellation type, e.t.c
        it = std::remove_if(_buffer.begin(), _buffer.end(), [](std::complex<double> item){return std::abs(item) <= 0.1;});
        _buffer.erase(it, _buffer.end());
        if(Radio80211ah::verboseMode)
        {
            Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "[DATA_DECOMPOSER]OFDM Data Symbols! ");
            for(unsigned int counter = 0; counter < _buffer.size(); counter++)
            {
                Radio80211ah::LoggerHelper::Clear();
                Radio80211ah::LoggerHelper::AppendStr("[DATA_DECOMPOSER]complex number with real: ");
                Radio80211ah::LoggerHelper::AppendDouble(symbol[counter].real(), 5);
                Radio80211ah::LoggerHelper::AppendStr(" and imaginary: ");
                Radio80211ah::LoggerHelper::AppendDouble(symbol[counter].imag(), 5);
                Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, Radio80211ah::LoggerHelper::Get());
            }
        }
        Radio80211ah::LoggerWrapper::Write(Radio80211ah::LogLevel::Debug, "*********DATA DECOMPOSER FINISHED*********");
        return _buffer;
    }

    void DataComposer :: InsertData(std::vector<std::complex<double>>& data)
    {
        _buffer.push_back(std::complex<double> (0, 0));
        _buffer.push_back(std::complex<double> (0, 0));
        _buffer.push_back(std::complex<double> (0, 0));

        if(data.size() >= _dataPortion)
        {
            _buffer.insert(_buffer.end(), data.begin(), data.begin() + _dataPortion);
            data.erase(data.begin(), data.begin() + _dataPortion);
        }
        else
        {
            int fillerCount = _dataPortion - data.size();
            _buffer.insert(_buffer.end(), data.begin(), data.end());
            data.erase(data.begin(), data.end());
            for(int counter = 0; counter < fillerCount; counter++)
                _buffer.push_back(std::complex<double>(0, 0));
        }

        // pilot insertion
        _buffer.push_back(std::complex<double> (1, 0));
        if(data.size() >= _dataPortion)
        {
            _buffer.insert(_buffer.end(), data.begin(), data.begin() + _dataPortion);
            data.erase(data.begin(), data.begin() + _dataPortion);
        }
        else
        {
            int fillerCount = _dataPortion - data.size();
            _buffer.insert(_buffer.end(), data.begin(), data.end());
            data.erase(data.begin(), data.end());
            for(int counter = 0; counter < fillerCount; counter++)
                _buffer.push_back(std::complex<double>(0, 0));
        }

        _buffer.push_back(std::complex<double> (0, 0));

        if(data.size() >= 6)
        {
            _buffer.insert(_buffer.end(), data.begin(), data.begin() + _dataPortion);
            data.erase(data.begin(), data.begin() + _dataPortion);
        }
        else
        {
            int fillerCount = _dataPortion - data.size();
            _buffer.insert(_buffer.end(), data.begin(), data.end());
            data.erase(data.begin(), data.end());
            for(int counter = 0; counter < fillerCount; counter++)
                _buffer.push_back(std::complex<double>(0, 0));
        }

        // pilot insertion
        _buffer.push_back(std::complex<double> (1, 0));
        if(data.size() >= _dataPortion)
        {
            _buffer.insert(_buffer.end(), data.begin(), data.begin() + _dataPortion);
            data.erase(data.begin(), data.begin() + _dataPortion);
        }
        else
        {
            int fillerCount = _dataPortion - data.size();
            _buffer.insert(_buffer.end(), data.begin(), data.end());
            data.erase(data.begin(), data.end());
            for(int counter = 0; counter < fillerCount; counter++)
                _buffer.push_back(std::complex<double>(0, 0));
        }

        _buffer.push_back(std::complex<double> (0, 0));
        _buffer.push_back(std::complex<double> (0, 0));
    }

    void DataComposer :: ModifyData(std::vector<std::complex<double>>& data)
    {
        std::vector<std::complex<double>> modifiedData;

        modifiedData.push_back(std::complex<double> (0, 0));
        modifiedData.push_back(std::complex<double> (0, 0));
        modifiedData.push_back(std::complex<double> (0, 0));

        if(data.size() >= _dataPortion)
        {
            modifiedData.insert(modifiedData.end(), data.begin(), data.begin() + _dataPortion);
            data.erase(data.begin(), data.begin() + _dataPortion);
        }
        else
        {
            int fillerCount = _dataPortion - data.size();
            modifiedData.insert(modifiedData.end(), data.begin(), data.end());
            data.erase(data.begin(), data.end());
            for(int counter = 0; counter < fillerCount; counter++)
                modifiedData.push_back(std::complex<double>(0, 0));
        }

        // pilot insertion
        modifiedData.push_back(std::complex<double> (1, 0));
        if(data.size() >= _dataPortion)
        {
            modifiedData.insert(modifiedData.end(), data.begin(), data.begin() + _dataPortion);
            data.erase(data.begin(), data.begin() + _dataPortion);
        }
        else
        {
            int fillerCount = _dataPortion - data.size();
            modifiedData.insert(modifiedData.end(), data.begin(), data.end());
            data.erase(data.begin(), data.end());
            for(int counter = 0; counter < fillerCount; counter++)
                modifiedData.push_back(std::complex<double>(0, 0));
        }

        modifiedData.push_back(std::complex<double> (0, 0));

        if(data.size() >= _dataPortion)
        {
            modifiedData.insert(modifiedData.end(), data.begin(), data.begin() + _dataPortion);
            data.erase(data.begin(), data.begin() + _dataPortion);
        }
        else
        {
            int fillerCount = _dataPortion - data.size();
            modifiedData.insert(modifiedData.end(), data.begin(), data.end());
            data.erase(data.begin(), data.end());
            for(int counter = 0; counter < fillerCount; counter++)
                modifiedData.push_back(std::complex<double>(0, 0));
        }

        // pilot insertion
        modifiedData.push_back(std::complex<double> (1, 0));
        if(data.size() >= _dataPortion)
        {
            modifiedData.insert(modifiedData.end(), data.begin(), data.begin() + _dataPortion);
            data.erase(data.begin(), data.begin() + _dataPortion);
        }
        else
        {
            int fillerCount = _dataPortion - data.size();
            modifiedData.insert(modifiedData.end(), data.begin(), data.end());
            data.erase(data.begin(), data.end());
            for(int counter = 0; counter < fillerCount; counter++)
                modifiedData.push_back(std::complex<double>(0, 0));
        }

        modifiedData.push_back(std::complex<double> (0, 0));
        modifiedData.push_back(std::complex<double> (0, 0));

        data.assign(modifiedData.begin(), modifiedData.end());
    }

}
