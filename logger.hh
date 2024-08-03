#ifndef __logger_HH__
#define __logger_HH__

#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <cstring>   // For strerror
#include <cerrno>    // For errno

#define addPrefix(msg) std::string("[").append(__FILE__)\
        .append(" : ").append(__func__)\
        .append(" : ").append(std::to_string(__LINE__))\
        .append("] ").append("-- MSG: ").append(msg).c_str()

#define LogWarn(msg) Mylogger::getInstance()->warn(addPrefix(msg))
#define LogDEBUG(msg) Mylogger::getInstance()->debug(addPrefix(msg))
#define LogINFO(msg) Mylogger::getInstance()->info(addPrefix(msg))
#define LogERROR(msg) Mylogger::getInstance()->error(addPrefix(msg))

class Mylogger{
    Mylogger(const Mylogger&) = delete;
    Mylogger(Mylogger&&) = delete;
public:
    class AutoRelease{
    public:
        AutoRelease();
        ~AutoRelease();
    };
public:
	void warn(const char *msg);
	void error(const char *msg);
	void debug(const char *msg);
	void info(const char *msg);

    static Mylogger* getInstance();
    static void destroy();

private:
	Mylogger();
	~Mylogger();

private:
    log4cpp::Category & _mycat;
    static Mylogger* _pInstance;
    static AutoRelease _ar;
};

#endif