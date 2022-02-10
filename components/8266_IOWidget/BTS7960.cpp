#include "BTS7960.h"
#include "DeviceCommands.h"

BTS7960 *_bts7960 = NULL;

//=======================================================================
void IRAM_ATTR BTS7960_PWM_Handler()
{
  if ((_bts7960 == NULL) ||
      (_bts7960->isInit() == false)) return;
      
  _bts7960->run_PWM();
}

BTS7960::BTS7960()
{
  PWM_PIN_L = 0;
  PWM_PIN_R = 0;
  EN_PIN_L = 0;
  EN_PIN_R = 0;
  SPEED = 0;
  IS_INIT = false;
}

void BTS7960::init(uint8_t _EN_PIN_R, uint8_t _EN_PIN_L, uint8_t _PWM_PIN_R, uint8_t _PWM_PIN_L) 
{
  Serial.println("BTS7960 Init");
  
  if ((PWM_PIN_R == 0) || (PWM_PIN_L == 0)) return;
  PWM_PIN_R = _PWM_PIN_R;
  PWM_PIN_L = _PWM_PIN_L;
  
  EN_PIN_R = _EN_PIN_R;
  EN_PIN_L = _EN_PIN_L;
  
  SPEED = 0;  
  
  _init();
}

void BTS7960::init() 
{
  Serial.println("BTS7960 Default Init");
  
  PWM_PIN_R = 13; //D7;
  PWM_PIN_L = 2;  //D4;
  EN_PIN_L =  15; //D8;
  EN_PIN_R  = 16; //D0;
  SPEED = 0;  
  _init();
}

void BTS7960::_init()
{
  Serial.println("BTS7960 _Init");

  pinMode(PWM_PIN_L, OUTPUT);
  pinMode(PWM_PIN_R, OUTPUT);
  pinMode(EN_PIN_L, OUTPUT);
  pinMode(EN_PIN_R, OUTPUT);
  motor_stop();
  motor_disable();
  
  Serial.println("BTS7960 Start iTimer");

  if (ITimer.attachInterruptInterval(PWM_TIMING_INTERVAL_US, BTS7960_PWM_Handler))
  {
    Serial.print(F("Starting BTS7960 ITimer OK"));
  }
  else
  {
    Serial.println(F("Can't set BTS7960 ITimer correctly"));
  }

  _bts7960 = this;
  IS_INIT = true;

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

// SPEED determines the positive pulse of the PWM signal.
// Values can be 0 - 100, where 0 = off and 100 = full speed.
//
void BTS7960::run_PWM()
{
  if (++PWM_COUNTER > 100) PWM_COUNTER=0;
  
  if (PWM_COUNTER >= CURR_SPEED) 
  {
    if (PWM_STATE != 1)
    {
      PWM_STATE=1;
      digitalWrite(PWM_PIN_L, LOW);
      digitalWrite(PWM_PIN_R, LOW);
    }
  }
  else if (PWM_STATE != 2)
  {
    PWM_STATE=2;
    motor_disable();
    if (dir == Forward)
    {
      digitalWrite(PWM_PIN_L, LOW);
      digitalWrite(PWM_PIN_R, HIGH);
    }
    else
    {
      digitalWrite(PWM_PIN_L, HIGH);
      digitalWrite(PWM_PIN_R, LOW);
    }
    motor_enable();
  }
}


void BTS7960::motor_setSpeed(uint8_t speed)
{
  if (SPEED > 100) speed = 100;
  SPEED = speed;
}


void BTS7960::motor_run(uint8_t dir, uint8_t distance)
{
  motor_disable();
  
  if (dir == 0)
  {
    digitalWrite(PWM_PIN_L, LOW);
    digitalWrite(PWM_PIN_R, SPEED);
  }
  else
  {
    digitalWrite(PWM_PIN_L, SPEED);
    digitalWrite(PWM_PIN_R, LOW);
  }
  
  delayMicroseconds(100);

  motor_enable();
}


void BTS7960::motor_stop()
{
  digitalWrite(PWM_PIN_L, LOW);
  digitalWrite(PWM_PIN_R, LOW);
  motor_disable();
}


void BTS7960::motor_brake()
{
  digitalWrite(PWM_PIN_L, HIGH);
  digitalWrite(PWM_PIN_R, HIGH);
  delayMicroseconds(1000);
  digitalWrite(PWM_PIN_L, LOW);
  digitalWrite(PWM_PIN_R, LOW);
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
