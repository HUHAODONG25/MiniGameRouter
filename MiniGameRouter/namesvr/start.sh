#!/bin/bash
source /etc/profile
g++ -o main_namesvr main_namesvr.cpp namesvr.cpp ../protobuf/message.pb.cc -I ../include -I ../protobuf -lcpp_redis -ltacopie -lpthread -lprotobuf -lzmq