#ifndef CAN_SIGNAL_H
#define CAN_SIGNAL_H

#include "std_types.h"

/* Giai nen signal Intel Little Edian : LSB tai start bit, */

Std_ReturnType Can_UnpackIntel(
    const uint8_t *data, uint8_t dlc, 
    uint8_t startBit, uint8_t lenght, uint32_t *raw );

/* Dong goi Signal Intel Little Endian */
Std_ReturnType Can_PackIntel(
    uint8_t *data, uint8_t dlc, 
    uint8_t startBit, uint8_t lenght, uint32_t raw );
    
#endif /* CAN_SIGNAL_H */
