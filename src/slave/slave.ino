/*
Slave program that will receive data wired from the Master program. Will notably control the stepper motor with
the number of steps passed from the Master and also stop movement when the switch is activated. 
*/

#include <Wire.h>

#define stepPin 2  
#define dirPin  5  
#define enablePin 8 
//#define yMinusPin  
//#define yPlusPin 14
const int switchPinRight = 11;
const int switchPinLeft = 10;
int currentSteps = 0;
int targetSteps = 0;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(switchPinRight, INPUT_PULLUP);
  pinMode(switchPinLeft, INPUT_PULLUP);

 // pinMode(yMinusPin, INPUT_PULLUP);
 // pinMode(yPlusPin, INPUT_PULLUP);

  digitalWrite(enablePin, LOW);

  //Starts connection with the Master, awaits data receipt
  Wire.begin(8);
  Wire.onReceive(receiveData);

  Serial.begin(9600);
  Serial.println("Ready to receive step count.");
}

void loop() {
}

/*
Method that will be called when the slave receives data from the master
*/
void receiveData(int byteCount) {
  int neg = 0, steps = 0;
  neg = Wire.read();
  steps = Wire.read();
  steps = (steps << 8) + Wire.read(); //shift first 8 bits received and add the last 8 bits at the end

  Serial.print("Received steps: ");
  Serial.println(steps);
  Serial.println(neg);

  targetSteps = steps;
  moveMotor(neg, targetSteps);
}

/*
Method that will move the stepper motor and also manages negative steps and when the switch is activated
*/
void moveMotor(int neg, int steps) {
  int stepsPosNeg = neg == 1 ? -1 : 1;

  if (steps == 0) return;
  else if (neg == 0) {
    digitalWrite(dirPin, HIGH); } 
  else {
    digitalWrite(dirPin, LOW); }

  for (int i = 0; i < steps; i++) {
    int switchStateRight = digitalRead(switchPinRight);
    int switchStateLeft = digitalRead(switchPinLeft); 
    if (switchStateRight == HIGH or switchStateLeft == HIGH) {
      return; //switch is pressed == reached end of the bed
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