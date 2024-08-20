
// #include <zmq.hpp>
#include <string>
#include <iostream>
// #include <thread>
// #include <atomic>
// #include <functional>
// #include <chrono>
// #include <unistd.h>
// #include "Message.h"
#include "helper.h"


int main() {
    // 初始化helper
    Helper helper("localhost", 40001, "B", 1, 2);
    helper.Init();
    std::cout << "hello" << std::endl;
    std::cout << helper.RecvMsg().content <<std::endl;
    std::vector<std::string> contents(10); 
    // 获取开始时间点
    auto start = std::chrono::high_resolution_clock::now();
    int count = 0;
    while (count < 999) {
        Message message = helper.RecvMsg();
        count++;
        std::cout << message.timestamp << " " << message.content << " " <<count << std::endl;
    }
    Message m_test;
    auto now = std::chrono::system_clock::now();
    auto currentTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    std::cout <<"finish discover"<< m_test.timestampToString(currentTimestamp) << std::endl;
    // 获取结束时间点
    auto end = std::chrono::high_resolution_clock::now();

    // 计算持续时间
    std::chrono::duration<double> duration = end - start;

    std::cout << "Elapsed time: " << duration.count() << " seconds" << std::endl;
    
    return 0;
}

