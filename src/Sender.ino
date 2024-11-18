#include <Wire.h>
#include <Servo.h>

#define servoPin 9   // Pin to control the servo

int angle = 0;        // First angle value
int angle2 = 0;       // Second angle value
Servo myServo;        // Create a Servo object

void setup() {
  pinMode(servoPin, OUTPUT);    // Pin for controlling the servo

  Serial.begin(9600);           // Start serial communication at 9600 baud rate
  Wire.begin();                 // Start I2C communication as master
  myServo.attach(servoPin);     // Attach the servo to the specified pin
  myServo.write(0);             // Initialize the servo at 0 degrees
  Serial.println("Enter the first angle (0-180):");
}

void loop() {
  if (Serial.available() > 0) {
    // Read the first angle from Serial Monitor
    angle = Serial.parseInt();
    Serial.read();  // Clear the buffer

    // Check if the first angle is within the valid range (0-180)
    if (angle >= 0 && angle <= 180) {
      Serial.print("Sending first angle: ");
      Serial.println(angle);

      // Move the servo to the first angle
      myServo.write(angle); // Move servo to the first angle
      delay(1000);           // Wait for the servo to reach the position

      // Ask for the second angle
      delay(2000);  // Wait for a moment before asking for the second angle
      Serial.println("Enter the second angle (0-180):");

      // Wait until the user provides the second angle
      while (Serial.available() == 0) {
        // Wait for the user input
      }

      // Read the second angle
      angle2 = Serial.parseInt();  
      Serial.read();  // Clear the buffer

      // Check if the second angle is within the valid range (0-180)
      if (angle2 >= 0 && angle2 <= 180) {
        Serial.print("Sending second angle: ");
        Serial.println(angle2);

        delay(1000);             // Wait for the servo to reach the position

        // Send both angles over I2C to the slave Arduino
        Wire.beginTransmission(8); // 8 is the I2C address of the slave Arduino
        Wire.write(angle);         // Send the first angle data
        Wire.write(angle2);        // Send the second angle data
        Wire.endTransmission();    // End the transmission

        // Provide feedback in Serial Monitor
        Serial.print("Angles sent to slave: ");
        Serial.print(angle);
        Serial.print(", ");
        Serial.println(angle2);

        delay(4000);  // Wait before accepting the next angle input
        Serial.println("Enter the first angle (0-180):");
      } 
      else {
        Serial.println("Invalid second angle! Please enter a value between 0 and 180.");
      }
    } 
    else {
      Serial.println("Invalid first angle! Please enter a value between 0 and 180.");
    }
  }
}
