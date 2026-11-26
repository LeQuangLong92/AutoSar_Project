





class Dong_vat:
    def __init__(self,Ten,tuoi):
        self.Ten = Ten
        self.tuoi=tuoi
    def tieng_keu(self):
        """ Lop con se ghi de override - tinh Da hinh polymorphism"""
        return ""
    def luong_thuc_an(self):
        """ Lop con se ghi de len - tinh da hinh polymorphism"""
        return 0
    def __str__(self):
        return f"{self.Ten} , {self.tuoi} tuổi , {self.luong_thuc_an(): ,.0f}kg , Tiếng kêu : {self.tieng_keu()} \n"

class Bo(Dong_vat):
    def __init__(self,Ten,tuoi,San_luong_sua):
        super().__init__(Ten,tuoi)
        self.San_luong_sua=San_luong_sua

    def tieng_keu(self):
        return "Ù Ò"
    def luong_thuc_an(self):
        return 7


class Ga(Dong_vat):
    def __init__(self,Ten,tuoi,San_luong_trung):
        super().__init__(Ten,tuoi)
        self.San_luong_trung=San_luong_trung
    def tieng_keu(self):
        return "Ò Ó O"
    def luong_thuc_an(self):
        return 1.2



def main():
    Trang_trai = [
        Bo("Bò Vàng",3,San_luong_sua= 20),
        Bo("Bò VN",5,San_luong_sua = 30),
        Ga("Gà Tam Hoàng",1,San_luong_trung=3),
        Ga("Tre",0.8,San_luong_trung = 6)

    ]
    print("------DANH SÁCH VẬT NUÔI TRANG TRẠI------\n")
    for cv in Trang_trai:
        print(cv)
    print("TÍNH TỔNG LƯỢNG THỨC ĂN TRANG TRẠI \n")
    Tong_thuc_an = sum(cv.luong_thuc_an()for cv in Trang_trai )
    print(f" Tổng Thức Ăn : {Tong_thuc_an}kg")

    print("TÍNH SỐ LƯỢNG TỪNG CON VẬT TRONG TRANG TRẠI")
    bo = sum(1 for cv in Trang_trai if isinstance (cv,Bo))
    ga = sum(1 for cv in Trang_trai if isinstance(cv,Ga) )
    print(f"Số lượng bò : {bo} con; Số lượng gà : {ga} con\n")
    
if __name__ == "__main__":
    main()
    
