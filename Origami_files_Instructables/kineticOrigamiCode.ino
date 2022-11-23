#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// define digital gates
#define gate1 10
#define gate2 11
#define gate3 12
#define gate4 13

#define echoPin1 2
#define trigPin1 3
#define echoPin2 4
#define trigPin2 5
#define echoPin3 6
#define trigPin3 7
#define echoPin4 8
#define trigPin4 9

// position variable for servo motors
int pos = 0;
int pos1 = 0;   
int pos2 = 0;   
int pos3 = 0;   
int pos4 = 0;   

const int deg = 60;
const int MAX = 10x0; // max distance to trigger 

// trigger servo motors;
boolean trigServo1 = false;
boolean trigServo2 = false;
boolean trigServo3 = false;
boolean trigServo4 = false;

// variables for ultra sensors
long duration, distance, distance1, distance2, distance3, distance4;

// track time
int count;
int lastCount;

bool afterReset;

void runServo(Servo servo, int numDelay, int n, int formalPos, boolean trig) {
//  pos = formalPos;
//  boolean finishedTask = false;
//  if (pos == deg) {
//    finishedTask = true;
//  } else {
//    Serial.println("pos = " + String(pos) + " trig? = " + String(trig) + " finished? = " + String(finishedTask));
//    if ((finishedTask == false) && trig) {
//      pos += n;
//    } else {
//      pos = 70;
//    }
//    servo.write(pos);
//    delay(5);
//  }
  pos = formalPos;
  if (pos < deg) {
    pos += 1;
    servo.write(pos);
  }
  
}

void closeServo(Servo servo, int numDelay, int n, int formalPos) {
  pos = formalPos;
  if (pos > 0) {
    pos -= 1;
    servo.write(pos);
  }
  
}

void UltraSensor(int trigPin,int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
}

void setup() {
  servo1.attach(gate1);
  servo2.attach(gate2);
  servo3.attach(gate3);
  servo4.attach(gate4);

  //set up the trig and echo gates
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);

  Serial.begin(9600);
  Serial.println("Start running detection");
  afterReset = true;
  count = 0;
}

void loop() {
//  runServo(servo1, pos1, 70, 15, 1);
//  runServo(servo2, pos2, 70, 15, 1);
//  runServo(servo3, pos3, 70, 15, 1);
//  runServo(servo4, pos4, 70, 15, 1);
  if (count == 0) {
    servo1.write(0);
    servo2.write(0);
    servo3.write(0);
    servo4.write(0);
    UltraSensor(trigPin1, echoPin1);
    distance1 = distance;
  
    UltraSensor(trigPin2, echoPin2);
    distance2 = distance;
  
    UltraSensor(trigPin3, echoPin3);
    distance3 = distance;
  
    UltraSensor(trigPin4, echoPin4);
    distance4 = distance;
  }

  if (count - lastCount > 30) {
    UltraSensor(trigPin1, echoPin1);
    distance1 = distance;
  
    UltraSensor(trigPin2, echoPin2);
    distance2 = distance;
  
    UltraSensor(trigPin3, echoPin3);
    distance3 = distance;
  
    UltraSensor(trigPin4, echoPin4);
    distance4 = distance;

    lastCount = count;
  }

  Serial.print(distance1);
  Serial.print(" - ");
  Serial.print(distance2);
  Serial.print(" - ");
  Serial.print(distance3);
  Serial.print(" - ");
  Serial.println(distance4);

  if (distance1 <= MAX) {
    trigServo1 = true;
  } else {
    trigServo1 = false;
  }
  if (distance2 <= MAX) {
    trigServo2 = true;
  } else {
    trigServo2 = false;
  }
  if (distance3 <= MAX) {
    trigServo3 = true;
  } else {
    trigServo3 = false;
  }
  if (distance4 <= MAX) {
    trigServo4 = true;
  } else {
    trigServo4 = false;
  }

  if (trigServo1) {
    runServo(servo1, 15, 1, pos1, trigServo1);
    pos1 = pos;
  } else {
    closeServo(servo1, 15, 1, pos1);
    pos1 = pos;
  }
  if (trigServo2) {
    runServo(servo2, 15, 1, pos2, trigServo2);
    pos2 = pos;
  } else {
    closeServo(servo2, 15, 1, pos2);
    pos2 = pos;
  }
  if (trigServo3) {
    runServo(servo3, 15, 1, pos3, trigServo3);
    pos3 = pos;
  }else {
    closeServo(servo3, 15, 1, pos3);
    pos3 = pos;
  }
  if (trigServo4) {
    runServo(servo4, 15, 1, pos4, trigServo4);
    pos4 = pos;
  } else {
    closeServo(servo4, 15, 1, pos4);
    pos4 = pos;
  }
  count += 1;
  if (count > 256) {
    count = 1;
    lastCount = 0;
  }
  Serial.println(count);
  delay(5);
}
