#include <stdio.h>
#include "Can.h"
#include "CanIf.h"

static void Can_PrintFrame(const char *dir, Can_IdType id, uint8 dlc, const uint8 *data)
{
    uint8 i;

    printf("  [CAN %s] ID=0x%03lX DLC=%u DATA=", dir, (unsigned long)id, (unsigned)dlc);
    for (i = 0u; i < dlc; i++)
    {
        printf("%02X ", (unsigned)data[i]);
    }
    printf("\n");
}

Std_ReturnType Can_Write(uint8 Hth, const Can_PduType *PduInfo)
{
    Std_ReturnType ret = E_NOT_OK;

    (void)Hth;
    if ((PduInfo != NULL) && (PduInfo->sdu != NULL) && (PduInfo->length <= 8u))
    {
        Can_PrintFrame("TX", PduInfo->id, PduInfo->length, PduInfo->sdu);
        ret = E_OK;
    }
    return ret;
}

void Can_Sim_Receive(Can_IdType id, const uint8 *data, uint8 dlc)
{
    uint8 buf[8] = {0u};
    PduInfoType pdu;
    uint8 i;

    if ((data != NULL) && (dlc <= 8u))
    {
        for (i = 0u; i < dlc; i++)
        {
            buf[i] = data[i];
        }
        pdu.SduDataPtr = buf;
        pdu.SduLength  = dlc;

        Can_PrintFrame("RX", id, dlc, buf);
        CanIf_RxIndication(id, &pdu);
    }
}