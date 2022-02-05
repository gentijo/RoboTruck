
 
#include "BTS7960.h"
#include "TimerInterrupt.h"


#define BUILTIN_LED     2       // Pin D4 mapped to pin GPIO2/TXD1 of ESP8266, NodeMCU and WeMoS, control on-board LED

volatile bool statusLed = false;
volatile uint32_t lastMillis = 0;


BTS7960::BTS7960(uint8_t EN_A, uint8_t EN_B, uint8_t PWM_A, uint8_t PWM_B) 
{
	_PWM_A = PWN_A;
	_PWM_B = PWM_B;
	_EN_A = _EN_A;
	_EN_B = _EN_B;
  _SPEED = 0;
  
	pinMode(_PWM_A, OUTPUT);
	pinMode(_PWM_B, OUTPUT);
	pinMode(_EN_A, OUTPUT);
	pinMode(_EN_B, OUTPUT);

 
  // Interval in microsecs
  if (ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, this.TimerHandler))
  {
    lastMillis = millis();
    Serial.print(F("Starting ITimer OK, millis() = ")); Serial.println(lastMillis);
  }
  else
  {
    Serial.println(F("Can't set ITimer correctly. Select another freq. or interval"));
  }

}

void BTS7960::setSpeed(uint8_t speed)
{
  _SPEED = speed;
}


void BTS7960::run(uint8_t dir)
{
  if (dir == 0)
  {
    analogWrite(_PWM_A, 0);
    delayMicroseconds(100);
    analogWrite(_PWM_B, _SPEED);
  }
  else
  {
    analogWrite(_PWM_A, _SPEED);
    analogWrite(_PWM_B, 0);
  }

  enable();
}


void BTS7960::stop()
{
  analogWrite(_PWM_A, LOW);
  analogWrite(_PWM_B, LOW);
  disable();
}


void BTS7960::brake()
{
  analogWrite(_PWM_A, LOW);
  analogWrite(_PWM_B, HIGH);
  delayMicroseconds(1000);
  disable();
}

void BTS7960::enable(){
  digitalWrite(_EN_A,1);
  digitalWrite(_EN_B,1);  
}

void BTS7960::disable()
{
  digitalWrite(_EN_A, 0);
  digitalWrite(_EN_B, 0);
}
