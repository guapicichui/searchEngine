#include "logger.hh"
using namespace log4cpp;

Mylogger * Mylogger::_pInstance = nullptr;
Mylogger::AutoRelease Mylogger::_ar;

Mylogger::AutoRelease::AutoRelease() {}
Mylogger::AutoRelease::~AutoRelease()
{
	Mylogger::destroy();
}

Mylogger::Mylogger()
: _mycat(Category::getRoot().getInstance("--"))
{
    auto ptn1 = new PatternLayout();
    ptn1->setConversionPattern("%d %c [%-5p] %m%n");

    auto ptn2 = new PatternLayout();
    ptn2->setConversionPattern("%d %c [%p] %m%n");

    auto pos = new OstreamAppender("console", &std::cout);
    pos->setLayout(ptn1);

    auto pfile = new RollingFileAppender("LogFile", "pro.log", 1024*1024*100, 4);
    pfile->setLayout(ptn2);

    _mycat.setPriority(Priority::DEBUG);
    _mycat.addAppender(pos);
    _mycat.addAppender(pfile);
}

Mylogger::~Mylogger(){
    Category::shutdown();
}

Mylogger * Mylogger::getInstance(){
    if(nullptr == _pInstance){
        _pInstance = new Mylogger();
    }
    return _pInstance;
}

void Mylogger::destroy(){
    if(_pInstance){
        delete _pInstance;
        _pInstance = nullptr;
		std::cout << "Mylogger::destroy" << std::endl;
    }
}

void Mylogger::warn(const char * msg){
    _mycat.warn(msg);
}

void Mylogger::error(const char * msg){
    _mycat.error(msg);
}

void Mylogger::debug(const char * msg){
    _mycat.debug(msg);
}

void Mylogger::info(const char * msg){
    _mycat.info(msg);
}