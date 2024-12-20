#include <Wire.h>
#include <Servo.h>

#define servo_pin_1 9 
#define servo_pin_2 10 

int angle_1 = 0;
int angle_2 = 0; 
int nema_angle = 0;

Servo servo_1; 
Servo servo_2;

void setup() {
  pinMode(servo_pin_1, OUTPUT);
  pinMode(servo_pin_2, OUTPUT);

  Serial.begin(9600);
  Wire.begin();

  servo_1.attach(servo_pin_1);
  servo_2.attach(servo_pin_2);

  servo_1.write(0);
  servo_2.write(0);

  Serial.println("Enter the first angle for Servo1 (0-180):");
}

void loop() {
  if (Serial.available() > 0) {
    angle_1 = Serial.parseInt();
    Serial.read();

    if (angle_1 > 180) angle_1 = 180;
    Serial.print("First angle for Servo1: ");
    Serial.println(angle_1);

    servo_1.write(angle_1);
    delay(1000); 

    Serial.println("Enter the angle for Servo2 (0-180):");

    while (Serial.available() == 0) {
    }

    angle_2 = Serial.parseInt();
    Serial.read(); 

    if (angle_2 > 180) angle_2 = 180;
    Serial.print("Angle for Servo2: ");
    Serial.println(angle_2);

    servo_2.write(angle_2);
    delay(1000);

    Serial.println("Enter the angle for NEMA motor:");

    while (Serial.available() == 0) {
    }

    nema_angle = Serial.parseInt();
    Serial.read(); 

    Serial.print("Sending to NEMA: ");
    Serial.println(nema_angle);

    delay(1000);

    Wire.beginTransmission(8); 
    Wire.write(angle_1); 
    Wire.write(angle_2); 
    Wire.write(nema_angle); 
    Wire.endTransmission(); 

    delay(4000);
    Serial.println("Enter the first angle for Servo1 (0-180):");
  }
}
