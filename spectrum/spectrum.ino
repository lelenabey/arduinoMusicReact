/*
 * Arduino Spectrum Analizer
 * 
 * learnelectronics
 * 27 April 2017
 * black magic stolen from CBM80Amiga
 * 
 * www.youtube.com/c/learnelectronics
 * arduino1069@gmail.com
 * 
 * Fix_FFT library available @ https://github.com/kosme/arduinoFFT
 */

#include <FastLED.h>
#include "fix_fft.h"                                  //library to perfom the Fast Fourier Transform

//FASTLED_USING_NAMESPACE

CRGB leds[443];
int updateLEDS=1;
uint8_t colorIndex =1;
char im[128], data[128];                              //variables for the FFT
char x = 0, ylim = 60;                                //variables for drawing the graphics
int i = 0, val;                                       //counters
int brightness=255;
void setup()
{
  FastLED.addLeds<WS2812B,3,GRB>(leds, 443).setCorrection(TypicalLEDStrip);
  //Serial.begin(9600);
  //analogReference(DEFAULT);                           // Use default (5v) aref voltage.
};
void updateStrip(){
       for(i = 52; i < 104; i++){
      leds[i] = leds[i +updateLEDS];
    }
        for(i = 156; i > 104; i--){
      leds[i] = leds[i- updateLEDS];
    }
    for(i = 156; i < 222; i++){
      leds[i] = leds[i +updateLEDS];
    }
        for(i = 278; i > 222 ; i--){
      leds[i] = leds[i- updateLEDS];
    }
    for(i = 278; i < 327; i++){
      leds[i] = leds[i +updateLEDS];
    }
        for(i = 379; i > 327 ; i--){
      leds[i] = leds[i- updateLEDS];
    }
    for(i = 379; i < 442; i++){
      leds[i] = leds[i +updateLEDS];
    }
        for(i = 52; i > 0 ; i--){
      leds[i] = leds[i- updateLEDS];
    }
   
};

void loop()
{
  for(i = 52; i < 104; i++){
      leds[i] = leds[i +updateLEDS];
    }
        for(i = 156; i > 104; i--){
      leds[i] = leds[i- updateLEDS];
    }
    for(i = 156; i < 222; i++){
      leds[i] = leds[i +updateLEDS];
    }
        for(i = 278; i > 222 ; i--){
      leds[i] = leds[i- updateLEDS];
    }
    for(i = 278; i < 327; i++){
      leds[i] = leds[i +updateLEDS];
    }
        for(i = 379; i > 327 ; i--){
      leds[i] = leds[i- updateLEDS];
    }
    for(i = 379; i < 442; i++){
      leds[i] = leds[i +updateLEDS];
    }
        for(i = 52; i > 0 ; i--){
      leds[i] = leds[i- updateLEDS];
    }
  
  int min=1024, max=0;                                //set minumum & maximum ADC values
  for (i = 0; i < 128; i++) {                         //take 128 samples
    val = analogRead(A1);                             //get audio from Analog 0
    data[i] = val /* 4 - 128*/;                          //each element of array is val/4-128
    im[i] = 0;                                        //
    if(val>max) max=val;                              //capture maximum level
    if(val<min) min=val;                              //capture minimum level
  };
    
  fix_fft(data, im, 7, 0);                            //perform the FFT on data
  int value=0;
                             //clear display
  for (i = 1; i < 64; i++) {   // In the current design, 60Hz and noise
    int dat = sqrt(data[i] * data[i] + im[i] * im[i]);//filter out noise and hum
    value = max(0, dat-3);
      if (i<=4){
        colorIndex = max(value, colorIndex);
        leds[104] = CHSV( 213+colorIndex, 255-colorIndex*2, colorIndex*5);
        leds[222] = CHSV( 213+colorIndex, 255-colorIndex*2, colorIndex*5);
        leds[327] = CHSV( 213+colorIndex, 255-colorIndex*2, colorIndex*5);
        leds[0] = CHSV( 213+colorIndex, 255-colorIndex*2, colorIndex*5);
        leds[442] = CHSV( 213+colorIndex, 255-colorIndex*2, colorIndex*5);
        
//        leds[135] = ColorFromPalette( RainbowStripeColors_p, 3, colorIndex*5, LINEARBLEND); // 125Hz
//        leds[73] = ColorFromPalette( RainbowStripeColors_p, 3, colorIndex*5, LINEARBLEND); // 125Hz
//        leds[189] = ColorFromPalette( RainbowStripeColors_p, 3, colorIndex*5, LINEARBLEND); // 125Hz
//        leds[255] = ColorFromPalette( RainbowStripeColors_p, 3, colorIndex*5, LINEARBLEND); // 125Hz
//        leds[298] = ColorFromPalette( RainbowStripeColors_p, 3, colorIndex*5, LINEARBLEND); // 125Hz
//        leds[357] = ColorFromPalette( RainbowStripeColors_p, 3, colorIndex*5, LINEARBLEND); // 125Hz
//        leds[31] = ColorFromPalette( RainbowStripeColors_p, 3, colorIndex*5, LINEARBLEND); // 125Hz
//        leds[411] = ColorFromPalette( RainbowStripeColors_p, 3, colorIndex*5, LINEARBLEND); // 125Hz
      }
      if (i==4) colorIndex=0;
      if (i >4   && i<=11 ) {
        colorIndex = max(value, colorIndex);
        leds[73] = CHSV( 171+colorIndex, 255-colorIndex*2, colorIndex*10); // 125Hz
        leds[31] = CHSV( 171+colorIndex, 255-colorIndex*2, colorIndex*10); // 125Hz
        leds[255] = CHSV( 171+colorIndex, 255-colorIndex*2, colorIndex*10); // 125Hz
        leds[298] = CHSV( 171+colorIndex, 255-colorIndex*2, colorIndex*10); // 125Hz
        
//        leds[328] = ColorFromPalette( RainbowStripeColors_p, 60, colorIndex*10, LINEARBLEND); // 500Hz
//        leds[221] = ColorFromPalette( RainbowStripeColors_p, 60, colorIndex*10, LINEARBLEND); // 500Hz
//        leds[442] = ColorFromPalette( RainbowStripeColors_p, 60, colorIndex*10, LINEARBLEND); // 500Hz
//        leds[105] = ColorFromPalette( RainbowStripeColors_p, 60, colorIndex*10, LINEARBLEND); // 500Hz
      }
      if (i==11) colorIndex=0;
      //if (i >7   && i<=11 )  leds[327] = ColorFromPalette( RainbowStripeColors_p, 90, colorIndex*10, LINEARBLEND); // 1000Hz
      if (i >11  && i<=15 ) {
        colorIndex = max(value, colorIndex);
        leds[135] = CHSV( 128+colorIndex*5, 255-colorIndex*2, colorIndex*10); // 125Hz
        leds[189] = CHSV( 128+colorIndex*5, 255-colorIndex*2, colorIndex*10); // 125Hz
        
//        leds[0] = ColorFromPalette( RainbowStripeColors_p, 120, colorIndex*10, LINEARBLEND); // 2000Hz
//        leds[326] = ColorFromPalette( RainbowStripeColors_p, 120, colorIndex*10, LINEARBLEND); // 2000Hz
      }
      if (i==15) colorIndex=0;
      if (i >15  && i<=20 ){
        colorIndex = max(value, colorIndex);
        leds[357] = CHSV( 50-colorIndex, 255-colorIndex*2, colorIndex*20); // 125Hz
        leds[411] = CHSV( 50-colorIndex, 255-colorIndex*2, colorIndex*20); // 125Hz
        
//        leds[223] = ColorFromPalette( RainbowStripeColors_p, 90, colorIndex*20, LINEARBLEND); // 16000Hz
//        leds[103] = ColorFromPalette( RainbowStripeColors_p, 90, colorIndex*20, LINEARBLEND); // 16000Hz
      }
      if (i==20) colorIndex=0;
      if (i >20 ){
        colorIndex = max(value, colorIndex);
        leds[49] = CHSV( 160, 255-colorIndex*20, colorIndex*30);
        leds[55] = CHSV( 160, 255-colorIndex*20, colorIndex*30);
        leds[153] = CHSV( 160, 255-colorIndex*20, colorIndex*30);
        leds[159] = CHSV( 160, 255-colorIndex*20, colorIndex*30);
        leds[275] = CHSV( 160, 255-colorIndex*20, colorIndex*30);
        leds[281] = CHSV( 160, 255-colorIndex*20, colorIndex*30);
        //leds[376] = CHSV( 160, 255-colorIndex*20, colorIndex*30);
        //leds[382] = CHSV( 160, 255-colorIndex*20, colorIndex*30);
        //leds[42].fadeToBlackBy(colorIndex*5);
        //for(int c = 42; c < 42 + 20; c++) {
          //leds[c] = CRGB::White;
          //leds[c].fadeLightBy(colorIndex*5);
        //}
        //leds[104] = ColorFromPalette( RainbowStripeColors_p, 30, colorIndex*5, LINEARBLEND); // 250Hz
      }
      //if (i >15  && i<=20 )  leds[442] = ColorFromPalette( RainbowStripeColors_p, 150, colorIndex*8, LINEARBLEND); // 4000Hz
      //if (i >20  && i<=31 )  leds[222] = ColorFromPalette( RainbowStripeColors_p, 210, colorIndex*100, LINEARBLEND); // 8000Hz
      
      //if (dat <6) fadeToBlackBy(leds, 443, 10);;
//      if (dat >8 && dat<=20) brightness = 196;
//      if (dat >20) brightness = 255;
//    FastLED.show(); 
  //FastLED.delay(1000/100); 
    //delay(1);
    //Serial.println(dat);
    //fadeToBlackBy(leds, 443, 10);
    //display.drawLine(i*2 + x, ylim, i*2 + x, ylim - dat, WHITE); // draw bar graphics for freqs above 500Hz to buffer
  };     
//  leds[104] = ColorFromPalette( RainbowStripeColors_p, colorIndex, brightness, LINEARBLEND);
//  leds[222] = ColorFromPalette( RainbowStripeColors_p, colorIndex, brightness, LINEARBLEND);
//  leds[327] = ColorFromPalette( RainbowStripeColors_p, colorIndex, brightness, LINEARBLEND);
//  leds[0] = ColorFromPalette( RainbowStripeColors_p, colorIndex, brightness, LINEARBLEND);
//  leds[442] = ColorFromPalette( RainbowStripeColors_p, colorIndex, brightness, LINEARBLEND);

  FastLED.show(); 
  //delay(1);
                                   
                                  //show the buffer
};



