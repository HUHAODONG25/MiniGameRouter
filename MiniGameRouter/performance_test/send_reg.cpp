
// #include <zmq.hpp>
#include <string>
#include <iostream>
// #include <thread>
// #include <atomic>
// #include <functional>
#include <chrono>
// #include <unistd.h>
// #include "Message.h"
#include "helper.h"


int main(int argc, char* argv[]) {
    std::string port_str = argv[1];
    int port = std::stoi(port_str);
    // 初始化helper
    Helper helper("localhost", port, "A", 1, 2);
    helper.Init();
    Message m_test;
    auto now = std::chrono::system_clock::now();
    auto currentTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    std::cout <<"finish reg"<< m_test.timestampToString(currentTimestamp) << std::endl;
    Endpoint ep;
    ep.SetAddress("localhost:40001");
    helper.SendMsg(ep, "hello");
    // while(true) {
    //     Message m = helper.RecvMsg();
    //     Message m_test;
    //     auto now = std::chrono::system_clock::now();
    //     auto currentTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    //     std::cout << m_test.timestampToString(currentTimestamp) << " " << m.content << std::endl;
    // }
    return 0;
}

