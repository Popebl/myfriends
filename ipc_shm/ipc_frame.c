#include <stdint.h>
#include <stdio.h>
#include "ipc_frame.h"
#include <string.h>
#include <unistd.h>

// API function definitions

// Read the addr element
uint64_t get_ipc_frame_addr(ipc_frame_t *s) {
    return s->addr;
}

// Write to the addr element
void set_ipc_frame_addr(ipc_frame_t *s, uint64_t addr) {
    s->addr = addr;
}

// Read the data_length element
uint64_t get_ipc_frame_data_length(ipc_frame_t *s) {
    return s->data_length;
}

// Write to the data_length element
void set_ipc_frame_data_length(ipc_frame_t *s, uint64_t length) {
    s->data_length = length;
}

// Read an element from the data array
uint64_t get_ipc_frame_data_element(ipc_frame_t *s, int index) {
    if (index < 0 || index >= 510) {
        // Error handling: index out of range
        return 0; // Or another appropriate error return value
    }
    return s->data[index];
}

// Write to an element in the data array
void set_ipc_frame_data_element(ipc_frame_t *s, int index, uint64_t value) {
    if (index < 0 || index >= 510) {
        // Error handling: index out of range
        return;
    }
    s->data[index] = value;
}

/*
// Example usage
int main() {
    ipc_frame_t s;

    // Set the address
    set_addr(&s, 0x123456789ABCDEF0);
    printf("Addr: 0x%lx\n", get_addr(&s));

    // Set the data length
    set_data_length(&s, 100);
    printf("Data Length: %lu\n", get_data_length(&s));

    // Set and get an element in the data array
    set_data_element(&s, 0, 0xDEADBEEF);
    printf("Data[0]: 0x%lx\n", get_data_element(&s, 0));

    return 0;
}
*/