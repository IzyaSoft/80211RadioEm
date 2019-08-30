#include "Logger.h"
#include <iostream>

namespace Radio80211ah
{
    #ifdef COMPILE_WITH_LOG4CPP
        log4cpp::Category* rootCategory;
    #endif

    void LoggerWrapper :: Init()
    {
        std::string initFileName = "log4cpp.properties";
        #ifdef COMPILE_WITH_LOG4CPP
        log4cpp::PropertyConfigurator::configure(initFileName);
        rootCategory = &log4cpp::Category::getRoot();
        #endif
    }

    void LoggerWrapper :: Write(Radio80211ah::LogLevel severity, std::string message)
    {
        #ifdef COMPILE_WITH_LOG4CPP
        switch(severity)
        {
            case Radio80211ah::LogLevel::Debug:
                 rootCategory->debug(message);
                 break;
            case Radio80211ah::LogLevel::Error:
                 rootCategory->error(message);
                 break;
            case Radio80211ah::LogLevel::Warning:
                 rootCategory->warn(message);
                 break;
            case Radio80211ah::LogLevel::Info:
                 rootCategory->info(message);
                 break;
        }
        #else
            std::cout << message <<std::endl;
        #endif
    }
}
