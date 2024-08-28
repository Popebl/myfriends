#include "ipc_frame.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SHM_SIZE sizeof(ipc_frame_t)

int main() {
    // 创建共享内存的键
    key_t key = ftok("shmfile", 65);
    // 创建共享内存
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    // 绑定共享内存
    ipc_frame_t *frame = (ipc_frame_t*) shmat(shmid, (void*)0, 0);

    // 准备数据
    frame->addr = 0x12345678;
    frame->data_length = 4;
    frame->data[0] = 0x11111111;
    frame->data[1] = 0x22222222;
    frame->data[2] = 0x33333333;
    frame->data[3] = 0x44444444;

    printf("Sender: Data written to shared memory.\n");

    // 等待接收方读取数据
    sleep(10);

    // 分离共享内存
    shmdt(frame);

    return 0;
}
