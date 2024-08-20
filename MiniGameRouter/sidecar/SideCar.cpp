#include "SideCar.h"
#include <random>


SideCar::SideCar(std::string namesvr_address, std::string route_file, int port) : context(1), tick_socket(context, zmq::socket_type::pull), \
                                                                                  from_svc(context, zmq::socket_type::pull), to_svc(context, zmq::socket_type::push), \
                                    from_out(context, zmq::socket_type::pull), ns_socket(context, zmq::socket_type::dealer) {
    
    // 根据配置文件获取路由策略
    routing_config = parseConfigFile(route_file);
    
    ns_ep.svc_name = "Namesvr";
    ns_ep.weight = 1;
    ns_ep.SetAddress(namesvr_address);
    
    // 根据端口号绑定通道
    to_svc.connect("ipc:///tmp/to_svc_" + std::to_string(port));
    from_svc.bind("ipc:///tmp/from_svc_" + std::to_string(port));
    from_out.bind("tcp://*:" + std::to_string(port));
    tick_socket.bind("ipc:///tmp/tick_" + std::to_string(port));
}

bool SideCar::Init() {
    // 接收到服务注册消息
    zmq::message_t messageMsg;
    from_svc.recv(messageMsg, zmq::recv_flags::none);
    std::string init_m(static_cast<char*>(messageMsg.data()), messageMsg.size());
    // 去序列化
    Message init_message(init_m);
    if(init_message.m_type != REGISTER) {
        return false;
    }
    // 根据发送方初始化通道
    self_ep = init_message.sender;
    std::string ep_address = self_ep.ip_address + ":" + std::to_string(self_ep.port);
    // std::cout << ep_address << std::endl;

    // -----------------------------继续把消息转发给namesvr---------------------------------------------------
    // 配置ns_socket
    std::string identity = self_ep.GetAddress();
    // ns_socket.setsockopt(ZMQ_IDENTITY, identity.c_str(), identity.size());
    ns_socket.set(zmq::sockopt::routing_id, identity);
    ns_socket.connect("tcp://" + ns_ep.GetAddress());
    // 发送
    ns_socket.send(messageMsg, zmq::send_flags::none);
    // std::cout << "waiting for reply" << std::endl;

    // 接收实际消息
    zmq::message_t reply;
    ns_socket.recv(reply, zmq::recv_flags::none);
    std::string reply_str(static_cast<char*>(reply.data()), reply.size());
    Message rep_message(reply_str);
    // std::cout << "Reply from Namesvr: " << rep_message.content << std::endl;
    //-------------------------------把reply传递给svr端-------------------------
    to_svc.send(reply, zmq::send_flags::none);
    // 测试时间
    
    auto now = std::chrono::system_clock::now();
    auto currentTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    Message m_test;
    std::cout << m_test.timestampToString(currentTimestamp) << " " <<self_ep.GetAddress() << ": " << rep_message.content << std::endl;
    return true;
}

bool SideCar::Tick() {
    zmq::message_t messageMsg;
    tick_socket.recv(messageMsg, zmq::recv_flags::dontwait);
    if(messageMsg.size() == 0) {
        return false;
    }
    ns_socket.send(messageMsg, zmq::send_flags::none);
    return true;
}


bool SideCar::SvcToOut() {
    zmq::message_t messageMsg;
    from_svc.recv(messageMsg, zmq::recv_flags::dontwait);
    if(messageMsg.size() == 0) {
        return false;
    }
    std::string m(static_cast<char*>(messageMsg.data()), messageMsg.size());
    Message message(m);
    
    if(message.m_type == NORMAL) {
        // 测试记录时间
        from_svc_count++;
        if(from_svc_count == 1 || from_svc_count == 10000) {
            auto now = std::chrono::system_clock::now();
            auto currentTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
            Message m_test;
            std::cout <<"from svc to out "<< from_svc_count << ": "<< m_test.timestampToString(currentTimestamp) << std::endl;
        }

        std::string svc_name = message.receiver.svc_name;
        
        
        // 根据路由策略发送
        if(message.receiver.ip_address.size() != 0) {     // 指定目标路由，如果message中有receiver的IP地址，直接按照地址路由
            SendByEp(message.receiver.GetAddress(), m);
        } else if(message.key.size() != 0){                 // 动态键值路由，如果message包含key，按照key路由
            // 查找动态键值表
            auto it = dynamic_config.find(message.key);
            if(it !=  dynamic_config.end() && it->second.size() != 0) {               // 找到就直接发
                SendByEp(it->second, m);
            } else {                                        // 没找到就请求namesvr
                std::string IP = GetDynamic(message.key);
                if(IP.size() == 0) {
                    return true;
                }
                SendByEp(IP, m);
            }
        } else {                                            // 根据配置文件，从随机，一致性哈希，权重中选取路由策略
            // 先找缓存
            auto it = svcs.find(svc_name);
            // 没找到就去服务发现
            if(it == svcs.end()) {
                Discover(message.sender, message.receiver);
                std::cout << "after discover" << std::endl;
            }
            
            std::string r_svc_name = message.receiver.svc_name;
            if(routing_config[r_svc_name] == RANDOM) {      // 随机路由
                SendByRand(r_svc_name, m);
            } else if(routing_config[r_svc_name] == CONSISTENT_HASH) {      // 一致性哈希路由
                // 获取开始时间点
                auto start = std::chrono::high_resolution_clock::now();
                SendByHash(r_svc_name, message.sender.GetAddress(), m);
                // 获取结束时间点
                auto end = std::chrono::high_resolution_clock::now();
                // 计算持续时间
                std::chrono::duration<double> duration = end - start;
                std::cout << "Elapsed time: " << duration.count() << " seconds" << std::endl;
            } else if(routing_config[r_svc_name] == WEIGHT) {
                SendByWeight(r_svc_name, m);
            }
        }
    } else if(message.m_type == SET_DYNAMIC){
        // 直接转发给namesvr
        ns_socket.send(messageMsg, zmq::send_flags::none);
    }
    return true;
}

bool SideCar::OutToSvc() {
    // 要根据m_type改一下，对不同m_type做不同处理
    // 接收消息
    
    zmq::message_t messageMsg;
    from_out.recv(messageMsg, zmq::recv_flags::dontwait);
    if(messageMsg.size() == 0) {
        return false;
    }
    // 发送给svr
    
    std::string msg(static_cast<char*>(messageMsg.data()), messageMsg.size());
    Message message(msg);
    if(message.m_type == NORMAL) {
        // 测试记录时间
        to_svc_count++;
        if(to_svc_count == 1 || to_svc_count == 10000) {
            auto now = std::chrono::system_clock::now();
            auto currentTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
            Message m_test;
            std::cout <<"from out to svc "<< to_svc_count << ": "<< m_test.timestampToString(currentTimestamp) << std::endl;
        }
        to_svc.send(messageMsg, zmq::send_flags::none);
    } else if(message.m_type == ADD || message.m_type == DELETE) {
        std::cout << "update" << std::endl;
        // 更新节点
        Endpoint update_ep;
        update_ep.ParseFromString(message.content);
        // 先根据svc_name查找
        auto it_v = svcs.find(update_ep.svc_name);
        // 如果没找到就什么都不做
        if(it_v == svcs.end()) {
            return true;
        }
        // std::cout << "update ep svc: " << update_ep.svc_name << std::endl;
        // 找到svc_name之后再查找节点是否存在
        auto it_ep = std::find(it_v->second.begin(), it_v->second.end(), update_ep);
        
        if(it_ep == it_v->second.end() && message.m_type == ADD) {              // 如果没找到，而且是增加节点，就添加到vector    
            // std::cout << "add" << std::endl;     
            it_v->second.push_back(update_ep);
            // 根据配置文件构建辅助数据结构
            if(routing_config[update_ep.svc_name] == CONSISTENT_HASH) {         // 如果是一致性hash
                auto it_h = hash_rings.find(update_ep.svc_name);
                it_h->second.add_ep(update_ep);
            } else if(routing_config[update_ep.svc_name] == WEIGHT) {           // 如果是基于权重
                auto it_p = prefix_sums.find(update_ep.svc_name);
                int total = it_p->second.back();
                it_p->second.push_back(total + update_ep.weight);
            }
        } else if(it_ep != it_v->second.end() && message.m_type == DELETE){     // 如果找到了，而且是删除节点，就从vector中删除
            it_v->second.erase(it_ep);
            // 根据配置文件构建辅助数据结构
            if(routing_config[update_ep.svc_name] == CONSISTENT_HASH) {         // 如果是一致性hash
                auto it_h = hash_rings.find(update_ep.svc_name);
                it_h->second.delete_ep(update_ep);
                
            } else if(routing_config[update_ep.svc_name] == WEIGHT) {           // 如果是基于权重
                // 重新建立前缀和
                std::vector<int> prefix_sum;
                if(it_v->second.size() != 0) {
                    prefix_sum[0] = it_v->second[0].weight;
                    for(int i = 1; i < it_v->second.size(); i++) {
                        prefix_sum[i] = prefix_sum[i - 1] + it_v->second[i].weight;
                    }
                    prefix_sums[update_ep.svc_name] =  prefix_sum;
                }
                
            }
        }
        
    } else if(message.m_type == DEL_DYNAMIC) {                      // 删除动态键值
        auto it_d = dynamic_config.find(message.key);
        if(it_d != dynamic_config.end()) {
            dynamic_config.erase(it_d);
        }
    }
    // 可能以后有别的
        
    
    return true;
}

bool SideCar::Discover(Endpoint sender, Endpoint receiver) {
    // 构建服务发现消息
    Message discover_message(sender, ns_ep, DISCOVER, receiver.svc_name);
    std::string d_m = discover_message.SerializeToString();
    // 发送请求给namesvr
    zmq::message_t request(d_m.size());
    memcpy(request.data(), d_m.data(), d_m.size());
    
    ns_socket.send(request, zmq::send_flags::none);
    // 接收回复
    zmq::message_t reply;
    ns_socket.recv(reply, zmq::recv_flags::none);
    std::string replyMessage(static_cast<char*>(reply.data()), reply.size());
    Message reply_message(replyMessage);
    
    std::vector<Endpoint> eps = reply_message.StringToVectorEp();
    // 存到缓存中
    svcs.insert(std::pair<std::string, std::vector<Endpoint>>(eps[0].svc_name, eps));
    // 根据配置文件，如果是一致性哈希，就建立哈希环
    if(routing_config[eps[0].svc_name] == CONSISTENT_HASH) {
        ConsistentHash c_hash(eps);
        hash_rings.insert(std::pair<std::string, ConsistentHash>(eps[0].svc_name, eps));
    }
    // 根据配置文件，如果是权重，就建立前缀和
    if(routing_config[eps[0].svc_name] == WEIGHT) {
        std::vector<int> prefix_sum(eps.size());
        // std::cout << eps[0].GetAddress();
        prefix_sum[0] = eps[0].weight;
        for(int i = 1; i < eps.size(); i++) {
            prefix_sum[i] = prefix_sum[i - 1] + eps[i].weight;
        }
        prefix_sums.insert(std::pair<std::string, std::vector<int>>(eps[0].svc_name, prefix_sum));
    }
    
    return true;
}

bool SideCar::SendByEp(std::string address, const std::string& message) {
    // 创建套接字
    // std::cout << address << std::endl;
    zmq::socket_t sender(context, zmq::socket_type::push);
    sender.connect("tcp://" + address);
    
    // 发送消息
    zmq::message_t messageMsg(message.size());
    memcpy(messageMsg.data(), message.data(), message.size());
    if(sender.send(messageMsg, zmq::send_flags::none)) {
        sender.close();
        return true;
    }
    return true;
    
}



bool SideCar::SendByHash(std::string svc_name, std::string key, const std::string& message) {
    auto it_h = hash_rings.find(svc_name); 
    if(it_h == hash_rings.end()) {
        return false;
    }
    Endpoint r_ep = it_h->second.get_ep_by_key(key);
     
    std::string address = r_ep.GetAddress();
    return SendByEp(address, message);
}

bool SideCar::SendByRand(std::string svc_name, const std::string& message) {
    std::vector<Endpoint> eps = svcs[svc_name];
    // 创建一个随机数引擎
    std::random_device rd;
    std::mt19937 gen(rd());
    // 创建一个均匀分布的随机数生成器
    std::uniform_int_distribution<> dis(0, eps.size() - 1);
    // 生成随机数
    int r = dis(gen);
    // 发送
    return SendByEp(svcs[svc_name][r].GetAddress(), message);
};
bool SideCar::SendByWeight(std::string svc_name, const std::string& message){
    int total_weight = prefix_sums[svc_name].back();
    // 创建一个随机数引擎
    std::random_device rd;
    std::mt19937 gen(rd());
    // 创建一个均匀分布的随机数生成器
    std::uniform_int_distribution<> dis(1, total_weight);
    // 生成随机数
    int r = dis(gen);
    auto it = std::lower_bound(prefix_sums[svc_name].begin(), prefix_sums[svc_name].end(), r);
    int index = std::distance(prefix_sums[svc_name].begin(), it);
    // 发送
    return SendByEp(svcs[svc_name][index].GetAddress(), message);
}

std::string SideCar::GetDynamic(std::string key) {
    Message message(self_ep, ns_ep, GET_DYNAMIC, "");
    message.SetKey(key);
    std::string msg = message.SerializeToString();
    // 发送请求给namesvr
    zmq::message_t request(msg.size());
    memcpy(request.data(), msg.data(), msg.size());
    
    ns_socket.send(request, zmq::send_flags::none);
    // 接收回复
    zmq::message_t reply;
    ns_socket.recv(reply, zmq::recv_flags::none);
    std::string replyMessage(static_cast<char*>(reply.data()), reply.size());
    Message reply_message(replyMessage);
    if(reply_message.content.size() != 0) {
        // 加入动态键值表
        dynamic_config.insert(std::pair<std::string, std::string>(key, reply_message.content));
    }
    
    // 返回IP地址
    return reply_message.content;
}

