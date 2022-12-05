// read sensor data and control the image and sound volume

import processing.serial.*;
import processing.sound.*;
SoundFile song;

Serial myPort;  // Create object from Serial class
int val;      // Data received from the serial port

void setup() 
{
  size(700, 700);
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  //println(portName);
  song =new SoundFile(this,"clip.mp3");
  song.loop();
}

void draw()
{
  if ( myPort.available() > 0) {  // If data is available,
    val = myPort.read();         // read it and store it in val, 0-250
  }
  background(2, 44, 67);
  
  float volume=pow(float(val)-115,2)/400.0;//volume for sound
  ellipse(350, 350, val, val);
  fill(255, 215, 0);
  song.amp(volume);
  println(val);
  
  delay(100);
}
