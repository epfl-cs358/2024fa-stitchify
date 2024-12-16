#include <Wire.h>
#include <Servo.h>

#define servoPin1 9
#define servoPin2 10 
#define servoBigPin 11

int angle1 = 0, angle2 = 0, angle = 0;
int nemaAngle = 0;   
int maxSteps = 3000;

int servo1Left = 150;
int servo2Left = 110;
int servo1Right = 40;
int servo2Right = 0;
int bigServoRight = 0;
int bigServoLeft = 12; //need to check on prototype but difference of angles should be = 12 degrees

Servo servo1;     
Servo servo2;
Servo servoBig;

void setup() {
  pinMode(servoPin1, OUTPUT);  
  pinMode(servoPin2, OUTPUT);  
  pinMode(servoBigPin, OUTPUT);

  Serial.begin(9600);           
  Wire.begin();              

  servo1.attach(servoPin1); 
  servo2.attach(servoPin2); 
  servoBig.attach(servoBigPin);

  servo1.write(0);
  servo2.write(0); 
  servoBig.write(0);

  delay(1000); //delay to solve big servo weird behavior

  Serial.println("Enter commands: s1 x, s2 x, or n x (e.g., 's1 90').");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim(); 
    if (input.startsWith("l")) {
      servo1.write(servo1Left);     
      servo2.write(servo2Left);     
      servoBig.write(bigServoLeft);   
      Serial.print("Servos moved left");

    } else if (input.startsWith("r")) {
      servo1.write(servo1Right);     
      servo2.write(servo2Right);    
      servoBig.write(bigServoRight);       
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
      servo1.write(angle1);         
      Serial.print("Servo1 moved to: ");
      Serial.println(angle1);

    } else if (input.startsWith("s2 ")) {

      angle2 = input.substring(3).toInt();
      if (angle2 > 180) angle2 = 180;
      servo2.write(angle2); 
      Serial.print("Servo2 moved to: ");
      Serial.println(angle2);

    } else if (input.startsWith("n ")) {
      nemaAngle = input.substring(2).toInt();
      int neg = 0;
      moveServoDirection(neg);
      
      if (nemaAngle < 0) {
        nemaAngle = -nemaAngle;
        neg = 1;
        moveServoDirection(neg);
      }
      int bit1 = nemaAngle >> 8;
      int bit2 = nemaAngle & 255;

      Serial.print("Sending to NEMA motor: ");
      Serial.println(neg);
      Serial.println((bit1 << 8) + bit2);

      delay(500);
      Wire.beginTransmission(8);
      Wire.write(neg); 
      Wire.write(bit1); 
      Wire.write(bit2);
      Wire.endTransmission();

    } else if (input.startsWith("+ knit ")) {
      Serial.print("knitting lines negative : ");
      int nbLines = input.substring(6).toInt();
      Serial.println(nbLines);
      knit(nbLines, 0);
    
    } else if (input.startsWith("- knit ")) {
      Serial.print("knitting lines negative : ");
      int nbLines = input.substring(6).toInt();
      Serial.println(nbLines);
      knit(nbLines, 1);

    } else {
      Serial.println("Invalid command. Use 's1 x', 's2 x', or 'n x'.");
    }
  }
}

void knit(int lines, int startingDirection){
  int neg = startingDirection;

  for(int i = 0; i < lines; i++){
    moveServoDirection(neg);
    delay(500);
    knitOneLine(neg);
    neg = neg == 0 ? 1 : 0;
  }    
}

void knitOneLine(int neg){
  int bit1 = maxSteps >> 8;
  int bit2 = maxSteps & 255;
  Wire.beginTransmission(8);
  Wire.write(neg); 
  Wire.write(bit1);
  Wire.write(bit2);
  Wire.endTransmission();
}

void moveServoDirection(int neg){
  if(neg == 0){
    servo1.write(servo1Right);     
    servo2.write(servo2Right);  
    servoBig.write(bigServoRight);   
  } else {
    servo1.write(servo1Left);     
    servo2.write(servo2Left); 
    servoBig.write(bigServoLeft);    
  }
}