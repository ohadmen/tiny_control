#include <cstdio>
#include <fstream>      // std::ifstream
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "joystick_node.h"


class MinimalPublisher : public rclcpp::Node
{

public:
  MinimalPublisher()
      : Node("minimal_publisher")
  {
    JSevent e;
    std::ifstream fd("/dev/input/js0", std::ifstream::in);
    // rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
    auto publisher = this->create_publisher<std_msgs::msg::String>("topic", 10);
    while (true)
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
      publisher->publish(message);
    }
  }
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
