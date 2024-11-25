#include <Wire.h>

#define stepPin 2  
#define dirPin  5
#define enablePin 8  
#define yMinusPin 2 
#define yPlusPin 14  
const int SwitchPin = 11;
int currentSteps = 0; 
int targetSteps = 0; 

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);

  pinMode(yMinusPin, INPUT_PULLUP); 
  pinMode(yPlusPin, INPUT_PULLUP);  

  digitalWrite(enablePin, LOW);

  Wire.begin(8);
  Wire.onReceive(receiveData);

  Serial.begin(9600);

  pinMode(SwitchPin, INPUT_PULLUP);
  Serial.println("Z- switch test started. ");

  Serial.println("Ready to receive step count.");
}

void loop() {
}

void receiveData(int byteCount) {
  int steps = 0; 
  while (Wire.available()) {
    steps = (steps << 8) + Wire.read(); 
  }
  targetSteps = steps;

  Serial.print("Received steps: ");
  Serial.println(steps);

  moveMotor(targetSteps);
}

// Function to move the motor to the target position
void moveMotor(int targetSteps) {
  int stepDifference = targetSteps - currentSteps;

  int stepPosNeg = 1;
  if(stepDifference < 0) stepPosNeg = -1;

  if (stepDifference > 0) {
    // Move forward
    digitalWrite(dirPin, HIGH);
  } else if (stepDifference < 0) {
    // Move backward
    digitalWrite(dirPin, LOW);
    // Make the step difference positive
    stepDifference = -stepDifference; 
  } else {
    // Already at the target position
    return;
  }

  // Move the motor step by step
  for (int i = 0; i < stepDifference; i++) {
    // Check if any of the limit switches are pressed
    int switchState = digitalRead(SwitchPin);
    if (switchState == LOW) {
    //Serial.println("Switch is NOT pressed!");
    } else {
      break;
    }

    currentSteps += stepPosNeg;

    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500); 
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }


  Serial.print("Motor moved to position: ");
  Serial.println(currentSteps);
}
