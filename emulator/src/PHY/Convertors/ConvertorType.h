#ifndef PHY_CONVERTORS_CONSTELLATIONTYPE_H_
#define PHY_CONVERTORS_CONSTELLATIONTYPE_H_

namespace Radio80211ah
{
    enum class ConvertorType : unsigned int
    {
        PaddingInserter,
        Scrembler,
        Fec,
        BlockRepetition,
        BccInterleaver,
        ConstellationMapper,
        SpatialMapper,
        Idft,
        WindowInserter,
        GuardIntervalInserter
    };
}

#endif /* PHY_CONVERTORS_CONVERTORTYPE_H_ */
