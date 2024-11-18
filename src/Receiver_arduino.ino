#include <Servo.h>

Servo myServo;
char mystr[10];
int angle = 0;

void setup() {
  Serial.begin(9600);
  myServo.attach(9);
  myServo.write(0);
}

void loop() {
  memset(mystr, 0, sizeof(mystr));
  Serial.readBytesUntil('\n', mystr, sizeof(mystr) - 1);
  Serial.println(mystr);

  angle = atoi(mystr);

  if (angle >= 0 && angle <= 180) {
    myServo.write(angle);
    Serial.print("Servo moved to ");
    Serial.print(angle);
    Serial.println(" degrees");
  } else {
    Serial.println("Invalid angle received. Please send a value between 0 and 180.");
  }
  
  delay(1000);
}
