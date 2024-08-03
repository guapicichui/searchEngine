#include "DirScanner.hh"
DirScanner::DirScanner() {}

DirScanner& DirScanner::getInstance()
{
    static DirScanner dirScanner;
    return dirScanner;
}

std::vector<std::string> DirScanner::getPageFilesPathEn()
{
    std::vector<std::string> pageFilesPathEn;
    // read english XML
    std::string pageDirPathEn = Configuration::getInstance().getWebPageDirPathEn();
    DIR* dir = opendir(pageDirPathEn.c_str());
    std::string errorMsg = "Failed to open directory: ";
    errorMsg.append(pageDirPathEn);
    if (nullptr == dir)
    {
        LogERROR(errorMsg);
        exit(0);
    }    
    struct dirent* pageFileEn;
    while ((pageFileEn = readdir(dir)) != nullptr) {
        std::string fileName = pageFileEn->d_name;

        if (fileName == "." || fileName == ".." || fileName[0] == '.'){
            continue;
        }
        std::string path = Configuration::getInstance().getWebPageDirPathEn();
        pageFilesPathEn.push_back(path.append("/").append(fileName));
    }
    closedir(dir);

    return pageFilesPathEn;
}

std::vector<std::string> DirScanner::getPageFilesPathCn()
{
    std::vector<std::string> pageFilesPathCn;
    // read Chinese XML
    std::string pageDirPathCn = Configuration::getInstance().getWebPageDirPathCn();
    DIR* dir = opendir(pageDirPathCn.c_str());
    std::string errorMsg = "Failed to open directory: ";
    errorMsg.append(pageDirPathCn);
    if (nullptr == dir)
    {
        LogERROR(errorMsg);
    }
    struct dirent* pageFileCn;
    while ((pageFileCn = readdir(dir)) != nullptr)
    {
        std::string fileName = pageFileCn->d_name;
        if (fileName == "." || fileName == ".." || fileName[0] == '.'){
            continue;
        }
        std::string path = Configuration::getInstance().getWebPageDirPathCn();
        pageFilesPathCn.push_back(path.append("/").append(fileName));
    }
    closedir(dir);
    
    return pageFilesPathCn;
}
