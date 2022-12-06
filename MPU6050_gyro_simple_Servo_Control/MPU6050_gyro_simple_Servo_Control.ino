/*
    IMU - ARDUINO - DC MOTOR (wings of bird)
                  - SERVO MOTOR (not using for now)
                  - PROCESSING (visual+sound effect)
    Function:
    - raise hand, dc motor speed up; lower hand, motor speed down;
    - the higher the speed is, the bigger the moon in Processing is;
    - the volume of music change according to speed now. Can be changed to other axis of imu.
                  
    ARDUINO-PROCESSING:
    - Comment all the serial.println(), if communication between arduino and processing needed.
    - Adjust the speed of sending mainly via delay in loop():
      - too fast: processing can't react in time
      - too slow: arduino can't react to imu in time
      - Baud rate: 9600. can be adjusted, but not helping much.
    
    
*/

#include <Wire.h>
#include <MPU6050.h>
#include <Servo.h>

// servo variables
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
int previousPos=0; // latest position of servo

//pin definition
int enA = 9;
int in1 = 4;
int in2 = 5;

int speed;// speed of dc motor, int, 0-250

//imu variable
MPU6050 mpu;


void setup() 
{
  //dc motor set up
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  //enable motor
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  
  Serial.begin(9600);

  
  // Initialize MPU6050
  Serial.println("Initialize MPU6050");
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  //imu set up
  mpu.calibrateGyro();
  mpu.setThreshold(3);
  checkSettings();
  
  //myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  
}

void checkSettings()
{
  Serial.println();
  
  Serial.print(" * Sleep Mode:        ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
  
  Serial.print(" * Clock Source:      ");
  switch(mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }
  
  Serial.print(" * Gyroscope:         ");
  switch(mpu.getScale())
  {
    case MPU6050_SCALE_2000DPS:        Serial.println("2000 dps"); break;
    case MPU6050_SCALE_1000DPS:        Serial.println("1000 dps"); break;
    case MPU6050_SCALE_500DPS:         Serial.println("500 dps"); break;
    case MPU6050_SCALE_250DPS:         Serial.println("250 dps"); break;
  } 
  
  Serial.print(" * Gyroscope offsets: ");
  Serial.print(mpu.getGyroOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getGyroOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getGyroOffsetZ());
  
  Serial.println();
}


//servo Motor functions

// goes +5 degree
int turnUp(int previousPos){
    for (pos = previousPos; ((pos <= previousPos+5)&&(pos<180)); pos += 1) { 
    // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);
      //Serial.println("pos:");
      //Serial.println(pos); 
  }
  previousPos=pos;//update latest position
  //Serial.println("previousPos:");
  //Serial.println(previousPos);

  return previousPos;
}

int turnDown(int previousPos){
    for (pos = previousPos; ((pos >= previousPos-5)&&(pos>0)); pos -= 1) { 
    // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);
      //Serial.println("pos:");
      //Serial.println(pos); 
  }
  previousPos=pos;//update latest position
  //Serial.println("previousPos:");
 //Serial.println(previousPos);

  return previousPos;
}






void loop()
{
  Vector rawGyro = mpu.readRawGyro();
  Vector normGyro = mpu.readNormalizeGyro();

//base control
 
//wing control
  speed=map(rawGyro.YAxis,-17000,17000,-125,125);
  speed+=125;
  //Serial.println(speed);

  // communicate to processing  
  Serial.write(int(speed));// int(speed)
  
 
  analogWrite(enA, speed);

  delay(500);

  //Serial.println(rawGyro.YAxis);

  
   
}
