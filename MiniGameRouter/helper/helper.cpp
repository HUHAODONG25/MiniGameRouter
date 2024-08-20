#include "helper.h"

bool Helper::SendReg() {
    // 设置Message
    Endpoint receiver("Namesvr");
    Message message(self_ep, receiver, REGISTER, "");
    message.SetTimeStamp();
    std::string send_msg = message.SerializeToString();
    // 发送Message
    zmq::message_t messageMsg(send_msg.size());
    memcpy(messageMsg.data(), send_msg.data(), send_msg.size());
    from_svc.send(messageMsg, zmq::send_flags::none);
    return true;
}

bool Helper::SendMsg(Endpoint ep, const std::string& msg, const std::string& key) {
    
    // 设置Message
    Message message(self_ep, ep, NORMAL, msg);
    message.SetKey(key);
    message.SetTimeStamp();
    std::string send_msg = message.SerializeToString();
    // 发送Message
    zmq::message_t messageMsg(send_msg.size());
    memcpy(messageMsg.data(), send_msg.data(), send_msg.size());
    from_svc.send(messageMsg, zmq::send_flags::none);
    // 测试记录时间
    send_count++;
    if(send_count == 1 || send_count == 10000) {
        auto now = std::chrono::system_clock::now();
        auto currentTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        Message m_test;
        std::cout <<"send out "<< send_count << ": "<< m_test.timestampToString(currentTimestamp) << std::endl;
    }
    

    return true;
}


Message Helper::RecvMsg() {
    
    // 接收Message
    zmq::message_t messageMsg;
    to_svc.recv(messageMsg, zmq::recv_flags::none);
    std::string recv_msg(static_cast<char*>(messageMsg.data()), messageMsg.size());
    std::cout <<self_ep.GetAddress()<< "Message size: " << messageMsg.size() << std::endl;
    // 解析Message
    Message message(recv_msg);
    // 测试记录时间
    recv_count++;
    if(recv_count == 2 || recv_count == 10001) {
        auto now = std::chrono::system_clock::now();
        auto currentTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        Message m_test;
        std::cout <<"recv "<< recv_count << ": "<< m_test.timestampToString(currentTimestamp) << std::endl;
    }
    return message;
}

void Helper::SetDynamic(const std::string& key, const std::string& IP, int ttl) {
    // 设置Message
    Endpoint receiver;
    receiver.SetAddress(IP);
    Message message(self_ep, receiver, SET_DYNAMIC, std::to_string(ttl));
    message.SetKey(key);
    message.SetTimeStamp();
    std::string send_msg = message.SerializeToString();
    // 发送Message
    zmq::message_t messageMsg(send_msg.size());
    memcpy(messageMsg.data(), send_msg.data(), send_msg.size());
    from_svc.send(messageMsg, zmq::send_flags::none);
}

void Helper::SendTick() {
    // 设置Message
    Endpoint receiver;
    Message message(self_ep, receiver, TICK, "");
    std::string send_msg = message.SerializeToString();
    
    
    while(true) {
        // 循环发送Message
        zmq::message_t messageMsg(send_msg.size());
        memcpy(messageMsg.data(), send_msg.data(), send_msg.size());
        // 每隔一半ttl就发送
        tick_socket.send(messageMsg, zmq::send_flags::none);
        std::this_thread::sleep_for(std::chrono::seconds(ttl/2));   
    }
}