#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 300
#define UPDATES_PER_SECOND 100
// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
//#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

// Arduino Frequency to Voltage converter without the aid of ICs - 2012

int DigitalIn13 = 13; //Input of pulses
int Voltage = 9; //Voltage from frequency conversion (output pin supporting PWM)
float Frequency = 0; //Frequency of the pulses
unsigned long HighTime; //the HIGH time of pulses
unsigned long LowTime; //the LOW time of pulses
unsigned long Period; //period = HighTime + LowTime
unsigned int volt = 0; // Variable to hold the voltage read
uint8_t brightness = 255;

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

void setup() {
   Serial.begin(9600);
   pinMode(DigitalIn13, INPUT); //sets pulses pin as input
   //pinMode(Voltage, OUTPUT); // sets voltage pin as output
   FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

   currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
}

void loop() {
  FillLEDsFromPaletteColors( brightness);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    
 HighTime = pulseIn(DigitalIn13, HIGH); //the HIGH time of pulses in ms
 LowTime = pulseIn(DigitalIn13, LOW); //the LOW time of pulses
 Period = HighTime + LowTime; //period
 Frequency = 1/(Period * 0.000001); //Frequency
 
 brightness = map(Frequency, 0, 242, 0, 255); //maps the frequency into voltage
 Serial.write(brightness);
 Serial.write(DigitalIn13);
 //analogWrite(Voltage,volt); //writes voltage from frequency
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
