#include "PageLib.hh"

PageLib::PageLib() {}

void PageLib::create()
{
    std::vector<std::string> filesEn = DirScanner::getInstance().getPageFilesPathEn();
    std::vector<std::string> filesCn = DirScanner::getInstance().getPageFilesPathCn();

    for (auto file : filesEn)
        LogINFO(file);
    for (auto file : filesCn)
        LogINFO(file);
    for (auto file : filesEn)
    {
        std::vector<WebPage>& webPageLib = _handleXML.makeWebPageLib(file, ENG);
        _simHashPage.simHashHandle(webPageLib);
        _handlePage.computeWordsFrequency(webPageLib);
    }

    for (auto file : filesCn)
    {
        std::vector<WebPage>& webPageLib = _handleXML.makeWebPageLib(file, ZHCN);
        _simHashPage.simHashHandle(webPageLib);
        _handlePage.computeWordsFrequency(webPageLib);
    }

    _handlePage.buildIndexTable();
}

void PageLib::store()
{
    _handlePage.store();
    return;
}