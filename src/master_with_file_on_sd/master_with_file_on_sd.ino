#include <Wire.h>
#include <Servo.h>
#include <SD.h>

#define servo_pin_1 9 
#define servo_pin_2 10 
#define chip_select 4 

int angle_1 = 0;     
int angle_2 = 0;
int nema_angle = 0;  

Servo servo_1; 
Servo servo_2;

File command_file;

void setup() {
  pinMode(servo_pin_1, OUTPUT);
  pinMode(servo_pin_2, OUTPUT);

  Serial.begin(9600);           
  Wire.begin();

  servo_1.attach(servo_pin_1); 
  servo_2.attach(servo_pin_2);

  servo_1.write(0); 
  servo_2.write(0); 


  if (!SD.begin(chip_select)) {
    Serial.println("SD card initialization failed!");
    return;
  }

  command_file = SD.open("commands.txt");
  if (!command_file) {
    Serial.println("Failed to open commands.txt!");
    return;
  }
  Serial.println("commands.txt opened successfully.");
}

void loop() {
  Serial.println("1");
  if (command_file.available()) {
    String input = command_file.readStringUntil('\n'); 
    input.trim();
    Serial.println(input);

    if (input.startsWith("s1 ")) {
      angle_1 = input.substring(3).toInt();
      if (angle_1 > 180) angle_1 = 180;
      servo_1.write(angle_1);
      Serial.print("Servo1 moved to: ");
      Serial.println(angle_1);

    } else if (input.startsWith("s2 ")) {
      nema_angle = input.substring(2).toInt();
      int neg = 0;
      if (nema_angle < 0) 
      {
        nema_angle = -nema_angle;
        neg = 1;
      }
      Serial.print("Sending to NEMA motor: ");
      Serial.println(neg);
      Serial.println(nema_angle);

      Wire.beginTransmission(8);
      Wire.write(neg); 
      Wire.write(nema_angle); 
      Wire.endTransmission();
      
    } else {
      Serial.println("Invalid command. Use 's1 x', 's2 x', or 'n x'.");
    }
    delay(1000);
  } else {
    Serial.println("End of commands file reached.");
    command_file.close();
    while (1);
  }
}
