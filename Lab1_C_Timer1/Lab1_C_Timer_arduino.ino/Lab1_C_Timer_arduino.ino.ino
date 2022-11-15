//Blink with the period of 2 second, without delay

const int ledPin =  13;
int check = LOW;             // check flag for LED state
unsigned long lastTime = 0;        // will store last time LED was updated
const long interval = 1000;           // interval at which to blink (milliseconds)

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastTime >= interval) {
    lastTime = currentTime;    // save the last time you blinked the LED
    check^=1;// toggle flag
    digitalWrite(ledPin, check);// set LED according to flag
  }
}
