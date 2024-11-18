#define stepPinX 2
#define dirPinX  5

#define stepPinY 3
#define dirPinY  6

#define stepPinZ 4
#define dirPinZ  7

#define enablePin 8

void setup() {
  pinMode(stepPinX, OUTPUT);
  pinMode(dirPinX, OUTPUT);

  pinMode(stepPinY, OUTPUT);
  pinMode(dirPinY, OUTPUT);

  pinMode(stepPinZ, OUTPUT);
  pinMode(dirPinZ, OUTPUT);

  pinMode(enablePin, OUTPUT);

  digitalWrite(enablePin, LOW);

  digitalWrite(dirPinX, HIGH);
  digitalWrite(dirPinY, HIGH);
  digitalWrite(dirPinZ, HIGH);
}

void loop() {
  for (int i = 0; i < 200; i++) {
    digitalWrite(stepPinX, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPinX, LOW);
    delayMicroseconds(500);
  }

  delay(1000);

  for (int i = 0; i < 200; i++) {
    digitalWrite(stepPinY, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPinY, LOW);
    delayMicroseconds(500);
  }

  delay(1000);

  for (int i = 0; i < 200; i++) {
    digitalWrite(stepPinZ, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPinZ, LOW);
    delayMicroseconds(500);
  }

  delay(1000);

  digitalWrite(dirPinX, LOW);
  digitalWrite(dirPinY, LOW);
  digitalWrite(dirPinZ, LOW);

  for (int i = 0; i < 200; i++) {
    digitalWrite(stepPinX, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPinX, LOW);
    delayMicroseconds(500);
  }

  delay(1000);

  for (int i = 0; i < 200; i++) {
    digitalWrite(stepPinY, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPinY, LOW);
    delayMicroseconds(500);
  }

  delay(1000);

  for (int i = 0; i < 200; i++) {
    digitalWrite(stepPinZ, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPinZ, LOW);
    delayMicroseconds(500);
  }

  delay(1000);
}