#pragma once
#include "Endpoint.h"
#include <vector>
#include <chrono>
#include <thread>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

enum MessageType {
    NORMAL = 1,         // 普通消息包
    TICK = 2,           // 心跳包
    REGISTER = 3,       // 服务注册包
    DISCOVER = 4,       // 服务发现包
    ADD = 5,            // 增加服务包
    DELETE = 6,         // 删除服务包
    SET_DYNAMIC = 7,    // 设置动态键值
    GET_DYNAMIC = 8,    // 获取动态键值
    DEL_DYNAMIC = 9,    // 删除动态键值
};


class Message {
public:
    Endpoint sender;      // 发送者是Endpoint
    Endpoint receiver;    // 接收者是Endpoint
    std::string key = "";
    MessageType m_type;   // 消息类型
    std::string content;
    std::string timestamp;

    // 构造函数
    Message() {}
    Message(Endpoint s, Endpoint r, MessageType mt, const std::string& c) : sender(s), receiver(r), m_type(mt), content(c) {
        
    }
    Message(const std::string& data) {
        ParseFromString(data);
    }

    void SetKey(std::string k) { key = k; }
    void SetTimeStamp() {
        // 获取当前时间的时间戳
        auto now = std::chrono::system_clock::now();
        auto time_stamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

        // 将时间戳转换为字符串
        timestamp = timestampToString(time_stamp);
    }
    // 序列化
    void SerializeToMessageProto(MessageProto* messageProto) const {
        sender.SerializeToEndpointProto(messageProto->mutable_sender());
        receiver.SerializeToEndpointProto(messageProto->mutable_receiver());
        messageProto->set_key(key);
        messageProto->set_m_type(static_cast<int>(m_type));
        messageProto->set_content(content);
        messageProto->set_timestamp(timestamp);
    }

    void ParseFromMessageProto(const MessageProto& messageProto) {
        sender.ParseFromEndpointProto(messageProto.sender());
        receiver.ParseFromEndpointProto(messageProto.receiver());
        m_type = static_cast<MessageType>(messageProto.m_type());
        content = messageProto.content();
        timestamp = messageProto.timestamp();
        key = messageProto.key();
    }

    std::string SerializeToString() const {
        MessageProto messageProto;
        SerializeToMessageProto(&messageProto);
        return messageProto.SerializeAsString();
    }

    void ParseFromString(const std::string& data) {
        MessageProto messageProto;
        messageProto.ParseFromString(data);
        ParseFromMessageProto(messageProto);
    }
    
    // Endpoint向量序列化成content
    std::vector<Endpoint> StringToVectorEp() {
        ContentProto content_proto;
        content_proto.ParseFromString(content);
        std::vector<Endpoint> res;
        for(int i = 0; i < content_proto.eps_size(); i++) {
            Endpoint ep;
            ep.ParseFromEndpointProto(content_proto.eps(i));
            res.push_back(ep);
        }
        return res;
    }

    void VectorEpToString(std::vector<Endpoint> eps) {
        ContentProto content_proto;
        for(auto ep : eps) {
            EndpointProto* endpointProto = content_proto.add_eps();
            ep.SerializeToEndpointProto(endpointProto);
        }
        content = content_proto.SerializeAsString();
    }

    // 时间戳转换字符串
    // 将时间戳转换为字符串，保留毫秒级精度
    std::string timestampToString(std::chrono::milliseconds timestamp) {
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(timestamp);
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timestamp - seconds);

        std::time_t time = seconds.count();
        std::tm* tm = std::localtime(&time);
        std::ostringstream oss;
        oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
        oss << '.' << std::setw(3) << std::setfill('0') << milliseconds.count();
        return oss.str();
    }

    // 将字符串转换为时间戳，保留毫秒级精度
    std::chrono::milliseconds stringToTimestamp(const std::string& timeString) {
        std::tm tm = {};
        std::istringstream iss(timeString.substr(0, 19));
        iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

        std::time_t time = std::mktime(&tm);
        auto milliseconds = std::stoi(timeString.substr(20, 3));

        auto duration = std::chrono::seconds(time) + std::chrono::milliseconds(milliseconds);
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    }
};




