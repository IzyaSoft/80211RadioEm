#ifndef GLOBALDEFS_H_
#define GLOBALDEFS_H_

#include <string>

namespace Radio80211ah
{
    extern std::string emulatorVersion;
    extern bool verboseMode;
    const int minimumSubcarrierNumber = -16;
    const int maximumSubcarrierNumber =  15;
    const unsigned int subcarriersNumber = 32;

    const std::string convertCommand = "convert";
    const std::string sendCommand = "send";
    const std::string useDevice = "use-device";
    const std::string helpCommand = "help";

    const std::string consoleDevice = "console";
    const std::string usbDevice = "usb";
}

#endif /* GLOBALDEFS_H_ */
