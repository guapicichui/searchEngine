#ifndef __HANDLEXML_HH__
#define __HANDLEXML_HH__
#include "WebPage.hh"
#include "tinyxml/tinyxml2.h"
#include "DirScanner.hh"
#include <regex>
#include <fstream>

class HandleXML{
private:
    std::unordered_map<int, std::pair<int, int>> _offsetLib; 
    std::vector<WebPage> _webPageLib;
public: 
    std::vector<WebPage>& makeWebPageLib(std::string fileName, TEXT_TYPE type);
    void storeWebPage();
};

#endif //_PAGELIBPREPROCESSOR_H