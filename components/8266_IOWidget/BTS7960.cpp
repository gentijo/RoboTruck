
#include "BTS7960.h"


#define BUILTIN_LED     2       // Pin D4 mapped to pin GPIO2/TXD1 of ESP8266, NodeMCU and WeMoS, control on-board LED
volatile bool     statusLed = false;
volatile uint32_t lastMillis = 0;



//=======================================================================
void IRAM_ATTR BTS7960_TimerHandler()
{
  static bool started = false;

  if (!started)
  {
    started = true;
    pinMode(BUILTIN_LED, OUTPUT);
  }

  digitalWrite(BUILTIN_LED, statusLed);  //Toggle LED Pin
  statusLed = !statusLed;

#if (TIMER_INTERRUPT_DEBUG > 0)
  Serial.println("Delta ms = " + String(millis() - lastMillis));
  lastMillis = millis();
#endif
}



BTS7960::BTS7960(uint8_t EN_PIN_A, uint8_t EN_PIN_B, uint8_t PWM_PIN_A, uint8_t PWM_PIN_B) 
{
	_PWM_PIN_A = PWM_PIN_A;
	_PWM_PIN_B = PWM_PIN_B;
	_EN_PIN_A = _EN_PIN_A;
	_EN_PIN_B = _EN_PIN_B;
  _SPEED = 0;
  
	pinMode(_PWM_PIN_A, OUTPUT);
	pinMode(_PWM_PIN_B, OUTPUT);
	pinMode(_EN_PIN_A, OUTPUT);
	pinMode(_EN_PIN_B, OUTPUT);

 
  // Interval in microsecs
  if (ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, BTS7960_TimerHandler))
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
    analogWrite(_PWM_PIN_A, LOW);
    delayMicroseconds(100);
    analogWrite(_PWM_PIN_B, _SPEED);
  }
  else
  {
    analogWrite(_PWM_PIN_A, _SPEED);
    analogWrite(_PWM_PIN_B, LOW);
  }

  enable();
}


void BTS7960::stop()
{
  analogWrite(_PWM_PIN_A, LOW);
  analogWrite(_PWM_PIN_B, LOW);
  disable();
}


void BTS7960::brake()
{
  analogWrite(_PWM_PIN_A, LOW);
  analogWrite(_PWM_PIN_B, HIGH);
  delayMicroseconds(1000);
  disable();
}

void BTS7960::enable(){
  digitalWrite(_EN_PIN_A, HIGH);
  digitalWrite(_EN_PIN_B, HIGH);  
}

void BTS7960::disable()
{
  digitalWrite(_EN_PIN_A, LOW);
  digitalWrite(_EN_PIN_B, LOW);
}
