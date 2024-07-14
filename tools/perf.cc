#include "../include/xdma_utils.hh"
#include "../include/time_utils.hh"

#define SZ_SHORT (12)
#define SZ_LONG (1024*1024)

int main()
{
    char wr_buf[] = "Hello World";
    char *rd_buf = (char *)malloc(SZ_SHORT);
    char *wr_buf_long = (char *)malloc(SZ_LONG);
    char *rd_buf_long = (char *)malloc(SZ_LONG);
    char *wr_dev_name = "/dev/xdma0_h2c_0";
    char *rd_dev_name = "/dev/xdma0_c2h_0";
    char *lite_dev_name = "/dev/xdma0_user";

    uint64_t address = 0x0000;

    {
        printf("\n========== Short Memory Test ==========\n");
        int wr_dev_fd = dev_init(wr_dev_name);
        int rd_dev_fd = dev_init(rd_dev_name);
        timespec t1, t2, t3, t4;
        float wr_time = 0.f;
        float rd_time = 0.f;

        for (int i = 0; i < 16; ++i) {
            GETTIME(t1);
            memcpy_h2d(wr_dev_fd, address, wr_buf, SZ_SHORT);
            GETTIME(t2);
            GETTIME(t3);
            memcpy_d2h(rd_dev_fd, address, rd_buf, SZ_SHORT);
            GETTIME(t4);
            if (i >= 4) {
                wr_time += DIFF(t1, t2);
                rd_time += DIFF(t3, t4);
            }
            printf("%d: wr latency = %.0f ns, rd latency = %.0f ns\n", i, DIFF(t1, t2), DIFF(t3, t4));
        }

        printf("avg wr latency = %.2f ns\navg rd latency = %.2f ns\n", wr_time / 12.f, rd_time / 12.f);
    }

    {
        printf("\n========== Long Memory Test (1 MB) ==========\n");
        int wr_dev_fd = dev_init(wr_dev_name);
        int rd_dev_fd = dev_init(rd_dev_name);
        timespec t1, t2, t3, t4;
        float wr_time = 0.f;
        float rd_time = 0.f;

        for (int i = 0; i < 16; ++i) {
            GETTIME(t1);
            memcpy_h2d(wr_dev_fd, address, wr_buf_long, SZ_LONG);
            GETTIME(t2);
            GETTIME(t3);
            memcpy_d2h(rd_dev_fd, address, rd_buf_long, SZ_LONG);
            GETTIME(t4);
            if (i >= 4) {
                wr_time += DIFF(t1, t2);
                rd_time += DIFF(t3, t4);
            }
            printf("%d: wr latency = %.0f ns, rd latency = %.0f ns\n", i, DIFF(t1, t2), DIFF(t3, t4));
        }

        printf("avg wr latency = %.2f ns\navg rd latency = %.2f ns\n", wr_time / 12.f, rd_time / 12.f);
        printf("avg wr bandwidth = %.2f GB/s\navg rd bandwidth = %.2f GB/s\n",
               SZ_LONG / (wr_time / 12.f), SZ_LONG / (rd_time / 12.f));
    }

    {
        printf("\n========== Register Test ==========\n");
        int lite_dev_fd = dev_init(lite_dev_name);
        timespec t1, t2;

        uint8_t state = 0x0001;
        for (int i = 0; i < 6; i++) {
            uint8_t *ptr = (uint8_t *)(map(lite_dev_fd, 0x0000));
            GETTIME(t1); *ptr = state; GETTIME(t2);
            state <<= 1;
            printf("%d: latency = %.0f ns\n", i, DIFF(t1, t2));
            for (int i = 0; i < 1e8; i++);
        }
    }

    return 0;
}
