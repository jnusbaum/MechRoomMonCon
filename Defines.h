#ifndef Defines_h
#define Defines_h

#define DEVICENAME "MECHROOM"
#define MQTTHOST "192.168.0.134"

// 10 minutes                                                                   
#define MIN_RUN_TIME 600000
// 10 sec
#define MIN_STOP_TIME 10000

// temp check interval                                                          
#define PERIOD 10000

#define HIGH_POINT 120
#define LOW_POINT 110

#define BASETOPIC "sorrelhills"
#define TEMPTOPIC BASETOPIC "/temperature/"
#define RELAYTOPIC BASETOPIC "/relay/"
#define STATUSTOPIC BASETOPIC "/device/status/" DEVICENAME
#define CONFIGRECEIVETOPIC BASETOPIC "/device/config/" DEVICENAME

#define MIN_WATER_TEMP 35
#define MAX_WATER_TEMP 150
#define MAX_TEMP_MOVE 45

#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(x)     Serial.print (x)
#define DEBUG_PRINTF(x, y)     Serial.printf (x, y)
#define DEBUG_PRINTLN(x)  Serial.println (x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTF(x, y)
#define DEBUG_PRINTLN(x)
#endif

#endif
