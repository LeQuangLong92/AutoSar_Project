#include "can_signal.h"

static Std_ReturnType Can_CheckArgs(uint8_t dlc, uint8_t startBit, uint8_t length)
{
    Std_ReturnType ret = E_OK;

    if ((dlc > 8u) || (length == 0u) || (length > 32u))
    {
        ret = E_NOT_OK;
    }
    else if (((uint16_t)startBit + (uint16_t)length) > ((uint16_t)dlc * 8u))
    {
        ret = E_NOT_OK;             /* signal vượt quá độ dài frame */
    }
    else
    {
        /* tham số hợp lệ */
    }
    return ret;
}

Std_ReturnType Can_UnpackIntel(const uint8_t *data, uint8_t dlc,
                               uint8_t startBit, uint8_t length,
                               uint32_t *raw)
{
    uint32_t value = 0u;
    uint8_t  i;
    uint8_t  bit;

    if ((data == NULL_PTR) || (raw == NULL_PTR))
    {
        return E_NOT_OK;
    }
    if (Can_CheckArgs(dlc, startBit, length) != E_OK)
    {
        return E_NOT_OK;
    }

    for (i = 0u; i < length; i++)
    {
        bit = (uint8_t)(startBit + i);
        value |= (uint32_t)((data[bit / 8u] >> (bit % 8u)) & 1u) << i;
    }
    *raw = value;
    return E_OK;
}

Std_ReturnType Can_PackIntel(uint8_t *data, uint8_t dlc,
                             uint8_t startBit, uint8_t length,
                             uint32_t raw)
{
    uint8_t i;
    uint8_t bit;
    uint8_t mask;

    if (data == NULL_PTR)
    {
        return E_NOT_OK;
    }
    if (Can_CheckArgs(dlc, startBit, length) != E_OK)
    {
        return E_NOT_OK;
    }
    if ((length < 32u) && ((raw >> length) != 0u))
    {
        return E_NOT_OK;            /* giá trị không vừa số bit của signal */
    }

    for (i = 0u; i < length; i++)
    {
        bit  = (uint8_t)(startBit + i);
        mask = (uint8_t)(1u << (bit % 8u));
        if (((raw >> i) & 1u) != 0u)
        {
            data[bit / 8u] |= mask;
        }
        else
        {
            data[bit / 8u] &= (uint8_t)~mask;
        }
    }
    return E_OK;
}