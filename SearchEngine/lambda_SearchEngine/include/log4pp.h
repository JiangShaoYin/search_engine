#pragma once
#include <iostream>
#include <string>
#include <log4cpp/SimpleLayout.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>

using namespace std;
#define suffix(msg) std::string(msg).append(" ##")\
        .append(__FILE__).append(":").append(__func__)\
        .append(":").append(int2string(__LINE__))\
        .append("##").c_str()

#define logError(msg, ...) Mylogger::getInstance()->error(suffix(msg),##__VA_ARGS__)
#define logWarn(msg, ...) Mylogger::getInstance()->warn(suffix(msg),##__VA_ARGS__)
#define logInfo(msg, ...) Mylogger::getInstance()->info(suffix(msg),##__VA_ARGS__)
#define logDebug(msg, ...) Mylogger::getInstance()->debug(suffix(msg),##__VA_ARGS__)

inline std::string int2string(int line) {
    std::ostringstream oss;
    oss << line;
    return oss.str();
}

using std::cout;
using std::endl;
using namespace log4cpp;


class Mylogger
{
public:

    template<class...Args>
	void warn(const char * msg,Args...args);

    template<class...Args>
	void error(const char * msg,Args...args);

    template<class...Args>
	void debug(const char * msg,Args...args);

    template<class...Args>
    void info(const char * msg,Args...args);
    

    static Mylogger * getInstance(){
        if (_mylogger == nullptr){
            _mylogger = new Mylogger();
        }
        return _mylogger;
    }

    static void destroy(){
        if (_mylogger){
            _mylogger->_Mylog.info("Mylogger destroy");
            _mylogger->_Mylog.shutdown();
            delete(_mylogger);
            _mylogger = nullptr;
        }
    }
private:
    Mylogger()
    :_Mylog(Category::getRoot())
    {  
        //1、设置日志格式
        PatternLayout *ptn1 = new PatternLayout;
        ptn1->setConversionPattern("%d: %p %c %x:%m%n");

        PatternLayout *ptn2 = new PatternLayout;
        ptn2->setConversionPattern("%d: %p %c %x:%m%n");

        PatternLayout *ptn3 = new PatternLayout;
        ptn3->setConversionPattern("%d: %p %c %x:%m%n");
        
        //2、设置Appender
        auto *os_app = new OstreamAppender("osAppender",&cout);
        os_app->setLayout(ptn1);

        auto *file_app = new FileAppender("fileAppender","../../../log/mylog.log");
        file_app->setLayout(ptn2);

        auto *rollfile_app = new RollingFileAppender("rollfileAppender","../../../log/rollmylog.log",5 * 1024, 5);
        rollfile_app->setLayout(ptn3);
        
        //设置root priority,appender
        _Mylog.setPriority(Priority::DEBUG);
        _Mylog.addAppender(os_app);
        _Mylog.addAppender(file_app);
        _Mylog.addAppender(rollfile_app);
    }
    
private:
    static Mylogger *_mylogger;
    Category &_Mylog;
};


template<class...Args>
void Mylogger::warn(const char * msg,Args...args){
    _Mylog.warn(msg,args...);
}
template<class...Args>
void Mylogger::error(const char * msg,Args...args){
    _Mylog.error(msg,args...);
}
template<class...Args>
void Mylogger::debug(const char * msg,Args...args){
    _Mylog.debug(msg,args...);
}

template<class...Args>
void Mylogger::info(const char * msg,Args...args){
    _Mylog.info(msg,args...);
}

