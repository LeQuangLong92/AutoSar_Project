#ifndef SWC_OVERSPEED_H
#define SWC_OVERSPEED_H

#define SWC_OVERSPEED_THRESHOLD_KMH  120u
#define SWC_DEBOUNCE_CYCLES          3u

void Swc_OverSpeed_Init(void);
void Swc_Run_OverSpeedWarning(void);     /* runnable, gọi mỗi chu kỳ */

#endif /* SWC_OVERSPEED_H */