#ifndef DATA_OFDMSYMBOLS_H_
#define DATA_OFDMSYMBOLS_H_

namespace Radio80211ah
{
    enum class OfdmSymbols: unsigned int
    {
        STF = 1,
        LTF = 2,
        SID = 3,
        DATA = 4
    };

}

#endif /* DATA_OFDMSYMBOLS_H_ */
