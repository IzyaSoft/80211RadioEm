#include "StfSymbol.h"

namespace Radio80211ah
{
    StfSymbol :: StfSymbol()
    {
        InitStf();
    }

    void StfSymbol :: InitStf()
    {
        _stf.push_back(std::complex<double>(0, 0)); // -16 subcarrier
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(0.5 * _multiplyer, 0.5 * _multiplyer));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(- 1 * _multiplyer, - 1 * _multiplyer));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(1 * _multiplyer, 1 * _multiplyer));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(- 1 * _multiplyer, - 1 * _multiplyer));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(- 1 * _multiplyer, - 1 * _multiplyer));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(- 0.5* _multiplyer, - 0.5 * _multiplyer));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(0, 0));
        _stf.push_back(std::complex<double>(0, 0));
    }
}
