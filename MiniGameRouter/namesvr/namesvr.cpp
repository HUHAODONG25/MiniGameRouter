#include "namesvr.h"


bool NameSvr::Run() {

    // 接收标识符
    zmq::message_t identity;
    ns_socket.recv(identity, zmq::recv_flags::dontwait);
    if(identity.size() == 0) {
        return false;
    }
    // 接收实际消息
    zmq::message_t messageMsg;
    ns_socket.recv(messageMsg, zmq::recv_flags::none);
    if(messageMsg.size() == 0) {
        return true;
    }
    std::string m(static_cast<char*>(messageMsg.data()), messageMsg.size());
    Message message(m);
    
    

    // 处理消息    
    if(message.m_type == REGISTER) {                    // 服务注册，有回复消息
        // 从消息中获取服务名称
        std::string service_name = message.sender.svc_name;
        Message res_message(self_ep, message.sender, REGISTER,"");
        // 服务注册
        register_service(service_name, message.sender);
        // 获取订阅该服务的服务
        std::vector<std::string> svc_names = get_sub_service(service_name);
        // 同步服务更新
        SyncUpdateEp(svc_names, message.sender, ADD);
        // 设置回复消息
        res_message.content = "Successfully Registered";
        
        // 回复消息
        SendBack(identity, res_message);
        return true;
    } else if(message.m_type == DISCOVER) {             // 服务发现， 有回复消息
        // 从消息中获取服务名称
        std::string service_name = message.content;
        Message res_message(self_ep, message.sender, DISCOVER,"");
        // 根据的服务类型，订阅服务
        subscribe_service(message.sender.svc_name, message.content);
        std::cout << service_name <<std::endl;
        // 服务发现
        std::vector<Endpoint> eps = discover_service(service_name);
        std::cout << eps[0].GetAddress() << std::endl;
        // 把实例vector序列化
        res_message.VectorEpToString(eps);
        // 回复消息
        std::cout << "send back discover " << eps.size() << std::endl;
        SendBack(identity, res_message);
        return true;
    } else if(message.m_type == TICK) {                 // 服务保活，无回复消息
        // 从消息中获取服务名称
        std::string service_name = message.sender.svc_name;
        keep_service_alive(service_name, message.sender);
    } else if(message.m_type == SET_DYNAMIC) {          // 动态键值注册，无回复消息
        std::string key = message.key;
        std::string cur_value = get_dynamic(key);
        if(cur_value.size() == 0) {                     // 如果键值不存在，则可以set
            std::string IP = message.receiver.GetAddress();
            int ttl = std::stoi(message.content);
            register_dynamic(key, IP, ttl);
            subscribe_dynamic(message.sender.GetAddress(), key);
        } else {                                        // 如果键值存在，就不可以更改
            // Message res_message(self_ep, message.sender, SET_DYNAMIC, "Set Dynamic failed, the key already exist");
            // SendBack(identity, res_message);
        }
        
    } else if(message.m_type == GET_DYNAMIC) {          // sidecar请求动态键值，有回复消息
        std::string IP = get_dynamic(message.key);
        subscribe_dynamic(message.sender.GetAddress(), message.key);
        Message res_message(self_ep, message.sender, GET_DYNAMIC, IP);
        SendBack(identity, res_message);
    }
    return true;
}

bool NameSvr::Tick() {
    TimePoint cur_time = std::chrono::system_clock::now();
    // 删除过期实例
    while(!service_help_map.empty() && service_help_map.begin()->first < cur_time) {
        std::cout << "Tick1" << std::endl;
        std::unordered_set<std::string> eps_strs = service_help_map.begin()->second;
        service_help_map.erase(service_help_map.begin());
        for(auto ep_str : eps_strs) {
            Endpoint ep;
            ep.ParseFromString(ep_str);
            std::string svc_name = ep.svc_name;
            // 同步更新给服务
            std::vector<std::string> sub_svc_names = get_sub_service(svc_name);
            std::cout << "sub_svc_name: " << sub_svc_names.size() << std::endl;
            SyncUpdateEp(sub_svc_names, ep, DELETE);
            // 在缓存中删除
            remove_expired_service(svc_name, ep);
        }
    }
    // 删除过期动态键值
    while(!dynamic_help_map.empty() && dynamic_help_map.begin()->first < cur_time) {
        std::unordered_set<std::string> keys = dynamic_help_map.begin()->second;
        dynamic_help_map.erase(dynamic_help_map.begin());
        for(auto key : keys) {
            // 同步更新给服务
            std::vector<std::string> sub_addresses = get_sub_dynamic(key);
            SyncDelDynamic(sub_addresses, key);
            // 在缓存中删除
            remove_expired_dynamic(key);
        }
    }
    return true;
}

bool NameSvr::Sync() {
    TimePoint cur_t = std::chrono::system_clock::now();
    if(cur_t < last_sync_time + std::chrono::seconds(tts)) {
        return false;
    }
    
    std::cout << "sync with redis" << std::endl;
    // 增加服务实例
    for(auto it : service_ep_add_map) {
        client.sadd(it.first, it.second);
    }
    service_ep_add_map.clear();
    // 增加订阅服务
    for(auto it : service_sub_add_map) {
        client.sadd(it.first, it.second);
    }
    service_sub_add_map.clear();
    // 删除服务实例
    for(auto it : service_ep_del_map) {
        client.srem(it.first, it.second);
    }
    service_ep_del_map.clear();

    // 增加动态键值
    client.mset(dynamic_value_add_vec);
    dynamic_value_add_vec.clear();
    // 增加动态键值时间
    client.mset(dynamic_time_add_vec);
    dynamic_time_add_vec.clear();
    // 增加动态键值订阅
    for(auto it : dynamic_sub_add_map) {
        client.sadd(it.first, it.second);
    }
    dynamic_sub_add_map.clear();
    // 删除动态键值
    client.del(dynamic_del_vec);
    dynamic_del_vec.clear();
    // 删除动态键值时间
    client.del(dynamic_time_del_vec);
    dynamic_time_del_vec.clear();
    // 删除动态键值订阅
    client.del(dynamic_sub_del_vec);
    dynamic_sub_del_vec.clear();
    
    // 重新设置同步时间
    last_sync_time = std::chrono::system_clock::now();

    // 异步提交
    client.commit();
    
    return true;
}
//--------------------发送消息--------------
// 回复
bool NameSvr::SendBack(zmq::message_t &identity, Message message) {
    // 序列化回复消息
    std::string res_msg = message.SerializeToString();
    zmq::message_t res_messageMsg(res_msg.size());
    memcpy(res_messageMsg.data(), res_msg.data(), res_msg.size());
    
    // 发送响应
    ns_socket.send(identity, zmq::send_flags::sndmore);
    ns_socket.send(res_messageMsg, zmq::send_flags::none);
    return true;
}
// 同步更新节点
bool NameSvr::SyncUpdateEp(std::vector<std::string> svc_names, Endpoint ep, MessageType m_type) {
    std::cout << "sync update to eps" << std::endl;
    std::string ep_str = ep.SerializeToString();
    for(auto svc : svc_names) {
        std::vector<Endpoint> recv_eps = discover_service(svc);
        for(auto recv_ep : recv_eps) {
            // 设置message
            Message message(self_ep, recv_ep, m_type, ep_str);
            // 设置连接socket
            zmq::socket_t sender(context, zmq::socket_type::push);
            sender.connect("tcp://" + recv_ep.GetAddress());
            // 序列化
            std::string msg = message.SerializeToString();
            zmq::message_t messageMsg(msg.size());
            memcpy(messageMsg.data(), msg.data(), msg.size());
            // 发送
            sender.send(messageMsg, zmq::send_flags::dontwait);
            // 关闭套接字
            sender.close();
        }
    }
    return true;
}
// 同步删除动态键值
bool NameSvr::SyncDelDynamic(std::vector<std::string> addresses, const std::string& key) {
    std::cout << "sync delete dynamic" << std::endl;
    for(auto IP : addresses) {
        // 获取recv_ep
        Endpoint recv_ep;
        recv_ep.SetAddress(IP);
        // 设置message
        Message message(self_ep, recv_ep, DEL_DYNAMIC, "");
        message.SetKey(key);
        // 设置连接socket
        zmq::socket_t sender(context, zmq::socket_type::push);
        sender.connect("tcp://" + recv_ep.GetAddress());
        // 序列化
        std::string msg = message.SerializeToString();
        zmq::message_t messageMsg(msg.size());
        memcpy(messageMsg.data(), msg.data(), msg.size());
        // 发送
        sender.send(messageMsg, zmq::send_flags::dontwait);
        // 关闭套接字
        sender.close();
    }
    return true;
}
//----------------------实现缓存操作--------------------
// 服务注册
void NameSvr::register_service(const std::string& service_name, Endpoint ep) {
    TimePoint t = std::chrono::system_clock::now() + std::chrono::seconds(ttl);
    services_ep_map[service_name].insert({ep.GetAddress(),std::make_pair(ep, t)});
    service_ep_add_map[service_name].push_back(ep.SerializeToString());
    service_help_map[t].insert(ep.SerializeToString());
}

// 保活，刷新ttl
void NameSvr::keep_service_alive(const std::string& service_name, Endpoint ep) {
    std::cout << "keep " << ep.GetAddress() << " alive, " << services_ep_map[service_name].size() <<std::endl;
    TimePoint new_t = std::chrono::system_clock::now() + std::chrono::seconds(ttl);
    TimePoint old_t = services_ep_map[service_name][ep.GetAddress()].second;
    services_ep_map[service_name][ep.GetAddress()].second = new_t;
    service_help_map[old_t].erase(ep.SerializeToString());
    if(service_help_map[old_t].empty()) {
        service_help_map.erase(old_t);
    }
    service_help_map[new_t].insert(ep.SerializeToString());
}

// 服务发现，返回服务实例
std::vector<Endpoint> NameSvr::discover_service(const std::string& service_name) {
    std::vector<Endpoint> service_instances;
    std::cout << "discover " << service_name << std::endl;
    auto it = services_ep_map.find(service_name);
    if(it != services_ep_map.end()) {
        for(auto instance : it->second) {
            std::cout << instance.first << std::endl;
            service_instances.push_back(instance.second.first);
        }
    }
    

    return service_instances;
}
// 获取订阅服务，返回订阅过该服务的服务
std::vector<std::string> NameSvr::get_sub_service(const std::string& service_name) {
    std::vector<std::string> sub_services;
    auto it = services_sub_map.find(service_name);
    if(it != services_sub_map.end()) {
        for(auto sub_svc : it->second) {
            sub_services.push_back(sub_svc);
        }
    }
    
    return sub_services;
}
// 从集合中删除过期的服务实例
void NameSvr::remove_expired_service(const std::string& service_name, Endpoint ep) {
    TimePoint t = services_ep_map[service_name][ep.GetAddress()].second;
    services_ep_map[service_name].erase(ep.GetAddress());
    std::cout << "remove " << ep.GetAddress() << std::endl;
    service_ep_del_map[service_name].push_back(ep.SerializeToString());
}

// A服务可以订阅B服务，当B服务的服务实例产生变化时，同步给A服务
void NameSvr::subscribe_service(const std::string& service_name_A, const std::string& service_name_B) {
    auto it = services_sub_map[service_name_B].find(service_name_A);
    if(it == services_sub_map[service_name_B].end()) {
        services_sub_map[service_name_B].insert(service_name_A);
        service_sub_add_map[service_name_B + "_sub"].push_back(service_name_A);
    }
    
    
}

//------------------动态键值------------------
// 注册动态键值
void NameSvr::register_dynamic(const std::string& key, const std::string& value, int d_ttl) {
    TimePoint t = std::chrono::system_clock::now() + std::chrono::seconds(d_ttl);
    dynamic_map.insert({key, std::make_pair(value, t)});
    dynamic_help_map[t].insert(key);
    dynamic_value_add_vec.push_back(std::make_pair(key, value));
    dynamic_time_add_vec.push_back(std::make_pair(key + "_time",time_point_to_string(t)));
}
// 动态键值，根据键获取值
std::string NameSvr::get_dynamic(const std::string& key) {
    std::string value = "";
    auto it = dynamic_map.find(key);
    if(it != dynamic_map.end()) {
        value = it->second.first;
    }
    return value;
}
// 订阅动态键值
void NameSvr::subscribe_dynamic(const std::string& address, const std::string& key) {
    dynamic_sub_map[key].insert(address);
    dynamic_sub_add_map[key + "_sub"].push_back(address);
}
// 获取订阅实例
std::vector<std::string> NameSvr::get_sub_dynamic(const std::string& key){
    std::vector<std::string> sub_addresses;
    auto it = dynamic_sub_map.find(key);
    if(it != dynamic_sub_map.end()) {
        for(auto address : it->second) {
            sub_addresses.push_back(address);
        }
    }
    return sub_addresses;
}

void NameSvr::remove_expired_dynamic(const std::string& key) {
    dynamic_sub_map.erase(key);
    dynamic_map.erase(key);
    std::cout << "remove " << key << std::endl;
    dynamic_del_vec.push_back(key);
    dynamic_time_del_vec.push_back(key + "_time");
    dynamic_sub_del_vec.push_back(key + "_sub");
}