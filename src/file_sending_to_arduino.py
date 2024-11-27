import serial
import time

arduino_port = "/dev/cu.usbserial-10" #depends on computer
baud_rate = 9600
commands_file = "commands.txt"

try:
    ser = serial.Serial(arduino_port, baud_rate, timeout=1)
    time.sleep(2)
    print(f"Connected to Arduino on {arduino_port}")
except Exception as e:
    print(f"Error connecting to Arduino: {e}")
    exit()
response = ser.readline().decode().strip()
try:
    with open(commands_file, "r") as file:
        for line in file:
            command = line.strip()
            if command:
                print(f"Sending: {command}")
                ser.write((command + "\n").encode())
                time.sleep(1)
                response = ser.readline().decode().strip()
                if response:
                    print(f"Arduino response: {response}")
except FileNotFoundError:
    print(f"File not found: {commands_file}")
except Exception as e:
    print(f"Error: {e}")
finally:
    ser.close()
    print("Connection closed.")
