#include <Wire.h>
#include "BTS7960.h"

#define SDA_PIN 4
#define SCL_PIN 5

const int16_t I2C_MASTER = 0x42;
const int16_t I2C_SLAVE = 0x08;

#define BTS7960_DEVID   1
#define BTS7960_enabled false


BTS7960 dev_BTS7960;

//=======================================================================
//                               Setup
//=======================================================================
void setup() {
  
  Serial.begin(115200);           // start serial for output
  while (!Serial);
  
  Serial.println("\r\n8266 IOWidget Setup");
  Wire.begin(SDA_PIN, SCL_PIN, I2C_SLAVE); // new syntax: join i2c bus (address required for slave)
  Wire.onReceive(receiveEvent); // register event

  Serial.print(F("\nStarting TimerInterruptTest on ")); Serial.println(ARDUINO_BOARD);
  Serial.println(ESP8266_TIMER_INTERRUPT_VERSION);
  Serial.print(F("CPU Frequency = ")); Serial.print(F_CPU / 1000000); Serial.println(F(" MHz"));
}

void loop() {
}


//
// command format
// Device
// Cmd    Byte, Define command to execute. 
// Data   Byte, Data supporting the command
//
void receiveEvent(size_t howMany) 
{
  Serial.print("Receive Event: count ");
  Serial.println(howMany, DEC);

  int size = Wire.available();
  if (size < 3) return;
  
  uint8_t devid = Wire.read();
  uint8_t cmd = Wire.read();

  // Command contains data ?
  byte x = 0;
  if (size > 3) {
      byte data[Wire.available() -1];
      while (1 < Wire.available()) { // loop through all but the last
        data[x++] = Wire.read(); // receive byte as a character
    }
    execCommand(devid, cmd, data);
  }

  execCommand(devid, cmd, NULL);
}

void execCommand(uint8_t devid, uint8_t cmd, uint8_t data[])
{

#ifdef  BTS7960_enabled
  if (devid == BTS7960_DEVID) dev_BTS7960.executeCommand(cmd, data);
#endif

}
