# Zumo-Maze-Solver
A Zumo 32U4 Robot that navigates a maze and recognizes houses to make deliveries
*Description:*
The Zumo32U4 Robot Line Follower and Delivery program is designed to enable a Zumo32U4 robot to autonomously navigate along a predefined path marked by lines while avoiding obstacles in its environment. The robot achieves this functionality through a combination of line sensors and proximity sensors.

Functionality:
1. *Line Following:* The robot utilizes three line sensors to detect lines on the ground. It follows the path by adjusting its movement based on the readings from these sensors. If the robot deviates from the path or encounters a junction, it makes appropriate turns to realign itself with the path.

2. *Obstacle Avoidance:* In addition to line following, the robot is equipped with front-facing proximity sensors. These sensors detect houses in the robot's path. When a house is detected, the robot stops, takes count, maneuvers around the house, and resumes its forward movement along the line.

3. *User Interaction:* The program requires user interaction to initiate the robot's operation. Before the robot starts moving, the user needs to press button A on the robot, as indicated on the LCD screen. Once the button is pressed, the robot begins its autonomous navigation.

Instructions for Use:
1. *Hardware Setup:*
   - Ensure that the Zumo32U4 robot is assembled correctly and all components are properly connected.
   - Attach the line sensors and proximity sensors to the appropriate ports on the robot.

2. *Software Setup:*
   - Install the necessary libraries for the Zumo32U4 robot, including the Zumo32U4 library.
   - Upload the provided Arduino sketch (`allsesnorswork.ino`) to the Zumo32U4 robot using the Arduino IDE or compatible software.

3. *Operation:*
   - Power on the Zumo32U4 robot.
   - Wait for the LCD screen to display the prompt: "Press A for 1 house."
   - Press button A on the robot to initiate the autonomous operation.
   - The robot will begin following the predefined path marked by lines while avoiding obstacles.
   - Monitor the robot's progress and intervene if necessary.

4. *User Interaction:*
   - If the robot encounters any issues or deviates from the path, the user can stop the robot manually by powering it off.
   - Adjustments to the robot's behavior can be made by modifying the code parameters in the Arduino sketch according to specific requirements.

Note:
- Ensure that the environment in which the robot operates is suitable for line following and obstacle avoidance. Clear any obstacles or debris that may interfere with the robot's movement.
- Exercise caution when operating the robot near edges or steep drops to prevent accidents or damage to the robot.

Author:
Kris Patrick

Acknowledgments:
- This project utilizes the Zumo32U4 library and associated hardware, developed by [Pololu Corporation](https://www.pololu.com/).

Disclaimer:
- This software and associated documentation are provided "as is" without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose, and non-infringement. In no event shall the authors or copyright holders be liable for any claim, damages, or other liability, whether in an action of contract, tort, or otherwise, arising from, out of, or in connection with the software or the use or other dealings in the software.
