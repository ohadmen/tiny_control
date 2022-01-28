cmake_minimum_required(VERSION 3.8)
project(controller)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# ------ motors_driver_node ------
add_executable(motors_driver_node src/motors_driver_node.cpp)
target_include_directories(motors_driver_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(motors_driver_node rclcpp std_msgs)
target_compile_features(motors_driver_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
install(TARGETS motors_driver_node DESTINATION lib/${PROJECT_NAME})

# ------ joystick_node ------
add_executable(joystick_node src/joystick_node.cpp)
target_include_directories(joystick_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
  ament_target_dependencies(joystick_node rclcpp std_msgs)
  target_compile_features(joystick_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
install(TARGETS joystick_node DESTINATION lib/${PROJECT_NAME})


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
