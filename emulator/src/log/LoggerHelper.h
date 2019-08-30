#ifndef LOG_LOGGERHELPER_H_
#define LOG_LOGGERHELPER_H_

#include <string>
#include <sstream>

namespace Radio80211ah
{
    class LoggerHelper
    {
    public:
        static void Place(std::string strVal);
        static void AppendStr(std::string strVal);
        //static void AppendInt(int intVal, std::ios_base& (*formatFlags)(std::ios_base&));
        static void AppendInt(int intVal, std::ios::fmtflags flags);
        static void AppendChar(char charVal, std::ios::fmtflags flags);
        static void AppendBool(bool logicalVal);
        static void AppendDouble(double floatVal, int precision);
        static void Clear() {_stringBuilder.str("");}
        static std::string Get() {return _stringBuilder.str();}
    private:
        static std::ostringstream _stringBuilder;
    };
}

#endif /* LOG_LOGGERHELPER_H_ */
