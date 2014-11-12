/****************************************************************
 * File:    TMP36_001                                           *
 * Author:  Shawn Kelley                                        *
 * Date:    11-FEB-2013                                         *
 * Desc:    Connect TMP36 to arduino via breadboard circuit     *
 *          and write temperature in F / C to serial            *
 * Update:                                                      *
 *    11-FEB-2013                                               *
 *          - write csv formated txt to file on SD card         *
 *    12-FEB-2013                                               *
 *          - added record_temp function                        *
 *          - added 'timer' var for delay value                 *
 *          - added removal of existing temps.csv to function   *
 *    13-FEB-2013                                               *
 *          - added datastream to cosm                          *
 *    12-NOV-2014                                               *
 *          - removed networking and cosm                       *
 ****************************************************************/

/***** libs n stuff *****/
#include <SD.h>

/****** Globals *****/
File tFile; 
const int chipSelect = 4;
const int sensorPin = 0;
unsigned long timer = 60000;  //milliseconds

/***** setup stuff *****/
void setup()
{
  Serial.begin(9600);
  
  //SD card setup stuff
  Serial.println("Initializing SD card...");
  pinMode(10, OUTPUT);
  
  if (!SD.begin(4))
  {
    Serial.println("initialization failed!");
    Serial.println("did you remember to insert the SD card, dumbass???");
    return;
  }
  Serial.println("IT IS AAALIVE!!!");
  
  if (SD.exists("temps.csv")) {
    SD.remove("temps.csv");
  }
}

void loop() 
{
  int reading = analogRead(sensorPin);
  
  float voltage = (((float)reading / 1024) * 5.0);
  
  float temp_c = (voltage - 0.5) * 100 ;
  float temp_f = (temp_c * 9.0 / 5.0) + 32.0;

 //current temp
 Serial.print("Current TEMP is ");
 Serial.print(temp_c); Serial.print("C | ");
 Serial.print(temp_f); Serial.println("F ");
 
 record_temp(temp_c, temp_f);
 
 delay(timer);
 
}

/***** functions *****/
void record_temp(float tempc, float tempf)
{
  tFile = SD.open("temps.csv", FILE_WRITE);
  
  if (tFile) {
    tFile.print(tempc);
    tFile.print(",");
    tFile.println(tempf);
    tFile.close();
  } else {
    Serial.println("error opening file");
  }

}


