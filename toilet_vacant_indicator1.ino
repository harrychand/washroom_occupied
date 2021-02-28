/*
  Harry's washroom vacant Projects 
  
  @ 1 Ultrasonic Sensor

  This sketch reads four(4) ultrasonic
  rangefinder and identified if the person
  standing on designed area, if yes, it will
  return the range and arduino will determined
  if the door indicator will show red (full) or
  green (vacant). for Covid projects

  The circuit:
   * +V connection of the PING))) attached to +5V
   * GND connection attached to ground
   * SIG connection attached to digital pin 7

  http://www.arduino.cc/en/Tutorial/Ping

  This example code is in the public domain.
*/

#include <Adafruit_NeoPixel.h>

int sensor1 = 0;
int sensor2 = 0;
int sensor3 = 0;
int sensor4 = 0;
float dist = 0;
int trigger; 
int echo;
const int highMax = 220; /Adjust the distance to sense
const int highMin = 1;
const int TrigDey = 1500;

// LED Pin
int LEDa1 = A1;
int LEDa2 = A2;
int LEDa3 = A3;
int LEDa4 = A4;

// NeoPixal
int NUMPIXELS = 12;
const int neoPin = A0;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, neoPin, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(9600);
  //LED indicator
  pinMode(LEDa1,OUTPUT);
  pinMode(LEDa2,OUTPUT);
  pinMode(LEDa3,OUTPUT);
  pinMode(LEDa4,OUTPUT);
  digitalWrite(LEDa1, LOW);
  digitalWrite(LEDa2, LOW);
  digitalWrite(LEDa3, LOW);
  digitalWrite(LEDa4, LOW);
  //Ultrasonic Sensor
  pinMode(3,OUTPUT);
  pinMode(2,INPUT);
  pinMode(5,OUTPUT);
  pinMode(4,INPUT);
  pinMode(7,OUTPUT);
  pinMode(6,INPUT);
  pinMode(9,OUTPUT);
  pinMode(8,INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  pixels.begin();
/* comment or uncomment based on number of sensors to use */
  sensor1 = readUltrasonicDistance(3, 2, LEDa1); 
  //sensor2 = readUltrasonicDistance(5, 4, LEDa2);
  //sensor3 = readUltrasonicDistance(7, 6, LEDa3);
  //sensor4 = readUltrasonicDistance(9, 8, LEDa4);
  Serial.print(sensor1);
  Serial.print("cm , ");
  //Serial.print(sensor2);
  //Serial.print("cm , ");
  //Serial.print(sensor3);
  //Serial.print("cm , ");
  //Serial.print(sensor4);
  //Serial.println("cm , ");
 
  //Outdoor Indicator 
  if(sensor1 > highMax || sensor2 > highMax 
     || sensor3 > highMax || sensor4 > highMax)
	{
    delay(1500);
    NeoPixels(1);
    pixels.show();
	}
  else 
	{
    NeoPixels(0);
    pixels.show();
	}
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(TrigDey); // Wait for 3000 ms
  pixels.clear();
}

long readUltrasonicDistance(int trigger, int echo, int led)
{
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);        
  digitalWrite(trigger,HIGH);   
  delayMicroseconds(10);        
  digitalWrite(trigger,LOW);    
  dist=pulseIn(echo,HIGH)/58;
  LED_SensorIndicator(dist, led);
  return dist; 
}

void NeoPixels(int colour)
{
  if (colour == 1) {
  	for(int i=0;i<NUMPIXELS;i++){
    	pixels.setPixelColor(i, pixels.Color(0,255,0)); 
  	} 
  }
  if (colour == 0) {
  	for(int i=0;i<NUMPIXELS;i++){
    	pixels.setPixelColor(i, pixels.Color(255,0,0)); 
  	} 
  }
}

void LED_SensorIndicator(int sonic, int led)
{
  if(sonic < highMax && sonic > highMin)
	{digitalWrite(led,HIGH);}
  else 
	{digitalWrite(led,LOW);} 
}
