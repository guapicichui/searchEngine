#ifndef _SPLITTOOL_HH__
#define _SPLITTOOL_HH__
#include <vector>
#include <string>
#include "jiebaSingle.hh"
#include "nltk.hh"

class SplitTool{
private:
    SplitTool();
public:
    static SplitTool& getInstance();
    std::vector<std::string>& makeWordsCn(std::string text, std::vector<std::string>& result); //中文词组

    std::vector<std::string>& makeWordsEn(const std::string& text, std::vector<std::string>& result); //英文单词

    std::vector<char> makeAlphas(const std::string& word); //英文字母

    std::vector<std::string>& makePhrasesEn(const std::string& text, std::vector<std::string>& result); //英文短语
    
    std::vector<std::string> makeCharacterCn(const std::string& text); //中文汉字
};

#endif //_SPLITTOOL_H