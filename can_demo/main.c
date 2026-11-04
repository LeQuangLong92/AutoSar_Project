#include <stdio.h>
#include "Com.h"
#include "Can.h"
#include "Swc.h"

#define CAN_ID_VEHICLE_DATA  (0x200u)
#define SIM_TICKS            (15u)

int main(void)
{
    uint8 tick;

    Com_Init();

    for (tick = 0u; tick < SIM_TICKS; tick++)
    {
        printf("--- tick %u (t=%u ms) ---\n", (unsigned)tick, (unsigned)tick * 10u);

        Com_MainFunctionRx();
        Swc_DashRx_Run10ms();
        Swc_EngineTx_Run10ms();
        Com_MainFunctionTx();

        /* ECU khac gui VehicleData o tick 3..8, sau do im lang -> gay timeout */
        if ((tick >= 3u) && (tick <= 8u))
        {
            uint8  frame[8] = {0u};
            uint16 raw = (uint16)(4000u + ((unsigned)(tick - 3u) * 500u));   /* 40.00, 45.00, ... km/h */

            frame[0] = (uint8)(raw & 0xFFu);
            frame[1] = (uint8)(raw >> 8);
            Can_Sim_Receive(CAN_ID_VEHICLE_DATA, frame, 8u);
        }
    }
    return 0;
}