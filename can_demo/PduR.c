#include "PduR.h"
#include "Com.h"
#include "CanIf.h"

/* Bang dinh tuyen: chi so = PDU ID phia tren, gia tri = PDU ID phia duoi */
static const PduIdType PduR_TxRouting[] = { CANIF_TXPDU_ENGINE_DATA };   /* Com Tx 0 -> CanIf Tx 0 */
static const PduIdType PduR_RxRouting[] = { COM_RXPDU_VEHICLE_DATA };    /* CanIf Rx 0 -> Com Rx 0 */

#define PDUR_TX_COUNT  ((uint8)(sizeof(PduR_TxRouting) / sizeof(PduR_TxRouting[0])))
#define PDUR_RX_COUNT  ((uint8)(sizeof(PduR_RxRouting) / sizeof(PduR_RxRouting[0])))

Std_ReturnType PduR_ComTransmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    Std_ReturnType ret = E_NOT_OK;

    if (TxPduId < PDUR_TX_COUNT)
    {
        ret = CanIf_Transmit(PduR_TxRouting[TxPduId], PduInfoPtr);
    }
    return ret;
}

void PduR_CanIfRxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
    if (RxPduId < PDUR_RX_COUNT)
    {
        Com_RxIndication(PduR_RxRouting[RxPduId], PduInfoPtr);
    }
}