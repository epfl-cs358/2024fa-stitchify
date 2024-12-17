# Stitchify


<!-- ABOUT THE PROJECT -->
## About The Project
Fueled by curiosity, we worked to create a knitting machine from start to finish. We based our work on the open source project OpenKnit, and spent a lot of time analysing and researching about how to go about in creating our machine. We obviously didn't have 5-6 years like OpenKnit did, so we had to simplify OpenKnit's design by a lot in order to fit the time frame of 10 weeks.
<!-- High-level structure -->
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
![image](https://github.com/user-attachments/assets/b4b510b4-6ebb-4623-97de-5d04ebab56fb)

## Mechanical Designs 
 * **Carriage** :
 * **Aluminium structure** :
 * **Electronic supports** :
 * **Flatbed** :
 * **Yarn feeder, slider** :
 * **Stepper motor and belt pincher** :
 * **Comb** :

## Code Implementation
The code implementation included the master-slave data sharing channel and management, the controller for the stepper motor (slave) and servo motors (master) as well as a simple command interpreter. 

## Knitting Process


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

**10. ESP32-CAM vs Wemos D1 R32 vs Arduino Uno** : We originally wanted to use the ESP32-CAM as it had built-in wifi connectivity and would allow wireless communication with the main Arduino Uno, in addition to its small size. However, we discovered that in the way we wanted to use it, there would only be a very small number of usable pins, which wasn't enough at all. We decided to look into the Wemos R32, which also had built-in wifi and looked a lot like an Arduino Uno. But there was a lot of pins adaptation issues as the Wemos uses a different pin naming pattern. In the end, we just decided to use an additional Arduino Uno for prototype 1 and will try to use the Wemos R1 D32 for connectivity with the webapp. 

<!-- Implementation -->
## Step-by-step 
