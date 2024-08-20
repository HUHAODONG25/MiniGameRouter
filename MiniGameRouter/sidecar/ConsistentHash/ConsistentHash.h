#include <map>
#include <vector>
#include "Endpoint.h"

class ConsistentHash {
    std::map<u_int32_t, Endpoint> hash_ring;  // 虚拟节点一致性哈希环，key是哈希值，value是端点
    int ep_num;                               // 真实端点数量
    int v_num;                                // 每个真实端点对应的虚拟端点数量

public:
    ConsistentHash() {};
    ConsistentHash(std::vector<Endpoint> eps, int virtual_num = 100);
    Endpoint get_ep_by_key(std::string key);
    bool delete_ep(Endpoint ep);
    bool add_ep(Endpoint ep);
};