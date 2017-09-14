int ledPin = 11;
int ledPin2 = 10;
unsigned int i=0;
boolean rise=true;
int period=2000;
void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}
void loop()
{
  if(i == period)
  {
    i=1;
    rise= !rise;
  }
  if(rise == false)
  {
    digitalWrite(ledPin, LOW);
    digitalWrite(ledPin2, LOW);
    delayMicroseconds(i);
    digitalWrite(ledPin, HIGH);
    digitalWrite(ledPin2, HIGH);
    delayMicroseconds(period-i);
    i=i+1;
  }
  if(rise == true)
  {
    digitalWrite(ledPin, LOW);
    digitalWrite(ledPin2, LOW);
    delayMicroseconds(period-i);
    digitalWrite(ledPin, HIGH);
    digitalWrite(ledPin2, HIGH);
    delayMicroseconds(i);
    i=i+1;
  }
}
