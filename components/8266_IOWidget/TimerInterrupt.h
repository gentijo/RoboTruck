#define TIMER_INTERVAL_MS       1000

// These define's must be placed at the beginning before 
// #include "ESP8266TimerInterrupt.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. 
// Only for special ISR debugging only. Can hang the system.
#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     0

// Select a Timer Clock
#define USING_TIM_DIV1                false           // for shortest and most accurate timer
#define USING_TIM_DIV16               true           // for medium time and medium accurate timer
#define USING_TIM_DIV256              false            // for longest timer but least accurate. Default

#if defined(ESP8266)
  #include "ESP8266TimerInterrupt.h"
#else
  #error No native timer interrupt code found for this board
  #error Please check your Tools->Board setting.
#endif
