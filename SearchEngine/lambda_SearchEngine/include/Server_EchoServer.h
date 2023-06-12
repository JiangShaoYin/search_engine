#ifndef __ECHOSERVER_H__
#define __ECHOSERVER_H__

#include <sw/redis++/redis++.h>
#include <unistd.h>

#include <iostream>
#include "Server_Thread.h"
#include "CppJieba.h"
#include "KeyRecommander.h"
#include "Server_TcpConnection.h"
#include "Server_TcpServer.h"
#include "Server_ThreadPool.h"
#include "WebPageSearcher.h"
#include "CacheManager.h"
#include "log4pp.h"

using std::cout;
using std::endl;
using namespace sw::redis;


class MyTask {
public:
    MyTask(const string &msg, const TcpConnectionPtr &con,
           CnDictionary &cndict, EngDictionary &engdict, sw::redis::Redis &redis)
        : _msg(msg), _con(con), _cndcit(cndict), _engdict(engdict), _redis(redis) {
        }

    void process() {
        // 切出msg的前1位int,设为flag
        auto & _currCache = CacheManager::GetInstance(nullptr)->getCache(atoi(name));
        string num = _msg.substr(0, 1);
        int flag = atoi(num.c_str());
        // 剩余内容为search的参数
        string search = _msg.substr(2);
        // 通过flag跳转到不同的类，返回不同的结果:长度+内容
        // 返回Result=flag+搜索结果
        string Result;
        if (1 == flag) {
            auto val = _currCache.get(search);
            logInfo("通过%s号线程查询缓存",name);
            if (!val.empty()) {
                logInfo("关键词缓存已有数据,%s号线程命中缓存",name);
                Result = val;
            } else {
                logInfo("推荐关键词%s为第一次查询",search);
                KeyRecommander Key(search, _con, _cndcit, _engdict);
                Key.doQuery();
                _result = Key.getResult();
                Result.append("1").append(" ").append(_result);
                _currCache.put(search,Result);
            }
        } else {
            auto val = _redis.get(_msg);
            if (val) {
                logInfo("网页缓存已有数据,%s号线程命中缓存",search);
                Result = *val;
            } else {
                logInfo("网页关键词%s为第一次查询",search);
                WebPageSearcher page(search);
                _result = page.doQuery(search);
                Result.append("2").append(" ").append(_result);
                _redis.set(_msg, Result);
            }
        }
        //返回结果给客户端，长度+内容
        _con->sendInLoop(Result);
    }

private:
    string _msg;
    string _result;
    TcpConnectionPtr _con;
    CnDictionary &_cndcit;
    EngDictionary &_engdict;
    Redis &_redis;
};

class EchoServer {
public:
    EchoServer(size_t threadNum, size_t queSize, const string &ip, unsigned short port, CnDictionary &cndict, EngDictionary &engdict)
        : _pool(threadNum, queSize), _server(ip, port), _cndict(cndict), _engdict(engdict), redis("tcp://127.0.0.1:6379") {
        }

    ~EchoServer() {
    }

    void start() {
        _pool.start();  // 子线程会在TaskQueue中取Task，因为现在TaskQueue是空的，所以会调用pop阻塞

        // 将Tcp通信过程中的三个事件注册给了TcpServer，然后交给EventLoop，最后交给TcpConnection
        using namespace std::placeholders;
        _server.setAllCallback(std::bind(&EchoServer::onConnection, this, _1), 
                               std::bind(&EchoServer::onMessage, this, _1), 
                               std::bind(&EchoServer::onClose, this, _1));
        // 让服务器调用ready函数，使得服务器处于监听状态
        // 并且让Reactor/EventLoop进行循环监听(使用epoll_wait进行监听)
        // 监听的文件描述符包括三种：
        // 1、listenfd（有没有新的连接请求过来）
        // 2、evtfd,监听线程池与EventLoop通信的文件描述符,只要被监听，让EventLoop/Reactor
        // 将线程池处理之后的msg发送给客户端
        // 3、connfd，也就是Acceptor类调用accept函数的正确返回结果，如果有可读事件，
        // 就表明客户端发送了数据给了服务器，服务器就可以与客户端进行通信
        _server.start();
    }

    void stop() {
        _pool.stop();
        _server.stop();
    }

    // 连接建立
    void onConnection(const TcpConnectionPtr &con) {
        logInfo("建立连接 %s",con->toString().c_str());
    }

    void onMessage(const TcpConnectionPtr &con) {
        int length = con->receiveInt();
        string msg = con->receive();
        // 处理msg
        // 需要将msg进行处理之后，再将其发送给客户端
        // 就需要做业务逻辑的处理，也就是处理msg
        // 将msg最后的换行符去掉
        msg.pop_back();

        MyTask task(msg, con, _cndict, _engdict, redis);

        // 在执行了push操作，将task放在任务队列里面
        _pool.addTask(std::bind(&MyTask::process, task));
    }

    void onClose(const TcpConnectionPtr &con) {
        logInfo("断开连接 %s",con->toString().c_str());
    }

private:
    ThreadPool _pool;
    TcpServer _server;
    CnDictionary &_cndict;
    EngDictionary &_engdict;
    sw::redis::Redis redis;
};

#endif
