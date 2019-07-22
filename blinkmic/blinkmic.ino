#include <FastLED.h>

FASTLED_USING_NAMESPACE


#define DATA_PIN    3
//#define CLK_PIN   4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    7
CRGB leds[NUM_LEDS];
#define updateLEDS 1
#define BRIGHTNESS  255
/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int a0 = 4;     // potentiometer wiper (middle terminal) connected to analog pin 3
int a1 = 1;  
    uint8_t colorIndex =1;                   // outside leads to ground and +5V
int i;
double val = 0;           // variable to store the value read
int red=10;
int blue =11;
double low = 0;
double high = 0;
double thres = 1.01;
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

CRGBPalette16 currentPalette;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //pinMode(red, OUTPUT);   
  //pinMode(blue, OUTPUT); 
  Serial.begin(9600);      
}
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

// the loop routine runs over and over again forever:
void loop() {

  for(int i = NUM_LEDS - 1; i >= updateLEDS+(NUM_LEDS - 1)/2; i--) {
    leds[i] = leds[i - updateLEDS];
    leds[NUM_LEDS -2 - i] = leds[i + updateLEDS];
  }
    unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level

   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;

   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(a0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   val = (peakToPeak * 5.0) / 1024;  // convert to volts
  
  //val = analogRead(a0);    // read the input pin
  Serial.println(val);
  if(val < low){
    low = val;
  }
  else if(val > high){
    high = val;
  }
  i++;
  //high = high*.95;
  if(i >10000){
    low = 0;
    high = 0;
    i = 0;
  }
  //thres = (high+low)/2;
  if(val > low and val <=(thres)){
    
    for( int i = 0; i < updateLEDS; i++) {
        leds[i+(NUM_LEDS - 1)/2] = ColorFromPalette( RainbowStripeColors_p, colorIndex, BRIGHTNESS, LINEARBLEND);
        colorIndex += 3;
    }
  }
  else if(val >(thres)){
    
   SetupBlackAndWhiteStripedPalette();
   
   for( int i = 0; i < 20; i++) {
    leds[i] = CRGB::White;
    leds[NUM_LEDS -2 - i] = CRGB::White;
   }
   //fadeToBlackBy( leds, NUM_LEDS, 10);
  }
  else{
    //Serial.println(0);
      //analogWrite(red,0); 
      //analogWrite(blue, 0); 
   //fadeToBlackBy( leds, 20, 10);
   
  }
  //sinelon();
  FastLED.show(); 
  //FastLED.delay(1000/100); 
  delay(1);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
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
