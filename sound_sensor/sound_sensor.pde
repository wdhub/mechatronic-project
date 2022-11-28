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
  song =new SoundFile(this,"clip.mp3");
  song.loop();
}

void draw()
{
  if ( myPort.available() > 0) {  // If data is available,
    val = myPort.read();         // read it and store it in val
  }
  background(2, 44, 67);
  
  float volume=pow(val-20,2)/10;
  ellipse(350, 350, volume*100, volume*100);
  fill(255, 215, 0);
  song.amp(volume);
  println(volume);
}
