#include <Servo.h>
Servo myservo;

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

/*
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
*/

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
  myservo.attach(5); 
  // setupESP8266();            
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
        myservo.write(0); 
        delay(2000);
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
        myservo.write(90); 
        digitalWrite(9, HIGH);  
        digitalWrite(10, LOW);
        blink();
        delay(2000);
        digitalWrite(9, LOW);    
        Door = 1;   
      }
      else if (Door==1) {    
        digitalWrite(13, HIGH);
        digitalWrite(12, LOW);
        digitalWrite(10, HIGH);  
        digitalWrite(9, LOW);
        myservo.write(0); 
        blink();
        delay(2000);
        digitalWrite(10, LOW);    
        Door = 0;   
      }
    }
  }
  // anydata(m, Door);
}
