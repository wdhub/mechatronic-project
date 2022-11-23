/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int previousPos=0;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);//enable serial
}

// goes +5 degree
int turnUp(int previousPos){
    for (pos = previousPos; ((pos <= previousPos+5)&&(pos<180)); pos += 1) { 
    // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);
      Serial.println("pos:");
      Serial.println(pos); 
  }
  previousPos=pos;//update latest position
  Serial.println("previousPos:");
  Serial.println(previousPos);

  return previousPos;
}

int turnDown(int previousPos){
    for (pos = previousPos; ((pos >= previousPos-5)&&(pos>0)); pos -= 1) { 
    // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);
      Serial.println("pos:");
      Serial.println(pos); 
  }
  previousPos=pos;//update latest position
  Serial.println("previousPos:");
  Serial.println(previousPos);

  return previousPos;
}

void loop() {
  int sensorReading = analogRead(A0);
  //if x-axis>200, turn up
  if(sensorReading>300)
    previousPos=turnUp(previousPos);
  //if x-axis<-200, turn down
  if(sensorReading<300)
    previousPos=turnDown(previousPos);
  
  Serial.println("sensor:");
  Serial.println(sensorReading);
  
}
