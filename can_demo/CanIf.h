#ifndef CANIF_H
#define CANIF_H

#include "Std_Types.h"

#define CANIF_TXPDU_ENGINE_DATA  (0u)

Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);
void CanIf_RxIndication(Can_IdType canId, const PduInfoType *PduInfoPtr);

#endif