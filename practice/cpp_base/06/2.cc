#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/BasicLayout.hh>
#include "log4cpp/FileAppender.hh"
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
using namespace std;
using namespace log4cpp;

int main(){
    OstreamAppender *oApp = new OstreamAppender("testOut", &cout);
    oApp->setLayout(new BasicLayout());
    FileAppender *fApp = new FileAppender("testFile","file.log");
    fApp->setLayout(new BasicLayout());
    RollingFileAppender *rApp = new RollingFileAppender("testRoll","roll.log",1*1024, 2);
    rApp->setLayout(new BasicLayout());

    Category & cat = Category::getRoot();
    cat.setAppender(oApp);
    // cat.setAppender(fApp);
    cat.setAppender(rApp);
    cat.setPriority(Priority::INFO);
    for(int i = 0; i < 1000; i ++){
        cat.debug("this is debug");
        cat.info("this is info");
        cat.notice("this is notic");
        cat.error("this is error");
        cat.emerg("this is emerg");
    }
    return 0;
}

