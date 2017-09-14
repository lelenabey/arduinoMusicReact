#include <LedCube.h>

#define SIZE 3
#define COLS (SIZE*SIZE)

byte levelPins[SIZE] = {11,12,13};
byte colPins[COLS] = {2,3,4,5,6,7,8,9,10};

LedCube cube(3, levelPins, colPins);

void setup ()
{
//    Serial.begin(9600);
}

void loop ()
{
    delay(100);
    cube.enableBuffer(false);
        
    // random column drop
    for(byte x=0; x<=15; x++) {
        cube.lightDrop(random(0,cube.getCols()), random(50,150));
    }
    
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
    
    // cols in and out
    for(byte c=1, d=0; c<=36; c++)
    {
        if(c%2 == 0){
            for(d=0; d<20; d++) {
                cube.lightColumn(2,1);
                cube.lightColumn(4,1);
                cube.lightColumn(6,1);
                cube.lightColumn(8,1);
            }
        } else if(c%4 == 1) {
            for(d=0; d<30; d++) {
                cube.lightColumn(1,1);
                cube.lightColumn(3,1);
                cube.lightColumn(7,1);
                cube.lightColumn(9,1);
            }
        } else {
            for(d=0; d<70; d++) {
                cube.lightColumn(5,1);
            }
        }
    }
    
}

