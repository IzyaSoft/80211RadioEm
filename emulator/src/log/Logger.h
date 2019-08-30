#ifndef LOG_LOGGER_H_
#define LOG_LOGGER_H_

#ifdef COMPILE_WITH_LOG4CPP
#include "log4cpp/Category.hh"
#include "log4cpp/PropertyConfigurator.hh"
#endif

#include <string>

namespace Radio80211ah
{
    enum class LogLevel : unsigned int
    {
        Debug,
        Error,
        Warning,
        Info
    };

    class LoggerWrapper
    {
    public:
        static void Init();
        static void Write(Radio80211ah::LogLevel severity, std::string message);
    private:
    };
}

#endif /* LOG_LOGGER_H_ */
