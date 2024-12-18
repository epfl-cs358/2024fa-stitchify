/*
 * Knitting Machine Control Code
 * 
 * Supported Commands:
 * - l        : Move small servos to the left
 * - r        : Move small servos to the right
 * - s x      : Move big servo to position x
 * - s1 x     : Move small servo 1 to position x
 * - s2 x     : Move small servo 2 to position x
 * - n x      : Move NEMA motors by x steps
 * - kr       : Knit a full row to the right
 * - kl       : Knit a full row to the left
 * - fl       : Go to the first needle on the left from the switch point
 * - fr       : Go to the first needle on the right from the switch point
 * - al       : Move after the first needle left (continue from the last step to the end)
 * - ar       : Move after the first needle right (continue from the last step to the end)
 * - lt x     : Left take x needles (raise needles up)
 * - rt x     : Right take x needles (raise needles up)
 * - ls x     : Left skip x needles (lower needles down)
 * - rs x     : Right skip x needles (lower needles down)
 * - knit x   : Knit x double rows (right and left equals one row)
 *
 */
#include <Wire.h>
#include <Servo.h>

#define servo1_pin 9 
#define servo2_pin 10 
#define servo_big_pin 11
#define COMM_RECEIVE_PIN 7


//Values to be valibrated
int servo1_left_take = 130;
int servo2_left_take = 180;
int servo1_right_take = 0;
int servo2_right_take = 50;

int servo1_left_skip = 130;
int servo2_left_skip = 50;
int servo1_right_skip = 130;
int servo2_right_skip = 50;

int servo_big_left = 70;
int servo_big_right = 1;

int first_needle_distance_left = 270;
int first_needle_distance_right = 250;

int carriage_steps = 2500;
int needle_steps = 42;

int delay_big_servo = 1000;
int delay_small_servo = 500;

int delay_sending = 500;


//Declaration of other components
Servo servo1;     
Servo servo2;
Servo servoBig;

void setup() {
  pinMode(servo1_pin, OUTPUT);  
  pinMode(servo2_pin, OUTPUT);  

  pinMode(COMM_RECEIVE_PIN, INPUT);

  Serial.begin(9600);           
  Wire.begin();              

  servo1.attach(servo1_pin); 
  servo2.attach(servo2_pin); 
  servoBig.attach(servo_big_pin,900,2200);

  servo1.write(0);
  servo2.write(0); 

  Serial.println("Enter commands: s1 x, s2 x, or n x (e.g., 's1 90').");
}


void moveStep(String input)
{
  if (input.startsWith("l")) {
    servo1.write(servo1_left_take);     
    servo2.write(servo2_left_take);        
    Serial.print("Servos moved left");

  }else if (input.startsWith("r")) {
    servo1.write(servo1_right_take);     
    servo2.write(servo2_right_take);        
    Serial.print("Servos moved right");

  }else if (input.startsWith("s ")) {
    int angle = input.substring(2).toInt();
    servoBig.write(angle);     
    Serial.print("Big servo moved");

  }else if (input.startsWith("s1 ")) {
    int angle = input.substring(3).toInt();
    if (angle > 180) angle = 180;   
    servo1.write(angle);         
    Serial.print("Servo1 moved to: ");
    Serial.println(angle);

  } else if (input.startsWith("s2 ")) {

    int angle = input.substring(3).toInt();
    if (angle > 180) angle = 180;
    servo2.write(angle); 
    Serial.print("Servo2 moved to: ");
    Serial.println(angle);

  } else if (input.startsWith("n ")) {
    int nema_angle = input.substring(2).toInt();
    int neg = 0;
    if (nema_angle < 0) 
    {
      nema_angle = -nema_angle;
      neg = 1;
    }
    int bit_high = nema_angle >> 8;
    int bit_low = nema_angle & 255;


    Serial.print("Sending to NEMA motor: ");
    Serial.println(neg);
    Serial.println((bit_high << 8) + bit_low);

    Wire.beginTransmission(8);
    Wire.write(neg); 
    Wire.write(bit_high); 
    Wire.write(bit_low);
    Wire.endTransmission();


    delay(delay_sending);
    while (digitalRead(COMM_RECEIVE_PIN) == LOW) {
      Serial.println("x");
    }
    Serial.println("Signal received from slave");

  } 
  else {

    Serial.println("Invalid command. Use 's1 x', 's2 x', or 'n x'.");
  }
}

void goFirstRight()
{
  moveStep("r");
  moveStep("s "+String(servo_big_left));
  delay(delay_big_servo);
  moveStep("n "+String(first_needle_distance_right));
  moveStep("s "+String(servo_big_right));
  delay(delay_big_servo);
}

void goFirstLeft()
{
  moveStep("l");
  moveStep("s "+String(servo_big_right));
  delay(delay_big_servo);
  moveStep("n -"+String(first_needle_distance_left));
  moveStep("s "+String(servo_big_left));
  delay(delay_big_servo);
}

void moveRow(String input)
{
  Serial.println(input);
  if (input.startsWith("kr")) {
    goFirstRight();
    moveStep("n "+String(carriage_steps));
  }
  else if(input.startsWith("kl")) {
    goFirstLeft();
    moveStep("n -"+String(carriage_steps));
  }
  else if(input.startsWith("fl")) {
    goFirstLeft();
  }
  else if(input.startsWith("fr")) {
    goFirstRight();
  }

  else if(input.startsWith("ar")) {
    moveStep("n "+String(first_needle_distance_left));
  }
  else if(input.startsWith("al")) {
    moveStep("n "+String(first_needle_distance_right));
  }
  else if(input.startsWith("lt ")) {
    int n_needles = input.substring(4).toInt();
    servo1.write(servo1_left_take);     
    servo2.write(servo2_left_take);        
    delay(delay_small_servo);
    moveStep("n "+String(needle_steps * n_needles));

  }
  else if(input.startsWith("ls ")) {
    int n_needles = input.substring(4).toInt();
    servo1.write(servo1_left_skip);     
    servo2.write(servo2_left_skip);    
    delay(delay_small_servo);
    moveStep("n "+ String(needle_steps * n_needles));

  }
  else if(input.startsWith("rt ")) {
    int n_needles = input.substring(4).toInt();
    servo1.write(servo1_right_take);     
    servo2.write(servo2_right_take);     
    delay(delay_small_servo);
    moveStep("n "+String(needle_steps * n_needles));

  }
  else if(input.startsWith("rs ")) {
    int n_needles = input.substring(4).toInt();
    servo1.write(servo1_right_skip);     
    servo2.write(servo2_right_skip);   
    delay(delay_small_servo);
    moveStep("n "+String(needle_steps * n_needles));


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
      int number_rows = input.substring(5).toInt();
      for(int i=0; i<number_rows; i++)
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