# RCMv2-Matlab-ROS2-NoU2
https://github.com/joshua-8/RCMv2-Matlab-ROS2-NoU2

### [video of test](https://github.com/joshua-8/RCMv2-Matlab-ROS2-NoU2/discussions/1)

### This is an example of controlling an Alfredo Systems NoU2 board from Matlab over Wifi using ROS 2 and micro-ros for communication

## based on the [RCMv2](https://github.com/rcmgames/rcmv2) software framework

## compatible with
* [Alfredo Systems NoU2](https://www.alfredosys.com/products/alfredo-nou2/)

## SETUP
(notes from my setup on Windows)
* install ROS2 iron on Ubuntu inside VMware Workstation, with the network set as Bridged
    * the interface between micro ros on the esp32 and ROS2 needs Linux
    * (I tried WSL but it didn't work)
    * https://docs.ros.org/en/iron/Installation/Ubuntu-Install-Debs.html
* install ros addon for matlab
* clone this repository to your computer, open it in VS Code, and install the PlatformIO extension

## EXAMPLE
* (I connected my computer to a wifi network from my phone since I didn't want to connect the NoU to university wifi)
* in the Ubuntu VM, in a terminal, run: sudo docker run -it --rm --net=host microros/micro-ros-agent:iron udp4 --port 8888
* find set_microros_wifi_transports() in RCMV2/RCMv2.ino and change "router", and "password" to your wifi network name and password
* also in set_microros_wifi_transports() change "192.168.43.110" to the ip address of the Ubuntu VM
* upload the code to the NoU2 board using platformio (sorry, for now you have to do this every time your computer's ip address changes)
* If the blue light on the NoU2 blinks quickly, that means it didn't find the wifi network or your computer. Restart the NoU2.
    * you should see things print in the terminal of the Ubuntu VM where the micro-ros-agent is running "create_topic" and "subscriber_created"
* open MATLAB/nou2_example.m in MATLAB and run it
* motors 1 and 2 and servos 1 and 2 should move once a second

### Known issues:
* subscribing to more than 4 motors/servos causes an RCCHECK error
   * If values for all 10 motors/servos can be sent as an array in one message that might be the best way to fix this (and also reduce how many messages need to be sent)

### Libraries used:
* [JMotor](https://github.com/joshua-8/JMotor) library for motor control
* [micro-ROS](https://micro.ros.org/) for communication
