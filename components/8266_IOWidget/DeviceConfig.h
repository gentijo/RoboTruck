 
#ifndef DEVCONFIG_h
#define DEVCONFIG_h


#define I2C_MASTER_ADDR 0x42
#define I2C_SLAVE_ADDR  0x08


#define BTS7960_enabled true

  #define SDA_PIN 4
  #define SCL_PIN 5


#if  BTS7960_enabled == true
  #include "BTS7960.h"
  #define SDA_PIN 4
  #define SCL_PIN 5
#endif

#endif
