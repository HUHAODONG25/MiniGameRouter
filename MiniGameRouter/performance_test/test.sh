#!/bin/bash
source /etc/profile
g++ -o cur_time cur_time.cpp
g++ -o by_ep_send by_ep_send.cpp ../helper/helper.cpp ../smhasher/src/MurmurHash3.cpp ../protobuf/message.pb.cc -I ../include -I ../protobuf -I ../helper  -lprotobuf -lzmq -pthread
g++ -o by_ep_recv by_ep_recv.cpp ../helper/helper.cpp ../smhasher/src/MurmurHash3.cpp ../protobuf/message.pb.cc -I ../include -I ../protobuf -I ../helper  -lprotobuf -lzmq -pthread
g++ -o send_reg send_reg.cpp ../helper/helper.cpp ../smhasher/src/MurmurHash3.cpp ../protobuf/message.pb.cc -I ../include -I ../protobuf -I ../helper  -lprotobuf -lzmq -pthread

