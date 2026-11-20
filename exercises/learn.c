#include <stdio.h>
#include <stdint.h>

// 1. Định nghĩa địa chỉ thanh ghi cố định bằng "Hằng con trỏ" và "Volatile"
/* #define LED_REG   (*(volatile uint8_t * const)0x40001000)

// Định nghĩa các mặt nạ bit (Mask)
#define MASK_RED    (1U << 0)
#define MASK_GREEN  (1U << 1)
#define MASK_BLUE   (1U << 2)
#define MASK_BLINK  (1U << 3) */

typedef struct {
    uint8_t Red_En : 1 ; 
    uint8_t Green_En : 1;
    uint8_t Blue_En : 1;
    uint8_t Blink : 1 ;
    uint8_t Reserved : 4 ;

}Led_Reg_t;
// Hàm in nhị phân của bạn (đã sửa lỗi) để quan sát sự thay đổi của thanh ghi
static void print_bits(const char *label, Led_Reg_t reg) {
    uint8_t *val = (uint8_t*)&reg; // Chuyển đổi struct sang con trỏ uint8_t
    printf("%-15s", label);
    for (int i = 7; i >= 0; i--) {
        printf("%u", (unsigned)((*val >> i) & 1U));
        if ((i % 4 == 0) && (i != 0)) printf(" ");
    }
    printf(" (0x%02X)\n", (unsigned)*val);
}


/* 
static void bin(const char *label, uint32_t v, int bits)
{
    int i;
    // In nhãn ra màn hình, căn lề trái tối thiểu 10 ký tự (-10) giúp các dòng thẳng hàng
    printf("%-10s", label); 
    
    // Vòng lặp duyệt từ bit cao nhất (bits-1) lùi dần về bit 0
    for (i = bits - 1; i >= 0; i--)
    {
        // Dịch phải i bit, AND với 1 để lấy bit cuối rồi ép kiểu sang unsigned để in
        printf("%u", (unsigned)((v >> i) & 1U));
        
        // Cứ sau 4 bit thì chèn 1 khoảng trắng (trừ bit cuối cùng i=0)
        if ((i%4==0)&&(i!=0))
        {
            printf(" ");
        }
    }
    // In thêm giá trị dưới dạng Hex (Hệ 16) ở cuối dòng để đối chiếu nhanh
    printf(" (0x%X)\n", (unsigned)v);    
} */
int main(void)
{  
     
    /* uint32_t reg = 0x2CU; // Khởi tạo thanh ghi với giá trị 0x2C (00101100)
    uint8_t mask = 1U<<0 ; // Tạo mặt nạ để set bit 0 (00000001)
 */
/*     printf("VD1: Set bit 0\n");
    bin("reg", reg, 8);  // In ra nhãn "data" với giá trị 0xEF (11101111) trong 7 bit
    bin("mask",mask,8);// In ra nhãn "mask" với giá trị 1 (00000001) trong 7 bit
    bin("reg|mask",reg|mask,8); // In ra nhãn "data|mask" với giá trị 0xEF | 1 = 0xEF (11101111   

    printf("VD2: Clear bit2 \n");
    bin("reg", reg, 8);  // In ra nhãn "data" với giá trị 0xEF (11101111) trong 7 bit
    bin("mask",mask<<2,8); // In ra nhãn "mask
    bin("reg&~mask",reg&~(mask<<2),8); // In ra nhãn "data&~mask" với giá trị 0xEF & ~1 = 0xEE (11101110) 

    printf("VD3:Toggle bit 3\n"); // Dao bit so 3
    bin("reg", reg, 8);  // In ra nhãn "data"
    bin("mask",mask<<3,8); // In ra nhãn "mask"
    bin("reg^mask",reg^(mask<<2),8); // In ra nhãn "data^mask" với giá trị 0xEF ^ 1 = 0xEE (11101110))
    
    printf("VD4:Read bit 3\n"); // Đọc bit số 3)
    bin("reg", reg, 8);  // In ra nhãn "data"
    bin("reg>>3",reg>>3,8); // In ra nhãn "mask"
    bin("&mask",(reg>>3)&mask,8); // In ra nhãn "data&mask" với giá trị 0xEF & 1 = 0xEE (11101110)))
    
    printf("VD5: Dem bit bang v &=v-1,v=0xB4\n"); // Đếm số bit 1 bằng cách v &= v-1
    {
        uint32_t v = 0xB4U; int n = 0;
        bin("v",v,8);
        while(v!=0U){ 
            v &=v-1U;n++;
            bin("v",v,8);}
        printf("so lan lap = %d\n",n);
    }
     */

   /*  printf("VD6: field_get(0x3CA5,pos 4,len 12)\n"); */ // Lấy trường bit từ vị trí pos với độ dài len
    /* bin("cab",0x3CA5U,16); // In ra nhãn "data" với giá trị 0x3CA5 (0011110010100101) trong 16 bit
    bin("cab>>4",0x3CA5U>>4,16); // In ra nhãn "data" với giá trị 0x3CA5 >> 4 = 0x03CA (0000001111001010) trong 16 bit
    uint16_t mask16 = (1U<<12)-1U; // Tạo mặt nạ để lấy 12 bit (0000111111111111)
    bin("mask",mask16,16); // In ra nhãn "mask" với giá trị 0x0FFF (0000111111111111) trong 16 bit
    bin("ket qua",(0x3CA5U>>4)&mask16,16); // In ra nhãn "ket qua" với giá trị 0x3CA5 & 0x0FFF = 0x0CA5 (000011001010010１) trong １6 bit */
    
/*     bin("ket qua",(0x3CA5U>>4)&((1U<<12)-1U),16); */
/* 
    printf("VD7: field_set(0xFFFF, pos = 4, len = 4, value = 0):\n");
    uint16_t mask2 =((1U<<4)-1U)<<4;
    bin("data",0xFFFFU,16); // In ra nhãn "data" với giá trị 0xFFFF (1111111111111111) trong 16 bit
    bin("mask",mask2,16); // In ra nhãn "mask" với giá trị 0x00F0 (0000000011110000) trong 16 bit
    bin("ket qua",0xFFFFU & ~mask2 ,16); // In ra nhãn "~mask" với giá trị 0xFF0F (1111111100001111) trong 16 bit */

   /*  printf("VD8: Dao thu tu byte swap32(0x12345678) thanh 0x87654321:\n");
    uint32_t v = 0x12345678U;
    uint32_t swap32(uint32_t v)
     {
    return ((v & 0x000000FFU)<<24) | ((v & 0x0000FF00U)<<8) | ((v & 0x00FF0000U)>>8) | ((v & 0xFF000000U)>>24);
     }

    bin("v",v,32); // In ra nhãn "data" với giá trị 0x12345678 (00010010001101000101011001111000) trong 32 bit
    uint32_t v1 = (v & 0x000000FFU)<<24 ; // Lấy byte thấp nhất (0x78)
    bin("v1",v1,32); // In ra nhãn "v1" với giá trị 0x78000000 (01111000000000000000000000000000) trong 32 bit
    uint32_t v2 = (v & 0x0000FF00U)<<8 ; // Lấy byte thứ 2 (0x56)
    bin("v2",v2,32); // In ra nhãn "v2" với giá trị 0x00560000 (00000000010101100000000000000000) trong 32 bit
    uint32_t v3 = (v & 0x00FF0000U)>>8 ; // Lấy byte thứ 3 (0x34)
    bin("v3",v3,32); // In ra nhãn "v3" với giá trị 0x00003400 (00000000000000000011010000000000) trong 32 bit
    uint32_t v4 = (v&0xFF000000U)>>24 ; // Lấy byte cao nhất (0x12)
    bin("v4",v4,32); // In ra nhãn "v4" với giá trị 0x00000012 (00000000000000000000000000010010) trong 32 bit
    uint32_t result = v1 | v2 | (v3) | (v4);;
    bin("result",result,32); // In ra nhãn "result" với giá trị 0x87654321 (10000111011001010100001100100001) trong 32 bit
    bin("swap32(v)",swap32(v),32); // In ra nhãn "swap32(v)" với giá trị 0x87654321 (10000111011001010100001100100001) trong 32 bit */
/*     printf("VD9: Padding Struct\n");
    typedef struct {
        uint8_t a;
        uint32_t b;
        uint8_t c;
    }bad;
    printf("sizeof(bad) = %u\n", (unsigned)sizeof(bad));
    typedef struct {
        uint32_t b;
        uint8_t a;
        uint8_t c;

    } good;
    printf("sizeof(good) = %u\n", (unsigned)sizeof(good));
 */
/*     printf("VD10: Endianncess\n");
    {
    uint32_t v = 0x12345678U;
    const uint8_t *p = (const uint8_t*)&v; // Nhìn v như 4 byte liên tiếp
    }
    printf("VD11: Con tro va mang \n");
    {
    uint8_t buf[4] = {10U,20U,30U,40U};
    uint8_t *p = &buf[0]; // p trỏ tới phần tử đầu tiên của mảng buf
    uint8_t * const const_p = buf; // p trỏ tới phần tử đầu tiên của mảng buf
    const uint8_t *ptr2 =buf; // ptr2 trỏ tới phần tử đầu tiên của mảng buf
    *const_p = 50U; // Ghi giá trị 50 vào phần tử đầu tiên của mảng buf thông qua con trỏ const_p
    ptr2++; // Tăng con trỏ ptr2 để trỏ tới phần tử tiếp theo của mảng buf      
    //ptr2 =60U; // Ghi giá trị 60 vào phần tử thứ hai của mảng buf thông qua con trỏ ptr2
    printf("Gia tri cua buf[0] sau khi ghi qua const_p: %u\n",*(const_p));
    for(uint8_t i = 0U;i<4U;i++)
    {                                                                                                                                                                                                                                                                                   
        printf("buf[%u] = %u\n",i,*p);
        p++; // Tăng con trỏ p để trỏ tới phần tử tiếp theo                                                                                                                                                                                                                                                                                                                                                                                         
    }
    uint32_t x =5 ;
    uint32_t *q = &x; // q trỏ tới biến x                                       
    printf("Gia tri cua x :%d\n",x);
    printf("Gia tri cua q: %p\n",q);
    *q = 7; // Ghi giá trị 7 vào biến x thông qua con trỏ q
    printf("Gia tri cua x sau khi ghi qua con tro q: %d\n",*q);
    } */
    
/*   // Giả lập vùng nhớ cho thanh ghi (vì chạy trên PC không có phần cứng thật)
    uint8_t virtual_reg = 0x00; 
    #undef LED_REG
    #define LED_REG virtual_reg // Trỏ tạm vào biến này để test code

    bin("Trạng thái đầu", LED_REG, 8);

    // 2. NHIỆM VỤ 1: Hãy dùng phép toán BITWISE thích hợp để:
    // "BẬT" (Set) cùng lúc LED Đỏ và LED Lam lên 1 (Sử dụng các MASK ở trên)
    LED_REG |= (MASK_RED | MASK_BLUE);
    bin("Sau khi bật R,B", LED_REG, 8);

    // 3. NHIỆM VỤ 2: Hãy dùng phép toán BITWISE thích hợp để:
    // "TẮT" (Clear) LED Đỏ đi, nhưng giữ nguyên các LED và chế độ khác
    LED_REG &= (~MASK_RED);
    bin("Sau khi tắt R", LED_REG, 8);

    // 4. NHIỆM VỤ 3: Hãy dùng phép toán BITWISE thích hợp để:
    // "ĐẢO" (Toggle) liên tục trạng thái bit BLINK_MODE 3 lần bằng vòng lặp for
    printf("\n--- Bắt đầu Toggle BLINK_MODE ---\n");
    for (int i = 0; i < 3; i++) {
        LED_REG = LED_REG ^MASK_BLINK;
        bin("Đang Toggle", LED_REG, 8);
    } */
    
    
// Khai báo một biến cấu trúc thanh ghi, ban đầu tắt hết các bit (bằng 0)
    Led_Reg_t my_led = {0}; 
    
    print_bits("Trạng thái đầu", my_led);

    // 1. NHIỆM VỤ 1: Hãy BẬT LED Đỏ (RED_EN) và LED Lam (BLUE_EN) lên 1
    my_led.Red_EN = 1;
    my_led.Blue_EN = 1;
    print_bits("Sau khi bật R,B", my_led);

    // 2. NHIỆM VỤ 2: Hãy TẮT LED Đỏ đi, và BẬT chế độ nhấp nháy (BLINK_MODE) lên 1
    my_led.Red_EN = 0;
    my_led.Blink = 1;
    print_bits("Sau khi sửa", my_led);

    // 3. NHIỆM VỤ 3: Hãy dùng vòng lặp for lặp 3 lần, mỗi lần hãy ĐẢO trạng thái 
    // của LED Lục (GREEN_EN). (Mẹo nhỏ: có thể dùng toán tử logic đảo '!')
    printf("\n--- Bắt đầu Toggle GREEN_EN ---\n");
    for (int i = 0; i < 3; i++) {
        my_led.GREEN_EN = ! my_led.GREEN_EN; 
        print_bits("Đang Toggle G", my_led);
    return 0;

}
