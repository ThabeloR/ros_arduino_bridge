/***************************************************************
   Servo Sweep - by Nathaniel Gallinger

   Sweep servos one degree step at a time with a user defined
   delay in between steps.  Supports changing direction 
   mid-sweep.  Important for applications such as robotic arms
   where the stock servo speed is too fast for the strength
   of your system.

 *************************************************************/

#ifdef USE_SERVOS

// Constants
const int MAX_STEERING_ANGLE = 45; // Maximum angle for inner wheel
const float WHEELBASE = 65.0;   
const float TRACK_WIDTH = 63.5; 

// Servo Objects (Assumes you have four defined)
const int FRONT_LEFT_STEERING_SERVO = 1; 
const int FRONT_RIGHT_STEERING_SERVO = 2;
const int REAR_LEFT_STEERING_SERVO = 3;
const int REAR_RIGHT_STEERING_SERVO = 0;  
// Constructor
SweepServo::SweepServo()
{
  this->currentPositionDegrees = 0;
  this->targetPositionDegrees = 0;
  this->lastSweepCommand = 0;
}


// Init
void SweepServo::initServo(
    int servoPin,
    int stepDelayMs,
    int initPosition)
{
  this->servo.attach(servoPin);
  this->stepDelayMs = stepDelayMs;
  this->currentPositionDegrees = initPosition;
  this->targetPositionDegrees = initPosition;
  this->lastSweepCommand = millis();
}


// Perform Sweep
void SweepServo::doSweep()
{

  // Get ellapsed time
  int delta = millis() - this->lastSweepCommand;

  // Check if time for a step
  if (delta > this->stepDelayMs) {
    // Check step direction
    if (this->targetPositionDegrees > this->currentPositionDegrees) {
      this->currentPositionDegrees++;
      this->servo.write(this->currentPositionDegrees);
    }
    else if (this->targetPositionDegrees < this->currentPositionDegrees) {
      this->currentPositionDegrees--;
      this->servo.write(this->currentPositionDegrees);
    }
    // if target == current position, do nothing

    // reset timer
    this->lastSweepCommand = millis();
  }
}


// Set a new target position  `1
void SweepServo::setTargetPosition(int position)
{
  this->targetPositionDegrees = position;
}

// Ackermann Steering Calculation Function
void setServoAnglesForSteering(float steeringInput, float turningRadius) {
  // Simplified Ackermann Calculation (adjust based on your setup)
  float innerAngleRadians = atan2(WHEELBASE, (turningRadius - TRACK_WIDTH/2)); 
  float outerAngleRadians = atan2(WHEELBASE, (turningRadius + TRACK_WIDTH/2));
  float innerAngle = innerAngleRadians * 180.0f / PI;
  float outerAngle = outerAngleRadians * 180.0f / PI;
 
  // Apply Steering Logic with Ackermann
  int frontLeftServoAngle, frontRightServoAngle, rearLeftServoAngle, rearRightServoAngle;

  if (steeringInput > 0) { // Right Turn
    frontLeftServoAngle = map(outerAngle, -MAX_STEERING_ANGLE, MAX_STEERING_ANGLE, 25, 155); 
    frontRightServoAngle = map(innerAngle, -MAX_STEERING_ANGLE, MAX_STEERING_ANGLE, 25, 155);

    // Adjust rear angles as required
    rearLeftServoAngle = map(-innerAngle/ 2.0f , -MAX_STEERING_ANGLE / 2, MAX_STEERING_ANGLE / 2, 25, 155);
    rearRightServoAngle = map(-outerAngle / 2.0f , -MAX_STEERING_ANGLE / 2, MAX_STEERING_ANGLE / 2, 25, 155); 

  } else if (steeringInput < 0) { // Left Turn
    // Similar logic as right turn, with inverted angles for inner and outer wheels
    frontLeftServoAngle = map(-outerAngle, -MAX_STEERING_ANGLE, MAX_STEERING_ANGLE, 25, 155); 
    frontRightServoAngle = map(-innerAngle, -MAX_STEERING_ANGLE, MAX_STEERING_ANGLE, 25, 155);

    // Adjust rear angles as required
    rearLeftServoAngle = map(innerAngle/ 2.0f  , -MAX_STEERING_ANGLE / 2, MAX_STEERING_ANGLE / 2, 25, 155);
    rearRightServoAngle = map(outerAngle/ 2.0f  , -MAX_STEERING_ANGLE / 2, MAX_STEERING_ANGLE / 2, 25, 155); 
    // ...
  } else { 
    // ... Set all servos to center for straight steering 
    frontLeftServoAngle = frontRightServoAngle = rearLeftServoAngle = rearRightServoAngle = 90;
  }

  // Apply calculated angles to servos
  servos[FRONT_LEFT_STEERING_SERVO].setTargetPosition(frontLeftServoAngle);
  servos[FRONT_RIGHT_STEERING_SERVO].setTargetPosition(frontRightServoAngle);
  servos[REAR_LEFT_STEERING_SERVO].setTargetPosition(rearLeftServoAngle);
  servos[REAR_RIGHT_STEERING_SERVO].setTargetPosition(rearRightServoAngle);
}


// Accessor for servo object
Servo SweepServo::getServo()
{
  return this->servo;
}


#endif
