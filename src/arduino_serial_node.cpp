#include <ros/ros.h>
#include <std_msgs/Int16.h>
#include <rosserial_arduino/Serial.h>

ros::NodeHandle nh;
rosserial_arduino::Serial serial; 

// Callback for incoming "steer_commands"
void steeringCommandCallback(const std_msgs::Int16::ConstPtr& msg) {  
    // Build the servo command string
    String command = "h "; 
    command += String(msg->data); 
    command += "\r\n"; // Ensure correct line termination

    // Send the command to the Arduino
    serial.write(command.c_str()); 
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "arduino_serial_node");  

  // Configure and open serial port
  if (nh.getParam("/port", port_name)) {
    serial.setPort("/dev/ttyACM0"); 
    serial.setBaudrate(57600);  // Match your Arduino's baudrate
  } else {
    ROS_ERROR("Serial port not specified");
    return -1; 
  } 
  serial.open();

  // Subscribe to the "steer_commands" topic which will carry messages from joy_input_node
  ros::Subscriber steer_sub = nh.subscribe("steer_commands", 10, steeringCommandCallback); 

  ros::spin();
  return 0;
}