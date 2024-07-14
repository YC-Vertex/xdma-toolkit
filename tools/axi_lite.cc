#include "../include/xdma_mm.hh"
#include "../include/xdma_lite.hh"

int main()
{
    char *dev_name = "/dev/xdma0_user";
    int dev_fd = dev_init(dev_name);

    uint8_t state = 0x0001;
    for (int pos = 0; pos < 6; pos++) {
        *(uint8_t *)(map(dev_fd, 0x0000)) = state;
        state <<= 1;
        for (int i = 0; i < 1e8; i++);
    }

    // uint8_t state = *(uint8_t *)(map(dev_fd, 0x0000));
    // printf("button state = %x\n", state);

    return 0;
}
