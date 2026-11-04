#ifndef PDUR_H
#define PDUR_H

#include "Std_Types.h"

Std_ReturnType PduR_ComTransmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);
void PduR_CanIfRxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);

#endif