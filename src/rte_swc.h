#ifndef RTE_SWC_H
#define RTE_SWC_H

#include "std_types.h"

#define RTE_E_OK                 E_OK
#define RTE_E_INVALID            ((Std_ReturnType)0x01u)
#define RTE_E_MAX_AGE_EXCEEDED   ((Std_ReturnType)0x40u)

Std_ReturnType Rte_Read_VehSpeed(uint16_t *speed);
Std_ReturnType Rte_Write_OverSpeedWarn(boolean warn);

#endif /* RTE_SWC_H */