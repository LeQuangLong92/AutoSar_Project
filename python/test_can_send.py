import can


def gui_tin_hieu():
    """ Gửi 1 CAN Message qua CAN virtual  bus"""
    #Tạo một kết nổi tới CAN BUS ảo
    bus = can.interface.bus(channel = 'test',interface = 'vitural')
    # Tạo 1 message: ID = 0x123, dữ liệu 8 byte
    msg = can.Message(arbitration_id =0x123,
                      data = [0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08],
                      is_extended_id = False
                      )
    bus.send(msg)
    print(f"Da gui : ID ={hex(msg.arbitration_id)} , Data ={list(msg.data)}")
    bus.shutdonw()
    
if __name__=='__main__':
    gui_tin_hieu()