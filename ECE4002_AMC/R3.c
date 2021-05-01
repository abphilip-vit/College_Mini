String ssid     = "Simulator Wifi";  
String password = ""; 
String host     = "api.thingspeak.com"; 
const int httpPort   = 80;
String uri     = "/update?api_key=RDRD4KQJS6ECPD7V&field1=";
int Distance = 0;
int Door = 0; // Closed Initially
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

int setupESP8266(void) {
  Serial.begin(115200);   
  Serial.println("AT");   
  delay(10);        
  if (!Serial.find("OK")) return 1;
  Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
  delay(10);        
  if (!Serial.find("OK")) return 2;
  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort);
  delay(50);        
  if (!Serial.find("OK")) return 3;
  return 0;
}

void anydata(int t1, int t2) {
  int temp1 = map(t1,0,1000,0,1000);
  int temp2 = map(t2,0,1000,0,1000);
  String httpPacket = "GET " + uri + String(temp1) + "&field2=" + String(temp2) +"&amp" + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
  int length = httpPacket.length();
  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  delay(10); 
  Serial.print(httpPacket);
  delay(10); 
  if (!Serial.find("SEND OK\r\n")) return;
}
void ring(){
  tone(7, 1000, 200);
  delay(100);
  noTone(7);
}
void blink(){
  for(int i=0;i<5;i++){
    digitalWrite(8, HIGH);
    delay(200);
    digitalWrite(8, LOW);
    delay(200);
  }
}

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, INPUT);
  pinMode(10, INPUT);
  pinMode(9, INPUT);
  pinMode(8, OUTPUT);
  setupESP8266();            
}

void loop() {
  Distance = 0.01723 * readUltrasonicDistance(3, 2);
  int m = 0;
  if (Distance >= 100) {
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    m=0;
    if (Door==1) {    
      	digitalWrite(13, HIGH);      
        digitalWrite(10, HIGH);  
        digitalWrite(9, LOW);
        blink();
        digitalWrite(13, HIGH);
        digitalWrite(10, LOW);    
        Door = 0;   
    }
  }

  else {
    if (Door==0){
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
      ring();
    }
    else if (Door==1){
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);
    }
    m=1;
    // 11 is the close/open button
    if(digitalRead(11)==HIGH) {
      if (Door==0) {    
        digitalWrite(12, HIGH);
        digitalWrite(13, LOW);
        digitalWrite(9, HIGH);  
        digitalWrite(10, LOW);
        blink();
        digitalWrite(9, LOW);    
        Door = 1;   
      }
      else if (Door==1) {    
        digitalWrite(13, HIGH);
        digitalWrite(12, LOW);
        digitalWrite(10, HIGH);  
        digitalWrite(9, LOW);
        blink();
        digitalWrite(10, LOW);    
        Door = 0;   
      }
    }
  }
  anydata(m, Door);
}

// Ultrasonic Sensor
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

int TimerOverflow = 0;

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;
}
int main(void)
{
	char string[10];
	long count;
	double distance;
	DDRA = (1<<PA0);
	PORTD = (1<<PD6);
	sei();
	TIMSK = (1 << TOIE1);	
	TCCR1A = 0;		/* Set all bit to zero Normal operation */

	while(1)
	{
		PORTA |= (1 << PA0);    /* Give 10us trigger pulse on trig. pin to HC-SR04 */
		_delay_us(10);
		PORTA &= (~(1 << PA0));
		
		TCNT1 = 0;	                        /* Clear Timer counter */
		TCCR1B = (1<<ICES1)||(1<<CS10);	    /* Capture on rising edge, No scaler*/
		TIFR = 1<<ICF1;
		TIFR = 1<<TOV1;                     /*Calculate width of Echo by Input Capture (ICP) */
		while ((TIFR & (1 << ICF1)) == 0);  /* Wait for rising edge */
		TCNT1 = 0;	            /* Clear Timer counter */
		TCCR1B = 0x01;	        /* Capture on falling edge, No scaler */
		TIFR = 1<<ICF1;	        /* Clear ICP flag (Input Capture flag) */
		TIFR = 1<<TOV1;	        /* Clear Timer Overflow flag */
		TimerOverflow = 0;      /* Clear Timer overflow count */

		while ((TIFR & (1 << ICF1)) == 0);      /* Wait for falling edge */
		count = ICR1 + (65535 * TimerOverflow);	/* Take count */
		distance = (double)count / 466.47;      /* 8MHz Timer freq, sound speed =343 m/s */
		_delay_ms(200);
	}
}

// Motor
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	DDRA = (1<<PA0)|(1<<PA1);
	DDRB = 0x00;
    while (1) { 
 		if(PINB & 1<<PB0){
			PORTA = (1<<PA0);
			_delay_ms(5000);
 			PORTA = 0x00;
		 }
		 else if(PINB & 1<<PB1){
			 PORTA = (1<<PA1);
			 _delay_ms(5000);
			 PORTA = 0x00;
		 }
    }
}