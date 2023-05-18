#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/RollingFileAppender.hh>
#include "log4cpp/FileAppender.hh"
using namespace std;
using namespace log4cpp;

#define PRE ("FILE: " + string(__FILE__) + " FUNCTION: " + string(__FUNCTION__) + " LINE: " +to_string(__LINE__))


class Mylogger {
 public:
  void warn(const char *msg) {
    _logger.warn(msg);
  }
  void error(const char *msg) {
    _logger.error(msg);
  }
  void debug(const char *msg) {
    _logger.debug(msg);
  }
  void info(const char *msg) {
    _logger.info(msg);
  }
  void fatal(const char *msg) {
    _logger.fatal(msg);
  }
  void crit(const char *msg) {
    _logger.crit(msg);
  }
  static Mylogger *getInstance() {
    if (_pInstance == nullptr) {
      _pInstance = new Mylogger();
    }
    return _pInstance;
  }

 private:
  Mylogger() {
    cout << "Mylogger()" << endl;
    init();
  }
  ~Mylogger() {
    cout << "~Mylogger()" << endl;
  }

  void init() {
    PatternLayout *ptn1 = new PatternLayout();
    ptn1->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ptn2 = new PatternLayout();
    ptn2->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ptn3 = new PatternLayout();
    ptn3->setConversionPattern("%d %c [%p] %m%n");

    OstreamAppender *oApp = new OstreamAppender("testOut", &cout);
    oApp->setLayout(ptn1);
    FileAppender *fApp = new FileAppender("testFile", "file.log");
    fApp->setLayout(ptn2);
    RollingFileAppender *rApp = new RollingFileAppender("testRoll", "roll.log", 1 * 1024, 2);
    rApp->setLayout(ptn3);

    _logger.setAppender(oApp);
    _logger.setAppender(fApp);
    _logger.setAppender(rApp);
    _logger.setPriority(Priority::DEBUG);
  }

 private:
  static Mylogger *_pInstance;
  Category &_logger = Category::getRoot();
};

Mylogger *Mylogger::_pInstance = nullptr;

void test0() {
  // 第一步，完成单例模式的写法
  Mylogger *log = Mylogger::getInstance();

  log->info("The log is info message");
  log->error("The log is error message");
  log->fatal("The log is fatal message");
  log->crit("The log is crit message");
}

void LogInfo(string s) {
  Mylogger *log = Mylogger::getInstance();
  log->info(s.c_str());
}
void LogError(string s) {
  Mylogger *log = Mylogger::getInstance();
  log->error(s.c_str());
}
void LogWarn(string s) {
  Mylogger *log = Mylogger::getInstance();
  log->warn(s.c_str());
}
void LogDebug(string s) {
  Mylogger *log = Mylogger::getInstance();
  log->debug(s.c_str());
}

void test1() {
  printf("hello,world\n");
  // 第二步，像使用printf一样
  // 只要求能输出纯字符串信息即可，不需要做到格式化输出
  LogInfo(PRE + "The log is info message");
  LogError(PRE + "The log is error message");
  LogWarn(PRE + "The log is warn message");
  LogDebug(PRE + "The log is debug message");
}

int main() {
  // test0();
  test1();
  return 0;
}
