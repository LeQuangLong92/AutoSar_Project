#include <stdio.h>
#include <stdint.h>

int main(void)
{
    uint8_t  speed = 250U;      /* 0..255 */
    int8_t   temp  = -40;       /* -128..127 */
    uint16_t rpm   = 6500U;     /* 0..65535 */
    uint32_t odo   = 123456U;

    printf("sizeof: u8=%zu u16=%zu u32=%zu\n",
           sizeof(uint8_t), sizeof(uint16_t), sizeof(uint32_t));
    printf("speed=%u temp=%d rpm=%u odo=%lu\n",
           (unsigned)speed, (int)temp, (unsigned)rpm, (unsigned long)odo);

    /* Tràn số: uint8_t chỉ chứa tối đa 255 */
    speed = (uint8_t)(speed + 10U);
    printf("speed sau khi +10 = %u\n", (unsigned)speed);

    return 0;
}