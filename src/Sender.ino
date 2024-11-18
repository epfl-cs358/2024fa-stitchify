#include <Servo.h>

Servo myServo;  
int angle = 0;

void setup() {
  Serial.begin(9600);   
  myServo.attach(9);    
}

void loop() {
  for (angle = 0; angle <= 180; angle += 45) {  
    myServo.write(angle);  
    Serial.write(angle);
    delay(1000);  
  }
}
