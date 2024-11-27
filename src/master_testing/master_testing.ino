#include <Wire.h>
#include <Servo.h>

#define servoPin1 9 
#define servoPin2 10 

int angle1 = 0;
int angle2 = 0; 
int nemaAngle = 0;

Servo servo1; 
Servo servo2;

void setup() {
  pinMode(servoPin1, OUTPUT);
  pinMode(servoPin2, OUTPUT);

  Serial.begin(9600);
  Wire.begin();

  servo1.attach(servoPin1);
  servo2.attach(servoPin2);

  servo1.write(0);
  servo2.write(0);

  Serial.println("Enter the first angle for Servo1 (0-180):");
}

void loop() {
  if (Serial.available() > 0) {
    angle1 = Serial.parseInt();
    Serial.read();

    if (angle1 > 180) angle1 = 180;
    Serial.print("First angle for Servo1: ");
    Serial.println(angle1);

    servo1.write(angle1);
    delay(1000); 

    Serial.println("Enter the angle for Servo2 (0-180):");

    while (Serial.available() == 0) {
    }

    angle2 = Serial.parseInt();
    Serial.read(); 

    if (angle2 > 180) angle2 = 180;
    Serial.print("Angle for Servo2: ");
    Serial.println(angle2);

    servo2.write(angle2);
    delay(1000);

    Serial.println("Enter the angle for NEMA motor:");

    while (Serial.available() == 0) {
    }

    nemaAngle = Serial.parseInt();
    Serial.read(); 

    Serial.print("Sending to NEMA: ");
    Serial.println(nemaAngle);

    delay(1000);

    Wire.beginTransmission(8); 
    Wire.write(angle1); 
    Wire.write(angle2); 
    Wire.write(nemaAngle); 
    Wire.endTransmission(); 

    delay(4000);
    Serial.println("Enter the first angle for Servo1 (0-180):");
  }
}
