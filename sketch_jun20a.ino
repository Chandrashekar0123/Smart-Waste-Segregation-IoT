#include <Servo.h>
#include <LiquidCrystal.h>
Servo servo1;
const int trigPin = 9;
const int echoPin = 10;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
long duration;
int distance=0;
int potPin = A0; //input pin
int soil=0;
int fsoil;
void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
//Serial.print("Humidity");
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
servo1.attach(8);
}
void loop() 
{

  
  int soil=0;
  for(int i=0;i<2;i++)
  {
digitalWrite(trigPin, LOW);
delayMicroseconds(7);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
delayMicroseconds(10);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2+distance;
delay(10);

  }
  distance=distance/2;
  Serial.println(distance);
if ((distance <15 && distance>1) || fsoil>3)
{
  delay(1000);
for(int i=0;i<3;i++)
{
soil = analogRead(potPin) ;
soil = constrain(soil, 485, 1023);
fsoil = (map(soil, 485, 1023, 100, 0))+fsoil;
delay(75);
}
fsoil=fsoil/3;
Serial.println(fsoil);
Serial.print("%");
if(fsoil>3)
{delay(1000);
  Serial.print("WET ");
  lcd.clear();
  lcd.print("wet detected");
  servo1.write(180);
delay(3000);} 
else{ delay(1000);
  Serial.print("dry ");
  lcd.clear();
  lcd.print("dry detected");
servo1.write(0);
delay(3000);}

servo1.write(80);}
distance=0;
fsoil=0;
delay(1000);
lcd.clear();
lcd.print("Running...");



}
