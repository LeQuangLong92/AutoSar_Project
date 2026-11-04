#include "CanIf.h"
#include "Can.h"
#include "PduR.h"

typedef struct { Can_IdType canId; uint8 hth; }            CanIf_TxCfgType;
typedef struct { Can_IdType canId; PduIdType upperPduId; } CanIf_RxCfgType;

static const CanIf_TxCfgType CanIf_TxCfg[] = { { 0x100u, 0u } };   /* EngineData  */
static const CanIf_RxCfgType CanIf_RxCfg[] = { { 0x200u, 0u } };   /* VehicleData */

#define CANIF_TX_COUNT  ((uint8)(sizeof(CanIf_TxCfg) / sizeof(CanIf_TxCfg[0])))
#define CANIF_RX_COUNT  ((uint8)(sizeof(CanIf_RxCfg) / sizeof(CanIf_RxCfg[0])))

Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    Std_ReturnType ret = E_NOT_OK;

    if ((PduInfoPtr != NULL) && (TxPduId < CANIF_TX_COUNT))
    {
        Can_PduType canPdu;

        canPdu.swPduHandle = TxPduId;
        canPdu.length      = (uint8)PduInfoPtr->SduLength;
        canPdu.id          = CanIf_TxCfg[TxPduId].canId;
        canPdu.sdu         = PduInfoPtr->SduDataPtr;

        ret = Can_Write(CanIf_TxCfg[TxPduId].hth, &canPdu);
    }
    return ret;
}

void CanIf_RxIndication(Can_IdType canId, const PduInfoType *PduInfoPtr)
{
    uint8 i;

    if (PduInfoPtr != NULL)
    {
        for (i = 0u; i < CANIF_RX_COUNT; i++)
        {
            if (CanIf_RxCfg[i].canId == canId)
            {
                PduR_CanIfRxIndication(CanIf_RxCfg[i].upperPduId, PduInfoPtr);
            }
        }
    }
}