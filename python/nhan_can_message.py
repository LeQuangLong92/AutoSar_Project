import can
import cantools


def nhan_va_giai_ma(so_luong_can_nhan=1, timeout=3.0):
    """Lắng nghe CAN bus, giải mã message nhận được theo DBC"""
    db = cantools.database.load_file('engine.dbc')
    bus = can.interface.Bus(channel='test', interface='virtual')

    ket_qua = []
    for _ in range(so_luong_can_nhan):
        msg = bus.recv(timeout=timeout)
        if msg is None:
            print("Không nhận được message nào trong thời gian chờ!")
            break

        # cantools tự tìm đúng message definition dựa theo arbitration_id
        decoded = db.decode_message(msg.arbitration_id, msg.data)
        print(f"[NHẬN] ID={hex(msg.arbitration_id)}, Giải mã={decoded}")
        ket_qua.append(decoded)

    bus.shutdown()
    return ket_qua


if __name__ == "__main__":
    nhan_va_giai_ma(so_luong_can_nhan=2)