
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


int main() {
    // 初始化helper
    Helper helper("localhost", 41001, "B", 1, 2);
    helper.Init();
    //std::string key = "userid_12345";
    std::string key = "";
    std::string IP = "localhost:50002";
    // helper.SetDynamic(key, IP, 60);
    Endpoint ep;
    ep.svc_name = "A";
    //ep.SetAddress("localhost:50002");
    // 先建立连接
    auto start1 = std::chrono::high_resolution_clock::now();
    helper.SendMsg(ep, "hello", key);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1 - start1;
    std::cout << "Elapsed time: " << duration1.count() << " seconds" << std::endl;
    std::cout << "hello" << std::endl;
    std::string s;
    std::cin >> s;
    // 获取开始时间点
    auto start = std::chrono::high_resolution_clock::now();
    Message m_test;
    
    auto now = std::chrono::system_clock::now();
    auto currentTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    std::cout << "real start time"<<m_test.timestampToString(currentTimestamp) << std::endl; 
    for(int i = 0; i < 10000; i++) {
        helper.SendMsg(ep, "hello", key);
        std::this_thread::sleep_for(std::chrono::microseconds(150));  // 控制发送速率
    }
     // 获取结束时间点
    auto end = std::chrono::high_resolution_clock::now();

    // 计算持续时间
    std::chrono::duration<double> duration = end - start;

    std::cout << "Elapsed time: " << duration.count() << " seconds" << std::endl;
    return 0;
}

