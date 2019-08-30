#ifndef CONFIGURATION_CONFIGURATIONKEYS_H_
#define CONFIGURATION_CONFIGURATIONKEYS_H_

namespace Radio80211ah
{
    // common options
    #define HELP_LONG "--help"
    #define HELP_SHORT "-h"
    #define VERSION_LONG "--version"
    #define VERSION_SHORT "-v"
    #define VERBOSE_LONG "--verbose"
    #define VERBOSE_SHORT "-vv"
    //#define LOGFILE_LONG "--logfile"
    // mode option
    #define INTERACTIVE_MODE_LONG "--interactive"
    #define INTERACTIVE_MODE_SHORT "-ia"
    // io plus settings options
    #define TRANSMIT_VIA_DEVICE_LONG "--device"
    #define TRANSMIT_VIA_DEVICE_SHORT "-d"
    #define TRANSMIT_SYMBOLS_LONG "--symbols"
    #define TRANSMIT_SYMBOLS_SHORT "-sb"
    #define CONVERT_LINE_LONG "--line"
    #define CONVERT_LINE_SHORT "-l"
    #define CONVERT_FILE_LONG "--file"
    #define CONVERT_FILE_SHORT "-f"
    #define CONVERT_DIRECT_LONG "--direct"
    #define CONVERT_DIRECT_SHORT "-dr"
    #define CONVERT_REVERSE_LONG "--reverse"
    #define CONVERT_REVERSE_SHORT "-rv"
    #define CONVERT_ROUND_LONG "--round"
    #define USE_SUBCARRIER_LONG "--subcarrier"
    #define USE_SUBCARRIER_SHORT "-sc"
    #define REPEAT_TRANSMISSION_LONG "--repeat"
    #define REPEAT_TRANSMISSION_SHORT "-r"
}

#endif /* CONFIGURATION_CONFIGURATIONKEYS_H_ */
