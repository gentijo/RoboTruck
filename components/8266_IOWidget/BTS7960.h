 
#ifndef BTS7960_h
#define BTS7960_h


#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "TimerInterrupt.h"
#include "DeviceCommands.h"

#define PWM_TIMING_INTERVAL_US 50

class BTS7960
{
  public:
    BTS7960();

    void init(uint8_t EN_PIN_R, uint8_t EN_PIN_L, uint8_t PWM_PIN_R, uint8_t PWM_PIN_L);
    void init();

    void executeCommand(uint8_t cmd, uint8_t data[]);
    bool isInit() { return IS_INIT;} 
    
	  void motor_setSpeed(uint8_t speed);
	  void motor_run(uint8_t dir);
	  void motor_stop();
    void motor_brake();
    void run_PWM();

    
  private:
    void motor_enable();
    void motor_disable();

    void _init();


    uint8_t EN_PIN_L;
    uint8_t EN_PIN_R;
    uint8_t PWM_PIN_L;
    uint8_t PWM_PIN_R;
    uint8_t SPEED;
    uint8_t DIR = Forward;
    bool    IS_INIT = false;
    
    uint8_t CURR_SPEED = 0;
    uint8_t PWM_COUNTER = 0;

    // Init ESP8266 timer 1
    ESP8266Timer ITimer;


    enum {
      Forward = 1,
      Reverse
    } Direction;

};
#endif
