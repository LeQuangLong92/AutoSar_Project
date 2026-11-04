#ifndef CAN_H
#define CAN_H

#include "Std_Types.h"

typedef struct
{
    PduIdType   swPduHandle;
    uint8       length;
    Can_IdType  id;
    uint8      *sdu;
} Can_PduType;

Std_ReturnType Can_Write(uint8 Hth, const Can_PduType *PduInfo);

/* Chi co trong mo phong: gia lap ECU khac gui frame len bus */
void Can_Sim_Receive(Can_IdType id, const uint8 *data, uint8 dlc);

#endif