#pragma once
#include <cpp_redis/cpp_redis>
#include <zmq.hpp>
#include "../include/Message.h"
#include <chrono>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using TimePoint = std::chrono::time_point<std::chrono::system_clock>;

class NameSvr {
    cpp_redis::client client;           // 用于redis服务注册
    // cpp_redis::subscriber subscriber;   // 用于订阅失活
    int ttl;                            // 服务实例存活时间
    zmq::context_t context;             // 上下文
    zmq::socket_t ns_socket;            // 负责接收消息
    Endpoint self_ep;                   // 自己endpoint
    int tts;                            // 与db同步时间

    //----------实现缓存-----------------

    
    // 上一次和db同步时间
    TimePoint last_sync_time;

    // 服务实例表，二级map，记录每个服务类型有哪些服务实例。 svc_name----address----Endpoint----timestamp
    std::unordered_map<std::string, std::unordered_map<std::string, std::pair<Endpoint, TimePoint>>> services_ep_map;
    std::map<TimePoint, std::unordered_set<std::string>> service_help_map;
    // 服务订阅表，记录有哪些服务依赖该服务                 svc_name----svc_name
    std::unordered_map<std::string, std::unordered_set<std::string>> services_sub_map;
    // 动态键值表                                         key----value----timestamp
    std::unordered_map<std::string, std::pair<std::string, TimePoint>> dynamic_map;
    std::map<TimePoint, std::unordered_set<std::string>> dynamic_help_map;
    // 动态键值订阅表，记录有哪些服务实例订阅了键值          key
    std::unordered_map<std::string, std::unordered_set<std::string>> dynamic_sub_map;
    //---------用于和redis进行增量同步------------------
    std::unordered_map<std::string, std::vector<std::string>> service_ep_add_map;           // svc_name----Endpoints_str
    std::unordered_map<std::string, std::vector<std::string>> service_ep_del_map;           // svc_name----Endpoints_str
    std::unordered_map<std::string, std::vector<std::string>> service_sub_add_map;          // svc_name----svc_names

    std::vector<std::pair<std::string, std::string>> dynamic_value_add_vec;                 // key----value
    std::vector<std::pair<std::string, std::string>> dynamic_time_add_vec;                  // key_time----time_str           
    std::vector<std::string> dynamic_del_vec;                                               // key
    std::unordered_map<std::string, std::vector<std::string>> dynamic_sub_add_map;          // key----Endpoints_str
    std::vector<std::string> dynamic_time_del_vec;                                          // key_time
    std::vector<std::string> dynamic_sub_del_vec;                                           // key_sub
    



public:
    NameSvr(std::string ip_address, int port, int ttl, int tts) : context(1), ns_socket(context, zmq::socket_type::router), self_ep(ip_address, port, "Namesvr", 1), ttl(ttl), tts(tts) {
        client.connect("127.0.0.1", 6379);
        ns_socket.bind("tcp://*:" + std::to_string(port));
        last_sync_time = std::chrono::system_clock::now();
    }
    // 运行
    bool Run();
    bool Tick();
    bool Sync();
    //--------------------实现各类消息发送-------------------
    // 辅助回复消息
    bool SendBack(zmq::message_t &identity, Message message);
    // 同步实例更新消息
    bool SyncUpdateEp(std::vector<std::string> svc_names, Endpoint ep, MessageType m_type);
    bool SyncDelDynamic(std::vector<std::string> addresses, const std::string& key);

    //---------------------服务实例---------------------
    void register_service(const std::string& service_name, Endpoint ep);
    void keep_service_alive(const std::string& service_name, Endpoint ep);
    std::vector<Endpoint> discover_service(const std::string& service_name);
    std::vector<std::string> get_sub_service(const std::string& service_name);    
    void remove_expired_service(const std::string& service_name, Endpoint ep);
    void subscribe_service(const std::string& service_name, const std::string& sub_service_name);
    //--------------------------动态键值-----------------------
    void register_dynamic(const std::string& key, const std::string& value, int d_ttl);
    std::string get_dynamic(const std::string& key);
    void subscribe_dynamic(const std::string& address, const std::string& key);
    std::vector<std::string> get_sub_dynamic(const std::string& key);
    void remove_expired_dynamic(const std::string& key);
    // -----------------------辅助函数---------------------------
    // 将字符串按指定分隔符拆分
    std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(str);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
    // 时间点到string
    std::string time_point_to_string(const std::chrono::time_point<std::chrono::system_clock>& tp) {
        std::time_t time = std::chrono::system_clock::to_time_t(tp);
        std::tm tm = *std::localtime(&time);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
    // string到时间点
    std::chrono::time_point<std::chrono::system_clock> string_to_time_point(const std::string& str) {
        std::istringstream iss(str);
        std::tm tm = {};
        iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
        if (iss.fail()) {
            throw std::runtime_error("Failed to parse time string");
        }
        std::time_t time = std::mktime(&tm);
        return std::chrono::system_clock::from_time_t(time);
    }
};