const int SwitchPin = 11;

void setup() {
  Serial.begin(9600);

  pinMode(SwitchPin, INPUT_PULLUP);
  
  Serial.println("Z- switch test started. ");
}

void loop() {
  int switchState = digitalRead(SwitchPin);
  
  if (switchState == LOW) {
    Serial.println("Switch is NOT pressed!");
  } else {
    Serial.println("Switch is pressed.");
  }

  delay(500);
}
