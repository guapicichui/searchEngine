#ifndef __DICTPRODUCER_HH_
#define __DICTPRODUCER_HH_
#include "SplitTool.hh" 
#include "Configuration.hh"
#include <fstream>

class DictProducer {
public:
    DictProducer();
    void getTextCn(std::vector<std::string>& words);
    void getTextEn(std::vector<std::string>& words, std::vector<std::string>& phrases);
    void buildDictWithIndexEn();
    void buildDictWithIndexCn();
private:
    void store();
    void disPlayFilePath();
    
private: 
    std::vector<std::pair<std::string, int>> _dictCn;
    std::unordered_map<std::string, std::set<int>> _indexCn;
    std::vector<std::pair<std::string, int>> _dictEn;
    std::unordered_map<std::string, std::set<int>> _indexEn;
    std::unordered_map<std::string, int> _tempDict;
};

#endif //_DICTPRODUCER_H