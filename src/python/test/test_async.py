from machine import UART

# Setup the connection to your GPS here
# This example uses UART 3 with RX on pin Y10
# Baudrate is 9600bps, with the standard 8 bits, 1 stop bit, no parity
uart = UART(1, 9600, rx=19, tx=18)
#uart.init(115200, bits=8, parity=None, stop=1)
#, rx=19, tx=18

# Basic UART --> terminal printer, use to test your GPS module
while True:
    if uart.any():
        print(uart.read(), end='')


