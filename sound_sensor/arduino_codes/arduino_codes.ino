#include <MPU6050.h>

/*
  Analog Input

  Demonstrates analog input by reading an analog sensor on analog pin 0 and
  turning on and off a light emitting diode(LED) connected to digital pin 13.
  The amount of time the LED will be on and off depends on the value obtained
  by analogRead().

  The circuit:
  - potentiometer
    center pin of the potentiometer to the analog input 0
    one side pin (either one) to ground
    the other side pin to +5V
  - LED
    anode (long leg) attached to digital output 13
    cathode (short leg) attached to ground

  - Note: because most Arduinos have a built-in LED attached to pin 13 on the
    board, the LED is optional.

  created by David Cuartielles
  modified 30 Aug 2011
  By Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInput
*/

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
float value = 0;  // variable to store the value coming from the sensor
float thres = 452.0;//30degree, 0.79*10/(10+0.79*10)*5/5*1024
float temp=0;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);  
}

void loop() {
  // read the value from the sensor:
  value = analogRead(sensorPin);
  temp=1/(1/298.15+1/4300.00*(log(value/(1023-value))))-273.15;//calculate temperature, https://en.wikipedia.org/wiki/Thermistor
  //Serial.println(temp,6);
  Serial.write(int(temp));
  // stop the program for for <value> milliseconds:
  delay(value);
}
