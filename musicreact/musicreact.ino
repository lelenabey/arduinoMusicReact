/*
////////////////////////////////////////////////////////////////////////////////
  Bola musical luminosa

 Es una bola que reacciona a la presion sonora iluminandose.
 Según el nivel se ilumina secuencialmente  en azul, verde y rojo.

 El circuito:
 * LED RGB de 4 patillas. Ánodo conectado a 5v, cátodos conectados a
   pines 9,10 y 11 y luego a tierra a través de resistencias de 220 Ohm.
 * Microfono preamplificado en pin analógico 0. (yo use el Breakout Board
   for Electret Microphone sku: BOB-08669 de sparkfun ).
   Tambien se puede utilizar cualquier elemento que nos proporcione un
   voltaje variable hasta 5V.

 Vídeo:                        http://www.youtube.com/watch?v=_QrF_CfAFEY
 Mira tambien:                 http://www.youtube.com/watch?v=hckZEcqkg40


 creado el 22 de junio de 2010
 Por Alejandro Taracido Cano (TCRobotics)
 Canal de youtube:             http://www.youtube.com/user/TCRobotics
 ///////////////////////////////////////////////////////////////////////////////
  Musical ball light
  
 It is a ball that reacts to the sound pressure with light.
 According to the sound level it sequentially lights in blue, green and red.
  
 The circuit:
 * 4-pin RGB LED. 5v connected to anode, cathodes connected to
   pin 9,10 and 11 and then to ground through 220 Ohm resistor.
 * Analog microphone preamplifiers in pin 0. (I use the Breakout Board
   for Electret Microphone sku: BOB-08 669 from SparkFun).
   You can also use anything that will give us a variable voltage
   between 5 and 0 volts.

 Video: http://www.youtube.com/watch?v=_QrF_CfAFEY
 See also: http://www.youtube.com/watch?v=hckZEcqkg40


 created 22 Jun 2010
 By Alejandro Taracido Cano (TCRobotics)
 Youtube channel: http://www.youtube.com/user/TCRobotics
////////////////////////////////////////////////////////////////////////////////
 */
int MicPin = 0;          // pin that the mic is attached to

int redPin = 9;          // pins that the cathodes of LED are attached to  
int greenPin = 10;
int bluePin = 11;

int MicValue = 0;        // the Microphone value

void setup() {
  //Serial.begin(9600);  //for test the input value initialize serial
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  analogWrite(redPin, 255);       //turn off all LEDs
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
}

void loop() {

  MicValue = analogRead(MicPin);  //read the value of the microphone

  //Serial.println(MicValue);     //for test the input value

  if (MicValue > 530) {     //adjust this value to the desired sensitivity
    analogWrite(bluePin,0); //lights up blue
    delay(15);              //small delay for quick response at low noise levels
    }
  
  if (MicValue > 540) {       //adjust this value to the desired sensitivity
    analogWrite(bluePin,255); //lights up green and turn off blue
    analogWrite(greenPin, 0);
    delay(60);               //mid delay for response at mid noise levels
    }
  
  if (MicValue > 550) {        //adjust this value to the desired sensitivity
    analogWrite(greenPin,255); //lights up red and turn off green
    analogWrite(redPin, 0);
    delay(140);                //high delay for response at high noise levels
    }

analogWrite(greenPin, 255);    //Turn off all LEDs
analogWrite(redPin, 255);
analogWrite(bluePin,255);  

} 


