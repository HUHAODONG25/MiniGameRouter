#!/bin/bash
source /etc/profile
g++ -o by_ep by_ep.cpp ../helper/helper.cpp ../smhasher/src/MurmurHash3.cpp ../protobuf/message.pb.cc -I ../include -I ../protobuf -I ../helper  -lprotobuf -lzmq -pthread
g++ -o by_other by_other.cpp ../helper/helper.cpp ../smhasher/src/MurmurHash3.cpp ../protobuf/message.pb.cc -I ../include -I ../protobuf -I ../helper  -lprotobuf -lzmq -pthread
g++ -o by_key by_key.cpp ../helper/helper.cpp ../smhasher/src/MurmurHash3.cpp ../protobuf/message.pb.cc -I ../include -I ../protobuf -I ../helper  -lprotobuf -lzmq -pthread
# g++ -o receiver receiver.cpp ../helper/helper.cpp ../smhasher/src/MurmurHash3.cpp ../protobuf/message.pb.cc -I ../include -I ../protobuf -I ../helper  -lprotobuf -lzmq

# ./sender localhost 50001 A 1
# ./receiver localhost 50011 B 1