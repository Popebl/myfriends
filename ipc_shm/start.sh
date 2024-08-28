#!/bin/bash

# 编译C程序
gcc sender.c ipc_frame.c -o sender
gcc receiver.c ipc_frame.c -o receiver

# 启动接收器进程
./receiver &

# 启动发送器进程
./sender
