#ifndef __CONFIGURATION_HH__
#define __CONFIGURATION_HH__
#include "logger.hh"

class Configuration {
private:
    std::string _webPageDirPathCn;
    std::string _webPageDirPathEn;
    std::string _dictPathEn;
    std::string _dictPathCn;
private:
    Configuration();
public:
    static Configuration& getInstance();
    std::string getDictPathEn();
    std::string getDictPathCn();
    std::string getIndexPathCn();
    std::string getIndexPathEn();
    std::string getWebPageDirPathEn();
    std::string getWebPageDirPathCn();
    std::string getWebPageLibPath();
    std::string getWebPageInvertIndexPath();
    std::string getWebPageForwardIndexPath();
    std::string getWebPageOffsetPath();
};

#endif //_CONFIGURATION_H