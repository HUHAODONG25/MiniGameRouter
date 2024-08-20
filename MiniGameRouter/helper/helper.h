#include <zmq.hpp>
#include <string>
#include <iostream>
#include <thread>
#include <atomic>
#include <functional>
#include "../include/Message.h"


class Helper {
    zmq::context_t context;
    zmq::socket_t from_svc;     // 从服务push到sidecar
    zmq::socket_t to_svc;       // 从sidecar pull到服务
    zmq::socket_t tick_socket;  // 专门用于tick
    Endpoint self_ep;
    int ttl;                    // 保活时间
    std::thread tick_thread;
    std::atomic<bool> running;

    int send_count = 0;
    int recv_count = 0;

public:
    Helper() {}
    Helper(std::string ip_address, int port, std::string svc_name, int weight, int t) : context(1), ttl(t), to_svc(context, zmq::socket_type::pull), \
                                                                                 from_svc(context, zmq::socket_type::push), \
                                                                                 tick_socket(context, zmq::socket_type::push), \
                                                                                 self_ep(ip_address, port, svc_name, weight){
        // 设置发送高水位标记
        int sndhwm = 1000;
        from_svc.set(zmq::sockopt::sndhwm, sndhwm);
        // 设置最大消息大小
        int64_t max_msg_size = 1024 * 1024;  // 1 MB
        from_svc.set(zmq::sockopt::maxmsgsize, max_msg_size);


        to_svc.bind("ipc:///tmp/to_svc_" + std::to_string(port));
        from_svc.connect("ipc:///tmp/from_svc_" + std::to_string(port));
        tick_socket.connect("ipc:///tmp/tick_" + std::to_string(port));
        running = true;
    }
    ~Helper() {
        running = false;
        tick_thread.join();
    }
    void Init() {
        // 发送注册包
        auto now = std::chrono::system_clock::now();
        auto currentTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        Message m_test;
        std::cout << m_test.timestampToString(currentTimestamp) << self_ep.GetAddress()<<" start init" << std::endl;
        SendReg();
        // 接收注册结果
        Message message = RecvMsg();
        // 发送注册包
        auto now2 = std::chrono::system_clock::now();
        auto currentTimestamp2 = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        std::cout << m_test.timestampToString(currentTimestamp2) << self_ep.GetAddress()<<" " << message.content <<std::endl;
        // std::cout << message.content << std::endl;
        // 另外开一个线程，发送心跳包
        std::cout << "start tick_thread" << std::endl;
        tick_thread = std::thread(&Helper::SendTick, this);

    }
    bool SendReg();
    bool SendMsg(Endpoint ep, const std::string& msg,const std::string& key = "");
    void SetDynamic(const std::string& key, const std::string& IP, int ttl);
    void SendTick();
    Message RecvMsg();
};