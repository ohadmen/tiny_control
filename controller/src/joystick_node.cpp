#include <cstdio>
#include <fstream>      // std::ifstream
#include "rclcpp/rclcpp.hpp"
#include "controller/msg/joystick_update.hpp"   
#include "defs.h"


class JoystickListener : public rclcpp::Node
{

public:
  JoystickListener()
      : Node("joystick_listener")
  {
    auto event = controller::msg::JoystickUpdate();
    std::ifstream fd(tc::joystick_port, std::ifstream::in);
    // rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
    auto publisher = this->create_publisher<controller::msg::JoystickUpdate>(tc::joystick_topic, 10);
    RCLCPP_INFO(this->get_logger(), "Starting joystick node");
    while (rclcpp::ok())
    {
      fd.read(reinterpret_cast<char *>(&event), sizeof(controller::msg::JoystickUpdate));
      if (!fd)
      {
        continue;
      }
      
      // if (e.type == JSevent::etype::button)
      // {
          
      //   message.data =  "Button: time:" + std::to_string(e.time) + " value:" + std::to_string(e.value) + " number:" +std::to_string(e.number);
      // }
      // else
      // {
      //   message.data =  "Axis: time:" + std::to_string(e.time) + " value:" + std::to_string(e.value) + " number:" + std::to_string(e.number);
      // }
      // RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
      publisher->publish(event);
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
