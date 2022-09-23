## Line Following Robot
<p>A PID controlled Line Following Robot(LFR) is hardware project for Robotics course(CSE461).The robot follows the black path by measuring the value of IR sensor which is attached with the robot's front.The IR sensor sends data to arduino UNO and UNO command the motor driver to run accordingly by calculating the PID.the benefits of adding the PID here is,it can make sure the robot to run smoothly otherwise there'll be a chance to dislocate the robot from the track.</p>


### Components 
1. 5V yellow motor
2. 9V battery for motor driver
3. L298N motor driver
4. Wheel
5. 5 array IR sensor
6. PVC as chesis
7. LI-ION battery

### PID formula
` int motorSpeed = Kp * error + Ki * errorSum + Kd * (error - lastError);`