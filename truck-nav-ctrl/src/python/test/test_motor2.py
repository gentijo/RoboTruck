import utime
from machine import I2C, Pin
from LolinMotorShield import LOLIN_I2C_MOTOR

i2c = I2C(0, scl=Pin(22), sda=Pin(21), freq=400000)
print(i2c.scan())

m1 = LOLIN_I2C_MOTOR(i2c, 48)

#data = bytearray(2)
data = i2c.readfrom_mem(48, LOLIN_I2C_MOTOR.GET_SLAVE_STATUS, 2)
print(data)
#i2c.readfrom_mem_into(48, LOLIN_I2C_MOTOR.GET_SLAVE_STATUS, data)
#print(data)