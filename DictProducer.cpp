#include "DictProducer.hh"

DictProducer::DictProducer()  {}

void DictProducer::getTextCn(std::vector<std::string>& words)
{
    for (auto elem : words)
    {
        if (_tempDict.find(elem) != _tempDict.end())
            ++_tempDict[elem];
        else
            _tempDict.insert(std::pair<std::string, int>(elem, 1));
    }
}

void DictProducer::getTextEn(std::vector<std::string>& words, std::vector<std::string>& phrases)
{    
    for (auto elem : words)
    {
        if (_tempDict.find(elem) != _tempDict.end())
            ++_tempDict[elem];
        else
            _tempDict.insert(std::pair<std::string, int>(elem, 1));
    }
    for (auto elem : phrases)
    {
        if (_tempDict.find(elem) != _tempDict.end())
            ++_tempDict[elem];
        else
            _tempDict.insert(std::pair<std::string, int>(elem, 1));
    }
}

void DictProducer::buildDictWithIndexEn()
{
    for (auto elem : _tempDict)
    {
        int index = _dictEn.size();
        _dictEn.push_back(elem);
        std::vector<char> alphas = SplitTool::getInstance().makeAlphas(elem.first);
        for (auto alpha : alphas)
        {
            if (_indexEn.find(std::string(1, alpha)) != _indexEn.end())
                _indexEn[std::string(1, alpha)].insert(index);
            else
                _indexEn.insert(std::pair<std::string, std::set<int>>(std::string(1, alpha), std::set<int>({index})));
        }
    }
    store();
    return;
}

void DictProducer::buildDictWithIndexCn()
{
    for (auto elem : _tempDict)
    {
        int index = _dictCn.size();
        _dictCn.push_back(elem);
        for (auto ch : SplitTool::getInstance().makeCharacterCn(elem.first))
        {
            if (_indexCn.find(ch) != _indexCn.end())
                _indexCn[ch].insert(index);
            else
                _indexCn.insert(std::pair<std::string, std::set<int>>(ch, {index}));
        }
    }
    store();
    return;
}

void DictProducer::store()
{
    std::string dictPathCn = Configuration::getInstance().getDictPathCn();
    std::string indexPathCn = Configuration::getInstance().getIndexPathCn();
    std::string dictPathEn = Configuration::getInstance().getDictPathEn();
    std::string indexPathEn = Configuration::getInstance().getIndexPathEn();
    std::ofstream outFile;

    //write En dict
    outFile.open(dictPathEn);
    std::string errorMsg = "Error opening file for writing: ";
    errorMsg.append(dictPathEn);
    if (!outFile)
        LogERROR(errorMsg);
    for (std::pair<std::string, int> elem : _dictEn)
    {
        outFile << elem.first << " " << elem.second << std::endl;
    }
    outFile.close();

    //write En index
    outFile.open(indexPathEn);
    errorMsg.resize(33);
    errorMsg.append(indexPathEn);
    if(!outFile)
        LogERROR(errorMsg);
    for (auto elem : _indexEn)
    {
        outFile << elem.first;
        for (int i : elem.second)
            outFile << " " << i;
        outFile << "\n";
    }
    outFile.close();

    //write Cn dict
    outFile.open(dictPathCn);
    errorMsg.resize(33);
    errorMsg.append(dictPathCn);
    if (!outFile)
        LogERROR(errorMsg);
    for (auto elem : _dictCn)
        outFile << elem.first << " " << elem.second << std::endl;
    outFile.close();

    //write Cn index
    outFile.open(indexPathCn);
    errorMsg.resize(33);
    errorMsg.append(indexPathCn);
    if (!outFile)
        LogERROR(errorMsg);
    for (auto elem : _indexCn)
    {
        outFile << elem.first;
        for (int i : elem.second)
            outFile << " " << i;
        outFile << "\n";
    }
    outFile.close();
}

void DictProducer::disPlayFilePath()
{
    std::cout << Configuration::getInstance().getDictPathCn() << std::endl;
    std::cout << Configuration::getInstance().getDictPathEn() << std::endl;
    std::cout << Configuration::getInstance().getIndexPathCn() << std::endl;
    std::cout << Configuration::getInstance().getIndexPathEn() << std::endl;
}