#include "DFRobot_BMP388_I2C.h"
 
DFRobot_BMP388_I2C bmp388;

float temperature = -51;

void Temperature_Init(){
 while(bmp388.begin() != 0){
    Serial.println("Initialization error! Check Wiring");
    delay(1000);
  }
}

float Temperature_Print(){
  delay(2000);
  temperature = bmp388.readTemperature();

  if(temperature > (-51))
  {
    return temperature;
  }
  else Serial.println("No value of Temperature");
}
