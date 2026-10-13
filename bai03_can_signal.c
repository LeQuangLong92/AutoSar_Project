#include <stdio.h>
#include <stdint.h>

int main(void)
{
    /* Frame giả lập: 8 byte dữ liệu */
    uint8_t data[8] = {0x10U, 0x27U, 0x35U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};

    /* Engine speed: byte 0-1, little-endian, factor 0.25 rpm/bit */
    uint16_t raw_rpm = (uint16_t)((uint16_t)data[0] | ((uint16_t)data[1] << 8));
    double rpm = (double)raw_rpm * 0.25;

    /* Gear: 4 bit cao của byte 2; Mode: 4 bit thap */
    uint8_t gear = (uint8_t)((data[2] >> 4) & 0x0FU);
    uint8_t mode = (uint8_t)(data[2] & 0x0FU);

    printf("raw_rpm = %u (0x%04X)\n", (unsigned)raw_rpm, (unsigned)raw_rpm);
    printf("rpm     = %.2f\n", rpm);
    printf("gear    = %u, mode = %u\n", (unsigned)gear, (unsigned)mode);

    return 0;
}