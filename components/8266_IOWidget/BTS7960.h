 
#ifndef BTS7960_h
#define BTS7960_h

#define BTS7960_DEVID   1

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "DeviceCommands.h"

#define PWM_TIMING_INTERVAL_US 50
#define MAX_SPEED_SETTING 100

enum Direction {
  Forward = 1,
  Reverse = 2
};

enum PWM_State {
  PWM_STATE_LOW=1,
  PWM_STATE_HIGH=2,
  PWM_STATE_INIT=3
};

#define TICK_FREQ 80000000.0


class BTS7960
{
  public:
    BTS7960();

    void init(uint8_t EN_Pin_R, uint8_t EN_Pin_L, uint8_t PWM_Pin_R, uint8_t PWM_Pin_L);
    void init();
    bool startIntervalTimer(float interval);
    void stopIntervalTimer();


    void executeCommand(uint8_t cmd, uint8_t data[]);
    void runBackground();
    
    bool isInit() { return Is_Init_;} 
    bool isRunning() { return Is_Running_;}
    
	  void motor_setSpeed(uint8_t speed);
    void motor_initSpeedCurve();

	  void motor_run(Direction dir, uint16_t distance);
	  void motor_stop();
    void motor_brake();
    
    void run_PWM();

    void motor_setCurrentSpeed(uint8_t speed);
    
    void motor_enable();
    void motor_disable();

    void _init();

    uint8_t EN_Pin_L_;
    uint8_t EN_Pin_R_;
    uint8_t PWM_Pin_L_;
    uint8_t PWM_Pin_R_;
    
    float   PWM_Low_Interval_;
    float   PWM_High_Interval_;
    float   PWM_Freq_ =  15000.0;
    
    
    unsigned long lastSpeedCheck=0;
    
    bool    Is_Init_ = false;
    bool    Is_Running_ = false;

    uint8_t   Speed_=5;
    volatile PWM_State PWM_State_ = PWM_STATE_LOW;
    volatile uint8_t CurrentSpeed_;

    uint16_t  Distance_=0;
    Direction Dir_ = Forward;

};
#endif
