#pragma once

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief                      open and initialize device
 * 
 * @param      dev             device name, e.g. "/dev/xdma0_h2c_0"
 * @return     int             device file descriptor
 */
int dev_init(char *dev) {
    int fd = open(dev, O_RDWR);
    assert(fd > 0);
    return fd;
}

/**
 * @brief                      read data from device to local memory (buffer), (i.e. device-to-host)
 * 
 * @param      dev_fd          device file descriptor
 * @param      addr            source address in device
 * @param      buffer          buffer base pointer
 * @param      size            data size (bytes)
 * @return     int             0 = success, -1 = failed
 */
int memcpy_d2h (int dev_fd, uint64_t addr, void *buffer, uint64_t size) 
{
    // seek to addr
    if ( addr != lseek(dev_fd, addr, SEEK_SET) ) {
        fprintf(stderr, "seek 0x%lx failed.\n", addr);
        return -1;
    }
    // read from device
    if ( size != read(dev_fd, buffer, size) ) {
        fprintf(stderr, "read 0x%lx bytes @ 0x%lx failed.\n", size, addr);
        return -1;
    }
    return 0;
}

/**
 * @brief                      write data from local memory (buffer) to device, (i.e. host-to-device)
 * 
 * @param      dev_fd          device file descriptor
 * @param      addr            target address in device
 * @param      buffer          buffer base pointer
 * @param      size            data size (bytes)
 * @return     int             0 = success, -1 = failed
 */
int memcpy_h2d (int dev_fd, uint64_t addr, void *buffer, uint64_t size) 
{
    // seek to addr
    if ( addr != lseek(dev_fd, addr, SEEK_SET) ) {
        fprintf(stderr, "seek 0x%lx failed.\n", addr);
        return -1;
    }
    // write to device
    if ( size != write(dev_fd, buffer, size) ) {
        fprintf(stderr, "write 0x%lx bytes @ 0x%lx failed.\n", size, addr);
        return -1;
    }
    return 0;
}
