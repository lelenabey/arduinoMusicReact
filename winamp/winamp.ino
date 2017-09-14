#include <SoftPWM.h>
#include <SoftPWM_timer.h>

/*#################################################
 ### --- Winamp + arduio vu meter ---- ###
 ### --- Copyright 2010 - Dave Johnson --- ###
 ###--- Dave@SilverCG.com - www.SilverCG.com --- ###
 ###_____________________________________________###
 ### --- this code includes a vu meter based off ###
 ### data from winamp and converts it to 3 rows ###
 ### of multiplexed leds. ---- ###
 #################################################*/
#include <SoftPWM.h>
 
#define DELAY 80
 
int colpins[] = {2,3,4,5,6,7,8,9,10};
 int rowpins[] = {11,12,13};
 int power = 1;
 //---------------------------------------------
 long timer;
 const long muxInterval = 10;
 int mux = 0;
 int full[27];
 float lvl;
 
void setup() {
 Serial.begin(57600);
// for (int pin=0; pin<9; pin++) {
// pinMode( colpins[pin], OUTPUT );
// }
 for (int pin=0; pin<3; pin++) {
 pinMode( rowpins[pin], OUTPUT );
 }
 timer = millis();
 
SoftPWMBegin();
 
  for (int i = 0; i < 9; i++){
    SoftPWMSet(colpins[i], 0);
  }
}
void loop(){
 
int divide = 5;
 //------------------------------------------------------------
 float total; // for calculations below. <>
 int data[9]; // raw serial data <>
 
if (Serial.available() >10) {
 byte i = Serial.read();
 if (int(i) == 255) {
 for (int c = 0; c < 9; c++){
 data[c] = int(Serial.read());
 
}
 }
 }
 // some math -------------
 
lvl = (data[0] + data[1] + data[2] + data[3] + data[4] + data[5] + data[6] + data[7] + data[8]) / 9;
 //lvl = (data[1] + data[2] + data[3]) / divide;
 //lvl2 = (data[0] + data[7] + data[8]) / divide;
 //lvl3 = (data[4] + data[5] + data[6]) / divide;
 // math end -----------------
 
// reset leds ---------------
 for (int i = 0; i < 27; i++){ full[i] = 0; } 
 
 int length = 5; // sets how long the tail is, so as the meter goes up there is 9 or less leds on at a times... 
 // feel free to change this to what you like. 
 // ------------------------------- 
 int mapvalue2; 
 int mapvalue = map(lvl, 0, 255, 0, 27); 
 if (mapvalue >= length){
 mapvalue2 = mapvalue - length + 1;
 }
 if (mapvalue < length) {
 mapvalue2 = 0;
 }
 for (int x = mapvalue2; x <= mapvalue; x++){
 full[x] = 1;
 }
 // set leds end--------------
 
// patterns feel free to change these to what ever you want the posiblities are endless. 0 - 26 is equel to 27 leds..
 
// int meterlist[9]= {full[0], full[1], full[2], full[13], full[14], full[15], full[16], full[17], full[26]};
// int meterlist2[9] = {full[5], full[4], full[3], full[12], full[11], full[20], full[19], full[18], full[25]};
// int meterlist3[9] = {full[6], full[7], full[8], full[9], full[10], full[21], full[22], full[23], full[24]};
//
//int meterlist[9]= {full[0], full[1], full[2], full[3], full[4], full[5], full[6], full[7], full[8]};
//int meterlist2[9] = {full[17], full[16], full[15], full[14], full[13], full[12], full[11], full[10], full[9]};
//int meterlist3[9] = {full[18], full[19], full[20], full[21], full[22], full[23], full[24], full[25], full[26]};
 
 
int meterlist[9]= {full[2], full[3], full[8], full[9], full[14], full[15], full[20], full[21], full[26]};
int meterlist2[9] = {full[1], full[4], full[7], full[10], full[13], full[16], full[19], full[22], full[25]};
int meterlist3[9] = {full[0], full[5], full[6], full[11], full[12], full[17], full[18], full[23], full[24]};
 
//int meterlist[9]= {full[0], full[6], full[12], full[18], full[5], full[11], full[17], full[23], full[26]};
//int meterlist2[9] = {full[1], full[7], full[13], full[19], full[4], full[10], full[16], full[22], full[26]};
//int meterlist3[9] = {full[2], full[8], full[14], full[20], full[3], full[9], full[15], full[21], full[26]};
 
//map to 9
//int meterlist[9]= {full[0], full[1], full[2], full[3], full[4], full[5], full[6], full[7], full[8]};
//int meterlist2[9]= {full[0], full[1], full[2], full[3], full[4], full[5], full[6], full[7], full[8]};
//int meterlist3[9]= {full[0], full[1], full[2], full[3], full[4], full[5], full[6], full[7], full[8]};
 
//int meterlist[9]= {full[26], full[16], full[14], full[4], full[2], full[8], full[10], full[20], full[22]};
//int meterlist2[9] = {full[24], full[18], full[12], full[6], full[0], full[6], full[12], full[18], full[24]};
//int meterlist3[9] = {full[22], full[20], full[10], full[8], full[2], full[4], full[14], full[16], full[26]};
 
//multiplex drawing.
 if (millis() - timer < muxInterval) { timer = millis(); mux++; if (mux > 2){
 mux = 0;
 }
 for (int i = 0; i <=8; i++){ 
 SoftPWMSet(colpins[i], 0);
 } digitalWrite(rowpins[0], LOW); 
 digitalWrite(rowpins[1], LOW); 
 digitalWrite(rowpins[2], LOW); 
 if (mux == 0) { for (int i = 8; i >= 0; i--) {
 if (meterlist[i] == 1){
 SoftPWMSet(colpins[i], power, true);
 digitalWrite(rowpins[0], HIGH);
 }
 
}
 }
 if (mux == 1) {
 
for (int i = 8; i >= 0; i--) {
 if (meterlist2[i] == 1){
 SoftPWMSet(colpins[i], power, true);
 digitalWrite(rowpins[1], HIGH);
 }
 
}
 }
 if (mux == 2) {
 
for (int i = 8; i >= 0; i--) {
 if (meterlist3[i] == 1){
 SoftPWMSet(colpins[i], power, true);
 digitalWrite(rowpins[2], HIGH);
 }
 
}
 }
 
}
 
}
