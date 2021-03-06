#include <FastLED.h>

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    3
//#define CLK_PIN   4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    300
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120
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
uint8_t gHue = 0;
void setup() { 
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);               
  // initialize the digital pin as an output.
  //pinMode(red, OUTPUT);   
  //pinMode(blue, OUTPUT); 
  //Serial.begin(230400);      
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
    //Serial.println(-1);
    //analogWrite(red, 255); 
    //digitalWrite(blue, LOW);// turn the LED on (HIGH is the voltage level)          
    //delay(10);// wait for a second
  }
  else if(val >(thres)){
    juggle();
    //Serial.println(2);
    //analogWrite(red, 25);  
    //digitalWrite(blue, HIGH);// turn the LED off by making the voltage LOW    
   // delay(10);// wait for a second
  }
  else{
    //Serial.println(0);
      //analogWrite(red,0); 
      //analogWrite(blue, 0); 
   
  }

  for(int i = NUM_LEDS - 1; i >= updateLEDS; i--) {
    leds[i] = leds[i - updateLEDS];
  }
  

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  //FastLED.delay(1000/FRAMES_PER_SECOND); 
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  //for( int i = 0; i < 8; i++) {
    leds[beatsin16( 7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  //}
}

void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}
