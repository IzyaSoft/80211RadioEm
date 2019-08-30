#include "LtfSymbol.h"

namespace Radio80211ah
{
    LtfSymbol :: LtfSymbol()
    {
        InitLtf();
    }

    void LtfSymbol :: InitLtf()
    {
        _ltf.push_back(std::complex<double>(0, 0));
        _ltf.push_back(std::complex<double>(0, 0));
        _ltf.push_back(std::complex<double>(0, 0));

        _ltf.push_back(std::complex<double>(1, 0));
        _ltf.push_back(std::complex<double>(-1, 0));
        _ltf.push_back(std::complex<double>(1, 0));
        _ltf.push_back(std::complex<double>(-1, 0));

        _ltf.push_back(std::complex<double>(-1, 0));
        _ltf.push_back(std::complex<double>(1, 0));
        _ltf.push_back(std::complex<double>(-1, 0));
        _ltf.push_back(std::complex<double>(1, 0));

        _ltf.push_back(std::complex<double>(1, 0));
        _ltf.push_back(std::complex<double>(-1, 0));
        _ltf.push_back(std::complex<double>(1, 0));
        _ltf.push_back(std::complex<double>(1, 0));
        _ltf.push_back(std::complex<double>(1, 0));

        _ltf.push_back(std::complex<double>(0, 0));   // zero frequency

        _ltf.push_back(std::complex<double>(-1, 0));
        _ltf.push_back(std::complex<double>(-1, 0));
        _ltf.push_back(std::complex<double>(-1, 0));
        _ltf.push_back(std::complex<double>(1, 0));

        _ltf.push_back(std::complex<double>(-1, 0));
        _ltf.push_back(std::complex<double>(-1, 0));
        _ltf.push_back(std::complex<double>(-1, 0));
        _ltf.push_back(std::complex<double>(1, 0));

        _ltf.push_back(std::complex<double>(-1, 0));
        _ltf.push_back(std::complex<double>(1, 0));
        _ltf.push_back(std::complex<double>(1, 0));
        _ltf.push_back(std::complex<double>(1, 0));
        _ltf.push_back(std::complex<double>(-1, 0));

        _ltf.push_back(std::complex<double>(0, 0));
        _ltf.push_back(std::complex<double>(0, 0));
    }
}
