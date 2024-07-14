#include "../include/xdma_utils.hh"

#include <stdlib.h>
#include <time.h>

int main()
{
    srand((unsigned)time(NULL));

    char *dev_name = "/dev/xdma0_user";
    int dev_fd = dev_init(dev_name);

    for (int addr = 0; addr < 16; ++addr) {
        uint8_t wr = rand() % 256, rd;
        *(uint8_t *)(map(dev_fd, addr)) = wr;
        rd = *(uint8_t *)(map(dev_fd, addr));
        printf("wr = 0x%02x, rd = 0x%02x, eq = %x\n", wr, rd, wr == rd);
    }

    return 0;
}
