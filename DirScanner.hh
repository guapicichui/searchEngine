#ifndef _DIRSCANNER_HH_
#define _DIRSCANNER_HH_
#include "logger.hh"
#include "Configuration.hh"
#include <dirent.h> // POSIX 目录操作头文件
#include <sys/types.h> // 类型定义

class DirScanner {
public: 
    static DirScanner& getInstance();
    std::vector<std::string> getPageFilesPathCn();
    std::vector<std::string> getPageFilesPathEn();
private:
    DirScanner();
};

#endif //_DIRSCANNER_H