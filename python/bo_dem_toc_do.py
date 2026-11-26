def tinh_toc_do_trung_binh(quang_duong_km, thoi_gian_gio):
    """Tính tốc độ trung bình (km/h)"""
    if thoi_gian_gio <= 0:
        raise ValueError("Thời gian phải lớn hơn 0")
    return quang_duong_km / thoi_gian_gio


def kiem_tra_qua_toc(toc_do, gioi_han=120):
    """Kiểm tra xe có vượt quá tốc độ cho phép không"""
    return toc_do > gioi_han
