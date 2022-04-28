# teleop_joy
How to control robot using a joystick.

------

## Built with

- ROS Foxy under Ubuntu 20.04 LTS

------

## Getting Started

### Installation

``` $ sudo apt-get install ros-foxy-joy```
    
------

### Run

Run teleop_joy launch.


``` bash
$ sudo chmod a+rw /dev/input/js0
```

``` bash
$ ros2 launch teleop_joy teleop_joy.launch.py
```

------

### Reference

[1]. joy, http://wiki.ros.org/joy

------

This repository is for your reference only. copying, patent application, academic journals are strictly prohibited.

Copyright © 2022 ZM Robotics Software Laboratory.
