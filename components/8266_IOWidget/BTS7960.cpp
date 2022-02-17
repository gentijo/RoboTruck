#include "BTS7960.h"

BTS7960 *_bts7960 = NULL;

#define ICACHE_RAM_ATTR

/*
 * 
 */
ICACHE_RAM_ATTR void BTS7960_PWM_Handler()
{
  if (_bts7960 != NULL) _bts7960->run_PWM();
}

/*
 * 
 */
BTS7960::BTS7960()
{
  PWM_Pin_L_ = 0;
  PWM_Pin_R_ = 0;
  EN_Pin_L_ = 0;
  EN_Pin_R_ = 0;
  Speed_ = 0;
  
  PWM_Freq_=15000;
  
  Is_Init_ = false;
  Is_Running_ = false;
}

/*
 * 
 */
void BTS7960::init(uint8_t _EN_Pin_R, uint8_t _EN_Pin_L, uint8_t _PWM_Pin_R, uint8_t _PWM_Pin_L) 
{
  Serial.println("BTS7960 Init");
  
  if ((PWM_Pin_R_ == 0) || (PWM_Pin_L_ == 0)) return;
  PWM_Pin_R_ = _PWM_Pin_R;
  PWM_Pin_L_ = _PWM_Pin_L;
  
  EN_Pin_R_ = _EN_Pin_R;
  EN_Pin_L_ = _EN_Pin_L;
  
  Speed_ = 0;  
  
  _init();
}

/*
 * 
 */
void BTS7960::init() 
{
  Serial.println("BTS7960 Default Init");
  
  PWM_Pin_R_ = 13; //D7;
  PWM_Pin_L_ = 2;  //D4;
  EN_Pin_L_ =  15; //D8;
  EN_Pin_R_  = 16; //D0;
  Speed_ = 0;  
  
  _init();
}

/*
 * 
 */
void BTS7960::_init()
{
  Serial.println("BTS7960 _Init");
  _bts7960 = this;

  pinMode(PWM_Pin_L_, OUTPUT);
  pinMode(PWM_Pin_R_, OUTPUT);
  pinMode(EN_Pin_L_, OUTPUT);
  pinMode(EN_Pin_R_, OUTPUT);
  
  motor_stop();
  motor_disable();

  Is_Init_ = true;
}

void BTS7960::executeCommand(uint8_t cmd, uint8_t data[])
{
  switch(cmd)
  {
    case MOTOR_SET_SPEED:
      if (sizeof(data) > 0) motor_setSpeed(data[0]);
      break;
      
    case MOTOR_RUN:
      if (sizeof(data) == 1) motor_run((Direction)data[0], 0);
      if (sizeof(data) == 3) motor_run((Direction)data[0], data[1]*256+data[2]);
      break;
    
    case MOTOR_STOP:
      motor_stop();
      break;

    case MOTOR_BRAKE:
      motor_brake();
      break;
      
  }
}

void BTS7960::runBackground()
{
  unsigned long now= millis();
  
  if ((now - lastSpeedCheck) > 2000)
  {
    lastSpeedCheck = now;
    if (CurrentSpeed_ < Speed_)
    {
      
    }
  }
  
}

/*
 * SPEED determines the positive pulse of the PWM signal.
 * Values can be 0 - 100, where 0 = off and MAX_SPEED = full speed.
 */
//
ICACHE_RAM_ATTR void BTS7960::run_PWM()
{  
  if (!Is_Init_) return;
  if (!Is_Running_) return;
  
  if (PWM_State_ != PWM_STATE_HIGH)
  {
    PWM_State_ = PWM_STATE_HIGH;
    startIntervalTimer(PWM_High_Interval_);
    
   // motor_disable();
    if (Dir_ == Forward)
    {
      digitalWrite(PWM_Pin_L_, LOW);
      digitalWrite(PWM_Pin_R_, HIGH);
    }
    else
    {
      digitalWrite(PWM_Pin_L_, HIGH);
      digitalWrite(PWM_Pin_R_, LOW);
    }
   // motor_enable();
  }
  else if (PWM_State_ != PWM_STATE_LOW)
  {
    PWM_State_ = PWM_STATE_LOW;
  
    startIntervalTimer(PWM_Low_Interval_);

    digitalWrite(PWM_Pin_L_, LOW);
    digitalWrite(PWM_Pin_R_, LOW);
  }
}

/*
 * 
 */
void BTS7960::motor_setSpeed(uint8_t speed)
{
  if (Speed_ > MAX_SPEED_SETTING) Speed_ = MAX_SPEED_SETTING;
  Speed_ = speed;
  motor_initSpeedCurve();
}

/*
 * 
 */
void BTS7960::motor_initSpeedCurve()
{
  if (!Is_Running_) motor_setCurrentSpeed(Speed_);
}

/*
 * 
 */
void BTS7960::motor_setCurrentSpeed(uint8_t speed)
{
  if (speed > MAX_SPEED_SETTING) speed = MAX_SPEED_SETTING;
  CurrentSpeed_ = speed;
  
  Serial.print("Set Current Speed %: ");
  Serial.println(speed, DEC);

  float PWM_Interval_ = ((1.0/PWM_Freq_)/(1.0/TICK_FREQ));
  Serial.print("PWM Interval : ");
  Serial.println(PWM_Interval_, DEC);
  
  Serial.print("PWM Freq : ");
  Serial.println((float)PWM_Freq_);
  Serial.print("Tick Freq : ");
  Serial.println((float)TICK_FREQ);
    
  PWM_High_Interval_ = (PWM_Interval_ * ((float)speed/100.0));
  PWM_Low_Interval_ = PWM_Interval_ - PWM_High_Interval_;
  
  Serial.print("Current Speed Interval Low: ");
  Serial.print(PWM_Low_Interval_);
  Serial.print(" High: ");
  Serial.println(PWM_High_Interval_);
}

/*
 * 
 */
void BTS7960::motor_run(Direction _dir, uint16_t _distance)
{
  motor_disable();
  motor_stop();    
  motor_enable();
  
  Dir_ = _dir;
  Distance_ = _distance;
  Is_Running_ = true;
  run_PWM();
}

/*
 * 
 */
void BTS7960::motor_stop()
{
  Is_Running_ = false;
  digitalWrite(PWM_Pin_L_, LOW);
  digitalWrite(PWM_Pin_R_, LOW);
  motor_disable();
}

/*
 * 
 */
void BTS7960::motor_brake()
{
  Is_Running_ = false;
  
  digitalWrite(PWM_Pin_L_, HIGH);
  digitalWrite(PWM_Pin_R_, HIGH);
  delayMicroseconds(1000);
  digitalWrite(PWM_Pin_L_, LOW);
  digitalWrite(PWM_Pin_R_, LOW);
  motor_disable();
}

/*
 * 
 */
void BTS7960::motor_enable(){
  digitalWrite(EN_Pin_L_, HIGH);
  digitalWrite(EN_Pin_R_, HIGH);  
}

/*
 * 
 */
void BTS7960::motor_disable()
{
  Is_Running_ = false;
  digitalWrite(EN_Pin_L_, LOW);
  digitalWrite(EN_Pin_R_, LOW);
}

/*
 * 
 */
bool BTS7960::startIntervalTimer(float interval)
{
  // Clock to timer (prescaler) is always 80MHz, even F_CPU is 160 MHz
//  timer1_attachInterrupt(BTS7960_PWM_Handler);
//  timer1_write(interval);
//  timer1_enable(TIM_DIV1, TIM_EDGE, TIM_SINGLE);

  return true;
}

/*
 * 
 */
void BTS7960::stopIntervalTimer()
{
//  timer1_disable();
}
