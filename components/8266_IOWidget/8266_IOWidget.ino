// Wire Slave Receiver
// by devyte
// based on the example by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// This example code is in the public domain.


#include <Wire.h>

#define SDA_PIN 4
#define SCL_PIN 5

const int16_t I2C_MASTER = 0x42;
const int16_t I2C_SLAVE = 0x08;

void setup() {
  Serial.begin(115200);           // start serial for output
  Serial.println("\r\nHello world");
  
  Wire.begin(SDA_PIN, SCL_PIN, I2C_SLAVE); // new syntax: join i2c bus (address required for slave)
  Wire.onReceive(receiveEvent); // register event

 //=======================================================================
//                               Setup
//=======================================================================
void setup()
{
  Serial.begin(115200);
  while (!Serial);

  delay(300);

 
}

}

void loop() {
}

enum ERROR_CODE {
  INVALID_COMMAND = 0x0 
}

//
// command format
// Cmd    Byte, Define command to execute. 
// Data   Byte, Data supporting the command
//
void receiveEvent(size_t howMany) {

  byte cmd;
  Serial.print("Receive Event: count ");
  Serial.println(howMany, DEC);


  int size = Wire.available();
  if (size < 2) setError(ERROR_CODE.INVALID_COMMAND);
  cmd = Wire.read();

  // Command contains data ?
  byte x = 0;
  if (size > 2) {
      byte data[wire.available() -1];
      while (1 < Wire.available()) { // loop through all but the last
        data[x++] = Wire.read(); // receive byte as a character
    }
    execCommand(cmd, data);
  }

  execCommand(cmd, null);
}

void execCommand(byte cmd, byte data[])
{
  switch(cmd){
    case 
  }
  
}
