#ifndef __IPC_FRAME_H__
#define __IPC_FRAME_H__

#include <stdint.h>
#include <stdio.h>

// Structure definition
typedef struct {
    uint64_t addr;         // 64-bit address
    uint64_t data_length;  // 64-bit data length
    uint64_t data[510];    // Array of 64-bit data, with 510 elements
} ipc_frame_t;

uint64_t get_ipc_frame_addr(ipc_frame_t *s);
void set_ipc_frame_addr(ipc_frame_t *s, uint64_t addr);
uint64_t get_ipc_frame_data_length(ipc_frame_t *s);
void set_ipc_frame_data_length(ipc_frame_t *s, uint64_t length);
uint64_t get_ipc_frame_data_element(ipc_frame_t *s, int index);
void set_ipc_frame_data_element(ipc_frame_t *s, int index, uint64_t value);

void init_ipc_frame(ipc_frame_t *frame, uint64_t addr, uint64_t *data, size_t data_length); 
ssize_t send_ipc_frame(int sockfd, ipc_frame_t *frame); 
ssize_t receive_ipc_frame(int sockfd, ipc_frame_t *frame); 

#endif //#ifndef __IPC_FRAME_H__