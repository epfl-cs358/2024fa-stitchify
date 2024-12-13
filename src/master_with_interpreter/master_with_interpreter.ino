#include <Wire.h>
#include <Servo.h>

#define servoPin1 9 
#define servoPin2 10 
#define servoBigPin 11

int angle1 = 0, angle2 = 0, angle = 0;
int nemaAngle = 0;   

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


void moveStep(String input)
{
  if (input.startsWith("l")) {
    servo1.write(servo1left);     
    servo2.write(servo2left);        
    Serial.print("Servos moved left");

  }else if (input.startsWith("r")) {
    servo1.write(servo1right);     
    servo2.write(servo2right);        
    Serial.print("Servos moved right");

  }else if (input.startsWith("s ")) {
    angle = input.substring(2).toInt();
    if (angle > 180) angle = 180;   
    servoBig.write(angle);     
    Serial.print("Big servo moved");

  }else if (input.startsWith("s1 ")) {
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

void moveRow(String input)
{
  if (input.startsWith("kr")) {
    moveStep("r");
    delay(5000);
    moveStep("s 110");
    delay(5000);
    moveStep("n 250");
    delay(5000);
    moveStep("s 75");
    delay(5000);
    moveStep("n 2500");
    delay(5000);
  }
  else if (input.startsWith("kl")) {
    moveStep("l");
    delay(5000);
    moveStep("s 75");
    delay(5000);
    moveStep("n -250");
    delay(5000);
    moveStep("s 110");
    delay(5000);
    moveStep("n -2500");
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
        delay(5000);
        moveRow("kr");
        delay(5000);
      }
    }
    else
    {
      moveRow(input);
    }
  }
}

