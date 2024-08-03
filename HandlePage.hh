#ifndef __HANDLEPAGE_HH__
#define __HANDLEPAGE_HH__
#include "DictProducer.hh"
#include "logger.hh"
#include "WebPage.hh"
#include <cmath>

class HandlePage{
private:
    std::unordered_map<std::string, int> _wordsFrequency;
    std::vector<std::unordered_map<std::string, int>> _pageWordsFrequency;
    std::unordered_map<std::string, std::set<std::pair<int, double>>> _invertIndexTable;
    std::vector<std::unordered_map<std::string, double>> _forwardIndexTable;
    DictProducer _dictProducer;
public:
    void computeWordsFrequency(std::vector<WebPage>& webPageLib);
    void buildIndexTable();
    void store();
    
};

#endif