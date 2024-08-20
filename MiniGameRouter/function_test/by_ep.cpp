
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



int count = 0;

std::atomic<bool> running(true);
void to_svc_thread(Helper& helper) {
    while (running) {
        Message message = helper.RecvMsg();
        count++;
        std::cout << message.timestamp <<", " << message.content << ", " << count << std::endl;
    }
}

void from_svc_thread(Helper& helper, std::string recv_address) {
    std::string input;
    Endpoint ep;
    ep.SetAddress(recv_address);
    while (running) {
        std::getline(std::cin, input);
        if(input.size() == 0) {
            continue;
        }
        helper.SendMsg(ep, input);
        if (input == "quit") {
            running = false;
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    // 命令行提供参数
    if (argc < 5) {
        std::cout << "Please provide an integer argument." << std::endl;
        return 1;
    }
    std::string ip = argv[1];
    std::string port_str = argv[2];
    std::string svc_name = argv[3];
    std::string weight_str = argv[4];
    int port = std::stoi(port_str);
    int weight = std::stoi(weight_str);
    // 初始化helper
    Helper helper(ip, port, svc_name, weight, 2);
    helper.Init();
    std::cout << "hello" << std::endl;
    // 输入目的地址
    std::string recv_address;
    std::cin >> recv_address;
    // 创建并启动两个线程
    std::thread input([&helper, recv_address]() {
        from_svc_thread(helper, recv_address);
    });
    std::thread output([&helper]() {
        to_svc_thread(helper);
    });
    // std::thread output(from_svc_thread, helper, recv_address);
    // std::thread input(to_svc_thread, helper);

    // 等待线程完成
    output.join();
    input.join();
    return 0;
}

