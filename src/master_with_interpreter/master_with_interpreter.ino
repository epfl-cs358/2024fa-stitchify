#include <Wire.h>
#include <Servo.h>

#define servoPin1 9
#define servoPin2 10 
#define servoBigPin 11

int angle1 = 0, angle2 = 0, angle = 0;
int nemaAngle = 0;   
const int angleNeedleUp = 90;
const int angleNeedleDown = 0;
const int timeBetweenNeedles = 100; //TODO : replace with true value, need in milliseconds
const int timeFromLeftTillNeedle = 100; //TODO : replace with true value, need in milliseconds
const int timeFromRightTillNeedle = 120; //TODO : replace with true value, need in milliseconds
const int timeFirstNeedleTillEnd = 40; //TODO : replace with true value, need in milliseconds
int negatif = 0;

int servo1left = 130;
int servo2left = 130;
int servo1right = 0;
int servo2right = 0;

Servo servo1;     
Servo servo2;
Servo servoBig;

void setup() {
  pinMode(servoPin1, OUTPUT);  
  pinMode(servoPin2, OUTPUT);  

  Serial.begin(9600);           
  Wire.begin();              

  servo1.attach(servoPin1); 
  servo2.attach(servoPin2); 
  servoBig.attach(servoBigPin);

  servo1.write(0);
  servo2.write(0); 

  Serial.println("Enter commands: s1 x, s2 x, or n x (e.g., 's1 90').");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim(); 
    if (input.startsWith("l")) {
      servo1.write(servo1left);     
      servo2.write(servo2left);        
      Serial.print("Servos moved left");

    } else if (input.startsWith("r")) {
      servo1.write(servo1right);     
      servo2.write(servo2right);        
      Serial.print("Servos moved right");

    } else if (input.startsWith("s ")) {
      angle = input.substring(2).toInt();
      if (angle > 180) angle = 180; 
      for(int i = 0; i < angle; i++){
        servoBig.write(i); 
        delay(15);
      }  
      Serial.print("Big servo moved");

    } else if (input.startsWith("s1 ")) {
      angle1 = input.substring(3).toInt();
      if (angle1 > 180) angle1 = 180; 
      //choseNeedles(servo1, servo2, angle1); //TODO: replace with number of needles needed to be up
      servo1.write(angle1);         
      Serial.print("Servo1 moved to: ");
      Serial.println(angle1);

    } else if (input.startsWith("s2 ")) {

      angle2 = input.substring(3).toInt();
      if (angle2 > 180) angle2 = 180;
      //choseNeedles(servo2, servo1, angle2); //TODO: replace with number of needles needed to be up
      servo2.write(angle2); 
      Serial.print("Servo2 moved to: ");
      Serial.println(angle2);

    } else if (input.startsWith("n ")) {
      nemaAngle = input.substring(2).toInt();
      int neg = 0;
      if (nemaAngle < 0) 
      {
        nemaAngle = -nemaAngle;
        neg = 1;
      }
      int bit1 = nemaAngle >> 8;
      int bit2 = nemaAngle & 255;

      Serial.print("Sending to NEMA motor: ");
      Serial.println(neg);
      Serial.println((bit1 << 8) + bit2);

      Wire.beginTransmission(8);
      Wire.write(neg); 
      Wire.write(bit1); 
      Wire.write(bit2);
      Wire.endTransmission();

    } else {
      Serial.println("Invalid command. Use 's1 x', 's2 x', or 'n x'.");
    }
  }
}

void choseNeedles(Servo servoUp, Servo servoDown, int nbNeedles){
  int timeUp = timeBetweenNeedles * nbNeedles;
  servoUp.write(angleNeedleUp);
  servoDown.write(angleNeedleDown);
  delay(timeFirstNeedleTillEnd);
  servoDown.write(angleNeedleUp);
  delay(timeUp - timeFirstNeedleTillEnd);
  servoUp.write(angleNeedleDown);
}

void knit(int lines, int startingDirection){

  // knit first line where all needles are chosen
  if(startingDirection == 0){
    choseNeedles(servo1, servo2, 25);
  } else {
    choseNeedles(servo2, servo1, 25);
  }

  for(int i = 1; i < lines; i += 2){
    if(startingDirection == 0){
      delay(timeBetweenNeedles + timeFromLeftTillNeedle); //skip first needle
      choseNeedles(servo2, servo1, 24); //go all the way after skipping the first needle 
      if(i == lines - 1) return;
      delay(timeBetweenNeedles + timeFromRightTillNeedle);
      choseNeedles(servo1, servo2, 24);
    }
    
  }
}