import pytest
import cantools


@pytest.fixture
def message_def():
    """Fixture: load sẵn định nghĩa message, dùng chung cho mọi test"""
    db = cantools.database.load_file('engine.dbc')
    return db.get_message_by_name('EngineData')


@pytest.mark.parametrize("rpm, nhiet_do", [
    (3000, 25),
    (800, -10),
    (0, -40),      # giá trị biên: RPM = 0, nhiệt độ thấp nhất
    (16000, 215),  # giá trị biên: RPM và nhiệt độ cao nhất
])
def test_ma_hoa_giai_ma_khong_mat_du_lieu(message_def, rpm, nhiet_do):
    """Kiểm tra: mã hóa rồi giải mã lại phải ra đúng giá trị ban đầu"""
    du_lieu_ma_hoa = message_def.encode({'EngineRPM': rpm, 'EngineTemp': nhiet_do})
    ket_qua_giai_ma = message_def.decode(du_lieu_ma_hoa)

    assert ket_qua_giai_ma['EngineRPM'] == rpm
    assert ket_qua_giai_ma['EngineTemp'] == nhiet_do


def test_rpm_vuot_gioi_han_phai_bao_loi(message_def):
    """Kiểm tra: RPM vượt quá 16000 (giới hạn trong DBC) phải bị từ chối"""
    with pytest.raises(cantools.database.EncodeError):
        message_def.encode({'EngineRPM': 20000, 'EngineTemp': 25})


def test_frame_id_dung_theo_dbc(message_def):
    """Kiểm tra: CAN ID phải đúng 256 (0x100) như đã định nghĩa trong DBC"""
    assert message_def.frame_id == 256