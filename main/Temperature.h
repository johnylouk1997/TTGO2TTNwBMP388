#include "DFRobot_BMP388_I2C.h"
 
DFRobot_BMP388_I2C bmp388;

float temperature = -51;// bmp388 outputs values above 50 Celsius

void Temperature_Init(){
 while(bmp388.begin() != 0){
    Serial.println("Initialization error! Check Wiring");
    delay(1000);
  }
}

float Temperature_Print(){
  while (millis() < 2000); // wait for 2s
  
  do temperature = bmp388.readTemperature()
  while (temperature == (-51));
  
  return temperature;
}
