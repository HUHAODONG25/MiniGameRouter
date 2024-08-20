#pragma once
#include <zmq.hpp>
#include "Message.h"
#include <vector>
#include <map>
#include <ConsistentHash.h>
#include <fstream>
#include <algorithm>

enum RouteType {
    CONSISTENT_HASH = 1,
    RANDOM = 2,
    WEIGHT = 3,
};

class SideCar {
    Endpoint self_ep;           // 自己的svc
    Endpoint ns_ep;             // namesvr
    zmq::context_t context;     // 上下文
    zmq::socket_t tick_socket;  // 专门接收svr的tick
    zmq::socket_t from_svc;     // 从自己服务来
    zmq::socket_t to_svc;       // 到自己服务去
    zmq::socket_t from_out;     // 从外面来
    zmq::socket_t ns_socket;    // 到NameSvr去，并接收回复
    
    std::map<std::string, std::vector<Endpoint>> svcs;      // key是服务名称，value是对应的端点数组，存储所有服务们
    std::map<std::string, std::vector<int>> prefix_sums;    // 权重的前缀和，可以O(logn)实现权重随机
    std::map<std::string, ConsistentHash> hash_rings;       // 根据配置文件，使用hash的才创建
    std::map<std::string, RouteType> routing_config;        // 获取配置文件内容
    std::map<std::string, std::string> dynamic_config;      // 动态键值，key---IP地址
   
    int from_svc_count = 0;
    int to_svc_count = 0;

public:
    SideCar();
    SideCar(std::string svr_address, std::string route_file, int port);
    bool Init();
    bool Tick();
    bool SvcToOut();
    bool OutToSvc();
    bool Discover(Endpoint sender, Endpoint receiver);
    bool SendByEp(std::string address, const std::string& content);
    bool SendByHash(std::string svc_name, const std::string key, const std::string& content);
    bool SendByRand(std::string svc_name, const std::string& content);
    bool SendByWeight(std::string svc_name, const std::string& content);
    std::string GetDynamic(std::string key);
    
    //----------------------------------------------配置文件处理----------------------------------------------

    std::string& trim(std::string &s) 
    {
        if (s.empty()) 
        {
            return s;
        }
        s.erase(0,s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ") + 1);
        return s;
    }
    /// @brief 根据配置文件获取routing_config
    /// @param configFile 是配置文件名
    /// @return 返回一个map
    std::map<std::string, RouteType> parseConfigFile(const std::string& configFile) {
        std::map<std::string, RouteType> services;

        std::ifstream file(configFile);
        if (!file.is_open()) {
            std::cerr << "Failed to open the file: " << configFile << std::endl;
            return services;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream lineStream(line);
            std::string svc_name, route_type_str;

            if (std::getline(lineStream, svc_name, ',') &&
                std::getline(lineStream, route_type_str, ';')) {
                svc_name = trim(svc_name);
                route_type_str = trim(route_type_str);

                RouteType route_type;
                // String to RouteType
                if (route_type_str == "RANDOM") {
                    route_type = RANDOM;
                } else if (route_type_str == "CONSISTENT_HASH") {
                    route_type = CONSISTENT_HASH;
                } else if (route_type_str == "WEIGHT") {
                    route_type = WEIGHT;
                }
                services[svc_name] = route_type;
            }
        }

        file.close();
        return services;
    }
    
};