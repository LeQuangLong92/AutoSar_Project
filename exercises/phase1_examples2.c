/* Ví dụ 10-11: endianness, con trỏ và mảng.
 * Biên dịch: gcc -std=c11 -Wall -Wextra -Wconversion -o examples2 phase1_examples2.c
 */
#include <stdint.h>
#include <stdio.h>

/* Một "thanh ghi giả" trong RAM, để tập cách ghi qua con trỏ volatile
   giống như ghi vào thanh ghi phần cứng ở địa chỉ cố định. */
static volatile uint32_t fake_reg = 0U;
#define FAKE_REG (*(volatile uint32_t *)&fake_reg)

int main(void)
{
    printf("VD10: endianness\n");
    {
        uint32_t v = 0x12345678U;
        const uint8_t *p = (const uint8_t *)&v;      /* nhìn v như 4 byte liên tiếp */
        const uint8_t d[2] = {0x12U, 0x34U};         /* 2 byte nhận từ CAN */
        unsigned i;

        for (i = 0U; i < 4U; i++) {
            printf("  byte %u (dia chi thap -> cao) = 0x%02X\n", i, (unsigned)p[i]);
        }
        printf("  ghep kieu Intel    (d[0] | d[1]<<8) = 0x%04X\n", (unsigned)((uint32_t)d[0] | ((uint32_t)d[1] << 8)));
        printf("  ghep kieu Motorola (d[0]<<8 | d[1]) = 0x%04X\n", (unsigned)(((uint32_t)d[0] << 8) | (uint32_t)d[1]));
    }

    printf("VD11: con tro va mang\n");
    {
        uint8_t  buf[4] = {10U, 20U, 30U, 40U};
        uint8_t *p = buf;                             /* p trỏ tới phần tử đầu */
        uint32_t words[3] = {1U, 2U, 3U};
        uint32_t x = 5U;
        uint32_t *q = &x;

        printf("  p[2] = %u,  *(p + 2) = %u\n", (unsigned)p[2], (unsigned)*(p + 2));
        p[2] = 99U;
        printf("  sau p[2] = 99: buf[2] = %u\n", (unsigned)buf[2]);
        printf("  (p + 2) - p = %d phan tu\n", (int)((p + 2) - p));
        printf("  words+1 cach words %d byte\n",
               (int)((const uint8_t *)(words + 1) - (const uint8_t *)words));

        printf("  x truoc = %u\n", (unsigned)x);
        *q = 7U;                                      /* ghi qua con trỏ */
        printf("  sau *q = 7: x = %u\n", (unsigned)x);

        printf("  fake_reg truoc = %u\n", (unsigned)FAKE_REG);
        FAKE_REG |= (1U << 5);                        /* y hệt bật bit của thanh ghi thật */
        printf("  sau FAKE_REG |= (1U << 5): %u (0x%X)\n", (unsigned)FAKE_REG, (unsigned)FAKE_REG);
    }
    return 0;
}
