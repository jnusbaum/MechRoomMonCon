#ifndef DeviceAddresses_h
#define DeviceAddresses_h

#include <DallasTemperature.h>


// function to print a device address
void printAddress(DeviceAddress &deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

// function to print the temperature for a device
void printTemperature(const char *name, float tempF)
{
  Serial.printf("Temp for %s = %.2f\n", name, tempF);
  //Serial.printf("Temp C: %.2f", tempC);
  //Serial.printf("Temp F: %f\n", tempF);
}


DeviceAddress dev_one = { 0x28, 0x5D, 0x43, 0x45, 0x92, 0x13, 0x02, 0xDE }; // 1
DeviceAddress dev_two = { 0x28, 0x71, 0x3E, 0x45, 0x92, 0x0E, 0x02, 0xF1 }; // 2
DeviceAddress dev_three = { 0x28, 0xBE, 0x1A, 0x45, 0x92, 0x16, 0x02, 0x37 }; // 3
DeviceAddress dev_four = { 0x28, 0x96, 0x47, 0x45, 0x92, 0x13, 0x02, 0xA6 }; // 4
DeviceAddress dev_five = { 0x28, 0xD2, 0x45, 0x45, 0x92, 0x13, 0x02, 0x8C }; // 5
DeviceAddress dev_six = { 0x28, 0x4C, 0x13, 0x94, 0x97, 0x01, 0x03, 0xBF }; // 6
DeviceAddress dev_seven = { 0x28, 0xF4, 0x0E, 0x94, 0x97, 0x0E, 0x03, 0x91 }; // 7
DeviceAddress dev_eight = { 0x28, 0x4D, 0x05, 0x94, 0x97, 0x0E, 0x03, 0x70 }; // 8
DeviceAddress dev_nine = { 0x28, 0x73, 0x56, 0x94, 0x97, 0x07, 0x03, 0xE7 }; // 9
DeviceAddress dev_ten = { 0x28, 0xD6, 0x19, 0x94, 0x97, 0x01, 0x03, 0x7C }; // 10
DeviceAddress dev_eleven = { 0x28, 0x79, 0x62, 0x94, 0x97, 0x09, 0x03, 0x6F }; // 11
DeviceAddress dev_twelve = { 0x28, 0x42, 0x22, 0x94, 0x97, 0x07, 0x03, 0x4F }; // 12
DeviceAddress dev_thirteen { 0x28, 0x8D, 0x0A, 0x94, 0x97, 0x13, 0x03, 0xE5 }; // 13
DeviceAddress dev_fourteen = { 0x28, 0x51, 0x50, 0x94, 0x97, 0x14, 0x03, 0x1A }; // 14
DeviceAddress dev_fifteen = { 0x28, 0x89, 0x21, 0x94, 0x97, 0x14, 0x03, 0xDF }; // 15
DeviceAddress dev_sixteen = { 0x28, 0x54, 0x6C, 0x94, 0x97, 0x10, 0x03, 0x6F }; // 16
DeviceAddress dev_seventeen = { 0x28, 0x22, 0x01, 0x94, 0x97, 0x06, 0x03, 0xFE }; // 17
DeviceAddress dev_eighteen = { 0x28, 0xD7, 0x2B, 0x94, 0x97, 0x01, 0x03, 0x4C }; // 18
DeviceAddress dev_nineteen = { 0x28, 0x0B, 0x54, 0x94, 0x97, 0x01, 0x03, 0xF7 }; // 19
DeviceAddress dev_twenty = { 0x28, 0x8D, 0x23, 0x94, 0x97, 0x10, 0x03, 0xBB }; // 20
DeviceAddress dev_twentyone = { 0x28, 0x30, 0x50, 0x94, 0x97, 0x01, 0x03, 0xFD }; // 21
DeviceAddress dev_twentytwo = { 0x28, 0xB1, 0x20, 0x94, 0x97, 0x10, 0x03, 0x65 }; // 22
DeviceAddress dev_twentythree = { 0x28, 0x65, 0x5D, 0x94, 0x97, 0x09, 0x03, 0xA2 }; // 23
DeviceAddress dev_twentyfour = { 0x28, 0x00, 0x62, 0x94, 0x97, 0x10, 0x03, 0x3F }; // 24
DeviceAddress dev_twentyfive = { 0x28, 0x71, 0x63, 0x94, 0x97, 0x07, 0x03, 0xDF }; // 25
DeviceAddress dev_twentysix = { 0x28, 0xDA, 0xE3, 0xBA, 0x1B, 0x19, 0x01, 0x80 }; // 26
DeviceAddress dev_twentyseven = { 0x28, 0xAF, 0xEA, 0x12, 0x1C, 0x19, 0x01, 0xCF }; // 27
DeviceAddress dev_twentyeight = { 0x28, 0x06, 0x8B, 0xF7, 0x1B, 0x19, 0x01, 0x6B }; // 28
DeviceAddress dev_twentynine = { 0x28, 0x36, 0x73, 0x3A, 0x1B, 0x19, 0x01, 0xBA }; // 29
DeviceAddress dev_twentythirty = { 0x28, 0xB8, 0x02, 0xEA, 0x1B, 0x19, 0x01, 0xE2 }; // 30

#endif
