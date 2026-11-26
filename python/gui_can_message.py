import can
import cantools
import time


def gui_du_lieu_engine(rpm, nhiet_do):
    """Mã hóa và gửi 1 CAN message EngineData qua virtual bus"""
    # Đọc định nghĩa tín hiệu từ file DBC
    db = cantools.database.load_file('engine.dbc')
    message_def = db.get_message_by_name('EngineData')

    # Mã hóa: cantools tự động áp dụng đúng factor/offset/endianness theo DBC
    du_lieu_ma_hoa = message_def.encode({
        'EngineRPM': rpm,
        'EngineTemp': nhiet_do
    })

    # Gửi qua CAN bus
    bus = can.interface.Bus(channel='test', interface='virtual')
    msg = can.Message(
        arbitration_id=message_def.frame_id,   # lấy đúng ID từ DBC, không cần tự nhớ 0x100
        data=du_lieu_ma_hoa,
        is_extended_id=False
    )
    bus.send(msg)
    print(f"[GỬI] RPM={rpm}, Nhiệt độ={nhiet_do}°C, raw_bytes={list(du_lieu_ma_hoa)}")
    bus.shutdown()

    return msg


if __name__ == "__main__":
    gui_du_lieu_engine(rpm=3000, nhiet_do=25)
    time.sleep(0.5)
    gui_du_lieu_engine(rpm=800, nhiet_do=-10)