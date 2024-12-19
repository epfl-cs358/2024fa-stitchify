#include <Wire.h>

#define stepPin 2  
#define dirPin  5  
#define enablePin 8 
#define COMM_SEND_PIN 11

const int switchPinRight = 12;
const int switchPinLeft = 13;

const int expectedPosLeft = 0;
const int expectedPosRight = 0;

int currentPos = 0, targetSteps = 0, stepsPosNeg = 0;

void setup() 
{
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);

  pinMode(switchPinRight, INPUT_PULLUP);
  pinMode(switchPinLeft, INPUT_PULLUP);

  pinMode(COMM_SEND_PIN, OUTPUT);
  digitalWrite(COMM_SEND_PIN, LOW);


  digitalWrite(enablePin, LOW);

  Wire.begin(8);
  Wire.onReceive(receiveData);

  Serial.begin(9600);
  Serial.println("Ready to receive step count.");

  int switchStateRight = digitalRead(switchPinRight);
  int switchStateLeft = digitalRead(switchPinLeft);
  Serial.println(switchStateRight);
  Serial.println(switchStateLeft);
}

void loop() 
{
}

void sendSignalToMaster() {
  digitalWrite(COMM_SEND_PIN, HIGH);
}

void receiveData(int byteCount) 
{
  digitalWrite(COMM_SEND_PIN, LOW);
  
  int neg = 0, steps = 0;
  neg = Wire.read();
  steps = Wire.read();
  steps = (steps << 8) + Wire.read();

  Serial.print("Received steps: ");
  Serial.println(steps);
  Serial.println(neg);

  targetSteps = steps;
  moveMotor(neg, targetSteps);
}

void backUp(int neg)
{
  if (neg == 0) 
  {
    digitalWrite(dirPin, LOW); 
    } 
    else {
      digitalWrite(dirPin, HIGH); 
    }

    for(int j = 0; j < 45; j++)
    { 
      currentPos -= stepsPosNeg;
      digitalWrite(stepPin, HIGH);
      delay(500);
      digitalWrite(stepPin, LOW);
      delay(500);
    }
}

void moveMotor(int neg, int steps) {
  stepsPosNeg = neg == 1 ? -1 : 1;

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

  bool switchPressedAsExpected = 1;
  for (int i = 0; i < steps; i++) {

    int switchStateRight = digitalRead(switchPinRight);
    int switchStateLeft = digitalRead(switchPinLeft);
    if (switchStateRight == HIGH or switchStateLeft == HIGH) {

      if(switchStateRight == HIGH && abs(currentPos - expectedPosRight)>2) 
      {
        switchPressedAsExpected = 0;
      }
      if(switchStateLeft == HIGH && abs(currentPos!=expectedPosLeft)>2) 
      {
        switchPressedAsExpected = 0;
      }

      backUp(neg);
      break;
    }

    currentPos += stepsPosNeg;
    digitalWrite(stepPin, HIGH);
    delay(700);
    digitalWrite(stepPin, LOW);
    delay(700);
  }

  /*
  //We can for example only send signal if switched pressed as expected
  if(switchPressedAsExpected) 
  {
    sendSignalToMaster();
  }
  */


  sendSignalToMaster();

  Serial.print("Motor moved by: ");
  Serial.println(steps);
  Serial.print("Motor at Pos: ");
  Serial.println(currentPos);
}