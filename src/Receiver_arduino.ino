#define stepPinX 2
#define dirPinX  5
#define enablePin 8

char mystr[10];
int angle = 0;
int steps = 0;

void setup() {
  pinMode(stepPinX, OUTPUT);   
  pinMode(dirPinX, OUTPUT);   
  pinMode(enablePin, OUTPUT); 

  digitalWrite(enablePin, LOW); 
  digitalWrite(dirPinX, HIGH);  

  Serial.begin(9600);
}

void loop() {
  memset(mystr, 0, sizeof(mystr));   
  Serial.readBytesUntil('\n', mystr, sizeof(mystr) - 1); 
  angle = atoi(mystr); 

  digitalWrite(dirPinX, LOW); 
  for (int i = 0; i < steps; i++) 
  {
    digitalWrite(stepPinX, HIGH);
    delayMicroseconds(500); 
    digitalWrite(stepPinX, LOW);
    delayMicroseconds(500);
  }
  
  Serial.print(steps);
  delay(1000);
}
