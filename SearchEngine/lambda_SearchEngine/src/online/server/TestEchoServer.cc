#include "../../../include/Server_EchoServer.h"
#include "../../../include/Configuration.h"
#include "../../../include/CppJieba.h"
#include "../../../include/KeyRecommander.h"
#include "../../../include/CnDictionary.h"
#include "../../../include/EngDictionary.h"
#include "../../../include/CppJieba.h"
#include "../../../include/Configuration.h"
#include "../../../include/CacheManager.h"
#include "../../../include/Timerfd.h"
#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

auto conf = Configuration::GetInstance("../../../conf/myconf.conf");
auto _jieba = SplitToolCppJieba::GetInstance(conf.get());
auto _cacheManager = CacheManager::GetInstance(conf.get());
Mylogger * Mylogger::_mylogger = nullptr;

int main(int argc, char **argv)
{
    logInfo("启动TimerFd");
    thread th(timerFd);   
    logInfo("初始化CacheManger");
    _cacheManager->init();
    string ip = conf->getConfigMap("ip");
    int port = stoi(conf->getConfigMap("port"));
    //CPPJIEBA初始化
    //中文英文字典初始化
    logInfo("初始化中文字典");
    CnDictionary cn(conf->getConfigMap("onlinedata"));
    cn.init();
    logInfo("初始化英文字典");
    EngDictionary eng(conf->getConfigMap("onlinedata"));
    eng.init();

    logInfo("初始化服务器");
    EchoServer server(stoi(conf->getConfigMap("THREADNUM")), 10, ip, port,cn,eng);
    logInfo("服务器启动");
    server.start();
    th.join();
    return 0;
}

