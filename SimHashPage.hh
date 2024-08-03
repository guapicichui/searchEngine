#ifndef __SIMHASHPAGE_HH__
#define __SIMHASHPAGE_HH__

#define LOGGER_LEVEL LL_WARN 
#include "simhash/Simhasher.hpp"
#include "WebPage.hh"

class SimHashPage{
private:
    simhash::Simhasher _simHasher;
    std::vector<uint64_t> _simhashPageLib;
private:
    void buildSimhash(std::vector<WebPage>& webPageLib);
public:
    SimHashPage();
    std::vector<WebPage>& simHashHandle(std::vector<WebPage>& webPageLib);
};

#endif