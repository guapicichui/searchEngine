#include "HandlePage.hh"

void HandlePage::computeWordsFrequency(std::vector<WebPage> &webPageLib)
{
    std::unordered_map<std::string, int> webPageMap;
    std::vector<std::string> tempWords;
    std::vector<std::string> tempPhrases;
    for (WebPage page : webPageLib)
    {
        tempWords.resize(0);
        tempPhrases.resize(0);

        if (page._type == ENG)
        {
            std::string abstract = page._abstract;
            std::string title = page._title;
            for (auto &ch : abstract)
                if (ch >= 'A' && ch <= 'Z')
                    ch = 'a' - 'A' + ch;
            for (auto &ch : title)
                if (ch >= 'A' && ch <= 'Z')
                    ch = 'a' - 'A' + ch;

            // LogDEBUG(abstract);
            // LogDEBUG(title);
            std::cout << "abstract: " << abstract << std::endl;

            SplitTool::getInstance().makeWordsEn(abstract, tempWords);
            LogDEBUG("abstract make words");

            SplitTool::getInstance().makePhrasesEn(abstract, tempPhrases);
            LogDEBUG("abstract make Phrases");
            SplitTool::getInstance().makeWordsEn(title, tempWords);

            SplitTool::getInstance().makePhrasesEn(title, tempPhrases);
            _dictProducer.getTextEn(tempWords, tempPhrases);

            for (auto word : tempWords)
            {
                if (webPageMap.find(word) != webPageMap.end())
                    ++webPageMap[word];
                else
                    webPageMap.insert(std::pair<std::string, int>(word, 1));
                if (_wordsFrequency.find(word) != _wordsFrequency.end())
                    ++_wordsFrequency[word];
                else
                    _wordsFrequency.insert(std::pair<std::string, int>(word, 1));
            }

            for (auto phrase : tempPhrases)
            {
                if (webPageMap.find(phrase) != webPageMap.end())
                    ++webPageMap[phrase];
                else
                    webPageMap.insert(std::pair<std::string, int>(phrase, 1));
                if (_wordsFrequency.find(phrase) != _wordsFrequency.end())
                    ++_wordsFrequency[phrase];
                else
                    _wordsFrequency.insert(std::pair<std::string, int>(phrase, 1));
            }
            _pageWordsFrequency.push_back(webPageMap);
        }
        else if (page._type == ZHCN)
        {
            std::string abstract = page._abstract;
            std::string title = page._title;

            SplitTool::getInstance().makeWordsCn(abstract, tempWords);
            SplitTool::getInstance().makeWordsCn(title, tempWords);
            _dictProducer.getTextCn(tempWords);

            for (auto word : tempWords)
            {
                if (webPageMap.find(word) != webPageMap.end())
                    ++webPageMap[word];
                else
                    webPageMap.insert(std::pair<std::string, int>(word, 1));
                if (_wordsFrequency.find(word) != _wordsFrequency.end())
                    ++_wordsFrequency[word];
                else
                    _wordsFrequency.insert(std::pair<std::string, int>(word, 1));
            }

            _pageWordsFrequency.push_back(webPageMap);
        }
    }
}

void HandlePage::buildIndexTable()
{
    std::unordered_map<std::string, double> _wordsPageNums;
    _forwardIndexTable.reserve(_pageWordsFrequency.size());
    double TF = 0, IDF = 0;
    double weight = 0;
    for (auto page : _pageWordsFrequency)
    {
        for (auto word : page)
            if (_wordsPageNums.find(word.first) != _wordsPageNums.end())
                ++_wordsPageNums[word.first];
            else
                _wordsPageNums.insert(std::pair<std::string, int>(word.first, 1.0));
    }

    for (int i = 0; i < _pageWordsFrequency.size(); ++i)
    {
        for (auto word : _pageWordsFrequency[i])
        {
            TF = word.second;
            weight = std::log2((double)_pageWordsFrequency.size() + 1 / (_wordsPageNums[word.first] + 1)) * TF;
            if (_invertIndexTable.find(word.first) != _invertIndexTable.end())
                _invertIndexTable[word.first].insert(std::pair<int, double>(i, weight));
            else
                _invertIndexTable.insert(std::pair<std::string, std::set<std::pair<int, double>>>(word.first, {std::pair<int, double>(i, weight)}));
            _forwardIndexTable[i][word.first] = weight;
        }
    }
}

void HandlePage::store()
{
    _dictProducer.buildDictWithIndexCn();
    LogINFO("finish build dict_cn");
    _dictProducer.buildDictWithIndexEn();
    LogINFO("finish build dict_en");

    std::string invertIndexTablePath = Configuration::getInstance().getWebPageInvertIndexPath();
    std::string forwardIndexTablePath = Configuration::getInstance().getWebPageForwardIndexPath();

    std::ofstream ofsInvert(invertIndexTablePath);
    std::ofstream ofsForward(forwardIndexTablePath);
    if (!ofsInvert)
        LogERROR(std::string("open file fail! : ").append(invertIndexTablePath));
    if (!ofsForward)
        LogERROR(std::string("open file fail! : ").append(forwardIndexTablePath));
    
    for (auto [word, _set] : _invertIndexTable)
    {
        ofsInvert << word;
        for (auto pairs : _set)
        {
            ofsInvert << " " << pairs.first << " " << pairs.second;
        }
        ofsInvert << "\n";
    }
    LogINFO("finish make invertIndexTable");
    for (auto page : _forwardIndexTable)
    {
        for (auto pairs : page)
        {
            ofsForward << " " << pairs.first << " " << pairs.second;
        }
        ofsForward << "\n";
    }
    LogINFO("finish make forwardIndexTable");
    ofsForward.close();
    ofsInvert.close();
}
