/*
  Name:		HeatingTempMon.ino
  Created:	10/28/2019 2:46:05 PM
  Author:	nusbaum

  configurable parameters
  
  hot water system parameters
  - min run time for pump
  - min temp for hot water
  - max temp for hot water
  - min water temp for temp data cleaning
  - max water temp for temp data cleaning
  - max temp move for temp data cleaning

  temperature sampling
  - sampling interval

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <MQTT.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "Defines.h"
#include "Status.h"
#include "DeviceAddresses.h"
#include "TempSensor.h"
#include "Relay.h"

#define DEBUG

#define MAXBUSSES 4

WiFiClient net;
MQTTClient client(4096);

char mqtt_client_id[] = DEVICENAME;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "us.pool.ntp.org");

int numbusses = 3;
SensorBus busses[3];
int numrelays = 1;
Relay relays[1];

// previous temp value used for cleaning
float prevTempValue = 125;

void config() {
  DEBUG_PRINTF("client id: %s\n", mqtt_client_id);
  DEBUG_PRINTF("number of interfaces: %d\n", numbusses);

  int pin_number = -1;
  int num_sensors = -1;
  // bus 0
  num_sensors = 12;
  pin_number = 0;
  busses[0].initialize(pin_number, num_sensors);
  busses[0].initsensor(0, "KITCHEN-OUT", "0x28, 0x96, 0x47, 0x45, 0x92, 0x13, 0x02, 0xA6");
  busses[0].initsensor(1, "WHEAT1-OUT", "0x28, 0xAF, 0xEA, 0x12, 0x1C, 0x19, 0x01, 0xCF");
  busses[0].initsensor(2, "GARAGE-OUT", "0x28, 0xD2, 0x45, 0x45, 0x92, 0x13, 0x02, 0x8C");
  busses[0].initsensor(3, "WHEAT-IN", "0x28, 0xDA, 0xE3, 0xBA, 0x1B, 0x19, 0x01, 0x80");
  busses[0].initsensor(4, "WHEAT1-BURN", "0x28, 0x75, 0x61, 0x79, 0xA2, 0x00, 0x03, 0xD1");
  busses[0].initsensor(5, "WHEAT2-BURN", "0x28, 0x71, 0x63, 0x94, 0x97, 0x07, 0x03, 0xDF");
  busses[0].initsensor(6, "WHEAT2-OUT",  "0x28, 0xB8, 0x02, 0xEA, 0x1B, 0x19, 0x01, 0xE2");
  busses[0].initsensor(7, "GARAGE-IN", "0x28, 0xBE, 0x1A, 0x45, 0x92, 0x16, 0x02, 0x37");
  busses[0].initsensor(8, "LAUNDRY-OUT", "0x28, 0x4C, 0x13, 0x94, 0x97, 0x01, 0x03, 0xBF");
  busses[0].initsensor(9, "LAUNDRY-IN",  "0x28, 0x5D, 0x43, 0x45, 0x92, 0x13, 0x02, 0xDE");
  busses[0].initsensor(10, "KITCHEN-IN", "0x28, 0x71, 0x3E, 0x45, 0x92, 0x0E, 0x02, 0xF1");
  busses[0].initsensor(11, "WHEAT-RETURN", "0x28, 0x00, 0xBC, 0x79, 0xA2, 0x00, 0x03, 0x10");

  // bus 1
  num_sensors = 8;
  pin_number = 2;
  busses[1].initialize(pin_number, num_sensors);
  busses[1].initsensor(0, "FAMILY-IN",  "0x28, 0x89, 0x21, 0x94, 0x97, 0x14, 0x03, 0xDF");
  busses[1].initsensor(1, "FAMILY-OUT",  "0x28, 0x79, 0x62, 0x94, 0x97, 0x09, 0x03, 0x6F");
  busses[1].initsensor(2, "OFFICE-IN", "0x28, 0x54, 0x6C, 0x94, 0x97, 0x10, 0x03, 0x6F");
  busses[1].initsensor(3, "EXERCISE-IN", "0x28, 0x22, 0x01, 0x94, 0x97, 0x06, 0x03, 0xFE");
  busses[1].initsensor(4, "OFFICE-OUT",  "0x28, 0x42, 0x22, 0x94, 0x97, 0x07, 0x03, 0x4F");
  busses[1].initsensor(5, "EXERCISE-OUT",  "0x28, 0x8D, 0x0A, 0x94, 0x97, 0x13, 0x03, 0xE5");
  busses[1].initsensor(6, "GUEST-IN",  "0x28, 0xD7, 0x2B, 0x94, 0x97, 0x01, 0x03, 0x4C");
  busses[1].initsensor(7, "GUEST-OUT", "0x28, 0x51, 0x50, 0x94, 0x97, 0x14, 0x03, 0x1A");

  // bus 2
  num_sensors = 5;
  pin_number = 4;
  busses[2].initialize(pin_number, num_sensors);
  busses[2].initsensor(0, "BOILER-OUT",  "0x28, 0x73, 0x56, 0x94, 0x97, 0x07, 0x03, 0xE7");
  busses[2].initsensor(1, "VALVE-INSYS", "0x28, 0x4D, 0x05, 0x94, 0x97, 0x0E, 0x03, 0x70");
  busses[2].initsensor(2, "VALVE-OUT", "0x28, 0xF4, 0x0E, 0x94, 0x97, 0x0E, 0x03, 0x91");
  busses[2].initsensor(3, "BOILER-IN", "0x28, 0xD6, 0x19, 0x94, 0x97, 0x01, 0x03, 0x7C");
  busses[2].initsensor(4, "BOILER-BURN", "0x28, 0x36, 0x73, 0x3A, 0x1B, 0x19, 0x01, 0xBA");

  busses[0].begin();
  busses[1].begin();
  busses[2].begin();

  relays[0].initialize("HWCIRCPUMP", 13);
  relays[0].begin();
  
  publishStatus(client, timeClient, "CONFIGURED");
}


void connect() {
  DEBUG_PRINT("Wait for WiFi... ");
  while (WiFi.status() != WL_CONNECTED) {
    DEBUG_PRINT(".");
    delay(500);
  }
  
  DEBUG_PRINTLN("");
  DEBUG_PRINTLN("WiFi connected");
  DEBUG_PRINTLN("IP address: ");
  DEBUG_PRINTLN(WiFi.localIP());
  DEBUG_PRINTLN("MAC address: ");
  DEBUG_PRINTLN(WiFi.macAddress());

  DEBUG_PRINT("\nconnecting to MQTT...");
  while (!client.connect(mqtt_client_id)) {
    DEBUG_PRINT(".");
    delay(500);
  }
  DEBUG_PRINTLN("\nconnected!");
}


unsigned long pump_change = 0;

void turn_off_pump()
{
  DEBUG_PRINTLN("turning Pump off");
  relays[0].deEnergize();
  DEBUG_PRINTLN("Pump off");
}


void turn_on_pump()
{
  DEBUG_PRINTLN(String("Turning pump on - pin number: ") + relays[0].pin);                     
  relays[0].energize();
  DEBUG_PRINTLN("Pump on");
}


void setup() {
  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin("nusbaum-24g", "we live in Park City now");
  client.begin(MQTTHOST, net);

  connect();

  timeClient.begin();
  timeClient.forceUpdate();

  publishStatus(client, timeClient, "STARTING");

  config();
}


unsigned long period = PERIOD;
unsigned long previousMillis = 0;

void loop() 
{
  client.loop();
  delay(10);
  
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > period)
  {
    if (!client.connected()) 
    {
      connect();
      publishStatus(client, timeClient, "RECONNECTED");
    }

    timeClient.update();

    previousMillis = currentMillis;

    unsigned long etime = timeClient.getEpochTime();
    for (int x = 0; x < numbusses; ++x)
    {
      busses[x].requestTemps();
    }
    DEBUG_PRINTF("time = %lu\n", etime);
    delay(500);
    
    for (int x = 0; x < numbusses; ++x)
    {
      busses[x].processTemps(client, timeClient);
    }


    float wheat_ret_temp = busses[0].getTempF(11);
    DEBUG_PRINTF("sampled temp = %f\n", wheat_ret_temp);
    // clean data
    if (wheat_ret_temp < MIN_WATER_TEMP || wheat_ret_temp > MAX_WATER_TEMP || abs(wheat_ret_temp - prevTempValue) > MAX_TEMP_MOVE) {
      DEBUG_PRINTF("got bad value %f\n", wheat_ret_temp);
      wheat_ret_temp = prevTempValue;
      DEBUG_PRINTF("using value %f\n", wheat_ret_temp);
    }
    else {
      prevTempValue = wheat_ret_temp;
    }
    
    DEBUG_PRINTF("temp = %f\n", wheat_ret_temp);
    // if pump on
    if (relays[0].energized)
    {
      //   has it been on for more than 10 minutes?
      if ((currentMillis - pump_change) > MIN_RUN_TIME)
      {
        // is return temp > high point?
        if (wheat_ret_temp > HIGH_POINT)
        {
          // turn off pump, set pump status
          turn_off_pump();
          pump_change = currentMillis;
          publishStatus(client, timeClient, "PUMP-STOPPED");
        }
      }
      publishState(client, timeClient, relays[0].devname, true);
    }
    else
    {
      // is return temp < low point?
      if (wheat_ret_temp < LOW_POINT)
      {
        if ((currentMillis - pump_change) > MIN_STOP_TIME)
        {
          // turn pump on,
          turn_on_pump();
          // record time
          pump_change = currentMillis;
          publishStatus(client, timeClient, "PUMP-RUNNING");
        }
      }
      publishState(client, timeClient, relays[0].devname, false);
    }
        
    publishStatus(client, timeClient, "RUNNING");
  }
}
