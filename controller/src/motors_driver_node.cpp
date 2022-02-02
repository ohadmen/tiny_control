#include <cstdio>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "controller/msg/joystick_update.hpp"   
#include "defs.h"
#include <array>
using std::placeholders::_1;

class JoystickState : public rclcpp::Node
{
  std::array<uint16_t,8> m_axis;
  std::array<bool,12> m_button;
  uint32_t m_lastUpdate;
  public:
    JoystickState()
    : Node("joystick_state")
    {
      subscription_ = this->create_subscription<controller::msg::JoystickUpdate>(
      tc::joystick_topic, 10, std::bind(&JoystickState::topic_callback, this, _1));
    }

  private:
    void topic_callback(const controller::msg::JoystickUpdate::SharedPtr msg) 
    {
      m_lastUpdate = msg.get()->time;
      std::string message;
            if (msg.get()->type == 1)
      {
        m_button[msg.get()->number]=msg.get()->value;
        message  =  "Button: time:" + std::to_string(msg.get()->time) + " value:" + std::to_string(msg.get()->value) + " number:" +std::to_string(msg.get()->number);
      }
      else
      {
        m_axis[msg.get()->number]=msg.get()->value;
        message =  "Axis: time:" + std::to_string(msg.get()->time) + " value:" + std::to_string(msg.get()->value) + " number:" + std::to_string(msg.get()->number);
      }
      RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.c_str());

      
    }
    rclcpp::Subscription<controller::msg::JoystickUpdate>::SharedPtr subscription_;
};

int main(int argc, char ** argv)
{

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<JoystickState>());
  rclcpp::shutdown();
  return 0;
}
