#include <Zumo32U4.h>
#include <Wire.h>
Zumo32U4LCD lcd;

Zumo32U4OLED display;
Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4ButtonA buttonA;
const uint8_t sensorThreshold = 6; // this threshold based on the robot's sensor's sensitivity

// True if the robot is turning left (counter-clockwise).
bool turningLeft = false;

// True if the robot is turning right (clockwise).
bool turningRight = false;

unsigned int lineSensorValues[3];
unsigned int numofh=0;

void setup() {
  lineSensors.initThreeSensors();
  proxSensors.initFrontSensor();

  // Wait for the user to press A before driving the motors.
  display.clear();
  lcd.print("Press A for 1 house");
  buttonA.waitForButton();
  lcd.clear();
}

void turnRight() {
  motors.setSpeeds(-150, -150); 
  delay(100); 
  motors.setSpeeds(200, -200);
  delay(100); 
  turningLeft = false;
  turningRight = true;
}

void turnLeft() {
  motors.setSpeeds(-150, -150);
  delay(100); 
  motors.setSpeeds(-200, 200);
  delay(100); 
  turningLeft = true;
  turningRight = false;
}

void stopMotors() {
  motors.setSpeeds(0, 0);
  turningLeft = false;
  turningRight = false;
}

void objectMotors() {
  motors.setSpeeds(-150, -150);
  delay(100);
  stopMotors();
  delay(3000);
  motors.setSpeeds(0, 200);
  delay(2000);
  turningLeft = false;
  turningRight = false;
}

void loop() {
  do {
    // Read line sensors
    lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);
    proxSensors.read();
    uint8_t leftValue = proxSensors.countsFrontWithLeftLeds();
    uint8_t rightValue = proxSensors.countsFrontWithRightLeds();
    bool objectSeen = leftValue >= sensorThreshold || rightValue >= sensorThreshold;

    // Check if any of the sensors detect a line
    if (lineSensorValues[0] > 300 || lineSensorValues[1] > 300 || lineSensorValues[2] > 300) {
      // At least one sensor detects a line
      if (lineSensorValues[0] > 200 && lineSensorValues[1] < 200 && lineSensorValues[2] < 200) {
        // Only left sensor detects line, turn right
        turnRight();
        while (lineSensorValues[0] > 200) {
          lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);
        }
      } else if (lineSensorValues[0] < 200 && lineSensorValues[1] < 200 && lineSensorValues[2] > 200) {
        // Only right sensor detects line, turn left
        turnLeft();
        while (lineSensorValues[2] > 200) {
          lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);
        }
      } else if (lineSensorValues[0] > 300 && lineSensorValues[1] > 300 && lineSensorValues[2] > 300) {
        // All sensors detect line, stop
        motors.setSpeeds(300, -300);
        delay(150); // Adjust speed as needed
        while (lineSensorValues[2] > 300) {
          lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);
        }
      }else if (lineSensorValues[0] > 400 || lineSensorValues[1] > 400 || lineSensorValues[2] > 400) {
        // All sensors detect line, stop
        motors.setSpeeds(300, -300);
        delay(150); // Adjust speed as needed
        while (lineSensorValues[1] > 300) {
          lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);
        }
      }
       else {
        // Either all sensors detect a line or a combination of left and right sensors detect a line
        // Make a sharp turn in the opposite direction
        if (lineSensorValues[2] > 100 && lineSensorValues[0] > 120 && lineSensorValues[1] > 100) {
          // Right sensor detects line more strongly, turn left
          motors.setSpeeds(-500, 200); // Turn left
          while (lineSensorValues[1] > 300) {
            lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);
          }
        }
      }
    } else {
      // No line detected, check for an object
      if (objectSeen) {
        delay(200);
        numofh++;
        lcd.print("del. to "+ numofh);
        objectMotors();
        while (leftValue >= sensorThreshold || rightValue >= sensorThreshold) {
          proxSensors.read();
          leftValue = proxSensors.countsFrontWithLeftLeds();
          rightValue = proxSensors.countsFrontWithRightLeds();
        }
      } else {
        // No line or object seen, continue forward
        motors.setSpeeds(100, 100);
      }
      //Attempt at mkaing the house stop after visiting two houses
      if(numofh==2){
        stopMotors();
      }
    }
    //re initialize prox sensor values
     proxSensors.read();
    leftValue = proxSensors.countsFrontWithLeftLeds();
    rightValue = proxSensors.countsFrontWithRightLeds();

    // Resume movement if no object is detected
    if (!objectSeen) {
      motors.setSpeeds(100, 100); // Continue forward
    }
    delay(50);
  } while (true); // Endless loop
}
