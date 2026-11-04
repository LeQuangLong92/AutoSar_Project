#ifndef RTE_H
#define RTE_H

#include "Std_Types.h"

#define RTE_E_OK       ((Std_ReturnType)0u)
#define RTE_E_INVALID  ((Std_ReturnType)1u)
#define RTE_E_TIMEOUT  ((Std_ReturnType)129u)

Std_ReturnType Rte_Write_EngineSpeed(uint16 data);
Std_ReturnType Rte_Write_CoolantTemp(uint8 data);
Std_ReturnType Rte_Read_VehSpeed(uint16 *data);

#endif