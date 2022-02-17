#include <Wire.h>
#include "DeviceConfig.h"

#if  BTS7960_enabled == true
BTS7960 dev_BTS7960;
#endif

const int16_t g_I2C_MASTER = I2C_MASTER_ADDR;
const int16_t g_I2C_SLAVE = I2C_SLAVE_ADDR;


//=======================================================================
//                               Setup
//=======================================================================
void setup() {
  
  Serial.begin(115200);  
  
  Serial.println("\r\nMotor Widget Setup");
  Serial.print(F("CPU Frequency = ")); Serial.print(F_CPU / 1000000); Serial.println(F(" MHz"));

#if  BTS7960_enabled == true
  dev_BTS7960.init();
#endif
  
  Wire.begin(SDA_PIN, SCL_PIN, I2C_SLAVE_ADDR); 
  Wire.onReceive(receiveEvent);
}

void loop() {
  
  delay(1000);
    
#if  BTS7960_enabled == true
      dev_BTS7960.runBackground();
#endif

}


//
// command format
// Devid  Byte, Id of the Device you are addressing which is a sub address of the I2C addr
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

#if  BTS7960_enabled == true
  if (devid == BTS7960_DEVID) dev_BTS7960.executeCommand(cmd, data);
#endif

}
