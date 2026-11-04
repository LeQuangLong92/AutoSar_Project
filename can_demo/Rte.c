#include "Rte.h"
#include "Com.h"

Std_ReturnType Rte_Write_EngineSpeed(uint16 data)
{
    return (Std_ReturnType)Com_SendSignal(COM_SIG_ENGINE_SPEED, &data);
}

Std_ReturnType Rte_Write_CoolantTemp(uint8 data)
{
    return (Std_ReturnType)Com_SendSignal(COM_SIG_COOLANT_TEMP, &data);
}

Std_ReturnType Rte_Read_VehSpeed(uint16 *data)
{
    Std_ReturnType ret;

    if (data == NULL)
    {
        ret = RTE_E_INVALID;
    }
    else if (Com_ReceiveSignal(COM_SIG_VEH_SPEED, data) != E_OK)
    {
        ret = RTE_E_INVALID;
    }
    else if (Com_IsRxTimeout(COM_RXPDU_VEHICLE_DATA) == TRUE)
    {
        ret = RTE_E_TIMEOUT;
    }
    else
    {
        ret = RTE_E_OK;
    }
    return ret;
}