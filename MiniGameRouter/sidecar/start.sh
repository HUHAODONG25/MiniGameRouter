#!/bin/bash
source /etc/profile
g++ -o main_sidecar main_sidecar.cpp ConsistentHash/ConsistentHash.cpp SideCar.cpp ../smhasher/src/MurmurHash3.cpp ../protobuf/message.pb.cc -I ../include -I ../protobuf -I ConsistentHash -I ../smhasher/src -lprotobuf -lzmq