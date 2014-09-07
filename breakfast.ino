/*
  Hello World.ino
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2013-9-18

  Grove - Serial LCD RGB Backlight demo.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <Wire.h>
#include "rgb_lcd.h"
#include <SoftwareSerial.h> //this is a must
#include <math.h>

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
int R, G, B;

// Button
const int buttonPin = A3;    // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status
int idx = 0;

// Sensors
const int tempPin = A0;  // Temp Sensor is attached to
const int touchPin = A2;
const int lightPin = A1;

void setup() 
{
    // initialize the pushbutton pin as an input:
    pinMode(buttonPin, INPUT);  
  
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.
    lcd.print("Breakfast?");

    delay(1000);
}

void loop() 
{
    // read the state of the pushbutton value:
    int buttonState = digitalRead(buttonPin);

    //idx = millis()/1000;
    if (readTouch() > 0 ) 
      idx ++;
    
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    
    //if (buttonState == HIGH) {    
    //if ( readLight() < 1 ) {       // Lights are off  
    if ( readLight() == 0 ) {       // Lights always on
      if (idx % 4 == 0 ) {
          R = 0;  
          G = 255;
          B = 0;
      } else if ( idx % 4 == 1  ){
          R = 0;  
          G = 0;
          B = 255;
      } else if ( idx % 4 == 2  ){
          R = 255;  
          G = 0;
          B = 0;
      } else if ( idx % 4 == 3  ){
          R = 0;  
          G = 0;
          B = 0;
      }
    } else {
          // ButtonState <> High
          R = 0;  
          G = 0;
          B = 0;
    }
    
    lcd.setRGB(R, G, B);
    
    // print the number of seconds since reset:
    //lcd.print(idx);
    
    //lcd.print(  readTemp() );
    
    delay(100);
}

float readTemp()
{
  const int B=3975; 
  double TEMP;
  int sensorValue = analogRead( tempPin );
  float Rsensor;
  Rsensor=(float)(1023-sensorValue)*10000/sensorValue;
  TEMP=1/(log(Rsensor/10000)/B+1/298.15)-273.15;
  return TEMP;
}

int readLight()
{
  const int B=300; 
  int sensorValue = analogRead( lightPin );
  if (sensorValue > B)
    return 1;
  else
    return 0;
}

int readTouch()
{
  const int B=1000; 
  int sensorValue = analogRead( touchPin );
  if (sensorValue > B)
    return 1;
  else
    return 0;
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
