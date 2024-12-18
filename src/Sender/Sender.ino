#define stepPinX 2      
#define dirPinX  5      
#define enablePin 8     
char s1[5] = "45\n"; 
char s2[5] = "0\n";
void setup() {
  pinMode(stepPinX, OUTPUT);   
  pinMode(dirPinX, OUTPUT);   
  pinMode(enablePin, OUTPUT); 
  digitalWrite(enablePin, LOW); 
  digitalWrite(dirPinX, HIGH);  
  Serial.begin(9600);
}
void loop() {
  for (int i = 0; i < 200; i++) {
    digitalWrite(stepPinX, HIGH);
    delayMicroseconds(500); 
    digitalWrite(stepPinX, LOW);
    delayMicroseconds(500);
  }
  Serial.println(s1); 
  delay(1000); 
  digitalWrite(dirPinX, LOW);   
  for (int i = 0; i < 200; i++) {
    digitalWrite(stepPinX, HIGH);
    delayMicroseconds(500);  
    digitalWrite(stepPinX, LOW);
    delayMicroseconds(500);
  }
  Serial.println(s2); 
  delay(1000);
}
