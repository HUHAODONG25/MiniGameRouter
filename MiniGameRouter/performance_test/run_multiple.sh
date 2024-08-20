#!/bin/bash

# 可执行文件的路径
executable="./send_reg"

# 初始参数
param=50001

# 执行次数
num_executions=1000
./cur_time
for ((i=1; i<=num_executions; i++))
do
    echo "Starting execution $i with parameter $param"
    $executable $param &
    param=$((param + 1))
done

echo "All instances started."