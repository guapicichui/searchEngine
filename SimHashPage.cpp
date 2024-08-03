#include "SimHashPage.hh"

SimHashPage::SimHashPage() : _simHasher("simhash/dict/jieba.dict.utf8", "simhash/dict/hmm_model.utf8", 
                             "simhash/dict/idf.utf8", "simhash/dict/stop_words.utf8") {}

void SimHashPage::buildSimhash(std::vector<WebPage> &webPageLib)
{
    uint64_t hash = 0;
    _simhashPageLib.reserve(_simhashPageLib.size() + webPageLib.size());
    for (auto page : webPageLib)
    {
        _simHasher.make(page._title.append(page._abstract), 5, hash);
        _simhashPageLib.push_back(hash);
    }
}

std::vector<WebPage>& SimHashPage::simHashHandle(std::vector<WebPage> &webPageLib)
{
    std::vector<WebPage>::iterator fast = webPageLib.begin(), slow = webPageLib.begin();
    while (fast != webPageLib.end())
    {
        bool flag = true;
        for (auto hash : _simhashPageLib)
        {
            uint64_t pageHash = 0;
            _simHasher.make(fast->_title.append(fast->_abstract), 5, pageHash);
            if (simhash::Simhasher::isEqual(pageHash, hash))
            {
                flag = false;
                fast++;
                break;
            }           
        }
        if (flag)
            *slow++ = *fast++;
    }
    webPageLib.resize(slow - webPageLib.begin());
    buildSimhash(webPageLib);
    return webPageLib;
}