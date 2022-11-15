/*Lab 2. Embedded programming.  
 * What is happening below?
 * Follow the code and fill in comments for clarification
 * f=16*10^6/(64*1000*(256-6))=1Hz
 * Interruption: overflow interruption, 8 bits counter
 */

int count=0, check=1;   
int sensorValue = 0;



ISR (TIMER0_OVF_vect)// timer0 overflow interrupt service (what to do during interrupt)    
  {
  count++; 
  // toggle pin13 everytime counter reach 1000
  if (count == 1000 && check == 1)
    {
      PORTB |= 0x20;// set pin13 as high
      count = 0;// reset count to 0
      check = 0; // togle check flag
      sensorValue = digitalRead(13);// the code I added to validate the result
      Serial.println(sensorValue);             
    }
  else if (count == 1000 && check == 0)
    {
      PORTB = 0x00;// reset all the port B
      count = 0;// reset count to 0
      check = 1;// toggle flag
      sensorValue = digitalRead(13);// the code I added to validate the result
      Serial.println(sensorValue);
    }
  else
    {
    
    }

  }




int main(void) 
  {
  cli(); //no interrupt
  DDRB |= 0b00100000; //pin13 as read/input, other pins remain the same
  TCCR0A = 0; //reset timer A
  TCCR0B = 0; //reset timer B
  TIMSK0 |= (1<<TOIE0); //enable timer 0 overflow interrupt
  TCNT0 = 6; //set timer 0 start value to 6
  //f=16*10^6/(64*1000*(256-6))=1Hz
  TCCR0B |= (1<<CS01) | (1<<CS00); //I/O clk/64
   //f=16*10^6/(1*1024*15625)=1Hz
   
  PORTB = 0x00;//reset portB
  sei(); //enable interrupt
  Serial.begin(9600);
  //wait for interruption
  while(1) 
    {

    }
  }
  
