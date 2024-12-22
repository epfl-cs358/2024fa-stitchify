<!-- ABOUT THE PROJECT -->

## Authors

Wiktoria Rozkosz, Bogdan Cîrje, Imane Raihane, Lorie Xu, Yasmine Hidri, Victor Zablocki


## About The Project
Fueled by curiosity, we worked to create a knitting machine from start to finish. The Knitting Robot is an Arduino-based automation system designed to knit simple fabric patterns such as scarves or scalable fabrics. The project aims to create a functional prototype capable of knitting patterns autonomously.

We based our work on the open source project OpenKnit, and spent a lot of time analysing and researching about how to go about in creating our machine. We obviously didn't have 5-6 years like OpenKnit did, so we had to simplify OpenKnit's design by a lot in order to fit the time frame of 10 weeks.

This is our project prototype in motion:
https://github.com/user-attachments/assets/023492ee-7dcc-4365-b6ac-0f5af49786ec


## Key Features
* **Web Interface**: A web app allows users to upload knitting patterns and customize their projects (e.g., scarves, beanies, or pullovers).
* **Real-Time Feedback**: An LCD screen on the knitting robot shows the progress and alerts users to any errors during operation.
* **Modular Design**: The system is designed to be modular, allowing future expansions and adaptations for more complex knitting patterns.
* **Educational Potential**: This project serves as a tool for teaching robotics, automation, and programming concepts.

## How It Works
The knitting robot operates by using a combination of stepper motors, actuators, and precision-controlled components to manipulate needles and yarn. The process is divided into the following key steps:
### 1. Pattern Upload:
* The user uploads a knitting pattern through the web interface. Typically, this pattern is a custom, text-based file that describes the sequence of knitting actions required for the design.
### 2. Conversion to Instructions:
* The uploaded pattern is then parsed and converted into a series of detailed instructions. These instructions control the robot’s movement and actions, dictating how needles should be raised or lowered.
* The system ensures precise execution of the pattern, coordinating between the needles, yarn feeder, and other actuators.
### 3. Knitting Process:
* Needle Movement: The carriage moves one needle at a time, enabling precise control over which needles are raised. Small servos embedded in the carriage allow the user to select individual needles for activation, ensuring each stitch is placed according to the pattern.
* Yarn Feeding: A large servo controls the yarn feeder, which performs a swiping motion to ensure accurate placement of the yarn on the needles. This motion enhances precision, especially at the endpoints, that require fine control over yarn tension and placement.
* Carriage Movement: The entire carriage is moved by a belt system powered by a NEMA stepper motor, ensuring smooth, coordinated motion across the entire width of the knitting surface.
### 4. Real-Time Feedback:
* LCD Screen: The system features an LCD screen that displays the progress of the knitting process, providing real-time feedback on the pattern's completion.
### 5. User Interaction:
* User Button: A dedicated button allows the user to pause or stop the machine after each row and confirm whether everything is functioning correctly. This button can be used to provide manual intervention if needed, ensuring the process runs smoothly.
### 6. Safety Features:
* Endpoint Switches: At the endpoints of the carriage, there are limit switches that prevent the system from overextending or damaging itself. These switches stop the carriage when it reaches the end of its travel, ensuring safe operation.
This combination of precise needle control, enhanced yarn feeding mechanisms, and real-time monitoring allows the knitting robot to produce high-quality knitting patterns with minimal manual intervention.


## Used Components

### Yarn Types:
- **Heavy Yarn**  
- **Normal Yarn**  
- **Synthetic Yarn** (Optional)

### Key Components:

1. **Needles**:  
   - 500 knitting needles required for the machine.

2. **Motors**:  
   - **8 or more motors**: NEMA 17 or Bipolar 17HS4401 stepper motors.
   - Motors for the following tasks:  
     - 1 motor for each yarn color.  
     - Motors for yarn feeders and moving the rails.
     - 2 motors for moving the beds on the Y-axis.

3. **Connectivity Modules**:  
   - **Wi-Fi Modules** or **Bluetooth Modules** for remote control or data transmission.

4. **Security Sensors**:  
   - **HC-SR04 Ultrasonic Distance Sensor** for clearance monitoring in the working area.

5. **Mechanical Parts**:  
   - **Belts**: 10 x 5-meter belts and their necessary attachments.
   - **Screws, metal beams, belts, and wiring** (provided in stock).

6. **Microcontroller ISP**:  
   - 10 units required, with or without camera integration.

7. **Voltage Converter**:  
   - **8-channel logic-level converter** - CHF 1 each.

8. **Measuring Components**:  
   - **MPU-6050 6 DOF Inertial Measurement Unit** for motion sensing of knitting needles - CHF 5.  
   - **CUI AMT-102-V Rotary Incremental Encoder** (Optional) for measuring needle motion - CHF 21.  
   - **Chihai CHF-GM37-550ABHL Gear Motor with Encoder** for controlling needles precisely - CHF 25.  
   - Additional motors, as needed - CHF 35.

9. **Display and Control**:  
   - **LCD Screen** to show progress and yarn levels.  
   - Yarn levels can be detected by weight sensors or through camera integration.  
   - **Power Supply**: Required for the overall system.  
   - **Control Button** for manual operation and adjustments.

10. **Other Components**:  
    - Additional motors and components for electrical setup.

---

### Additional Information

- **Design Files**:  
  All parts for 3D printing are available on our GitHub repository. Files for laser cutting (wood and plexiglass) are also included.

- **Materials Provided**:  
  Screws, metal beams, belts, and wiring are available for the assembly.

---

## Estimated Cost
The estimated cost of the project is around $500, which includes motors, stepper controllers, structural components, and electronics.
---
## Fusion Designs
Below is the very first overall design on Fusion that was created for this project :
![image](https://github.com/user-attachments/assets/2c703827-1e71-48b2-8ce7-e5d362c67b4f)
After numerous trials and errors, we finally settled on the final prototype Fusion design as seen below, which can also be found in the repository :

![image](https://github.com/user-attachments/assets/b0767661-cf87-4043-b2c7-fcce12c3b953)
![image](https://github.com/user-attachments/assets/86f9496e-424e-49e2-ae00-a32b2dc6d54e)

## Electrical Designs
Below is the initial design incorporating multiple stepper motors to improve torque, 1 ESP32-CAM for computer vision (which wasn't implemented in our project in the end), the Wemos D1 R32, 16-channel servo controller and the Arduino Uno :
![385799670-8f64526a-a05f-4db1-b084-6b4fe1a5de26](https://github.com/user-attachments/assets/1a5c0a5b-f347-4705-9548-388151839b8f)

Below is the current project's Fritzing sketch :
![image](https://github.com/user-attachments/assets/42b10e1d-9c68-4cb7-bc1e-d57afe74b177)


## Mechanical Designs
 * **Carriage** : ![image](https://github.com/user-attachments/assets/4fd38ac5-f687-4b51-980a-7e5eac8973f6)
 * **Aluminium structure** : ![image](https://github.com/user-attachments/assets/3f7c5bb9-529f-47a9-b5f7-1feda77b6e96)
 * **Flatbed** : ![image](https://github.com/user-attachments/assets/cd4c9e36-d478-4eea-930e-ee60951d1314)
 * **Yarn feeder, slider** : ![image](https://github.com/user-attachments/assets/5a23cc61-96bd-4c34-b919-b2d0b9764bfe)
 * **Stepper motor and belt pincher** : ![image](https://github.com/user-attachments/assets/d8f58b81-8279-4ec2-b44f-7d1e8c1482e6)
![image](https://github.com/user-attachments/assets/3d6c0d18-9bd0-4fb9-8170-d4e40dfb4f6c)

 * **Comb** : First tried a prototype using paper clips to see how it could work, then we made a comb with a hole to allow the addition of a weight.

## Code Implementation
The code implementation included the master-slave different data sharing channels and management, the controller for the stepper motor (slave) and servo motors (master), a WEMOS hosting a webapp that allow communication and the launch of customized patterns, and a file format that was designed to define pattern.

## Program Overview

### Command Parsing & Buffer Management
- Commands control various knitting machine components such as servos, motors, needle movements, and knitting actions.
- The program buffers incoming serial commands and processes them sequentially.

### Movement Control
- Supports servo and motor movement commands (`l`, `r`, `s x`, `n x`) for precise positioning.
- Knitting commands (`kr`, `kl`, `lt x`, `rt x`) manage the machine's movement during the knitting process.
- Supports knitting multiple rows with optional row confirmation (`knit x`, `knits x`, `knitp x`).
- Alternates between knitting rows to complete a full knit.

### LCD Feedback
- Provides real-time feedback via LCD, including status updates like "Knitting done".

### Serial Communication
- Listens for serial commands, handles multiple commands separated by semicolons, and processes them in sequence.
- Communicates with NEMA motors via I2C using the Wire library additional channel for acknowledgments from the slave.


### Synchronization & Delays
- Includes delays to synchronize servo and motor movements, ensuring proper sequencing of actions.


### Multi-command Support
- Supports processing multiple commands in a single input, separated by semicolons, for efficient execution.

### Wemos Integration
- **SPIFFS**: Utilizes the SPIFFS (Serial Peripheral Interface Flash File System) for managing storage and hosting files efficiently on the Wemos device.
- **HTTP Requests**: Sends HTTP requests from the Wemos device to a server, facilitating communication and pattern management.
- **Backend Communication**: Integrates with a Node.js backend to handle pattern requests, ensuring smooth interaction between the React frontend and the Wemos device.

### Wemos to Master Communication
- The **Wemos device** communicates directly with the **master controller**, sending commands and pattern data via **HTTP requests**. This enables the Wemos to relay instructions, such as motor movements or pattern changes, to the master, ensuring seamless control and coordination between the Wemos, the master, and the knitting machine.

### Web Application
- The web application is built using **React** and includes several pages:
  - **Home**

    <img width="500" alt="Screenshot 2024-12-20 at 10 12 34" src="https://github.com/user-attachments/assets/f98fc7d6-c8c0-48ae-8aa1-89e73558ca09" />
  - **Project Overview**
    <img width="500" alt="Screenshot 2024-12-20 at 10 16 41" src="https://github.com/user-attachments/assets/62eb2c9d-9873-4859-be34-c35cea9ae388" />
  - **Download Pattern**
    <img width="500" alt="Screenshot 2024-12-20 at 10 10 01" src="https://github.com/user-attachments/assets/285e6b2b-cef1-433c-9519-202bbea0db6b" />
  - **Create Pattern**
    <img width="500" alt="Screenshot 2024-12-20 at 10 07 44" src="https://github.com/user-attachments/assets/62037330-264f-4165-b16a-cd746a30fdf9" />
  - **Contact**
    <img width="500" alt="Screenshot 2024-12-20 at 10 08 14" src="https://github.com/user-attachments/assets/2e8d399f-57ce-430b-a658-7bbc4f56c193" />


- The React frontend communicates with the Wemos device to upload/download patterns and interact with the knitting machine.

- **Backend**: The lightweight server, built with Node.js, handles pattern requests from the React frontend to the Wemos device.
---

## File Breakdown

### `master_with_interpreter`
- Handles command parsing, communication with the slave, and overall program management.

### `slave`
- Receives I2C commands from the master and controls the NEMA motors based on those commands.

## Knitting Machine Control Code

### Supported Commands

#### # Movement Commands
- **`l`**: Move small servos to the left.
- **`r`**: Move small servos to the right.
- **`s x`**: Move the big servo to position `x` (range: 0–180).
- **`s1 x`**: Move small servo 1 to position `x` (range: 0–180).
- **`s2 x`**: Move small servo 2 to position `x` (range: 0–180).
- **`n x`**: Move NEMA motors by `x` steps (positive for forward, negative for reverse).

#### # Basic Knitting Commands
- **`krb`**: Knit a full row to the right (basic).
- **`klb`**: Knit a full row to the left (basic).

#### # Advanced Knitting Commands
- **`krs`**: Knit a full row to the right (switch, wait for confirmation).
- **`kls`**: Knit a full row to the left (switch, wait for confirmation).
- **`krp`**: Knit a full row to the right (pattern, wait for confirmation).
- **`klp`**: Knit a full row to the left (pattern, wait for confirmation).

#### # Needle Positioning Commands
- **`fl`**: Move to the first needle on the left from the switch point.
- **`fr`**: Move to the first needle on the right from the switch point.
- **`al`**: Move after the first needle on the left (continue from the last step to the end).
- **`ar`**: Move after the first needle on the right (continue from the last step to the end).

#### # Needle Management Commands
- **`lt x`**: Take `x` needles to the left (raise needles up).
- **`rt x`**: Take `x` needles to the right (raise needles up).
- **`ls x`**: Skip `x` needles to the left (lower needles down).
- **`rs x`**: Skip `x` needles to the right (lower needles down).

#### # Row Knitting Commands
- **`knit x`**: Knit `x` rows (a right and left movement together count as one row).
- **`knits x`**: Knit `x` rows (step-by-step, waiting for confirmation after each row).
- **`knitp x`**: Knit `x` rows (pause after each row, wait for confirmation to continue).

### Examples
1. Move small servo 1 to position 90:
   ```
   s1 90
   ```
2. Knit 5 rows with step-by-step confirmation:
   ```
   knits 5
   ```
3. Take 10 needles to the right:
   ```
   rt 10
   ```
4. Knit a full row to the left with pattern confirmation:
   ```
   klp
   ```

### Notes
- For all servo commands, ensure that the position values (`x`) are within the valid range of 0–180.
- For `knit`, `knits`, and `knitp` commands, the row count includes both right and left movements as a single row.
- Confirmations for step (`knits`) and pattern (`knitp`) commands must be manually provided before proceeding to the next step.


<!-- Issues -->
## Issues and Decisions Taken
Some of the issues we encountered during our prototyping and the decisions taken in regards to them are described below :

**1. Circular or flatbed design** : Originally, the circular design was preferred for its simplicity and the numerous available models on the market could've provided valuable insights and support for our project. However, we finally decided to work on the flatbed design, as it offered a more interesting and intricate mechanism and was overall more challenging.

**2. Number of needles, beds, lenghts etc** : There was a lot of discussion about how big the first prototype needed to be. The option of adding a second bed was pushed back to the second prototype and we sadly didn't have enough time to implement it in the end. We decided to use 23 needles, the ones given by the MIT teaching team, for the first prototype as the ones sponsored were too different to the project OpenKnit we were basing our machine on and would necessitate more work on the design part.

**3. Servos and stepper motors** : In the earliest design, there were 4 servos as we needed two carriages on both sides of the bed (double bed) and more stepperes to improve torque. In the end, we decided on reducing those numbers to two servos (not counting the one for the yarn feeder) and one stepper. Since the number of servos was lowered, the 16-channel servo controller wasn't needed anymore.

**4. Yarn feeder** : Originally, the yarn feeder could roll on the top bar, pushed by the carriage linked to the stepper motor on the side. This design was to allow multiple yarn feeders to coexist, thus introducing the ability to use multiple yarns for the same knit. It was however put aside as the tension created by the stepper on the side generated too much friction and the movement wasn't smooth enough. We decided to put the yarn feeder directly linked to the carriage along with the servo motor that could control its angles.

**5. Yarn feeder slider** : At the beginning, it was just supposed to slide on the top aluminium bar. We added two bearings to improve the smoothness of the movement and reduce the irregularities of the sliding. The bearings were on top and bottom of the bar at first, then moved to the two sides to fix the movement area and not allow any liberties to the slider. However, after the last changes made to the yarn feeder, the slider wasn't needed anymore (but can be an interesting upgrade in case of further work on the project).

**6. Carriage** : The carriage was, at first, designed to roll on a bar at the end of the bed. We however decided to change its support, as it generated too much movement and wasn't stable enough. The overall design was also reworked to be lighter both in weight and material, reducing the printing time. We decided to have metal rods directly fixed above the carriage with marble bearings inside to allow smooth movement at all times.

**7. Carriage rods support** : Initially, they were to be fixed on the bed using a 3D printed piece but the piece took up too much space and hindered the movement of the carriage. We finally decided on using MDF triangle panels fixed on the aluminium bars to hold up the rods, pulley and stepper.

**8. Stepper motor** : It was first designed to be fixed on the side bars, allowing movement of the carriage, which will push the first design of the yarn feeder. However, as it was far from where the heaviest build was (the carriage), it had difficulties to push everything and the belt would twist. We moved the stepper motor down, in between the two bars that supported the carriage, and fixed everything (metal rods, stepper and pulley) on a MDF side panel after careful computations on the carriage's position.

**9. Switches** : They were originally also supposed to be fixed on the side panels, but further consideration showed they would hinder the pulley and stepper motor supports. In the end, they are fixed on the bed.

**10. ESP32-CAM vs Wemos D1 R32 vs Arduino Uno** : We originally wanted to use the ESP32-CAM as it had built-in wifi connectivity and would allow wireless communication with the main Arduino Uno, in addition to its small size. However, we discovered that in the way we wanted to use it, there would only be a very small number of usable pins, which wasn't enough at all. We decided to look into the Wemos R32, which also had built-in wifi and looked a lot like an Arduino Uno. But there was a lot of pins adaptation issues as the Wemos uses a different pin naming pattern. In the end, we just decided to use an additional Arduino Uno for prototype 1 and managed to use the Wemos R1 D32 for connectivity with the webapp.

## Possible Future Enhancements

While the current prototype of the knitting machine is functional, there are several possible improvements and upgrades that could be explored in future iterations of the project:

- **Automated Yarn Feeder**: Future versions could include a more sophisticated yarn feeder capable of handling multiple yarns simultaneously, allowing for more complex and varied knitting patterns.

- **Second Bed**: The design for a second bed could be revisited to enable multi-layer knitting, enhancing the machine’s capabilities for more advanced knitting techniques.

- **Computer Vision Implementation**: The integration of an ESP32-CAM or similar vision system could enable advanced control features, such as automated pattern recognition or more precise needle positioning through real-time image processing.

- **Improved Web Interface**: The web application could be enhanced to make pattern creation more intuitive, offer real-time feedback during the knitting process, and improve communication with the machine. Features could include drag-and-drop pattern design, live status updates, and automatic pattern generation.

## Final Prototype 
![396272513-12e6db7e-80a0-43ea-b348-9f53fb4e29a5](https://github.com/user-attachments/assets/c27c6ae6-081a-45dd-acc4-1e2682aeb572)
![396790100-0d9a8779-574e-494d-af5e-7b810effc59a](https://github.com/user-attachments/assets/b5ff6b3d-0af7-4b92-abce-495b6ddac506)
![396790045-effc61c9-1916-40eb-b391-8df3ec1e6962](https://github.com/user-attachments/assets/689e2a9f-d93e-4417-9f96-19fd86818005)
![2](https://github.com/user-attachments/assets/3fe234f7-b4fa-4cbc-a8e4-2114ae3cf102)
![3](https://github.com/user-attachments/assets/c578a88d-b044-4fa2-922c-78![4](https://github.com/user-attachments/assets/bdf6de66-becd-46b1-8ea1-5ac387f09bfa)
04e1432b35)

## Videos

https://github.com/user-attachments/assets/3eb57e5a-5048-47de-83a3-ed956dd14b73
https://github.com/user-attachments/assets/bcacb11a-032e-467d-a626-ce686c609b23
https://github.com/user-attachments/assets/3af8717c-1401-49d2-a916-b31e1aa85cad





## Real-World Applications
The knitting robot could be used in textile prototyping, allowing designers to test new patterns and fabric types quickly. It could also be useful for small-scale textile production in custom-made fashion.


## Conclusion

The Knitting Robot is a unique blend of robotics, software, and knitting technology. By automating the knitting process, this project aims to make knitting more accessible, efficient, and customizable.

## License

Distributed under the MIT License. See LICENSE.txt for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/badge/CONTRIBUTORS-6-brightgreen?style=for-the-badge
[contributors-url]: https://github.com/epfl-cs358/2024sp-exoskeleton/graphs/contributors
[license-shield]: https://img.shields.io/badge/LICENSE-MIT-brightyellow?style=for-the-badge
[license-url]: https://github.com/epfl-cs358/2024sp-exoskeleton/blob/main/LICENSE
