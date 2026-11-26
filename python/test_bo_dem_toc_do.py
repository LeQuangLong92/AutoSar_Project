
import pytest
from bo_dem_toc_do import tinh_toc_do_trung_binh,kiem_tra_qua_toc


def test_tinh_toc_do_hop_le():
    """ Test với số bình thường"""
    ket_qua = tinh_toc_do_trung_binh(100,2)
    assert ket_qua ==50


def test_tinh_toc_do_le():
    """Test với số thập phân"""
    ket_qua = tinh_toc_do_trung_binh(150, 3)
    assert ket_qua == 50.0


def test_phai_bao_loi_khi_thoi_gian_bang_khong():
    """ Test hàm kiểm tra tốc độ trung bình phải báo lỗi khi thời gian bằng 0"""
    with pytest.raises(ValueError):
        tinh_toc_do_trung_binh(100,0)

def test_qua_toc():
    assert kiem_tra_qua_toc(150) == True
    assert kiem_tra_qua_toc(100) == False

