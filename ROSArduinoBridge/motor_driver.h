/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/

#ifdef L298_MOTOR_DRIVER
  #define FRONT_RIGHT_MOTOR_BACKWARD 2
  #define FRONT_LEFT_MOTOR_BACKWARD  4
  #define FRONT_RIGHT_MOTOR_FORWARD  3
  #define FRONT_LEFT_MOTOR_FORWARD   5
  #define MID_RIGHT_MOTOR_BACKWARD 6
  #define MID_LEFT_MOTOR_BACKWARD  8
  #define MID_RIGHT_MOTOR_FORWARD  7
  #define MID_LEFT_MOTOR_FORWARD   9
  #define BACK_RIGHT_MOTOR_BACKWARD 10
  #define BACK_LEFT_MOTOR_BACKWARD  12
  #define BACK_RIGHT_MOTOR_FORWARD  11
  #define BACK_LEFT_MOTOR_FORWARD   13
  #define FRONT_RIGHT_MOTOR_ENABLE 40
  #define FRONT_LEFT_MOTOR_ENABLE 42
  #define MID_RIGHT_MOTOR_ENABLE 44
  #define MID_LEFT_MOTOR_ENABLE 46
  #define BACK_RIGHT_MOTOR_ENABLE 48
  #define BACK_LEFT_MOTOR_ENABLE 50
#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);
