#ifndef COM_H
#define COM_H

#include "Std_Types.h"

typedef uint16 Com_SignalIdType;

#define COM_SIG_ENGINE_SPEED    ((Com_SignalIdType)0u)   /* Tx, 16 bit */
#define COM_SIG_COOLANT_TEMP    ((Com_SignalIdType)1u)   /* Tx,  8 bit */
#define COM_SIG_VEH_SPEED       ((Com_SignalIdType)2u)   /* Rx, 16 bit */

#define COM_TXPDU_ENGINE_DATA   (0u)
#define COM_RXPDU_VEHICLE_DATA  (0u)

void    Com_Init(void);
uint8   Com_SendSignal(Com_SignalIdType SignalId, const void *SignalDataPtr);
uint8   Com_ReceiveSignal(Com_SignalIdType SignalId, void *SignalDataPtr);
boolean Com_IsRxTimeout(PduIdType RxPduId);               /* ham tro giup cua vi du */
void    Com_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);
void    Com_MainFunctionRx(void);
void    Com_MainFunctionTx(void);

#endif