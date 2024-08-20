#include <MurmurHash3.h>
#include "ConsistentHash.h"

ConsistentHash::ConsistentHash(std::vector<Endpoint> eps, int virtual_num) {
    ep_num = eps.size();
    v_num = virtual_num;
   
    for(int i = 0; i < ep_num; ++i) {
        for(int j = 0; j < v_num; ++j) {
            std::string ep_key = eps[i].GetAddress() + std::to_string(j);
            
            u_int32_t hash;
            u_int32_t seed = 0;
            MurmurHash3_x86_32(ep_key.c_str(), ep_key.length(), seed, &hash);
            hash_ring.insert(std::pair<u_int32_t, Endpoint>(hash, eps[i]));
        }
    }
}

Endpoint ConsistentHash::get_ep_by_key(std::string key) {
    u_int32_t key_hash;
    u_int32_t seed = 0;
    MurmurHash3_x86_32(key.c_str(), key.length(), seed, &key_hash);
    auto it = hash_ring.lower_bound(key_hash);
    if(it == hash_ring.end()) {
        return hash_ring.begin()->second;
    }
    return it->second;
}

bool ConsistentHash::delete_ep(Endpoint ep) {
    for(int j = 0; j < v_num; j++) {
        std::string ep_key = ep.GetAddress() + std::to_string(j);
        u_int32_t hash;
        u_int32_t seed = 0;
        MurmurHash3_x86_32(ep_key.c_str(), ep_key.length(), seed, &hash);
        auto it = hash_ring.find(hash);
        if(it != hash_ring.end()) {
            hash_ring.erase(it);
        }
    }
    return true;
}

bool ConsistentHash::add_ep(Endpoint ep) {
    for(int j = 0; j < v_num; j++) {
        std::string ep_key = ep.GetAddress() + std::to_string(j);
            
        u_int32_t hash;
        u_int32_t seed = 0;
        MurmurHash3_x86_32(ep_key.c_str(), ep_key.length(), seed, &hash);
        hash_ring.insert(std::pair<u_int32_t, Endpoint>(hash, ep));
    }
    return true;
}