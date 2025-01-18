% Create a figure window for the sliders
fig = uifigure('Name', 'Motor and Servo Control', 'Position', [100, 100, 400, 700]);

% Create enable/disable switch
enableSwitch = uiswitch(fig,"Position",[200,650,100,100]);

% Create labels for telemetry
batteryVoltageLabel = uilabel(fig, 'Position', [20, 650, 360, 22], 'Text', 'Battery Voltage: 0');
millisLabel = uilabel(fig, 'Position', [20, 620, 360, 22], 'Text', 'Millis: 0');

% Create sliders for motor and servo control
sliders = gobjects(10, 1);
labels = ["Motor 1", "Motor 2", "Motor 3", "Motor 4", "Motor 5", "Motor 6", "Servo 1", "Servo 2", "Servo 3", "Servo 4"];
for i = 1:10
    uilabel(fig, 'Position', [20, 600 - 50 * i, 60, 22], 'Text', labels(i));
    sliders(i) = uislider(fig, 'Position', [100, 600 - 50 * i, 250, 3], 'Limits', [-1, 1], 'Value', 0);
end

compNode = ros2node("/computer", 0);

enablePub = ros2publisher(compNode, "/rcm/enabled", "example_interfaces/Bool");
enableMsg = ros2message(enablePub);

controlPub = ros2publisher(compNode, "/rcm/control", "example_interfaces/Float32MultiArray");
controlMsg = ros2message(controlPub);

ros2subscriber(compNode, "/rcm/telemetry", "example_interfaces/Float32MultiArray", @rcmTelemetryCallback, 'Reliability', 'besteffort');

% Initialize loop variables
loopCount = 0;

global batteryVoltage millis
batteryVoltage = 0;
millis = 0;

while true
    enableMsg.data = enableSwitch.Value=="On";
    send(enablePub, enableMsg); % nou will shut off outputs if this stops running

    % Read slider values
    motor1 = sliders(1).Value;
    motor2 = sliders(2).Value;
    motor3 = sliders(3).Value;
    motor4 = sliders(4).Value;
    motor5 = sliders(5).Value;
    motor6 = sliders(6).Value;
    servo1 = sliders(7).Value;
    servo2 = sliders(8).Value;
    servo3 = sliders(9).Value;
    servo4 = sliders(10).Value;

    controlMsg.data=single([motor1 motor2 motor3 motor4 motor5 motor6 servo1 servo2 servo3 servo4]);
    send(controlPub,controlMsg);

    % Update telemetry UI
    batteryVoltageLabel.Text = ['Battery Voltage: ', num2str(batteryVoltage)];
    millisLabel.Text = ['Millis: ', num2str(millis)];


    pause(0.05); %20Hz
    loopCount=loopCount+1;
end

function rcmTelemetryCallback(msg)
    global batteryVoltage millis
    batteryVoltage=msg.data(1);
    millis=msg.data(2);
end
