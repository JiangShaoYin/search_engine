#include "../../../include/Client.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
using std::string;
using std::stringstream;
using std::vector;

Client::Client(const string &ip, unsigned short port)
    : epfd_(CreateEpollFd())  // 创建epfd文件描述符
      ,sock_(),
      isClosed_(false),
      addr_(ip, port) {
  // 取消输出缓冲
  setbuf(stdout, NULL);
}

Client::~Client() {
  if (!isClosed_) {
    Close();
  }
}

// 连接服务器
void Client::Connect() {
  int ret = ::connect(sock_.fd(), (struct sockaddr *)addr_.GetInetAddrPtr(), sizeof(struct sockaddr));
  if (ret < 0) {
    perror("connect");
    return;
  }
  // socket设置为TCP_NODELAY
  // _sock.setTcpNoDelay(true);
}

void Client::Start() {
  isClosed_ = false;

  Connect();                      // 连接服务器
  TcpConnection con(sock_.fd());  // 创建TcpConnection对象

  // 将连接和标准输入加入epoll监听
  AddEpollReadFd(sock_.fd());
  AddEpollReadFd(STDIN_FILENO);

  printf("\n\n");
  system("toilet --gay -f smblock \"Welcome . Lambda . Group\"");
  printf("\n\n");

  auto startTime = std::chrono::high_resolution_clock::now();
  auto endTime = std::chrono::high_resolution_clock::now();

  struct epoll_event events[2];
  int flag = 1;
  while (!isClosed_) {
    if(flag) {
      cout << "========== 1->关键字 :: 2->网页 :: 3->退出 ==========" << endl;
      cout << "lambda>> ";
      flag = 0;
    }
    // 调用epoll_wait函数，监听epfd上的文件描述符，不设置超时时间
    int nready = epoll_wait(epfd_, events, 2, -1);
    if (nready <= 0) {
      perror("epoll_wait");
      return;
    }
    // cout << "nready : " << nready << endl;
    for (int i = 0; i < nready; ++i) {
      // 如果是标准输入可读
      if (events[i].data.fd == STDIN_FILENO) {
        // cout << "cin is ready" << endl;
        // 从标准输入读取数据
        string msg = ReadStdin();
        // cout << "====================cin msg : " << msg << endl;
        if (msg.size() == 0) {
          // 如果读取到的数据为空，就继续读取
          continue;
        }
        // 处理输入
        // 1. 提取命令，1关键字/2网页/3退出
        int idx = msg.find_first_of(" ");
        string cmd = msg.substr(0, idx);
        if (cmd != "1" && cmd != "2" && cmd != "3") {  // 如果输入的命令不是1/2/3
          cout << "输入错误，请重新输入" << endl;
          continue;
        }
        // 如果是退出命令
        if (cmd == "3") {
          cout << "client close" << endl;
          Close();
          return;
        }
        // 2. 提取查询词
        // 找到queryWord开始位置
        int start = msg.find_first_not_of(" ", idx);
        string queryWord = msg.substr(start, msg.size());
        // 3. 拼接返回值
        string sendmsg;
        sendmsg.append(cmd);
        sendmsg.append(" ");
        sendmsg.append(queryWord);
        sendmsg.append("\n");
        // 杰森事项后期添加
        // 4. 将数据发送给服务器
        // cout << "====================client sendmsg : " << sendmsg << endl;
        SendServer(sendmsg, con);
        cout << "正在查询，请稍后..." << endl;
        // cout << "重新赋值start" << endl;
        startTime = std::chrono::high_resolution_clock::now();
      }

      // 如果是服务器可读
      if (events[i].data.fd == sock_.fd()) {
        // cout << "server is ready" << endl;
        // 1. 从服务器读取数据
        string msg = ReadServer(con);
        // 切出前一个字符，判断flag
        string num = msg.substr(0, 1);
        // 1:key;2:web
        int flag = atoi(num.c_str());
        // json对数据的接收方式不同
        // 1：string;遇见空字符串进行换行
        // 2：struct;换页
        string result = msg.substr(2);
        if (result.size() == 0) {
          cout << "server close" << endl;
          Close();
          return;
        }
        // cout << "重新赋值end" << endl;
        endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        std::cout << "查询耗时" << static_cast<double>(duration.count()) / 1000.0 << " 秒" << std::endl;
        if (1 == flag) {
          DisplayKey(result);
        } else {
          DisplayWeb(result);
        }
        cout << "========== 1->关键字 :: 2->网页 :: 3->退出 ==========" << endl;
        cout << "lambda>> ";
      }
    }
  }
}

// 将文件描述符放在红黑树上进行监听或者从红黑树上摘除
void Client::AddEpollReadFd(int fd) {
  struct epoll_event evt;
  evt.data.fd = fd;
  evt.events = EPOLLIN;

  int ret = ::epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, &evt);
  if (ret < 0) {
    perror("epoll_ctl add");
    return;
  }
}

string Client::ReadStdin() {
  string msg;
  getline(cin, msg);
  return msg;
}

void Client::SendServer(string msg, TcpConnection &con) {
  // 1. 发送数据长度，目前会将换行符也发送过去
  int len = msg.size();
  // cout << "before send len : " << len << endl;  // 测试
  con.SendInt(len);
  // cout << "after send len : " << len << endl;  // 测试
  // 2. 发送数据
  // cout << "before send msg : " << msg << endl;  // 测试
  con.Send(msg);
  // cout << "after send msg : " << msg << endl;  // 测试
}

string Client::ReadServer(TcpConnection &con) {
  // 1. 读取数据长度
  // cout << "before receive len" << endl;  // 测试
  int len = con.ReceiveInt();
  // cout << "after receive len : " << len << endl;  // 测试
  // 2. 读取数据
  // cout << "before receive msg" << endl;  // 测试
  string msg = con.Receive(len);
 // cout << "after receive msg : " << msg << endl;  // 测试
  return msg;
}

void Client::DisplayKey(string result) {
  // 处理json
  auto j = json::parse(result);

 // cout << j << endl;
  vector<string> key = j;
  for (auto &ele : key) {
    if (ele == "") {
      cout << " " << endl;
    } else {
      cout << ele << " ";
    }
  }
}

void from_json(const json &j, Page &w) {
  j.at("id").get_to(w.id);
  j.at("summary").get_to(w.summary);
  j.at("title").get_to(w.title);
  j.at("url").get_to(w.url);
}
void Client::DisplayWeb(string result) {
  if(result == "未查到相关文章！"){
    cout << result << endl;
    return;
  }
  auto j = json::parse(result);
  // 判断是够parse成功
  // if (j.is_discarded()) {
  //   cout << "未查到相关文章！" << endl;
  //   return;
  // }
  vector<Page> page = j.get<vector<Page>>();
  // 分页显示结果
  PagingDisplay(page);
}

// 分页显示结果
void Client::PagingDisplay(vector<Page> &v) {
  int totalPage = v.size() / 5;
  if (v.size() % 5 != 0) {
    totalPage += 1;
  }
  int currentPage = 1;
  bool first = true;
  string input;
  while (true) {
    if (first) {
      first = false;
      input = "1";
    }
    // 如果输入的是q或者是数字，才进入下一步
    if (input == "q" || atoi(input.c_str()) != 0) {
      // 如果输入的是q，退出循环
      if (input == "q") {
        break;
      }
      // 如果输入的是数字，在范围内才进行下一步
      int com = atoi(input.c_str());
      if (com > 0 && com <= totalPage) {
        currentPage = com;
        // 输出当前页的内容
        cout.flush();
        cout << ">>>>>>>>>>>>>>>>当前为第 " << currentPage << " 页, 内容为：<<<<<<<<<<<<<<<<<" << endl;
        int start = (currentPage - 1) * 5;
        int cnt = 1;
        while (cnt <= 5 && start < v.size()) {
          cout << "[" << cnt << "]---------------------------------------------------------" << endl;
          cout << "【title】 " << v[start].title << endl;
          cout << "【url】 " << v[start].url << endl;
          cout << "【summary】 " << v[start].summary << endl;
          start++;
          cnt++;
        }
      } else {
        cout << "输入页面不存在，请重新输入。" << endl;
      }
    } else {
      cout << "输入错误，请重新输入。" << endl;
    }
    // 输出页脚提示信息
    cout << "共 " << totalPage << " 页, 输入 ";
      cout << "[1] - [" << totalPage << "] ";
    cout << "跳转到对应页, 输入 [q] 退出 >> ";
    cin >> input;
    currentPage = atoi(input.c_str());
  }
}

void Client::Close() {
  isClosed_ = true;
}

// 创建epfd文件描述符
int Client::CreateEpollFd() {
  int fd = epoll_create1(0);
  if (fd < 0) {
    perror("epoll_create1");
    return fd;
  }
  return fd;
}
