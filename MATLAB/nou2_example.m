compNode=ros2node("/computer",0);

enablePub=ros2publisher(compNode,"/rcm/enabled","example_interfaces/Bool");
enableMsg=ros2message(enablePub);

motor1Pub=ros2publisher(compNode,"/rcm/motor1","std_msgs/Float32");
motor1Msg=ros2message(motor1Pub);

motor2Pub=ros2publisher(compNode,"/rcm/motor2","std_msgs/Float32");
motor2Msg=ros2message(motor2Pub);

servo1Pub=ros2publisher(compNode,"/rcm/servo1","std_msgs/Float32");
servo1Msg=ros2message(servo1Pub);

servo2Pub=ros2publisher(compNode,"/rcm/servo2","std_msgs/Float32");
servo2Msg=ros2message(servo2Pub);

loopCount=0;

while(true)
    enableMsg.data=true;
    send(enablePub,enableMsg); % nou will shut off outputs if this stops running

     if(mod(loopCount,200)<100)
         motor1Msg.data=single(1.0);
         motor2Msg.data=single(0.5);
         servo1Msg.data=single(1.0);
         servo2Msg.data=single(0.5);
     else
         motor1Msg.data=single(-1.0);
         motor2Msg.data=single(-0.5);
         servo1Msg.data=single(-1.0);
         servo2Msg.data=single(-0.5);
     end

     send(motor1Pub,motor1Msg);
     send(motor2Pub,motor2Msg);
     send(servo1Pub,servo1Msg);
     send(servo2Pub,servo2Msg);
 
     pause(0.01);
     loopCount=loopCount+1;
 end