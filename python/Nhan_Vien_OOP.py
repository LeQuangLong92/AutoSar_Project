class NhanVien:
    """Lớp cơ sở đại diện cho một nhân viên"""

    def __init__(self, ten, luong_co_ban):
        self.ten = ten
        self.luong_co_ban = luong_co_ban

    def tinh_luong(self):
        """Tính lương - lớp con sẽ ghi đè (override) phương thức này"""
        return self.luong_co_ban

    def __str__(self):
        return f"{self.ten}: {self.tinh_luong():,.0f}đ"


class NhanVienChinhThuc(NhanVien):
    """Nhân viên chính thức - có thêm thưởng theo % lương cơ bản"""

    def __init__(self, ten, luong_co_ban, phan_tram_thuong):
        super().__init__(ten, luong_co_ban)   # gọi __init__ của lớp cha
        self.phan_tram_thuong = phan_tram_thuong

    def tinh_luong(self):
        """Ghi đè cách tính lương: cộng thêm tiền thưởng"""
        thuong = self.luong_co_ban * self.phan_tram_thuong / 100
        return self.luong_co_ban + thuong


class NhanVienThoiVu(NhanVien):
    """Nhân viên thời vụ - lương tính theo số giờ làm"""

    def __init__(self, ten, luong_theo_gio, so_gio_lam):
        super().__init__(ten, luong_theo_gio)
        self.so_gio_lam = so_gio_lam

    def tinh_luong(self):
        """Ghi đè cách tính lương: lương giờ x số giờ làm"""
        return self.luong_co_ban * self.so_gio_lam


def main():
    # Danh sách nhân viên gồm nhiều loại khác nhau
    danh_sach_nhan_vien = [
        NhanVienChinhThuc("Nguyễn Văn A", 15000000, 20),
        NhanVienThoiVu("Trần Thị B", 50000, 120),
        NhanVienChinhThuc("Lê Văn C", 20000000, 10),
        NhanVienThoiVu("Phạm Thị D", 45000, 80),
    ]

    print("=== BẢNG LƯƠNG NHÂN VIÊN ===")
    for nv in danh_sach_nhan_vien:
        print(nv)   # tự động gọi __str__, bên trong gọi tinh_luong() riêng của từng loại

    # Dùng list comprehension để tính tổng lương toàn công ty
    tong_luong = sum(nv.tinh_luong() for nv in danh_sach_nhan_vien)
    print(f"\nTổng chi lương: {tong_luong:,.0f}đ")

    # Lọc ra những nhân viên có lương trên 15 triệu
    luong_cao = [nv.ten for nv in danh_sach_nhan_vien if nv.tinh_luong() > 15000000]
    print(f"Nhân viên lương trên 15 triệu: {luong_cao}")


if __name__ == "__main__":
    main()