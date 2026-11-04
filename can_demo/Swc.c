#include <stdio.h>
#include "Swc.h"
#include "Rte.h"

/* Runnable gui: rpm tang 100 moi chu ky, nhiet do co dinh 80 do C */
void Swc_EngineTx_Run10ms(void)
{
    static uint16 rpm = 800u;

    uint16 rawRpm  = (uint16)(rpm * 4u);          /* factor 0.25 -> raw = rpm / 0.25 */
    uint8  rawTemp = (uint8)(80u + 40u);          /* offset -40  -> raw = degC + 40  */

    (void)Rte_Write_EngineSpeed(rawRpm);
    (void)Rte_Write_CoolantTemp(rawTemp);

    rpm = (uint16)(rpm + 100u);
}

/* Runnable nhan: doc toc do xe, xu ly timeout */
void Swc_DashRx_Run10ms(void)
{
    uint16 raw = 0u;
    Std_ReturnType ret = Rte_Read_VehSpeed(&raw);

    if (ret == RTE_E_OK)
    {
        printf("  [SWC RX] VehSpeed = %u.%02u km/h\n",
               (unsigned)(raw / 100u), (unsigned)(raw % 100u));
    }
    else
    {
        printf("  [SWC RX] VehSpeed: TIMEOUT (hien thi '--')\n");
    }
}