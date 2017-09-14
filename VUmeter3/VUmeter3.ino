// Led VU Meter Example
// Version 1.0
// Written by James Newbould

#include <LedCube.h>

#define SIZE 3
#define COLS (SIZE*SIZE)

byte levelPins[SIZE] = {11,12,13};
byte colPins[COLS] = {2,3,4,5,6,7,8,9,10};

LedCube cube(3, levelPins, colPins);
int led[12] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 ,13}; // Assign the pins for the leds
int leftChannel = 0;  // left channel input
int left, i;

void setup()
{
for (i = 0; i < 12; i++)  // Tell the arduino that the leds are digital outputs
  pinMode(led[i], OUTPUT);
//  Serial.begin(9600); // Uncomment to enable troubleshooting over serial.
}

void loop()
{
left = analogRead(leftChannel);  // read the left channel
// Serial.println(left);  // uncomment to check the raw input.
left = left/20;    // adjusts the sensitivity  
left = constrain(left,0,12);
 // Serial.println(left);  // uncomment to check the modified input.
// left = 1500;  // uncomment to test all leds light.
// left = 0;    // uncomment to check the leds are not lit when the input is 0.

if (left>0) {
   for(i = 0; i < 9; i++)
     {
     digitalWrite(led[i], HIGH);
     
     }
  
  

   for (i = 9; i < left; i++) // turn on the leds up to the volume level
    {
     digitalWrite(led[i], HIGH);
    }
    
    for(i = i; i < 12; i++)  // turn off the leds above the voltage level
     {
      digitalWrite(led[i], LOW);
     }
  left=0;
}
else
{
  delay(100);
    cube.enableBuffer(false);
    
    // light one level at a time, increasing speed each time
    for(byte d=25; d>2; d-=2) {
        for(byte r=0; r<cube.getLevels(); r++) {
            cube.lightLevel(r,d);
        }
    }
    
    
    
    // circle around cube at a random level
    for(byte x=0; x<=5; x++) {
        cube.lightPerimeter(random(0,cube.getLevels()), random(1,5), random(25,100));
    }
    
    
}
}
