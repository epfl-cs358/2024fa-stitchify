#include <Wire.h>

// Pin definitions for the CNC shield (X-axis stepper motor)
#define stepPin 2    // X-axis step pin
#define dirPin  5    // X-axis direction pin
#define enablePin 8  // Enable pin for the motor driver
#define yMinusPin 2  // Y- axis end-stop pin (Negative end stop)
#define yPlusPin 14  // Y+ axis end-stop pin (Positive end stop)
const int SwitchPin = 11;
int currentSteps = 0; // Track the current step position
int targetSteps = 0;  // Target steps based on received data

void setup() {
  // Configure motor driver pins
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // Configure the Y-axis limit switch pins for end stops
  pinMode(yMinusPin, INPUT_PULLUP);  // Y- limit switch (Normally Open)
  pinMode(yPlusPin, INPUT_PULLUP);   // Y+ limit switch (Normally Open)

  // Enable the stepper motor
  digitalWrite(enablePin, LOW);

  // Start I2C communication as slave with address 8
  Wire.begin(8);
  Wire.onReceive(receiveData);

  // Start serial communication for debugging
  Serial.begin(9600);

  pinMode(SwitchPin, INPUT_PULLUP);
  Serial.println("Z- switch test started. ");

  Serial.println("Ready to receive step count.");
}

void loop() {
  // Nothing to do here; motor movement is handled in `moveMotor` function
}

// I2C receive event handler
void receiveData(int byteCount) {
  int steps = 0; // Reset steps variable
  while (Wire.available()) {
    steps = (steps << 8) + Wire.read();  // Read the received byte (step count data)
  }

  // Update the target position with the received step count
  targetSteps = steps;

  Serial.print("Received steps: ");
  Serial.println(steps);

  moveMotor(targetSteps);
}

// Function to move the motor by currentSteps position
void moveMotor(int steps) {

  int stepsPosNeg = 1;
  if(steps < 0) stepsPosNeg = -1;

  if (steps > 0) {
    // Move forward
    digitalWrite(dirPin, HIGH);
  } else if (steps < 0) {
    // Move backward
    digitalWrite(dirPin, LOW);
    steps = -steps; // Make the step difference positive
  } else {
    // Already at the target position
    return;
  }

  // Move the motor step by step
  for (int i = 0; i < steps; i++) {
    // Check if any of the limit switches are pressed
    int switchState = digitalRead(SwitchPin);
    if (switchState == LOW) {
    Serial.println("Switch is NOT pressed!");
    } else {
      Serial.println("Switch is pressed.");
    }
    if (digitalRead(yPlusPin) == LOW) {
      Serial.println("Y+ limit switch pressed. Stopping motor.");
      return; // Stop movement if Y+ switch is pressed
    }

    currentSteps += stepsPosNeg;

    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500); // Adjust delay for speed control
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }

  Serial.print("Motor moved by: ");
  Serial.println(steps);
  Serial.print("Motor at Pos: ");
  Serial.println(currentSteps);
}
