/* Ví dụ 12: volatile. KHÔNG chạy file này (hàm wait_* có thể treo vĩnh viễn),
 * chỉ biên dịch ra assembly để xem:
 *   gcc -O2 -S -o volatile_demo.s volatile_demo.c
 */
int          flag_plain;      /* biến thường          */
volatile int flag_vol;        /* biến có volatile     */

void wait_plain(void)    { while (flag_plain == 0) { } }
void wait_volatile(void) { while (flag_vol == 0) { } }
