 
#ifndef BTS7960_h
#define BTS7960_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "TimerInterrupt.h"


class BTS7960
{
  public:
    BTS7960(uint8_t EN_A, uint8_t EN_B, uint8_t PWM_A, uint8_t PWM_B);

    BTS7960(uint8_t PWM_A, uint8_t PWM_B) { BTS7960( 0,0, PWM_A, PWM_B); }

	  void setSpeed(uint8_t speed);
	  void run(uint8_t dir);
	  void stop();
    void brake();

    
  private:
    void enable();
    void disable();
    void IRAM_ATTR TimerHandler();

    uint8_t _EN_PIN_A;
    uint8_t _EN_PIN_B;
    uint8_t _PWM_PIN_A;
    uint8_t _PWM_PIN_B;
    uint8_t _SPEED;

    // Init ESP8266 timer 1
    ESP8266Timer ITimer;


};
#endif
