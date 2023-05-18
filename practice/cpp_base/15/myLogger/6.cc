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

#define addprefix(msg)	string("[").append(__FILE__)\
		  .append(":").append(__FUNCTION__)\
		  .append(":").append(to_string(__LINE__))\
		  .append("] ").append(msg).c_str()
#define LogError(msg, ...) Mylogger::getInstance()->error(addprefix(msg), ##__VA_ARGS__)
#define LogWarn(msg, ...) Mylogger::getInstance()->warn(addprefix(msg), ##__VA_ARGS__)
#define LogInfo(msg, ...) Mylogger::getInstance()->info(addprefix(msg), ##__VA_ARGS__)
#define LogDebug(msg, ...) Mylogger::getInstance()->debug(addprefix(msg), ##__VA_ARGS__)

class Mylogger {
 public:
  template <typename... Args>
  void warn(Args ... args) {
    // 输出可变参数与值
    _logger.warn(args...);
  }
  template <typename... Args>
  void error(Args ... args) {
    _logger.error(args...);
  }
  template <typename... Args>
  void debug(Args ... args) {
    _logger.debug(args...);
  }
  template <typename... Args>
  void info(Args ... args) {
    _logger.info(args...);
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

void test1() {
  printf("hello,world\n");
  int a = 1;
  // 验证 LogInfo, LogDebug, LogError, LogWarn 的可变参数
  LogInfo("hello,world, a = %d", a);
  LogDebug("hello,world, a = %d", a);
  LogWarn("hello,world, a = %d", a);
  LogError("hello,world, a = %d", a);
}

int main() {
  test1();
  return 0;
}
