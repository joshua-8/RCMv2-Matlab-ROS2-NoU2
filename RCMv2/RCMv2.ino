//   This program is template code for programming small esp32 powered wifi controlled robots.
//   https://github.com/rcmgames/RCMv2
//   for information see this page: https://github.com/RCMgames

/**
UNCOMMENT ONE OF THE FOLLOWING LINES DEPENDING ON WHAT HARDWARE YOU ARE USING
Remember to also choose the "environment" for your microcontroller in PlatformIO
*/
// #define RCM_HARDWARE_VERSION RCM_ORIGINAL // versions 1, 2, 3, and 3.1 of the original RCM hardware // https://github.com/RCMgames/RCM_hardware_documentation_and_user_guide
// #define RCM_HARDWARE_VERSION RCM_4_V1 // version 1 of the RCM 4 // https://github.com/RCMgames/RCM-Hardware-V4
// #define RCM_HARDWARE_VERSION RCM_BYTE_V2 // version 2 of the RCM BYTE // https://github.com/RCMgames/RCM-Hardware-BYTE
// #define RCM_HARDWARE_VERSION RCM_NIBBLE_V1 // version 1 of the RCM Nibble // https://github.com/RCMgames/RCM-Hardware-Nibble
// #define RCM_HARDWARE_VERSION RCM_D1_V1 // version 1 of the RCM D1 // https://github.com/RCMgames/RCM-Hardware-D1
#define RCM_HARDWARE_VERSION ALFREDO_NOU2_NO_VOLTAGE_MONITOR // voltageComp will always report 10 volts https://www.alfredosys.com/products/alfredo-nou2/
// #define RCM_HARDWARE_VERSION ALFREDO_NOU2_WITH_VOLTAGE_MONITOR // modified to add resistors VIN-30k-D36-10k-GND https://www.alfredosys.com/products/alfredo-nou2/
// #define RCM_HARDWARE_VERSION ALFREDO_NOU3 // https://www.alfredosys.com/products/alfredo-nou3/

/**
uncomment one of the following lines depending on which communication method you want to use
*/
// #define RCM_COMM_METHOD RCM_COMM_EWD // use the normal communication method for RCM robots
#define RCM_COMM_METHOD RCM_COMM_ROS // use the ROS communication method

#include "rcm.h" //defines pins

// set up motors and anything else you need here
// See this page for how to set up servos and motors for each type of RCM board:
// https://github.com/RCMgames/useful-code/tree/main/boards
// See this page for information about how to set up a robot's drivetrain using the JMotor library
// https://github.com/joshua-8/JMotor/wiki/How-to-set-up-a-drivetrain

// all the servo drivers
JMotorDriverEsp32Servo servo1Driver = JMotorDriverEsp32Servo(servo1port);
JMotorDriverEsp32Servo servo2Driver = JMotorDriverEsp32Servo(servo2port);
JMotorDriverEsp32Servo servo3Driver = JMotorDriverEsp32Servo(servo3port);
JMotorDriverEsp32Servo servo4Driver = JMotorDriverEsp32Servo(servo4port);

// all the motor drivers
JMotorDriverEsp32HBridge motorADriver = JMotorDriverEsp32HBridge(motor1port);
JMotorDriverEsp32HBridge motorBDriver = JMotorDriverEsp32HBridge(motor2port);
JMotorDriverEsp32HBridge motorCDriver = JMotorDriverEsp32HBridge(motor3port);
JMotorDriverEsp32HBridge motorDDriver = JMotorDriverEsp32HBridge(motor4port);
JMotorDriverEsp32HBridge motorEDriver = JMotorDriverEsp32HBridge(motor5port);
JMotorDriverEsp32HBridge motorFDriver = JMotorDriverEsp32HBridge(motor6port);

// variables for the drivers
float servo1Val = 0;
float servo2Val = 0;
float servo3Val = 0;
float servo4Val = 0;

float motor1Val = 0;
float motor2Val = 0;
float motor3Val = 0;
float motor4Val = 0;
float motor5Val = 0;
float motor6Val = 0;

void Enabled()
{
    // code to run while enabled, put your main code here
    servo1Driver.set(servo1Val);
    servo2Driver.set(servo2Val);
    servo3Driver.set(servo3Val);
    servo4Driver.set(servo4Val);

    motorADriver.set(motor1Val);
    motorBDriver.set(motor2Val);
    motorCDriver.set(motor3Val);
    motorDDriver.set(motor4Val);
    motorEDriver.set(motor5Val);
    motorFDriver.set(motor6Val);
}

void Enable()
{
    // turn on outputs
    servo1Driver.enable();
    servo2Driver.enable();
    servo3Driver.enable();
    servo4Driver.enable();

    motorADriver.enable();
    motorBDriver.enable();
    motorCDriver.enable();
    motorDDriver.enable();
    motorEDriver.enable();
    motorFDriver.enable();
}

void Disable()
{
    // turn off outputs
    servo1Driver.disable();
    servo2Driver.disable();
    servo3Driver.disable();
    servo4Driver.disable();

    motorADriver.disable();
    motorBDriver.disable();
    motorCDriver.disable();
    motorDDriver.disable();
    motorEDriver.disable();
    motorFDriver.disable();
}

void PowerOn()
{
    // runs once on robot startup, set pin modes and use begin() if applicable here
}

void Always()
{
    // always runs if void loop is running, JMotor run() functions should be put here
    // (but only the "top level", for example if you call drivetrainController.run() you don't also need to call leftMotorController.run())

    delay(1);
}

#if RCM_COMM_METHOD == RCM_COMM_EWD
void WifiDataToParse()
{
    enabled = EWD::recvBl();
    // add data to read here: (EWD::recvBl, EWD::recvBy, EWD::recvIn, EWD::recvFl)(boolean, byte, int, float)
}
void WifiDataToSend()
{
    EWD::sendFl(voltageComp.getSupplyVoltage());
    // add data to send here: (EWD::sendBl(), EWD::sendBy(), EWD::sendIn(), EWD::sendFl())(boolean, byte, int, float)
}

void configWifi()
{
    EWD::mode = EWD::Mode::connectToNetwork;
    EWD::routerName = "router";
    EWD::routerPassword = "password";
    EWD::routerPort = 25210;

    // EWD::mode = EWD::Mode::createAP;
    // EWD::APName = "rcm0";
    // EWD::APPassword = "rcmPassword";
    // EWD::APPort = 25210;
}
#elif RCM_COMM_METHOD == RCM_COMM_ROS ////////////// ignore everything below this line unless you're using ROS mode /////////////////////////////////////////////
void ROSWifiSettings()
{
    // SSID, password, IP, port (on a computer run: sudo docker run -it --rm --net=host microros/micro-ros-agent:iron udp4 --port 8888 )
    set_microros_wifi_transports("router", "password", "192.168.43.110", 8888); // doesn't complete until it connects to the wifi network
    nodeName = "nou_robot";
    numSubscribers = 40; // change max number of subscribers
}

#include <example_interfaces/msg/bool.h>
#include <std_msgs/msg/byte.h>
#include <std_msgs/msg/float32.h>
#include <std_msgs/msg/int32.h>
// and lots of other message types are available (see file available_ros2_types)
// #include <geometry_msgs/msg/twist.h>

// declare publishers
declarePub(milliseconds, std_msgs__msg__Int32);

// declare subscribers and write callback functions
declareSubAndCallback(cmd_m1, std_msgs__msg__Float32);
motor1Val = cmd_m1Msg->data;
} // end of callback

declareSubAndCallback(cmd_m2, std_msgs__msg__Float32);
motor2Val = cmd_m2Msg->data;
} // end of callback

declareSubAndCallback(cmd_m3, std_msgs__msg__Float32);
motor3Val = cmd_m3Msg->data;
} // end of callback

declareSubAndCallback(cmd_m4, std_msgs__msg__Float32);
motor4Val = cmd_m4Msg->data;
} // end of callback

declareSubAndCallback(cmd_m5, std_msgs__msg__Float32);
motor5Val = cmd_m5Msg->data;
} // end of callback

declareSubAndCallback(cmd_m6, std_msgs__msg__Float32);
motor6Val = cmd_m6Msg->data;
} // end of callback

declareSubAndCallback(cmd_s1, std_msgs__msg__Float32);
servo1Val = cmd_s1Msg->data;
} // end of callback

declareSubAndCallback(cmd_s2, std_msgs__msg__Float32);
servo2Val = cmd_s2Msg->data;
} // end of callback

declareSubAndCallback(cmd_s3, std_msgs__msg__Float32);
servo3Val = cmd_s3Msg->data;
} // end of callback

declareSubAndCallback(cmd_s4, std_msgs__msg__Float32);
servo4Val = cmd_s4Msg->data;
} // end of callback

void ROSbegin()
{
    // create publishers
    createPublisher(milliseconds, std_msgs__msg__Int32, "/rcm/milliseconds");
    millisecondsMsg.data = 0;

    // add subscribers
    // note, there's a built in /rcm/enabled subscriber

    // FOR SOME REASON THERE'S A MAXIMUM OF 4 SUBSCRIBERS
    addSub(cmd_m1, std_msgs__msg__Float32, "/rcm/motor1");
    addSub(cmd_m2, std_msgs__msg__Float32, "/rcm/motor2");
    // addSub(cmd_m3, std_msgs__msg__Float32, "/rcm/motor3");
    // addSub(cmd_m4, std_msgs__msg__Float32, "/rcm/motor4");
    // addSub(cmd_m5, std_msgs__msg__Float32, "/rcm/motor5");
    // addSub(cmd_m6, std_msgs__msg__Float32, "/rcm/motor6");
    addSub(cmd_s1, std_msgs__msg__Float32, "/rcm/servo1");
    addSub(cmd_s2, std_msgs__msg__Float32, "/rcm/servo2");
    // addSub(cmd_s3, std_msgs__msg__Float32, "/rcm/servo3");
    // addSub(cmd_s4, std_msgs__msg__Float32, "/rcm/servo4");
}

void ROSrun()
{
    rosSpin(1);
    // you can add more publishers here
    millisecondsMsg.data = millis();
    publish(milliseconds);
}
#endif

#include "rcmutil.h"
