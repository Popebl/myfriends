#include "ipc_frame.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SHM_SIZE sizeof(ipc_frame_t)

int main() {
    
    // 创建文件以确保文件存在
    FILE *file = fopen("/tmp/shmfile", "w");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fclose(file);
    
    // 创建共享内存的键
    key_t key = ftok("shmfile", 65);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // 获取共享内存
    int shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // 绑定共享内存
    ipc_frame_t *frame = (ipc_frame_t*) shmat(shmid, (void*)0, 0);
    if (frame == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory attached at address %p\n", (void *)frame);

    // 读取并处理数据
    printf("Receiver: Frame received: addr=%lx, data_length=%lu\n", frame->addr, frame->data_length);

    for (size_t i = 0; i < frame->data_length; i++) {
        printf("data[%lu] = %lx\n", i, frame->data[i]);
    }

    // 分离共享内存
    if (shmdt(frame) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // 删除共享内存
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
