class CongViec:
    """Lớp đại diện cho một công việc trong danh sách"""

    def __init__(self, noi_dung, hoan_thanh=False):
        self.noi_dung = noi_dung
        self.hoan_thanh = hoan_thanh

    def danh_dau_xong(self):
        self.hoan_thanh = True

    def __str__(self):
        trang_thai = "x" if self.hoan_thanh else " "
        return f"[{trang_thai}] {self.noi_dung}"


class DanhSachCongViec: 
    """Lớp quản lý danh sách công việc, có thể lưu/đọc từ file"""

    def __init__(self, ten_file="todo.txt"):
        self.ten_file = ten_file
        self.danh_sach = []

    def them(self, noi_dung):
        self.danh_sach.append(CongViec(noi_dung))
        print(f"Đã thêm: {noi_dung}")

    def hoan_thanh(self, vi_tri):
        """Đánh dấu hoàn thành theo vị trí (bắt đầu từ 1)"""
        if 1 <= vi_tri <= len(self.danh_sach):
            self.danh_sach[vi_tri - 1].danh_dau_xong()
            print(f"Đã hoàn thành việc số {vi_tri}")
        else:
            print("Vị trí không hợp lệ!")

    def hien_thi(self):
        print("\n=== DANH SÁCH CÔNG VIỆC ===")
        if not self.danh_sach:
            print("Chưa có công việc nào.")
            return
        for i, cv in enumerate(self.danh_sach, start=1):
            print(f"{i}. {cv}")

    def luu_vao_file(self):
        """Ghi danh sách công việc ra file"""
        with open(self.ten_file, "w", encoding="utf-8") as f:
            for cv in self.danh_sach:
                trang_thai = "1" if cv.hoan_thanh else "0"
                f.write(f"{trang_thai}|{cv.noi_dung}\n")
        print(f"Đã lưu vào file {self.ten_file}")

    def doc_tu_file(self):
        """Đọc danh sách công việc từ file (nếu có)"""
        try:
            with open(self.ten_file, "r", encoding="utf-8") as f:
                self.danh_sach = []
                for dong in f:
                    trang_thai, noi_dung = dong.strip().split("|", 1)
                    cv = CongViec(noi_dung, hoan_thanh=(trang_thai == "1"))
                    self.danh_sach.append(cv)
            print(f"Đã đọc {len(self.danh_sach)} công việc từ file")
        except FileNotFoundError:
            print("Chưa có file lưu trước đó, bắt đầu danh sách mới.")


def main():
    ds = DanhSachCongViec("todo.txt")

    ds.doc_tu_file()      # Đọc dữ liệu cũ (nếu có) khi mở chương trình
    ds.hien_thi()

    ds.them("Học Python")
    ds.them("Làm bài tập OOP")
    ds.them("Đọc sách")

    ds.hoan_thanh(1)       # Đánh dấu "Học Python" là xong

    ds.hien_thi()
    ds.luu_vao_file()      # Lưu lại vào file để lần sau mở vẫn còn


if __name__ == "__main__":
    main()