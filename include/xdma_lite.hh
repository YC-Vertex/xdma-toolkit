#pragma once

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/mman.h>

/**
 * @brief                      map device address to process memory
 * 
 * @param      dev_fd          device file descriptor
 * @param      addr            address in device
 * @return     void*           pointer to device memory location
 */
void *map(int dev_fd, uint64_t addr) {
    off_t pagesize, aligned, offset;
    pagesize = sysconf(_SC_PAGESIZE);
    aligned = addr & (~(pagesize - 1));
    offset = addr & (pagesize - 1);
    void *maddr = mmap(NULL, offset + 4, PROT_READ | PROT_WRITE, MAP_SHARED, dev_fd, aligned);
    return maddr + offset;
}
