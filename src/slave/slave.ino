#include <Wire.h>

#define stepPin 2  
#define dirPin  5  
#define enablePin 8 
//#define yMinusPin  
//#define yPlusPin 14
const int SwitchPin = 11;
int currentSteps = 0;
int targetSteps = 0;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);

 // pinMode(yMinusPin, INPUT_PULLUP);
 // pinMode(yPlusPin, INPUT_PULLUP);

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
  int neg = 0;
  neg = Wire.read();

  int steps = 0; 
  steps = Wire.read();

  Serial.print("Received steps: ");
  Serial.println(steps);
  Serial.println(neg);

  targetSteps = steps;
  moveMotor(neg, targetSteps);
}

void moveMotor(int neg, int steps) {

  int stepsPosNeg = 1;
  if(neg == 1) stepsPosNeg = -1;

  if (steps == 0)
  {
    return;
  } 
  else if (neg == 0) 
  {
    digitalWrite(dirPin, HIGH);
  } 
  else 
  {
    digitalWrite(dirPin, LOW);
  }

  for (int i = 0; i < steps; i++) {
   int switchState = digitalRead(SwitchPin);
    if (switchState == LOW) 
    {
    //Serial.println("Switch is NOT pressed!");
    } 
    else 
    {
      Serial.println("Switch is pressed.");
      break;
    }

    currentSteps += stepsPosNeg;

    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }

  Serial.print("Motor moved by: ");
  Serial.println(steps);
  Serial.print("Motor at Pos: ");
  Serial.println(currentSteps);
}
