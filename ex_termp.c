#include <stdio.h>
#include <stdint.h>

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
        if ((i % 4 == 0) && (i != 0))
        {
            printf(" ");
        }
    }
    // In thêm giá trị dưới dạng Hex (Hệ 16) ở cuối dòng để đối chiếu nhanh
    printf(" (0x%X)\n", (unsigned)v);    
}