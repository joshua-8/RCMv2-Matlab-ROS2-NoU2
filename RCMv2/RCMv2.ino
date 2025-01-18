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
    numSubscribers = 10; // change max number of subscribers
}

#include <example_interfaces/msg/bool.h>
#include <example_interfaces/msg/float32_multi_array.h>
#include <std_msgs/msg/multi_array_layout.h>
// and lots of other message types are available (see file available_ros2_types)

// declare publishers
declarePub(telemetry, example_interfaces__msg__Float32MultiArray);

declareSubAndCallback(control, example_interfaces__msg__Float32MultiArray);
if (controlMsg->data.size == 10) {
    motor1Val = controlMsg->data.data[0];
    motor2Val = controlMsg->data.data[1];
    motor3Val = controlMsg->data.data[2];
    motor4Val = controlMsg->data.data[3];
    motor5Val = controlMsg->data.data[4];
    motor6Val = controlMsg->data.data[5];
    servo1Val = controlMsg->data.data[6];
    servo2Val = controlMsg->data.data[7];
    servo3Val = controlMsg->data.data[8];
    servo4Val = controlMsg->data.data[9];
}
} // end of callback

void ROSbegin()
{
    // create publishers
    createPublisher(telemetry, example_interfaces__msg__Float32MultiArray, "/rcm/telemetry");

    telemetryMsg.data.capacity = 2; // CHANGE TO ADD MORE

    telemetryMsg.data.data = (float*)malloc(telemetryMsg.data.capacity * sizeof(float));
    telemetryMsg.data.size = telemetryMsg.data.capacity;

    // add subscribers
    // note, there's a built in /rcm/enabled subscriber
    // allocate memory for the message
    controlMsg.data.capacity = 100;
    controlMsg.data.size = 0;
    controlMsg.data.data = (float*)malloc(controlMsg.data.capacity * sizeof(float));
    controlMsg.layout.data_offset = 0;
    controlMsg.layout.dim.capacity = 100;
    controlMsg.layout.dim.size = 0;
    controlMsg.layout.dim.data = (example_interfaces__msg__MultiArrayDimension*)malloc(controlMsg.layout.dim.capacity * sizeof(example_interfaces__msg__MultiArrayDimension));
    for (size_t i = 0; i < controlMsg.layout.dim.capacity; i++) {
        controlMsg.layout.dim.data[i].label.capacity = 20;
        controlMsg.layout.dim.data[i].label.size = 0;
        controlMsg.layout.dim.data[i].label.data = (char*)malloc(controlMsg.layout.dim.data[i].label.capacity * sizeof(char));
    }

    addSub(control, example_interfaces__msg__Float32MultiArray, "/rcm/control");
}

void ROSrun()
{
    rosSpin(50); // 20Hz
    // you can add more data to publish here
    telemetryMsg.data.data[0] = voltageComp.getSupplyVoltage();
    telemetryMsg.data.data[1] = (float)millis();
    publish(telemetry);
}
#endif

#include "rcmutil.h"
