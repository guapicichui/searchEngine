#include "Configuration.hh"

Configuration::Configuration()
{
    //配置文件读取所有需要的文件路径
}

Configuration& Configuration::getInstance()
{
    static Configuration conFig;
    return conFig;
}

std::string Configuration::getWebPageDirPathEn()
{
    return "./XMLFiles/en";
}

std::string Configuration::getWebPageDirPathCn()
{
    return "./XMLFiles/zh_cn";
}

std::string Configuration::getDictPathEn()
{
    _dictPathEn = "./my_dict/dict_en.dat";
    return _dictPathEn;
}

std::string Configuration::getDictPathCn()
{
    _dictPathCn = "./my_dict/dict_cn.dat";
    return _dictPathCn;
}

std::string Configuration::getIndexPathCn()
{
    return "./my_dict/index_cn.dat";
}
std::string Configuration::getIndexPathEn()
{
    return "./my_dict/index_en.dat";
}

std::string Configuration::getWebPageLibPath()
{
    return "./webPageLib/page_lib.dat";
}

std::string Configuration::getWebPageForwardIndexPath()
{
    return "./webPageLib/page_forward_index.dat";
}

std::string Configuration::getWebPageInvertIndexPath()
{
    return "./webPageLib/page_invert_index.dat";
}

std::string Configuration::getWebPageOffsetPath()
{
    return "./webPageLib/page_offset.dat";
}