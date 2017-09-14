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
left = left/10;    // adjusts the sensitivity  
//left = constrain(left,0,12);
 // Serial.println(left);  // uncomment to check the modified input.
// left = 1500;  // uncomment to test all leds light.
// left = 0;    // uncomment to check the leds are not lit when the input is 0.

if (left<25 ) {
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
    
    // single random light at a time
    cube.randomLight(random(25,100),100);
    
    // random column drop
    for(byte x=0; x<=15; x++) {
        cube.lightDrop(random(0,cube.getCols()), random(50,150));
    }
    
    // circle around cube at a random level
    for(byte x=0; x<=5; x++) {
        cube.lightPerimeter(random(0,cube.getLevels()), random(1,5), random(25,100));
    }
    
    // random columns
    cube.randomColumn(25);
    
    // turn off a single column randomly
    cube.enableBuffer();
    for(byte c=0; c<25; c++)
    {
        cube.fillBuffer();
        cube.invertBuffer();
        cube.randomColumn();
        cube.drawBuffer(10);
    }
    cube.enableBuffer(false);
    
   
    
    // diamond and box
    byte diamond[] = {0,4, 1,1, 1,3, 1,4, 1,5, 1,7, 2,4};
    byte box[] = {0,0, 0,1, 0,2, 0,3, 0,5, 0,6, 0,7, 0,8, 1,1,  1,0, 1,2, 1,6, 1,8,  2,0, 2,1, 2,2, 2,3, 2,5, 2,6, 2,7, 2,8};
    cube.lightSequence(box, sizeof(box), 200);
    cube.lightSequence(diamond, sizeof(diamond), 400);
    
    // helicopter effect
    cube.enableBuffer();
    byte topSeq[8] = {0,3,6,7,8,5,2,1};
    byte botSeq[8] = {8,5,2,1,0,3,6,7};
    for(byte r = 0; r<7; r++){
        for(byte s= 0; s<8; s++){
            cube.clearBuffer();
            cube.lightOn(0,botSeq[s]);
            cube.lightOn(1,4);
            cube.lightOn(2,topSeq[s]);
            cube.drawBuffer(20); 
        }
    }
    
    // turn off one light at a time
    cube.fillBuffer();
    cube.drawBuffer(25);
    for(byte w=0, l, c; w<27; ){
        l = random(0,cube.getLevels());
        c = random(0,cube.getCols());
        if(cube.getBufferAt(l,c)){
            cube.lightOff(l,c);
            cube.drawBuffer(15+w*2);
            w++;
        }
    }
}
}
