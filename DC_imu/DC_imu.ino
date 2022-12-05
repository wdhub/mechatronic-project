#include <Wire.h>
#include <MPU6050.h>
#include<LiquidCrystal.h> // lcd Header
LiquidCrystal lcd(13,12,11,10,9,8); // pins for LCD Connection
 
#define motor1_pin1 2
#define motor1_pin2 3
#define motor2_pin1 4
#define motor2_pin2 5
 
MPU6050 gy_521;
 
int16_t ax, ay, az;
int16_t gx, gy, gz;
 
int motor1_speed;
int motor2_speed;
 
void setup ( )
{
Wire.begin( );
 
lcd.begin(16,2); //initializing lcd
Serial.begin(9600); // initializing serial
lcd.print("Initializing.....");
delay(2000);
lcd.clear();
 
Serial.println ("Initializing MPU and testing connections");
// Initialize MPU6050
Serial.println("Initialize MPU6050");
while(!gy_521.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
{
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
}
Serial.println(gy_521.testConnection( ) ? "Successfully Connected" : "Connection failed");
delay(2000);
Serial.print("Reading Values");
delay(2000);
}
 
void loop ( )
{
gy_521.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
ax = map(ax, -17000, 17000, -125, 125);
 
motor1_speed = 125+ax; //To move first motor
motor2_speed = 125-ax; //To move second motor
 
Serial.print ("Motor1 Speed = ");
lcd.setCursor(0,0);
lcd.print ("MOT1 Speed = ");
Serial.print (motor1_speed, DEC);
lcd.print (motor1_speed, DEC);
 
Serial.print ("Motor2 Speed = ");
lcd.setCursor(0,1);
lcd.print ("MOT2 Speed = ");
Serial.println (motor2_speed, DEC);
lcd.print (motor2_speed, DEC);
delay(300);
analogWrite (motor1_pin2, motor1_speed);
analogWrite (motor2_pin2, motor2_speed);
delay (300);
}
