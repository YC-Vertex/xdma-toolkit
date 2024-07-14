#include "../include/xdma_mm.hh"

int main()
{
    char wr_buf[] = "Hello World";
    char *rd_buf = (char *)malloc(sizeof(wr_buf));
    char *wr_dev_name = "/dev/xdma0_h2c_0";
    char *rd_dev_name = "/dev/xdma0_c2h_0";

    uint64_t address = 0x10000A8F0;

    int wr_dev_fd = dev_init(wr_dev_name);
    memcpy_h2d(wr_dev_fd, address, wr_buf, sizeof(wr_buf));
    printf("wr = %s\n", wr_buf);
    
    int rd_dev_fd = dev_init(rd_dev_name);
    memcpy_d2h(rd_dev_fd, address, rd_buf, sizeof(wr_buf));
    printf("rd = %s\n", rd_buf);

    return 0;
}
