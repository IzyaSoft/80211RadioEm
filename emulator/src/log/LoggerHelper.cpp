#include "LoggerHelper.h"

namespace Radio80211ah
{
    std::ostringstream LoggerHelper :: _stringBuilder;

    void LoggerHelper :: Place(std::string strVal)
    {
        _stringBuilder.str(strVal);
    }

    void LoggerHelper :: AppendStr(std::string strVal)
    {
        _stringBuilder << strVal;
    }

    //void LoggerHelper :: AppendInt(int intVal, std::ios_base& (*formatFlags)(std::ios_base&))
    void LoggerHelper :: AppendInt(int intVal, std::ios::fmtflags flags)
    {
        _stringBuilder.flags(flags);
        _stringBuilder << intVal;
    }

    void LoggerHelper :: AppendChar(char charVal, std::ios::fmtflags flags)
    {
        _stringBuilder.flags(flags);
        _stringBuilder << (int)charVal;
    }

    void LoggerHelper :: AppendBool(bool logicalVal)
    {
        _stringBuilder << logicalVal;
    }

    void LoggerHelper :: AppendDouble(double floatVal, int precision)
    {
        _stringBuilder.precision(precision);
        _stringBuilder << floatVal;
    }
}
