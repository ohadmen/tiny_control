#include <cstdio>
#include <fstream>      // std::ifstream
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "joystick_node.h"
#include "defs.h"


class MinimalPublisher : public rclcpp::Node
{

public:
  MinimalPublisher()
      : Node("minimal_publisher")
  {
    JSevent e;
    std::ifstream fd(tc::joystick_port, std::ifstream::in);
    // rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
    auto publisher = this->create_publisher<std_msgs::msg::String>(tc::joystick_topic, 10);
    RCLCPP_INFO(this->get_logger(), "Starting joystick node");
    while (rclcpp::ok())
    {

      fd.read(reinterpret_cast<char *>(&e), sizeof(JSevent));
      if (!fd)
      {
        continue;
      }
      auto message = std_msgs::msg::String();
      if (e.type == JSevent::etype::button)
      {
          
        message.data =  "Button: time:" + std::to_string(e.time) + " value:" + std::to_string(e.value) + " number:" +std::to_string(e.number);
      }
      else
      {
        message.data =  "Axis: time:" + std::to_string(e.time) + " value:" + std::to_string(e.value) + " number:" + std::to_string(e.number);
      }
      RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
      publisher->publish(message);
    }
    RCLCPP_INFO(this->get_logger(), "exiting joystick node");
  }
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
