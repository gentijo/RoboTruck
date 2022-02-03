


class LOLIN_I2C_MOTOR:

#Motor Command
    GET_SLAVE_STATUS = 0x01
    RESET_SLAVE = 0x02
    CHANGE_I2C_ADDRESS = 0x03
    CHANGE_STATUS = 0x04
    CHANGE_FREQ = 0x05
    CHANGE_DUTY = 0x06


#MOTOR_STATUS
    MOTOR_STATUS_STOP = 0x00
    MOTOR_STATUS_CCW = 0x02
    MOTOR_STATUS_CW = 0x03
    MOTOR_STATUS_SHORT_BRAKE = 0x04
    MOTOR_STATUS_STANDBY = 0x05


#MOTOR_CHANNEL
    MOTOR_CH_A=0x00
    MOTOR_CH_B=0x01
    MOTOR_CH_BOTH=0x03

    def __init__(self, i2c, addr):
        self.i2c = i2c
        self.address = addr
        
        
    # Change Motor Status.
    # 
    # ch： Motor Channel
    #  MOTOR_CH_A
    #  MOTOR_CH_B
    #  MOTOR_CH_BOTH
    # 
    # sta: Motor Status
    #   MOTOR_STATUS_STOP
    #   MOTOR_STATUS_CCW
    #   MOTOR_STATUS_CW
    #   MOTOR_STATUS_SHORT_BRAKE
    #   MOTOR_STATUS_STANDBY

    def changeStatus(self, ch, sta):
        send_data[0] = CHANGE_STATUS
        send_data[1] = ch
        send_data[2] = sta
        result = sendData(send_data, 3);
        return result;

    # Change Motor Frequency
    # 
    # ch： Motor Channel
    #  MOTOR_CH_A
    #  MOTOR_CH_B
    #  MOTOR_CH_BOTH
    # 
    # freq: PWM frequency (Hz)
    #  1 - 80,000 Hz
    #
    def changeFreq(self, ch, freq):
        send_data[0] = CHANGE_FREQ
        send_data[1] = ch

        send_data[2] = (uint8_t)(freq & 0xff)
        send_data[3] = (uint8_t)((freq >> 8) & 0xff)
        send_data[4] = (uint8_t)((freq >> 16) & 0xff)
        
        result = sendData(send_data, 5)

        return result


    # Change Motor Duty.
    # 
    #     ch： Motor Channel
    #             MOTOR_CH_A
    #             MOTOR_CH_B
    #             MOTOR_CH_BOTH
    #     
    #     duty: PWM Duty (%)
    #             0.01 - 100.00 (%)
    def changeDuty(self, ch, duty):
        
        _duty = duty * 100;

        send_data[0] = CHANGE_DUTY;
        send_data[1] = ch;

        send_data[2] = (uint8_t)(_duty & 0xff);
        send_data[3] = (uint8_t)((_duty >> 8) & 0xff);
        
        result = sendData(send_data, 4);
        return result;


    #
    # Reset Device.
    #
    def reset(self):
        send_data[0] = RESET_SLAVE
        result = sendData(send_data, 1)
        return result


    #
    # Change Device I2C address
    #  address: when address=0, address>=127, will change address to default I2C address 0x31
    #
    def changeAddress(address):
        send_data[0] = CHANGE_I2C_ADDRESS
        send_data[1] = address
        result = sendData(send_data, 2)

        return result


    #
    # Get PRODUCT_ID and Firmwave VERSION
    #
    def getInfo(void):
        #send_data = bytearray(2)
        
        data = i2c.readfrom_mem(self.address, GET_SLAVE_STATUS, 2)
        print(data)
        
        #result = self.i2c.(send_data, 1);
        if result == 0:
            self.PRODUCT_ID = get_data[0]
            self.VERSION = get_data[1]
        else:
            self.PRODUCT_ID = 0
            self.VERSION = 0


        return result


    #
    # Send and Get I2C Data
    #
#     def sendData(self, data, len):
# 
#         if ((_address == 0) || (_address >= 127)):
#             return 1;
#         else:
#             Wire.beginTransmission(_address);
#                 for (i = 0; i < len; i++):
#                     Wire.write(data[i]);
#             Wire.endTransmission();
#             sleep(50);
# 
#         if (data[0] == GET_SLAVE_STATUS):
#             Wire.requestFrom(_address, 2);
#         else:
#             Wire.requestFrom(_address, 1);
# 
#         i = 0;
# 
#         while (Wire.available()):
#             get_data[i] = Wire.read();
#             i++;
# 
#         return 0;
