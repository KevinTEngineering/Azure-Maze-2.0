/*
   THIS IS FOR TESTING BOTH BALL PUMPS
*/

#include "SpeedyStepper.h"

SpeedyStepper BallPump1;
SpeedyStepper BallPump2;

const byte BALL_PUMP_SELECTOR_POT = A7; // POT

const long BALL_PUMP_1_STEPS_PER_REV = 200 * 5;
const long BALL_PUMP_1_MICROSTEPPING = 8;
const long BALL_PUMP_1_STEPS_PER_REV_INCLUDING_MICROSTEPPING = (BALL_PUMP_1_STEPS_PER_REV * BALL_PUMP_1_MICROSTEPPING);
const long BALL_PUMP_1_SPEED_IN_SPS = 750; // 5000; // 750;
const long BALL_PUMP_1_ACCELERATION_IN_RPSS = 5000;
const byte BALL_PUMP_1_HOME_SENSOR = 24;          // barrel sensor
const byte BALL_PUMP_1_SENSOR = 28;               // Optical Ball sensor
const long BALL_PUMP_1_DIRECTION_TOWARD_HOME = -1; // -1 is CCW
const long BALL_PUMP_1_DIRECTION = -1;             // -1 is CCW 15000
const long BALL_PUMP_1_MAX_STEPS = 15000;

const long BALL_PUMP_2_STEPS_PER_REV = 200 * 5;
const long BALL_PUMP_2_MICROSTEPPING = 8;
const long BALL_PUMP_2_STEPS_PER_REV_INCLUDING_MICROSTEPPING = (BALL_PUMP_1_STEPS_PER_REV * BALL_PUMP_1_MICROSTEPPING);
const long BALL_PUMP_2_SPEED_IN_SPS = 750; // 5000; // 750;
const long BALL_PUMP_2_ACCELERATION_IN_RPSS = 5000;
const byte BALL_PUMP_2_HOME_SENSOR = 27;           // barrel sensor
const byte BALL_PUMP_2_SENSOR = 29;                // Optical ball sensor
const long BALL_PUMP_2_DIRECTION_TOWARD_HOME = 1; // -1 is CCW
const long BALL_PUMP_2_DIRECTION = 1;             // -1 is CCW
const long BALL_PUMP_2_MAX_STEPS = 1500000;

void setup()
{

  Serial.begin(9600);
  Serial.println("Setup begins");

  pinMode(BALL_PUMP_SELECTOR_POT, INPUT_PULLUP);

  BallPump1.connectToPort(1);
  BallPump1.setStepsPerRevolution(BALL_PUMP_1_STEPS_PER_REV * BALL_PUMP_1_MICROSTEPPING);
  BallPump1.setSpeedInStepsPerSecond(BALL_PUMP_1_SPEED_IN_SPS);
  BallPump1.setAccelerationInStepsPerSecondPerSecond(BALL_PUMP_1_ACCELERATION_IN_RPSS);
  BallPump1.disableStepper();

  pinMode(BALL_PUMP_1_SENSOR, INPUT_PULLUP);
  pinMode(29, INPUT_PULLUP);
  pinMode(BALL_PUMP_1_HOME_SENSOR, INPUT_PULLUP);

  BallPump2.connectToPort(2);
  BallPump2.setStepsPerRevolution(BALL_PUMP_2_STEPS_PER_REV * BALL_PUMP_2_MICROSTEPPING);
  BallPump2.setSpeedInStepsPerSecond(BALL_PUMP_2_SPEED_IN_SPS);
  BallPump2.setAccelerationInStepsPerSecondPerSecond(BALL_PUMP_2_ACCELERATION_IN_RPSS);
  BallPump2.disableStepper();

  pinMode(BALL_PUMP_2_SENSOR, INPUT);
  pinMode(BALL_PUMP_2_HOME_SENSOR, INPUT_PULLUP);

  int ballPumpSelector = 0;
  int ballPump1HomeSensorState = 0;
  int ballPump2HomeSensorState = 0;

  // BALL PUMPS SETUP HERE//

  Serial.println("Start Homing Ball Pump 1");
  BallPump1.enableStepper();
  // Don't Assume the Ball Pump Is correctly homed, offset and ready to accept a ball - so rotate some first then home
  BallPump1.moveRelativeInSteps(100 * BALL_PUMP_1_DIRECTION_TOWARD_HOME);
  BallPump1.moveToHomeInSteps(BALL_PUMP_1_DIRECTION_TOWARD_HOME, BALL_PUMP_1_SPEED_IN_SPS,
                              BALL_PUMP_1_MAX_STEPS, BALL_PUMP_1_HOME_SENSOR);
  BallPump1.disableStepper();
   ballPump1HomeSensorState = digitalRead(BALL_PUMP_1_HOME_SENSOR);
  Serial.print("BALL_PUMP#1_HOME_SENSOR_STATE = ");
  Serial.println(ballPump1HomeSensorState);
  Serial.println("Ball Pump 1 Homed");
  Serial.println("Moving to allow ball to enter gate");
  // Homing sensor is located such that ball will not enter gate - at home so we have to rotate it - to allow ball to enter gate.
//  BallPump1.enableStepper();
//   BallPump1.moveRelativeInSteps(3500 * BALL_PUMP_1_DIRECTION_TOWARD_HOME);
//  BallPump1.disableStepper();
  Serial.println("Ball Pump 1 Ready for Ball");



//  Serial.println("Start Homing Ball Pump 2");
//  BallPump2.enableStepper();
//  // Don't Assume the Ball Pump Is correctly homed, offset and ready to accept a ball - so rotate some first then home
//  BallPump2.moveRelativeInSteps(10000 * BALL_PUMP_2_DIRECTION_TOWARD_HOME);
//  BallPump2.moveToHomeInSteps(BALL_PUMP_2_DIRECTION_TOWARD_HOME, BALL_PUMP_2_SPEED_IN_SPS,
//                              BALL_PUMP_2_MAX_STEPS, BALL_PUMP_2_HOME_SENSOR);
//  BallPump2.disableStepper();
//  ballPump2HomeSensorState = digitalRead(BALL_PUMP_2_HOME_SENSOR);
//  Serial.print("BALL_PUMP#2_HOME_SENSOR_STATE = ");
//  Serial.println(ballPump2HomeSensorState);
//  Serial.println("Ball Pump 2 Homed");
////      Serial.println("Moving to allow ball to enter gate");
////      // Homing sensor is located such that ball will not enter gate - at home so we have to rotate it - to allow ball to enter gate.
////      BallPump2.enableStepper();
////      BallPump2.moveRelativeInSteps(3500 * BALL_PUMP_2_DIRECTION_TOWARD_HOME);
////      BallPump2.disableStepper();
//  Serial.println("Ball Pump 2 Ready for Ball");


  Serial.println("setup complete");
  delay(1000);
}
double correction = 1;

void loop()
{
//  Serial.print("Port 23 status");
//  Serial.println(digitalRead(23));
//    Serial.print("Current pos: ");
//    Serial.println(BallPump1.getCurrentPositionInSteps());
    int ballPump1HomeSensorState = 0;
    ballPump1HomeSensorState = digitalRead(BALL_PUMP_1_HOME_SENSOR);
    Serial.print("BALL_PUMP#1_HOME_SENSOR_STATE = ");
    Serial.println(ballPump1HomeSensorState);
    int ballPumpHomeSensorState = 1;
    if (digitalRead(28) == LOW && digitalRead(23) == HIGH) // Select Pump 1
    {
  
      Serial.println("Pump 1");
      // Move Ball Pump 1
      //
      if ((digitalRead(28) == LOW)) // LOW for an active LOW sensor
      {                                              // Ball Detected - Pump ball
        Serial.println("Move Ball pump #1, one Rotation");
        Serial.println("Checking2");
        BallPump1.enableStepper();
        BallPump1.moveRelativeInSteps(BALL_PUMP_1_STEPS_PER_REV * 8.3 * BALL_PUMP_1_DIRECTION);
 
        BallPump1.disableStepper();
        Serial.println("Moved Ball pump #1, one Rotation");
        Serial.println(correction);
        correction += correction*0.8 - correction *.4;
      }
      else
      {
      
        Serial.println("No ball detected in ball pump #1");
        ballPumpHomeSensorState = digitalRead(BALL_PUMP_1_HOME_SENSOR);
        Serial.print("BALL_PUMP#1_HOME_SENSOR_STATE = ");
        Serial.println(ballPumpHomeSensorState);
      }
    }
  
  
    else if (digitalRead(28) == LOW && digitalRead(23) == LOW)// Select Pump 2
    {
      // Move Ball Pump 2

      Serial.println("Pump 2");
  
      if ((digitalRead(27)) == LOW) // HIGH for an active HIGH sensor
      {
        Serial.println("Move Ball pump #2, one Rotation");
        BallPump2.enableStepper();
        BallPump2.moveRelativeInSteps(BALL_PUMP_2_STEPS_PER_REV * 8 * BALL_PUMP_2_DIRECTION); //
        BallPump2.disableStepper();
        Serial.println("Moved Ball pump #2, one Rotation");
      }
      else
      {
        Serial.println("No ball detected in ball pump #2");
        ballPumpHomeSensorState = digitalRead(BALL_PUMP_2_HOME_SENSOR);
        Serial.print("BALL_PUMP#2_HOME_SENSOR_STATE = ");
        Serial.println(ballPumpHomeSensorState);
      }
    }
  delay(1000);
}
