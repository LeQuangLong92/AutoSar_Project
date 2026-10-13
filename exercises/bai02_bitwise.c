#include <stdio.h>
#include <stdint.h>

#define FLAG_DOOR_OPEN   ((uint8_t)(1U << 0))
#define FLAG_LIGHT_ON    ((uint8_t)(1U << 1))
#define FLAG_BELT_OFF    ((uint8_t)(1U << 2))
#define FLAG_ENGINE_RUN  ((uint8_t)(1U << 7))

int main(void)
{
    uint8_t status = 0x00U;

    status |= FLAG_DOOR_OPEN;               /* SET bit 0 */
    status |= FLAG_ENGINE_RUN;              /* SET bit 7 */
    status |= FLAG_LIGHT_ON;                /* SET bit 1 */
    printf("sau SET   : 0x%02X\n", (unsigned)status);

    status &= (uint8_t)~FLAG_LIGHT_ON;      /* CLEAR bit 1 */
    printf("sau CLEAR : 0x%02X\n", (unsigned)status);

    status ^= FLAG_BELT_OFF;                /* TOGGLE bit 2 */
    printf("sau TOGGLE: 0x%02X\n", (unsigned)status);

    if ((status & FLAG_DOOR_OPEN) != 0U)    /* CHECK bit 0 */
    {
        printf("Cua dang mo\n");
    }

    return 0;
}