// Led VU Meter Example
// Version 1.0
// Written by James Newbould


int led[3][3][3] = {{ 2, 3, 4},{ 5, 6, 7},{8, 9, 10}} ; // Assign the pins for the leds
int ground[3] ={11, 12 ,13};
int leftChannel = 0;  // left channel input
int left, i, left1;

void setup()
{
for (i = 0; i < 3; i++)  // Tell the arduino that the leds are digital outputs
  pinMode(led[i][i][i], OUTPUT);
//  Serial.begin(9600); // Uncomment to enable troubleshooting over serial.
}

void loop()
{
left = analogRead(leftChannel);  // read the left channel
// Serial.println(left);  // uncomment to check the raw input.
   
left1=map(left, left/50, left, 1, 3);// adjusts the sensitivity  
 // Serial.println(left);  // uncomment to check the modified input.
// left = 1500;  // uncomment to test all leds light.
// left = 0;    // uncomment to check the leds are not lit when the input is 0.

  
   for(i = 0; i < 3; i++)
     {
     digitalWrite(led[i][i][i], LOW);
     digitalWrite(ground[i], HIGH);
     }
  
  
  if (left >0)
  {
   for (i = 0; i < left1; i++) // turn on the leds up to the volume level
    {
     digitalWrite(led[i][i][i], HIGH);
    }
    
    for(i = i; i < 3; i++)  // turn off the leds above the voltage level
     {
      digitalWrite(led[i][i][i], LOW);
     }
  }
}
