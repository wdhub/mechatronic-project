/*
Run the code and go through it for understanding
Make notes what is happening at each row.

Interruption: compare match interrupt, timer1 16bits
Function: blink pin13, period =2s
//f=16*10^6/(1*1024*15625)=1Hz
 * 
 */

int sensorValue = 0;
 
void setup() {
  DDRB |= 0x20;//pin13 as read/input, other pins remain the same
  PORTB |= 0x20;//set pin13 digital high, other pins remain the same 
 
  cli();
  TCCR1A = 0;//reset timer A
  TCCR1B = 0;//reset timer B
  OCR1A = 15624; //initialize output compare value for timer A
  //f=16*10^6/(1*1024*15625)=1Hz

  
  TCCR1B |= (1 << WGM12); //set WGM12 to 1, CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10);//I/O clk/1024 
  TIMSK1 |= (1 << OCIE1A); //enable time interrupt 
  SREG |= 0x80; //enable global interrupt, is this necessary?
  Serial.begin(9600);
}

ISR(TIMER1_COMPA_vect){// timer interrupt service: what to do during interruption
   PORTB ^= 0x20; //blink pin13, toggle
   //Serial.print("hello");
   sensorValue = digitalRead(13);
   Serial.println(sensorValue);

}

void loop() {//wait for interrupt

}
