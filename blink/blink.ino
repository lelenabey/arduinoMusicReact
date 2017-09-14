/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int a0 = 0;     // potentiometer wiper (middle terminal) connected to analog pin 3
int a1 = 1;  
                       // outside leads to ground and +5V
int i;
float val = 0;           // variable to store the value read
int red=10;
int blue =11;
float low = 0;
float high = 0;
float thres = 1.01;
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(red, OUTPUT);   
  pinMode(blue, OUTPUT); 
  Serial.begin(256000);      
}

// the loop routine runs over and over again forever:
void loop() {
  val = analogRead(a0);    // read the input pin
  //Serial.println(val);
  if(val < low){
    low = val;
  }
  else if(val > high){
    high = val*.75;
  }
  i++;
  //high = high*.95;
  if(i >10000){
    low = 0;
    high = 0;
    i = 0;
  }
  thres = (high+low)/2;
  if(val > low and val <=(thres)){
    Serial.println(-1);
    analogWrite(red, 255); 
    digitalWrite(blue, LOW);// turn the LED on (HIGH is the voltage level)          
    //delay(10);// wait for a second
  }
  else if(val >(thres)){
    Serial.println(2);
    analogWrite(red, 25);  
    digitalWrite(blue, HIGH);// turn the LED off by making the voltage LOW    
   // delay(10);// wait for a second
  }
  else{
    //Serial.println(0);
      analogWrite(red,0); 
      analogWrite(blue, 0); 
   
  }
}
