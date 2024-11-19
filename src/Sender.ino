#include <Wire.h>
#include <Servo.h>

#define servoPin1 9   // Pin to control the first servo
#define servoPin2 10  // Pin to control the second servo

int angle1 = 0;        // First angle value for Servo1
int angle2 = 0;        // First angle value for Servo2
int nemaAngle = 0;     // Second angle value for NEMA motor

Servo servo1;          // Create Servo1 object
Servo servo2;          // Create Servo2 object

void setup() {
  pinMode(servoPin1, OUTPUT);    // Pin for controlling the first servo
  pinMode(servoPin2, OUTPUT);    // Pin for controlling the second servo

  Serial.begin(9600);           // Start serial communication at 9600 baud rate
  Wire.begin();                 // Start I2C communication as master

  servo1.attach(servoPin1);     // Attach the first servo to the specified pin
  servo2.attach(servoPin2);     // Attach the second servo to the specified pin

  servo1.write(0);              // Initialize the first servo at 0 degrees
  servo2.write(0);              // Initialize the second servo at 0 degrees

  Serial.println("Enter the first angle for Servo1 (0-180):");
}

void loop() {
  if (Serial.available() > 0) {
    // Read the first angle for Servo1 from Serial Monitor
    angle1 = Serial.parseInt();
    Serial.read();  // Clear the buffer

    // Check if the first angle is within the valid range (0-180)
    if (angle1 > 180) angle1 = 180;
    Serial.print("First angle for Servo1: ");
    Serial.println(angle1);

    // Move the first servo to the specified angle
    servo1.write(angle1); // Move Servo1 to the first angle
    delay(1000);           // Wait for the servo to reach the position

    Serial.println("Enter the angle for Servo2 (0-180):");

    // Wait until the user provides the angle for Servo2
    while (Serial.available() == 0) {
      // Wait for the user input
    }

    // Read the angle for Servo2
    angle2 = Serial.parseInt();
    Serial.read();  // Clear the buffer

    // Check if the angle is within the valid range (0-180)
    if (angle2 > 180) angle2 = 180;
    Serial.print("Angle for Servo2: ");
    Serial.println(angle2);

    // Move the second servo to the specified angle
    servo2.write(angle2); // Move Servo2 to the second angle
    delay(1000);           // Wait for the servo to reach the position

    Serial.println("Enter the angle for NEMA motor:");

    // Wait until the user provides the NEMA motor angle
    while (Serial.available() == 0) {
      // Wait for the user input
    }

    // Read the angle for NEMA motor
    nemaAngle = Serial.parseInt();
    Serial.read();  // Clear the buffer

    Serial.print("Sending to NEMA: ");
    Serial.println(nemaAngle);

    delay(1000);  // Wait before sending data

    // Send all angles over I2C to the slave Arduino
    Wire.beginTransmission(8); // 8 is the I2C address of the slave Arduino
    Wire.write(angle1);        // Send the first servo angle
    Wire.write(angle2);        // Send the second servo angle
    Wire.write(nemaAngle);     // Send the NEMA motor angle
    Wire.endTransmission();    // End the transmission

    delay(4000);  // Wait before accepting the next angle input
    Serial.println("Enter the first angle for Servo1 (0-180):");
  }
}
