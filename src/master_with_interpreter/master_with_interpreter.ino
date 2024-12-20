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
 * - knits x  : Knit x double rows with confirmation after each row
 * - knitp x  : Knit x double rows of pattern with confirmation after each row
 */
#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal.h>


#define servo1_pin 9 
#define servo2_pin 10 
#define servo_big_pin 11
#define CONF_RECEIVE_PIN 8
#define COMM_RECEIVE_PIN 7

#define MAX_BUFFER_SIZE 100
#define MAX_COMMAND_LENGTH 10

LiquidCrystal lcd(13, 12, 5, 4, 3, 2);


//Values to be valibrated
const int servo1_left_take = 170;   // Position for taking left needles with servo 1
const int servo2_left_take = 140;   // Position for taking left needles with servo 2
const int servo1_right_take = 60;    // Position for taking right needles with servo 1
const int servo2_right_take = 10;   // Position for taking right needles with servo 2

const int servo1_left_skip = 170;   // Position for skipping left needles with servo 1
const int servo2_left_skip = 10;    // Position for skipping left needles with servo 2
const int servo1_right_skip = 170;  // Position for skipping right needles with servo 1
const int servo2_right_skip = 10;   // Position for skipping right needles with servo 2

const int servo_big_left = 70;      // Position for big servo when moving to the left
const int servo_big_right = 1;      // Position for big servo when moving to the right

const int first_needle_distance_left = 250;  // Distance to the first needle on the left (measured from switch, after bump)
const int first_needle_distance_right = 250; // Distance to the first needle on the right (measured from switch,  after bump)

const int carriage_steps = 2500;   // Number of steps required to move the entire carriage
const int needle_steps = 40;       // Number of steps needed per needle 

const int delay_big_servo = 1000;  // Delay for big servo movement (longer movement)
const int delay_small_servo = 500; // Delay for small servo movement (shorter movement)
const int delay_sending = 500;      // Delay for sending commands to NEMA motor (for communication pin switch)


//Declaration of other components
Servo servo1;     
Servo servo2;
Servo servoBig;


//Declaration of the buffer
struct CommandBuffer {
    char commands[MAX_BUFFER_SIZE][MAX_COMMAND_LENGTH];
    int head;
    int tail;
    int count;
} cmdBuffer;

/**
 * Initializes the command buffer to manage incoming commands for processing.
 * Resets the buffer head, tail, and count values.
 */
void initCommandBuffer() {
    cmdBuffer.head = 0;
    cmdBuffer.tail = 0;
    cmdBuffer.count = 0;
}

/**
 * Checks if the command buffer is full.
 * @return true if the buffer is full, false otherwise.
 */
bool isBufferFull() {
    return cmdBuffer.count >= MAX_BUFFER_SIZE;
}

/**
 * Checks if the command buffer is empty.
 * @return true if the buffer is empty, false otherwise.
 */
bool isBufferEmpty() {
    return cmdBuffer.count == 0;
}

/**
 * Adds a command string to the command buffer if there's space.
 * @param command The command string to add.
 * @return true if the command was added successfully, false otherwise.
 */
bool addToBuffer(String command) {
    if (isBufferFull() || command.length() >= MAX_COMMAND_LENGTH) {
        Serial.println("Buffer full or command too long");
        return false;
    }
    
    command.toCharArray(cmdBuffer.commands[cmdBuffer.tail], MAX_COMMAND_LENGTH);
    cmdBuffer.tail = (cmdBuffer.tail + 1) % MAX_BUFFER_SIZE;
    cmdBuffer.count++;
    
    Serial.print("Command added to buffer: ");
    Serial.println(command);
    Serial.print("Buffer count: ");
    Serial.println(cmdBuffer.count);
    
    return true;
}

/**
 * Displays a message on the LCD.
 * This function clears the existing display and prints new text.
 * @param line1 The first line of text to display. This is mandatory.
 * @param line2 The second line of text to display. This is optional and defaults to an empty string if not provided.
 */
void displayMessage(String line1, String line2 = "") {
  lcd.clear();                   
  lcd.setCursor(0, 0);          
  lcd.print(line1);               
  lcd.setCursor(0, 1);            
  lcd.print(line2);               
}

/**
 * Sets up hardware pins, initializes servos, and prepares the system.
 * Called once during the microcontroller's boot process.
 */
void setup() {
    pinMode(servo1_pin, OUTPUT);  
    pinMode(servo2_pin, OUTPUT);  
    pinMode(COMM_RECEIVE_PIN, INPUT);
    
    Serial.begin(9600);           
    Wire.begin();              
    
    servo1.attach(servo1_pin); 
    servo2.attach(servo2_pin); 
    servoBig.attach(servo_big_pin, 900, 2200);
    
    servo1.write(0);
    servo2.write(0); 
    
    initCommandBuffer();
    
    Serial.println("Knitting machine controller ready.");

    lcd.begin(16, 2);
    displayMessage("Welcome to", "Stitchify");
    delay(2000);
    
}

/**
 * Moves components based on the given input command string.
 * Handles movement of servos and NEMA motors.
 * Checking serial while moving NEMA.
 * @param input The command string containing the movement instructions.
 */
void moveStep(String input)
{
  if (input.startsWith("l")) {
    servo1.write(servo1_left_take);     
    servo2.write(servo2_left_take);        
    Serial.print("Servos moved left");
    delay(delay_small_servo);

  }else if (input.startsWith("r")) {
    servo1.write(servo1_right_take);     
    servo2.write(servo2_right_take);        
    Serial.print("Servos moved right");
    delay(delay_small_servo);

  }else if (input.startsWith("s ")) {
    int angle = input.substring(2).toInt();
    servoBig.write(angle);     
    Serial.print("Big servo moved");
    delay(delay_big_servo);

  }else if (input.startsWith("s1 ")) {
    int angle = input.substring(3).toInt();
    if (angle > 180) angle = 180;   
    servo1.write(angle);         
    Serial.print("Servo1 moved to: ");
    Serial.println(angle);
    delay(delay_small_servo);

  } else if (input.startsWith("s2 ")) {

    int angle = input.substring(3).toInt();
    if (angle > 180) angle = 180;
    servo2.write(angle); 
    Serial.print("Servo2 moved to: ");
    Serial.println(angle);
    delay(delay_small_servo);

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
      checkSerial();
    }
    Serial.println("Signal received from slave");

  } 
  else {

    Serial.println("Invalid command. Use 's1 x', 's2 x', or 'n x'.");
  }
}

/**
 * Moves the knitting machine to the first needle on the right side (so that it's up).
 */
void goFirstRight()
{
  moveStep("r");
  moveStep("s "+String(servo_big_left));
  moveStep("n "+String(first_needle_distance_right));
  moveStep("s "+String(servo_big_right));
}

/**
 * Moves the knitting machine to the first needle on the left side (so that it's up).
 */
void goFirstLeft()
{
  moveStep("l");
  moveStep("s "+String(servo_big_right));
  moveStep("n -"+String(first_needle_distance_left));
  moveStep("s "+String(servo_big_left));
}


/**
 * Executes a row movement command based on the input.
 * Handles knitting rows and needle adjustments.
 * @param input The row command string.
 */
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
  else if (input.startsWith("krp")) {
    goFirstRight();
    moveStep("n "+String(carriage_steps));
  }
  else if(input.startsWith("klp")) {
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
    moveStep("n -"+String(first_needle_distance_right));
  }
  else if(input.startsWith("lt ")) {
    int n_needles = input.substring(4).toInt();
    moveStep("s1 "+String(servo1_left_take));     
    moveStep("s2 "+String(servo2_left_take));   
    moveStep("n -"+String(needle_steps * n_needles));

  }
  else if(input.startsWith("ls ")) {
    int n_needles = input.substring(4).toInt();
    moveStep("s1 "+String(servo1_left_skip));     
    moveStep("s2 "+String(servo2_left_skip));   
    moveStep("n -"+ String(needle_steps * n_needles));

  }
  else if(input.startsWith("rt ")) {
    int n_needles = input.substring(4).toInt();
    moveStep("s1 "+String(servo1_right_take));     
    moveStep("s2 "+String(servo2_right_take));   
    moveStep("n "+String(needle_steps * n_needles));

  }
  else if(input.startsWith("rs ")) {
    int n_needles = input.substring(4).toInt();
    moveStep("s1 "+String(servo1_right_skip));     
    moveStep("s2 "+String(servo2_right_skip));   
    moveStep("n "+String(needle_steps * n_needles));
  }
  else
  {
    moveStep(input);
  }
}

/**
 * Waits for confirmation from the CONF_RECEIVE_PIN before proceeding.
 * Used during specific knitting operations requiring acknowledgment.
 * Checking serial while waiting.
 * @return true once confirmation is received.
 */
bool waitForRowConfirmation() {
  displayMessage("Is everything", "okay?");
  delay(1000);
  while(CONF_RECEIVE_PIN == LOW) {}
  checkSerial();
  lcd.clear();  
  lcd.print("Row confirmed");  
  delay(1000);
}

/**
 * Processes knitting commands, including multiple rows and patterns.
 * @param input The knitting command string.
 */
void knit(String input)
{
  if (input.startsWith("knit ")) {
    int number_rows = input.substring(5).toInt();
    displayMessage("Ready to knit:", String(number_rows) + " rows");
    delay(2000);
    for(int i=0; i<number_rows; i++)
    {
      if(i%2==0) moveRow("kl");
      if(i%2==1) moveRow("kr");
      displayMessage("Knitted " + String(i + 1), "/" + String(number_rows) + " rows");
      delay(1000);

    }
    displayMessage("Knitting done!");

  }
  if (input.startsWith("knits ")) {
    int number_rows = input.substring(6).toInt();
    displayMessage("Ready to knit:", String(number_rows) + " rows");
    delay(2000);
    for(int i=0; i<number_rows; i++)
    {
      if(i%2==0) moveRow("klp");
      if(i%2==1) moveRow("krp");
      waitForRowConfirmation();
      displayMessage("Knitted " + String(i + 1), "/" + String(number_rows) + " rows");
      delay(1000);
    }
    displayMessage("Knitting done!");

  }
  if (input.startsWith("knitp ")) {
    int number_rows = input.substring(6).toInt();
    for(int i=0; i<number_rows; i++)
    {
      if(i%2==0) moveRow("klp");
      if(i%2==1) moveRow("krp");
      waitForRowConfirmation();
      
    }
  }
  else
  {
    moveRow(input);
  }
  displayMessage("Knitting done!");

}

/**
 * Retrieves the next command from the buffer.
 * @return The next command string, or an empty string if the buffer is empty.
 */
String getNextCommand() {
  if (isBufferEmpty()) {
      return "";
  }
  String command = String(cmdBuffer.commands[cmdBuffer.head]);
  cmdBuffer.head = (cmdBuffer.head + 1) % MAX_BUFFER_SIZE;
  cmdBuffer.count--;
  return command;
}


/**
 * Processes buffered commands, executing them in sequence.
 */
void processBufferedCommands() {
  if (!isBufferEmpty()) {
    String command = getNextCommand();
    if (command.length() > 0) {
      knit(command);
    }
  }
}


/**
 * Reads serial input for incoming commands and adds them to the buffer.
 * Supports parsing multiple commands separated by semicolons.
 */
void checkSerial()
{
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    int start_index = 0;
    int semicolon_index;
    do{
      semicolon_index = input.indexOf(';', start_index);
      String command;
      if(semicolon_index == -1) 
      {
        command = input.substring(start_index);
      } 
      else 
      {
        command = input.substring(start_index, semicolon_index);
        start_index = semicolon_index + 1;
      }
      command.trim();
      if(command.length() > 0) 
      {
        addToBuffer(command);
      }
            
    }while(semicolon_index != -1);
  }
}

/**
 * Main loop function, repeatedly called during the program's execution.
 * Handles serial input and processes buffered commands.
 */
void loop() {
  checkSerial();
  processBufferedCommands();
}

