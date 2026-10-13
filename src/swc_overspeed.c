#include "swc_overspeed.h"
#include "rte_swc.h"

static uint8_t overCnt;

void Swc_OverSpeed_Init(void)
{
    overCnt = 0u;
}

void Swc_Run_OverSpeedWarning(void)
{
    uint16_t speed = 0u;
    boolean  warn  = FALSE;

    if (Rte_Read_VehSpeed(&speed) == RTE_E_OK)
    {
        if (speed > SWC_OVERSPEED_THRESHOLD_KMH)
        {
            if (overCnt < SWC_DEBOUNCE_CYCLES) { overCnt++; }
            if (overCnt >= SWC_DEBOUNCE_CYCLES) { warn = TRUE; }
        }
        else
        {
            overCnt = 0u;
        }
    }
    else
    {
        overCnt = 0u;                    /* fail-safe: lỗi đọc thì không cảnh báo */
    }

    (void)Rte_Write_OverSpeedWarn(warn);
}