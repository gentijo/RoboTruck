
#include "BTS7960.h"
#include "DeviceCommands.h"

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

BTS7960::BTS7960()
{
  PWM_PIN_L = 0;
  PWM_PIN_R = 0;
  EN_PIN_L = 0;
  EN_PIN_R = 0;
  SPEED = 0;
}

void BTS7960::init(uint8_t _EN_PIN_R, uint8_t _EN_PIN_L, uint8_t _PWM_PIN_R, uint8_t _PWM_PIN_L) 
{
  if ((PWM_PIN_R == 0) || (PWM_PIN_L == 0)) return;
  PWM_PIN_R = _PWM_PIN_R;
  PWM_PIN_L = _PWM_PIN_L;
  
  EN_PIN_R = _EN_PIN_R;
  EN_PIN_L = _EN_PIN_L;
  
  SPEED = 0;  
  
  init();
}

void BTS7960::init() 
{
  PWM_PIN_R = D7;
  PWM_PIN_L = D4;
  EN_PIN_L =  D8;
  EN_PIN_R  = D0;
  SPEED = 0;  
  init();
}

void BTS7960::_init()
{
  pinMode(PWM_PIN_L, OUTPUT);
  pinMode(PWM_PIN_R, OUTPUT);
  pinMode(EN_PIN_L, OUTPUT);
  pinMode(EN_PIN_R, OUTPUT);
 
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

void BTS7960::executeCommand(uint8_t cmd, uint8_t data[])
{
  switch(cmd)
  {
    case MOTOR_SET_SPEED:
      if (sizeof(data) > 0) motor_setSpeed(data[0]);
      break;
      
    case MOTOR_RUN:
      if (sizeof(data) > 0) motor_run(data[0]);
      break;
    
    case MOTOR_STOP:
      motor_stop();
      break;

    case MOTOR_BRAKE:
      motor_brake();
      break;
      
  }
}


void BTS7960::motor_setSpeed(uint8_t speed)
{
  SPEED = speed;
}


void BTS7960::motor_run(uint8_t dir)
{
  motor_disable();
  
  if (dir == 0)
  {
    analogWrite(PWM_PIN_L, LOW);
    analogWrite(PWM_PIN_R, SPEED);
  }
  else
  {
    analogWrite(PWM_PIN_L, SPEED);
    analogWrite(PWM_PIN_R, LOW);
  }
  
  delayMicroseconds(100);

  motor_enable();
}


void BTS7960::motor_stop()
{
  analogWrite(PWM_PIN_L, LOW);
  analogWrite(PWM_PIN_R, LOW);
  motor_disable();
}


void BTS7960::motor_brake()
{
  analogWrite(PWM_PIN_L, HIGH);
  analogWrite(PWM_PIN_R, HIGH);
  delayMicroseconds(1000);
  analogWrite(PWM_PIN_L, LOW);
  analogWrite(PWM_PIN_R, LOW);
  motor_disable();
}

void BTS7960::motor_enable(){
  digitalWrite(EN_PIN_L, HIGH);
  digitalWrite(EN_PIN_R, HIGH);  
}

void BTS7960::motor_disable()
{
  digitalWrite(EN_PIN_L, LOW);
  digitalWrite(EN_PIN_R, LOW);
}
