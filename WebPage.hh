#ifndef _WEBPAGE_HH__
#define _WEBPAGE_HH__
#include "logger.hh"
#include <unordered_map>

enum TEXT_TYPE {ENG, ZHCN};

struct WebPage {
    int _pageId;
    TEXT_TYPE _type;
    std::string _title;
    std::string _url;
    std::string _abstract;
};

#endif //_WEBPAGE_H