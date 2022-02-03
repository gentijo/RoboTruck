import utime
from machine import I2C, Pin
from mpu9250 import MPU9250
from mpu6500 import MPU6500

i2c = I2C(0, scl=Pin(22), sda=Pin(21), freq=400000)
sensor = MPU9250(i2c)

print ("MPU9250 test")
print("MPU9250 id: " + hex(sensor.whoami))

while True:
    print(sensor.acceleration)
    print(sensor.gyro)
    print(sensor.magnetic)
    print(sensor.temperature)

    utime.sleep_ms(1000)

