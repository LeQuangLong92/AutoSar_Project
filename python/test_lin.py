import pytest
import ldfparser


@pytest.fixture
def frame_def():
    ldf = ldfparser.parse_ldf(path="door_control.ldf")
    return ldf.get_unconditional_frame('FRAME_A')


@pytest.mark.parametrize("vi_tri_cua_so, trang_thai_khoa", [
    (0, 0),
    (100, 1),
    (50, 0),
])
def test_ma_hoa_giai_ma_ldf(frame_def, vi_tri_cua_so, trang_thai_khoa):
    du_lieu = frame_def.encode_raw({
        'WindowPosition': vi_tri_cua_so,
        'DoorLockStatus': trang_thai_khoa
    })
    ket_qua = frame_def.decode(du_lieu)

    assert ket_qua['WindowPosition'] == vi_tri_cua_so
    assert ket_qua['DoorLockStatus'] == trang_thai_khoa