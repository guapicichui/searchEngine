#include "HandleXML.hh"

void HandleXML::storeWebPage()
{
    const std::string webPagePath = Configuration::getInstance().getWebPageLibPath();
    const std::string webPageIndexPath = Configuration::getInstance().getWebPageOffsetPath();
    
    std::ofstream ofs1(webPagePath, std::ios::out | std::ios::app);
    std::ofstream ofs2(webPageIndexPath, std::ios::out | std::ios::app);

    if (!ofs1)
        LogERROR(std::string("open file fail! : ").append(webPagePath));
    if (!ofs2)
        LogERROR(std::string("open file fail! : ").append(webPageIndexPath));
    for (size_t idx = 0; idx != _webPageLib.size(); ++idx)
    {
        ofs2 << _webPageLib[idx]._pageId << " " << ofs1.tellp() << " ";
        ofs1 << _webPageLib[idx]._pageId
            << " " << _webPageLib[idx]._title
            << " " << _webPageLib[idx]._url
            << " " << _webPageLib[idx]._abstract << "\n";
        ofs2 << ofs1.tellp() << "\n";
    }
    ofs1.close();
    ofs2.close();
    return;
}

std::vector<WebPage> &HandleXML::makeWebPageLib(std::string fileName, TEXT_TYPE type)
{
    std::regex reg("<[^>]+>"); // 通用正则表达式
    tinyxml2::XMLDocument xmlDoc;
    static int count = 0;
    
    _webPageLib.resize(0);
    xmlDoc.LoadFile(fileName.c_str());

    std::string error = "xml doc loadFile fail! Path : ";
    if (xmlDoc.ErrorID())
    {
        std::cout << xmlDoc.ErrorID();
        LogERROR(error.append(fileName));
        exit(1);
    }

    tinyxml2::XMLElement *itemNode = xmlDoc.FirstChildElement("feed")->FirstChildElement("doc");
    while (itemNode)
    {
        WebPage webPage;
        webPage._pageId = count++;
        webPage._type = type;
        if (itemNode->FirstChildElement("title"))
            webPage._title = itemNode->FirstChildElement("title")->GetText();
        else
            LogERROR(std::string("this file has no title : ").append(fileName));

        if (itemNode->FirstChildElement("url"))
            webPage._url = itemNode->FirstChildElement("url")->GetText();
        else
            LogERROR(std::string("this file has no url : ").append(fileName));

        if (itemNode->FirstChildElement("abstract"))
            if (itemNode->FirstChildElement("abstract")->FirstChild() != nullptr)
            {
                webPage._abstract = itemNode->FirstChildElement("abstract")->GetText();
                webPage._abstract = regex_replace(webPage._abstract, reg, "");
            }
            else
                LogERROR(std::string("this file has no abstract child : ").append(fileName));
        else
            LogERROR(std::string("this file has no abstract : ").append(fileName));
        
        // LogERROR(std::string("this Page has finished read: ").append(fileName));
        _webPageLib.push_back(webPage);
        itemNode = itemNode->NextSiblingElement("doc");
    }
    LogDEBUG(std::string("this file finish read : ").append(fileName));
    return _webPageLib;
}