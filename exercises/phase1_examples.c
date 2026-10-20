/* Các ví dụ minh họa giai đoạn 1: chạy rồi đối chiếu với phần giải thích.
 * Biên dịch: gcc -std=c11 -Wall -Wextra -o examples phase1_examples.c
 */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static void bin(const char *label, uint32_t v, int bits)
{
    int i;
    printf("  %-10s ", label);
    for (i = bits - 1; i >= 0; i--) 
    {
        printf("%u", (unsigned)((v >> i) & 1U));
        if (((i % 4) == 0) && (i != 0)) 
        { printf(" "); 
        }
    }
    printf("   (0x%X)\n", (unsigned)v);
}

typedef struct { uint8_t a; uint32_t b; uint8_t c; } Bad;
typedef struct { uint32_t b; uint8_t a; uint8_t c; } Good;

int main(void)
{
    uint32_t reg = 0x2CU;

    printf("VD1: set bit 0\n");
    bin("reg", reg, 8); bin("mask", 1U << 0, 8); bin("reg | mask", reg | (1U << 0), 8);

    printf("VD2: clear bit 2\n");
    bin("reg", reg, 8); bin("mask", 1U << 2, 8); bin("~mask", ~(1U << 2) & 0xFFU, 8);
    bin("reg & ~mask", reg & ~(1U << 2), 8);

    printf("VD3: toggle bit 5\n");
    bin("reg", reg, 8); bin("mask", 1U << 5, 8); bin("reg ^ mask", reg ^ (1U << 5), 8);

    printf("VD4: read bit 3\n");
    bin("reg", reg, 8); bin("reg >> 3", reg >> 3, 8); bin("& 1", (reg >> 3) & 1U, 8);

    printf("VD5: dem bit bang v &= v-1, v = 0xB4\n");
    {
        uint32_t v = 0xB4U; int n = 0;
        while (v != 0U) { bin("v", v, 8); v &= (v - 1U); n++; }
        printf("  so lan lap = %d\n", n);
    }

    printf("VD6: field_get(0x3CA5, pos 4, len 12)\n");
    bin("reg", 0x3CA5U, 16); bin("reg >> 4", 0x3CA5U >> 4, 16);
    bin("mask", (1U << 12) - 1U, 16); bin("ket qua", (0x3CA5U >> 4) & ((1U << 12) - 1U), 16);
    printf("  = %u\n", (unsigned)((0x3CA5U >> 4) & ((1U << 12) - 1U)));

    printf("VD7: field_set(0xFFFF, pos 4, len 4, value 0)\n");
    {
        uint32_t m = ((1U << 4) - 1U) << 4;
        bin("reg", 0xFFFFU, 16); bin("m", m, 16); bin("~m", ~m & 0xFFFFU, 16);
        bin("reg & ~m", 0xFFFFU & ~m, 16);
    }

    printf("VD8: swap32(0x12345678)\n");
    {
        uint32_t v = 0x12345678U;
        printf("  b0<<24 = 0x%08X\n", (unsigned)((v & 0x000000FFU) << 24));
        printf("  b1<<8  = 0x%08X\n", (unsigned)((v & 0x0000FF00U) << 8));
        printf("  b2>>8  = 0x%08X\n", (unsigned)((v & 0x00FF0000U) >> 8));
        printf("  b3>>24 = 0x%08X\n", (unsigned)((v & 0xFF000000U) >> 24));
    }

    printf("VD9: padding\n");
    printf("  sizeof(Bad)  = %u  (a@%u, b@%u, c@%u)\n", (unsigned)sizeof(Bad),
           (unsigned)offsetof(Bad, a), (unsigned)offsetof(Bad, b), (unsigned)offsetof(Bad, c));
    printf("  sizeof(Good) = %u  (b@%u, a@%u, c@%u)\n", (unsigned)sizeof(Good),
           (unsigned)offsetof(Good, b), (unsigned)offsetof(Good, a), (unsigned)offsetof(Good, c));
    return 0;
}
