#include <stdio.h>
#include <stdint.h>

int main(void)
{
    uint8_t flags = 0x00U;

    flags |= (1U << 3);     /* set bit 3 */
    flags |= (1U << 0);     /* set bit 0 */
    flags &= (uint8_t)~(1U << 0);   /* clear bit 0 */

    printf("flags = 0x%02X\n", flags);
    return 0;
}