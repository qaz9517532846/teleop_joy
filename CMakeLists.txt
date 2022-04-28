cmake_minimum_required(VERSION 3.0.2)
project(teleop_joy)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  sensor_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES teleop_joy
#  CATKIN_DEPENDS geometry_msgs roscpp sensor_msgs
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(teleop_joy src/teleop_joy.cpp)
target_link_libraries(teleop_joy ${catkin_LIBRARIES})