class san_pham:
    """Tạo 1 Class là sản phẩm"""

    def __init__(self, ten_san_pham, gia, so_luong_ton):
        self.ten_san_pham = ten_san_pham
        self.gia = gia
        self.so_luong_ton = so_luong_ton

    def ban_hang(self, so_luong):
        if so_luong > self.so_luong_ton:
            print(f"Số lượng tồn kho không đủ; Số lượng tồn kho hiện tại là: {self.so_luong_ton} \n")
        else:
            self.so_luong_ton -= so_luong
            Doanh_thu = so_luong * self.gia

            print(f"Đã bán : {so_luong} ; Số lượng tồn kho hiện tại là : {self.so_luong_ton}\n")
            print(f" Doanh thu bán hàng : {Doanh_thu:,.0f}đ\n")

    def nhap_hang(self, so_luong):
        self.so_luong_ton += so_luong
        print(f"Đã nhập số lượng hàng : {so_luong} : Số lượng tồn kho hiện tại : {self.so_luong_ton}")


def main():
    Ao = san_pham("Áo Thun", 200000, 10)
    print(f"{Ao.ten_san_pham}")
    print(f"{Ao.gia:,.0f}đ")
    print(f"{Ao.so_luong_ton}")
    Ao.ban_hang(5)
    Ao.ban_hang(15)
    Ao.nhap_hang(20)


if __name__ == "__main__":
    main()