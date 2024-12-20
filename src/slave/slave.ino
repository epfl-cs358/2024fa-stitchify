#include <Wire.h>

// Pin definitions
#define step_pin 2           // Step pin for motor driver
#define dir_pin  5           // Direction pin for motor driver
#define comm_send_pin 11     // Communication pin to signal master device

// Switch pins for detecting end positions
const int switch_pin_right = 12;
const int switch_pin_left = 13;

// Expected positions for calibration
const int expected_pos_left = 0;
const int expected_pos_right = 0;

// Variables to track motor state and movement
int current_pos = 0, target_steps = 0, steps_pos_neg = 0;

/**
 * @brief Initializes hardware, I2C communication, and prints initial switch states for debugging.
 */
void setup() 
{
  pinMode(step_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);

  pinMode(switch_pin_right, INPUT_PULLUP);
  pinMode(switch_pin_left, INPUT_PULLUP);

  pinMode(comm_send_pin, OUTPUT);
  digitalWrite(comm_send_pin, LOW);

  Wire.begin(8);
  Wire.onReceive(receive_data);

  Serial.begin(9600);
  Serial.println("Ready to receive step count.");

  int switch_state_right = digitalRead(switch_pin_right);
  int switch_state_left = digitalRead(switch_pin_left);
  Serial.println(switch_state_right);
  Serial.println(switch_state_left);
}

/**
 * @brief Main loop, currently unused.
 */
void loop() 
{
}

/**
 * @brief Sends a signal to the master device via the communication pin.
 */
void send_signal_to_master() {
  digitalWrite(comm_send_pin, HIGH);
}

/**
 * @brief Callback function to handle data received via I2C. Parses the step count and direction.
 * 
 * @param byte_count Number of bytes received via I2C.
 */
void receive_data(int byte_count) 
{
  digitalWrite(comm_send_pin, LOW);

  int neg = 0, steps = 0;

  neg = Wire.read();
  steps = Wire.read();
  steps = (steps << 8) + Wire.read();

  Serial.print("Received steps: ");
  Serial.println(steps);
  Serial.println(neg);

  target_steps = steps;
  move_motor(neg, target_steps);
}

/**
 * @brief Moves the motor slightly backward when switch activation.
 * 
 * @param neg Direction flag: 0 for forward, 1 for reverse.
 */
void back_up(int neg)
{
  if (neg == 0) 
  {
    digitalWrite(dir_pin, LOW); 
  } 
  else 
  {
    digitalWrite(dir_pin, HIGH); 
  }

  for (int j = 0; j < 45; j++)
  { 
    current_pos -= steps_pos_neg; 
    digitalWrite(step_pin, HIGH);
    delay(500);
    digitalWrite(step_pin, LOW);
    delay(500);
  }
}

/**
 * @brief Moves the motor a specified number of steps in the given direction while monitoring switch states.
 * 
 * @param neg Direction flag: 0 for forward, 1 for reverse.
 * @param steps Number of steps to move.
 */
void move_motor(int neg, int steps) {
  steps_pos_neg = neg == 1 ? -1 : 1;

  if (steps == 0) 
  {
    return;
  }
  else if (neg == 0) 
  {
    digitalWrite(dir_pin, HIGH); 
  } 
  else 
  {
    digitalWrite(dir_pin, LOW); 
  }

  bool switch_pressed_as_expected = 1;

  for (int i = 0; i < steps; i++) {
    int switch_state_right = digitalRead(switch_pin_right);
    int switch_state_left = digitalRead(switch_pin_left);

    if (switch_state_right == HIGH || switch_state_left == HIGH) {

      if (switch_state_right == HIGH && abs(current_pos - expected_pos_right) > 2) 
      {
        switch_pressed_as_expected = 0;
      }
      if (switch_state_left == HIGH && abs(current_pos != expected_pos_left) > 2) 
      {
        switch_pressed_as_expected = 0;
      }

      back_up(neg);
      break;
    }

    current_pos += steps_pos_neg;
    digitalWrite(step_pin, HIGH);
    delay(700);
    digitalWrite(step_pin, LOW);
    delay(700);
  }

  // Option to send a signal only if switches behaved as expected
  /*
  if (switch_pressed_as_expected) 
  {
    send_signal_to_master();
  }
  */

  // Notify the master device of movement completion
  send_signal_to_master();

  Serial.print("Motor moved by: ");
  Serial.println(steps);
  Serial.print("Motor at Pos: ");
  Serial.println(current_pos);
}
