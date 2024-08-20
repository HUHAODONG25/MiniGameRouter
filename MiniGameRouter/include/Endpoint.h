#pragma once
#include <string>
#include <sstream>
#include "message.pb.h"

class Endpoint {
public:
    std::string ip_address = "";  // 地址
    int port = 0;                // 端口号
    std::string svc_name = "";    // 属于哪种服务
    int weight = 0;              // 权重

    // 构造函数
    Endpoint() {};
    Endpoint(std::string service) : svc_name(service) {}
    Endpoint(const std::string& ip, int p, const std::string& service, int w = 1) :
        ip_address(ip), port(p), svc_name(service), weight(w){
    }
    // 重载比较
    bool operator==(const Endpoint& other) const {
        return (ip_address == other.ip_address) && (port == other.port);
    }
    
    // IP地址
    std::string GetAddress() {
        std::string address = ip_address + ":" + std::to_string(port);
        return address;
    }
    void SetAddress(std::string address) {
        std::istringstream iss(address);
        std::getline(iss, ip_address, ':');  // 使用冒号作为分隔符，将IP地址提取出来
        std::string portStr;
        std::getline(iss, portStr);  // 提取冒号后面的端口号部分
        port = std::stoi(portStr);   // 将端口号字符串转换为整数
    }
    // 序列化
    void SerializeToEndpointProto(EndpointProto* endpointProto) const {
        endpointProto->set_ip_address(ip_address);
        endpointProto->set_port(port);
        endpointProto->set_svc_name(svc_name);
        endpointProto->set_weight(weight);
    }

    void ParseFromEndpointProto(const EndpointProto& endpointProto) {
        ip_address = endpointProto.ip_address();
        port = endpointProto.port();
        svc_name = endpointProto.svc_name();
        weight = endpointProto.weight();
    }

    std::string SerializeToString() const {
        EndpointProto endpointProto;
        SerializeToEndpointProto(&endpointProto);
        return endpointProto.SerializeAsString();
    }

    void ParseFromString(const std::string& data) {
        EndpointProto endpointProto;
        endpointProto.ParseFromString(data);
        ParseFromEndpointProto(endpointProto);
    }
};