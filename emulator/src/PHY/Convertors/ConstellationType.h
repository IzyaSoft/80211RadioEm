#ifndef PHY_CONVERTORS_CONVERTORTYPE_H_
#define PHY_CONVERTORS_CONVERTORTYPE_H_

namespace Radio80211ah
{
    enum class ConstellationType : unsigned int
    {
        BPSK = 1,
        QPSK = 2,
        QAM16 = 3,
        QAM64 = 4,
        QAM256 = 5
    };
}

#endif /* PHY_CONVERTORS_CONVERTORTYPE_H_ */
