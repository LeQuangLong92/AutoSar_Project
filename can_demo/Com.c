#include "Com.h"
#include "PduR.h"

#define COM_PDU_LENGTH         (8u)
#define COM_RX_TIMEOUT_CYCLES  (3u)      /* 3 x 10 ms = 30 ms */

typedef struct
{
    boolean isTx;
    uint8   startBit;
    uint8   bitLen;
} Com_SignalCfgType;

static const Com_SignalCfgType Com_SignalCfg[] =
{
    { TRUE,   0u, 16u },    /* EngineSpeed */
    { TRUE,  16u,  8u },    /* CoolantTemp */
    { FALSE,  0u, 16u }     /* VehSpeed    */
};
#define COM_SIGNAL_COUNT  ((uint8)(sizeof(Com_SignalCfg) / sizeof(Com_SignalCfg[0])))

static uint8 Com_TxPduBuf[COM_PDU_LENGTH];
static uint8 Com_RxPduBuf[COM_PDU_LENGTH];
static uint8 Com_RxTimeoutCnt;

/* ---------- Dong goi / giai ma bit (Intel, little-endian) ---------- */
static void Com_PackIntel(uint8 *buf, uint8 startBit, uint8 bitLen, uint32 value)
{
    uint8 i;

    for (i = 0u; i < bitLen; i++)
    {
        uint8 bitPos  = (uint8)(startBit + i);
        uint8 byteIdx = (uint8)(bitPos / 8u);
        uint8 bitIdx  = (uint8)(bitPos % 8u);

        if (((value >> i) & 1u) != 0u)
        {
            buf[byteIdx] = (uint8)(buf[byteIdx] | (1u << bitIdx));
        }
        else
        {
            buf[byteIdx] = (uint8)(buf[byteIdx] & ~(1u << bitIdx));
        }
    }
}

static uint32 Com_UnpackIntel(const uint8 *buf, uint8 startBit, uint8 bitLen)
{
    uint32 value = 0u;
    uint8  i;

    for (i = 0u; i < bitLen; i++)
    {
        uint8 bitPos  = (uint8)(startBit + i);
        uint8 byteIdx = (uint8)(bitPos / 8u);
        uint8 bitIdx  = (uint8)(bitPos % 8u);

        if (((buf[byteIdx] >> bitIdx) & 1u) != 0u)
        {
            value |= ((uint32)1u << i);
        }
    }
    return value;
}

/* Doc/ghi gia tri qua con tro void theo do rong signal */
static uint32 Com_ReadValue(const void *ptr, uint8 bitLen)
{
    uint32 v;

    if (bitLen <= 8u)       { v = *(const uint8 *)ptr;  }
    else if (bitLen <= 16u) { v = *(const uint16 *)ptr; }
    else                    { v = *(const uint32 *)ptr; }
    return v;
}

static void Com_WriteValue(void *ptr, uint8 bitLen, uint32 v)
{
    if (bitLen <= 8u)       { *(uint8 *)ptr  = (uint8)v;  }
    else if (bitLen <= 16u) { *(uint16 *)ptr = (uint16)v; }
    else                    { *(uint32 *)ptr = v;         }
}

/* ---------- API ---------- */
void Com_Init(void)
{
    uint8 i;

    for (i = 0u; i < COM_PDU_LENGTH; i++)
    {
        Com_TxPduBuf[i] = 0u;        /* init value cua signal */
        Com_RxPduBuf[i] = 0u;
    }
    Com_RxTimeoutCnt = COM_RX_TIMEOUT_CYCLES;   /* chua nhan frame nao = dang timeout */
}

uint8 Com_SendSignal(Com_SignalIdType SignalId, const void *SignalDataPtr)
{
    uint8 ret = E_NOT_OK;

    if ((SignalId < COM_SIGNAL_COUNT) && (SignalDataPtr != NULL) &&
        (Com_SignalCfg[SignalId].isTx == TRUE))
    {
        Com_PackIntel(Com_TxPduBuf,
                      Com_SignalCfg[SignalId].startBit,
                      Com_SignalCfg[SignalId].bitLen,
                      Com_ReadValue(SignalDataPtr, Com_SignalCfg[SignalId].bitLen));
        ret = E_OK;
    }
    return ret;
}

uint8 Com_ReceiveSignal(Com_SignalIdType SignalId, void *SignalDataPtr)
{
    uint8 ret = E_NOT_OK;

    if ((SignalId < COM_SIGNAL_COUNT) && (SignalDataPtr != NULL) &&
        (Com_SignalCfg[SignalId].isTx == FALSE))
    {
        uint32 v = Com_UnpackIntel(Com_RxPduBuf,
                                   Com_SignalCfg[SignalId].startBit,
                                   Com_SignalCfg[SignalId].bitLen);
        Com_WriteValue(SignalDataPtr, Com_SignalCfg[SignalId].bitLen, v);
        ret = E_OK;
    }
    return ret;
}

boolean Com_IsRxTimeout(PduIdType RxPduId)
{
    (void)RxPduId;
    return (Com_RxTimeoutCnt >= COM_RX_TIMEOUT_CYCLES) ? TRUE : FALSE;
}

/* PduR goi khi co frame den */
void Com_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
    uint8 i;

    if ((RxPduId == COM_RXPDU_VEHICLE_DATA) && (PduInfoPtr != NULL) &&
        (PduInfoPtr->SduDataPtr != NULL) && (PduInfoPtr->SduLength == COM_PDU_LENGTH))
    {
        for (i = 0u; i < COM_PDU_LENGTH; i++)
        {
            Com_RxPduBuf[i] = PduInfoPtr->SduDataPtr[i];
        }
        Com_RxTimeoutCnt = 0u;       /* reset bo dem timeout */
    }
}

/* Goi dinh ky moi 10 ms boi scheduler/OS */
void Com_MainFunctionRx(void)
{
    if (Com_RxTimeoutCnt < COM_RX_TIMEOUT_CYCLES)
    {
        Com_RxTimeoutCnt++;
    }
}

void Com_MainFunctionTx(void)
{
    PduInfoType pdu;

    pdu.SduDataPtr = Com_TxPduBuf;
    pdu.SduLength  = COM_PDU_LENGTH;
    (void)PduR_ComTransmit(COM_TXPDU_ENGINE_DATA, &pdu);
}

Rte.h

c
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