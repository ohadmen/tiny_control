#include <cstdio>
#include <string>
#include <fcntl.h> //open
#include <unistd.h> //read
#include "rclcpp/rclcpp.hpp"
#include "controller/msg/joystick_update.hpp"
#include "defs.h"

class JoystickListener : public rclcpp::Node
{
  int m_fd;
  controller::msg::JoystickUpdate m_event;
  bool readInput()
  {
    auto &fd = m_fd;
    auto &event = m_event;

    ssize_t bytes = read(fd, &event, sizeof(controller::msg::JoystickUpdate));
    if (bytes != sizeof(controller::msg::JoystickUpdate))
        return false;
    std::string msg;
    if (event.type == 1)
      msg  =  "Button: time:" + std::to_string(event.time) + " value:" + std::to_string(event.value) + " number:" +std::to_string(event.number);
    else
      msg  =  "axis: time:" + std::to_string(event.time) + " value:" + std::to_string(event.value) + " number:" +std::to_string(event.number);
    RCLCPP_INFO(this->get_logger(), "%s",msg.c_str());
    return true;

  }

public:
  JoystickListener()
      : Node("joystick_listener"),

        m_fd(open(tc::joystick_port, O_RDONLY))


  {


    auto publisher = this->create_publisher<controller::msg::JoystickUpdate>(tc::joystick_topic, 10);
    RCLCPP_INFO(this->get_logger(), "Starting joystick node");
    while (rclcpp::ok())
    {
      if (!readInput())
      {
        continue;
      }

      publisher->publish(m_event);
    }
    RCLCPP_INFO(this->get_logger(), "exiting joystick node");
  }
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<JoystickListener>());
  rclcpp::shutdown();
  return 0;
}
