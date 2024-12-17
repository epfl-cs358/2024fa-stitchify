#include <Wire.h>
#include <Servo.h>

#define servoPin1 9 
#define servoPin2 10 
#define servoBigPin 11
#define COMM_RECEIVE_PIN 12

int angle1 = 0, angle2 = 0, angle = 0;
int nemaAngle = 0;   

int servo1lefttake = 130;
int servo2lefttake = 180;
int servo1righttake = 0;
int servo2righttake = 50;

int servo1leftskip = 130;
int servo2leftskip = 50;
int servo1rightskip = 130;
int servo2rightskip = 50;

int servoleft = 70;
int servoright = 1;

int firstNeedleDistanceLeft = 270;
int firstNeedleDistanceRight = 250;

int carriageSteps = 2500;
int needleSteps = 42;

int delayBigServo = 1000;
int delaySmallServo = 500;

Servo servo1;     
Servo servo2;
Servo servoBig;

void setup() {
  pinMode(servoPin1, OUTPUT);  
  pinMode(servoPin2, OUTPUT);  

  pinMode(COMM_RECEIVE_PIN, INPUT);

  Serial.begin(9600);           
  Wire.begin();              

  servo1.attach(servoPin1); 
  servo2.attach(servoPin2); 
  servoBig.attach(servoBigPin,900,2200);

  servo1.write(0);
  servo2.write(0); 

  Serial.println("Enter commands: s1 x, s2 x, or n x (e.g., 's1 90').");
}


void moveStep(String input)
{
  if (input.startsWith("l")) {
    servo1.write(servo1lefttake);     
    servo2.write(servo2lefttake);        
    Serial.print("Servos moved left");

  }else if (input.startsWith("r")) {
    servo1.write(servo1righttake);     
    servo2.write(servo2righttake);        
    Serial.print("Servos moved right");

  }else if (input.startsWith("s ")) {
    angle = input.substring(2).toInt();
    servoBig.write(angle);     
    Serial.print("Big servo moved");

  }else if (input.startsWith("s1 ")) {
    angle = input.substring(3).toInt();
    if (angle > 180) angle = 180;   
    servo1.write(angle);         
    Serial.print("Servo1 moved to: ");
    Serial.println(angle);

  } else if (input.startsWith("s2 ")) {

    angle = input.substring(3).toInt();
    if (angle > 180) angle = 180;
    servo2.write(angle); 
    Serial.print("Servo2 moved to: ");
    Serial.println(angle);

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

    while (digitalRead(COMM_RECEIVE_PIN) != HIGH) {
      Serial.println('x');
    }
    // Signal received from slave, hence everythig okey and we can continue next row
    Serial.println("Signal received from slave");

  } 
  else {
    Serial.println("Invalid command. Use 's1 x', 's2 x', or 'n x'.");
  }
}

void goFirstRight()
{
  moveStep("r");
  moveStep("s "+String(servoleft));
  delay(delayBigServo);
  moveStep("n "+String(firstNeedleDistanceRight));
  delay(5000); //not needed if security measures used
  moveStep("s "+String(servoright));
  delay(delayBigServo);
}

void goFirstLeft()
{
  moveStep("l");
  moveStep("s "+String(servoright));
  delay(delayBigServo);
  moveStep("n -"+String(firstNeedleDistanceLeft));
  delay(5000); //not needed if security measures used
  moveStep("s "+String(servoleft));
  delay(delayBigServo);
}

void moveRow(String input)
{
  Serial.println(input);
  if (input.startsWith("kr")) {
    goFirstRight();
    moveStep("n "+String(carriageSteps));
    delay(5000); //TODO: not needed if security measures used
  }
  else if(input.startsWith("kl")) {
    goFirstLeft();
    moveStep("n -"+String(carriageSteps));
    delay(5000); //TODO: not needed if security measures used
  }
  else if(input.startsWith("fl")) {
    goFirstLeft();
  }
  else if(input.startsWith("fr")) {
    goFirstRight();
  }
  else if(input.startsWith("ar")) {
    moveStep("n "+String(firstNeedleDistanceLeft));
  }
  else if(input.startsWith("al")) {
    moveStep("n "+String(firstNeedleDistanceRight));
  }
  else if(input.startsWith("lt ")) {
    int nNeedles = input.substring(4).toInt();
    servo1.write(servo1lefttake);     
    servo2.write(servo2lefttake);        
    delay(delaySmallServo);
    moveStep("n "+String(needleSteps * nNeedles));
    delay(5000); //TODO: not needed if security measures used
  }
  else if(input.startsWith("ls ")) {
    int nNeedles = input.substring(4).toInt();
    servo1.write(servo1leftskip);     
    servo2.write(servo2leftskip);    
    delay(delaySmallServo);
    moveStep("n "+ String(needleSteps * nNeedles));
    delay(5000); //TODO: not needed if security measures used    

  }
  else if(input.startsWith("rt ")) {
    int nNeedles = input.substring(4).toInt();
    servo1.write(servo1righttake);     
    servo2.write(servo2righttake);     
    delay(delaySmallServo);
    moveStep("n "+String(needleSteps * nNeedles));
    delay(5000); //TODO: not needed if security measures used 

  }
  else if(input.startsWith("rs ")) {
    int nNeedles = input.substring(4).toInt();
    servo1.write(servo1rightskip);     
    servo2.write(servo1rightskip);   
    delay(delaySmallServo);
    moveStep("n "+String(needleSteps * nNeedles));
    delay(5000); //TODO: not needed if security measures used

  }
  else
  {
    moveStep(input);
  }
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim(); 
    if (input.startsWith("knit ")) {
      int numberRows = input.substring(5).toInt();
      for(int i=0; i<numberRows; i++)
      {
        moveRow("kl");
        moveRow("kr");
      }
    }
    else
    {
      moveRow(input);
    }
  }
}