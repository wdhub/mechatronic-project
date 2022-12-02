// Motor A
 
int enA = 8;
int in1 = 2;
int in2 = 3;
 
void setup()
 
{
 
  // Set all the motor control pins to outputs
 
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
 
}
 
void demoOne()
 
{
 
  // This function will run the motors in both directions at a fixed speed
 
  // Turn on motor A
 
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(1000);

}
 
void demoTwo()
 
{
  
  for (int i = 0; i < 256; i++)
 
  {
 
    analogWrite(enA, i);
    delay(20);
 
  } 
 
  // Decelerate from maximum speed to zero
 
  for (int i = 255; i >= 0; --i)
 
  {
 
    analogWrite(enA, i);
    delay(20);
 
  } 
 
  // Now turn off motors
 
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
}
 
void loop()
 
{
 
  demoOne();
 
  delay(1000);
 
  demoTwo();
 
  delay(1000);
 
}
