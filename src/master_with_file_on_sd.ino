#include <Wire.h>
#include <Servo.h>
#include <SD.h>

#define servoPin1 9 
#define servoPin2 10 
#define chipSelect 4 

int angle1 = 0;     
int angle2 = 0;
int nemaAngle = 0;  

Servo servo1; 
Servo servo2;

File commandFile;

void setup() {
  pinMode(servoPin1, OUTPUT);
  pinMode(servoPin2, OUTPUT);

  Serial.begin(9600);           
  Wire.begin();

  servo1.attach(servoPin1); 
  servo2.attach(servoPin2);

  servo1.write(0); 
  servo2.write(0); 


  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    return;
  }

  commandFile = SD.open("commands.txt");
  if (!commandFile) {
    Serial.println("Failed to open commands.txt!");
    return;
  }
  Serial.println("commands.txt opened successfully.");
}

void loop() {
  Serial.println("1");
  if (commandFile.available()) {
    String input = commandFile.readStringUntil('\n'); 
    input.trim();
    Serial.println(input);

    if (input.startsWith("s1 ")) {
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
      Serial.print("Sending to NEMA motor: ");
      Serial.println(nemaAngle);

      Wire.beginTransmission(8); 
      Wire.write(nemaAngle);
      Wire.endTransmission();

    } else {
      Serial.println("Invalid command. Use 's1 x', 's2 x', or 'n x'.");
    }
    delay(1000);
  } else {
    Serial.println("End of commands file reached.");
    commandFile.close();
    while (1);
  }
}
