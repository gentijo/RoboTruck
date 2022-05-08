# micropyGPS Sentence Test
# When properly connected to working GPS module,
# will print the names of the sentences it receives
# If you are having issues receiving sentences, use UART_test.py to ensure
# your UART is hooked up and configured correctly

from machine import UART
from micropyGPS import MicropyGPS

# Setup the connection to your GPS here
# This example uses UART 3 with RX on pin Y10
# Baudrate is 9600bps, with the standard 8 bits, 1 stop bit, no parity
uart = UART(1, 9600, rx=19, tx=18)

# Instatntiate the micropyGPS object
my_gps = MicropyGPS()

# Continuous Tests for characters available in the UART buffer, any characters are feed into the GPS
# object. When enough char are feed to represent a whole, valid sentence, stat is set as the name of the
# sentence and printed
while True:
    if uart.any():
        buf = uart.read()        
        for ch in buf:
            stat = my_gps.update(chr(ch)) # Note the conversion to to chr, UART outputs ints normally

        print("Lon: ", my_gps.longitude_string())
        print("Lat: ", my_gps.latitude_string())
        print("Time: ", my_gps.date_string())
        print("Sats: ", my_gps.satellites_in_view, ":", my_gps.satellites_in_use)
        
        if stat:
            print("xxx ", stat)
            stat = None
