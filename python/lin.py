import ldfparser
import binascii


def demo_ldf():
    ldf = ldfparser.parse_ldf(path ="door_control.ldf")
    frame = ldf.get_unconditional_frame('FRAME_A')
    # return frame
    baudrate = ldf.get_baudrate()
    print(f"baudrate: {baudrate}")
    du_lieu = frame.encode_raw({
        'WindowPosition' : 40,
        'DoorLockStatus' : 1
    })
    print(f"Du lieu ma hoa: {binascii.hexlify(du_lieu)}")
    ket_qua = frame.decode(du_lieu)
    print(f"{ket_qua}")

if __name__ == "__main__":
    demo_ldf()